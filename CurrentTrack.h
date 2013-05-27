#ifndef CURRENT_TRACK_H
#define CURRENT_TRACK_H
#include "track.h"


#define CURRENT_TRACK_FILE_NAME	"current_track.trk"
#define MIN_LOG_DISTANCE	5.0 // m

class CCurrentTrack : public CTrack
{
public:
	enum
	{
		LOG_METHOD_TIME = 0,
		LOG_METHOD_DISTANCE,
		LOG_METHOD_AUTO
	};
	CCurrentTrack(void);
	~CCurrentTrack(void);
	void setLogMethod(int iLogMethod);
	bool setLogDistance(double dLogDistance);
	double  GetDistance( double dCurLat, double dCurLong,double dOldLat, double dOldLong);
	void TrigMePerSec(void);

private:
	int		   m_iLogMethod;
	double	   m_dLogDistance;
	int m_time_counter;
	void UpdateByTime(void);
	void UpdateByDistance(double dLogDistance);
	void UpdateAuto(void);
	void addCurrentPt(void);
};
#endif//CURRENT_TRACK_H