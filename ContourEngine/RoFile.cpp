#include "stdafx.h"
#include "RoFile.h"

#if 0
void CRoFile :: SetPathName ( const TCHAR *sPathName )
{
    if ( sPathName )
        _tcsncpy ( _sPathName, sPathName, MAX_PATH );
    else
        _sPathName [ 0 ]  = 0;
}

bool CRoFile :: Open ( int iMode )
{
    Close ();

    switch ( iMode ) {
    case modeRead:
        _hFile = ::CreateFile ( _sPathName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

        if ( IsValid ())
        {
            _iSize = (int) ::GetFileSize ( _hFile, NULL );

            if ( _iSize == 0xFFFFFFFF )
                _iSize = 0;
        }
        break;

    case modeWrite:
        _hFile = ::CreateFile ( _sPathName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
        _iSize = 0;
        break;
    }

    _iMode = iMode;
    return IsValid ();
}

int CRoFile :: Read ( void *buf, int iSize )
{
    if ( _iMode != modeRead )
        return 0;

    DWORD dwReaded=0;
    ::ReadFile ( _hFile, buf, iSize, &dwReaded, NULL );

    return (int) dwReaded;
}

int CRoFile :: Write ( void *buf, int iSize )
{
    if ( _iMode != modeWrite )
        return 0;

    DWORD dwWrited=0;
    ::WriteFile ( _hFile, buf, iSize, &dwWrited, NULL );

    return (int) dwWrited;
}


void CRoFile :: ChangeSubName ( LPCTSTR sSubName )
{
    TCHAR *sDot = _tcsrchr ( _sPathName, _T('.'));
    TCHAR *sDir = _tcsrchr ( _sPathName, _T('\\'));

    if ( sDot > sDir )
        _tcscpy ( sDot + 1, sSubName );
    else
    {
        _tcscat ( _sPathName, "." );
        _tcscat ( _sPathName, sSubName );
    }
}
#endif

CRoFile :: CRoFile ( LPCTSTR sPathName, UINT nOpenFlags )
{
    if ( sPathName == NULL )
        return;

    try
    {
        Open ( sPathName, nOpenFlags );
    }
    catch ( ... )
    {
    }
}

bool CRoFile :: IsFileExist ( LPCTSTR sPathName )
{
	WIN32_FIND_DATA FindFileData;
    HANDLE hFind = FindFirstFile ( sPathName, &FindFileData );

    if ( hFind == INVALID_HANDLE_VALUE )
        return false;

    FindClose ( hFind );
    return true;
}

#include "RoBuffer.h"
UINT CRoFile :: ReadToBuffer ( CRoBuffer& buf, int iOffset, int iSize )
{
    int iFileSize = GetLength ();
    if ( iFileSize == 0 )
        return 0;

    if (( iSize > iFileSize ) || ( iSize == 0 ))
        iSize = iFileSize;

    if ( iOffset )
        Seek ( iOffset );

    buf.Alloc ( iSize );

    return CFile::Read ( buf.Pointer (), iSize );
}
