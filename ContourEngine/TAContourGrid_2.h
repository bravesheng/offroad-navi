#ifndef __TAContourGrid_2_h__
#define __TAContourGrid_2_h__

#include "RoFile.h"
#include "RoBuffer.h"
#include "RoWorkDir.h"
#include "RoMapFileBase.h"
#include "RoRotate.h"
#include "RoCoord.h"

class CTAContourGrid {
public:
    CTAContourGrid () : _iMeshX(0), _iMeshY(0), _iGridX(0), _iGridY(0){}

    static void SetWorkDir ( LPCTSTR sWorkDir ){ m_WorkDir.Set ( sWorkDir ); }
    void GetPathName ( CString& str, int iMeshX, int iMeshY ){ str.Format ( _T("%sN%dE%d.cs2"), m_WorkDir.Get (), iMeshY, iMeshX ); }
    bool Load ( int iX, int iY );

    void Draw ( QPainter *painter , int iOffsetX, int iOffsetY, int iScale, int iDivider );
    void DrawClip ( QPainter *painter , int iOffsetX, int iOffsetY, int iScale, int iDivider );
    static void DrawAltitude ( QPainter& painter );

    int XMin ()
    {
        //TRACE ( _T("MeshX=%d GridX=%d\r\n"), _iMeshX, _iGridX );
        return ( _iMeshX * (WGS84IntScale/100) + _iGridX * CRoMapFileBase::GridWidth ()); 
    }
    int XMax (){ return XMin () + CRoMapFileBase::GridWidth (); }
    int YMin (){ return ( _iMeshY * (WGS84IntScale/100) + _iGridY * CRoMapFileBase::GridWidth ()); }
    int YMax (){ return YMin () + CRoMapFileBase::GridWidth (); }

    static void SetAltitudeMode ( int iAltitudeMode ){ m_iAltitudeMode = iAltitudeMode; }
    static void SetAltitudeColor ( int iAltitudeColor ){ m_iAltitudeColor = iAltitudeColor; }
    static void ClearAltitudeMs ()
    {
        m_iAltitudeMIdx = 0;
        memset ( m_iAltitudeMCnts, 0, sizeof ( m_iAltitudeMCnts ));
        memset ( m_iAltitudeMatrix, 0, sizeof ( m_iAltitudeMatrix ));
    }

protected:
    bool LoadGrid ( int iGridX, int iGridY );
    void RestoreLinks ();
    int PtStart ( int iIdx ){ return ( iIdx == 0 ? 0 : _iIdxes [ iIdx - 1 ]); };
    int PtSize ( int iIdx ){ return ( iIdx == 0 ? _iIdxes [ iIdx ] : _iIdxes [ iIdx ] - _iIdxes [ iIdx - 1]); };

    int _iMeshX;
    int _iMeshY;
    int _iGridX;
    int _iGridY;

    CRoFile _file;
    //CRoBufferT2D<int> _iOffsets;
    int _iOffsets [20][20];
    CRoBuffer _buf;

    CRoBufferT<int>   _iIdxes;
    CRoBufferT<int>   _iAltitudes;
    CRoBufferT<POINT> _ptXYs;

    static CRoWorkDir m_WorkDir;;

    static bool InsertAltitude ( int iAltitude );
    static bool InsertAltitudeRect ( QRect& rect );

    static int m_iAltitudeMode;
    static int m_iAltitudeColor;

    static int m_iAltitudeMs [ 20 ];
    static int m_iAltitudeMCnts [ 20 ];
    static int m_iAltitudeMIdx;
    static QRect m_rectAltitudeMs [ 20 ];
    static int m_iAltitudeMatrix [ 6 ][ 6 ];
};

#endif
