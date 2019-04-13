#pragma once

#include "winUtil.h"
#include <string>
#define _AMD64_
#include <debugapi.h>


void ConsoleWriteLn(char const * s, size_t len)
{
#ifdef UNICODE
	std::wstring wc(len + 1, L'\n');
	mbstowcs(&wc[0], s, len);
	::OutputDebugString(wc.c_str());
#else
	std::string c(len + 1, L'\n');
	strcpy(&c[0], s);
	c[len] = '\n';
	::OutputDebugString(c.c_str());
#endif
}
