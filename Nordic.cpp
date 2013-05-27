#include "Nordic.h"

//external function type definitions
typedef BOOL (*pFuncGetBool)(void);
typedef USHORT (*pFuncGetUShort)(void);
typedef UCHAR (*pFuncGetUCHARParamUCHAR)(UCHAR);
typedef UCHAR (*pFuncGetUCHAR)(void);
typedef UCHAR* (*pFuncGetUCHARPt)(void);
typedef BOOL (*pFuncGetBoolParamUCharPt)(UCHAR*);
typedef BOOL (*pFuncStart)(USHORT, UCHAR);
typedef BOOL (*pFuncGetId)(UCHAR, UCHAR*, USHORT*);

QLibrary Nordic("NOR_DLL");

BOOL NOR_Open(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBool NOR_Open = (pFuncGetBool)Nordic.resolve("NOR_Open");
        if(NOR_Open)
        {
            return NOR_Open();
        }
    }
	return FALSE;
}
BOOL NOR_Close(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBool NOR_Close = (pFuncGetBool)Nordic.resolve("NOR_Close");
        if(NOR_Close)
        {
            return NOR_Close();
        }
    }
	return FALSE;
}

BOOL NOR_Reset(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBool NOR_Reset = (pFuncGetBool)Nordic.resolve("NOR_Reset");
        if(NOR_Reset)
        {
            return NOR_Reset();
        }
    }
	return FALSE;
}

UCHAR NOR_GetChStatus(UCHAR ucChannel)
{
    if(Nordic.isLoaded())
    {
        pFuncGetUCHARParamUCHAR NOR_GetChStatus = (pFuncGetUCHARParamUCHAR)Nordic.resolve("NOR_GetChStatus");
        if(NOR_GetChStatus)
        {
            return NOR_GetChStatus(ucChannel);
        }
    }
	return NULL;
}

BOOL NOR_GetChID(UCHAR ucChannel, UCHAR *ucManufact, USHORT *usDeviceNum)
{
    if(Nordic.isLoaded())
    {
        pFuncGetId NOR_GetChID = (pFuncGetId)Nordic.resolve("NOR_GetChID");
        if(NOR_GetChID)
        {
            return NOR_GetChID(ucChannel,ucManufact,usDeviceNum);
        }
    }
	return FALSE;
}

BOOL HRS_Start(USHORT usDeviceNumber, UCHAR ucManufactureID)
{
    if(Nordic.isLoaded())
    {
        pFuncStart HRS_Start = (pFuncStart)Nordic.resolve("HRS_Start");
        if(HRS_Start)
        {
            return HRS_Start(usDeviceNumber,ucManufactureID);
        }
    }
	return FALSE;
}

UCHAR HRS_GetHeartRate(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetUCHAR HRS_GetHeartRate = (pFuncGetUCHAR)Nordic.resolve("HRS_GetHeartRate");
        if(HRS_GetHeartRate)
        {
            return HRS_GetHeartRate();
        }
    }
	return NULL;
}

BOOL HRS_Stop(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBool HRS_Stop = (pFuncGetBool)Nordic.resolve("HRS_Stop");
        if(HRS_Stop)
        {
            return HRS_Stop();
        }
    }
	return FALSE;
}

BOOL CAD_Start(USHORT usDeviceNumber, UCHAR ucManufactureID)
{
    if(Nordic.isLoaded())
    {
        pFuncStart CAD_Start = (pFuncStart)Nordic.resolve("CAD_Start");
        if(CAD_Start)
        {
            return CAD_Start(usDeviceNumber, ucManufactureID);
        }
    }
	return FALSE;
}

USHORT CAD_GetCandence(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetUShort CAD_GetCandence = (pFuncGetUShort)Nordic.resolve("CAD_GetCandence");
        if(CAD_GetCandence)
        {
            return CAD_GetCandence();
        }
    }
	return NULL;
}

BOOL CAD_Stop(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBool CAD_Stop = (pFuncGetBool)Nordic.resolve("CAD_Stop");
        if(CAD_Stop)
        {
            return CAD_Stop();
        }
    }
	return FALSE;
}

BOOL RTK_Start(USHORT usDeviceNumber, UCHAR ucManufactureID)
{
    if(Nordic.isLoaded())
    {
        pFuncStart RTK_Start = (pFuncStart)Nordic.resolve("RTK_Start");
        if(RTK_Start)
        {
            return RTK_Start(usDeviceNumber, ucManufactureID);
        }
    }
	return FALSE;
}

UCHAR* RTK_GetRxBuf(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetUCHARPt RTK_GetRxBuf = (pFuncGetUCHARPt)Nordic.resolve("RTK_GetRxBuf");
        if(RTK_GetRxBuf)
        {
            return RTK_GetRxBuf();
        }
    }
	return NULL;
}

BOOL RTK_Stop(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBool RTK_Stop = (pFuncGetBool)Nordic.resolve("RTK_Stop");
        if(RTK_Stop)
        {
            return RTK_Stop();
        }
    }
	return FALSE;
}

BOOL SND_Start(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBool SND_Start = (pFuncGetBool)Nordic.resolve("SND_Start");
        if(SND_Start)
        {
            return SND_Start();
        }
    }
	return FALSE;
}

BOOL SND_SendTxBuf(UCHAR *ucTxBuf)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBoolParamUCharPt SND_SendTxBuf = (pFuncGetBoolParamUCharPt)Nordic.resolve("SND_SendTxBuf");
        if(SND_SendTxBuf)
        {
            return SND_SendTxBuf(ucTxBuf);
        }
    }
	return FALSE;
}

BOOL SND_Stop(void)
{
    if(Nordic.isLoaded())
    {
        pFuncGetBool SND_Stop = (pFuncGetBool)Nordic.resolve("SND_Stop");
        if(SND_Stop)
        {
            return SND_Stop();
        }
    }
	return FALSE;
}