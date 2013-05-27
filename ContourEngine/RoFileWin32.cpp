#include "stdafx.h"
#include "RoFileWin32.h"

void CFile :: Close ()
{
    if ( _hFile == INVALID_HANDLE_VALUE )
        return;

    ::CloseHandle ( _hFile );
    _hFile = INVALID_HANDLE_VALUE;
    m_hFile = (UINT) INVALID_HANDLE_VALUE;
}

bool CFile :: Open ( LPCTSTR sPathName, int iMode)
{
    Close ();

    _hFile = ::CreateFile ( sPathName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    m_hFile = (UINT) _hFile;

	return ( _hFile != INVALID_HANDLE_VALUE );
}

void CFile :: Seek ( int iOffset, int iType )
{
    if ( _hFile == INVALID_HANDLE_VALUE )
        return;

    ::SetFilePointer ( _hFile, iOffset, 0, FILE_BEGIN );
}

UINT CFile :: Read ( void* pBuf, UINT nCount )
{
    if ( _hFile == INVALID_HANDLE_VALUE )
        return 0;

    DWORD dwReaded;
    ::ReadFile ( _hFile, pBuf, nCount, &dwReaded, NULL );

    return dwReaded;
}
