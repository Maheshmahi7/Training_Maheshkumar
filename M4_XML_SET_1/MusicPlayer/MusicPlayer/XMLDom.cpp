#include "XMLDom.h"


XMLDom::XMLDom()
{
}


XMLDom::~XMLDom()
{
}
/*parser method to parse the xml file and store it in local variable*/
void XMLDom::createParser()
{
	XercesDOMParser*   parser = NULL;
	if (!parser)
	{
		parser = new XercesDOMParser();
		parser->parse(xmlFile);
		if (parser){
			DomDoc = parser->adoptDocument();
		}
	}
}

/*method to return the parsed xml file to the called function*/
DOMDocument* XMLDom::getDomDoc(){
	return DomDoc;
}