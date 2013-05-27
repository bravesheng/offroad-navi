#ifndef ANTSPORTSCREEN_H
#define ANTSPORTSCREEN_H

#include <QDialog>
#include <QLabel>
#include "RtSettingList.h"
#include "SettingScreen.h"

class ANTsportScreen : public QDialog
{
    Q_OBJECT
public:
	enum{
		LIST_CANDENCE = 0,
		LIST_HEART_RATE,
		LIST_MAX_NUM
	};
    ANTsportScreen(QWidget *parent = 0);

public slots:
	void ListSelect(int iSelect);
    void ButtonOnOff(int iSelect,int iOnOff);//iOnOff - 0->off, 1->on .

private:
//    CReturnButton ReturnBtn;
	SettingScreen *m_pParentDlg;
	qint8 m_iCandenceEnable;
	qint8 m_iHeartRateEnable;

protected:
    QLabel          *m_pLabelTitle;
    QPixmap         *m_pImageBackground;
    QPixmap         *m_pImageListItem1[3];
    QPixmap	        *m_pImageListStatus[2];
    RtSettingList   *m_pListBox;

    void paintEvent(QPaintEvent *event);
};

#endif // ANTSPORTSCREEN_H
