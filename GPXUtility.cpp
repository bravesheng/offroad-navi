#include "GPXUtility.h"
#include <QDebug>
#include <math.h>

GPXUtility::GPXUtility(QWidget *parent)
    : QWidget(parent)
{ 
}

GPXUtility::~GPXUtility()
{
}

bool GPXUtility::TRK2GPX(CTrack* pTrack, QString strTRK2GPX)
{
	bool bRet = false;	
  
	m_pTrack = pTrack;
	
	QString strGPXFile;
	strGPXFile = strTRK2GPX.left(strTRK2GPX.length()-3) + "GPX";

	QFile GPX;
    GPX.setFileName(strGPXFile);
    if (GPX.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<< "open write file OK!";
        CreateTRKGPX(&GPX);
        GPX.close();
		bRet = true;
    }
    else
    {
        qDebug()<< "Cannot write file!";
    }  	

	return bRet;
}

bool GPXUtility::CreateTRKGPX(QIODevice *device)
{
    QDomElement root;
    QDomProcessingInstruction gpxinstruction;

    gpxinstruction = GPXTRKDoc.createProcessingInstruction
                     ("xml","version=\"1.0\"");
    GPXTRKDoc.appendChild(gpxinstruction);

    root= GPXTRKDoc.createElement("gpx");
    root.setAttribute("version","1.1");
    root.setAttribute("creator","RTK-OffRoad Navigation");

    GPXTRKDoc.appendChild(root);

    QDomElement AddTrack;
    AddTrack = CreateTRK();
    root.appendChild(AddTrack);

    const int IndentSize = 1;
    QTextStream out(device);
    GPXTRKDoc.save(out, IndentSize);
    return true;
}

QDomElement GPXUtility::CreateTRK()
{
    QDomElement TRKelement;
    QDomElement TRKSubelement;
    QDomText text;

    TRKelement = GPXTRKDoc.createElement("trk");
    //----------------------------
    TRKSubelement = GPXTRKDoc.createElement("name");
	text.clear();
    text = GPXTRKDoc.createTextNode("RTK Test Track");
    TRKSubelement.appendChild(text);
    TRKelement.appendChild(TRKSubelement);
    //----------------------------
    TRKSubelement = GPXTRKDoc.createElement("trkseg");
    TRKelement.appendChild(TRKSubelement);
    //----------------------------------
	
	for(int i=0; i<m_pTrack->count(); i++)
    {
        QDomElement OneTRK = CreateOneTRKPT(i);
        TRKSubelement.appendChild(OneTRK);		
    }
    TRKelement.appendChild(TRKSubelement);

    return TRKelement;
}

