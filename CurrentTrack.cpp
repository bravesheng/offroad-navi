#include "CurrentTrack.h"
#include "RtGPS.h"
#include "Global.h"
#include "RdTripComputer.h"
extern CTripComputer g_TripComputer;

CCurrentTrack::CCurrentTrack(void)
:CTrack("current_track"),		//default name. should be fixed. except multi-language.
m_time_counter(0)
{
	m_color = QColor(0,0,0);	//default black
	m_iLogMethod = LOG_METHOD_TIME;
	m_dLogDistance = MIN_LOG_DISTANCE;
}

CCurrentTrack::~CCurrentTrack(void)
{
}

void CCurrentTrack::setLogMethod(int iLogMethod)
{
	m_iLogMethod = iLogMethod;
}

void CCurrentTrack::TrigMePerSec(void)
{
	if(m_iLogMethod ==LOG_METHOD_TIME)
	{
		UpdateByTime();
	}
	else if(m_iLogMethod == LOG_METHOD_DISTANCE)
	{
		UpdateByDistance(m_dLogDistance);
	}
	else if(m_iLogMethod == LOG_METHOD_AUTO)
	{
		UpdateAuto();
	}
	m_time_counter++;
}

void CCurrentTrack::UpdateByTime(void)
{
	if(m_time_counter % 3 == 0)	//run per 3 seconds
	{
		addCurrentPt();
	}
}

void CCurrentTrack::UpdateByDistance(double dLogDistance)
{
	BOOL bGPS_Fixed = FALSE;
	double dDist = 0.0;
	double dCurLon = 0.0;
	double dCurLat = 0.0;
	double dCurEle = 0.0;
	static bool bFirstTime = true;
	static double dOldLon = 0.0;
	static double dOldLat = 0.0;
	if(RtGPS_IfFix())
	{
		bGPS_Fixed = RtGPS_GetPos(&dCurLon, &dCurLat, &dCurEle);	
	}

	if(bGPS_Fixed)
	{
		if(bFirstTime)
		{
			bFirstTime = false;
			addCurrentPt();
			dOldLon = dCurLon;
			dOldLat = dCurLat;
			return;
		}

		dDist = GetDistance(dCurLat,dCurLon,dOldLat,dOldLon);
		if(dDist>dLogDistance)
		{
			addCurrentPt();
			dOldLon = dCurLon;
			dOldLat = dCurLat;
		}
	}
}

void CCurrentTrack::UpdateAuto(void)
{
	UpdateByDistance(MIN_LOG_DISTANCE);
}

double  CCurrentTrack::GetDistance( double dCurLat, double dCurLong,double dOldLat, double dOldLong)
{
	double dDistance = 0.0;

	dDistance = CGlobal::GetDistance(dCurLat,dCurLong,dOldLat,dOldLong);
//	dDistance = CGlobal::UnitConvert(CGlobal::UNIT_M, dDistance);

    return dDistance;
}

bool CCurrentTrack::setLogDistance(double dLogDistance)
{
	if(dLogDistance>MIN_LOG_DISTANCE)
	{
		m_dLogDistance = dLogDistance;
		return true;
	}
	return false;
}

void CCurrentTrack::addCurrentPt(void)
{
	CTrkPt* pTrkPt = new CTrkPt;
	RtGPS_GetPos(&pTrkPt->lon, &pTrkPt->lat,&pTrkPt->elevation);
	pTrkPt->elevation = AltimeterGetAltitude();
	pTrkPt->speed = g_TripComputer.GetSpeed();
	pTrkPt->cadence = CAD_GetCandence();
	pTrkPt->heart_rate = HRS_GetHeartRate();

	QDate CurrentDate;
	int year, month, day;
	RtGPS_GetDate(&year, &month, &day);
	CurrentDate.setDate(year, month, day);
	pTrkPt->datetime.setDate(CurrentDate);

	QTime CurrentTime;
	int hour, minute, second;
	RtGPS_GetTime(&hour, &minute, &second); 
	CurrentTime.setHMS(hour, minute, second);
	pTrkPt->datetime.setTime(CurrentTime);

	addTrkPt(pTrkPt);
	saveTrkFile();
}