#include "GadgetListItem.h"
#include "QPainter"
#include "ImagePool.h"
#include "colors.h"
#include <QDebug>

#define ITEM_WIDTH	202
#define ITEM_HEIGHT	38
#define FONT_SIZE	14
#define UNDER_LINE_WIDTH	1
#define BORDER_WIDTH	3
#define BORDER_TOP	3

CGadgetListItem::CGadgetListItem(QWidget *parent, const QString & text)
: RtPushButton(parent)
{
	this->setText(text);
	this->resize(ITEM_WIDTH,ITEM_HEIGHT);	
}

void CGadgetListItem::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
    //Draw text information
	if(!this->isDown())	//normal mode
	{
		//Draw under line
		QPen pen_underline;
		pen_underline.setColor(Qt::gray);
		pen_underline.setWidth(UNDER_LINE_WIDTH);
		painter.setPen(pen_underline);
		QLine underline(BORDER_WIDTH,ITEM_HEIGHT-BORDER_WIDTH,ITEM_WIDTH-BORDER_WIDTH,ITEM_HEIGHT-BORDER_WIDTH);
		painter.drawLine(underline);
		//Set Text Font
		QFont font(tr("Tahoma"), FONT_SIZE);
		font.setStyleStrategy(QFont::PreferDefault);
		painter.setFont(font);
		//Set Text Color
		painter.setPen(Qt::white);
		painter.drawText(BORDER_WIDTH+BORDER_WIDTH, BORDER_TOP, ITEM_WIDTH, ITEM_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, text());
	}
	else	//pressed mode
	{
		//Paint roundedRect for item focused
		painter.setBrush(COLOR_FOCUS_ON);
		painter.setPen(COLOR_FOCUS_ON);
		painter.drawRoundedRect(BORDER_WIDTH, 0, ITEM_WIDTH - BORDER_WIDTH, ITEM_HEIGHT, 5, 5);
		//Set Text Font
		QFont font(tr("Tahoma"), FONT_SIZE);
		font.setStyleStrategy(QFont::PreferDefault);
		painter.setFont(font);
		//Set Text Color
		painter.setPen(Qt::black);
		painter.drawText(BORDER_WIDTH+BORDER_WIDTH, BORDER_TOP, ITEM_WIDTH, ITEM_HEIGHT, Qt::AlignLeft | Qt::AlignVCenter, text());	
	}
	qDebug() << "Gadget:" << this->text();
}