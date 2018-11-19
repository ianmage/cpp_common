#pragma once

#include <pugixml.hpp>


//inline bool CopyNode(tinyxml2::XMLNode *pDstParent, tinyxml2::XMLNode const *pSrcNode);

//inline tinyxml2::XMLElement* NewXmlChild(tinyxml2::XMLElement *pNode, char const * name, tinyxml2::XMLDocument *pDoc);

inline pugi::char_t const * GetChildText(pugi::xml_node node, char const * name);

inline pugi::xml_node& NextSiblingNode(pugi::xml_node &node);


#include "xmlUtil.inl"
