#include "stdafx.h"
#include "RoWidget_2.h"

#define SCR_WIDTH 320
#define SCR_HEIGHT 240

CTAContourGrids CRoWidget::m_grids;
bool CRoWidget::m_bIsGridsInited = false;

CRoWidget :: CRoWidget ( QWidget *parent ) : QWidget (parent),
	_Image(SCR_WIDTH,SCR_HEIGHT,QImage::Format_ARGB32_Premultiplied ),
	_Painter(&_Image), _bg(QColor ( 137, 243, 140 ))
{ 
	_Painter.setBackground ( _bg );
    //_Painter.setRenderHint(QPainter::Antialiasing);
    if ( !m_bIsGridsInited )
    {
#ifdef _WIN32_WCE
        CTAContourGrids::SetWorkDir ( _T("\\MyFlashDisk\\contour\\" ));
        CRoGeoImage::SetWorkDir ( _T("\\MyFlashDisk\\contour\\png\\" ));
#else
        CTAContourGrids::SetWorkDir ( _T("E:\\contour\\danniel\\shapefile\\" ));
        CRoGeoImage::SetWorkDir ( _T("E:\\contour\\png\\" ));
#endif
        m_grids.Init ( 456, 456 );
        m_bIsGridsInited = true;
    }

#if 1
    //m_grids.SetAngle ( 30 );
    //Draw ( 121.3797, 25.049447 );
    Draw ( 121.33875, 25.00149 );
#endif
    //m_grids.ScaleUp ( &_Painter, 2 );
}

#pragma warning(disable:4100)

int iOffsetX = 0;
int iOffsetY = 0;

void CRoWidget :: paintEvent(QPaintEvent *)
{
	QPen m_Pen(Qt::black, 1, Qt::DashLine );

	QPainter painter;

	painter.begin (this);
#if 0
        QPixmap bmp;
         if ( bmp.load ( "E:\\contour\\png\\Grid1642.png" ))
            //_dc.drawPixmap ( iOffsetX, iOffsetY, iStep, iStep, bmp, 0, 0, 100, 100 );
            painter.drawPixmap ( -1718, -1192, 3507, 3507, bmp, 0, 0, 100, 100 );
#else
        //painter.drawImage ( iOffsetX, iOffsetY, _Image );
         m_grids.Show ( painter, iOffsetX, iOffsetY );
#endif
	painter.setPen ( m_Pen );
    //painter.setRenderHint(QPainter::Antialiasing, false);
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
                m_grids.MoveTo ( event->x (), event->y () );
	}
	else
	{
                m_grids.MoveTo ( SCR_WIDTH/2 - iOffsetX, SCR_HEIGHT/2 - iOffsetY );
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
