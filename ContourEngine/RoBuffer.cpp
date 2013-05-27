#include "stdafx.h"
#include "RoBuffer.h"

char *CRoBuffer :: Alloc  ( int iSize )
{
    if ( iSize <= _iAllocSize )
        _iSize = iSize;
    else
    {
        Release ();
        _pBuf = new char [ iSize ];

        if ( _pBuf )
            _iSize = _iAllocSize = iSize;
    }

    return _pBuf;
}

void CRoBuffer :: Release ()
{
    if ( _pBuf == NULL )
        return;
    
    delete [] _pBuf;
    _pBuf = NULL;
    _iAllocSize = _iSize = 0;
}

void CRoBuffer :: LoadFile ( LPCTSTR sPathName, int iOffset, int iSize )
{
    CRoFile file ( sPathName );
    file.ReadToBuffer ( *this, iOffset, iSize );
}
