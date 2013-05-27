#ifndef STDGADGETS_H
#define STDGADGETS_H

#include "Gadget.h"

///////////////////UNIQUE GADGETS//////////////////////////////////////
class CGadgetBigCompass : public CGadget
{
public:
	CGadgetBigCompass(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
protected:
    void paintEvent(QPaintEvent *event);
        QPixmap* m_pPixmapCompassGraduation;
	int CurrentAngle;
};

class CGadgetGpsSignalSmall : public CGadget
{
public:
    CGadgetGpsSignalSmall(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
protected:
	void paintEvent(QPaintEvent *event);
};

class CGadgetElevationPlot : public CGadget
{
public:
	CGadgetElevationPlot(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
protected:
	QList<int> m_PathListY;
	void paintEvent(QPaintEvent *event);
};

class CGadgetBatteryLevel : public CGadget
{
public:
	CGadgetBatteryLevel(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
protected:
	void paintEvent(QPaintEvent *event);
};
////////////////////////////////////////////////////////////////
/////////////////////CAbstractGadgetString/////////////////////////////
class CGadgetLocation : public CAbstractGadgetString
{
public:
    CGadgetLocation(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};

class CGadgetWaypointAtNext : public CAbstractGadgetString
{
public:
	CGadgetWaypointAtNext(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetWaypointAtDest : public CAbstractGadgetString
{
public:
	CGadgetWaypointAtDest(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetAccuracyGps : public CAbstractGadgetString
{
public:
	CGadgetAccuracyGps(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};
//////////////////////CAbstractGadgetSpeed//////////////////////////////
class CGadgetSpeed : public CAbstractGadgetSpeed
{
public:
    CGadgetSpeed(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetVerticalSpeed : public CAbstractGadgetSpeed
{
public:
	CGadgetVerticalSpeed(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};

class CGadgetSpeedOverallAvg : public CAbstractGadgetSpeed
{
public:
	CGadgetSpeedOverallAvg(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetSpeedMovingAvg : public CAbstractGadgetSpeed
{
public:
	CGadgetSpeedMovingAvg(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};
class CGadgetSpeedMaximum : public CAbstractGadgetSpeed
{
public:
	CGadgetSpeedMaximum(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

//////////////////////CAbstractGadgetTime//////////////////////////////
class CGadgetTimeOfDay : public CAbstractGadgetTime
{
public:
    CGadgetTimeOfDay(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};

class CGadgetEtaAtNext : public CAbstractGadgetTime
{
public:
	CGadgetEtaAtNext(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetEtaAtDest : public CAbstractGadgetTime
{
public:
	CGadgetEtaAtDest(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};
//////////////////////////////CAbstractGadgetDistance///////////////////////////////////////
class CGadgetOdometer : public CAbstractGadgetDistance
{
public:
    CGadgetOdometer(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};

class CGadgetTripOdometer : public CAbstractGadgetDistance
{
public:
    CGadgetTripOdometer(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};

class CGadgetDistanceToNext : public CAbstractGadgetDistance
{
public:
	CGadgetDistanceToNext(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetDistanceToDest : public CAbstractGadgetDistance
{
public:
    CGadgetDistanceToDest(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};
////////////////////////////////CAbstractGadgetTimeSpan///////////////////
class CGadgetTripTimeTotal : public CAbstractGadgetTimeSpan
{
public:
	CGadgetTripTimeTotal(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetTripTimeStopping : public CAbstractGadgetTimeSpan
{
public:
	CGadgetTripTimeStopping(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetTripTimeMoving : public CAbstractGadgetTimeSpan
{
public:
	CGadgetTripTimeMoving(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetTimeToNext : public CAbstractGadgetTimeSpan
{
public:
	CGadgetTimeToNext(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetTimeToDest : public CAbstractGadgetTimeSpan
{
public:
	CGadgetTimeToDest(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};
//////////////////////////////CAbstractGadgetElevation///////////////////////////////////////
class CGadgetElevation : public CAbstractGadgetElevation
{
public:
    CGadgetElevation(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount); 
};

class CGadgetTripElevation : public CAbstractGadgetElevation
{
public:
	CGadgetTripElevation(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};
//////////////////////////////CAbstractGadgetDirection///////////////////////////////////////
class CGadgetHeading : public CAbstractGadgetDirection
{
public:
	CGadgetHeading(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetBearing : public CAbstractGadgetDirection
{
public:
	CGadgetBearing(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetCourse : public CAbstractGadgetDirection
{
public:
	CGadgetCourse(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetToCourse : public CAbstractGadgetDirection
{
public:
	CGadgetToCourse(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};

class CGadgetOffCourse : public CAbstractGadgetDirection
{
public:
	CGadgetOffCourse(CGadgetsDialog* parent);
	void UpdateInfo(int TickCount);
};
////////////////////////////////CAbstractGadgetArrow///////////////////
class CGadgetPointer : public CAbstractGadgetArrow
{
public:
    CGadgetPointer(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};
////////////////////////////////CAbstractGadgetHeartRate///////////////////
class CGadgetHeartRate : public CAbstractGadgetHeartRate
{
public:
	CGadgetHeartRate(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};
////////////////////////////////CAbstractGadgetCadence///////////////////
class CGadgetCadence : public CAbstractGadgetCadence
{
public:
	CGadgetCadence(CGadgetsDialog* parent);
    void UpdateInfo(int TickCount);
};

#endif // STDGADGETS_H
