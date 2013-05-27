#include "stdafx.h"
#include "RoWidget.h"

#define SCR_WIDTH 320
#define SCR_HEIGHT 240

CRoWidget :: CRoWidget (QWidget* parent) :
	_Image(SCR_WIDTH,SCR_HEIGHT,QImage::Format_ARGB32_Premultiplied ),
	_Painter(&_Image), _bg(QColor ( 137, 243, 140 )), QWidget(parent)
{ 
	_Painter.setBackground ( _bg );
	_Painter.setRenderHint(QPainter::Antialiasing);

	CTAContourGrids::SetWorkDir ( _T("\\MyFlashDisk\\contour\\" ));
    _grids.Init ( 320, 240 );
    _grids.SetAngle ( 30 );
    Draw ( 121.3797, 25.049447 );
	//_grids.ScaleUp ( &_Painter, 2 );
}

#pragma warning(disable:4100)

void CRoWidget :: Draw ( double fLon, double fLat )
{
	_grids.DrawXY ( &_Painter, fLon, fLat );
}

int iOffsetX = 0;
int iOffsetY = 0;

void CRoWidget :: paintEvent(QPaintEvent *)
{
	QPen m_Pen(Qt::black, 1, Qt::DashLine );

	QPainter painter;

	painter.begin (this);

	painter.drawImage ( iOffsetX, iOffsetY, _Image );

	painter.setPen ( m_Pen );
	painter.setRenderHint(QPainter::Antialiasing, false);
	painter.drawLine ( 0, SCR_HEIGHT/2, SCR_WIDTH, SCR_HEIGHT/2 );
	painter.drawLine ( SCR_WIDTH/2, 0, SCR_WIDTH/2, SCR_HEIGHT );

	painter.end ();
}

int iPressX, iPressY;
bool bIsPressed = false;
void CRoWidget :: mousePressEvent ( QMouseEvent * event )
{
	iPressX = event->x ();
	iPressY = event->y ();

	bIsPressed = true;
}

void CRoWidget :: mouseReleaseEvent ( QMouseEvent * event )
{
	bIsPressed = false;

	if (( abs ( event->x () - iPressX ) < 3 ) && 
		( abs ( event->y () - iPressY ) < 3 ))
	{
		_grids.MoveTo ( &_Painter, event->x (), event->y () );
	}
	else
	{
		_grids.MoveTo ( &_Painter, SCR_WIDTH/2 - iOffsetX, SCR_HEIGHT/2 - iOffsetY );
		iOffsetX = iOffsetY = 0;
	}

	update ();
}

void CRoWidget :: mouseMoveEvent ( QMouseEvent * event )
{
	if ( bIsPressed )
	{
		iOffsetX = event->x () - iPressX;
		iOffsetY = event->y () - iPressY;

		update ();
	}
}
