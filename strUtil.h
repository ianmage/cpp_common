#pragma once

#include <string>
#include <vector>

constexpr bool StrStartsWith(char const * mainStr, char const * toMatch)
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


inline bool StrStartsWith(std::string const & mainStr, char const * toMatch)
{
	return StrStartsWith(mainStr.c_str(), toMatch);
}

inline bool StrStartsWith(std::string const & mainStr, std::string const & toMatch)
{
	return StrStartsWith(mainStr.c_str(), toMatch.c_str());
}


constexpr uint32_t StrLength(char const * s)
{
	uint32_t ret = 0;
	while (*(s++))
		++ret;
	return ret;
}


constexpr bool StrEndsWith(char const * mainStr, char const * toMatch)
{
	if (!toMatch)
		return true;
	if (!mainStr)
		return false;
	uint32_t const mainLen = StrLength(mainStr);
	uint32_t const matchLen = StrLength(toMatch);
	return mainLen >= matchLen &&
		StrStartsWith(&mainStr[mainLen - matchLen], toMatch);
}


inline bool StrEndsWith(std::string const & mainStr, char const * toMatch)
{
	return StrEndsWith(mainStr.c_str(), toMatch);
}


inline void StrReplace(std::string & src, std::string const & find, std::string const & rep)
{
	for (size_t i = 0; (i = src.find(find, i)) != std::string::npos; i += rep.length())
		src.replace(i, find.length(), rep);
}


inline void StrSplit(std::string const & src, char s, std::vector<std::string> & out)
{
	size_t pos1 = 0;
	size_t len = src.length();
	while (pos1 < len && src[pos1] == s)
		++pos1;
	if (pos1 == std::string::npos)
		return;
	size_t pos2 = src.find(s, pos1);
	while (std::string::npos != pos2) {
		out.emplace_back(src.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		while (pos1 < len && src[pos1] == s)
			++pos1;
		pos2 = src.find(s, pos1);
	}
	if (std::string::npos != pos1)
		out.emplace_back(src.substr(pos1));
}
