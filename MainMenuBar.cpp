#include "mainmenubar.h"
#include "ImagePool.h"
#include <QPainter>
#include <QtCore/QTimeLine>
#include <QProcess>
#include "gadgetsdialog.h"
#include "MainWindow.h"
#include "RtGPS.h"
#include "WEditScreen.h"
#include "QItemInfo.h"
#include "QPOIDatabase.h"
#include "GPXUtility.h"
#include <QMessageBox>

#define FRAME_START_POS				268
#define FRAME_END_POS				0
#define FRAME_WIDTH					320
#define FRAME_HEIGHT				240
#define FRAME_ANIMATION_TIME		500
#define DETECT_AREA_X				FRAME_START_POS
#define DETECT_AREA_Y				65
#define DETECT_AREA_WIDTH			70
#define DETECT_AREA_HEIGHT			100

//For OnRoad/OffRoad switch
#define		WM_NAVI_BASE 				WM_APP + 0x1300
#define		WM_NAVI_SWITCH_SCREEN		WM_NAVI_BASE + 0x01
#define		WM_NAVI_DST_UPDATED			WM_NAVI_BASE + 0x02
#define		WM_NAVI_RTE_UPDATED			WM_NAVI_BASE + 0x03
#define		WM_NAVI_WPT_UPDATED			WM_NAVI_BASE + 0x04


CMainMenuBar::CMainMenuBar(QWidget *parent)
: QWidget(parent),
m_ListBox(this, 62, 9, 250, 222),
m_BtnAddWaypoint(&m_ListBox),
m_BtnCompass(&m_ListBox),
m_BtnAltimeter(&m_ListBox),
m_BtnTripComputer(&m_ListBox),
m_BtnWaypointMgr(&m_ListBox),
m_BtnTrackMgr(&m_ListBox),
m_BtnSettings(&m_ListBox),
m_BtnExit(&m_ListBox),
m_BtnOnRoad(&m_ListBox)
{
    setGeometry(QRect(FRAME_START_POS, 0, FRAME_WIDTH, FRAME_HEIGHT));
	m_pWaypointDialog = NULL;
	m_pTrackDialog = NULL;
	m_pSettingDialog = NULL;

    // Prepare the animated switch:
    m_timeLine = new QTimeLine(FRAME_ANIMATION_TIME, this);
    m_timeLine->setCurveShape(QTimeLine::EaseInOutCurve);
    connect(m_timeLine, SIGNAL(frameChanged(int)), SLOT(setBarPosition(int)));
	connect(m_timeLine, SIGNAL(finished()), SLOT(SlideFinished()));

    m_BtnOnRoad.setText("Rousen Navigation");
	m_BtnAddWaypoint.setText("Add Waypoint");
	m_BtnCompass.setText("Compass");
	m_BtnAltimeter.setText("Altimeter");
	m_BtnTripComputer.setText("Trip Computer");
	m_BtnWaypointMgr.setText("Waypoints");
	m_BtnTrackMgr.setText("Tracks");
	m_BtnSettings.setText("Settings");
	m_BtnExit.setText("Exit");

	m_BtnOnRoad.SetImages(GetImg(IMG_ICON_COMPASS),GetImg(IMG_ICON_COMPASS), GetImg(IMG_ICON_COMPASS));
	m_BtnAddWaypoint.SetImages(GetImg(IMG_ICON_ADD_WAYPOINT),GetImg(IMG_ICON_ADD_WAYPOINT), GetImg(IMG_ICON_ADD_WAYPOINT));
	m_BtnCompass.SetImages(GetImg(IMG_ICON_COMPASS),GetImg(IMG_ICON_COMPASS), GetImg(IMG_ICON_COMPASS));
	m_BtnAltimeter.SetImages(GetImg(IMG_ICON_ALTIMETER),GetImg(IMG_ICON_ALTIMETER), GetImg(IMG_ICON_ALTIMETER));
	m_BtnTripComputer.SetImages(GetImg(IMG_ICON_TRIP_COMPUTER),GetImg(IMG_ICON_TRIP_COMPUTER), GetImg(IMG_ICON_TRIP_COMPUTER));
	m_BtnWaypointMgr.SetImages(GetImg(IMG_ICON_WAYPOINT),GetImg(IMG_ICON_WAYPOINT), GetImg(IMG_ICON_WAYPOINT));
	m_BtnTrackMgr.SetImages(GetImg(IMG_ICON_TRACK),GetImg(IMG_ICON_TRACK), GetImg(IMG_ICON_TRACK));
	m_BtnSettings.SetImages(GetImg(IMG_ICON_SETTINGS),GetImg(IMG_ICON_SETTINGS), GetImg(IMG_ICON_SETTINGS));
	m_BtnExit.SetImages(GetImg(IMG_ICON_EXIT),GetImg(IMG_ICON_EXIT), GetImg(IMG_ICON_EXIT));

	connect(&m_BtnOnRoad, SIGNAL(clicked()), this, SLOT(OpenOnRoad()));
	connect(&m_BtnAddWaypoint, SIGNAL(clicked()), this, SLOT(addWaypoint()));
	connect(&m_BtnSettings, SIGNAL(clicked()), this, SLOT(OpenSettings()));
	connect(&m_BtnCompass, SIGNAL(clicked()), this, SLOT(OpenCompass()));
	connect(&m_BtnAltimeter, SIGNAL(clicked()), this, SLOT(OpenAltimeter()));
	connect(&m_BtnTripComputer, SIGNAL(clicked()), this, SLOT(OpenTripComputer()));
	connect(&m_BtnWaypointMgr, SIGNAL(clicked()), this, SLOT(OpenWaypointMgr()));
	connect(&m_BtnTrackMgr, SIGNAL(clicked()), this, SLOT(OpenTrackMgr()));
	connect(&m_BtnExit, SIGNAL(clicked()), parent, SLOT(close()));

	m_ListBox.AddButton(&m_BtnOnRoad);
	m_ListBox.AddButton(&m_BtnAddWaypoint);
	m_ListBox.AddButton(&m_BtnCompass);
	m_ListBox.AddButton(&m_BtnAltimeter);
	m_ListBox.AddButton(&m_BtnTripComputer);
	m_ListBox.AddButton(&m_BtnWaypointMgr);
	m_ListBox.AddButton(&m_BtnTrackMgr);
	m_ListBox.AddButton(&m_BtnSettings);
	m_ListBox.AddButton(&m_BtnExit);
}

