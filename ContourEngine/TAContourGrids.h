#ifndef __TAContourGrids_h__
#define __TAContourGrids_h__

#include "TAContourGrid.h"
#include "RoCoord.h"
#include "RoRotate.h"

class CTAContourGrids {
public:
    CTAContourGrids () : _iScaleLevel (0)
	{
        CRoMapFileBase::SetGridWidth ( 2500 );
        CRoMapFileBase::SetMeshWidth ( 50000 );
		_iScale = m_iScales [ 0 ];
		_iDivider = m_iDividers [ 0 ];
	}

    static void SetWorkDir ( LPCTSTR sWorkDir ){ CTAContourGrid::SetWorkDir ( sWorkDir ); }

    void Init ( int iWidth, int iHeight ){ _iWidth = iWidth; _iHeight = iHeight; _rotate.SetOffset ( iWidth / 2, iHeight / 2 ); }
    void DrawXY ( QPainter *painter, double fLon, double fLat ){ DrawXYR (painter, ( int )( fLon * WGS84IntScale ), ( int )( fLat * WGS84IntScale )); }
    void MoveTo ( QPainter *painter, int iX, int iY );

    int Width (){ return _iWidth; }
    int Height (){ return _iHeight; }
    void SetScale ( QPainter *painter, int iScaleLevel )
	{
		if (( iScaleLevel >= 0 ) && ( iScaleLevel < ScaleLevel ))
		{
			_iScaleLevel = iScaleLevel;
			SetScale ( painter, m_iScales [ _iScaleLevel ], m_iDividers [ _iScaleLevel ]);
		}
	}

    void ScaleUp ( QPainter *painter, int iScaleUp = 1 )
	{
		int iScaleLevel = _iScaleLevel + iScaleUp;
		if ( iScaleLevel >= ScaleLevel )
			iScaleLevel = ScaleLevel - 1;

		if ( _iScaleLevel != iScaleLevel )
		{
			_iScaleLevel = iScaleLevel;
			SetScale ( painter, m_iScales [ _iScaleLevel ], m_iDividers [ _iScaleLevel ]);
		}
	}
    void ScaleDown ( QPainter *painter, int iScaleDown = 1 )
    {
		int iScaleLevel = _iScaleLevel - iScaleDown;
		if ( iScaleLevel < 0 )
			iScaleLevel = 0;

		if ( _iScaleLevel != iScaleLevel )
		{
			_iScaleLevel = iScaleLevel;
			SetScale ( painter, m_iScales [ _iScaleLevel ], m_iDividers [ _iScaleLevel ]);
		}
    }

    void SetAngle ( int iAngle ){ _rotate.SetAngle ( iAngle ); }
	void Rotate ( QPainter *painter, int iIncAngle ){ _rotate.IncAngle ( iIncAngle ); DrawXYR ( painter, _iX, _iY ); }

protected:
	enum
	{
		ScaleLevel = 10
	};

    void SetScale ( QPainter *painter, int iScale, int iDivider ){ _iScale = iScale; _iDivider = iDivider; DrawXYR ( painter, _iX, _iY ); }
    void DrawXY ( QPainter *painter, int iX, int iY );
    void DrawXYR ( QPainter *painter, int iX, int iY );

    CTAContourGrid _grid;
    CRoRotate _rotate;

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
