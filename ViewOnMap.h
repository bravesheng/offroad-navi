#ifndef VIEW_ON_MAP_H
#define VIEW_ON_MAP_H

#include <QWidget>
#include <QPushButton>
#include "ContourEngine\RoWidget_2.h"

class CViewOnMap : public QWidget
{
public:
	CViewOnMap(QWidget *parent = 0);
	~CViewOnMap(void);
	CRoWidget m_ContouWidget;

private:
	QPushButton m_BtnScaleUp;
	QPushButton m_BtnScaleDown;
//	CGadgetsDialog* m_pGadgetDialog;
};

#endif