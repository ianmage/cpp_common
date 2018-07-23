#pragma once

#include "tinyxml2.h"


inline bool CopyNode(tinyxml2::XMLNode *pDstParent, tinyxml2::XMLNode const *pSrcNode);

inline tinyxml2::XMLElement* NewXmlChild(tinyxml2::XMLElement *pNode, char const * name, tinyxml2::XMLDocument *pDoc);

inline void NextElement(tinyxml2::XMLElement* &pElem);


#include "xmlUtil.inl"
