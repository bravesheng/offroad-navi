#ifndef QITEMINFO_H
#define QITEMINFO_H

#include <QString>

class QItemInfo
{
public:
    int m_UniqueId;			//UUID for use to find the POI when different sorting type.
    short m_IconId;
    QString m_Name;
    double m_Lat;
    double m_Lon;
    double m_Alt;

public:
    QItemInfo();
    bool  GetDistance(double dCurLong, double dCurLat, int iUnitType, double& dDistance,double &dBearing);
    void operator=(QItemInfo* pItemInfo);
};

#endif // QITEMINFO_H
