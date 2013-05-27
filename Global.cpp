#include "Global.h"
#include <math.h>

#define Square(x) ((x)*(x))

const double CGlobal::m_dPI = 3.1415926535897932384626433832795028841971;

CGlobal::CGlobal()
{
}

double CGlobal::GetDistance(double dPointALat, double dPointALong, double dPointBLat, double dPointBLong)
{
    double dPointALongRadian = Degree2Radian(dPointALong);
    double dPointALatRadian = Degree2Radian(dPointALat);
    double dPointBLongRadian = Degree2Radian(dPointBLong);
    double dPointBLatRadian = Degree2Radian(dPointBLat);
    return GetDistanceRadian(dPointALatRadian, dPointALongRadian, dPointBLatRadian, dPointBLongRadian);
}

void CGlobal::GetDistance(double dPointALat, double dPointALong, double dPointBLat, double dPointBLong, double* pdDistance, double* pBearing)
{
    double dPointALongRadian = Degree2Radian(dPointALong);
    double dPointALatRadian = Degree2Radian(dPointALat);
    double dPointBLongRadian = Degree2Radian(dPointBLong);
    double dPointBLatRadian = Degree2Radian(dPointBLat);
    GreatCircle(dPointALatRadian, dPointALongRadian, dPointBLatRadian, dPointBLongRadian, pdDistance, pBearing);
}

double CGlobal::GetDistanceRadian(double dPointALat, double dPointALong, double dPointBLat, double dPointBLong )
{

    __int64 a = 6378137;
    double b = 6356752.3142;
    double f = 1/298.257223563;  // WGS-84 ellipsiod
    double DeltaLong = (dPointBLong-dPointALong);
    double U1 = atan((1-f) * tan(dPointALat));
    double U2 = atan((1-f) * tan(dPointBLat));
    double sinU1 = sin(U1);
    double cosU1 = cos(U1);
    double sinU2 = sin(U2);
    double cosU2 = cos(U2);

    double  lambda = DeltaLong;
    double  lambdaP =0.0;
    double  iterLimit = 20;
    double cosSqAlpha = 0.0;
    double	sinSigma  =0.0;
    double cos2SigmaM = 0.0;
    double cosSigma = 0.0;
    double sigma = 0.0;
    do {
                    double sinLambda = sin(lambda);
                    double cosLambda = cos(lambda);
                    sinSigma = sqrt((cosU2*sinLambda) * (cosU2*sinLambda) +
                                (cosU1*sinU2-sinU1*cosU2*cosLambda) * (cosU1*sinU2-sinU1*cosU2*cosLambda));
    if (sinSigma==0) return 0;  // co-incident points
    cosSigma = sinU1*sinU2 + cosU1*cosU2*cosLambda;
    sigma = atan2(sinSigma, cosSigma);
    double sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
    cosSqAlpha = 1 - sinAlpha*sinAlpha;
    cos2SigmaM = cosSigma - 2*sinU1*sinU2/cosSqAlpha;
    if (_isnan(cos2SigmaM)) cos2SigmaM = 0;  // equatorial line: cosSqAlpha=0 (¡±6)
    double C = f/16*cosSqAlpha*(4+f*(4-3*cosSqAlpha));
    lambdaP = lambda;
    lambda = DeltaLong + (1-C) * f * sinAlpha *
            (sigma + C*sinSigma*(cos2SigmaM+C*cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)));
    } while (fabs(lambda-lambdaP) > 1e-12 && --iterLimit>0);

    if (iterLimit==0) return 10000000000.0;  // formula failed to converge
    double AA = (double)(a*a);
    double uSq = cosSqAlpha * (AA - b*b) / (b*b);
    double  A = 1 + uSq/16384*(4096+uSq*(-768+uSq*(320-175*uSq)));
    double B = uSq/1024 * (256+uSq*(-128+uSq*(74-47*uSq)));
    double deltaSigma = B*sinSigma*(cos2SigmaM+B/4*(cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)-
            B/6*cos2SigmaM*(-3+4*sinSigma*sinSigma)*(-3+4*cos2SigmaM*cos2SigmaM)));
    double s = b*A*(sigma-deltaSigma);

    return s;
}

