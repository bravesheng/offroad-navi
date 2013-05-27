#ifndef RTWAYPOINTBUTTON_H
#define RTWAYPOINTBUTTON_H

#include "RtPushButton.h"
#include "RtImage.h"
#include "Global.h"

#define __ICON1_OFFSETX__   8
#define __ICON1_WIDTH__     29
#define __ICON2_OFFSETX__   220
#define __ICON2_WIDTH__     25

#define __TEXT1_OFFSETX__   40
#define __TEXT1_WIDTH__     120
#define __TEXT2_OFFSETX__   165
#define __TEXT2_WIDTH__     55

#define __WAYPOINT_HEIGHT__     42

class RtWaypointButton : public RtPushButton
{
public:
    RtWaypointButton(QWidget *parent = NULL, int iListIndex = -1);
    ~RtWaypointButton();
    void SetComponent(int iIconIdx = 0,QPixmap *pSymbol=NULL,QString Text1="",int iUnitType=0,double dDistance=999.0,QPixmap *pDirectIcon=NULL,double dAngle=0.0);
    void setSymbol(int iIconIdx = 0,QPixmap* pSymbol = NULL);
    void setName(QString &Name);
    QString getName(void);
    int getSymbolIdx(void);
    void setDirectAngle(qreal degrees );
    void setDistance(int iUnitType,double dDistance );

private:
    void paintCustomEvent(QPaintEvent *event);

protected:
    int            m_iIconIdx;
    RtImage        *m_pImgDirect;
    QPixmap        *m_pimgIconA;
    QPixmap        *m_pimgIconB;
    QString        m_strText1;
    QString        m_strText2;
};

#endif // RtWaypointButton_H
