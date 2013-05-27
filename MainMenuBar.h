#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

#include <QWidget>
#include "waypointscreen.h"
#include "TrackScreen.h"
#include "SettingScreen.h"
#include "RtListBox.h"
#include "MainMenuListItem.h"

class QTimeLine;

class CMainMenuBar : public QWidget
{
    Q_OBJECT
public:
    CMainMenuBar(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent* event);
protected slots:
	void mouseReleaseEvent(QMouseEvent *event);
private Q_SLOTS:
    void setBarPosition(int position);
	void SlideFinished(void);
	void OpenWaypointMgr(void);
	void OpenTrackMgr(void);
	void OpenAltimeter(void);
	void OpenTripComputer(void);
	void OpenCompass(void);
	void OpenSettings(void);
	void addWaypoint(void);

	//For OnRoad/OffRoad switch
	void OpenOnRoad(void);

private:
	QTimeLine *m_timeLine;
	RtListBox m_ListBox;
	CMainMenuListItem m_BtnWaypointMgr;
	CMainMenuListItem m_BtnTrackMgr;
	CMainMenuListItem m_BtnCompass;
	CMainMenuListItem m_BtnAltimeter;
	CMainMenuListItem m_BtnTripComputer;
	CMainMenuListItem m_BtnSettings;
	CMainMenuListItem m_BtnExit;
	CMainMenuListItem m_BtnAddWaypoint;
	CMainMenuListItem m_BtnOnRoad;
	WaypointScreen* m_pWaypointDialog;
	TrackScreen* m_pTrackDialog;
	SettingScreen* m_pSettingDialog;
};

#endif // MAINMENUBAR_H
