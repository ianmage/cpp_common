#pragma once

#include <vector>
#include "mathUtil.h"


void splitData(std::string strData, std::vector<float> & data, std::string const & delimit);

void parseBox(std::string const & strData, Box & b);

std::string toString(Vector3 const & v);
std::string toString(Box const & b);