double CGlobal::Degree2Radian(double fDegree)
{
    double fRadian =0.0;
    fRadian = fDegree* (m_dPI/180.);
    return fRadian;
}

double CGlobal::Radian2Degree(double fRadian)
{
    double fDegree =0.0;
    fDegree = fRadian * (180./m_dPI);
    return fDegree;
}

double CGlobal::Meter2KiloMeter(double dMeter)
{
    return dMeter / 1000.;
}

double CGlobal::KiloMeter2Meter(double dKiloMeter)
{
        return dKiloMeter*1000.;
}

double CGlobal::Meter2Mile(double dMeter)
{
    //1 ­^¨½ = 1.60934 ¤½¨½
    double dKiloMeter = Meter2KiloMeter(dMeter);
    return KiloMeter2Mile(dKiloMeter);
}

double CGlobal::Mile2Meter(double dMile)
{
    double dKiloMeter = 0.0;
    dKiloMeter = Mile2KiloMeter(dMile);
    return KiloMeter2Meter(dKiloMeter);
}

double CGlobal::Meter2Yard(double dMeter)
{
    return dMeter / 0.914;
}

double CGlobal::Yard2Meter(double dYard)
{
    return dYard * 0.914;
}

double CGlobal::KiloMeter2Mile(double dKiloMeter)
{
    return dKiloMeter / 1.60934;
}

double CGlobal::Mile2KiloMeter(double dMile)
{
    return dMile * 1.60934;
}

double CGlobal::UnitConvert(BYTE ucUnitType, double dDistance)
{
    double dConvertedDistance = 0.0;
    switch(ucUnitType)
    {
    case UNIT_KM:
        dConvertedDistance = CGlobal::Meter2KiloMeter(dDistance);
        break;
    case UNIT_YARD:
        dConvertedDistance = CGlobal::Meter2Yard(dDistance);
        break;
    case UNIT_MILE:
        dConvertedDistance = CGlobal::Meter2Mile(dDistance);
        break;
    case UNIT_M:
        dConvertedDistance = dDistance;
        break;
    }
    return dConvertedDistance;
}

