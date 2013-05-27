/******************************************************************************
 Description:

	Guide engine is used for trip guiding information.
 		
  Notes:

	Created by Richard.Lin. 2009/07/16

******************************************************************************/
#include "RdGuideEngine.h"
#include "MainMenuBar.h"
#include "RtGPS.h"
#include "Global.h"
#include "RdTripComputer.h"
#include "QPOIDatabase.h"
#include "QItemInfo.h"
#include "TrackList.h"
#include <math.h>
#include <QString>
#include <QDebug>

extern CTrackList g_TrackList;
extern CTripComputer g_TripComputer;
/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
CGuideEngine::CGuideEngine()
{
	QPOIDatabase PoiDb;
	QItemInfo    Intarget;
	
	//-- Waypoint
	if(PoiDb.ReadTarget(&Intarget))
	{
		SetTarget(&Intarget);
	}
	else
	{
		m_bSetTarget    = false;
		m_bWayPoint     = false;
		m_bTrack        = false;
		m_bWayPointList = false;
		m_dDestLon      = 0.0;
		m_dDestLat      = 0.0;
		m_dNextLon      = 0.0;
		m_dNextLat      = 0.0;
		m_iTrkPtNum     = 0;
	}
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
CGuideEngine::~CGuideEngine()
{
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_GUIDE CGuideEngine::SetTarget(QItemInfo *pItemInfo)
{
	m_bSetTarget = true;
	m_bWayPoint  = true;
	
	m_dDestLon   = pItemInfo->m_Lon;
	m_dDestLat   = pItemInfo->m_Lat;
	m_DestName   = pItemInfo->m_Name;

	m_dNextLon   = m_dDestLon;
	m_dNextLat   = m_dDestLat;
	m_NextName   = m_DestName;
	
	return RSLT_GUIDE_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_GUIDE CGuideEngine::SetTarget(QString strPathName)
{
	m_bSetTarget = true;
	m_bTrack     = true;

	m_TrkFile.setFileName(strPathName);

	if(m_TrkFile.exists())
	{
		if(m_TrkFile.open(QIODevice::ReadOnly))
		{
			m_TrkFile.seek(4);
            QDataStream in(&m_TrkFile);
            in >> m_TrkPtList;
            m_iTrkPtNum = m_TrkPtList.length();
			
			m_TrkFile.close();
		}
		else
		{
			return RSLT_GUIDE_ERR_OPEN_FILE;
		}
	}
	else
	{
		return RSLT_GUIDE_ERR_NO_FILE;
	}

	return RSLT_GUIDE_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_GUIDE CGuideEngine::SetTarget()
{
	m_bSetTarget    = true;
	m_bWayPointList = true;

	return RSLT_GUIDE_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_GUIDE CGuideEngine::CancelTarget()  
{
	m_bSetTarget    = false;
	m_bWayPoint     = false;
	m_bTrack        = false;
	m_bWayPointList = false;

	return RSLT_GUIDE_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
QString CGuideEngine::WayPointAtNext()
{
	return (m_NextName);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CGuideEngine::DistanceToNext()
{
	return (m_dNextDistance/1000.0);  //-- km
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
QTime CGuideEngine::EtaAtNext()
{
	return (m_NextTime);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_GUIDE CGuideEngine::TimeToNext(int *iHour, int *iMin)
{
	*iHour = m_iNextHour;
	*iMin  = m_iNextMin;
	
	return RSLT_GUIDE_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
QString CGuideEngine::WayPointAtDest()
{
	return (m_DestName);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CGuideEngine::DistanceToDest()
{
	return (m_dDestDistance/1000.0);  //-- km
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
QTime CGuideEngine::EtaAtDest()
{	
	return (m_DestTime);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_GUIDE CGuideEngine::TimeToDest(int *iHour, int *iMin)
{
	*iHour = m_iDestHour;
	*iMin  = m_iDestMin;
	
	return RSLT_GUIDE_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CGuideEngine::Course()
{
	return (m_dCourse);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CGuideEngine::ToCourse()
{
	return (m_dToCourse);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CGuideEngine::OffCourse()
{
	return (m_dOffCourse);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CGuideEngine::Bearing()
{
	return (m_dNextBearing);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CGuideEngine::Pointer()
{
	return (m_dNextPointer);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_GUIDE CGuideEngine::CalWayPointInfo()
{
	static bool bFirst = true;
	int    iMin;
	int    iSec;
	double dLon;
	double dLat;
	double dAlt;
	double dSpeed;
	double dDistance;
	double dBearing;  //-- Angle with North
	double dPointer;  //-- with eCompass
	double dHeading;  //-- eCompass angle
	QTime  time;
	QTime  tout;
	
	if((m_bSetTarget != true) || (m_bWayPoint != true))
	{
		return RSLT_GUIDE_INFO_NO_SET;
	}
	
/* -------------------------------------------------------------------- */
/*	  GPS information                                                   */
/* -------------------------------------------------------------------- */
	if(RtGPS_IfFix())  //-- GPS DLL will handle this
	{
		RtGPS_GetPos(&dLon, &dLat, &dAlt);  //-- The current GPS position
		CGlobal::GetDistance(dLat, dLon, m_dDestLat, m_dDestLon, &dDistance, &dBearing);  //-- Caculate the distance
		dBearing = CGlobal::Radian2Degree(dBearing);
		dSpeed = g_TripComputer.GetGuideMovingAvg();  //-- Get the moving speed in km/h

		dHeading = eCompass_GetYaw();
		dPointer = dBearing+dHeading;
		if(dPointer < 0)
		{
			dPointer += 360.0;
		}
		if(dPointer > 360.0)
		{
			dPointer -= 360.0;
		}
		
		if(bFirst == true)
		{
			bFirst = false;
			
			m_dCourse    = dBearing;
			m_dToCourse  = -1.0;
			m_dOffCourse = -1.0;
		}
		
		m_dDestDistance = dDistance;
		m_dDestBearing  = dBearing;
		m_dDestPointer  = dPointer;
		m_dNextDistance = m_dDestDistance;
		m_dNextBearing  = m_dDestBearing;
		m_dNextPointer  = m_dDestPointer;
		
		if(dSpeed == 0)
		{
			dSpeed = DEFAULT_SPEED_VAL;
		}
		iSec = (int)((dDistance*KM_DIV_HOUR)/dSpeed);
		iMin = (iSec/MIN_TO_SEC);
		
		time = QTime::currentTime();
		tout = time.addSecs(iSec);
		
		m_DestTime = tout;
		m_NextTime = m_DestTime;
		
		m_iDestHour = (iMin/MIN_TO_SEC);
		m_iDestMin  = (iMin%MIN_TO_SEC);
		m_iNextHour = m_iDestHour;
		m_iNextMin  = m_iDestMin;
	}
	
	return RSLT_GUIDE_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_GUIDE CGuideEngine::CalTrkInfo()
{
	int    i;
	int    iMin;
	int    iSec;
	double dLon;
	double dLat;
	double dAlt;
	double dSpeed;
	double dDistance;
	double dBearing;
	double dHeading;
	QTime  time;
	QTime  tout;
	
	if((m_bSetTarget != true) || (m_bTrack != true))
	{
		return RSLT_GUIDE_INFO_NO_SET;
	}
	
/* -------------------------------------------------------------------- */
/*	  GPS information                                                   */
/* -------------------------------------------------------------------- */
	if(RtGPS_IfFix())  //-- GPS DLL will handle this
	{
		RtGPS_GetPos(&dLon, &dLat, &dAlt);  //-- The current GPS position
		
		for(i=0; i<m_iTrkPtNum; i++)
		{
			CGlobal::GetDistance(dLat, dLon, g_TrackList.currentTrack()->TrkPt(i)->lat, g_TrackList.currentTrack()->TrkPt(i)->lon, &dDistance, &dBearing);
			dBearing = CGlobal::Radian2Degree(dBearing);
			dHeading = g_TripComputer.GetHeading();
			dBearing = dBearing-dHeading;
			if(dBearing < 0)
			{
				dBearing += 360.0;
			}
			if(dDistance < m_dNextDistance)
			{
			m_dNextLon      = m_TrkPtList.at(i)->lon;
			m_dNextLat      = m_TrkPtList.at(i)->lat;
				m_dNextDistance = dDistance;
				m_dNextBearing  = dBearing;

				//dSpeed = g_TripComputer.GetSpeed();  //-- Get the speed in km/h
				dSpeed = (g_TripComputer.GetSpeedMovingAvg()+g_TripComputer.GetSpeed())/(2.0);  //-- Get the moving speed in km/h
				if(dSpeed < DEFAULT_SPEED_VAL)
				{
					dSpeed = g_TripComputer.GetSpeedOverallAvg();
					if(dSpeed == 0)
					{
						dSpeed = DEFAULT_SPEED_VAL;
					}
				}
				iSec = (int)((dDistance*KM_DIV_HOUR)/dSpeed);
				iMin = (iSec/MIN_TO_SEC);
				
				time = QTime::currentTime();
				tout = time.addSecs(iSec);
				
				m_NextTime = tout;

				m_iNextHour = (iMin/MIN_TO_SEC);
				m_iNextMin  = (iMin%MIN_TO_SEC);
			}
			if(i == (m_iTrkPtNum-1))
			{
			m_dDestLon      = m_TrkPtList.at(i)->lon;
			m_dDestLat      = m_TrkPtList.at(i)->lat;
				m_dDestDistance = dDistance;
				m_dDestBearing  = dBearing;

				//dSpeed = g_TripComputer.GetSpeed();  //-- Get the speed in km/h
				dSpeed = (g_TripComputer.GetSpeedMovingAvg()+g_TripComputer.GetSpeed())/(2.0);  //-- Get the moving speed in km/h
				if(dSpeed < DEFAULT_SPEED_VAL)
				{
					dSpeed = g_TripComputer.GetSpeedOverallAvg();
					if(dSpeed == 0)
					{
						dSpeed = DEFAULT_SPEED_VAL;
					}
				}
				iSec = (int)((dDistance*KM_DIV_HOUR)/dSpeed);
				iMin = (iSec/MIN_TO_SEC);

				time = QTime::currentTime();
				tout = time.addSecs(iSec);
				
				m_DestTime = tout;

				m_iDestHour = (iMin/MIN_TO_SEC);
				m_iDestMin  = (iMin%MIN_TO_SEC);
			}
		}
	}
	
	return RSLT_GUIDE_OK;
}

