#ifndef __RoRotate_h__
#define __RoRotate_h__

class CRoRotate {
public:
    CRoRotate ( int iX = 0, int iY = 0, int iAngle = 0 ) : _iX(iX), _iY(iY), _iOffsetX(0), _iOffsetY(0) { SetAngle ( iAngle ); }

    void SetAngle ( int iAngle );
    int  Angle (){ return _iAngle; }
    void IncAngle ( int iIncAngle ){ SetAngle (( _iAngle + iIncAngle + 360 ) % 360 ); }

    void SetXY ( int iX, int iY ){ _iX = iX; _iY = iY; }
    void SetOffset ( int iOffsetX, int iOffsetY ){ _iOffsetX = iOffsetX; _iOffsetY = iOffsetY; }

    void RotateXY ( int& iX, int& iY );
    void RotateXY ( int& iX, int& iY, int iScale, int iDivider );
    void ReverseRotateXY ( int& iX, int& iY, int iScale, int iDivider );
    void ReverseRotateXY ( int& iX, int& iY );
    void GetWidth ( int& iWidth, int& iHeight );

protected:
    int _iX;
    int _iY;
    int _iOffsetX;
    int _iOffsetY;

    int _iAngle;
    int _iSinAngle;
    int _iCosAngle;
    int _iReverseSinAngle;
    int _iReverseCosAngle;
};

#endif
