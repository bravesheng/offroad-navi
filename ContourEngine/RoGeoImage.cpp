#include "stdafx.h"
#include "RoGeoImage.h"
#include "math.h"
#include "RoString.h"
#include "QMessageBox.h"

CRoWorkDir CRoGeoImage::m_WorkDir;

void CRoGeoImage :: DrawXY ( int iX, int iY, int iScale, int iDivider )
{
    // convert to bmp coord
    iX = ( iX - OrgX ) * 600 / 50000;
    iY = ( iY - OrgY ) * 600 / 50000;

    int iWidth = Width * 600 * iScale / iDivider / 50000;
    int iX1 = iX - iWidth / 2;
    int iY1 = iY - iWidth / 2;
    int iX2 = iX1 + iWidth;
    int iY2 = iY1 + iWidth;

#if 1
    bool bIs400 = false;
    bool bIs200 = false;
    if (( iScale / iDivider ) > 200 )
    {
        iX1 /= 4;
        iY1 /= 4;
        iX2 /= 4;
        iY2 /= 4;
        iWidth /= 4;
        bIs400 = true;
    }
    else if (( iScale / iDivider ) >= 50 )
    {
        iX1 /= 2;
        iY1 /= 2;
        iX2 /= 2;
        iY2 /= 2;
        iWidth /= 2;
        bIs200 = true;
    }

    int iOffsetX = 0 - ( iX1 % 100 ) * Width / iWidth;
    int iOffsetY = (( iY1 % 100 ) + iWidth - 100 ) * Width / iWidth;
    int iStep = 100 * Width / iWidth;
    iX1 -= ( iX1 % 100 );
    iY1 -= ( iY1 % 100 );

    QPixmap bmp;
    CString  str;
    //QMessageBox msg;

    Clear ();
#if 0
     if ( bmp.load ( "E:\\contour\\png\\Grid1642.png" ))
        _dc.drawPixmap ( 0, 0, 100, 100, bmp, 0, 0, 100, 100 );
    return;
#endif
    while (( iOffsetY + iStep ) >= 0 )
    {
        int iX1bak = iX1;
        int iOffsetXbak = iOffsetX;

        while ( iOffsetX < Width )
        {
            if ( bIs400 )
                str.Format ( _T("%sL1\\Grid%02d%02d.png"), m_WorkDir.Get (), iX1 / 100, iY1 / 100 );
                //str.Format ( _T("E:\\contour\\bmp\\L1\\Grid%02d%02d.bmp"), iX1 / 100, iY1 / 100 );
            else if ( bIs200 )
                str.Format ( _T("%sL0\\Grid%02d%02d.png"), m_WorkDir.Get (), iX1 / 100, iY1 / 100 );
                //str.Format ( _T("E:\\contour\\bmp\\L0\\Grid%02d%02d.bmp"), iX1 / 100, iY1 / 100 );
            else
                str.Format ( _T("%sGrid%02d%02d.png"), m_WorkDir.Get (), iX1 / 100, iY1 / 100 );
            //msg.setText ( str );
            if ( bmp.load ( str ))
            {
                //msg.exec ();
                drawPixmap ( iOffsetX, iOffsetY, iStep, iStep, bmp, 0, 0, 100, 100 );
            }

            iX1 += 100;
            iOffsetX += iStep;
        }

        iX1 = iX1bak;
        iY1 += 100;

        iOffsetX = iOffsetXbak;
        iOffsetY -= iStep;
    }
#else
    int iOffsetX = 0 - ( iX1 % 100 ) * Width / iWidth;
    int iOffsetY = (( iY1 % 100 ) + iWidth - 100 ) * Width / iWidth;
    int iStep = 100 * Width / iWidth;
    iX1 -= ( iX1 % 100 );
    iY1 -= ( iY1 % 100 );

    QPixmap bmp;
    CString  str;
    //QMessageBox msg;

    Clear ();
#if 0
     if ( bmp.load ( "E:\\contour\\png\\Grid1642.png" ))
        _dc.drawPixmap ( 0, 0, 100, 100, bmp, 0, 0, 100, 100 );
    return;
#endif
    while (( iOffsetY + iStep ) >= 0 )
    {
        int iX1bak = iX1;
        int iOffsetXbak = iOffsetX;

        while ( iOffsetX < Width )
        {
            str.Format ( _T("%sGrid%02d%02d.png"), m_WorkDir.Get (), iX1 / 100, iY1 / 100 );
            //msg.setText ( str );
            if ( bmp.load ( str ))
            {
                //msg.exec ();
                drawPixmap ( iOffsetX, iOffsetY, iStep, iStep, bmp, 0, 0, 100, 100 );
            }

            iX1 += 100;
            iOffsetX += iStep;
        }

        iX1 = iX1bak;
        iY1 += 100;

        iOffsetX = iOffsetXbak;
        iOffsetY -= iStep;
    }
#endif
}
