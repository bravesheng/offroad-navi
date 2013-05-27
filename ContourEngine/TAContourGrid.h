#ifndef __TAContourGrid_h__
#define __TAContourGrid_h__

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
    void Draw ( QPainter *painter , int iScale, int iDivider, CRoRotate& rotate );
    void DrawClip ( QPainter *painter , int iScale, int iDivider, CRoRotate& rotate );

    int XMin ()
    {
        //TRACE ( _T("MeshX=%d GridX=%d\r\n"), _iMeshX, _iGridX );
        return ( _iMeshX * (WGS84IntScale/100) + _iGridX * CRoMapFileBase::GridWidth ()); 
    }
    int XMax (){ return XMin () + CRoMapFileBase::GridWidth (); }
    int YMin (){ return ( _iMeshY * (WGS84IntScale/100) + _iGridY * CRoMapFileBase::GridWidth ()); }
    int YMax (){ return YMin () + CRoMapFileBase::GridWidth (); }

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
    CRoBufferT2D<int> _iOffsets;
    CRoBuffer _buf;

    CRoBufferT<int>   _iIdxes;
    CRoBufferT<int>   _iAltitudes;
    CRoBufferT<POINT> _ptXYs;

    static CRoWorkDir m_WorkDir;;
};

#endif
