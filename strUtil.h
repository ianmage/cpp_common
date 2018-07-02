#pragma once

#include <string>


bool startsWith(std::string const & mainStr, std::string const & toMatch);
bool endsWith(std::string const & mainStr, std::string const & toMatch);

void replace(std::string & src, std::string const & find, std::string const & rep);

