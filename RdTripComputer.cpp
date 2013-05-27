/******************************************************************************

 Description:

	Trip computer is used for trip information.
 		
  Notes:

	Created by Richard.Lin. 2009/07/13

******************************************************************************/
#include "MainMenuBar.h"
#include "RdTripComputer.h"
#include "RtGPS.h"
#include "Global.h"
#include <math.h>
#include <QTimer>
#include <QFile>
#include <QDebug>

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
CTripComputer::CTripComputer()
{
	//-- Re-init
	memset(dAvgVerSpeed, 0, ALT_FILTER_SIZE);

	dTotalGuideMovingSpeed = 0.0;
	iTripGuideTimeMoving   = 0;
	
	m_TripFile.setFileName(TRIP_FILE_PATH);
	
	if(m_TripFile.exists())
	{
		if(m_TripFile.open(QIODevice::ReadOnly))
		{
			QDataStream in(&m_TripFile);
			in >> dTripElevation;
			in >> iTripTimeTotal;
			in >> iTripTimeStopping;
			in >> iTripTimeMoving;
			in >> dBaseOdometer;
			in >> dSpeedMaximum;
			in >> dTotalSpeed;
			in >> dTotalMovingSpeed;
			in >> dTotalLon;
			in >> dTotalLat;

			m_TripFile.close();
		}
		else
		{
			TripReset();  //-- Reset the parameters
		}
	}
	else
	{
		TripReset();  //-- Reset the parameters
	}
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
CTripComputer::~CTripComputer()
{
	//-- Re-computed
	dTotalOdometer = GetTripOdometer()+dBaseOdometer;

	if(m_TripFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QDataStream out(&m_TripFile);
		out << dTripElevation;
		out << iTripTimeTotal;
		out << iTripTimeStopping;
		out << iTripTimeMoving;
		out << dTotalOdometer;
		out << dSpeedMaximum;
		out << dTotalSpeed;
		out << dTotalMovingSpeed;
		out << dTotalLon;
		out << dTotalLat;
		
		m_TripFile.close();
	}
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetVerticalSpeed()
{	
	return (dVerticalSpeed*METER_DIV_MIN);  //-- m/m
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetTripElevation()
{	
	return (dTripElevation);  //-- m
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetHeading()
{
	return (dHeading);
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetSpeed()
{	
	return (dSpeed*KNOTS_TO_KM);  //-- km/h
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetSpeedOverallAvg()
{
	if(iTripTimeTotal == 0)
	{
		dSpeedOverallAvg = 0.0;
	}
	else
	{
		dSpeedOverallAvg = (dTotalSpeed/iTripTimeTotal)*KNOTS_TO_KM;
	}
	
	return (dSpeedOverallAvg);  //-- km/h
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_TRIP CTripComputer::GetTripTimeTotal(int *iHour, int *iMin)
{
	*iMin  = (int)(iTripTimeTotal/MIN_TO_SEC);
	*iHour = (int)(*iMin/MIN_TO_SEC);

	*iMin = (int)(*iMin%MIN_TO_SEC);

	return RSLT_TRIP_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetOdometer()
{
	dTotalOdometer = GetTripOdometer()+dBaseOdometer;
	
	return ((dTotalOdometer/1000.0));  //-- km
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_TRIP CTripComputer::GetTripTimeStopping(int *iHour, int *iMin)
{
	*iMin  = (int)(iTripTimeStopping/MIN_TO_SEC);
	*iHour = (int)(*iMin/MIN_TO_SEC);

	*iMin = (int)(*iMin%MIN_TO_SEC);

	return RSLT_TRIP_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetSpeedMovingAvg()
{
	if(iTripTimeMoving == 0)
	{
		dSpeedMovingAvg = 0.0;
	}
	else
	{
		dSpeedMovingAvg = (dTotalMovingSpeed/iTripTimeMoving)*KNOTS_TO_KM;
	}

	return (dSpeedMovingAvg);  //-- km/h
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetGuideMovingAvg()
{
	if(iTripGuideTimeMoving == 0)
	{
		dGuideMovingAvg = 0;
	}
	else
	{
		dGuideMovingAvg = (dTotalGuideMovingSpeed/iTripGuideTimeMoving)*KNOTS_TO_KM;
	}

	return (dGuideMovingAvg);  //-- km/h
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_TRIP CTripComputer::GetTripTimeMoving(int *iHour, int *iMin)
{
	*iMin  = (int)(iTripTimeMoving/MIN_TO_SEC);
	*iHour = (int)(*iMin/MIN_TO_SEC);

	*iMin = (int)(*iMin%MIN_TO_SEC);

	return RSLT_TRIP_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetTripOdometer()
{
	dTripOdometer = CGlobal::GetDistance(0, 0, dTotalLat, dTotalLon);
	
	return ((dTripOdometer/1000.0));  //-- km
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
double CTripComputer::GetSpeedMaximum()
{
	return (dSpeedMaximum*KNOTS_TO_KM);  //-- km/h
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
RSLT_TRIP CTripComputer::TripReset()
{
	dVerticalSpeed    = 0.0;
	lElevation        = 0;
	dTripElevation    = 0.0;
	dHeading          = 0.0;
	dSpeed            = 0.0;
	dSpeedOverallAvg  = 0.0;
	iTripTimeTotal    = 0;
	iTripTimeStopping = 0;
	dSpeedMovingAvg   = 0.0;
	dGuideMovingAvg   = 0.0;
	iTripTimeMoving   = 0;
	dTripOdometer     = 0.0;
	dBaseOdometer     = 0.0;
	dSpeedMaximum     = 0.0;

	lOldElevation     = 0;
	dTotalSpeed       = 0.0;
	dTotalMovingSpeed = 0.0;
	dLon              = 0.0;
	dLat              = 0.0;
	dAlt              = 0.0;
	dOldLon           = 0.0;
	dOldLat           = 0.0;
	dTotalLon         = 0.0;
	dTotalLat         = 0.0;
	
	return RSLT_TRIP_OK;
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
void CTripComputer::TripUpdate()
{
	static int iAvgNum = 0;
	double dTmpVerSpeed;
	double dDifLon;
	double dDifLat;
	long   lDifAlt;
	
/* -------------------------------------------------------------------- */
/*	  GPS information                                                   */
/* -------------------------------------------------------------------- */
	if(RtGPS_IfFix())  //-- GPS DLL will handle this
	{
		//-- Time inforamtion
		dSpeed = RtGPS_GetSpeed();
		
		iTripTimeTotal++;
		if(dSpeed > MOVING_SPEED_THD)  //-- Moving
		{
			iTripTimeMoving++;
			iTripGuideTimeMoving++;
		}
		else if(dSpeed <= STOP_SPEED_THD)  //-- Stopping
		{
			iTripTimeStopping++;
		}
		else
		{
		}
		
		//-- Speed information
		if(dSpeed > dSpeedMaximum)
		{
			dSpeedMaximum = dSpeed;
		}
		dTotalSpeed += dSpeed;
		if(dSpeed > MOVING_SPEED_THD)
		{
			dTotalMovingSpeed += dSpeed;
			dTotalGuideMovingSpeed += dSpeed;
			
			if(RtGPS_GetDOP() <= GPS_HDOP_THD)  //-- Trust HDOP
			{
				//-- Distance information
				RtGPS_GetPos(&dLon, &dLat, &dAlt);
				if(dOldLon != 0)
				{
					dDifLon = (dOldLon-dLon);
					if(dDifLon<0)
					{
						dDifLon = -dDifLon;
					}
					dTotalLon += dDifLon;
				}
				dOldLon = dLon;

				if(dOldLat != 0)
				{
					dDifLat = (dOldLat-dLat);
					if(dDifLat<0)
					{
						dDifLat = -dDifLat;
					}
					dTotalLat += dDifLat;
				}
				dOldLat = dLat;
				
				//-- Heading information
				dHeading = RtGPS_GetHeading();
			}
		}
	}  //-- End RtGPS_IfFix()
	
	//-- Altimeter information
	lElevation = AltimeterGetAltitude();
	if(lElevation != -1)
	{
		if(lOldElevation != 0)
		{
			if(RtGPS_IfFix())
			{
				if(dSpeed == 0)
				{
					dVerticalSpeed = 0;
					return;
				}
			}
			lDifAlt = (lElevation-lOldElevation);
			if(lDifAlt < 0)
			{
				lDifAlt = -lDifAlt;
			}
			if(lDifAlt > UNREASONABLE_ALT)
			{
				return;
			}
			if(lDifAlt <= ALT_MOVE_THD)
			{
				dVerticalSpeed = 0;
				return;
			}
			else
			{
				dAvgVerSpeed[iAvgNum] = (double)(lElevation-lOldElevation);  //-- m/s
			}
			iAvgNum++;
			iAvgNum = (iAvgNum % ALT_FILTER_SIZE);
			dTmpVerSpeed = 0;
			for(int i=0; i<ALT_FILTER_SIZE; i++)
			{
				dTmpVerSpeed += dAvgVerSpeed[i];
			}
			dVerticalSpeed = (dTmpVerSpeed/ALT_FILTER_SIZE);
			
#if 0
			if(dVerticalSpeed < 0)
			{
				dTripElevation -= dVerticalSpeed;
				//dVerticalSpeed = -dVerticalSpeed;
			}
			else
#endif
			{
				dTripElevation += dVerticalSpeed;
			}
		}
		lOldElevation = lElevation;
	}
	
#if 0
	qDebug() << "iTripTimeTotal" << iTripTimeTotal;
	qDebug() << "iTripTimeMoving" << iTripTimeMoving;
	qDebug() << "iTripTimeStopping" << iTripTimeStopping;

	qDebug() << "dSpeedMaximum" << dSpeedMaximum;
	qDebug() << "dTotalSpeed" << dTotalSpeed;
	qDebug() << "dTotalMovingSpeed" << dTotalMovingSpeed;

	qDebug() << "dSpeed" << dSpeed;

	qDebug() << "dTotalLon" << dTotalLon;
	qDebug() << "dTotalLat" << dTotalLat;
	qDebug() << "dHeading" << dHeading;

	qDebug() << "lElevation" << lElevation;
	qDebug() << "dTripElevation" << dTripElevation;
	qDebug() << "dVerticalSpeed" << dVerticalSpeed;
#endif
}

