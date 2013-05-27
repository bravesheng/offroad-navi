#ifndef RT_GPS_H
#define RT_GPS_H

#include <QLibrary>
/*
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef int					HWND;
typedef unsigned int		DWORD;
*/

// Com port number definition
#define	OPEN_COM1		1	// use com1
#define	OPEN_COM2	 	2	// use com2
#define	OPEN_COM3	 	3	// use com3
#define	OPEN_COM4	 	4	// use com4
#define	OPEN_COM5	 	5	// use com5
#define	OPEN_COM6	 	6	// use com6
#define	OPEN_COM7	 	7	// use com7
#define	OPEN_COM8	 	8	// use com8
#define	OPEN_COM9	 	9	// use com9
#define	OPEN_COM10	 	10	// use com10
#define	OPEN_COM11	 	11	// use com11
#define	OPEN_COM12	 	12	// use com12
#define	OPEN_COM13	 	13	// use com13
#define	OPEN_COM14	 	14	// use com14
#define	OPEN_COM15	 	15	// use com15

// RTTMC_Init return value
#define	COMPORT_OPEN_FAILED		 	0
#define	DATA_READ_ERROR				1
#define	DATA_READ_OK				2
#define	THREAD_CREATE_FAILED		3
#define	INVALID_WINDOW_HANDLE		4

// GPS Fix mode
#define	GPS_NOFIX			0
#define	GPS_2D				1
#define	GPS_3D				2

typedef struct
{
	double dbGpslat;
	double dbGpslon;
} GPS_AVE;

#pragma pack(1)

//--------------------Define GSV data structure
typedef struct _SATELLITE_INFO_
{
	int	iSateId;
	int iElev;
	int iAzimuthInDegree;
	int	iCNO;
} SATEINFO;

//--------------------Define Lat/Lon/Alt data structure
typedef struct _POS_INFO
{
	double	dbLat;
	double	dbLon;
	double	dbAlt;
} Pos_Info;

//--------------------Define DOP structure
typedef struct _DOP_INFO
{
	double	dPdop;
	double	dHdop;
	double	dVdop;
} Dop_Info;

//--------------------Define Time structure
typedef struct _TIME_INFO
{
	int		iYear;
	int		iMonth;
	int		iDay;
	int		iUTCHour;
	int		iUTCMin;
	int		iUTCSec;
} Time_Info;

//--------------------Define GPS parameters structure
typedef struct _GPS_INFO_
{
	SATEINFO	SateInfo[20];       // 20 channel
	Pos_Info	PosInfo;
	Dop_Info	Dop;
	Time_Info	Time;
	double		dCOG;
	double		dbSpeed;
	BYTE		ucrFixMode;			// No Fix ; 2D and 3D
	int			iSateInView;		// 可觀察衛星數
	int			iSateInUsed[12];	// 使用衛星id
	int			iSateIsUsed;		// 使用衛星數
	BOOL		bFirstTimeToFixed;	// 是否是第一次鎖定
} GPSInfo;
#pragma pack ()

int RtGPS_Init(int nComport, int dwBaudrate);
int	RtGPS_GetUsedSatelliteNumber();
int	RtGPS_GetSatelliteInViewNumber();
int	RtGPS_IfFix();
int	RtGPS_GsaFixMode();
BOOL RtGPS_Uninit(void);
BOOL RtGPS_FirstTimeToFix(void);
BOOL RtGPS_GetDate(int* iYear, int* iMonth, int* iDay);
BOOL RtGPS_GetTime(int* iHour, int* iMinute, int* iSecond);
BOOL RtGPS_GetPos(double* dLong, double* dLat, double* dAlt = NULL);
BOOL RtGPS_GetUsedSatellites(int* piUsedSatellites);
BOOL RtGPS_GetSatelliteInfo(SATEINFO* pSatellites);
double RtGPS_GetDOP();
double RtGPS_GetSpeed();
void RtGPS_PosToDMS(double dbPos , int *iDeg , int *iMin , int *iSec);
double RtGPS_GetHeading();
#endif//RT_GPS_H