QDomElement GPXUtility::CreateOneTRKPT(int iLogIndex)
{
    QDomElement TRKPT;
    QDomText data;

    TRKPT = GPXTRKDoc.createElement("trkpt");
    QString strLat;
	strLat.setNum(m_pTrack->TrkPt(iLogIndex)->lat, 'g', 9);
    TRKPT.setAttribute("lat", strLat);

    QString strLong;
	if(fabs(m_pTrack->TrkPt(iLogIndex)->lon)>100)
		strLong.setNum(m_pTrack->TrkPt(iLogIndex)->lon, 'g', 10);
	else
		strLong.setNum(m_pTrack->TrkPt(iLogIndex)->lon, 'g', 9);
	TRKPT.setAttribute("lon",strLong);

    //Elevation
    //if Barometer alt is available, "ele" is Barometer alt, 
    //otherwise, it is GPS alt.
    //if both are not available, "ele" = -1;
    //ele format, xxxx.x
    QDomElement trkEle = GPXTRKDoc.createElement("ele");
    data.clear();
	double d_GPXEle = m_pTrack->TrkPt(iLogIndex)->elevation;   
	if(d_GPXEle < 0 ) // Barometer alt is not available
	{
		if(m_pTrack->TrkPt(iLogIndex)->elevation >=0 ) //GPS alt is available
			d_GPXEle = m_pTrack->TrkPt(iLogIndex)->elevation;
		else
			d_GPXEle = -1;
	}

    QString strEle;
	strEle.setNum(d_GPXEle, 'g', 6);
	int iPoint = strEle.indexOf(".");
	if(iPoint>0) //Find ponit
		strEle = strEle.left(iPoint+2);
	else
	{
		if(d_GPXEle == -1)
			strEle = "-1";
		else
			strEle = strEle + ".0";
	}
    //qDebug() << strEle << iPoint << strEle.left(iPoint+2);
    data = GPXTRKDoc.createTextNode(strEle);
    trkEle.appendChild(data);
    TRKPT.appendChild(trkEle);
    //=====================================================================
    
    //Time=================================================================
    QDomElement trkTime = GPXTRKDoc.createElement("time");
    data.clear();
    QString strTime;
	strTime.sprintf("%d-%d-%dT%d:%d:%dZ",
		m_pTrack->TrkPt(iLogIndex)->datetime.date().year(), 
		m_pTrack->TrkPt(iLogIndex)->datetime.date().month(),
		m_pTrack->TrkPt(iLogIndex)->datetime.date().day(),
		m_pTrack->TrkPt(iLogIndex)->datetime.time().hour(),
		m_pTrack->TrkPt(iLogIndex)->datetime.time().minute(),
		m_pTrack->TrkPt(iLogIndex)->datetime.time().second());
    data = GPXTRKDoc.createTextNode(strTime);
    trkTime.appendChild(data);
    TRKPT.appendChild(trkTime);
    //=====================================================================

    //Heart rate===========================================================
    QDomElement trkHR = GPXTRKDoc.createElement("hr");
    data.clear();
    QString strHR;
	strHR.setNum(m_pTrack->TrkPt(iLogIndex)->heart_rate, 10);	
	if(m_pTrack->TrkPt(iLogIndex)->heart_rate <= 0) //HR is not available
		strHR = "-1";

    data = GPXTRKDoc.createTextNode(strHR);
    trkHR.appendChild(data);
    TRKPT.appendChild(trkHR);
    //=====================================================================

    //cadence==============================================================
    QDomElement trkCad = GPXTRKDoc.createElement("cad");
    data.clear();
    QString strCad;     
	strCad.setNum(m_pTrack->TrkPt(iLogIndex)->cadence, 10);
	if(m_pTrack->TrkPt(iLogIndex)->cadence <= 0) //Cadence is not available
		strCad = "-1";
    data = GPXTRKDoc.createTextNode(strCad);
    trkCad.appendChild(data);
    TRKPT.appendChild(trkCad);
    //=====================================================================

    return TRKPT;
}

bool GPXUtility::WPT2GPX(QPOIDatabase& Poi, int iPOICnt, QString strWPTFile)
{
	bool bRet = false;
	
	iPOINum =  iPOICnt;	
	QString strGPXfile;
    strGPXfile = strWPTFile.left(strWPTFile.length()-2) + "GPX";
    qDebug()<< strGPXfile;

	QFile GPX;
    GPX.setFileName(strGPXfile);
    if (GPX.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<< "open write file OK!";		
		CreateWPTGPX(&GPX, Poi);		
		bRet = true;
    }
    else
    {
        qDebug()<< "Cannot write file!";
     }

	return bRet;
}

bool GPXUtility::CreateWPTGPX(QIODevice *device, QPOIDatabase& POIData)
{
    QDomElement root;
    QDomProcessingInstruction gpxinstruction;

    gpxinstruction = GPXTRKDoc.createProcessingInstruction
                     ("xml","version=\"1.0\"");
    GPXTRKDoc.appendChild(gpxinstruction);

    root= GPXTRKDoc.createElement("gpx");
    root.setAttribute("version","1.1");
    root.setAttribute("creator","RTK-OffRoad Navigation");
    GPXTRKDoc.appendChild(root);

    for(int i=0; i<iPOINum; i++)
    {
        QDomElement OneWPT = CreateOneWPTPT(i, POIData);
        root.appendChild(OneWPT);
    }

    const int IndentSize = 1;
    QTextStream out(device);
    GPXTRKDoc.save(out, IndentSize);
    return true;
}


QDomElement GPXUtility::CreateOneWPTPT(int iPOIIndex, QPOIDatabase& CurrentPOI)
{
   QDomElement WPTPT;   
   QDomText data;

   QItemInfo m_POIItem;
   m_POIItem = CurrentPOI.GetPOIItem(iPOIIndex);
   qDebug() << m_POIItem.m_Lon;

   WPTPT = GPXWPTDoc.createElement("wpt");

   QString strLat;
   strLat.setNum(m_POIItem.m_Lat, 'g', 9);
   WPTPT.setAttribute("lat", strLat);

   QString strLong;
   strLong.setNum(m_POIItem.m_Lon, 'g', 9);
   WPTPT.setAttribute("lon",strLong);

   QDomElement wptEle = GPXWPTDoc.createElement("ele");
   data.clear();
   QString strEle;
   strEle.setNum(m_POIItem.m_Alt, 'g', 9);
   data = GPXWPTDoc.createTextNode(strEle);
   wptEle.appendChild(data);
   WPTPT.appendChild(wptEle);

   QDomElement wptName = GPXWPTDoc.createElement("name");
   data.clear();
   data = GPXWPTDoc.createTextNode(m_POIItem.m_Name);
   wptName.appendChild(data);
   WPTPT.appendChild(wptName);   

   QString strIcon;
   strIcon.setNum(m_POIItem.m_IconId, 10);
   QDomElement wptSym = GPXWPTDoc.createElement("sym");
   data.clear();
   data = GPXWPTDoc.createTextNode(strIcon);
   wptSym.appendChild(data);
   WPTPT.appendChild(wptSym);   
   return WPTPT;
}


