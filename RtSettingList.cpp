#include <QTimer>
#include "RtSettingList.h"

RtSettingList::RtSettingList(QWidget *parent,int iX, int iY, int iWidth, int iHeight,bool bAutoScroll)
        :QWidget(parent)
{
    setGeometry(iX, iY, iWidth, iHeight);

    for (int i=0; i<__MAX_SETTING_ITEMS__; i++)
        m_pButtonList[i] = NULL;

    m_iItems = 0;
    m_iItemSelect = -1;
    m_iBoxHeight = 0;

    m_iPressY = 0;
    m_iLastScroll = 0;
	m_bAutoScroll = bAutoScroll;

    m_pimg1Up = NULL;
    m_pimg1Down = NULL;
    m_pimg1Select = NULL;
    m_pimg2Up = NULL;
    m_pimg2Down = NULL;
    m_pimg2Select = NULL;

	if(m_bAutoScroll)
	{
		m_pQTimerScroll = new QTimer(this);
		connect(m_pQTimerScroll, SIGNAL(timeout()), this, SLOT(AutoScroll()));

		m_pQTimerReset = new QTimer(this);
		connect(m_pQTimerReset, SIGNAL(timeout()), this, SLOT(ResetLastScroll()));
	}
}

void RtSettingList::SetImages1(QPixmap *pimgUp, QPixmap *pimgDown, QPixmap *pimgSelect)
{
    m_pimg1Up = pimgUp;
    m_pimg1Down = pimgDown;
    m_pimg1Select = pimgSelect;

    if(pimgUp->height()>0)
        m_iBoxHeight = pimgUp->height();
    else if(pimgDown->height()>0)
        m_iBoxHeight = pimgDown->height();
    else
        m_iBoxHeight = pimgSelect->height();

    //Set image item2 default as item1
    m_pimg2Up = m_pimg1Up;
    m_pimg2Down = m_pimg1Down;
    m_pimg2Select = m_pimg1Select;
}

void RtSettingList::SetImages2(QPixmap *pimgUp, QPixmap *pimgDown, QPixmap *pimgSelect)
{
    m_pimg2Up = pimgUp;
    m_pimg2Down = pimgDown;
    m_pimg2Select = pimgSelect;
}

RtSettingButton* RtSettingList::AddButton(QPixmap *pIconA,QString Text1,QString Text2,QPixmap *pIconB)
{
    if ( m_iItems >= __MAX_SETTING_ITEMS__ )
        return NULL;

    RtSettingButton* pButtonNew = new RtSettingButton(this, m_iItems);
    pButtonNew->setCheckable(true);
    if(m_iItems%2 == 0)
        pButtonNew->SetImages(m_pimg1Up, m_pimg1Down, m_pimg1Select);
    else
        pButtonNew->SetImages(m_pimg2Up, m_pimg2Down, m_pimg2Select);

    pButtonNew->SetComponent(pIconA,Text1,Text2,pIconB);

	if(m_bAutoScroll)
	{
		connect(pButtonNew, SIGNAL(MousePress(int)),   this,       SLOT(MousePress(int)));
		connect(pButtonNew, SIGNAL(MoveInterval(int)), this,       SLOT(ScrollList(int)));
		connect(pButtonNew, SIGNAL(MouseRelease()),    this,       SLOT(MouseRelease()));
	    connect(this,       SIGNAL(ButtonScroll()),    pButtonNew, SLOT(ButtonScroll()));
	}
    connect(pButtonNew, SIGNAL(ButtonClick(int)),  this,       SLOT(ListButtonClick(int)));
    connect(pButtonNew, SIGNAL(MoveIntervalX(int,int)), this,       SLOT(MouseMoveDffX(int,int)));


    QRect rect;
    if ( m_iItems == 0 )
    {
        rect = QRect(0, 0, width(), m_iBoxHeight);
    }
    else
    {
        RtSettingButton* pButtonNewLast = m_pButtonList[m_iItems-1];	// 0~m_iItems-1
        rect = pButtonNewLast->frameGeometry();
        rect.moveTop( rect.y() + m_iBoxHeight );
    }

    pButtonNew->setGeometry(rect);

    m_pButtonList[m_iItems] = pButtonNew;
    m_iItems++;

    return pButtonNew;
}

bool RtSettingList::DeleteButton(int iSelect)
{
    // parameter check
    if ( m_iItems <= iSelect || iSelect < 0 )
    {
        return false;
    }

    //Update the select status
    if ( m_iItemSelect != -1 )
    {
        m_pButtonList[m_iItemSelect]->setChecked(false);
        m_iItemSelect = -1;
    }

    QRect rectPrevious = m_pButtonList[iSelect]->frameGeometry();
    QRect rectNew;
    delete m_pButtonList[iSelect];

    for (int i=iSelect; i<m_iItems-1; i++)	// remaining items move up an item
    {
        m_pButtonList[i] = m_pButtonList[i+1];
        rectNew = m_pButtonList[i]->frameGeometry();
        m_pButtonList[i]->setGeometry(rectPrevious);
        rectPrevious = rectNew;
        m_pButtonList[i]->SetListIndex(i);	// re-set, button click return value;
    }
    m_pButtonList[m_iItems-1] = NULL;

    m_iItems --;	// total item decrease 1

    if ( m_iItems != 0 )
    {
            if ( (m_pButtonList[m_iItems-1]->y() + m_pButtonList[m_iItems-1]->height()) < height() )
            {// if last item is too high
                    int iShouldScrollDown = height() - (m_pButtonList[m_iItems-1]->y() + m_pButtonList[m_iItems-1]->height());
                    if ( m_pButtonList[0]->y() < 0 )
                    {// if first item can scroll down
                            int iCanScrollDown = -(m_pButtonList[0]->y());
                            int iScrollDown = (iShouldScrollDown > iCanScrollDown)? iCanScrollDown : iShouldScrollDown;
                            scroll(0, iScrollDown);
                    }
            }
    }
    return true;
}

