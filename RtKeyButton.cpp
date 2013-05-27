#include <QPainter>
#include <QPaintEvent>
#include "RtKeyButton.h"

RtKeyButton::RtKeyButton(QWidget *parent, int iListIndex)
        :QPushButton(parent)
{
    m_iStartY = 0;
    m_bIsScroll = false;
    m_iListIndex = iListIndex;
    m_RectText = QRect();
    m_LeftTop = QPoint(0,0);
    m_iStyle = AlignLeftTop;
    m_bExtKey = false;

    if(m_iListIndex != -1)
        connect(this, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
}

void RtKeyButton::mousePressEvent(QMouseEvent *event)
{
    m_bIsScroll = false;
    QPushButton::mousePressEvent(event);
    m_iStartY = event->y();

    emit MousePress(event->globalY(),m_iListIndex);
}

void RtKeyButton::mouseMoveEvent(QMouseEvent *event)
{
    if ( !m_bIsScroll )
            QPushButton::mouseMoveEvent(event);

    int iCurrentY = event->y();
    int iDiffY = iCurrentY-m_iStartY;
    if ( iDiffY > __MOVE_INTERVAL__ || iDiffY < -__MOVE_INTERVAL__ )
    {
       emit MoveInterval( iDiffY );
    }
}

void RtKeyButton::leaveEvent ( QEvent*) ///*event*/
{
    emit MouseRelease();
}

void RtKeyButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
    emit MouseRelease();
}

#define EXT_OFFSET_X    25
#define EXT_OFFSET_Y    25
#define EXT_WIDTH       15
#define EXT_HEIGHT      12
void RtKeyButton::paintEvent(QPaintEvent *event)
{
//    QPoint iOffset = QPoint(0,0);

    QPixmap *pimgDraw;
    if ( isDown() ) {
        pimgDraw = m_pimgDown;
//        iOffset = getLeftTopOffset(m_iStyle);
    }else if ( isChecked () ){
        pimgDraw = m_pimgSelect;
   }else if ( isEnabled()){
        pimgDraw = m_pimgUp;
    }else{
        if(m_pimgDisable)
            pimgDraw = m_pimgDisable;
        else
            pimgDraw = m_pimgUp;
   }

    if ( !pimgDraw->isNull())
    {
//        this->setGeometry(m_LeftTop.x()+iOffset.x(),m_LeftTop.y()+iOffset.y(),
//                          pimgDraw->width(),pimgDraw->height());

        QPainter painter(this);
        painter.drawPixmap(0, 0, *pimgDraw);

        //Draw Button Text
        if(!this->text().isEmpty())
        {
            //Set Text Font
            QFont font(tr("Arial"), 10);
            font.setStyleStrategy(QFont::PreferDefault);
            font.setBold(true);
            painter.setFont(font);

            //Set Text Color
            painter.setPen(QColor( Qt::black ));

            QRect RectText;
            if(m_RectText.isEmpty())
                RectText = rect();
            else
                RectText = m_RectText;

            painter.drawText(RectText,Qt::AlignCenter,text());

            //Draw the external key "..."
            if(m_bExtKey){
                QRect RectKey = rect();
                QRect RectExt((RectKey.width()-EXT_OFFSET_X),(RectKey.height()-EXT_OFFSET_Y),EXT_WIDTH,EXT_HEIGHT);
                painter.setPen(QColor( Qt::gray ));
                painter.drawText(RectExt,Qt::AlignCenter,"...");
            }
        }

        if(m_iListIndex != -1)
            paintCustomEvent(event);
   }
    else
    {
        QPushButton::paintEvent(event);
    }
}

void RtKeyButton::SetImages(QPixmap *pimgUp,QPixmap *pimgDown,QPixmap *pimgSelect,QPixmap *pimgDisable)
{
    m_pimgUp = pimgUp;
    m_pimgDown = pimgDown;
    m_pimgSelect = pimgSelect;
    m_pimgDisable = pimgDisable;
}

void RtKeyButton::setButtonText(QString &strText,QRect &rectText)
{
    setText(strText);
    m_RectText = rectText;
}

int RtKeyButton::GetImageHeight(void)
{
    int iTmpHeight = 0;
    if(m_pimgUp != NULL)
        iTmpHeight = m_pimgUp->height();
    else if(m_pimgDown != NULL)
        iTmpHeight = m_pimgDown->height();
    else if(m_pimgSelect != NULL)
        iTmpHeight = m_pimgSelect->height();
    else if(m_pimgDisable != NULL)
        iTmpHeight = m_pimgDisable->height();

    return iTmpHeight;
}

void RtKeyButton::ButtonScroll()
{
    m_bIsScroll = true;
    setDown(false);
}

void RtKeyButton::ButtonClicked()
{
    if(!m_bIsScroll)
        emit ButtonClick(m_iListIndex);
}

void RtKeyButton::setTopLeft(int iX,int iY)
{
    m_LeftTop = QPoint(iX,iY);
}

void RtKeyButton::setAlignStyle(int iStyle)
{
    m_iStyle = iStyle;
}

QPoint RtKeyButton::getLeftTopOffset(int iStyle)
{
    QPoint iOffset = QPoint(0,0);
    if(m_pimgUp->isNull()|| m_pimgDown->isNull())
        return iOffset;

    if(iStyle == AlignLeftTop){
    }else if(iStyle == AlignRightBottom){
        iOffset.setX((m_pimgUp->width() - m_pimgDown->width()));
        iOffset.setY((m_pimgUp->height() - m_pimgDown->height()));
    }else if(iStyle == AlignLeftBottom){
        iOffset.setY((m_pimgUp->height() - m_pimgDown->height()));
    }else if(iStyle == AlignRightTop){
        iOffset.setX((m_pimgUp->width() - m_pimgDown->width()));
    }else if(iStyle == AlignBottomCenter){
        iOffset.setX((m_pimgUp->width() - m_pimgDown->width())/2);
        iOffset.setY((m_pimgUp->height() - m_pimgDown->height()));
    }else if(iStyle == AlignTopCenter){
        iOffset.setX((m_pimgUp->width() - m_pimgDown->width())/2);
//        iOffset.setY((m_pimgUp->height() - m_pimgDown->height()));
    }else if(iStyle == AlignLeftCenter){
//        iOffset.setX((m_pimgUp->width() - m_pimgDown->width())/2);
        iOffset.setY((m_pimgUp->height() - m_pimgDown->height())/2);
    }else if(iStyle == AlignRightCenter){
        iOffset.setX((m_pimgUp->width() - m_pimgDown->width()));
        iOffset.setY((m_pimgUp->height() - m_pimgDown->height())/2);
    }else if(iStyle == AlignCenter){
        iOffset.setX((m_pimgUp->width() - m_pimgDown->width())/2);
        iOffset.setY((m_pimgUp->height() - m_pimgDown->height())/2);
    }

    return iOffset;
}

void RtKeyButton::setExtKey(bool bExtKey)
{
    m_bExtKey = bExtKey;
}
