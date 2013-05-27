#include "ExternalLibrary.h"
#include "RtGPS.h"
#include "Nordic.h"
//-----		ECompass information
struct  ECOMPASS_INFO
{
        short Yaw;
        short Roll;
        short Pitch;
        short DOE;
};

#define ALTI_IN_SIZE	1
#define ALTI_OUT_SIZE	3

typedef enum 
{
	__OK,
	_ALTI_ERROR_1,
	_ALTI_ERROR_2,
}API_RET;

//----------------------------------------------------------------------------------
typedef struct 
{ 
	// Altimeter 
	long OUT_TEMP;
	long OUT_PRESSURE;
	long OUT_ALTITUDE;

}INFO_GET, *pINFO_GET;	
//----------------------------------------------------------------------------------
typedef struct 
{ 
	// Altimeter 
	long IN_ALTITUDE;
}INFO_SET, *pINFO_SET;	

QLibrary eCompass("eCompass");
QLibrary Altimeter("BikeInfo");
extern QLibrary GPS;
extern QLibrary Nordic;

//external function type definitions
typedef void (*pFuncGetVersion)(int*, int*);
typedef int (*pFuncGetInt)(void);
typedef void (*pFuncCompassInfo)(ECOMPASS_INFO* pInfo);
typedef API_RET (*pFuncGetAltInfo)(pINFO_GET);
typedef API_RET (*pFuncCalibrateAlt)(pINFO_SET);
typedef void (*pFuncGetAltVersion)(BYTE*, BYTE*);
typedef BOOL (*pFuncReturnBoolCommand)(void);

//General library functions
void LoadLibraries(void)
{
    //Load Library eCompass
    if(!eCompass.isLoaded())
    {
        eCompass.load();
    }
	if(!Altimeter.isLoaded())
	{
		Altimeter.load();
	}
	if(!Nordic.isLoaded())
	{
		Nordic.load();
	}
	if(!GPS.isLoaded())
	{
		GPS.load();
	}
}

void ReleaseLibraries(void)
{
    if(eCompass.isLoaded())
    {
        eCompass.unload();
    }
	if(Altimeter.isLoaded())
	{
		Altimeter.unload();
	}
	if(Nordic.isLoaded())
	{
		Nordic.unload();
	}
	if(GPS.isLoaded())
	{
		GPS.unload();
	}
}

//eComnpass libray funcitons
void eCompass_GetVersion(int *pMajorVer, int *pMinorVer)
{
    if(eCompass.isLoaded())
    {
        pFuncGetVersion eCompass_GetVersion = (pFuncGetVersion) eCompass.resolve("eCompass_GetVersion");
        if(eCompass_GetVersion)
        {
            eCompass_GetVersion(pMajorVer, pMinorVer);
        }
    }
}

BOOL eCompass_Init()
{
    if(eCompass.isLoaded())
    {
        pFuncGetInt eCompass_Init = (pFuncGetInt) eCompass.resolve("eCompass_Init");
        if(eCompass_Init)
        {
            return eCompass_Init();
        }
    }
	return FALSE;
}

BOOL eCompass_Start()
{
    if(eCompass.isLoaded())
    {
        pFuncGetInt eCompass_Start = (pFuncGetInt) eCompass.resolve("eCompass_Start");
        if(eCompass_Start)
        {
            return eCompass_Start();
        }
    }
	return FALSE;
}

BOOL eCompass_Stop()
{
    if(eCompass.isLoaded())
    {
        pFuncGetInt eCompass_Stop = (pFuncGetInt) eCompass.resolve("eCompass_Stop");
        if(eCompass_Stop)
        {
            return eCompass_Stop();
        }
    }
	return FALSE;
}

short eCompass_GetYaw()
{
	ECOMPASS_INFO Info;

    if(eCompass.isLoaded())
    {
        pFuncCompassInfo eCompass_GetInfo = (pFuncCompassInfo) eCompass.resolve("eCompass_GetInfo");
        if(eCompass_GetInfo)
        {
			eCompass_GetInfo(&Info);
			return Info.Yaw;
        }
    }
	return -1;
}

//Altimeter library functions
long AltimeterGetTemperature()
{
	INFO_GET Info;

    if(Altimeter.isLoaded())
    {
        pFuncGetAltInfo AltiMeter_GetInfo = (pFuncGetAltInfo) Altimeter.resolve("GetBikeInfo");
        if(AltiMeter_GetInfo)
        {
			AltiMeter_GetInfo(&Info);
			return Info.OUT_TEMP;
        }
    }
	return -100;
}

long AltimeterGetPressure()
{
	INFO_GET Info;

    if(Altimeter.isLoaded())
    {
        pFuncGetAltInfo AltiMeter_GetInfo = (pFuncGetAltInfo) Altimeter.resolve("GetBikeInfo");
        if(AltiMeter_GetInfo)
        {
			AltiMeter_GetInfo(&Info);
			return Info.OUT_PRESSURE;
        }
    }
	return -1;
}


long AltimeterGetAltitude()
{
	INFO_GET Info;

    if(Altimeter.isLoaded())
    {
        pFuncGetAltInfo AltiMeter_GetInfo = (pFuncGetAltInfo) Altimeter.resolve("GetBikeInfo");
        if(AltiMeter_GetInfo)
        {
			AltiMeter_GetInfo(&Info);
			return Info.OUT_ALTITUDE;
        }
    }
	return -1;
}

BOOL AltimeterCalibrateAltitude(long altitude)
{
	INFO_SET Info;

	Info.IN_ALTITUDE = altitude;
    if(Altimeter.isLoaded())
    {
        pFuncCalibrateAlt AltiMeter_SetInfo = (pFuncCalibrateAlt) Altimeter.resolve("SetBikeInfo");
        if(AltiMeter_SetInfo)
        {
			AltiMeter_SetInfo(&Info);
			return TRUE;
        }
    }
	return FALSE;
}

void InitializeHardwareSensor(void)
{
	BOOL bResult;
	//initial hardware sensor
    LoadLibraries();
	
	RtGPS_Init(1,38400);	//Open GPS port
    eCompass_Init();	//initial e-compass
    eCompass_Start();	//start e-compass
	bResult = NOR_Open();
	bResult = HRS_Start();
	bResult = CAD_Start();
}

void UninitializeHardwareSensor(void)
{
	eCompass_Stop();
	HRS_Stop();
	CAD_Stop();
	NOR_Close();
}