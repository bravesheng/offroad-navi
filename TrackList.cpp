#include "TrackList.h"
#include <QDir>

void CTrackList::update(void)
{
	QDir currentDir;
	QStringList files;

	currentDir = QDir(TRACKS_DIR);
	QString SearchExt = "*.trk";

    files = currentDir.entryList(QStringList(SearchExt), QDir::Files | QDir::NoSymLinks, QDir::Name);

	int index = files.indexOf(CURRENT_TRACK_FILE_NAME);
	if( index != -1)
	{
		files.removeAt(index);
	}

	//add current_track
	m_TrackList.append(&m_CurrentTrack);
	//add tracks into list
	CTrack* pTrack;
	for(int i=0; i < files.count(); i++)
	{
		pTrack = new CTrack(currentDir.filePath(files[i]));
		m_TrackList.append(pTrack);
	}
}

int CTrackList::count(void)
{
	return m_TrackList.count();
}

CTrack* CTrackList::track(int index)
{
	return m_TrackList.at(index);
}

void CTrackList::addTrack(CTrack* pTrack)
{
	m_TrackList.append(pTrack);
}

void CTrackList::clear(void)
{
	while(!m_TrackList.isEmpty())
	{
		delete m_TrackList.takeFirst();
	}
}

CCurrentTrack* CTrackList::currentTrack(void)
{
	return &m_CurrentTrack;
}