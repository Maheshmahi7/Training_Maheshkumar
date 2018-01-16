#include "XMLDom.h"


XMLDom::XMLDom()
{
}


XMLDom::~XMLDom()
{
	DomDoc->release();
	delete xmlFile;
}
/*parser method to parse the xml file and store it in local variable*/
void XMLDom::createParser()
{
	XercesDOMParser*   parser = NULL;
	if (!parser)
	{
		parser = new XercesDOMParser();
		parser->parse(xmlFile);
		DomDoc = parser->adoptDocument();
	}
	delete parser;
}

/*method to return the parsed xml file to the called function*/
DOMDocument* XMLDom::getDomDoc(){
	return DomDoc;
}