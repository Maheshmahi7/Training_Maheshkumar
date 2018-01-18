#pragma once


#ifndef __XMLDomReader_h__
#define __XMLDomReader_h__

#include "XMLDom.h"


class XMLDomReader
{
	DOMDocument* xmlDoc;
	public:
		XMLDomReader(DOMDocument*);
		~XMLDomReader();
		void displaySongs();
		void displayArtists();
		void displayAlbums();
		void displayPlaylists();
		DOMDocument* createParser(const char*);

	private:
		string getChildValue(const char* parentTag, int parentIndex, const char* childTag, int childIndex);
		string getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex);
		int getRootElementCount(const char* rootElementTag);
		int getChildCount(const char* parentTag, int parentIndex, const char* childTag);
		string getChildByAttribute(const char* parentTag, const char* childTag, const char* attributevalue);
	};

#endif