// Sub-Routines #4
/****************************************************************************
* Function: void CDB_GreatCircle(double PointA_latitude, double PointA_longitude,
*                   	         double PointB_latitude, double PointB_longitude,
*                       	 double *GreatCircleDistance,
*                           	 double *GreatCircleBearing)
*
* Revision: 6.00
*
* Last Update: 17/06/96
*
* Compute great circle range (radians) and bearing(radians E of N) between 2
* points, A and B. The algorithm is given in "Map Projections Used by the
* U. S. Geological Survey", John P. Snyder, 1982 (Geological Survey Bulletin
* 1532).  Much more sophisticated (and time-consuming) algorithms exist for
* high accuracy over long baselines, see for example, "Spheroidal Geodesics,
* Reference Systems, & Local Geometry", U. S. Naval Ocean-ographic Office,
* publication SP-138.
*
* Input: PointA_Latitude 	- 	Point A WGS-84 latitude, radians.
*        PointA_Longitude 	- 	Point A WGS-84 longitude, radians.
*        PointB_Latitude 	- 	Point B WGS-84 latitude, radians.
*        PointB_Longitude	- 	Point B WGS-84 longitude, radians.
*
* Output: GreatCircleDistance - Distance between A and B, radians. meter
*         GreatCircleBearing - Bearing from A to B, radians east of north.
*
* Return Value: None.
****************************************************************************/
void CGlobal::GreatCircle(double PointA_Latitude, double PointA_Longitude,
                          double PointB_Latitude, double PointB_Longitude,
                          double *GreatCircleDistance, double *GreatCircleBearing)
{
    double Cos_PointA_Latitude;     /* Cosine of point A latitude. */
    double Cos_PointB_Latitude;     /* Cosine of point B latitude. */
    double Sin_PointA_Latitude;     /* Sine of point A latitude. */
    double Sin_PointB_Latitude;     /* Sine of point B latitude. */
    double Delta_Longitude;     	/* Longitude difference B - A, radians. */
    double Cos_Delta_Longitude;		/* Cosine of delta longitude. */
    double Sin_Delta_Longitude;     /* Sine of delta longitude. */
    double Sin_Distance;            /* Sine of great circle distance. */
    double Cos_Distance;            /* Cosine of great circle distance. */
    double Sin_Bearing;             /* Sine of great circle bearing. */
    double Cos_Bearing;             /* Cosine of great circle bearing. */
    double intermeadiate;           /* An intermeadiate calculation. */
    double temp_distance;

    Cos_PointA_Latitude = cos(PointA_Latitude);
    Cos_PointB_Latitude = cos(PointB_Latitude);
    Sin_PointA_Latitude = sin(PointA_Latitude);
    Sin_PointB_Latitude = sin(PointB_Latitude);

    Delta_Longitude 	= PointB_Longitude - PointA_Longitude;

    Cos_Delta_Longitude = cos(Delta_Longitude);
    Sin_Delta_Longitude = sin(Delta_Longitude);

    /* Get the cosine of the great circle distance. */
    Cos_Distance = Sin_PointA_Latitude*Sin_PointB_Latitude
            + Cos_PointA_Latitude*Cos_PointB_Latitude*Cos_Delta_Longitude;

    /* Get the sine of the great circle distance. */
    intermeadiate = Square(Cos_PointB_Latitude*Sin_Delta_Longitude)
            + Square(Cos_PointA_Latitude*Sin_PointB_Latitude
            - Sin_PointA_Latitude*Cos_PointB_Latitude*Cos_Delta_Longitude);

    Sin_Distance = sqrt(fabs(intermeadiate));

    /* Get the the great circle distance. */
    if(fabs(Sin_Distance)>.0000001 || fabs(Cos_Distance)>.0000001)
            temp_distance = atan2(Sin_Distance,Cos_Distance);
    else
            temp_distance = 0.0;                         /* Same point. */

    *GreatCircleDistance = temp_distance * Earth_r( (PointA_Latitude+PointB_Latitude)/2 );

    /* Get the sine of the great circle bearing. */
    Sin_Bearing = Sin_Delta_Longitude*Cos_PointB_Latitude;

    /* Get the cosine of the great circle bearing. */
    Cos_Bearing = Cos_PointA_Latitude*Sin_PointB_Latitude - Sin_PointA_Latitude*Cos_PointB_Latitude*Cos_Delta_Longitude;

    /* Get the great circle bearing. */
    if(fabs(Sin_Bearing)>.0000001 || fabs(Cos_Bearing)>.0000001)
    {
        intermeadiate = atan2(Sin_Bearing,Cos_Bearing);

        while(intermeadiate<0.0)
                intermeadiate += 2.0*m_dPI;//M_PI

        *GreatCircleBearing = intermeadiate;
    }
    else
        *GreatCircleBearing = 0.0;            /* Due north or co-incident. */
}

// Sub-Routines #5
/****************************************************************************
* Function: double CDB_Earth_r( double  lat )
*
* Revision: 6.01
*
* Last Update: 23/10/96
*
* Converts from WGS-84 latitude, longitude and height and X, Y and Z
* rectangular co-ordinates. For more information: Simo H. Laurila,
* "Electronic Surveying and Navigation", John Wiley & Sons (1976).
*
* Input:  lat.
*
* Output:  earth-radius.
*
* Return Value: None.
****************************************************************************/
double CGlobal::Earth_r(double lat)
{
    double n;         /* WGS-84 Radius of curvature in the prime vertical. */
    double a;         /* WGS-84 semimajor axis. */
    double e;         /* WGS-84 first eccentricity. */
    double slat;      /* sin(lat). */

    e = 0.0033527794541675;
    a = 6378147.8;
    slat = sin( lat );
    n = a * ( 1 - e* slat*slat );

    return( n );
}
