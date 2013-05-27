#ifndef RTLISTBOX_H
#define RTLISTBOX_H

#include <QWidget>
#include "RtPushButton.h"
/*
#include <QThread>

class ListThread : public QThread
{
    Q_OBJECT
public:
	void run(){
		sleep(200);
		emit UpdateListbox();
	};

signals:
    void UpdateListbox();
};
*/
#define __MAX_ITEMS__ 2048
#define __AutoScroll_INTERVAL__ 3

class RtListBox : public QWidget
{
    Q_OBJECT

public:
    RtListBox(QWidget *parent,int iX, int iY, int iWidth, int iHeight);
    RtPushButton* AddButton(RtPushButton* pButtonNew);
    RtPushButton* GetButton(int iIndex);
    bool DeleteButton(int iSelect);
	void DeleteAllButton(void);
    int count () const;
signals:
    void ButtonSelect(int iSelect);
    void ButtonScroll();

public slots:
    void MousePress(int iPressY);
    void ScrollList(int iDiffY);
    void MouseRelease();
    void AutoScroll();
    void ResetLastScroll();
    void ButtonClick(int iSelect);

protected:
    RtPushButton *m_pButtonList[__MAX_ITEMS__];
    int            m_iItems;
    int            m_iItemSelect;// -1 means "No Select", 0~m_iItems-1.					// -1 means "No Select", 0~m_iItems-1.
    int            m_iBoxHeight;
    int            m_iPressY;
    int            m_iLastScroll;
	int			   m_HeightUsed;

    QTimer       *m_pQTimerScroll;				// After xxx ms, scroll once
    QTimer       *m_pQTimerReset;				// If not scroll xxx ms, stop auto auto function

};

#endif // RtListBox_H
