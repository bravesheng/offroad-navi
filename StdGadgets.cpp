#include "StdGadgets.h"
#include "QPainter"
#include "ExternalLibrary.h"
#include "QTime"
#include "QTimer"
#include "RtGPS.h"
#include "Nordic.h"
#include "RdTripComputer.h"
#include "RdGuideEngine.h"

extern CTripComputer g_TripComputer;
extern CGuideEngine g_Guide;

////////////////////////////////////////////////////////////////////////////////
//**************************Compass Big Gadget*******************************//

CGadgetBigCompass::CGadgetBigCompass(CGadgetsDialog* parent):CGadget(parent)
{
	m_pPixmapCompassGraduation = GetImg(IMG_GADGET_COMPASS_GRADUATION);
    CurrentAngle = 0;
    SetMainSkin(IMG_GADGET_COMPASS);
    Name = "Compass";
    UpdateGadgetSize(2,2);
}


void CGadgetBigCompass::UpdateInfo(int TickCount)
{
	int NewAngle = eCompass_GetYaw();
	if(NewAngle != CurrentAngle)
	{
		CurrentAngle = NewAngle;
		this->update();
	}
}

void CGadgetBigCompass::paintEvent(QPaintEvent *event)
{
    //Create QPainter
    QPainter painter(this);
	CGadget::Paint(&painter);
    //Start paint this gadget
    painter.setRenderHint(QPainter::TextAntialiasing);
    //Paint arrow
    int HelfWidth = ONE_SLOT_WIDTH * WidthSlotNums / 2;
    int helfHeight = ONE_SLOT_HEIGHT * HeightSlotNums / 2;
    painter.translate(HelfWidth, helfHeight);
    painter.rotate(-CurrentAngle);
    painter.drawPixmap(-HelfWidth,-helfHeight,*m_pPixmapCompassGraduation);
}

//**************************GPS Signal Small Gadget**************************//
CGadgetGpsSignalSmall::CGadgetGpsSignalSmall(CGadgetsDialog* parent):CGadget(parent)
{
    SetMainSkin(IMG_GADGET_GPS_SIGNAL);
    Name = "GPS Signal";
}

void CGadgetGpsSignalSmall::UpdateInfo(int TickCount)
{

}

void CGadgetGpsSignalSmall::paintEvent(QPaintEvent *event)
{
    //Create QPainter
    QPainter painter(this);
	CGadget::Paint(&painter);
}

//**************************Elvation Plot Gadget*****************************//
CGadgetElevationPlot::CGadgetElevationPlot(CGadgetsDialog* parent)
:CGadget(parent)
{
    //SetMainSkin(IMG_GADGET_ELEVATION_PLOT);
    Name = "Elevation Plot";
    UpdateGadgetSize(3,1);
	bShowLabel = false;
	m_PathListY.append(50);
	//m_PathListX

}

void CGadgetElevationPlot::UpdateInfo(int TickCount)
{
	if(m_PathListY.length() == 100)
	{
		m_PathListY.removeAt(0);
	}
	int RandValue = (rand() % 10) - 5;
	int CurrentY = m_PathListY.last();
	if(((CurrentY + RandValue) >= 90) || ((CurrentY + RandValue) <= 10))
	{
		CurrentY -= RandValue;
	}
	else
	{
		CurrentY += RandValue;
	}
	m_PathListY.append(CurrentY);
	if(TickCount % 3 == 0)	//update screen per 3 seconds
	{
		update();
	}
}

void CGadgetElevationPlot::paintEvent(QPaintEvent *event)
{
	QPainterPath path;
	int x;
	path.addRect(0, 0, 300, 100);

	path.moveTo(0, m_PathListY.at(0));
	for(x=1; x < m_PathListY.length(); x++)
	{
		path.lineTo(x*3,m_PathListY.at(x));
	}
	path.lineTo(x*3-3,100);
	path.lineTo(0,100);

	QPainter painter(this);
	painter.fillRect(0, 0, 300, 100, QColor(66, 160, 255, 200));
	painter.setPen(QPen(QColor(0, 65, 96), 3, Qt::SolidLine,
                     Qt::FlatCap, Qt::MiterJoin));
	painter.setBrush(QColor(0, 0, 0, 150));

	painter.drawPath(path);
}

