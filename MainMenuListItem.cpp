#include "MainMenuListItem.h"
#include "QPainter"
#include "colors.h"
#define ITEM_WIDTH	250
#define ITEM_HEIGHT	57
#define FONT_SIZE	18

CMainMenuListItem::CMainMenuListItem(QWidget *parent)
: RtPushButton(parent)
{
	this->resize(ITEM_WIDTH,ITEM_HEIGHT);	
	this->m_RectText = QRect(60,0,170,55);
	this->m_AlignFlag = Qt::AlignVCenter|Qt::AlignLeft;
}

void CMainMenuListItem::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
    //Draw text information
	painter.setRenderHint(QPainter::Antialiasing);
	if(!this->isDown())	//normal mode
	{
		//Set Text Font
		QFont font(tr("Tahoma"), FONT_SIZE);
		font.setStyleStrategy(QFont::PreferDefault);
		painter.setFont(font);
		//Set Text Color
		painter.setPen(Qt::white);
		painter.drawText(m_RectText, m_AlignFlag, text());
	}
	else	//pressed mode
	{
		//Paint roundedRect for item focused
		painter.setBrush(COLOR_FOCUS_ON);
		painter.setPen(COLOR_FOCUS_ON);
		painter.drawRoundedRect(0, 0, ITEM_WIDTH, ITEM_HEIGHT, 5, 5);
		//Set Text Font
		QFont font(tr("Tahoma"), FONT_SIZE);
		font.setStyleStrategy(QFont::PreferDefault);
		painter.setFont(font);
		//Set Text Color
		painter.setPen(Qt::black);
		painter.drawText(m_RectText, m_AlignFlag, text());	
	}
	//Draw icon
	painter.drawPixmap(3, 3, *m_pimgUp);
}