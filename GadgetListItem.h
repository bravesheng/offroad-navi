#ifndef GADGET_LIST_ITEM_H
#define GADGET_LIST_ITEM_H

#include "RtPushButton.h"

class CGadgetListItem : public RtPushButton
{
public:
	CGadgetListItem(QWidget *parent, const QString & text);
protected:
    void paintEvent(QPaintEvent* event);

};

#endif//GADGET_LIST_ITEM_H