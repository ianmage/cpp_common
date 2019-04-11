#pragma once

#include "winUtil.h"
#include <string>
#define _AMD64_
#include <debugapi.h>


void ConsoleWriteLn(char const * s, size_t len)
{
	std::wstring wc(len + 1, L'\n');
	mbstowcs(&wc[0], s, len);
	::OutputDebugString(wc.c_str());
}