//**************************Battery Level Gadget*****************************//
CGadgetBatteryLevel::CGadgetBatteryLevel(CGadgetsDialog* parent)
:CGadget(parent)
{
    SetMainSkin(IMG_GADGET_BATTERY);
    Name = "Bettery Level";
}

void CGadgetBatteryLevel::UpdateInfo(int TickCount)
{

}

void CGadgetBatteryLevel::paintEvent(QPaintEvent *event)
{
    //Create QPainter
    QPainter painter(this);
	CGadget::Paint(&painter);
}
//////////////////////////////////////////////////////////////////////
////////////////////////////CAbstractGadgetString/////////////////////////////
//**************************Location Gadget**************************//
CGadgetLocation::CGadgetLocation(CGadgetsDialog* parent)
:CAbstractGadgetString(parent)
{
	Name = "Location";
}

void CGadgetLocation::UpdateInfo(int TickCount)
{
	double Lon, Lat, Alt;
	int n_degree = 0;
	int n_min = 0;
	int n_sec = 0;
	int e_degree = 0;
	int e_min = 0;
	int e_sec = 0;
	QString LonString, LatString;

	if(RtGPS_GetPos(&Lon, &Lat, &Alt))
	{
		RtGPS_PosToDMS(Lon, &n_degree, &n_min, &n_sec);
		RtGPS_PosToDMS(Lat, &e_degree, &e_min, &e_sec);
		m_Content.sprintf(("N %02d\xB0%02d'%03d\nE%03d\xB0%02d'%03d") , n_degree , n_min ,n_sec,
			e_degree, e_min, e_sec);
		this->update();
	}
}
//**************************Waypoint At Next************************************************//
CGadgetWaypointAtNext::CGadgetWaypointAtNext(CGadgetsDialog* parent)
:CAbstractGadgetString(parent)
{
	Name = "Next Point";
}

void CGadgetWaypointAtNext::UpdateInfo(int TickCount)
{
	QString NewContect = g_Guide.WayPointAtNext();
	if(NewContect != m_Content)	//equal to
	{
		m_Content = NewContect;
		update();
	}
}
//**************************Waypoint At Dest************************************************//
CGadgetWaypointAtDest::CGadgetWaypointAtDest(CGadgetsDialog* parent)
:CAbstractGadgetString(parent)
{
	Name = "Destination";
}

void CGadgetWaypointAtDest::UpdateInfo(int TickCount)
{
	QString NewContect = g_Guide.WayPointAtNext();
	if(NewContect != m_Content)	//equal to
	{
		m_Content = NewContect;
		update();
	}
}

//**************************Accuracy of GPS************************************************//
CGadgetAccuracyGps::CGadgetAccuracyGps(CGadgetsDialog* parent)
:CAbstractGadgetString(parent)
{
	Name = "Accuracy of GPS";
}

void CGadgetAccuracyGps::UpdateInfo(int TickCount)
{

}
//////////////////////CAbstractGadgetSpeed//////////////////////////////
//**************************Speed Gadget**************************//
CGadgetSpeed::CGadgetSpeed(CGadgetsDialog* parent)
:CAbstractGadgetSpeed(parent)
{
	Name = "Speed";
}

void CGadgetSpeed::UpdateInfo(int TickCount)
{
	double NewSpeed = g_TripComputer.GetSpeed();//RtGPS_GetSpeed();
	if(NewSpeed != m_Speed)
	{
		m_Speed = NewSpeed;
		update();
	}
}
//**************************Cadence Vertical Speed*******************************//
CGadgetVerticalSpeed::CGadgetVerticalSpeed(CGadgetsDialog* parent)
:CAbstractGadgetSpeed(parent)
{
	Name = "Vertical Speed";
}

void CGadgetVerticalSpeed::UpdateInfo(int TickCount)
{
	double NewSpeed = g_TripComputer.GetVerticalSpeed();
	if(NewSpeed != m_Speed)
	{
		m_Speed = NewSpeed;
		update();
	}
}
//**************************Speed Overall Avg.***********************************************//
CGadgetSpeedOverallAvg::CGadgetSpeedOverallAvg(CGadgetsDialog* parent)
: CAbstractGadgetSpeed(parent)
{
	Name = "Overall Avg";
}

