#include "Buttons.h"
#include "ImagePool.h"
#include "QPainter"

CRtAbstractButton::CRtAbstractButton(QWidget* pParent):QAbstractButton(pParent)
{

}

void CRtAbstractButton::paintEvent(QPaintEvent* event)
{
    //Create QPainter
    QPainter painter(this);
    //Paint background
	if(this->isDown())
	{
		if(pDownImage)
		{
			painter.drawPixmap(0, 0, *pDownImage);
		}
	}
	else
	{
		if(pNormalImage)
		{
			painter.drawPixmap(0, 0, *pNormalImage);
		}
	}

}

CReturnButton::CReturnButton(QWidget* pParent):CRtAbstractButton(pParent)
{
	pNormalImage = GetImg(IMG_BTN_RETURN);
	pDownImage = GetImg(IMG_BTN_RETURN_DOWN);
	setGeometry(0,0,40,40);											//set position in parent window
	connect(this, SIGNAL(clicked()), pParent, SLOT(close()));		//set click action
}
