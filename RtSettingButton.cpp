#include <QPainter>
#include <QPaintEvent>
#include "RtSettingButton.h"
#include "RtGlobalDefine.h"

RtSettingButton::RtSettingButton(QWidget *parent, int iListIndex)
        :QPushButton(parent)
{
	m_iIconBOffsetX = 0;
    m_iStartY = 0;
    m_bIsScroll = false;
    m_iListIndex = iListIndex;
	m_pimgIconA = NULL;
	m_pimgIconB = NULL;
	m_pimgUp = NULL;
    m_pimgDown = NULL;
    m_pimgSelect = NULL;
	m_pimgDisable = NULL;

    m_strText1 = tr("");
    m_strText2 = tr("");

    if(m_iListIndex != -1)
        connect(this, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
}

void RtSettingButton::mousePressEvent(QMouseEvent *event)
{
    m_bIsScroll = false;
    QPushButton::mousePressEvent(event);

    m_iStartY = event->y();
	m_iStartX = event->x();
    emit MousePress(event->globalY());
}

void RtSettingButton::mouseMoveEvent(QMouseEvent *event)
{
    if ( !m_bIsScroll )
            QPushButton::mouseMoveEvent(event);

    int iCurrentY = event->y();
	int iCurrentX = event->x();
    int iDiffY = iCurrentY-m_iStartY;
	int iDiffX = iCurrentX-m_iStartX;
    if ( iDiffY > __TOUCH_INTERVAL__ || iDiffY < -__TOUCH_INTERVAL__ )
    {
       emit MoveInterval( iDiffY );
    }

    if ( iDiffX > __TOUCH_INTERVAL__ || iDiffX < -__TOUCH_INTERVAL__ )
    {
       emit MoveIntervalX(m_iListIndex,iDiffX );
    }
}

void RtSettingButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
    emit MouseRelease();
}

void RtSettingButton::paintEvent(QPaintEvent *event)
{
    QPixmap *pimgDraw = NULL;
    if ( isDown() )
        pimgDraw = m_pimgDown;
    else if ( isChecked () )
        pimgDraw = m_pimgSelect;
    else if ( isEnabled())
        pimgDraw = m_pimgUp;
    else{
        if(m_pimgDisable)
            pimgDraw = m_pimgDisable;
        else
            pimgDraw = m_pimgUp;
   }
    if (pimgDraw != NULL)
    {
        QPainter painter(this);
		painter.drawPixmap(0, 0, *pimgDraw);

        if(m_iListIndex != -1)
        {
            QRect SrcRect = rect();

            //Set Text Font
            QFont font(g_strTitleFontFamily, g_iListFontPointSize);
            font.setStyleStrategy(QFont::PreferAntialias);
            painter.setFont(font);

            //Set Text Color
            painter.setPen(QColor( __TextBlackColor__ ));

            int iExtralWidth = 0;

            //Draw Icon2
            if(m_pimgIconB != NULL)
			{
				if(m_iIconBOffsetX == 0)
					m_iIconBOffsetX = __ICON2_OFFSETX__;

				painter.drawPixmap(m_iIconBOffsetX,(SrcRect.height()-m_pimgIconB->height())/2,*m_pimgIconB);
			}
            else
			{
                iExtralWidth += __ICON2_WIDTH__;
			}

            //Draw Text2
            if(!m_strText2.isEmpty())
            {
                QRect DistanceRect = QRect(__TEXT2_OFFSETX__,SrcRect.y(),__TEXT2_WIDTH__,SrcRect.height());
                painter.drawText(DistanceRect,Qt::AlignRight|Qt::AlignVCenter,m_strText2);
            }
            else
                iExtralWidth += __TEXT2_WIDTH__;

            //Draw Text1
            if(!m_strText1.isEmpty())
            {
                QRect TextRect = QRect(__TEXT1_OFFSETX__,SrcRect.y(),(__TEXT1_WIDTH__+iExtralWidth),SrcRect.height());
                painter.drawText(TextRect,Qt::AlignLeft|Qt::AlignVCenter,m_strText1);
            }

            //Draw Icon1
            if(m_pimgIconA != NULL)
                painter.drawPixmap(__ICON1_OFFSETX__,(SrcRect.height()-m_pimgIconA->height())/2,*m_pimgIconA);

        }
   }
    else
    {
        QPushButton::paintEvent(event);
    }
}

void RtSettingButton::SetImages(QPixmap *pimgUp, QPixmap *pimgDown, QPixmap *pimgSelect)
{
    m_pimgUp = pimgUp;
    m_pimgDown = pimgDown;
    m_pimgSelect = pimgSelect;
}

void RtSettingButton::ButtonScroll()
{
    m_bIsScroll = true;
    setDown(false);
}

void RtSettingButton::SetComponent(QPixmap *pIconA,QString &Text1,QString &Text2,QPixmap *pIconB)
{
    m_pimgIconA = pIconA;
    m_strText1 = Text1;
    m_strText2 = Text2;
    m_pimgIconB = pIconB;
}

void RtSettingButton::SetText1(QString &Text1)
{
	m_strText1 = Text1;
	update();
}

void RtSettingButton::SetIconB(QPixmap *pIconB)
{
	if(!m_pimgIconB)
		m_pimgIconB->detach();

    m_pimgIconB = pIconB;
    update();
}

void RtSettingButton::ButtonClicked()
{
    if(!m_bIsScroll)
        emit ButtonClick(m_iListIndex);
}

int RtSettingButton::GetImageHeight(void)
{
    int iTmpHeight = 0;
    if(m_pimgUp != NULL)
        iTmpHeight = m_pimgUp->height();
    else if(m_pimgDown != NULL)\
        iTmpHeight = m_pimgDown->height();
    else if(m_pimgSelect != NULL)\
        iTmpHeight = m_pimgSelect->height();
    else if(m_pimgDisable != NULL)
        iTmpHeight = m_pimgDisable->height();

    return iTmpHeight;
}

void RtSettingButton::SetIconB_OffsetX(int iOffsetX)
{
	if(iOffsetX != 0)
	   m_iIconBOffsetX = iOffsetX;
}