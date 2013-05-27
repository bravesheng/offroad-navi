#include "stdafx.h"
#include "TAContourGrid_2.h"
#include "RoMapFileBase.h"

CRoWorkDir CTAContourGrid::m_WorkDir;
int CTAContourGrid::m_iAltitudeMode = 10;
int CTAContourGrid::m_iAltitudeColor = 50;

int CTAContourGrid::m_iAltitudeMs [ 20 ];
int CTAContourGrid::m_iAltitudeMCnts [ 20 ];
int CTAContourGrid::m_iAltitudeMIdx;
QRect CTAContourGrid::m_rectAltitudeMs [ 20 ];
int CTAContourGrid::m_iAltitudeMatrix [ 6 ][ 6 ];

bool CTAContourGrid :: InsertAltitude ( int iAltitude )
{
    for ( int i1 = 0; i1 < m_iAltitudeMIdx; i1++ )
    {
        if ( m_iAltitudeMs [ i1 ] == iAltitude )
        {
            if ( m_iAltitudeMCnts [ i1 ] > 0 )
                return false;

            m_iAltitudeMCnts [ i1 ]++;
        }
    }

    if ( m_iAltitudeMIdx >= 20 )
        return false;

    m_iAltitudeMs [ m_iAltitudeMIdx++ ] = iAltitude;
    return true;
}

bool CTAContourGrid :: InsertAltitudeRect ( QRect& rect )
{
    if (( rect.left () < 0 ) || ( rect.right () > 456 ) || ( rect.top () < 0 ) || ( rect.bottom () > 456 ))
    {
        m_iAltitudeMIdx--;
        return false;
    }

    for ( int i1 = 0; i1 < m_iAltitudeMIdx - 1; i1++ )
    {
        if ( rect.intersects ( m_rectAltitudeMs [ i1 ]))
        {
            m_iAltitudeMIdx--;
            return false;
        }
    }

    if ( m_iAltitudeMatrix [ rect.top ()/ 80 ][ rect.left ()/ 80 ] != 0 )
    {
        m_iAltitudeMIdx--;
        return false;
    }

    m_rectAltitudeMs [ m_iAltitudeMIdx - 1 ] = rect;
    m_iAltitudeMatrix [ rect.top ()/ 80 ][ rect.left ()/ 80 ] = 1;

    return true;
}

void CTAContourGrid :: RestoreLinks ()
{
    short iLineSize;
    _file.Read ( &iLineSize, sizeof ( iLineSize ));
    //iReaded += sizeof ( short );
    //TRACE ( "Linesize=%d\r\n", iLineSize );

    //ASSERT ( iLineSize != 0 );

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

    //int iOffset = _iOffsets.Item ( iGridX, iGridY );
    int iOffset = _iOffsets [ iGridX ][ iGridY ];
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

    //_iOffsets.Alloc ( CRoMapFileBase::GridNum (), CRoMapFileBase::GridNum ());
    //if ( !_file.ReadSize ( _iOffsets.Buf (), _iOffsets.BufSize ()))
    if ( !_file.ReadSize ( _iOffsets, sizeof ( _iOffsets )))
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
#define EXPAND 1
#define _iBoundLeft     (0-EXPAND)
#define _iBoundRight    (456+EXPAND)
#define _iBoundTop      (456+EXPAND)
#define _iBoundBottom   (0-EXPAND)
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
    QFontMetrics fontM(painter->font());

    for ( int i1 = 0; i1 < _iIdxes.Size (); i1++ )
    {
        int iAltitude = _iAltitudes [ i1 ];

        if (( m_iAltitudeMode == 10 ) || (( iAltitude % m_iAltitudeMode ) == 0 ) || (( iAltitude % m_iAltitudeColor ) == 0 ))
        {
            if (( _iAltitudes [ i1 ] % m_iAltitudeColor ) == 0 )
                painter->setPen( Qt::blue );

            int iPtStart = PtStart ( i1 );
            int iPtSize  = PtSize ( i1 ) - 1;

            for ( int i2 = 0; i2 < iPtSize; i2++ )
            {
                painter->drawLine (
                    iOffsetX + ptXYs [ iPtStart + i2 ].x * iScale / iDivider, iOffsetY + ptXYs [ iPtStart + i2 ].y * iScale / iDivider,
                    iOffsetX + ptXYs [ iPtStart + i2 + 1 ].x * iScale / iDivider, iOffsetY + ptXYs [ iPtStart + i2 + 1 ].y * iScale / iDivider );

                if (( i2 == ( iPtSize / 2 )) && InsertAltitude ( iAltitude ))
                {
                    CString str;
                    str.Format ( TEXT("%dM"), iAltitude );

                    QRect Rect = fontM.boundingRect ( str );
                    int iX1 = iOffsetX + ptXYs [ iPtStart + i2 ].x * iScale / iDivider;
                    int iY1 = iOffsetY + ptXYs [ iPtStart + i2 ].y * iScale / iDivider;
                    int iX2 = iOffsetX + ptXYs [ iPtStart + i2 + 1 ].x * iScale / iDivider;
                    int iY2 = iOffsetY + ptXYs [ iPtStart + i2 + 1 ].y * iScale / iDivider;
                    int iFontOffsetX = ( iX1 + iX2 - Rect.width ()) / 2;
                    int iFontOffsetY = (( iY1 + iY2 ) /* - Rect.height ()*/) / 2;

                    Rect.adjust( iFontOffsetX, iFontOffsetY, iFontOffsetX, iFontOffsetY );
                    InsertAltitudeRect ( Rect );
                }
            }
            if (( _iAltitudes [ i1 ] % m_iAltitudeColor ) == 0 )
                painter->setPen( Qt::black );
        }
    }
}