bool GPXUtility::RTE2GPX(QString strRTEFile)
{
	bool bRet = false;	
	QString strGPXFile;
	strGPXFile = strRTEFile.left(strRTEFile.length()-3) + "GPX";

	QFile GPX;
    GPX.setFileName(strGPXFile);
    if (GPX.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<< "open write file OK!";
        CreateRTEGPX(&GPX);
        GPX.close();
		bRet = true;
    }
    else
    {
        qDebug()<< "Cannot write file!";
    }  	

	return bRet;
}

bool GPXUtility::CreateRTEGPX(QIODevice *device)
{	
	QDomElement root;
    QDomProcessingInstruction gpxinstruction;

    gpxinstruction = GPXTRKDoc.createProcessingInstruction
                     ("xml","version=\"1.0\"");
    GPXTRKDoc.appendChild(gpxinstruction);

    root= GPXTRKDoc.createElement("gpx");
    root.setAttribute("version","1.1");
    root.setAttribute("creator","RTK-OffRoad Navigation");
    GPXTRKDoc.appendChild(root);

	QDomElement AddRoute;
    AddRoute = CreateRTE();
    root.appendChild(AddRoute);

    const int IndentSize = 1;
    QTextStream out(device);
    GPXTRKDoc.save(out, IndentSize);
    return true;
}

QDomElement GPXUtility::CreateRTE()
{
    QDomElement RTEroot;
	QDomElement RTESubelement;
    QDomText data;
    
	RTEroot = GPXRTEDoc.createElement("rte");
	//-------------------------------------------------
    RTESubelement = GPXRTEDoc.createElement("name");
    data.clear();
    data = GPXRTEDoc.createTextNode("RTK Test Route");
	RTESubelement.appendChild(data);
	RTEroot.appendChild(RTESubelement);

    RTESubelement = GPXRTEDoc.createElement("number");
    data.clear();
    QString strNum = "1";
    //strNum.setNum(iRouteNum, 10);
    data = GPXRTEDoc.createTextNode(strNum);
    RTESubelement.appendChild(data);
	RTEroot.appendChild(RTESubelement);

	for(int i=0; i<10/*iRTENum*/; i++)
	{
		QDomElement OneRTE = CreateOneRTE(i);
		RTEroot.appendChild(OneRTE);
	}
    return RTEroot;
}

QDomElement GPXUtility::CreateOneRTE(int iRTEindex)
{
	QDomElement RTEPT;
    QDomText data;
	RTEPT = GPXRTEDoc.createElement("rtept");

    QString strLat;
    QString strLong;
    
	double dLat = 23.0 + iRTEindex*0.1;
	double dLong = 121.5 - iRTEindex*0.1;

	strLat.setNum(dLat, 'g', 9);
    if(fabs(dLong)>100)
        strLong.setNum(dLong, 'g', 10);
    else
        strLong.setNum(dLong, 'g', 9);

    RTEPT.setAttribute("lat", strLat);
    RTEPT.setAttribute("lon", strLong);

	QDomElement rteptEle = GPXRTEDoc.createElement("ele");
    data.clear();
    data = GPXRTEDoc.createTextNode("100");
    rteptEle.appendChild(data);
    RTEPT.appendChild(rteptEle);

	QDomElement rteptTime = GPXRTEDoc.createElement("time");
    data.clear();
	data = GPXRTEDoc.createTextNode("2009-07-30T11:39:34Z");
    rteptTime.appendChild(data);
    RTEPT.appendChild(rteptTime);

    QDomElement rteptName = GPXRTEDoc.createElement("name");
    data.clear();
	QString strName;
	strName.sprintf("RTE%d",iRTEindex);
    data = GPXRTEDoc.createTextNode(strName);
    rteptName.appendChild(data);
    RTEPT.appendChild(rteptName);

	QDomElement rteptSym = GPXRTEDoc.createElement("sym");
    data.clear();
    data = GPXRTEDoc.createTextNode("Dot");
    rteptSym.appendChild(data);
    RTEPT.appendChild(rteptSym);

    return RTEPT;
}
