#include "XMLDom.h"


XMLDom::XMLDom()
{
}


XMLDom::~XMLDom()
{
}

void XMLDom::createParser()
{
	XercesDOMParser*   parser = NULL;
	if (!parser)
	{
		parser = new XercesDOMParser();
		parser->parse(xmlFile);
		DomDoc = parser->adoptDocument();
	}
}

DOMDocument* XMLDom::getDomDoc(){
	return DomDoc;
}