void CTAContourGrid :: DrawClip ( QPainter *painter , int iOffsetX, int iOffsetY, int iScale, int iDivider )
{
    POINT *ptXYs = _ptXYs.Buf ();
    QFontMetrics fontM(painter->font());

    for ( int i1 = 0; i1 < _iIdxes.Size (); i1++ )
    {
        int iAltitude = _iAltitudes [ i1 ];

        if (( m_iAltitudeMode == 10 ) || (( iAltitude % m_iAltitudeMode ) == 0 ) || (( iAltitude % m_iAltitudeColor ) == 0 ))
        {
            if (( iAltitude % m_iAltitudeColor ) == 0 )
                painter->setPen( Qt::blue );

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
                {
                    painter->drawLine ( iX1, iY1, iX2, iY2 );

                    if (( i2 == ( iPtSize / 2 )) && InsertAltitude ( iAltitude ))
                    {
                        CString str;
                        str.Format ( TEXT("%dM"), iAltitude );

                        QRect Rect = fontM.boundingRect ( str );
                        int iFontOffsetX = ( iX1 + iX2 - Rect.width ()) / 2;
                        int iFontOffsetY = (( iY1 + iY2 )/* - Rect.height ()*/) / 2;

                        Rect.adjust( iFontOffsetX, iFontOffsetY, iFontOffsetX, iFontOffsetY );
                        InsertAltitudeRect ( Rect );
                    }
                }

                iX1 = iX2bak;
                iY1 = iY2bak;
            }

            if (( iAltitude % m_iAltitudeColor ) == 0 )
                painter->setPen( Qt::black );
        }
    }
}

void CTAContourGrid :: DrawAltitude ( QPainter& painter )
{
    // sort
    int i1;
#if 0
    for ( i1 = 0; i1 < m_iAltitudeMIdx; i1++ )
        TRACE ( "%d ", m_iAltitudeMs [ i1 ]);
    TRACE ( "==> " );
#endif

    //SetBkMode ( hDC, TRANSPARENT );

    for ( i1 = 0; i1 < m_iAltitudeMIdx; i1++ )
    {
        for ( int i2 = i1 + 1; i2 < m_iAltitudeMIdx; i2++ )
        {
            if ( m_iAltitudeMs [ i1 ] > m_iAltitudeMs [ i2 ])
            {
                int iTemp = m_iAltitudeMs [ i1 ];
                m_iAltitudeMs [ i1 ] = m_iAltitudeMs [ i2 ];
                m_iAltitudeMs [ i2 ] = iTemp;

                QRect rectTemp = m_rectAltitudeMs [ i1 ];
                m_rectAltitudeMs [ i1 ] = m_rectAltitudeMs [ i2 ];
                m_rectAltitudeMs [ i2 ] = rectTemp;
            }
        }
    }
#if 0
    for ( i1 = 0; i1 < m_iAltitudeMIdx; i1++ )
        TRACE ( "%d ", m_iAltitudeMs [ i1 ]);

    TRACE ( "\r\n" );
#endif
    int iStep = 10;

    if ( m_iAltitudeMIdx > 5 )
        iStep = ( m_iAltitudeMIdx * 10 ) / 5;

    for ( i1 = 0; i1 < m_iAltitudeMIdx; i1 = ( i1 * 10 + iStep ) / 10 )
    {
        CString str;
        str.Format ( TEXT("%dM"), m_iAltitudeMs [ i1 ]);

        painter.drawText ( m_rectAltitudeMs [i1], Qt::AlignCenter, str );
    }
}
