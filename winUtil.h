#pragma once

#include <string>


void ConsoleWriteLn(char const * s, size_t len);
inline void ConsoleWriteLn(std::string const& s) {
	return ConsoleWriteLn(s.c_str(), s.length());
}
