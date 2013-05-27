#include "stdafx.h"
#include "TAContourGrid.h"
#include "RoMapFileBase.h"

CRoWorkDir CTAContourGrid::m_WorkDir;

void CTAContourGrid :: RestoreLinks ()
{
    short iLineSize;
    _file.Read ( &iLineSize, sizeof ( iLineSize ));
    //iReaded += sizeof ( short );
    //TRACE ( "Linesize=%d\r\n", iLineSize );

    ASSERT ( iLineSize != 0 );

    _iIdxes.Alloc ( iLineSize );
    CRoBufferT<short> iIdxes ( iLineSize );
    _file.Read ( iIdxes.Buf (), iIdxes.BufSize ());
    //iReaded += iIdxes.BufSize ();
    _iIdxes [ 0 ] = iIdxes [ 0 ];
    for ( int i1 = 1; i1 < iLineSize; i1++ )
        _iIdxes [ i1 ] = iIdxes [ i1 ] + _iIdxes [ i1 - 1 ];

    _iAltitudes.Alloc ( iLineSize );
    CRoBufferT<short> iAltitudes ( iLineSize );
    _file.Read ( iAltitudes.Buf (), iAltitudes.BufSize ());
    //iReaded += iAltitudes.BufSize ();
    for ( int i1 = 0; i1 < iLineSize; i1++ )
        _iAltitudes [ i1 ] = iAltitudes [ i1 ];

    int iPtSize = _iIdxes [ iLineSize - 1 ];

    _ptXYs.Alloc ( iPtSize );
    CRoBufferT<short> ptXYs ( iPtSize * 2 );
    _file.Read ( ptXYs.Buf (), ptXYs.BufSize ());
    //iReaded += ptXYs.BufSize ();

    for ( int i1 = 0; i1 < iPtSize; i1++ )
    {
        _ptXYs [ i1 ].x = ptXYs [ i1 * 2 ];
        _ptXYs [ i1 ].y = ptXYs [ i1 * 2 + 1 ];
    }
}

bool CTAContourGrid :: LoadGrid ( int iGridX, int iGridY )
{
    if (( iGridX < 0 ) || ( iGridX >= CRoMapFileBase::GridNum ()) ||
        ( iGridY < 0 ) || ( iGridY >= CRoMapFileBase::GridNum ()))
        return false;

    //TRACE ( "LoadGrid %d,%d\r\n", iGridX, iGridY );

    int iOffset = _iOffsets.Item ( iGridX, iGridY );
    if ( iOffset == 0 )
        return false;

    _file.Seek ( iOffset );
    RestoreLinks ();

    _iGridX = iGridX;
    _iGridY = iGridY;

    return true;
}

bool CTAContourGrid :: Load ( int iX, int iY )
{
    int iMeshX = iX / (WGS84IntScale/100);
    int iMeshY = iY / (WGS84IntScale/100);

    iMeshX -= iMeshX % 50;
    iMeshY -= iMeshY % 50;

    int iGridX = ( iX - iMeshX * (WGS84IntScale/100)) / CRoMapFileBase::GridWidth ();
    int iGridY = ( iY - iMeshY * (WGS84IntScale/100)) / CRoMapFileBase::GridWidth ();

    if (( iMeshX == _iMeshX ) && ( iMeshY == _iMeshY ))
    {
        if (( iGridX == _iGridX ) && ( iGridY == _iGridY ))
            return true;

        return LoadGrid ( iGridX, iGridY );
    }

    CString str;
    GetPathName ( str, iMeshX, iMeshY );
    //TRACE ( "Load %s\r\n", str.GetBuffer ( 0 ));

    if ( !CRoFile::IsFileExist ( str ))
        return false;

    if ( _file.Open ( str, CFile::modeRead | CFile::shareDenyNone ) == FALSE )
    {
        _iMeshX = _iMeshY = 0;
        return false;
    }

    _iOffsets.Alloc ( CRoMapFileBase::GridNum (), CRoMapFileBase::GridNum ());
    if ( !_file.ReadSize ( _iOffsets.Buf (), _iOffsets.BufSize ()))
    {
        _iMeshX = _iMeshY = 0;
        return false;
    }

    _iMeshX = iMeshX;
    _iMeshY = iMeshY;

    return LoadGrid ( iGridX, iGridY );
}

