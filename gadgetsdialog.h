#ifndef GADGETSDIALOG_H
#define GADGETSDIALOG_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include "Gadget.h"
#include "Buttons.h"
#include "GadgetListBar.h"

#define SLOT_NUMS_X 3
#define SLOT_NUMS_Y 2
#define SLOT_NUMS   (SLOT_NUMS_X * SLOT_NUMS_Y)
#define TRIP_COMPUTER_MODE	1
#define COMPASS_MODE		2
#define ELEVATION_PLOT		3

class QTimer;

class CGadgetsDialog : public QWidget
{
    Q_OBJECT

public:
    CGadgetsDialog(QWidget *parent = 0, int mode = COMPASS_MODE);
    ~CGadgetsDialog();
    bool DropGadget(CGadget* pGadget, int x, int y);
	bool InsertGadgetIntoSlot(CGadget* pGadget, CGadgetSlot* pTargetSlot);
	bool InsertGadgetIntoSlot(CGadget* pGadget);
    void PrepareSlotsCoordinate(void);
    CGadgetSlot* CoordinateToSlot(int x, int y);
	bool AddGadget(GADGET_UNIT GadgetType);
protected:
    void paintEvent(QPaintEvent* event);
private:
	CGadgetListBar m_GadgetListBar;

	QList<CGadget*> GadgetList;
    CGadgetSlot SlotArray[SLOT_NUMS_X][SLOT_NUMS_Y];
    CReturnButton ReturnBtn;
	int LayoutMode;
	QTimer m_UpdateTimer;
	int m_UpdateTimerTickCount;

	bool IfTrashCanArea(int x, int y);
	bool RemoveGadgetFromCurrentSlot(CGadget* pGadget);
	bool DeleteGadget(CGadget* pGadget);
private slots:
	void UpdateGadgets();
};

#endif // GADGETSDIALOG_H
