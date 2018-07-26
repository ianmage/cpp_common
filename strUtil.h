#pragma once

#include <string>

constexpr bool strStartsWith(char const * mainStr, char const * toMatch)
{
	if (!toMatch)
		return true;
	if (!mainStr)
		return false;
	int idx = 0;
	bool ret = true;
	while (toMatch[idx]) {
		if (toMatch[idx] != mainStr[idx]) {
			ret = false;
			break;
		}
		++idx;
	}
	return ret;
}


inline bool strStartsWith(std::string const & mainStr, char const * toMatch)
{
	return strStartsWith(mainStr.c_str(), toMatch);
}


constexpr uint32_t StrLength(char const * s)
{
	uint32_t ret = 0;
	while (*(s++))
		++ret;
	return ret;
}


constexpr bool strEndsWith(char const * mainStr, char const * toMatch)
{
	if (!toMatch)
		return true;
	if (!mainStr)
		return false;
	uint32_t const mainLen = StrLength(mainStr);
	uint32_t const matchLen = StrLength(toMatch);
	return mainLen >= matchLen &&
		strStartsWith(&mainStr[mainLen - matchLen], toMatch);
}


inline bool strEndsWith(std::string const & mainStr, char const * toMatch)
{
	return strEndsWith(mainStr.c_str(), toMatch);
}


inline void strReplace(std::string & src, std::string const & find, std::string const & rep)
{
	for (size_t i = 0; (i = src.find(find, i)) != std::string::npos; i += rep.length())
		src.replace(i, find.length(), rep);
}
