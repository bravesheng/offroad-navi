#ifndef __RoWidget_2_h__
#define __RoWidget_2_h__

#include "QWidget.h"
#include "QPainter.h"
#include "TAContourGrids_2.h"
#include "..\Track.h"

class CRoWidget : public QWidget {
	Q_OBJECT
public:
    CRoWidget ( QWidget *widget = NULL );

    void Draw ( double fLon, double fLat ){ m_grids.DrawXY ( fLon, fLat ); }
    void DrawTrackLog ( CTrack& trackLog ){ if ( m_grids.DrawTrackLog ( trackLog )) update (); }

public slots:
        void ZoomIn (){ m_grids.ScaleDown (); update (); }
        void ZoomOut (){ m_grids.ScaleUp (); update (); }
        void RotateUp (){ m_grids.Rotate ( 10 ); update (); }
        void RotateDown (){ m_grids.Rotate ( -10 ); update (); }
		
protected:
    void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent ( QMouseEvent * event );
	virtual void mouseReleaseEvent ( QMouseEvent * event );
	virtual void mouseMoveEvent ( QMouseEvent * event );

	QImage _Image;
	QPainter _Painter;
	QBrush _bg;

    static CTAContourGrids m_grids;
    static bool m_bIsGridsInited;
};

#endif