void CGadgetSpeedOverallAvg::UpdateInfo(int TickCount)
{
	double NewSpeed = g_TripComputer.GetSpeedOverallAvg();
	if(NewSpeed != m_Speed)
	{
		m_Speed = NewSpeed;
		update();
	}
}
//**************************Speed Moving Avg.***********************************************//
CGadgetSpeedMovingAvg::CGadgetSpeedMovingAvg(CGadgetsDialog* parent)
: CAbstractGadgetSpeed(parent)
{
	Name = "Moving Avg";
}

void CGadgetSpeedMovingAvg::UpdateInfo(int TickCount)
{
	double NewSpeed = g_TripComputer.GetSpeedMovingAvg();
	if(NewSpeed != m_Speed)
	{
		m_Speed = NewSpeed;
		update();
	}
}
//**************************Speed Maximum ***********************************************//
CGadgetSpeedMaximum::CGadgetSpeedMaximum(CGadgetsDialog* parent)
: CAbstractGadgetSpeed(parent)
{
	Name = "Max Speed";
}

void CGadgetSpeedMaximum::UpdateInfo(int TickCount)
{
	double NewSpeed = g_TripComputer.GetSpeedMaximum();
	if(NewSpeed != m_Speed)
	{
		m_Speed = NewSpeed;
		update();
	}
}
//////////////////////CAbstractGadgetTime//////////////////////////////
//**************************TimeOfDay Gadget**************************//
CGadgetTimeOfDay::CGadgetTimeOfDay(CGadgetsDialog* parent)
:CAbstractGadgetTime(parent)
{
	Name = "Time of Day";
}

void CGadgetTimeOfDay::UpdateInfo(int TickCount)
{
	m_Time = QTime::currentTime();
	static int PreMinutes = m_Time.minute();

	if(PreMinutes != m_Time.minute())
	{
		update();
	}
}
//**************************ETA At Next************************************************//
CGadgetEtaAtNext::CGadgetEtaAtNext(CGadgetsDialog* parent)
:CAbstractGadgetTime(parent)
{
	Name = "ETA at Next";
}

void CGadgetEtaAtNext::UpdateInfo(int TickCount)
{
	QTime NewTime = g_Guide.EtaAtNext();
	if(m_Time != NewTime)
	{
		m_Time = NewTime;
		update();
	}
}
//**************************ETA At Destination************************************************//
CGadgetEtaAtDest::CGadgetEtaAtDest(CGadgetsDialog* parent)
:CAbstractGadgetTime(parent)
{
	Name = "ETA at Dest";
}

void CGadgetEtaAtDest::UpdateInfo(int TickCount)
{
	QTime NewTime = g_Guide.EtaAtDest();
	if(m_Time != NewTime)
	{
		m_Time = NewTime;
		update();
	}
}
//////////////////////////////CAbstractGadgetDistance///////////////////////////////////////
//**************************Odometer Gadget**************************//
CGadgetOdometer::CGadgetOdometer(CGadgetsDialog* parent)
:CAbstractGadgetDistance(parent)
{
	Name = "Odometer";
}

void CGadgetOdometer::UpdateInfo(int TickCount)
{
	double NewDistance = g_TripComputer.GetTripOdometer();
	if(NewDistance != m_Distance)
	{
		m_Distance = NewDistance;
		update();
	}
}
//**************************Trip Odometer Gadget**************************//
CGadgetTripOdometer::CGadgetTripOdometer(CGadgetsDialog* parent)
:CAbstractGadgetDistance(parent)
{
	Name = "Trip Odometer";
}

void CGadgetTripOdometer::UpdateInfo(int TickCount)
{
	double NewDistance = g_TripComputer.GetTripOdometer();
	if(NewDistance != m_Distance)
	{
		m_Distance = NewDistance;
		update();
	}
}
//**************************Distance To Next**************************//
CGadgetDistanceToNext::CGadgetDistanceToNext(CGadgetsDialog* parent)
:CAbstractGadgetDistance(parent)
{
	Name = "Dist to Next";
}

void CGadgetDistanceToNext::UpdateInfo(int TickCount)
{
	double NewDistance = g_Guide.DistanceToNext();
	if(NewDistance != m_Distance)
	{
		m_Distance = NewDistance;
		update();
	}
}
//**************************Distance To Destination**************************//
CGadgetDistanceToDest::CGadgetDistanceToDest(CGadgetsDialog* parent)
:CAbstractGadgetDistance(parent)
{
	Name = "Dist to Dest";
}

