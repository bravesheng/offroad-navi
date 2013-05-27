#include "MainWindow.h"
#include <QDir>

CMainWindow::CMainWindow(QWidget *parent)
: QWidget(parent),
m_BtnScaleUp(this),
m_BtnScaleDown(this),
m_ContouWidget(this),
m_MainMenuBar(this),
m_pGadgetDialog(NULL)
{
	setGeometry(0, 0, 320, 240);
	m_ContouWidget.setGeometry(0, 0, 320, 240);
	m_BtnScaleUp.setGeometry ( 10, 50, 30, 30 );
	m_BtnScaleUp.setText ( "+" );
	m_BtnScaleDown.setGeometry ( 10, 90, 30, 30 );
	m_BtnScaleDown.setText ( "-" );
	m_ContouWidget.lower();

	connect(&m_BtnScaleUp, SIGNAL(clicked()), &m_ContouWidget,SLOT(ZoomIn()));
	connect(&m_BtnScaleDown, SIGNAL(clicked()), &m_ContouWidget,SLOT(ZoomOut()));
	/*
	//TripStart();

	//2009.07.23 Andy: Add to create the \\MyFlashDisk\\TrackLog folder
	QDir MkPath;
	MkPath.mkpath(g_strTrackDB_Path);

	//2009.07.23 Andy: Add to create the .\data folder
	QString strPOIPath = QDir::currentPath();
	strPOIPath+="\\data";
	MkPath.mkpath(strPOIPath);

	// CurrentTrack path:\\MyFlashDisk\\TrackLog\\CurrentTrack.trk
	QString strCurrentTrack = g_strTrackDB_Path;
	strCurrentTrack += "\\CurrentTrack.trk";
	m_pCurrentTrack = new CCurrentTrack(strCurrentTrack);

	//m_pCurrentTrack->startLog();
	*/
}

CMainWindow::~CMainWindow()
{
	TripStop();

	//m_pCurrentTrack->stopLog();
}

/******************************************************************************
Function:       
Description:    
Parameters:     
Return Value:   
********************************************************************************/
void CMainWindow::TripStart()
{
	//-- Start QTimer
	m_pQTimerTrip = new QTimer(this);
	connect(m_pQTimerTrip, SIGNAL(timeout()), this, SLOT(TripUpdate()));
	m_pQTimerTrip->start(1000);
}

void CMainWindow::TripStop()
{
	//-- Stop QTimer
	m_pQTimerTrip->stop();
}

void CMainWindow::TripUpdate()
{
	double Lon, Lat, Alt;
	
	if(RtGPS_IfFix())
	{
		RtGPS_GetPos(&Lon, &Lat, &Alt);
		m_ContouWidget.Draw(Lon, Lat);
		m_ContouWidget.update();
	}
}

void CMainWindow::OpenGadgetPage(int mode)
{
	if(m_pGadgetDialog)
	{
		delete m_pGadgetDialog;
	}
	m_pGadgetDialog = new CGadgetsDialog(this, mode);
	m_pGadgetDialog->show();
}
