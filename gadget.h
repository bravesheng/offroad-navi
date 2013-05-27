#ifndef GADGET_H
#define GADGET_H

#include <QWidget>
#include <QMouseEvent>
#include "GadgetSlot.h"
#include "ImagePool.h"
#include <QTime>

#define GADGET_CONTENT_FONT					"Tahoma"
#define GADGET_CONTENT_STD_FONT_SIZE		18
#define SPEED_GADGET_FONT_SIZE				20
#define LOCATION_GADGET_FONT_SIZE			8
#define ONE_SLOT_WIDTH 100
#define ONE_SLOT_HEIGHT  100

typedef enum _GADGET_SCENE
{
    GADGET_SCENE_LOCATION = 0,
    GADGET_SCENE_TIME_OF_DAY,
    GADGET_SCENE_SPEED,
    GADGET_SCENE_ODOMETER,
    GADGET_SCENE_POINTER,
    GADGET_SCENE_COMPASS,
    CADGET_SCENE_GPS_SIGNAL_SMALL,
    GADGET_SCENE_GPS_PLOT,
    GADGET_SCENE_GPS_SIGNAL_BIG
}GADGET_SCENE;

typedef enum _GADGET_UNIT
{
	GADGET_LOCATION = 0,
	GADGET_SPEED,
	GADGET_TIME_OF_DAY,
	GADGET_ODOMETR,
	GADGET_ELEVATION,
	GADGET_POINTER,
	GADGET_BIG_COMPASS,
	GADGET_GPS_SIGNAL_SMALL,
	GADGET_ELEVATION_PLOT,
	GADGET_HEART_RATE,
	GADGET_CADENCE,
	GADGET_VERTICAL_SPEED,
	GADGET_TRIP_ELEVATION,
	GADGET_BATTERY_LEVEL,
	GADGET_HEADING,
	GADGET_ACCURACY_GPS,
	GADGET_SPEED_OVERALL_AVG,
	GADGET_TRIP_TIME_TOTAL,
	GADGET_TRIP_TIME_STOPPING,
	GADGET_SPEED_MOVING_AVG,
	GADGET_TRIP_TIME_MOVING,
	GADGET_TRIP_ODOMETER,
	GADGET_SPEED_MAX,
	GADGET_BEARING,
	GADGET_WPT_AT_NEXT,
	GADGET_ETA_AT_NEXT,
	GADGET_DST_TO_NEXT,
	GADGET_TIME_TO_NEXT,
	GADGET_WPT_AT_DST,
	GADGET_DISTANCE_TO_DST,
	GADGET_ETA_AT_DST,
	GADGET_TIME_TO_DST,
	GADGET_COURSE,
	GADGET_TO_COURSE,
	GADGET_OFF_COURSE,
	GADGET_NUMS
}GADGET_UNIT;

/*
This is basic class for widgets
It's based on QWidget And add following ability.
1. Include one basic skin.
2. Can display text lebel to show who it is.
3. Can dragable and have alpha blend effect.
*/

class CGadgetsDialog;

class CGadget : public QWidget
{
public:
    CGadgetSlot* pCurrentSlot;  //Define first slot you are slot in. NULL means slot undefined.
    CGadget(CGadgetsDialog* parent);
    void SetMainSkin(IMG_ID SkinIndex);
	QString* GetName(void);
	virtual void UpdateInfo(int TickCount) = NULL;      //Update current Gadget information
	void ShowLabel(bool bShow) {bShowLabel = bShow;}
	//bool operator==(CGadget*);
    int WidthSlotNums;  //To show how width this widget is. Unit is Slot.
    int HeightSlotNums; //To show how height this widget is. Unit is Slot.
protected:
    void Paint(QPainter *pPainter);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
	void UpdateGadgetSize(int WidgetSlot, int HeightSlot);	//must set if gadget over 1 slot.
    //virtual void Update();
    QString Name;    //name of this widget. Also will become label for this widget
	QString m_Content;	//Used for store result string.
    QTimer *pUpdateTimer;
	bool bShowLabel;
private:
    QPoint CurrentPos;  //current widget position in screen
    QPoint TargetPos;   //the target position that when mouse drag this widget
    QPixmap* pMainSkin; //main skin for this Gadgets
};

class CAbstractGadgetElevation : public CGadget
{
public:
	CAbstractGadgetElevation(CGadgetsDialog* parent);
protected:
	long m_ElevationValue;
    void paintEvent(QPaintEvent *event);
};

class CAbstractGadgetArrow : public CGadget
{
public:
	CAbstractGadgetArrow(CGadgetsDialog* parent);
protected:
	QPixmap* m_pPixmapArrow;
	double m_Angle;
    void paintEvent(QPaintEvent *event);
};

class CAbstractGadgetDistance : public CGadget
{
public:
	CAbstractGadgetDistance(CGadgetsDialog* parent);
protected:
	double m_Distance;
    void paintEvent(QPaintEvent *event);
};

class CAbstractGadgetSpeed : public CGadget
{
public:
	CAbstractGadgetSpeed(CGadgetsDialog* parent);
protected:
	double m_Speed;
    void paintEvent(QPaintEvent *event);
};

class CAbstractGadgetString : public CGadget
{
public:
	CAbstractGadgetString(CGadgetsDialog* parent);
protected:
    void paintEvent(QPaintEvent *event);
};

class CAbstractGadgetDirection : public CGadget
{
public:
	CAbstractGadgetDirection(CGadgetsDialog* parent);
protected:
	int m_Angle;
    void paintEvent(QPaintEvent *event);
};

class CAbstractGadgetTime : public CGadget
{
public:
	CAbstractGadgetTime(CGadgetsDialog* parent);
protected:
	QTime m_Time;
    void paintEvent(QPaintEvent *event);
};

class CAbstractGadgetTimeSpan : public CGadget
{
public:
	CAbstractGadgetTimeSpan(CGadgetsDialog* parent);
protected:
	int m_Hours;
	int m_Minutes;
    void paintEvent(QPaintEvent *event);
};

class CAbstractGadgetHeartRate : public CGadget
{
public:
	CAbstractGadgetHeartRate(CGadgetsDialog* parent);
protected:
	int m_HeartRate;
    void paintEvent(QPaintEvent *event);

};

class CAbstractGadgetCadence : public CGadget
{
public:
	CAbstractGadgetCadence(CGadgetsDialog* parent);
protected:
	int m_Cadence;
    void paintEvent(QPaintEvent *event);
};

#endif // GADGET_H
