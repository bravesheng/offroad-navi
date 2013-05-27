#ifndef TRACKSCREEN_H
#define TRACKSCREEN_H

#include <QDialog>
#include <QLabel>
#include "RtPushButton.h"
#include "RtListBox.h"
#include "Buttons.h"
#include "RtGlobalDefine.h"
#include <QTimer>

class TrackScreen : public QDialog
{
    Q_OBJECT

private:
	CReturnButton ReturnBtn;

public:
    TrackScreen(QWidget *parent = 0);
    ~TrackScreen();

public slots:
    void ListSelect(int iSelect);
    void ListScroll(void);
    void ViewOnMap();
    void Elevation();
    void Edit();
    void Share();
    void Home();
    void UpdateListbox(void);

private:
    int            m_iSelect;
    QPixmap        *m_pImageBackground;
    QPixmap        *m_pImageHome[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageMapView[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageElevation[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageEdit[BUTTON_IMG_COUNT];
    QPixmap        *m_pImageShare[BUTTON_IMG_COUNT];
 //   QPixmap        *m_pImageIcons[LIST_ICON_NUM];
    QLabel         *m_pLabelTitle;
    RtPushButton   *m_pPushButtonHome;
    RtPushButton   *m_pPushButtonView;
    RtPushButton   *m_pPushButtonElevation;
    RtPushButton   *m_pPushButtonEdit;
    RtPushButton   *m_pPushButtonShare;
    RtListBox      m_ListBox;

	QTimer		   *m_pListTimer;

    void paintEvent(QPaintEvent *event);
    void EnableFunctionButton(bool bEnable);
	void OnEditCurrentTrack();
};

#endif // TRACKSCREEN_H
