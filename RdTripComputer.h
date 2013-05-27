/******************************************************************************

 Description:

	Trip computer is used for trip information.
 		
  Notes:

	Created by Richard.Lin. 2009/07/13

******************************************************************************/
#ifndef __TRIP_COMPUTER_H__
#define __TRIP_COMPUTER_H__

#include "RtGPS.h"
#include "ExternalLibrary.h"
#include <QFile>

using namespace std;

#define TRIP_FILE_PATH    ("\\ShellDisk\\Shell\\OffRoadNavi\\data\\TripComputer.dat")

#define MIN_TO_SEC        (60)
#define METER_DIV_MIN     (60.0)
#define KM_DIV_HOUR       (3.6)
#define KNOTS_TO_KM       (1.852)  //-- http://hk.geocities.com/hk_weather/big5/others/calculators.html
#define MOVING_SPEED_THD  (0.06)
#define STOP_SPEED_THD    (0.06)
#define GPS_HDOP_THD      (3.0)
#define ALT_FILTER_SIZE   (3)
#define UNREASONABLE_ALT  (300)
#define ALT_MOVE_THD      (2)

/* -------------------------------------------------------------------- */
/*      Return value of function                                        */
/* -------------------------------------------------------------------- */
typedef enum
{
	RSLT_TRIP_OK = 0,
	RSLT_TRIP_ERR_DATA,

} RSLT_TRIP;

/* -------------------------------------------------------------------- */
/*      Class of CTripComputer                                          */
/* -------------------------------------------------------------------- */
class CTripComputer
{
public:
	CTripComputer();
	~CTripComputer();

	double    GetVerticalSpeed(void);                      //-- m/m
	double    GetTripElevation(void);                      //-- m
	double    GetHeading(void);                            //-- degree
	double    GetSpeed(void);                              //-- km/h
	double    GetSpeedOverallAvg(void);                    //-- km/h
	RSLT_TRIP GetTripTimeTotal(int *iHour, int *iMin);
	double    GetOdometer(void);                           //-- km
	RSLT_TRIP GetTripTimeStopping(int *iHour, int *iMin);
	double    GetSpeedMovingAvg(void);                     //-- km/h
	double    GetGuideMovingAvg(void);                     //-- km/h for Guide engine
	RSLT_TRIP GetTripTimeMoving(int *iHour, int *iMin);
	double    GetTripOdometer(void);                       //-- km
	double    GetSpeedMaximum(void);                       //-- km/h
	
	RSLT_TRIP TripReset(void);
	void      TripUpdate(void);
	
private:
	double    dVerticalSpeed;
	long      lElevation;
	double    dTripElevation;
	double    dHeading;
	double    dSpeed;
	double    dSpeedOverallAvg;
	int       iTripTimeTotal;
	int       iTripTimeStopping;
	double    dSpeedMovingAvg;
	double    dGuideMovingAvg;
	int       iTripTimeMoving;
	double    dTripOdometer;
	double    dTotalOdometer;
	double    dBaseOdometer;
	double    dSpeedMaximum;
	double    dTotalGuideMovingSpeed;
	int       iTripGuideTimeMoving;

	long      lOldElevation;
	double    dTotalSpeed;
	double    dTotalMovingSpeed;
	double    dLon;
	double    dLat;
	double    dAlt;
	double    dOldLon;
	double    dOldLat;
	double    dTotalLon;
	double    dTotalLat;

	double    dAvgVerSpeed[ALT_FILTER_SIZE];
	QFile     m_TripFile;
};

#endif // __TRIP_COMPUTER_H__

