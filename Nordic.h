#ifndef NORDIC_H
#define NORDIC_H

#include "QLibrary"

//--------------------------------------------------------------------------------//
#define ANT_COM_PORT     5
#define ANT_BAUDRATE     38400
#define ANT_SEARCH_CNT   12

#define HRS_DEVICE_TYPE  120
#define CAD_DEVICE_TYPE  123
#define RTK_DEVICE_TYPE  168
#define RTK_DEVICE_NUM   6
#define RTK_MANUFACT_ID  18
#define RTK_RF_FREQ      99

#define STATUS_UNASSIGN  0
#define STATUS_ASSIGNED  1
#define STATUS_SEARCHING 2
#define STATUS_TRACKING  3

#define CH_HRS           0
#define CH_CAD           1
#define CH_RTK           2
#define CH_SND           3

#define TOGGLE_MASK      0x80
#define MAX_LOST_CNT     60
#define BSC_PRECISION    ((ULONG)1000)

#define HRS_DEVICE_LOST  0xFF
#define CAD_DEVICE_LOST  0xFFFF
//--------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------//
BOOL   NOR_Open(void);
BOOL   NOR_Close(void);
BOOL   NOR_Reset(void);

UCHAR  NOR_GetChStatus(UCHAR ucChannel);
BOOL   NOR_GetChID(UCHAR ucChannel, UCHAR *ucManufact, USHORT *usDeviceNum);

BOOL   HRS_Start(USHORT usDeviceNumber=0, UCHAR ucManufactureID=0);
UCHAR  HRS_GetHeartRate(void);
BOOL   HRS_Stop(void);

BOOL   CAD_Start(USHORT usDeviceNumber=0, UCHAR ucManufactureID=0);
USHORT CAD_GetCandence(void);
BOOL   CAD_Stop(void);

BOOL   RTK_Start(USHORT usDeviceNumber=RTK_DEVICE_NUM, UCHAR ucManufactureID=RTK_MANUFACT_ID);
UCHAR *RTK_GetRxBuf(void);
BOOL   RTK_Stop(void);

BOOL   SND_Start(void);
BOOL   SND_SendTxBuf(UCHAR *ucTxBuf);
BOOL   SND_Stop(void);
//--------------------------------------------------------------------------------//

#endif//NORDIC_H