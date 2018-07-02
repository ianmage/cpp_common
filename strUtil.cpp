#include "strUtil.h"


bool startsWith(std::string const & mainStr, std::string const & toMatch)
{
	if (mainStr.length() >= toMatch.length())
		return 0 == mainStr.compare(0, toMatch.length(), toMatch);
	return false;
}


bool endsWith(std::string const & mainStr, std::string const & toMatch)
{
	if (mainStr.length() >= toMatch.length())
		return 0 == mainStr.compare(mainStr.length() - toMatch.length(), toMatch.length(), toMatch);
	return false;
}


void replace(std::string & src, std::string const & find, std::string const & rep)
{
	for (size_t i = 0; (i = src.find(find, i)) != std::string::npos; i += rep.length())
		src.replace(i, find.length(), rep);
}
