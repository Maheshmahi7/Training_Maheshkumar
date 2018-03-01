#pragma once

#ifndef __XMLDom_h__
#define __XMLDom_h__

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>

#ifndef __MSXML_LIBRARY_DEFINED__
#define __MSXML_LIBRARY_DEFINED__
#endif

#include <iostream>
#include <string>
#include "Property.h"

using namespace std;
XERCES_CPP_NAMESPACE_USE;

class XMLDom
{
public:
	static void Instantiate();
	static xercesc_3_2::DOMDocument* getDomDoc();
	static void setDomDoc(xercesc_3_2::DOMDocument* DomDoc);
private:
	XMLDom();
	~XMLDom();
	static bool Instance();
};
#endif;
