#ifndef __TAContourGrids_2_h__
#define __TAContourGrids_2_h__

#include "TAContourGrid_2.h"
#include "RoCoord.h"
#include "RoRotate.h"
#include "RoGeoImage.h"
#include "Track.h"

class CTAContourGrids {
public:
    CTAContourGrids () : _iScaleLevel (0), _Screen ( 456, 456, QColor(255,255,255))
	{
        CRoMapFileBase::SetGridWidth ( 2500 );
        CRoMapFileBase::SetMeshWidth ( 50000 );
		_iScale = m_iScales [ 0 ];
		_iDivider = m_iDividers [ 0 ];
        _Screen.SavedDC();
        _Screen.setRenderHint(QPainter::SmoothPixmapTransform);
    }

    static void SetWorkDir ( LPCTSTR sWorkDir ){ CTAContourGrid::SetWorkDir ( sWorkDir ); }

    void Init ( int iWidth, int iHeight ){ _iWidth = iWidth; _iHeight = iHeight; _rotate.SetOffset ( 320 / 2, 240 / 2 );  }
    void DrawXY ( double fLon, double fLat ){ DrawXY (( int )( fLon * WGS84IntScale ), ( int )( fLat * WGS84IntScale )); }
    void MoveTo ( int iX, int iY );
    void Show ( QPainter& painter, int iX, int iY ){ _Screen.Show ( painter, iX + (320-Width())/2, iY + (240-Height())/2 ); }
    bool DrawTrackLog ( CTrack& trackLog );

    int Width (){ return _iWidth; }
    int Height (){ return _iHeight; }
    void SetScale ( int iScaleLevel )
    {
        if (( iScaleLevel >= 0 ) && ( iScaleLevel < ScaleLevel ))
        {
            _iScaleLevel = iScaleLevel;
            SetScale ( m_iScales [ _iScaleLevel ], m_iDividers [ _iScaleLevel ]);
        }
    }

    void ScaleUp ( int iScaleUp = 1 )
    {
        int iScaleLevel = _iScaleLevel + iScaleUp;
        if ( iScaleLevel >= ScaleLevel )
            iScaleLevel = ScaleLevel - 1;

        if ( _iScaleLevel != iScaleLevel )
        {
            _iScaleLevel = iScaleLevel;
            SetScale ( m_iScales [ _iScaleLevel ], m_iDividers [ _iScaleLevel ]);
        }
    }
    void ScaleDown ( int iScaleDown = 1 )
    {
        int iScaleLevel = _iScaleLevel - iScaleDown;
        if ( iScaleLevel < 0 )
            iScaleLevel = 0;

        if ( _iScaleLevel != iScaleLevel )
        {
            _iScaleLevel = iScaleLevel;
            SetScale ( m_iScales [ _iScaleLevel ], m_iDividers [ _iScaleLevel ]);
        }
    }

    void SetAngle ( int iAngle ){ _rotate.SetAngle ( iAngle ); }
    void Rotate ( int iIncAngle ){ _rotate.IncAngle ( iIncAngle ); DrawXY (); }

protected:
	enum
	{
        ScaleLevel = 15
	};

    void SetScale ( int iScale, int iDivider ){ _iScale = iScale; _iDivider = iDivider; DrawXY (); }
    void DrawXY ( int iX, int iY );
    void DrawXY (){ DrawXY ( _iX, _iY ); }
    int  RotateAngle (){ return _rotate.Angle (); }
    void SetRotateParam ()
    {
        _Screen.RestoreDC();
        _Screen.translate( Width ()/2, Height()/2 );
        _Screen.rotate ( RotateAngle ());
        //qDebug ( "%d", _rotate.Angle ());
        _Screen.translate( -Width()/2, -Height()/2 );
    }

    CTAContourGrid _grid;
    CRoRotate      _rotate;
    CRoGeoImage    _Image;
    CRoMemDC       _Screen;
    CRoBufferT<POINT> _ptLogs;

	int _iScaleLevel;
	int _iScale;
	int _iDivider;

    static int m_iScales [ ScaleLevel ];
    static int m_iDividers [ ScaleLevel ];
    int _iX;
    int _iY;
	int _iWidth;
	int _iHeight;
};

#endif