void CGadgetDistanceToDest::UpdateInfo(int TickCount)
{
	double NewDistance = g_Guide.DistanceToDest();
	if(NewDistance != m_Distance)
	{
		m_Distance = NewDistance;
		update();
	}
}
////////////////////////////////CAbstractGadgetTimeSpan///////////////////
//**************************Trip Time - Total***********************************************//
CGadgetTripTimeTotal::CGadgetTripTimeTotal(CGadgetsDialog* parent)
: CAbstractGadgetTimeSpan(parent)
{
	Name = "Total Time";
}

void CGadgetTripTimeTotal::UpdateInfo(int TickCount)
{
	int NewHours, NewMinutes;

	g_TripComputer.GetTripTimeTotal(&NewHours, &NewMinutes);
	if((m_Hours != NewHours) || (m_Minutes != NewMinutes))
	{
		m_Hours = NewHours;
		m_Minutes = NewMinutes;
		update();
	}
}
//**************************Trip Time - Stopping***********************************************//
CGadgetTripTimeStopping::CGadgetTripTimeStopping(CGadgetsDialog* parent)
: CAbstractGadgetTimeSpan(parent)
{
	Name = "Stopping Time";
}

void CGadgetTripTimeStopping::UpdateInfo(int TickCount)
{
	int NewHours, NewMinutes;

	g_TripComputer.GetTripTimeStopping(&NewHours, &NewMinutes);
	if((m_Hours != NewHours) || (m_Minutes != NewMinutes))
	{
		m_Hours = NewHours;
		m_Minutes = NewMinutes;
		update();
	}
}
//**************************Trip Time - Moving***********************************************//
CGadgetTripTimeMoving::CGadgetTripTimeMoving(CGadgetsDialog* parent)
: CAbstractGadgetTimeSpan(parent)
{
	Name = "Moving Time";
}

void CGadgetTripTimeMoving::UpdateInfo(int TickCount)
{
	int NewHours, NewMinutes;

	g_TripComputer.GetTripTimeMoving(&NewHours, &NewMinutes);
	if((m_Hours != NewHours) || (m_Minutes != NewMinutes))
	{
		m_Hours = NewHours;
		m_Minutes = NewMinutes;
		update();
	}
}

//**************************Time to Next***********************************************//
CGadgetTimeToDest::CGadgetTimeToDest(CGadgetsDialog* parent)
: CAbstractGadgetTimeSpan(parent)
{
	Name = "Time to Dest";
}

void CGadgetTimeToDest::UpdateInfo(int TickCount)
{
	int NewHours, NewMinutes;

	g_Guide.TimeToDest(&NewHours, &NewMinutes);
	if((m_Hours != NewHours) || (m_Minutes != NewMinutes))
	{
		m_Hours = NewHours;
		m_Minutes = NewMinutes;
		update();
	}
}
//**************************Time to Dest***********************************************//
CGadgetTimeToNext::CGadgetTimeToNext(CGadgetsDialog* parent)
: CAbstractGadgetTimeSpan(parent)
{
	Name = "Time to Next";
}

void CGadgetTimeToNext::UpdateInfo(int TickCount)
{
	int NewHours, NewMinutes;

	g_Guide.TimeToNext(&NewHours, &NewMinutes);
	if((m_Hours != NewHours) || (m_Minutes != NewMinutes))
	{
		m_Hours = NewHours;
		m_Minutes = NewMinutes;
		update();
	}
}
//////////////////////////////CAbstractGadgetElevation///////////////////////////////////////
//**************************Elevation Gadget**************************//
CGadgetElevation::CGadgetElevation(CGadgetsDialog* parent)
:CAbstractGadgetElevation(parent)
{
	Name = "Elevation";
}

void CGadgetElevation::UpdateInfo(int TickCount)
{
	int NewValue = AltimeterGetAltitude();
	if(m_ElevationValue != NewValue)
	{
		m_ElevationValue = NewValue;
		update();
	}
}
//**************************Trip Elevation***************************************//
CGadgetTripElevation::CGadgetTripElevation(CGadgetsDialog* parent)
:CAbstractGadgetElevation(parent)
{
	Name = "Trip Elevation";
}

