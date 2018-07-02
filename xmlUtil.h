#pragma once

#include "tinyxml2.h"


bool CopyNode(tinyxml2::XMLNode *pDstParent, tinyxml2::XMLNode const *pSrcNode);

tinyxml2::XMLElement* newXmlChild(tinyxml2::XMLElement *pNode, char const * name, tinyxml2::XMLDocument *pDoc);
