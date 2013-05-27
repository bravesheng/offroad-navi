#ifndef MAIN_MENU_LIST_ITEM_H
#define MAIN_MENU_LIST_ITEM_H

#include "RtPushButton.h"

class CMainMenuListItem : public RtPushButton
{
public:
	CMainMenuListItem(QWidget *parent);
protected:
    void paintEvent(QPaintEvent* event);

};

#endif//MAIN_MENU_LIST_ITEM_H