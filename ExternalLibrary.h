#ifndef EXTERNALLIBRARY
#define EXTERNALLIBRARY
#include <QLibrary>

void LoadLibraries(void);
void ReleaseLibraries(void);
//e-Compass
void eCompass_GetVersion(int *pMajorVer, int *pMinorVer);
BOOL eCompass_Init();
BOOL eCompass_Start();
BOOL eCompass_Stop();
short eCompass_GetYaw();
//Altimeter
long AltimeterGetTemperature();
long AltimeterGetPressure();
long AltimeterGetAltitude();
BOOL AltimeterCalibrateAltitude(long altitude);
void AltimeterGetVersion(int *pMajorVer, int *pMinorVer);

void InitializeHardwareSensor(void);
void UninitializeHardwareSensor(void);


#endif // EXTERNALLIBRARY
