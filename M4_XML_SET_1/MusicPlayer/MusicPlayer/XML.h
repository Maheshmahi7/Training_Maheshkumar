#pragma once

#ifndef __XML_h__
#define __XML_h__

//#include <xercesc/util/PlatformUtils.hpp>
//#include <xercesc/parsers/XercesDOMParser.hpp>
//#include <xercesc/dom/DOM.hpp>
//#include <xercesc/util/XMLString.hpp>

#include <iostream>
#include <string>
#include "XMLDom.h"
#include "XMLDomReader.h"
#include "XMLDomWritter.h"


using namespace std;

class XML
{
public:
	XML();
	~XML();
	void userUI();
private:
	void menu();
	void readMenu();
	void writeMenu();
	int checkUserInput();
	XMLDom* Dom;
	DOMDocument* DomDoc;

};
#endif;
