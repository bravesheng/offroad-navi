#ifndef __RoGeoImage_h__
#define __RoGeoImage_h__

#include "RoWorkDir.h"
#include "RoMemDC.h"
#include "RoCoord.h"

class CRoGeoImage : public CRoMemDC {
public:
    CRoGeoImage () : CRoMemDC ((int) Width, (int)Width, QColor ( 255, 255, 255 )){}
    static void SetWorkDir ( LPCTSTR sWorkDir ){ m_WorkDir.Set ( sWorkDir ); }

    void DrawXY ( double fLon, double fLat, int iScale, int iDivider, int iAngle = 0 ){ DrawXY (( int )( fLon * WGS84IntScale ), ( int )( fLat * WGS84IntScale ), iScale, iDivider, iAngle ); }
    void DrawXY ( int iX, int iY, int iScale, int iDivider );

protected:
    enum
    {
        Width = 456,
        MapWidth = Width * 50000 / 600,
        OrgX = 12000000,
        OrgY = 2150000,
    };

    static CRoWorkDir m_WorkDir;
};

#endif
