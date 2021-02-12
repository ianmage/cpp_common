#pragma once

#include "winUtil.h"
#ifdef WIN32
#define _X86_
#else
#define _AMD64_
#endif
#include <debugapi.h>


void ConsoleWriteLn(char const * s, size_t len)
{
	size_t retVal;
#ifdef UNICODE
	std::wstring wc(len + 1, L'\n');
	mbstowcs_s(&retVal, &wc[0], wc.size(), s, len);
	::OutputDebugString(wc.c_str());
#else
	std::string c(len + 1, L'\n');
	strcpy(&c[0], s);
	c[len] = '\n';
	::OutputDebugString(c.c_str());
#endif
}
