#include "mResUtil.h"
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <set>
#include <iomanip>


void splitData(std::string strData, std::vector<float> & data, std::string const & delimit)
{
	if (strData[0]=='(' || strData[0]=='{')
		strData = strData.substr(1, strData.length() - 2);
	std::vector<std::string> tv;
	boost::split(tv, strData, boost::is_any_of(delimit));
	for (std::string const & sd : tv)
		data.push_back(std::stof(sd));
}


void parseBox(std::string const & strData, Box & b)
{
	std::string subStrData{ strData.substr(1, strData.length() - 2) };
	std::vector<std::string> tv;
	boost::split(tv, subStrData, boost::is_any_of(","));
	assert(tv.size() == 6);
	b.bMin.Set(std::stof(tv[0]), std::stof(tv[1]), std::stof(tv[2]));
	b.bMax.Set(std::stof(tv[3]), std::stof(tv[4]), std::stof(tv[5]));
}


std::string toString(Vector3 const & v)
{
	std::ostringstream buf;
	buf << std::setprecision(5);
	buf << "(" << v.x << "," << v.y << "," << v.z << ")";
	return buf.str();
}

std::string toString(Box const & b)
{
	std::ostringstream buf;
	buf << std::setprecision(5);
	buf << "(" << b.bMin.x << "," << b.bMin.y << "," << b.bMin.z << ","
		<< b.bMax.x << "," << b.bMax.y << "," << b.bMax.z << ")";
	return buf.str();
}
