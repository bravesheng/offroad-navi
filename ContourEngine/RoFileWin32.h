#ifndef __RoFileWin32_h__
#define __RoFileWin32_h__

#include "RoString.h"

class CFile {
public:
    CFile () : _hFile ( INVALID_HANDLE_VALUE ){ m_hFile = (UINT) INVALID_HANDLE_VALUE; }
    ~CFile (){ Close (); }

	enum
	{
		modeRead = 1,
		modeWrite = 2,
		modeCreate = 4,
		shareDenyNone = 8
	};

	enum
	{
		begin
	};

	UINT GetLength (){ return 0; }
	void Seek ( int iOffset, int iType );
	UINT Read ( void* pBuf, UINT nCount );
        void Write ( const void* /* pBuf */, UINT /* nCount */){}
	bool Open ( LPCTSTR sPathName, int iMode);

protected:
    void Close ();

    HANDLE  _hFile;
	UINT    m_hFile;
};

#endif
