#pragma once

#ifndef __XMLDomWritter_h__
#define __XMLDomWritter_h__

#include "XMLDom.h"
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>

#include <sstream>


class XMLDomWritter
{
	DOMDocument* xmlDoc;
public:
	XMLDomWritter(DOMDocument*);
	~XMLDomWritter();
	DOMDocument* addElementSong();
	DOMDocument* addElementAlbum();
	DOMDocument* addElementArtist();
	DOMDocument* createPlaylist();

	void addElementToFile();

};

#endif;