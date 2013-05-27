#ifndef GLOBAL_H
#define GLOBAL_H

const double MAX_DISTANCE_SHOW = 999.0;
const double MID_DISTANCE_SHOW = 9.9;

typedef unsigned char BYTE;
typedef int BOOL;

class CGlobal
{
public:
    enum DISTANCEUNIT
    {
        UNIT_M = 0,    //Meter
        UNIT_YARD,
        UNIT_KM,
        UNIT_MILE,
        UNIT_MAX_NUM
    };
    static const double  m_dPI;

public:
    CGlobal();
    static double   GetDistance(double dPointALat, double dPointALong, double dPointBLat, double dPointBLong );
    static void     GetDistance(double dPointALat, double dPointALong, double dPointBLat, double dPointBLong, double* pdDistance, double* pBearing);
    static double   Degree2Radian(double dDegree);
    static double   Radian2Degree(double dRadian);
    static double   Meter2KiloMeter(double dMeter);
    static double   KiloMeter2Meter(double dKiloMeter);
    static double   Meter2Mile(double dMeter);
    static double   Mile2Meter(double dMile);
    static double   Meter2Yard(double dMeter);
    static double   Yard2Meter(double dYard);
    static double   KiloMeter2Mile(double dKiloMeter);
    static double   Mile2KiloMeter(double dMile);
    static double   UnitConvert(BYTE ucUnitType, double dDistance);

private:
    static void     GreatCircle(double PointA_Latitude, double PointA_Longitude,
                                double PointB_Latitude, double PointB_Longitude,
                                double *GreatCircleDistance, double *GreatCircleBearing);
    static double   Earth_r(double lat);
    static double   GetDistanceRadian(double dPointALat, double dPointALong, double dPointBLat, double dPointBLong );

};

#endif // GLOBAL_H
