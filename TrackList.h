#ifndef TRACK_LIST_H
#define TRACK_LIST_H

#include "Track.h"
#include <QList>
#include "CurrentTrack.h"

class CTrackList
{
public:
	void update(void);	//update list
	int count(void);
	CTrack* track(int index);
	void addTrack(CTrack* pTrack);
	CCurrentTrack* currentTrack(void);
private:
	//m_TrackList only stored XML format tracks. Not included g_CurrentTrack in List.
	QList<CTrack*> m_TrackList; 
	CCurrentTrack m_CurrentTrack;
	void clear(void);
};

#endif//TRACK_LIST_H