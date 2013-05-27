#include "stdafx.h"
#include "RoRotate.h"

// for rotate
static int m_iSinAngles [] =
{
     0,  17,  34,  52,  69,  87, 104, 121, 139, 156,
   173, 190, 207, 224, 241, 258, 275, 292, 309, 325,
   342, 358, 374, 390, 406, 422, 438, 453, 469, 484,
   499, 515, 529, 544, 559, 573, 587, 601, 615, 629,
   642, 656, 669, 681, 694, 707, 719, 731, 743, 754,
   766, 777, 788, 798, 809, 819, 829, 838, 848, 857,
   866, 874, 882, 891, 898, 906, 913, 920, 927, 933,
   939, 945, 951, 956, 961, 965, 970, 974, 978, 981,
   984, 987, 990, 992, 994, 996, 997, 998, 999, 999,
   1000
};

void CRoRotate :: RotateXY ( int& iX, int& iY )
{

   if ( _iAngle == 0 )
      return;
/*
   if ( _iAngle == 180 )
   {
      iX = DSP_GridWidth * 2 - iX;
      iY = DSP_GridHeight * 2 - iY;
   }
   else
   {
*/
       int iDeltaX = iX - _iX;
	   int iDeltaY = iY - _iY;
	   iX = ( iDeltaX * _iCosAngle - iDeltaY * _iSinAngle ) / 1000 + _iX;
	   iY = ( iDeltaX * _iSinAngle + iDeltaY * _iCosAngle ) / 1000 + _iY;
//   }
}

void CRoRotate :: ReverseRotateXY ( int& iX, int& iY )
{

   if ( _iAngle == 0 )
      return;
/*
   if ( _iAngle == 180 )
   {
      iX = DSP_GridWidth * 2 - iX;
      iY = DSP_GridHeight * 2 - iY;
   }
   else
   {
*/
       int iDeltaX = iX - _iX;
	   int iDeltaY = iY - _iY;
	   iX = ( iDeltaX * _iReverseCosAngle - iDeltaY * _iReverseSinAngle ) / 1000 + _iX;
	   iY = ( iDeltaX * _iReverseSinAngle + iDeltaY * _iReverseCosAngle ) / 1000 + _iY;
//   }
}

void CRoRotate :: SetAngle ( int iAngle )
{
    iAngle = ( iAngle + 360 ) % 360;

	if ( _iAngle == iAngle )
		return;

	_iAngle = iAngle;
	iAngle   = 360 - _iAngle;

	int iAngleIndex = iAngle % 90;

	switch ( iAngle / 90 )
	{
	case 0:
		_iSinAngle = m_iSinAngles [ iAngleIndex ];
		_iCosAngle = m_iSinAngles [ 90 - iAngleIndex ];
		break;

	case 1:
		_iSinAngle =  m_iSinAngles [ 90 - iAngleIndex ];
		_iCosAngle = -m_iSinAngles [ iAngleIndex ];
		break;

	case 2:
		_iSinAngle = -m_iSinAngles [ iAngleIndex ];
		_iCosAngle = -m_iSinAngles [ 90 - iAngleIndex ];
		break;

	case 3:
		_iSinAngle = -m_iSinAngles [ 90 - iAngleIndex ];
		_iCosAngle =  m_iSinAngles [ iAngleIndex ];
		break;
	}

	iAngleIndex = _iAngle % 90;
	switch ( _iAngle / 90 )
	{
	case 0:
		_iReverseSinAngle = m_iSinAngles [ iAngleIndex ];
		_iReverseCosAngle = m_iSinAngles [ 90 - iAngleIndex ];
		break;

	case 1:
		_iReverseSinAngle =  m_iSinAngles [ 90 - iAngleIndex ];
		_iReverseCosAngle = -m_iSinAngles [ iAngleIndex ];
		break;

	case 2:
		_iReverseSinAngle = -m_iSinAngles [ iAngleIndex ];
		_iReverseCosAngle = -m_iSinAngles [ 90 - iAngleIndex ];
		break;

	case 3:
		_iReverseSinAngle = -m_iSinAngles [ 90 - iAngleIndex ];
		_iReverseCosAngle =  m_iSinAngles [ iAngleIndex ];
		break;
	}
}

void CRoRotate :: GetWidth ( int& iWidth, int& iHeight )
{
    int iX = _iX;
    int iY = _iY;

	_iX = iWidth / 2;
	_iY = iHeight / 2;

	int iXs [ 4 ] = { 0, 0, iWidth, iWidth };
	int iYs [ 4 ] = { 0, iHeight, iHeight, 0 };

	for ( int i1 = 0; i1 < 4; i1++ )
		ReverseRotateXY ( iXs [ i1 ], iYs [ i1 ]);

	int iMinX = iXs [ 0 ];
	int iMaxX = iXs [ 0 ];
	int iMinY = iYs [ 0 ];
	int iMaxY = iYs [ 0 ];

	for ( int i1 = 1; i1 < 4; i1++ )
	{
		if ( iXs [ i1 ] < iMinX )
			iMinX = iXs [ i1 ];
		else if ( iXs [ i1 ] > iMaxX )
			iMaxX = iXs [ i1 ];
		if ( iYs [ i1 ] < iMinY )
			iMinY = iYs [ i1 ];
		else if ( iYs [ i1 ] > iMaxY )
			iMaxY = iYs [ i1 ];
	}

	iWidth = iMaxX - iMinX;
	iHeight = iMaxY - iMinY;

    _iX = iX;
    _iY = iY;
}

void CRoRotate :: RotateXY ( int& iX, int& iY, int iScale, int iDivider )
{
    RotateXY ( iX, iY );
    iX = ( iX - _iX ) * iDivider / iScale + _iOffsetX;
    iY = _iOffsetY - ( iY - _iY ) * iDivider / iScale;
}

void CRoRotate :: ReverseRotateXY ( int& iX, int& iY, int iScale, int iDivider )
{
    iX = ( iX - _iOffsetX ) * iScale / iDivider + _iX;
    iY = _iY - ( iY - _iOffsetY ) * iScale / iDivider;
    ReverseRotateXY ( iX, iY );
}
