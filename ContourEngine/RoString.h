#ifndef __RoString_h__
#define __RoString_h__

#include "RoWin32.h"

class CString {
public:
	CString (){ _str [ 0 ] = 0; }

	void Format ( LPCTSTR fmt, ... )
	{
		va_list ap;
		va_start ( ap, fmt );
		_vstprintf ( _str, fmt, ap );
		va_end ( ap );
	}
	operator LPCTSTR (){ return _str; }
	operator QString (){
		char str [ 1024 ];
		TCHAR *pS = _str;
		char  *pD = str;
		while ( *pS )
			*pD++ = ( char ) *pS++;
		*pD = 0;
		return QString ( str ); 
	}

protected:
	TCHAR _str[1024];
};

#endif
