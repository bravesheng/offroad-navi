#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>

#include "ContourEngine\RoWidget_2.h"
#include "Buttons.h"
#include "ExternalLibrary.h"
#include "MainMenuBar.h"
#include "gadgetsdialog.h"
#include "CurrentTrack.h"

class CMainWindow : public QWidget
{
    Q_OBJECT
public:
    CMainWindow(QWidget *parent = 0);
	~CMainWindow();
	void OpenGadgetPage(int mode);
private:
	QPushButton m_BtnScaleUp;
	QPushButton m_BtnScaleDown;
	CMainMenuBar m_MainMenuBar;
	CGadgetsDialog* m_pGadgetDialog;
	CCurrentTrack  *m_pCurrentTrack;
	CRoWidget m_ContouWidget;
	QTimer *m_pQTimerTrip;
	void TripStart();
	void TripStop();
public slots:
	void TripUpdate();
};


#endif//MAIN_WINDOW_H

