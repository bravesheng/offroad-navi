#include <QPainter>
#include <QPaintEvent>
#include "RtWaypointButton.h"
#include "RtGlobalDefine.h"

RtWaypointButton::RtWaypointButton(QWidget *parent, int iListIndex)
:RtPushButton(parent)
{
    m_strText1 = tr("");
    m_strText2 = tr("");

    m_pImgDirect = NULL;
    m_pImgDirect = new RtImage(this);
    m_pImgDirect->setAngle(0);

}

RtWaypointButton::~RtWaypointButton()
{
    if(m_pImgDirect){
        delete m_pImgDirect;
        m_pImgDirect = NULL;
    }
}

void RtWaypointButton::paintCustomEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);

    QRect SrcRect = rect();

    //Set Text Font
    QFont font(g_strTitleFontFamily, g_iListFontPointSize);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);

    //Set Text Color
    painter.setPen(QColor( __TitleTextColor__ ));

    int iExtralWidth = 0;

    if(m_pImgDirect)
    {
        m_pImgDirect->update();
    }

    //Draw Text2
    if(!m_strText2.isEmpty())
    {
        QRect DistanceRect = QRect(__TEXT2_OFFSETX__,SrcRect.y(),__TEXT2_WIDTH__,SrcRect.height());
        painter.drawText(DistanceRect,Qt::AlignRight|Qt::AlignVCenter,m_strText2);
    }
    else
        iExtralWidth += __TEXT2_WIDTH__;

    //Draw Text1
    if(!m_strText1.isEmpty())
    {
        QRect TextRect = QRect(__TEXT1_OFFSETX__,SrcRect.y(),(__TEXT1_WIDTH__+iExtralWidth),SrcRect.height());
        painter.drawText(TextRect,Qt::AlignLeft|Qt::AlignVCenter,m_strText1);
    }

    //Draw Icon1
    if(!m_pimgIconA->isNull())
		painter.drawPixmap((__TEXT1_OFFSETX__-m_pimgIconA->width())/2,(SrcRect.height()-m_pimgIconA->height())/2,*m_pimgIconA);

}

void RtWaypointButton::SetComponent(int iIconIdx,QPixmap *pSymbol,QString Text1,int iUnitType,double dDistance,QPixmap *pDirectIcon,double dAngle)
{
    m_iIconIdx = iIconIdx;
    m_pimgIconA = pSymbol;
    m_strText1  = Text1;
    m_pimgIconB = pDirectIcon;
    m_pImgDirect->setAngle(dAngle);

    setDistance(iUnitType,dDistance);

    m_pImgDirect->setImage(pDirectIcon);
    m_pImgDirect->setGeometry(__ICON2_OFFSETX__,(__WAYPOINT_HEIGHT__-m_pimgIconB->height())/2,m_pimgIconB->width(),m_pimgIconB->height());
}

void RtWaypointButton::setDirectAngle(qreal degrees )
{
    m_pImgDirect->setAngle(degrees);
    update();
}

void RtWaypointButton::setDistance(int iUnitType,double dDistance )
{
    QString strDist;

    if(((iUnitType == CGlobal::UNIT_KM)||(iUnitType == CGlobal::UNIT_MILE)) && (dDistance>=0.1))
	{
       if(dDistance> MAX_DISTANCE_SHOW)
             dDistance = MAX_DISTANCE_SHOW;

        if(dDistance>MID_DISTANCE_SHOW)
           strDist.sprintf("%3.0f",dDistance);
		else
           strDist.sprintf("%3.1f",dDistance);
    }else {

        if(dDistance>MAX_DISTANCE_SHOW)
            dDistance = MAX_DISTANCE_SHOW;

        strDist.sprintf("%3.0f",dDistance);
    }

    QString strUnit[] ={"M","YD","KM","MI"};

   m_strText2 = strDist + strUnit[iUnitType];
//   update();
}

void RtWaypointButton::setSymbol(int iIconIdx,QPixmap* pSymbol)
{
    m_iIconIdx = iIconIdx;
    m_pimgIconA = pSymbol;
//    update();
}

int RtWaypointButton::getSymbolIdx(void)
{
    return m_iIconIdx;
}

void RtWaypointButton::setName(QString &Name)
{
    m_strText1 = Name;
//   update();
}

QString RtWaypointButton::getName(void)
{
    return m_strText1;
}
