#ifndef ALTIMETERSCREEN_H
#define ALTIMETERSCREEN_H

#include <QWidget>
#include <QLabel>
#include "RtSettingList.h"
#include "buttons.h"

class AltimeterScreen : public QWidget
{
    Q_OBJECT
public:
	enum{
		CALIBRATE_BAROMETER=0,
		CALIBRATE_ALTITUDE,
		CALIBRATE_GPS
	};

    AltimeterScreen(QWidget *parent = 0);

public slots:
	void ListSelect(int iSelect);

private:
//    CReturnButton ReturnBtn;

protected:
    QLabel          *m_pLabelTitle;
    QLabel          *m_pLabelNotes;
    QPixmap         *m_pImageBackground;
    QPixmap         *m_pImageListItem1[3];
    QPixmap         *m_pImageListItem2[3];

    RtSettingList   *m_pListBox;
    void paintEvent(QPaintEvent *event);
};

#endif // ALTIMETERSCREEN_H
