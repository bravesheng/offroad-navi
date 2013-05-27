#ifndef __RoBuffer_h__
#define __RoBuffer_h__

#include "RoFile.h"

class CRoBuffer {
public:
    CRoBuffer  ( int iSize = 0 ) : _iAllocSize (0), _iSize (0), _pBuf (NULL){ Alloc ( iSize ); }
    ~CRoBuffer (){ Release (); }

    char *Alloc  ( int iSize );
    void Release ();
    char *Pointer (){ return _pBuf; }

    int Size (){ return _iSize; }
    char& operator[]( int iIdx ){ return _pBuf [ iIdx ]; }

    void  LoadFile ( LPCTSTR sPathName, int iOffset = 0, int iSize = 0 );

protected:
    char *_pBuf;
    int   _iSize;
    int   _iAllocSize;
};

template <class Type>
class CRoBufferT : public CRoBuffer {
public:
    CRoBufferT ( int iSize = 0 ) : _iSizeT(0), CRoBuffer ( iSize * sizeof ( Type )){ Alloc ( iSize ); }
    Type *Alloc ( int iSize )
    {
        _pBufT = (Type *) CRoBuffer::Alloc ( iSize * sizeof ( Type ));
        _iSizeT = _pBufT ? iSize : 0;
        return _pBufT;
    }

    Type& operator[]( int iIdx ){ return Buf ()[ iIdx ]; }
    int Size (){ return _iSizeT; };
    int BufSize (){ return _iSizeT * sizeof ( Type ); }
    Type *Buf (){ return (Type *) _pBuf; };
    int Save ( CRoFile& file )
    {
        file.Write (( BYTE *) &_iSizeT, sizeof(int));
        if ( _iSizeT )
        {
            file.Write ( _pBuf, BufSize ());
            return ( sizeof ( int ) + BufSize ());
        }

        return sizeof ( int );
    }
    void Restore ( CRoFile& file )
    {
        file.Read (( BYTE *) &_iSizeT, sizeof(int));
        if ( _iSizeT )
        {
            Alloc ( _iSizeT );
            file.Read ( _pBufT, BufSize()); 
        }
    }
    void SaveOffset ( CRoFile& file, Type *pBuf ){ int iOffset = pBuf - _pBufT; file.Write (( BYTE *) &iOffset, sizeof(int)); }
    Type *RestoreOffset ( CRoFile& file ){ int iOffset; file.Read (( BYTE *) &iOffset, sizeof(int));  return ( _pBufT + iOffset ); }
    void Clear (){ if ( _pBufT ) memset ( _pBufT, 0, BufSize ()); }
    void Empty (){ _iSizeT = 0; }
    void AdjustSize ( int iSize ){ if ( iSize < _iSizeT ) _iSizeT = iSize; }

protected:
    Type *_pBufT;
    int   _iSizeT;
};

#ifdef _WIN32_WCE
template <class Type>
class CRoBufferT2D : public CRoBufferT<Type> {
public:
    CRoBufferT2D ( int iRow = 0, int iCol = 0 ) : _iCol(iCol), CRoBufferT<Type> ( iRow * iCol ) {}
    Type& Item ( int iRow, int iCol ){ return _pBufT [ iRow * _iCol + iCol]; }
    Type* Alloc ( int iRow, int iCol ){ CRoBufferT<Type>::Alloc ( iRow * iCol ); _iCol = iCol; return _pBufT; }

protected:
    int _iCol;
};
#endif
#endif
