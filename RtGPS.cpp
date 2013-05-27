#include "RtGPS.h"

//external function type definitions
typedef int (*pFuncGetInt)(void);
typedef double (*pFuncGetDouble)(void);
typedef BOOL (*pFuncParamOneIntPoint)(int*);
typedef BOOL (*pFuncParamThreeIntPoint)(int*, int*, int*);
typedef BOOL (*pFuncParamThreeDoublePoint)(double*, double*, double*);
typedef BOOL (*pFuncParamSatelliteInfo)(SATEINFO* pSatellites);
typedef int (*pFuncGpsInit)(HWND, int, DWORD);

QLibrary GPS("GPS");

int RtGPS_Init(int nComport, int dwBaudrate)
{
    if(GPS.isLoaded())
    {
        pFuncGpsInit RtGPS_Init = (pFuncGpsInit) GPS.resolve("RTGPS_Init");
        if(RtGPS_Init)
        {
            return RtGPS_Init(NULL, nComport, dwBaudrate);
        }
    }
	return NULL;
}

int	RtGPS_GetUsedSatelliteNumber(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetInt RtGPS_GetUsedSatelliteNumber = (pFuncGetInt) GPS.resolve("RTGPS_GetUsedSatelliteNumber");
        if(RtGPS_GetUsedSatelliteNumber)
        {
            return RtGPS_GetUsedSatelliteNumber();
        }
    }
	return NULL;
}

int	RtGPS_GetSatelliteInViewNumber(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetInt RtGPS_GetSatelliteInViewNumber = (pFuncGetInt) GPS.resolve("RTGPS_GetSatelliteInViewNumber");
        if(RtGPS_GetSatelliteInViewNumber)
        {
            return RtGPS_GetUsedSatelliteNumber();
        }
    }
	return NULL;
}
int	RtGPS_IfFix(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetInt RtGPS_IfFix = (pFuncGetInt) GPS.resolve("RTGPS_IfFix");
        if(RtGPS_IfFix)
        {
            return RtGPS_IfFix();
        }
    }
	return NULL;
}
int	RtGPS_GsaFixMode(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetInt RtGPS_GsaFixMode = (pFuncGetInt) GPS.resolve("RTGPS_GsaFixMode");
        if(RtGPS_GsaFixMode)
        {
            return RtGPS_GsaFixMode();
        }
    }
	return NULL;
}

BOOL RtGPS_Uninit(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetInt RtGPS_Uninit = (pFuncGetInt) GPS.resolve("RTGPS_Uninit");
        if(RtGPS_Uninit)
        {
            return RtGPS_Uninit();
        }
    }
	return FALSE;
}

BOOL RtGPS_FirstTimeToFix(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetInt RtGPS_FirstTimeToFix = (pFuncGetInt) GPS.resolve("RTGPS_FirstTimeToFix");
        if(RtGPS_FirstTimeToFix)
        {
            return RtGPS_FirstTimeToFix();
        }
    }
	return FALSE;
}

BOOL RtGPS_GetDate(int* iYear, int* iMonth, int* iDay)
{
    if(GPS.isLoaded())
    {
        pFuncParamThreeIntPoint RtGPS_GetDate = (pFuncParamThreeIntPoint) GPS.resolve("RTGPS_GetDate");
        if(RtGPS_GetDate)
        {
            return RtGPS_GetDate(iYear, iMonth, iDay);
        }
    }
	return FALSE;
}

BOOL RtGPS_GetTime(int* iHour, int* iMinute, int* iSecond)
{
    if(GPS.isLoaded())
    {
        pFuncParamThreeIntPoint RtGPS_GetTime = (pFuncParamThreeIntPoint) GPS.resolve("RTGPS_GetTime");
        if(RtGPS_GetTime)
        {
            return RtGPS_GetTime(iHour, iMinute, iSecond);
        }
    }
	return FALSE;
}

BOOL RtGPS_GetPos(double* dLong, double* dLat, double* dAlt)
{
    if(GPS.isLoaded())
    {
        pFuncParamThreeDoublePoint RtGPS_GetPos = (pFuncParamThreeDoublePoint) GPS.resolve("RTGPS_GetPos");
        if(RtGPS_GetPos)
        {
            return RtGPS_GetPos(dLong, dLat, dAlt);
        }
    }
	return FALSE;
}

BOOL RtGPS_GetUsedSatellites(int* piUsedSatellites)
{
    if(GPS.isLoaded())
    {
        pFuncParamOneIntPoint RtGPS_GetUsedSatellites = (pFuncParamOneIntPoint) GPS.resolve("RTGPS_GetUsedSatellites");
        if(RtGPS_GetUsedSatellites)
        {
            return RtGPS_GetUsedSatellites(piUsedSatellites);
        }
    }
	return FALSE;
}

BOOL RtGPS_GetSatelliteInfo(SATEINFO* pSatellites)
{
    if(GPS.isLoaded())
    {
        pFuncParamSatelliteInfo RtGPS_GetSatelliteInfo = (pFuncParamSatelliteInfo) GPS.resolve("RTGPS_GetSatelliteInfo");
        if(RtGPS_GetSatelliteInfo)
        {
            return RtGPS_GetSatelliteInfo(pSatellites);
        }
    }
	return FALSE;
}

double RtGPS_GetDOP(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetDouble RtGPS_GetDOP = (pFuncGetDouble) GPS.resolve("RTGPS_GetDOP");
        if(RtGPS_GetDOP)
        {
            return RtGPS_GetDOP();
        }
    }
	return NULL;
}

double RtGPS_GetSpeed(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetDouble RtGPS_GetSpeed = (pFuncGetDouble) GPS.resolve("RTGPS_GetSpeed");
        if(RtGPS_GetSpeed)
        {
            return RtGPS_GetSpeed();
        }
    }
	return NULL;
}

void RtGPS_PosToDMS(double dbPos , int *iDeg , int *iMin , int *iSec)
{
	int		ii = 0 , jj = 0;
	ii = int(dbPos/100) ;
	*iDeg = ii;

	jj = int(dbPos - ii *100) ;
	*iMin = jj;

	*iSec = (int)((dbPos - (ii*100 + jj) ) * 60 );
}

double RtGPS_GetHeading(void)
{
    if(GPS.isLoaded())
    {
        pFuncGetDouble RtGPS_GetHeading = (pFuncGetDouble) GPS.resolve("RTGPS_GetHeading");
        if(RtGPS_GetHeading)
        {
            return RtGPS_GetHeading();
        }
    }
	return NULL;
}