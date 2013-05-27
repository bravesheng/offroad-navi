#ifndef __RoMemDC_h__
#define __RoMemDC_h__

#include "QPainter.h"

class CRoMemDC : public QPainter {
//class CRoMemDC {
public:
        CRoMemDC ( int iWidth, int iHeight, const QColor & color ) :
              _Image ( iWidth, iHeight, QImage::Format_ARGB32_Premultiplied ),
              _bg( color )
          {
                begin ( &_Image ),
                setBackground ( _bg );
                //setRenderHint(QPainter::Antialiasing);
	  }
          ~CRoMemDC (){ end (); }

          void Show ( QPainter& painter, int iX, int iY ){ painter.drawImage ( iX, iY, _Image ); }
          void Clear (){ eraseRect ( QRect ( 0, 0, _Image.width (), _Image.height ())); }
	  QImage& Image (){ return _Image; }

          void SavedDC (){ _saveT = worldTransform (); }
          void RestoreDC (){ setWorldTransform ( _saveT ); }

protected:
        QTransform _saveT;
	QImage _Image;
	QBrush _bg;
};

#endif
