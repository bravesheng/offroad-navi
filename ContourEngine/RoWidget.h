#ifndef __RoWidget_h__
#define __RoWidget_h__

#include "QWidget.h"
#include "QPainter.h"
#include "TAContourGrids.h"

class CRoWidget : public QWidget {
	Q_OBJECT
public: 
	CRoWidget(QWidget* parent = NULL);

	void Draw ( double fLon, double fLat );

public slots:
	void ZoomIn (){ _grids.ScaleDown ( &_Painter ); update (); }
	void ZoomOut (){ _grids.ScaleUp ( &_Painter ); update (); }
	void RotateUp (){ _grids.Rotate ( &_Painter, 10 ); update (); }
	void RotateDown (){ _grids.Rotate ( &_Painter, -10 ); update (); }
		
protected:
    void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent ( QMouseEvent * event );
	virtual void mouseReleaseEvent ( QMouseEvent * event );
	virtual void mouseMoveEvent ( QMouseEvent * event );

	QImage _Image;
	QPainter _Painter;
	QBrush _bg;
	CTAContourGrids _grids;
};

#endif