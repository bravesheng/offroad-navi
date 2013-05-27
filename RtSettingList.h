#ifndef RTSETTINGLIST_H
#define RTSETTINGLIST_H

#include <QWidget>
#include "RtSettingButton.h"
#define __MAX_SETTING_ITEMS__  50
#define __AutoScroll_INTERVAL__  3

class RtSettingList : public QWidget
{
    Q_OBJECT

public:
    RtSettingList(QWidget *parent=NULL,int iX=0, int iY=0, int iWidth=0, int iHeight=0,bool bAutoScroll=false);
	RtSettingButton* AddButton(RtSettingButton* pButtonNew);
	RtSettingButton* GetButton(int iIndex);
    void SetImages1(QPixmap *pimgUp = NULL, QPixmap *pimgDown = NULL,
                   QPixmap *pimgSelect = NULL);
    void SetImages2(QPixmap *pimgUp = NULL, QPixmap *pimgDown = NULL,
                   QPixmap *pimgSelect = NULL);
    bool SetIconB(int iIndex,QPixmap *pIconB);
	void SetIconB_OffsetX(int iIndex,int iOffsetX);

    RtSettingButton* AddButton(QPixmap *pIconA,QString Text1,QString Text2,QPixmap *pIconB);
    bool DeleteButton(int iSelect);

signals:
    void ButtonSelect(int iSelect);
    void ButtonScroll();
    void ButtonOnOff(int iSelect,int iOnOff);//iOnOff - 0->off, 1->on .

public slots:
    void MousePress(int iPressY);
    void ScrollList(int iDiffY);
    void MouseRelease();
    void AutoScroll();
    void ResetLastScroll();
    void ListButtonClick(int iSelect);
	void MouseMoveDffX(int iListIndex,int iDiffX);

protected:
    RtSettingButton *m_pButtonList[__MAX_SETTING_ITEMS__];
	bool		   m_bAutoScroll;
    int            m_iItems;
    int            m_iItemSelect;// -1 means "No Select", 0~m_iItems-1.					// -1 means "No Select", 0~m_iItems-1.
    int            m_iBoxHeight;
    int            m_iPressY;
    int            m_iLastScroll;

    QPixmap        *m_pimg1Up;
    QPixmap        *m_pimg1Down;
    QPixmap        *m_pimg1Select;
    QPixmap        *m_pimg2Up;
    QPixmap        *m_pimg2Down;
    QPixmap        *m_pimg2Select;

    QTimer		   *m_pQTimerScroll;				// After xxx ms, scroll once
    QTimer         *m_pQTimerReset;				// If not scroll xxx ms, stop auto auto function

};

#endif // RtSettingList_H
