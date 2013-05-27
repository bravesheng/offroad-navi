/******************************************************************************

 Description:

	Guide engine is used for trip guiding information.
 		
  Notes:

	Created by Richard.Lin. 2009/07/16

******************************************************************************/
#ifndef __GUIDE_ENGINE_H__
#define __GUIDE_ENGINE_H__

#include "RtGPS.h"
#include "ExternalLibrary.h"
#include "RdTripComputer.h"
#include "QItemInfo.h"
#include <QDateTime>
#include <QFile>
#include "Track.h"

using namespace std;

#define DEFAULT_SPEED_VAL  (6.0)

/* -------------------------------------------------------------------- */
/*      Return value of function                                        */
/* -------------------------------------------------------------------- */
typedef enum
{
	RSLT_GUIDE_OK = 0,
	RSLT_GUIDE_INFO_NO_SET,
	RSLT_GUIDE_ERR_DATA,
	RSLT_GUIDE_ERR_NO_FILE,
	RSLT_GUIDE_ERR_OPEN_FILE,

} RSLT_GUIDE;

/* -------------------------------------------------------------------- */
/*      Class of CGuideEngine                                           */
/* -------------------------------------------------------------------- */
class CGuideEngine
{
public:
	CGuideEngine();
	~CGuideEngine();

	RSLT_GUIDE CalWayPointInfo(void);
	RSLT_GUIDE CalTrkInfo(void);

	RSLT_GUIDE SetTarget(QItemInfo *pItemInfo);  //-- WayPoint
	RSLT_GUIDE SetTarget(QString strPathName);   //-- Track
	RSLT_GUIDE SetTarget(void);                  //-- WayPoint list
	RSLT_GUIDE CancelTarget(void);    
	QString    WayPointAtNext(void); 
	double     DistanceToNext(void);
	QTime      EtaAtNext(void);      
	RSLT_GUIDE TimeToNext(int *iHour, int *iMin);
	QString    WayPointAtDest(void);
	double     DistanceToDest(void);
	QTime      EtaAtDest(void);
	RSLT_GUIDE TimeToDest(int *iHour, int *iMin);
	double     Course(void);
	double     ToCourse(void);
	double     OffCourse(void);
	double     Bearing(void);
	double     Pointer(void);
	
private:
	bool       m_bSetTarget;
	bool       m_bWayPoint;      //-- WayPoint mode
	bool       m_bTrack;         //-- Track mode
	bool       m_bWayPointList;  //-- WayPoint mode
	int        m_iTrkPtNum;
	
	double     m_dDestLon;
	double     m_dDestLat;
	QString    m_DestName;
	double     m_dDestDistance;
	QTime      m_DestTime;
	int        m_iDestHour;
	int        m_iDestMin;
	double     m_dDestBearing;
	double     m_dDestPointer;
	
	double     m_dNextLon;
	double     m_dNextLat;
	QString    m_NextName;
	double     m_dNextDistance;
	QTime      m_NextTime;
	int        m_iNextHour;
	int        m_iNextMin;
	double     m_dNextBearing;
	double     m_dNextPointer;
	
	double     m_dCourse;
	double     m_dToCourse;
	double     m_dOffCourse;
	
	QFile      m_TrkFile;
	
	QList<CTrkPt*> m_TrkPtList;
};

#endif // __GUIDE_ENGINE_H__

