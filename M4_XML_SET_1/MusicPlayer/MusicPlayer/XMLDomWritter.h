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
	void addElementSong();
	void addElementAlbum();
	void addElementArtist();
	void createPlaylist();

private:

	void addElementToFile(DOMDocument* pmyDOMDocument, const wchar_t * FullFilePath);

};

#endif;