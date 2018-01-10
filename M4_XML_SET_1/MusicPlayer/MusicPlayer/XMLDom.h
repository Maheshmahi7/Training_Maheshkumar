#pragma once


#ifndef __XmlDom_h__
#define __XmlDom_h__

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>

#include <string>

using namespace std;
XERCES_CPP_NAMESPACE_USE;


class XMLDom
{
	DOMDocument* m_doc;

	public:
		XMLDom(const char* xmlfile);
		~XMLDom();

		string getChildValue(const char* parentTag, int parentIndex, const char* childTag, int childIndex);
		string getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex,
			const char* attributeTag);
		int getRootElementCount(const char* rootElementTag);
		int getChildCount(const char* parentTag, int parentIndex, const char* childTag);

	private:
		XMLDom();
		XMLDom(const XMLDom&);
	};

#endif
