#ifndef __RoMapFileBase_h__
#define __RoMapFileBase_h__

class CRoMapFileBase {
public:
    CRoMapFileBase () : _iXMin(0), _iYMin(0), _iXMax(0), _iYMax(0) {}

    static void SetGridWidth ( int iGridWidth ){ m_iGridWidth = iGridWidth; CalcGridNum (); }
    static int  GridWidth (){ return m_iGridWidth; }
    static void SetMeshWidth ( int iMeshWidth ){ m_iMeshWidth = iMeshWidth; CalcGridNum (); }
    static int  MeshWidth (){ return m_iMeshWidth; }
    static int  GridNum (){ return m_iGridNum; }
    static void CalcGridNum ();

    int XMin (){ return _iXMin; }
    int YMin (){ return _iYMin; }
    int XMax (){ return _iXMax; }
    int YMax (){ return _iYMax; }

    int RangeX (){ return ( _iXMax - _iXMin ); }
    int RangeY (){ return ( _iYMax - _iYMin ); }
    void DumpRange ();

    void ClearRange (){ _iXMin = _iYMin = _iXMax = _iYMax = 0; }
    void SetRange ( int iXMin, int iYMin, int iXMax, int iYMax )
    {
        _iXMin = iXMin;
        _iYMin = iYMin;
        _iXMax = iXMax;
        _iYMax = iYMax;
    }

    void SetRange ( CRoMapFileBase& file )
    {
        _iXMin = file.XMin ();
        _iYMin = file.YMin ();
        _iXMax = file.XMax ();
        _iYMax = file.YMax ();
    }

    void SetGridRange ( CRoMapFileBase& file )
    {
        _iXMin = file.XMin () - ( file.XMin () % GridWidth ());
        _iYMin = file.YMin () - ( file.YMin () % GridWidth ());
        _iXMax = file.XMax () + ( GridWidth () - (( file.XMax () - 1 ) % GridWidth ())) - 1;
        _iYMax = file.YMax () + ( GridWidth () - (( file.YMax () - 1 ) % GridWidth ())) - 1;
    }

    int XGridNum (){ return ( _iXMax - _iXMin ) / GridWidth (); }
    int YGridNum (){ return ( _iYMax - _iYMin ) / GridWidth (); }

    void AdjustRangeX ( int iX, int iNewRange )
    {
        _iXMin = iX;
        _iXMax = iX + iNewRange;
    }

    void AdjustRangeY ( int iY, int iNewRange )
    {
        _iYMin = iY;
        _iYMax = iY + iNewRange;
    }

    void SelectRangeX ( int iX ){ AdjustRangeX ( iX - ( iX % GridWidth ()), GridWidth ()); }
    void SelectRangeY ( int iY ){ AdjustRangeY ( iY - ( iY % GridWidth ()), GridWidth ()); }
    void SelectRange ( int iX, int iY ){ SelectRangeX ( iX ); SelectRangeY ( iY ); }

    bool IsPointInRange ( int iX, int iY )
    {
        if (( iX < _iXMin ) || ( iX > _iXMax ))
            return false;

        if (( iY < _iYMin ) || ( iY > _iYMax ))
            return false;

        return true;
    }

    void ExpandToMesh ();
    virtual void StartCut (){}
    virtual void AddCutLine ( int /* iIdx */, int /* iX1 */, int /* iY1 */, int /* iX2 */, int /* iY2 */ ){}
    virtual void EndCut (){}

protected:
    static int m_iGridWidth;
    static int m_iMeshWidth;
    static int m_iGridNum;
    // UTM
    int	_iXMin;
    int	_iYMin;
    int	_iXMax;
    int	_iYMax;
};

#if 0
inline bool IsOnBoundary ( POINT& ptXY )
{
    return (( ptXY.x == 0 ) || ( ptXY.y == 0 ) || ( ptXY.x == CRoMapFileBase::GridWidth ()) || ( ptXY.y == CRoMapFileBase::GridWidth ()));
}
#endif
#endif
