#include "Track.h"
#include "RtGPS.h"
#include "GPXUtility.h"
#include <QFile>
#include <QDir>

QDataStream &operator<<(QDataStream &out, const CTrkPt* pTrkPt)
{
	if(pTrkPt)
	{
		out << pTrkPt->datetime;
		out << pTrkPt->lon;
		out << pTrkPt->lat;
		out << pTrkPt->elevation;
		out << pTrkPt->heart_rate;
		out << pTrkPt->cadence;
		out << pTrkPt->speed;
	}
	return out;
}

QDataStream &operator>>(QDataStream &in, CTrkPt* pTrkPt)
{
	if(pTrkPt == NULL)
	{
		pTrkPt = new CTrkPt;
	}
	in >> pTrkPt->datetime;
	in >> pTrkPt->lon;
	in >> pTrkPt->lat;
	in >> pTrkPt->elevation;
	in >> pTrkPt->heart_rate;
	in >> pTrkPt->cadence;
	in >> pTrkPt->speed;
	return in;
}


CTrack::CTrack(QString name)
{
	QDir dir(TRACKS_DIR);
	if(!dir.exists())
	{
		if(!dir.mkpath(TRACKS_DIR))
		{
			qDebug("make dir fail");
		}
	}
	m_name = name;
	readTrkFile();
}

QColor CTrack::color(void)
{
	return m_color;
}

void CTrack::setColor(QColor color)
{
	m_color = color;
}

QString CTrack::name(void) 
{
	return m_name;
}

void CTrack::setName(QString name)
{
	m_name = name;
}

CTrkPt* CTrack::TrkPt(int index)
{
	return m_TrkPtList.at(index);
}

void CTrack::addTrkPt(CTrkPt* pt)
{
	m_TrkPtList.append(pt);
}

int CTrack::count(void)
{
	return m_TrkPtList.count();
}

bool CTrack::readTrkFile(void)
{	
	bool return_value = false;
	QString filename;
	filename = TRACKS_DIR + m_name + ".trk";
	QFile file(filename);
	if(file.open(QIODevice::ReadOnly))
	{	//open file success
		QDataStream in(&file);    // read the data serialized from the file
		//clear original data
		clear();
		//read datas
		in >> m_color;
		in >> m_name;
		//append to track list
		while(!in.atEnd())
		{
			CTrkPt* pTrkPt = new CTrkPt;
			in >> pTrkPt;
			m_TrkPtList.append(pTrkPt);
		}
	}
	else
	{
		return_value = false;
	}
	file.close();
	return return_value;
}

bool CTrack::saveTrkFile(void)
{
	bool return_value = false;
	QString filename;
	filename = TRACKS_DIR + m_name + ".trk";
	QFile file(filename);
	if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{	//open file success
		if(!m_TrkPtList.isEmpty())
		{
			QDataStream out(&file);    // read the data serialized from the file
			out << m_color;
			out << m_name;
			for(int i=0; i < m_TrkPtList.count(); i++)
			{
				out << m_TrkPtList.at(i);
			}
		}
		else
		{
			return_value = false;
		}
	}
	file.close();
	return return_value;
}

void CTrack::clear(void)
{
	m_color = QColor(0,0,0);
	m_name.clear();
	while(!m_TrkPtList.isEmpty())
	{
		delete m_TrkPtList.takeFirst();
	}
}