#include <QTimer>
#include "RtListBox.h"

RtListBox::RtListBox(QWidget *parent,int iX, int iY, int iWidth, int iHeight)
:QWidget(parent),
m_HeightUsed(0),
m_iItems(0),
m_iItemSelect(-1),
m_iBoxHeight(0),
m_iPressY(0),
m_iLastScroll(0)
{
    setGeometry(iX, iY, iWidth, iHeight);

    for (int i=0; i<__MAX_ITEMS__; i++)
	{
        m_pButtonList[i] = NULL;
	}

    m_pQTimerScroll = new QTimer(this);
    connect(m_pQTimerScroll, SIGNAL(timeout()), this, SLOT(AutoScroll()));

    m_pQTimerReset = new QTimer(this);
    connect(m_pQTimerReset, SIGNAL(timeout()), this, SLOT(ResetLastScroll()));

}

RtPushButton* RtListBox::AddButton(RtPushButton* pButtonNew)
{
    if ( m_iItems >= __MAX_ITEMS__ )
	{
        return NULL;
	}
    m_iBoxHeight = pButtonNew->GetImageHeight();
    pButtonNew->setCheckable(true);

    connect(pButtonNew, SIGNAL(MousePress(int)),   this,       SLOT(MousePress(int)));
    connect(pButtonNew, SIGNAL(MoveInterval(int)), this,       SLOT(ScrollList(int)));
    connect(pButtonNew, SIGNAL(MouseRelease()),    this,       SLOT(MouseRelease()));
    connect(pButtonNew, SIGNAL(ButtonClick(int)),  this,       SLOT(ButtonClick(int)));
    connect(this,       SIGNAL(ButtonScroll()),    pButtonNew, SLOT(ButtonScroll()));

	//arrange item position
	pButtonNew->move(0, m_HeightUsed);
	m_HeightUsed += pButtonNew->height();
	//resize width to let mouse have reaction in all listbox
	pButtonNew->setMinimumWidth(this->width());
	//Add into list
	m_pButtonList[m_iItems] = pButtonNew;
	pButtonNew->SetListIndex(m_iItems);
	m_iItems++;
    return pButtonNew;
}

bool RtListBox::DeleteButton(int iSelect)
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

void RtListBox::DeleteAllButton(void)
{
    for (int i=0; i<m_iItems; i++)
	{
		delete m_pButtonList[i];
        m_pButtonList[i] = NULL;
	}

	m_HeightUsed = 0;
	m_iItems = 0;
	m_iItemSelect = -1;
	m_iBoxHeight = 0;
	m_iPressY = 0;
	m_iLastScroll = 0;
}

void RtListBox::MousePress(int iPressY)
{
    m_pQTimerScroll->stop();

    m_iLastScroll = 0;

    m_iPressY = iPressY - y();
}

void RtListBox::ScrollList(int iDiffY)
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

void RtListBox::MouseRelease()
{
    m_pQTimerReset->stop();
    m_iLastScroll -= m_iLastScroll%__AutoScroll_INTERVAL__;
    if( m_iLastScroll != 0 )
            m_pQTimerScroll->start(100);
}

void RtListBox::AutoScroll()
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

void RtListBox::ResetLastScroll()
{
    m_pQTimerReset->stop();
    m_iLastScroll = 0;
}

void RtListBox::ButtonClick(int iSelect)
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

int RtListBox::count () const
{
    return m_iItems;
}

RtPushButton* RtListBox::GetButton(int iIndex)
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