void RtSettingList::MousePress(int iPressY)
{
    m_pQTimerScroll->stop();

    m_iLastScroll = 0;

    m_iPressY = iPressY - y();
}

void RtSettingList::ScrollList(int iDiffY)
{
    m_pQTimerReset->start(200);

    int iButtonTop = m_pButtonList[0]->y();
    if ( iButtonTop + iDiffY >= 0 )
    {
            iDiffY = -iButtonTop;
    }
    else
    {
            int iButtonBottom = (m_pButtonList[m_iItems-1]->y() + m_pButtonList[m_iItems-1]->height());
            int iCanScroll = height() - iButtonBottom;
            if ( iCanScroll > 0 ) iCanScroll = 0;
            if ( iCanScroll >= iDiffY )
            {
                iDiffY = iCanScroll;
            }
    }

    if ( m_iItemSelect != -1 )
    {
            m_pButtonList[m_iItemSelect]->setChecked(false);
            m_iItemSelect = -1;
    }

    scroll(0, iDiffY);
    emit ButtonScroll();
    m_iLastScroll = iDiffY;
}

void RtSettingList::MouseMoveDffX(int iListIndex,int iDiffX)
{
	if(iDiffX>0)
		emit ButtonOnOff(iListIndex,0);//iOnOff - 0->off, 1->on .
	else
		emit ButtonOnOff(iListIndex,1);//iOnOff - 0->off, 1->on .

}

void RtSettingList::MouseRelease()
{
    m_pQTimerReset->stop();
    m_iLastScroll -= m_iLastScroll%__AutoScroll_INTERVAL__;
    if( m_iLastScroll != 0 )
            m_pQTimerScroll->start(100);
}

void RtSettingList::AutoScroll()
{
    if ( m_iLastScroll != 0 )
    {
        if ( m_iLastScroll > 0)
        {
                m_iLastScroll -= __AutoScroll_INTERVAL__;
        }
        else
        {
                m_iLastScroll += __AutoScroll_INTERVAL__;
        }
        ScrollList(m_iLastScroll);
        m_iLastScroll -= m_iLastScroll%__AutoScroll_INTERVAL__;
    }
    else
    {
        m_pQTimerScroll->stop();
    }
}

void RtSettingList::ResetLastScroll()
{
    m_pQTimerReset->stop();
    m_iLastScroll = 0;
}

void RtSettingList::ListButtonClick(int iSelect)
{
    if ( m_iItemSelect != -1 )
    {
            m_pButtonList[m_iItemSelect]->setChecked(false);
            m_iItemSelect = -1;
    }

    m_iItemSelect = iSelect;
    m_pButtonList[m_iItemSelect]->setChecked(true);
    emit ButtonSelect(m_iItemSelect);

}

bool RtSettingList::SetIconB(int iIndex,QPixmap *pIconB)
{
    // parameter check
    if ( m_iItems <= iIndex || iIndex < 0 )
    {
        return false;
    }

    if(m_pButtonList[iIndex] != NULL)
        m_pButtonList[iIndex]->SetIconB(pIconB);

	return true;
}

void RtSettingList::SetIconB_OffsetX(int iIndex,int iOffsetX)
{
	 if(m_pButtonList[iIndex] != 0)
		m_pButtonList[iIndex]->SetIconB_OffsetX(iOffsetX);
}

RtSettingButton* RtSettingList::AddButton(RtSettingButton* pButtonNew)
{
    if ( m_iItems >= __MAX_SETTING_ITEMS__ )
        return NULL;

    m_iBoxHeight = pButtonNew->GetImageHeight();
    pButtonNew->setCheckable(true);

    connect(pButtonNew, SIGNAL(MousePress(int)),   this,       SLOT(MousePress(int)));
    connect(pButtonNew, SIGNAL(MoveInterval(int)), this,       SLOT(ScrollList(int)));
    connect(pButtonNew, SIGNAL(MouseRelease()),    this,       SLOT(MouseRelease()));
    connect(pButtonNew, SIGNAL(ButtonClick(int)),  this,       SLOT(ButtonClick(int)));
    connect(this,       SIGNAL(ButtonScroll()),    pButtonNew, SLOT(ButtonScroll()));


    QRect rect;
    if ( m_iItems == 0 )
    {
        rect = QRect(0, 0, width(), m_iBoxHeight);
    }
    else
    {
        RtSettingButton* pButtonNewLast = m_pButtonList[m_iItems-1];	// 0~m_iItems-1
        rect = pButtonNewLast->frameGeometry();
        rect.moveTop( rect.y() + m_iBoxHeight );
    }

    pButtonNew->setGeometry(rect);

    m_pButtonList[m_iItems] = pButtonNew;
    m_iItems++;

    return pButtonNew;
}

RtSettingButton* RtSettingList::GetButton(int iIndex)
{
    // parameter check
    if ( m_iItems <= iIndex || iIndex < 0 )
    {
        return NULL;
    }

    if(m_pButtonList[iIndex] != NULL)
        return m_pButtonList[iIndex];

    return NULL;
}
