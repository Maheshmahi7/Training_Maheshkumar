#pragma once

#ifndef __XMLDomWritter_h__
#define __XMLDomWritter_h__

#include "XMLDom.h"
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>

#include <sstream>


class XMLDomWritter
{
public:
	XMLDomWritter(DOMDocument*);
	~XMLDomWritter();
	DOMDocument* addElementSong();
	DOMDocument* addElementAlbum();
	DOMDocument* addElementArtist();
	DOMDocument* createPlaylist();

	void addElementToFile();

private:
	DOMDocument* xmlDoc;
	int checkUserInput();
	string getChildByName(const char* parentTag, const char* childTag, const char* childValue);
	int getID(const char* parentTag, const char* childTag);
	string setId(const char* parentTag, const char* childTag);

};

#endif;