void CMainMenuBar::paintEvent(QPaintEvent*)//event
{
    QPainter painter(this);
	painter.drawPixmap(0, 0, GetImg(IMG_BAR_MAIN_MENU)->width(), GetImg(IMG_BAR_MAIN_MENU)->height(), *GetImg(IMG_BAR_MAIN_MENU));
}

void CMainMenuBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

	if(event->x() > 70)
	{
		return;
	}
	m_timeLine->setFrameRange(FRAME_START_POS, FRAME_END_POS);


	if(m_timeLine->state() == QTimeLine::NotRunning)
	{

		if(m_timeLine->currentFrame() == FRAME_END_POS)	//means opened
		{
			m_timeLine->setDirection(QTimeLine::Backward);
		}
		if(m_timeLine->currentFrame() == FRAME_START_POS)	//means not opened
		{
			m_timeLine->setDirection(QTimeLine::Forward);
			//setGeometry(QRect(FRAME_START_POS, 0, FRAME_WIDTH, FRAME_HEIGHT));
		}
	}
    m_timeLine->start();
}

/*!
    \internal
    Animation to change the state of the widget at the end of the
    set position or the start position. \n
    If one of the two possible states is reached the signal is
    send.
*/
void CMainMenuBar::setBarPosition(int position)
{
	QPoint CurrentPos;
	QPoint TargetPos;
    CurrentPos = this->pos();
    TargetPos.setX(position);
    TargetPos.setY(CurrentPos.y());
    move(TargetPos);
}

void CMainMenuBar::OpenWaypointMgr(void)
{
	if(m_pWaypointDialog)
	{
		delete m_pWaypointDialog;
	}
	m_pWaypointDialog = new WaypointScreen((QWidget*)parent());
	m_pWaypointDialog->show();
}

