#ifndef ROWIN32_H
#define ROWIN32_H

#ifndef _WIN32_WCE
#undef _UNICODE
#undef UNICODE

#include "windows.h"
#include "TCHAR.h"
#else
#include "windows.h"
#endif

#endif // ROWIN32_H
