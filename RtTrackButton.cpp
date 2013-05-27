#include <QPainter>
#include <QPaintEvent>
#include "RtTrackButton.h"
#include "RtGlobalDefine.h"
#include "TrackList.h"
#include "ImagePool.h"
extern CTrackList g_TrackList;

#define ICON_OFFSET_X   8
#define ICON_WIDTH     29
#define TEXT_OFFSET_X   40
#define TEXT_WIDTH     200

RtTrackButton::RtTrackButton(QWidget *parent)
:RtPushButton(parent)
{
	SetImages(GetImg(IMG_LIST_ITEM), GetImg(IMG_LIST_ITEM_DOWN), GetImg(IMG_LIST_ITEM_SELECTED1));
}

void RtTrackButton::paintCustomEvent(QPaintEvent*) ///*event*/
{
    QPainter painter(this);

    QRect SrcRect = rect();
	QPixmap* pIcon = GetImg(IMG_TRACK_ICON_C1);

    //Set text font
    QFont font(g_strTitleFontFamily, g_iListFontPointSize);
    font.setStyleStrategy(QFont::PreferAntialias);
    painter.setFont(font);

    //Set text color
    painter.setPen(QColor( __TitleTextColor__ ));

    //Draw track color icon
	//TODO: Need change icon when line color finished.
    painter.drawPixmap(ICON_OFFSET_X,((SrcRect.height() - pIcon->height()) / 2) , *pIcon);

    //Draw track name
	QRect TextRect = QRect(TEXT_OFFSET_X, SrcRect.y(), TEXT_WIDTH, SrcRect.height());
	if(m_iListIndex == 0)	//means current track
	{
		painter.drawText(TextRect,Qt::AlignLeft|Qt::AlignVCenter,g_TrackList.currentTrack()->name());
	}
	else if(!g_TrackList.track(m_iListIndex-1)->name().isEmpty())	//other saved tracks
    {
        painter.drawText(TextRect,Qt::AlignLeft|Qt::AlignVCenter,g_TrackList.track(m_iListIndex)->name());
    }
}