#if 0
static int _iBoundLeft;
static int _iBoundRight;
static int _iBoundTop;
static int _iBoundBottom;
#else
#define _iBoundLeft     0
#define _iBoundRight    320
#define _iBoundTop      240
#define _iBoundBottom   0
#endif

//static BOOL ClipTest( int iP, int iQ, double& fU1, double& fU2 )
static bool ClipTest( int iP, int iQ, int& fU1, int& fU2 )
{
    //double fRatio;
	int fRatio;
    bool bResult = true;;

    if ( iP < 0 )
    {
        //fRatio = (double) iQ / iP;
	    fRatio = iQ * 1000 / iP;

        if ( fRatio > fU2 )
            bResult = false;
        else if ( fRatio > fU1 )
            fU1 = fRatio;
    }
    else
    {
        if ( iP > 0 )
        {
            //fRatio = (double) iQ / iP;
		    fRatio = iQ * 1000 / iP;

            if ( fRatio < fU1 )
                bResult = false;
            else if  ( fRatio < fU2 )
                fU2 = fRatio;
        }
        else
        {
            if ( iQ < 0 )
                bResult = false;
        }
    }

    return bResult;
}

static bool TestClipping ( int& iXStart, int& iYStart, int& iXEnd, int& iYEnd )
{
   int iX1 = iXStart;
   int iY1 = iYStart;
   int iX2 = iXEnd;
   int iY2 = iYEnd;
   //double fU1 = 0;
   int fU1 = 0;
   //double fU2 = 1;
   int fU2 = 1000;
   int iDx = iX2 - iX1;

   if ( ClipTest( -iDx, iX1 - _iBoundLeft, fU1, fU2 ))
   {
      if ( ClipTest( iDx, _iBoundRight - iX1, fU1, fU2 ))
      {
         int iDy = iY2 - iY1;

         if ( ClipTest( -iDy, iY1 - _iBoundBottom, fU1, fU2 ))
         {
            if ( ClipTest( iDy, _iBoundTop - iY1, fU1, fU2 ))
            {
               if ( fU1 > 0 )
               {
                  //iXStart = iX1 + (int) (fU1 * iDx);
                  //iYStart = iY1 + (int) (fU1 * iDy);
				   iXStart = iX1 + (fU1 * iDx)/1000;
				   iYStart = iY1 + (fU1 * iDy)/1000;
               }

               if ( fU2 < 1 )
               {
                  //iXEnd = iX1 + (int) (fU2 * iDx);
                  //iYEnd = iY1 + (int) (fU2 * iDy);
                  iXEnd = iX1 + (fU2 * iDx)/1000;
                  iYEnd = iY1 + (fU2 * iDy)/1000;
               }

               return true;
            }
         }
      }
   }

   return false;
}

#pragma warning(disable:4100)
#pragma warning(disable:4189)

void CTAContourGrid :: Draw ( QPainter *painter , int iOffsetX, int iOffsetY, int iScale, int iDivider )
{
    POINT *ptXYs = _ptXYs.Buf ();

    for ( int i1 = 0; i1 < _iIdxes.Size (); i1++ )
    {
        int iPtStart = PtStart ( i1 );
        int iPtSize  = PtSize ( i1 );

        for ( int i2 = 0; i2 < iPtSize; i2++ )
            painter->drawLine (
				iOffsetX + ptXYs [ iPtStart + i2 ].x * iScale / iDivider, iOffsetY + ptXYs [ iPtStart + i2 ].y * iScale / iDivider,
				iOffsetX + ptXYs [ iPtStart + i2 + 1 ].x * iScale / iDivider, iOffsetY + ptXYs [ iPtStart + i2 + 1 ].y * iScale / iDivider );
    }
}

