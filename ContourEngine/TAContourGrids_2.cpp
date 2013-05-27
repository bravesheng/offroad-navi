#include "stdafx.h"
#include "TAContourGrids_2.h"
#include "RoMapFileBase.h"

int CTAContourGrids::m_iScales [ ScaleLevel ] =
{
    5, 6, 7, 9, 11, 13, 16, 20, 25, 50, 100, 200, 400, 800, 1500
};

int CTAContourGrids::m_iDividers [ ScaleLevel ] =
{
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

void CTAContourGrids :: DrawXY ( int iX, int iY )
{
    if ( _iScaleLevel <= 9 )
        _Image.setRenderHint(QPainter::SmoothPixmapTransform);
    else
        _Image.setRenderHint(QPainter::SmoothPixmapTransform, false );

    _Image.DrawXY ( iX, iY, _iScale, _iDivider );

    CTAContourGrid::ClearAltitudeMs ();
    int iWidth = Width () * _iScale / _iDivider;
    int iHeight = Height () * _iScale / _iDivider;

    int iXMin = iX - iWidth / 2;
    int iYMin = iY - iHeight / 2;
    int iXMax = iXMin + iWidth;
    int iYMax = iYMin + iHeight;

    if ( _iScaleLevel <= 9 )
    {
        if ( _iScaleLevel >= 9 )
            CTAContourGrid::SetAltitudeMode ( 100 );
        else if ( _iScaleLevel > 7 )
            CTAContourGrid::SetAltitudeMode ( 40 );
        else if ( _iScaleLevel > 4 )
            CTAContourGrid::SetAltitudeMode ( 20 );
        else
            CTAContourGrid::SetAltitudeMode ( 10 );

        if ( _iScaleLevel >= 9 )
            CTAContourGrid::SetAltitudeColor ( 150 );
        else if ( _iScaleLevel > 7 )
            CTAContourGrid::SetAltitudeColor ( 100 );
        else
            CTAContourGrid::SetAltitudeColor ( 50 );

        int iOffsetX = -( iXMin % CRoMapFileBase::GridWidth ());
        int iOffsetXSaved = iOffsetX;
        int iOffsetY = iHeight + ( iYMin % CRoMapFileBase::GridWidth ()) - CRoMapFileBase::GridWidth ();
        int iX0 = iXMin + iOffsetX;
        int iX0Saved = iX0;
        int iY0 = iYMin - ( iYMin % CRoMapFileBase::GridWidth ());

        while ( iY0 < iYMax )
        {
            while ( iX0 <= iXMax )
            {
                if ( _grid.Load ( iX0, iY0 ))
                {
                    if (( _grid.XMin () >= iXMin ) && ( _grid.XMax () <= iXMax ) &&
                        ( _grid.YMin () >= iYMin ) && ( _grid.YMax () <= iYMax ))
                    {
                        _grid.Draw ( &_Image, iOffsetX * _iDivider / _iScale, iOffsetY * _iDivider / _iScale, _iDivider, _iScale );
                    }
                    else
                        _grid.DrawClip ( &_Image, iOffsetX * _iDivider / _iScale, iOffsetY * _iDivider / _iScale, _iDivider, _iScale );
                }

                iX0 += CRoMapFileBase::GridWidth ();
                iOffsetX += CRoMapFileBase::GridWidth ();
            }

            iX0 = iX0Saved;
            iOffsetX = iOffsetXSaved;

            iY0 += CRoMapFileBase::GridWidth ();
            iOffsetY -= CRoMapFileBase::GridWidth ();
        }
    }

    if ( _ptLogs.Size ())
    {
        _Image.setPen(QColor(255,0,0));

        int iLogX0 = ( _ptLogs [ 0 ].x - iXMin ) * _iDivider / _iScale;
        int iLogY0 = Height () - ( _ptLogs [ 0 ].y - iYMin ) * _iDivider / _iScale;

        for ( int i1 = 1; i1 < _ptLogs.Size (); i1++ )
        {
            int iLogX1 = ( _ptLogs [ i1 ].x - iXMin ) * _iDivider / _iScale;
            int iLogY1 = Height () - ( _ptLogs [ i1 ].y - iYMin ) * _iDivider / _iScale;

            _Image.drawLine( iLogX0, iLogY0, iLogX1, iLogY1 );

            iLogX0 = iLogX1;
            iLogY0 = iLogY1;
        }

        _Image.setPen(QColor(0,0,0));
    }

    CTAContourGrid::DrawAltitude ( _Image );

    _iX = iX;
    _iY = iY;

    _rotate.SetXY( _iX, _iY );

    _Screen.RestoreDC();
    _Screen.Clear();
    SetRotateParam ();

    _Image.Show ( _Screen, 0, 0 );
}

void CTAContourGrids :: MoveTo ( int iX, int iY )
{
#if 1
    _rotate.ReverseRotateXY ( iX, iY, _iScale, _iDivider );
#else
    iX = _iX + ( iX - 160 ) * _iScale / _iDivider;
    iY = _iY + ( 120 - iY ) * _iScale / _iDivider;
#endif
    DrawXY ( iX, iY );
}

bool CTAContourGrids :: DrawTrackLog ( CTrack& track )
{
	int iCount = track.count();
    if ( iCount == 0 )
    {
        if ( _ptLogs.Size())
        {
            _ptLogs.Empty ();
            DrawXY ();
            return true;
        }

        return false;
    }

    _ptLogs.Alloc( iCount );
    int iMinX = 122 * WGS84IntScale;
    int iMinY = 26 * WGS84IntScale;
    int iMaxX = 0;
    int iMaxY = 0;
    int iX, iY;
    int iLastX = 0;
    int iLastY = 0;
    int iIdx = 0;

    int i1;
    for ( i1 = 0; i1 < iCount; i1++ )
    {
		CTrkPt* pt = track.TrkPt( i1 );
        //qDebug ( "%f,%f", pt.Lat(), pt.Long());

		iX = pt->lon * WGS84IntScale;
		iY = pt->lat * WGS84IntScale;

        if (( iX != iLastX ) || ( iY != iLastY ))
        {
            iLastX = _ptLogs [ iIdx ].x = iX;
            iLastY = _ptLogs [ iIdx ].y = iY;
            iIdx++;
            if ( iX > iMaxX )
                iMaxX = iX;
            if ( iY > iMaxY )
                iMaxY = iY;
            if ( iX < iMinX )
                iMinX = iX;
            if ( iY < iMinY )
                iMinY = iY;
        }
    }

    _ptLogs.AdjustSize ( iIdx );

    iX = ( iMinX + iMaxX ) / 2;
    iY = ( iMinY + iMaxY ) / 2;
    int iWidth = iMaxX - iMinX;
    int iHeight = iMaxY - iMinY;

    for ( i1 = 0; i1 < ScaleLevel; i1++ )
    {
        if (( 320 * m_iScales [ i1 ] / m_iDividers [ i1 ] >= iWidth ) &&
            ( 240 * m_iScales [ i1 ] / m_iDividers [ i1 ] >= iHeight ))
        {
            SetAngle ( 0 );
            SetScale ( i1 );
            DrawXY ( iX, iY );

            return true;
        }
    }

    return false;
}
