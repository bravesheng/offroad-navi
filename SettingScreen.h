#ifndef SETTINGSCREEN_H
#define SETTINGSCREEN_H

#include <QDialog>
#include <QLabel>
#include "RtSettingList.h"
#include "buttons.h"
#include "SettingLog.h"

class SettingScreen : public QDialog
{
    Q_OBJECT
public:
    enum{
		SYS_ID_UNIT=0,
		SYS_ID_ALTIMETER,
		SYS_ID_ANT_SPORT,
		SYS_ID_ABOUT
	};

	SettingLog			m_SettingLog;
	CSetting			m_Setting;

public:
    SettingScreen(QWidget *parent = 0);
    ~SettingScreen();
    void OnUnitScreen(void);
    void OnAltimeterScreen(void);
	void OnAntSport(void);
    void OnAboutScreen(void);

public slots:
    void SListSelect(int iSelect);
    void SListScroll(void);

private:
    int    m_iUnit;
 //   CReturnButton ReturnBtn;

protected:
    int             m_iSelect;
    QLabel          *m_pLabelTitle;
    QPixmap         *m_pImageBackground;
    QPixmap         *m_pImageListItem1[3];
    QPixmap         *m_pImageListItem2[3];
	QPixmap			*m_pListIcon[4];
	QPixmap			*m_pImageListStatus[3];
    RtSettingList   *m_pListBox;
    void paintEvent(QPaintEvent *event);
};

#endif // SETTINGSCREEN_H
