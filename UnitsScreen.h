#ifndef UNITSSCREEN_H
#define UNITSSCREEN_H

#include <QDialog>
#include <QLabel>
#include "RtSettingList.h"
#include "Buttons.h"
#include "SettingLog.h"
#include "SettingScreen.h"

class UnitsScreen : public QDialog
{
    Q_OBJECT
public:
    SettingLog m_SettingLog;
    CSetting   m_Setting;

    UnitsScreen(QWidget *parent = 0,int iSelect=0);
    int getSelect(void){return m_iSelect;};
    void setSelect(int iSelect);

public slots:
    void UListSelect(int iSelect);
    void UListScroll(void);

private:
//    CReturnButton ReturnBtn;
	SettingScreen *m_pParentDlg;

protected:
    int      	    m_iSelect;
    QLabel          *m_pLabelTitle;
    QPixmap         *m_pImageBackground;
    QPixmap         *m_pImageListItem1[3];
    QPixmap         *m_pImageListItem2[3];
    QPixmap	        *m_pImageListStatus[3];
    RtSettingList   *m_pListBox;
    void paintEvent(QPaintEvent *event);

};

#endif // UNITSSCREEN_H
