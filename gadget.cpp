#include "gadget.h"
#include <QPainter>
#include "GadgetsDialog.h"
#define LABEL_X 10
#define LABEL_Y 100
#define LABEL_FONT  "Tahoma"
#define LABEL_FONT_SIZE 10
#define CAPTION_HEIGHT	5

CGadget::CGadget(CGadgetsDialog* parent)
:QWidget(parent),
bShowLabel(true),
pMainSkin(NULL),
pCurrentSlot(NULL)
{
    //Initial member variable
    Name.clear();
	UpdateGadgetSize(1,1);
}

void CGadget::UpdateGadgetSize(int WidgetSlot, int HeightSlot)
{
	WidthSlotNums = WidgetSlot;
	HeightSlotNums = HeightSlot;
	resize(ONE_SLOT_WIDTH * WidthSlotNums, (ONE_SLOT_HEIGHT * HeightSlotNums) + CAPTION_HEIGHT);
}

void CGadget::Paint(QPainter *pPainter)
{
    //Paint background
    if(pMainSkin)
    {
        pPainter->drawPixmap(0, 0, *pMainSkin);
    }
    pPainter->setRenderHint(QPainter::TextAntialiasing);
    if(bShowLabel)
    {
        //Paint label string
        QFont font(LABEL_FONT, LABEL_FONT_SIZE);
        font.setBold(true);
        font.setStyleStrategy(QFont::PreferAntialias);
		pPainter->setFont(font);
        pPainter->setPen(QColor(255,255,255,255));
        pPainter->drawText(QRect(0,80,width(),20),Qt::AlignHCenter, Name);
    }
}

void CGadget::mouseMoveEvent(QMouseEvent *event)
{
    CurrentPos = this->pos();
    TargetPos.setX(CurrentPos.x()+ event->x()-(width()/2));
    TargetPos.setY(CurrentPos.y()+ event->y()-(height()/2));
    move(TargetPos);
    this->raise();
}

void CGadget::SetMainSkin(IMG_ID SkinIndex)
{
    pMainSkin = GetImg(SkinIndex);
}

void CGadget::mouseReleaseEvent(QMouseEvent *event)
{
	CurrentPos = this->pos();
	int WidgetCenterX = CurrentPos.x()+ event->x();
	int WidgetCenterY = CurrentPos.y()+ event->y();
	((CGadgetsDialog*)this->parent())->DropGadget(this, WidgetCenterX, WidgetCenterY);
	//lower();	//in order to let "add gadget" function work correctly.
}


QString* CGadget::GetName(void)
{
	return &Name;
}
/*
bool CGadget::operator==(CGadget* pCompareGadget)
{
	if(
}
*/
////////////////////////////////////////////////////////

CAbstractGadgetElevation::CAbstractGadgetElevation(CGadgetsDialog* parent)
:CGadget(parent),
m_ElevationValue(0)
{
    SetMainSkin(IMG_GADGET_ALTITUDE);
}

void CAbstractGadgetElevation::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    CGadget::Paint(&painter);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, GADGET_CONTENT_STD_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255,255));
	m_Content.sprintf("%d", m_ElevationValue);
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
    //Paint unit
    painter.setPen(QColor(240,199,3,255));
    font.setPointSize(11);
    painter.setFont(font);
    painter.drawText(QRect(0,65,width()-20,20),Qt::AlignRight, "m");
}

///////////////////////////////////////////////////////////////////
CAbstractGadgetArrow::CAbstractGadgetArrow(CGadgetsDialog* parent)
:CGadget(parent),
m_Angle(0)
{
	m_pPixmapArrow = GetImg(IMG_GADGET_ARROW);
}

void CAbstractGadgetArrow::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    CGadget::Paint(&painter);
    //Paint arrow
    int HelfWidth = ONE_SLOT_WIDTH * WidthSlotNums / 2;
    int helfHeight = ONE_SLOT_HEIGHT * HeightSlotNums / 2;
    painter.translate(HelfWidth, helfHeight);
    painter.rotate(-m_Angle);
    painter.drawPixmap(-HelfWidth,-helfHeight,*m_pPixmapArrow);
}

//////////////////////////////////////////////////////////////////
CAbstractGadgetDistance::CAbstractGadgetDistance(CGadgetsDialog* parent)
:CGadget(parent),
m_Distance(0)
{
	SetMainSkin(IMG_GADGET_LENGTH);
}

void CAbstractGadgetDistance::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    CGadget::Paint(&painter);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, GADGET_CONTENT_STD_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255,255));
	
	m_Content.sprintf("%.2f", m_Distance);
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
    //Paint unit
    painter.setPen(QColor(240,199,3,255));
    font.setPointSize(11);
    painter.setFont(font);
    painter.drawText(QRect(0,65,width()-20,20),Qt::AlignRight, "km");
}

/////////////////////////////////////////////////////////////////////

