#ifndef TRACKLOG_H
#define TRACKLOG_H

#include "RtGPS.h"
#include "Nordic.h"
#include "ExternalLibrary.h"
#include <QTime>
#include <QList>
#include <QColor>
#include <QDataStream>

#define TRACKS_DIR	"\\MyFlashDisk\\GPX\\Tracks\\"

class CTrkPt
{
public:
	QDateTime datetime;
	double lon;
	double lat;
	double elevation;	//use GPS data if eletric altimeter not exist.
	unsigned short heart_rate;
	unsigned short cadence;
	double speed;
};

class CTrack
{
public:
	CTrack();
	CTrack(QString name);
	QColor color(void);
	void setColor(QColor color);
	QString name(void);
	void setName(QString name);
	CTrkPt* TrkPt(int index);
	void addTrkPt(CTrkPt* pt);
	int count(void);
	bool readTrkFile(void);		//clear own data and read new data .trk data from file.
	bool saveTrkFile(void);		//save own data into .trk file.
	void clear(void);
protected:
	QColor m_color;
	QString m_name;
	QList<CTrkPt*> m_TrkPtList;
};

QDataStream &operator<<(QDataStream &out, const CTrkPt* pTrkPt);
QDataStream &operator>>(QDataStream &in, CTrkPt* pTrkPt);

#endif // TRACKLOG_H