#ifndef WAYPOINTSCREEN_H
#define WAYPOINTSCREEN_H

#include <QDialog>
#include <QLabel>
#include "RtPushButton.h"
#include "RtListBox.h"
#include "RtGlobalDefine.h"
#include "QPOIDatabase.h"
#include "Global.h"
#include "SettingLog.h"
#include <QTimer>

class WaypointScreen : public QDialog
{
    Q_OBJECT

private:
	SettingLog			m_SettingLog;
	CSetting			m_Setting;
    QPOIDatabase m_Database;
    BYTE	 m_iUnit;

// Declare Variable/Function
protected:
    enum{
        LIST_ICON1=0,
        LIST_ICON2,
        LIST_ICON3,
        LIST_ICON4,
        LIST_ICON5,
        LIST_ICON6,
        LIST_ICON7,
        LIST_ICON8,
        LIST_ICON9,
        LIST_ICON10,
        LIST_ICON_NUM
    };
    int            m_iSelect;
    QPixmap        *m_pImageBackground;
    QPixmap        *m_pImageQuit[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageHome[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageMapView[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageTarget[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageEdit[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageShare[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageListItem1[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageListItem2[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageIcons[LIST_ICON_NUM];
    QPixmap        *m_pImageDirectIcon;
    QLabel         *m_pLabelTitle;
    QTimer         *m_pTestDirect;
    RtPushButton   *m_pPushButtonHome;
    RtPushButton   *m_pPushButtonView;
    RtPushButton   *m_pPushButtonTarget;
    RtPushButton   *m_pPushButtonEdit;
    RtPushButton   *m_pPushButtonShare;
    RtListBox      *m_pListBox;
//    ListThread     *m_pListThread;
	QTimer		   *m_pListTimer;

    void paintEvent(QPaintEvent *event);
    void EnableFunctionButton(bool bEnable = false);

public:
    WaypointScreen(QWidget *parent = 0);

public slots:
    void UpdateDirect(void);
    void ListSelect(int iSelect);
    void ListScroll(void);
    void ViewOnMap();
    void Target();
    void Edit();
    void Share();
    void Home();
    void UpdateListbox(void);
};

#endif // WAYPOINTSCREEN_H
