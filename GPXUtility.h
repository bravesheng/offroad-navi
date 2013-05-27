#ifndef GPXUTILITY_H
#define GPXUTILITY_H

#include <QWidget>
#include <QFile>
#include <QDataStream>
#include <QDomDocument>
#include "QPOIDatabase.h"
#include "Track.h" 

class GPXUtility : public QWidget
{
public:
    GPXUtility(QWidget *parent = 0);
    ~GPXUtility();
	
	bool TRK2GPX( CTrack* pTrack, QString strTRK2GPX);	
	bool WPT2GPX(QPOIDatabase& Poi, int iPOICnt, QString strWPTFile);
	bool RTE2GPX(QString strRTEFile);

private:

	//For TRK	
	bool CreateTRKGPX(QIODevice *device);    
	QDomElement CreateTRK();
    QDomElement CreateOneTRKPT(int iLogIndex);
	QDomDocument    GPXTRKDoc;	
	CTrack* m_pTrack;
	//QList<TRKPT> TRK;

    //For WPT
	bool CreateWPTGPX(QIODevice *device, QPOIDatabase& POIData);
    QDomElement CreateOneWPTPT(int iPOIIndex, QPOIDatabase& CurrentPOI);
	QDomDocument    GPXWPTDoc;	  
    int iPOINum;		

    //For RTE
	bool CreateRTEGPX(QIODevice *device);
	QDomElement CreateRTE();
	QDomElement CreateOneRTE(int iRTEindex);
	QDomDocument    GPXRTEDoc;	        
    
};

#endif // GPXUTILITY_H
