#ifndef RTTRACKBUTTON_H
#define RTTRACKBUTTON_H

#include "RtPushButton.h"

class RtTrackButton : public RtPushButton
{
public:
    RtTrackButton(QWidget *parent = NULL);
private:
    void paintCustomEvent(QPaintEvent *event);
};

#endif // RtTrackButton_H
