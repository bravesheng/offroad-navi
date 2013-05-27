#include "AnalyzingThread.h"
#include "RdTripComputer.h"
#include "RdGuideEngine.h"
#include "TrackList.h"
#include <QDebug>

extern CTripComputer g_TripComputer;
extern CGuideEngine g_Guide;
extern CTrackList g_TrackList;

void CAnalyzingThread::run(void)
{
	m_pTimerOneSec = new QTimer(this);
	connect(m_pTimerOneSec, SIGNAL(timeout()), this, SLOT(OneSecondUpdate()));
	m_pTimerOneSec->start(1000);	// one second
	exec();
}

void CAnalyzingThread::OneSecondUpdate(void)
{
	qDebug("OneSecondUpdate");
	g_TripComputer.TripUpdate();
	g_TrackList.currentTrack()->TrigMePerSec();
	//-- Guide Information update  //-- 20090730 Richard.Lin
	g_Guide.CalWayPointInfo();
	g_Guide.CalTrkInfo();
}