
inline bool CopyNode(tinyxml2::XMLNode *pDstParent, tinyxml2::XMLNode const *pSrcNode)
{
	// Protect from evil
	if (!pDstParent || !pSrcNode)
		return false;
	// Get the document context where new memory will be allocated from
	tinyxml2::XMLDocument *pDoc = pDstParent->GetDocument();
	// Make the copy
	tinyxml2::XMLNode *pCopy = pSrcNode->ShallowClone(pDoc);
	if (!pCopy)	// Error handling required (e.g. throw)
		return false;
	// Add this child
	pDstParent->InsertEndChild(pCopy);
	// Add the grandkids
	for (auto pNode = pSrcNode->FirstChild(); pNode; pNode = pNode->NextSibling())
		CopyNode(pCopy, pNode);
	return true;
}


inline tinyxml2::XMLElement* NewXmlChild(tinyxml2::XMLElement *pNode, char const * name, tinyxml2::XMLDocument *pDoc)
{
	tinyxml2::XMLElement *pElm = pDoc->NewElement(name);
	pNode->LinkEndChild(pElm);
	return pElm;
}


inline void NextElement(tinyxml2::XMLElement* &pElem)
{
	pElem = pElem->NextSiblingElement(pElem->Name());
}
