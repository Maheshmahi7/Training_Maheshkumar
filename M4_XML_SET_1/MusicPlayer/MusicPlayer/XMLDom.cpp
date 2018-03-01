#include "XMLDom.h"

static XMLDom* xmlDom;
xercesc_3_2::DOMDocument* DomDoc;
XMLDom::XMLDom()
{
}


XMLDom::~XMLDom()
{
	if (xmlDom)
	{
		delete xmlDom;
	}
	xmlDom = NULL;
}

/*parser method to parse the xml file and store it in local variable*/

void XMLDom::Instantiate()
{
	if (xmlDom == NULL)
	{
		xmlDom = new XMLDom();
		XercesDOMParser*   parser = NULL;
		if (!parser)
		{
			parser = new XercesDOMParser();
			parser->parse(XML_FILE);
			if (parser){
				DomDoc = parser->adoptDocument();
			}
		}
	}
}

bool XMLDom::Instance()
{
	bool instance = true;
	if (xmlDom == NULL)
	{
		instance = false;
	}
	return instance;
}

void XMLDom::setDomDoc(DOMDocument* Doc)
{
	if (Instance())
	{
		DomDoc = Doc;
	}
}


/*method to return the parsed xml file to the called function*/
DOMDocument* XMLDom::getDomDoc(){
	DOMDocument* instance = NULL;
	if (Instance())
	{
		instance = DomDoc;
	}
	return instance;
}