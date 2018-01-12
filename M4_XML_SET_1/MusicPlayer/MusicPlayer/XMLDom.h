#pragma once

#ifndef __XMLDom_h__
#define __XMLDom_h__

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>

#include <iostream>
#include <string>

using namespace std;
XERCES_CPP_NAMESPACE_USE;

class XMLDom
{
private:
	const char* xmlFile = "./MusicPlayerData.xml";
	DOMDocument* DomDoc;

public:
	XMLDom();
	~XMLDom();
	void createParser();
	DOMDocument* getDomDoc();
};
#endif;
