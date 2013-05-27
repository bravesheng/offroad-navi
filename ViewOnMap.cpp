#include "ViewOnMap.h"
#include "ImagePool.h"
#include "RtPushButton.h"

CViewOnMap::CViewOnMap(QWidget *parent)
: QWidget(parent),
m_BtnScaleUp(this),
m_BtnScaleDown(this),
m_ContouWidget(this)
{
	setGeometry(0, 0, 320, 240);
	m_ContouWidget.setGeometry(0, 0, 320, 240);
	m_BtnScaleUp.setGeometry ( 10, 50, 30, 30 );
	m_BtnScaleUp.setText ( "+" );
	m_BtnScaleDown.setGeometry ( 10, 90, 30, 30 );
	m_BtnScaleDown.setText ( "-" );
	m_ContouWidget.lower();

	connect(&m_BtnScaleUp, SIGNAL(clicked()), &m_ContouWidget,SLOT(ZoomIn()));
	connect(&m_BtnScaleDown, SIGNAL(clicked()), &m_ContouWidget,SLOT(ZoomOut()));
	
// Load quit button
	QRect   rectButtonQuit        (   320-75,   240-75,  75,  75);

    RtPushButton *pPushButtonQuit = new RtPushButton(this);
    pPushButtonQuit->setGeometry( rectButtonQuit );
    pPushButtonQuit->SetImages(GetImg(IMG_ICON_EXIT), GetImg(IMG_ICON_EXIT));
    connect(pPushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));

}

CViewOnMap::~CViewOnMap(void)
{
}