void CTAContourGrid :: DrawClip ( QPainter *painter , int iOffsetX, int iOffsetY, int iScale, int iDivider )
{
    POINT *ptXYs = _ptXYs.Buf ();

    for ( int i1 = 0; i1 < _iIdxes.Size (); i1++ )
    {
        int iPtStart = PtStart ( i1 );
        int iPtSize  = PtSize ( i1 );

        int iX1 = iOffsetX + ptXYs [ iPtStart ].x * iScale / iDivider;
        int iY1 = iOffsetY + ptXYs [ iPtStart ].y * iScale / iDivider;

        for ( int i2 = 1; i2 < iPtSize; i2++ )
        {
            int iX2 = iOffsetX + ptXYs [ iPtStart + i2 ].x * iScale / iDivider;
            int iY2 = iOffsetY + ptXYs [ iPtStart + i2 ].y * iScale / iDivider;
			int iX2bak = iX2;
			int iY2bak = iY2;

            if ( TestClipping ( iX1, iY1, iX2, iY2 ))
				painter->drawLine ( iX1, iY1, iX2, iY2 );

            iX1 = iX2bak;
            iY1 = iY2bak;
        }
    }
}

void CTAContourGrid :: Draw ( QPainter *painter , int iScale, int iDivider, CRoRotate& rotate )
{
    POINT *ptXYs = _ptXYs.Buf ();
    int iMinX = XMin ();
    int iMinY = YMin ();

    for ( int i1 = 0; i1 < _iIdxes.Size (); i1++ )
    {
        int iPtStart = PtStart ( i1 );
        int iPtSize  = PtSize ( i1 );

        int iX1 = ptXYs [ iPtStart ].x + iMinX;
        int iY1 = CRoMapFileBase::GridWidth () - ptXYs [ iPtStart ].y + iMinY;
        rotate.RotateXY ( iX1, iY1, iScale, iDivider );

        for ( int i2 = 1; i2 < iPtSize; i2++ )
        {
            int iX2 = ptXYs [ iPtStart + i2 ].x + iMinX;
            int iY2 = CRoMapFileBase::GridWidth () - ptXYs [ iPtStart + i2 ].y + iMinY;
            rotate.RotateXY ( iX2, iY2, iScale, iDivider );
			int iX2bak = iX2;
			int iY2bak = iY2;

            painter->drawLine ( iX1, iY1, iX2, iY2 );

			iX1 = iX2bak;
			iY1 = iY2bak;
        }
    }
}

void CTAContourGrid :: DrawClip ( QPainter *painter , int iScale, int iDivider, CRoRotate& rotate )
{
#if 0
	Draw ( painter, iScale, iDivider, rotate );
#else
    POINT *ptXYs = _ptXYs.Buf ();
    int iMinX = XMin ();
    int iMinY = YMin ();

    for ( int i1 = 0; i1 < _iIdxes.Size (); i1++ )
    {
        int iPtStart = PtStart ( i1 );
        int iPtSize  = PtSize ( i1 );

        int iX1 = ptXYs [ iPtStart ].x + iMinX;
        int iY1 = CRoMapFileBase::GridWidth () - ptXYs [ iPtStart ].y + iMinY;
        rotate.RotateXY ( iX1, iY1, iScale, iDivider );

        //TRACE ( "%d,%d => ", ptXYs [ iPtStart ].x, ptXYs [ iPtStart ].y );
        //TRACE ( "%d,%d\r\n", iX1, iY1 );

        for ( int i2 = 1; i2 < iPtSize; i2++ )
        {
            int iX2 = ptXYs [ iPtStart + i2 ].x + iMinX;
            int iY2 = CRoMapFileBase::GridWidth () - ptXYs [ iPtStart + i2 ].y + iMinY;
            rotate.RotateXY ( iX2, iY2, iScale, iDivider );

            //TRACE ( "%d,%d => ", ptXYs [ iPtStart + i2 ].x, ptXYs [ iPtStart + i2 ].y );
            //TRACE ( "%d,%d\r\n", iX2, iY2 );

            if ( TestClipping ( iX1, iY1, iX2, iY2 ))
				painter->drawLine ( iX1, iY1, iX2, iY2 );

            iX1 = iX2;
            iY1 = iY2;
        }

        //return;
    }
#endif
}
