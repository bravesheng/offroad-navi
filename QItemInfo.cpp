#include "QItemInfo.h"
#include "Global.h"

QItemInfo::QItemInfo()
{
    m_IconId = 0;
    m_Name = "";
    m_Lat = 0.0;
    m_Lon = 0.0;
    m_Alt = 0.0;
}

void QItemInfo::operator=(QItemInfo* pItemInfo)
{
    m_UniqueId = pItemInfo->m_UniqueId;			//UUID for use to find the POI when different sorting type.
    m_IconId = pItemInfo->m_IconId;
    m_Name = pItemInfo->m_Name;
    m_Lat = pItemInfo->m_Lat;
    m_Lon = pItemInfo->m_Lon;
    m_Alt = pItemInfo->m_Alt;
    m_Name = pItemInfo->m_Name;
}

bool  QItemInfo::GetDistance(double dCurLong, double dCurLat, int iUnitType, double& dDistance,double& dBearing)
{
    bool bRet = true;

	double dBearRadian = 0.0;
    CGlobal::GetDistance(dCurLat, dCurLong, m_Lat, m_Lon,&dDistance,&dBearRadian);
	dBearing = CGlobal::Radian2Degree(dBearRadian);
    dDistance = CGlobal::UnitConvert(iUnitType, dDistance);

    return bRet;
}
