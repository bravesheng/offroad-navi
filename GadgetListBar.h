#ifndef GADGET_LIST_BAR_H
#define GADGET_LIST_BAR_H

#include "RtListBox.h"
#include "Gadget.h"
#include <QWidget>

class QTimeLine;
class CGadgetListItem;
class CGadgetsDialog;

class CGadgetListBar : public QWidget
{
    Q_OBJECT
public:
    CGadgetListBar(CGadgetsDialog *parent);
	~CGadgetListBar();
	bool IfTabArea(int screen_x, int screen_y);
protected:
    void paintEvent(QPaintEvent* event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
    QPixmap* pImgBackground;
	QTimeLine *m_timeLine;
	CGadgetsDialog* m_pGadgetsDlg;
	RtListBox m_ListBox;
	CGadgetListItem* m_pListBoxItem[GADGET_NUMS];
private slots:
    void setBarPosition(int position);
	void SlideFinished(void);
	void OpenBar(void);
	void CloseBar(void);
	void QuickCloseBar(void);
	//void AddGadget(void);
	void AddGadget(int GadgetIndex);

signals:
	void MouseRelease(QMouseEvent *event);
};

#endif//GADGET_LIST_BAR_H
