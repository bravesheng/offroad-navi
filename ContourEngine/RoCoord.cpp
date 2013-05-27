#include "stdafx.h"
#include <math.h>
#include "RoCoord.h"

#if 0
const double constFw = 0.00335281066474;
const double constFg = 0.00335292371299;
const double constPI = 3.141592653589793;
const double constAw = 6378137.0;
const double constAg = 6378160.0;

const double constA = 6378160.0;
const double constB = 6356774.7192;
const double constF = 0.00335292371299;
const double constK0 = 0.9999;

void WGS84toUTM ( double Lat84, double Lon84, int& Northing, int& Easting )
{
    double x,y,z,h,ew,eg;
    double fi,lamda,ro;
    double lont,lati, lati1, lati2;
    double fLat67, fLon67;

   ew = 2 * constFw - constFw * constFw ;
   eg = 2 * constFg - constFg*constFg ;
   fi=lamda=ro=0.;
   fi    = (double) (Lat84/180.0*constPI);
   lamda = (double) (Lon84/180.0*constPI);

   ro    = constAw/sqrt( 1-pow(ew*sin(fi),2));
   x=y=z=h=0.;
   h = 100 ;
   x = (ro + h)*cos(fi)*cos(lamda)+  757.0;
   y = (ro + h)*cos(fi)*sin(lamda)+  348.0;
   z = (ro*(1-pow(ew,2))+h)*sin(fi)+ 176.0;
   lont=lati=0.;
   lont = atan(y / x) + constPI;
   lati = 0.41887;
   //lati = atan((z+ro*eg*eg*sin(lati)) / sqrt(pow(x,2)+pow(y,2)));

   lati1 = z+ro*eg*eg*sin(lati);
   lati2 = pow(x,2)+pow(y,2);
   lati = atan( lati1 / sqrt( lati2 ) );

   fLon67=lont/constPI*180.0 ;
   fLat67=lati/constPI*180.0 ;

   double eccSquared = 2.0*constF-constF*constF;
   double LongOrigin = 121.0;
   double eccPrimeSquared;
   double N, T, C, A, M;
   double deg2rad = 3.141592653589793/180.0;

   eccPrimeSquared = (eccSquared)/(1-eccSquared);
   N = constA/sqrt(1-eccSquared*sin(fLat67*deg2rad)*sin(fLat67*deg2rad));
   T = tan(fLat67*deg2rad)*tan(fLat67*deg2rad);
   C = eccPrimeSquared*cos(fLat67*deg2rad)*cos(fLat67*deg2rad);
   A = (cos(fLat67*deg2rad))*(fLon67-LongOrigin)*deg2rad;
   M = 111133.34878*fLat67 - 16038.95495*sin(2*fLat67*deg2rad)
          + 16.83348915*sin(4*fLat67*deg2rad) - 0.021985885*sin(6*fLat67*deg2rad)
          + 0.000030398*sin(8*fLat67*deg2rad);
   Easting = (int)( constK0*N*(  A + (1-T+C)*A*A*A/6
                    + (5-18*T+T*T+72*C-58*eccPrimeSquared)*A*A*A*A*A/120
                     )
                 + 250000.0 );
   Northing = (int)( constK0*(  M + N*tan(fLat67*deg2rad) * (  A*A/2 + (5-T+9*C+4*C*C)*A*A*A*A/24
                     + (61-58*T+T*T+600*C-330*eccPrimeSquared)*A*A*A*A*A*A/720
                      )
                      )
                 );
}

void UTM2WGS84 ( int iUTMX, int iUTMY, double& fWGS84X, double& fWGS84Y )
{
    int iDiffX, iDiffY;
 
    int iWGS84X = 4356000;     // 121*36000;
    int iWGS84Y = 828000;      //  23*36000;
    int iUTMXnew;
    int iUTMYnew;
    double fLon;
    double fLat;

    while ( 1 )
    {
        fLon = (double) iWGS84X / 36000;
        fLat = (double) iWGS84Y / 36000;

        WGS84toUTM ( fLat, fLon, iUTMYnew, iUTMXnew );

        iDiffX = iUTMXnew - iUTMX;
        iDiffY = iUTMYnew - iUTMY;

        if ( abs(iDiffX) + abs(iDiffY) > 4 ) {
            if ( abs(iDiffX) >= 9 )
            {
                iWGS84X -= iDiffX/9;
            }
            else
            {
                if ( iDiffX > 0 )
                {
                    iWGS84X--;
                }
                else if ( iDiffX < 0 )
                {
                    iWGS84X++;
                }
            }
            if ( abs(iDiffY) >= 9 )
            {
                iWGS84Y -= iDiffY/9;
            }
            else
            {
                if ( iDiffY > 0 )
                {
                    iWGS84Y--;
                }
                else if ( iDiffY < 0 )
                {
                    iWGS84Y++;
                }
            }
        }
        else
        {
            fWGS84X = (double)iWGS84X / 36000;
            fWGS84Y = (double)iWGS84Y / 36000;

            return;
        }
    }
}

#else
void WGS84toUTM ( double Lat84, double Lon84, int& Northing, int& Easting )
{
    Northing = (int)( Lat84 * WGS84IntScale );
    Easting = (int)( Lon84 * WGS84IntScale );
}

void UTM2WGS84 ( int iUTMX, int iUTMY, double& fWGS84X, double& fWGS84Y )
{
    fWGS84X = (double)iUTMX / WGS84IntScale;
    fWGS84Y = (double)iUTMY / WGS84IntScale;
}
#endif
