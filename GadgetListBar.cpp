#include "GadgetListBar.h"
#include "ImagePool.h"
#include <QPainter>
#include <QtCore/QTimeLine>
#include <QMouseEvent>
#include "GadgetListItem.h"
#include "GadgetListBar.h"
#include "GadgetsDialog.h"

#define FRAME_START_X				288
#define FRAME_START_Y				0
#define FRAME_END_X					74
#define FRAME_WIDTH					246
#define FRAME_HEIGHT				240
#define FRAME_ANIMATION_TIME		500
#define TAB_AREA_X					0
#define TAB_AREA_Y					0
#define TAB_AREA_WIDTH				70
#define TAB_AREA_HEIGHT				65

QString GadgetNameTable[] =	//IMPORTANT: This array must meet order of GADGET_UNIT
{
"Location",
"Speed",
"Time of Day",
"Odometer",
"Elevation",
"Pointer",
"Big Compass",
"GPS Signal",
"Elevation Plot",
"Heart Rate",
"Cadence",
"Vertical Speed",
"Trip Elevation",
"Battery Level",
"Heading",
"Accuracy GPS",
"Speed - Overall Avg.",
"Trip Time - Total",
"Trip Time Stopping",
"Speed Moving Avg.",
"Trip Time - Moving",
"Trip Odometer",
"Speed - Maximum",
"Bearing",
"Waypoint at Next",
"ETA at Next",
"Distance to Next",
"Time to Next",
"Waypoint at Dest.",
"Distance to Destination",
"ETA at Destination",
"Time to Destination",
"Course",
"To Course",
"Off Course"
};

CGadgetListBar::CGadgetListBar(CGadgetsDialog *parent)
: QWidget((QWidget*)parent),
m_ListBox(this, 40, 0, FRAME_WIDTH-40, FRAME_HEIGHT),
m_pGadgetsDlg(parent)
{
    setGeometry(QRect(FRAME_START_X, FRAME_START_Y, FRAME_WIDTH, FRAME_HEIGHT));

    // Prepare the animated switch:
    m_timeLine = new QTimeLine(500, this);
    m_timeLine->setCurveShape(QTimeLine::EaseInOutCurve);
    connect(m_timeLine, SIGNAL(frameChanged(int)), SLOT(setBarPosition(int)));
	connect(m_timeLine, SIGNAL(finished()), SLOT(SlideFinished()));

	for(int i=0; i < GADGET_NUMS; i++)
	{
		m_pListBoxItem[i] = new CGadgetListItem(&m_ListBox, GadgetNameTable[i]);
		m_ListBox.AddButton(m_pListBoxItem[i]);
		connect(m_pListBoxItem[i], SIGNAL(ButtonClick(int)), this, SLOT(AddGadget(int)));
	}
}

CGadgetListBar::~CGadgetListBar()
{
	for(int i=0; i < 10; i++)
	{
		delete m_pListBoxItem[i];
	}
}

void CGadgetListBar::paintEvent(QPaintEvent*)//event
{
    QPainter painter(this);
	painter.drawPixmap(0, 0, GetImg(IMG_BAR_GADGET_LIST)->width(), GetImg(IMG_BAR_GADGET_LIST)->height(), *GetImg(IMG_BAR_GADGET_LIST));
}

void CGadgetListBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
	raise();
	QRect TabArea(TAB_AREA_X, TAB_AREA_Y, TAB_AREA_WIDTH, TAB_AREA_HEIGHT);

	if(!TabArea.contains(event->x(), event->y()))	//if mouse down is not under tab area,
	{
		if(m_timeLine->currentFrame() == FRAME_START_X)	//means closed
		{
			emit MouseRelease(event);
		}
		return;
	}

	if(m_timeLine->state() == QTimeLine::NotRunning)
	{
		if(this->pos().x() == FRAME_END_X)	//means opened
		{
			CloseBar();
		}
		else if(this->pos().x() == FRAME_START_X)	//means closed
		{
			OpenBar();
		}
	}
}

void CGadgetListBar::setBarPosition(int position)
{
	QPoint CurrentPos;
	QPoint TargetPos;
    CurrentPos = this->pos();
    TargetPos.setX(position);
    TargetPos.setY(CurrentPos.y());
    move(TargetPos);
}

void CGadgetListBar::SlideFinished(void)
{
	/*
	if(m_timeLine->currentFrame() == FRAME_START_POS)	//means menu closed
	{
		setGeometry(QRect(DETECT_AREA_X, DETECT_AREA_Y, DETECT_AREA_WIDTH, DETECT_AREA_HEIGHT));
	}
	*/
}

bool CGadgetListBar::IfTabArea(int screen_x, int screen_y)
{
	QRect TabArea(FRAME_START_X + TAB_AREA_X, FRAME_START_Y + TAB_AREA_Y, TAB_AREA_WIDTH, TAB_AREA_HEIGHT);
	if(TabArea.contains(screen_x, screen_y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CGadgetListBar::AddGadget(int GadgetIndex)
{
	//m_pGadgetsDlg->AddGadget(GadgetType);
	m_pGadgetsDlg->AddGadget((GADGET_UNIT)GadgetIndex);
	QuickCloseBar();
}

void CGadgetListBar::OpenBar(void)
{
	m_timeLine->setFrameRange(FRAME_START_X, FRAME_END_X);
	m_timeLine->start();
}

void CGadgetListBar::CloseBar(void)
{
	m_timeLine->setFrameRange(FRAME_END_X, FRAME_START_X);
	m_timeLine->start();
}

void CGadgetListBar::QuickCloseBar(void)
{
	setGeometry(QRect(FRAME_START_X, FRAME_START_Y, FRAME_WIDTH, FRAME_HEIGHT));
}