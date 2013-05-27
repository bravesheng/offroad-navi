#ifndef __RoWorkDir_h__
#define __RoWorkDir_h__

#include "RoWin32.h"

class CRoWorkDir {
public:
    CRoWorkDir ( LPCTSTR sWorkDir = TEXT("")){ Set ( sWorkDir ); }
    void Set ( LPCTSTR sWorkDir )
    {
        _tcscpy ( _sWorkDir, sWorkDir );

        int iLen = _tcslen ( _sWorkDir );
        if ( _sWorkDir [ iLen - 1 ] != TCHAR ( '\\' ))
        {
            _sWorkDir [ iLen - 1 ] = TCHAR ( '\\' );
            _sWorkDir [ iLen ] = 0;
        }
    }
    LPCTSTR Get (){ return _sWorkDir; }

protected:
    TCHAR _sWorkDir [ MAX_PATH ];
};

#endif