void CGadgetTripElevation::UpdateInfo(int TickCount)
{
	int NewValue = g_TripComputer.GetTripElevation();
	if(m_ElevationValue != NewValue)
	{
		m_ElevationValue = NewValue;
		update();
	}
}

/////////////////////////CAbstractGadgetDirection////////////////////////////
//**************************Heading************************************************//
CGadgetHeading::CGadgetHeading(CGadgetsDialog* parent)
:CAbstractGadgetDirection(parent)
{
	Name = "Heading";
}

void CGadgetHeading::UpdateInfo(int TickCount)
{
	int NewAngle = eCompass_GetYaw();
	if(NewAngle != m_Angle)
	{
		m_Angle = NewAngle;
		update();
	}
}
//**************************Bearing************************************************//
CGadgetBearing::CGadgetBearing(CGadgetsDialog* parent)
:CAbstractGadgetDirection(parent)
{
	Name = "Bearing";
}

void CGadgetBearing::UpdateInfo(int TickCount)
{
	double NewAngle = g_Guide.Bearing();
	if(NewAngle != m_Angle)
	{
		m_Angle = NewAngle;
		update();
	}
}
//**************************Course************************************************//
CGadgetCourse::CGadgetCourse(CGadgetsDialog* parent)
:CAbstractGadgetDirection(parent)
{
	Name = "Course";
}

void CGadgetCourse::UpdateInfo(int TickCount)
{
	double NewAngle = g_Guide.Course();
	if(NewAngle != m_Angle)
	{
		m_Angle = NewAngle;
		update();
	}
}
//**************************To Course************************************************//
CGadgetToCourse::CGadgetToCourse(CGadgetsDialog* parent)
:CAbstractGadgetDirection(parent)
{
	Name = "To Course";
}

void CGadgetToCourse::UpdateInfo(int TickCount)
{
	double NewAngle = g_Guide.ToCourse();
	if(NewAngle != m_Angle)
	{
		m_Angle = NewAngle;
		update();
	}
}
//**************************Off Course************************************************//
CGadgetOffCourse::CGadgetOffCourse(CGadgetsDialog* parent)
:CAbstractGadgetDirection(parent)
{
	Name = "Off Course";
}

void CGadgetOffCourse::UpdateInfo(int TickCount)
{
	double NewAngle = g_Guide.OffCourse();
	if(NewAngle != m_Angle)
	{
		m_Angle = NewAngle;
		update();
	}
}
////////////////////////////////CAbstractGadgetArrow///////////////////
//**************************Pointer Gadget**************************//
CGadgetPointer::CGadgetPointer(CGadgetsDialog* parent)
:CAbstractGadgetArrow(parent)
{
	Name = "Pointer";
}

void CGadgetPointer::UpdateInfo(int TickCount)
{
#if 0
	int NewAngle = eCompass_GetYaw();
#else
	double NewAngle = g_Guide.Pointer();
#endif
	if(NewAngle != m_Angle)
	{
		m_Angle = NewAngle;
		update();
	}
}
////////////////////////////////CAbstractGadgetHeartRate///////////////////
//**************************Heart Rate Gadget*******************************//
CGadgetHeartRate::CGadgetHeartRate(CGadgetsDialog* parent)
:CAbstractGadgetHeartRate(parent)
{
	Name = "Heart Rate";
}

void CGadgetHeartRate::UpdateInfo(int TickCount)
{
	//Update ANT heart-rate information.
	int NewHeartRate = HRS_GetHeartRate();
	if(m_HeartRate != NewHeartRate)
	{
		m_HeartRate = NewHeartRate;
		update();
	}
}
////////////////////////////////CAbstractGadgetCadence///////////////////
//**************************Cadence Gadget*******************************//
CGadgetCadence::CGadgetCadence(CGadgetsDialog* parent)
:CAbstractGadgetCadence(parent)
{
	Name = "Cadence";
}

void CGadgetCadence::UpdateInfo(int TickCount)
{
	//Update ANT cadence information.
	int NewCadence = HRS_GetHeartRate();
	if(m_Cadence != NewCadence)
	{
		m_Cadence = NewCadence;
		update();
	}
}
