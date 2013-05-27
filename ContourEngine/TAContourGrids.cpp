#include "stdafx.h"
#include "TAContourGrids.h"
#include "RoMapFileBase.h"

int CTAContourGrids::m_iScales [ ScaleLevel ] =
{
	5, 6, 7, 8, 9, 11, 13, 16, 20, 25
};

int CTAContourGrids::m_iDividers [ ScaleLevel ] =
{
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

void CTAContourGrids :: DrawXY ( QPainter *painter, int iX, int iY )
{
	painter->eraseRect ( QRect ( 0, 0, Width (), Height ()));

    int iWidth = Width () * _iScale / _iDivider;
    int iHeight = Height () * _iScale / _iDivider;

    int iXMin = iX - iWidth / 2;
    int iYMin = iY - iHeight / 2;
    int iXMax = iXMin + iWidth;
    int iYMax = iYMin + iHeight;

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
                    _grid.Draw ( painter, iOffsetX * _iDivider / _iScale, iOffsetY * _iDivider / _iScale, _iDivider, _iScale );
                else
                    _grid.DrawClip ( painter, iOffsetX * _iDivider / _iScale, iOffsetY * _iDivider / _iScale, _iDivider, _iScale );
            }

            iX0 += CRoMapFileBase::GridWidth ();
            iOffsetX += CRoMapFileBase::GridWidth ();
        }

        iX0 = iX0Saved;
        iOffsetX = iOffsetXSaved;

        iY0 += CRoMapFileBase::GridWidth ();
        iOffsetY -= CRoMapFileBase::GridWidth ();
    }

    _iX = iX;
    _iY = iY;
}

void CTAContourGrids :: DrawXYR ( QPainter *painter, int iX, int iY )
{
	painter->eraseRect ( QRect ( 0, 0, Width (), Height ()));

    int iWidth = Width () * _iScale / _iDivider;
    int iHeight = Height () * _iScale / _iDivider;

    _rotate.GetWidth ( iWidth, iHeight );

    int iXMin = iX - iWidth / 2;
    int iYMin = iY - iHeight / 2;
    int iXMax = iXMin + iWidth;
    int iYMax = iYMin + iHeight;

    int iX0 = iXMin;
    int iY0 = iYMin;

    _iX = iX;
    _iY = iY;
    _rotate.SetXY ( iX, iY );

    while ( iY0 < ( iYMax +  + CRoMapFileBase::GridWidth () ))
    {
        while ( iX0 <= ( iXMax  + CRoMapFileBase::GridWidth ()))
        {
            if ( _grid.Load ( iX0, iY0 ))
            {
                if (( _grid.XMin () >= iXMin ) && ( _grid.XMax () <= iXMax ) &&
                    ( _grid.YMin () >= iYMin ) && ( _grid.YMax () <= iYMax ))
                    _grid.Draw ( painter, _iScale, _iDivider, _rotate );
                else
                    _grid.DrawClip ( painter, _iScale, _iDivider, _rotate );

                //return;
            }

            iX0 += CRoMapFileBase::GridWidth ();
        }

        //return;

        iX0 = iXMin;
        iY0 += CRoMapFileBase::GridWidth ();
    }
}


void CTAContourGrids :: MoveTo ( QPainter *painter, int iX, int iY )
{
    _rotate.ReverseRotateXY ( iX, iY, _iScale, _iDivider );
    DrawXYR ( painter, iX, iY );
}
