#ifndef __RoCoord_h__
#define __RoCoord_h__

void WGS84toUTM ( double Lat84, double Lon84, int& Northing, int& Easting );
void UTM2WGS84 ( int iUTMX, int iUTMY, double& fWGS84X, double& fWGS84Y );

#define WGS84IntScale   100000

#endif