CAbstractGadgetSpeed::CAbstractGadgetSpeed(CGadgetsDialog* parent)
:CGadget(parent),
m_Speed(0)
{
	SetMainSkin(IMG_GADGET_SPEED);
}

void CAbstractGadgetSpeed::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    CGadget::Paint(&painter);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, SPEED_GADGET_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255,255));

	m_Content.sprintf("%.1f", m_Speed);
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
    //Paint unit
    painter.setPen(QColor(240,199,3,255));
    font.setPointSize(11);
    painter.setFont(font);
    painter.drawText(QRect(0,65,width(),20),Qt::AlignHCenter, "km/h");
}
/////////////////////////////////////////////////////////////////

CAbstractGadgetString::CAbstractGadgetString(CGadgetsDialog* parent)
:CGadget(parent)
{
	SetMainSkin(IMG_GADGET_STRING);
}

void CAbstractGadgetString::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    CGadget::Paint(&painter);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, LOCATION_GADGET_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255,255));
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
}
/////////////////////////////////////////////////////////////////
CAbstractGadgetTime::CAbstractGadgetTime(CGadgetsDialog* parent)
:CGadget(parent)
{
	SetMainSkin(IMG_GADGET_TIME);
}

void CAbstractGadgetTime::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    CGadget::Paint(&painter);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, GADGET_CONTENT_STD_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(0,0,0,255));
	//prepare string
	m_Content.sprintf("%02d:%02d", m_Time.hour(), m_Time.minute());
	//draw string
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
}
/////////////////////////////////////////////////////////////////
CAbstractGadgetTimeSpan::CAbstractGadgetTimeSpan(CGadgetsDialog* parent)
:CGadget(parent)
{
	SetMainSkin(IMG_GADGET_TIME);
}

void CAbstractGadgetTimeSpan::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    CGadget::Paint(&painter);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, GADGET_CONTENT_STD_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(0,0,0,255));
	//prepare string
	m_Content.sprintf("%02d:%02d", m_Hours, m_Minutes);
	//draw string
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
}
///////////////////////////////////////////////////////////////////
CAbstractGadgetHeartRate::CAbstractGadgetHeartRate(CGadgetsDialog* parent)
:CGadget(parent),
m_HeartRate(0)
{
	SetMainSkin(IMG_GADGET_HEARTBEAT);
}

void CAbstractGadgetHeartRate::paintEvent(QPaintEvent *event)
{
    //Create QPainter
    QPainter painter(this);
	CGadget::Paint(&painter);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, GADGET_CONTENT_STD_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255,255));
	m_Content.sprintf("%d", m_HeartRate);
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
    //Paint unit
    painter.setPen(QColor(240,199,3,255));
    font.setPointSize(11);
    painter.setFont(font);
    painter.drawText(QRect(0,65,width()-20,20),Qt::AlignRight, "bpm");
}

///////////////////////////////////////////////////////////////////
CAbstractGadgetCadence::CAbstractGadgetCadence(CGadgetsDialog* parent)
:CGadget(parent),
m_Cadence(0)
{
	SetMainSkin(IMG_GADGET_SPEED);
}

void CAbstractGadgetCadence::paintEvent(QPaintEvent *event)
{
    //Create QPainter
    QPainter painter(this);
	CGadget::Paint(&painter);
    //Start paint this gadget
    painter.setRenderHint(QPainter::TextAntialiasing);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, GADGET_CONTENT_STD_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255,255));
	m_Content.sprintf("%d", m_Cadence);
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
    //Paint unit
    painter.setPen(QColor(240,199,3,255));
    font.setPointSize(11);
    painter.setFont(font);
    painter.drawText(QRect(0,65,width()-20,20),Qt::AlignRight, "rpm");
}

/////////////////////////////////////////////////////////////////

CAbstractGadgetDirection::CAbstractGadgetDirection(CGadgetsDialog* parent)
:CGadget(parent),
m_Angle(-1)
{
	SetMainSkin(IMG_GADGET_STRING);
}

void CAbstractGadgetDirection::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
    CGadget::Paint(&painter);
    //Paint value string
    QFont font(GADGET_CONTENT_FONT, LOCATION_GADGET_FONT_SIZE);
    font.setBold(true);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255,255));
	//Prepare string
	if(m_Angle != -1)
	{
		switch(int((m_Angle + 22.5) / 45))
		{
		case 0:
			m_Content.sprintf("N");
			break;
		case 1:
			m_Content.sprintf("NE");
			break;
		case 2:
			m_Content.sprintf("E");
			break;
		case 3:
			m_Content.sprintf("SE");
			break;
		case 4:
			m_Content.sprintf("S");
			break;
		case 5:
			m_Content.sprintf("SW");
			break;
		case 6:
			m_Content.sprintf("W");
			break;
		case 7:
			m_Content.sprintf("NW");
			break;
		}
	}
	else
	{
		m_Content.clear();
	}
	//Draw string
    painter.drawText(QRect(0,35,width(),40),Qt::AlignHCenter, m_Content);
}