void CMainMenuBar::OpenTrackMgr(void)
{
	if(m_pTrackDialog)
	{
		delete m_pTrackDialog;
	}
	m_pTrackDialog = new TrackScreen((QWidget*)parent());
	m_pTrackDialog->show();
}

void CMainMenuBar::OpenSettings(void)
{
	
	if(m_pSettingDialog)
	{
		delete m_pSettingDialog;
	}
	m_pSettingDialog = new SettingScreen((QWidget*)parent());
	m_pSettingDialog->show();
}

void CMainMenuBar::OpenAltimeter(void)
{
	((CMainWindow*)parent())->OpenGadgetPage(ELEVATION_PLOT);
}

void CMainMenuBar::OpenTripComputer(void)
{
	((CMainWindow*)parent())->OpenGadgetPage(TRIP_COMPUTER_MODE);
}


void CMainMenuBar::OpenCompass(void)
{
	((CMainWindow*)parent())->OpenGadgetPage(COMPASS_MODE);
}

void CMainMenuBar::SlideFinished(void)
{
	if(m_timeLine->currentFrame() == FRAME_START_POS)	//means menu closed
	{
	//	setGeometry(QRect(DETECT_AREA_X, DETECT_AREA_Y, DETECT_AREA_WIDTH, DETECT_AREA_HEIGHT));
	}
}

void CMainMenuBar::addWaypoint(void)
{
	bool bGetGPS = false;
	double dLon = 0.0;
	double dLat = 0.0;
	double dEle = 0.0;

    if(RtGPS_IfFix())
	{
		if(RtGPS_GetPos(&dLon, &dLat, &dEle))
			bGetGPS = true;
	}
	
	if(bGetGPS)
	{
		WEditScreen *pWEditScreen = new WEditScreen((QWidget*)parent(),WEditScreen::BTN_TYPE_SAVE_ONLY);
		pWEditScreen->setModal(true);
	
		//Default value.
		QString strName = "";
		int iIconIdx =  0;
	
		pWEditScreen->setIconIdx(iIconIdx);
		pWEditScreen->setEditText(strName);
	
		int iRet = pWEditScreen->exec();

		if(iRet == 1)//Save
		{
			QString strModify = "";
			strModify = pWEditScreen->getEditText();
			int iIconModify = pWEditScreen->getIconIdx();
		
				QPOIDatabase m_AddPOIDB;
				QItemInfo m_ItemInfo;
				m_ItemInfo.m_UniqueId = 0;
				m_ItemInfo.m_IconId = iIconModify;
				m_ItemInfo.m_Name = strModify;
				m_ItemInfo.m_Lon = dLon;
				m_ItemInfo.m_Lat = dLat;
				m_ItemInfo.m_Alt = dEle;
		
				m_AddPOIDB.SavePOIItem(&m_ItemInfo);

				QPOIDatabase m_AddPOIDBTest;
				m_AddPOIDBTest.ReadDatabase(g_strWayPtDB_Path);
				int iPOICount = m_AddPOIDBTest.GetItemCount();
				GPXUtility mGPX;
				mGPX.WPT2GPX(m_AddPOIDBTest, iPOICount, g_strWayPtDB_Path);
		}
	}
	else
	{
		//Show "GPS Not Available." message
		 QMessageBox::warning(this, tr("Warnning"),
										tr("GPS Not Available."),
										QMessageBox::Ok,
										QMessageBox::Ok);
	
	}
}
//For OnRoad/OffRoad switch
void CMainMenuBar::OpenOnRoad(void)
{	
	//Send message to OnRoad Navigation
	HWND   OnRoad_hwnd = NULL;
	OnRoad_hwnd = ::FindWindow(NULL , L"MobileNavigator");	
	if(OnRoad_hwnd)
	{
	::SendMessage(OnRoad_hwnd, WM_NAVI_SWITCH_SCREEN, 1, 0);	
	QString strmsg;
	strmsg.sprintf("%d",WM_NAVI_SWITCH_SCREEN);
		qDebug() << strmsg << "--->" << "Show OnRoad";

	QWidget *parent = (QWidget*)this->parent();
	parent->setGeometry(0,0,0,0);
	}	
}
