#ifndef __RoFile_h__
#define __RoFile_h__

#include "RoFileWin32.h"
class CRoBuffer;

class CRoFile : public CFile {
public:
    CRoFile ( LPCTSTR sPathName = NULL, UINT nOpenFlags = modeRead | shareDenyNone );

    bool IsValid (){ return ( m_hFile != ( UINT ) INVALID_HANDLE_VALUE ); }
    UINT Size (){ return GetLength (); }
    void Seek ( int iOffset ){ CFile::Seek ( iOffset, CFile::begin ); }
    UINT Read ( void* pBuf, UINT nCount ){ return CFile::Read ( pBuf, nCount ); }
    bool ReadSize ( void* pBuf, UINT nCount ){ return ( CFile::Read ( pBuf, nCount ) == nCount ); }

    UINT ReadToBuffer ( CRoBuffer& buf, int iOffset = 0, int iSize = 0 );
    void WriteLine ( LPCTSTR sText ){ Write (( void*) sText, _tcslen ( sText )); Write ( _T("\r\n"), 2 ); }

    static bool IsFileExist ( LPCTSTR sPathName );
    static UINT Read ( LPCTSTR sPathName, void* buf, int iSize )
    {
        CRoFile file ( sPathName );
        return file.CFile::Read ( buf, iSize );
    }
};

class CRoFileWrite : public CRoFile {
public:
    CRoFileWrite ( LPCTSTR sPathName = NULL ) : CRoFile ( sPathName, modeWrite | modeCreate ){}
    bool Open ( LPCTSTR sPathName ){ return CFile::Open ( sPathName, CFile::modeWrite | CFile::modeCreate ); }
};

#endif

