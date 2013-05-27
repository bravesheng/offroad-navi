#include <QPainter>
#include <QPaintEvent>
#include "RtPushButton.h"

RtPushButton::RtPushButton(QWidget *parent)
:QPushButton(parent), 
m_pimgUp(NULL), 
m_pimgDown(NULL), 
m_pimgSelect(NULL), 
m_pimgDisable(NULL), 
m_FontSize(8), 
m_AlignFlag(Qt::AlignCenter),
m_iListIndex(-1),
m_bIsScroll(false),
m_iStartY(0)
{
	resize(0,0);	//reset size to zero for SetImages auto-resize use.
    m_RectText = QRect();
}

void RtPushButton::SetListIndex(int iListIndex)
{
	m_iListIndex = iListIndex;
    if(m_iListIndex != -1)
	{
        connect(this, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
	}
}

void RtPushButton::mousePressEvent(QMouseEvent *event)
{
    m_bIsScroll = false;
    QPushButton::mousePressEvent(event);

    m_iStartY = event->y();
    emit MousePress(event->globalY());
}

void RtPushButton::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_bIsScroll)
	{
		QPushButton::mouseMoveEvent(event);
	}
    int iCurrentY = event->y();
    int iDiffY = iCurrentY-m_iStartY;
    if(iDiffY > __MOVE_INTERVAL__ || iDiffY < -__MOVE_INTERVAL__)
    {
		emit MoveInterval(iDiffY);
    }
}

void RtPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
    emit MouseRelease();
}

void RtPushButton::paintEvent(QPaintEvent *event)
{
    QPixmap *pimgDraw;
    if ( isDown() )
	{
        pimgDraw = m_pimgDown;
	}
    else if ( isChecked () )
	{
        pimgDraw = m_pimgSelect;
	}
    else if ( isEnabled())
	{
        pimgDraw = m_pimgUp;
	}
    else
	{
        if(m_pimgDisable)
		{
            pimgDraw = m_pimgDisable;
		}
        else
		{
            pimgDraw = m_pimgUp;
		}
	}
	if( !pimgDraw->isNull())
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *pimgDraw);

        //Draw Button Text
        if(!this->text().isEmpty())
        {
            //Set Text Font
            QFont font(tr("Arial"), m_FontSize);
            font.setStyleStrategy(QFont::PreferDefault);
            painter.setFont(font);

            //Set Text Color
            painter.setPen(QColor( Qt::white ));

            QRect RectText;
            if(m_RectText.isEmpty())
			{
                RectText = rect();
			}
            else
			{
                RectText = m_RectText;
			}
            painter.drawText(RectText,m_AlignFlag,this->text());
        }

        if(m_iListIndex != -1)
		{
            paintCustomEvent(event);
		}
   }
    else
    {
        QPushButton::paintEvent(event);
    }
}

void RtPushButton::SetImages(QPixmap *pimgUp,QPixmap *pimgDown,QPixmap *pimgSelect,QPixmap *pimgDisable)
{
    m_pimgUp = pimgUp;
    m_pimgDown = pimgDown;
    m_pimgSelect = pimgSelect;
    m_pimgDisable = pimgDisable;
	if(this->size().height() == 0)	//means size still not decided. So decide using image width and height.
	{
		if(m_pimgUp)
		{
			this->resize(m_pimgUp->width(), m_pimgUp->height());
		}
	}
}

void RtPushButton::SetButtonText(QString &strText,QRect &rectText, int Align, int FontSize)
{
    setText(strText);
    m_RectText = rectText;
	m_FontSize = FontSize;
	m_AlignFlag = Align;
}

int RtPushButton::GetImageHeight(void)
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

void RtPushButton::ButtonScroll()
{
    m_bIsScroll = true;
    setDown(false);
}

void RtPushButton::ButtonClicked()
{
    if(!m_bIsScroll)
	{
        emit ButtonClick(m_iListIndex);
	}
}
