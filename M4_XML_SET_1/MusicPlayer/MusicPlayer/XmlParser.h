#pragma once


#ifndef __XMLDomReader_h__
#define __XMLDomReader_h__

#include "XMLDom.h"
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <sstream>
#include "UserInterface.h"


class XmlParser :public UserInterface
{
	public:
		XmlParser();
		~XmlParser();
		
		void displaySongs();
		void displayArtists();
		void displayAlbums();
		void displayPlaylists();

		string insertSong();
		string insertAlbum();
		string insertArtist();
		string insertPlaylist();

		static void addElementToFile();

		string updateSongName();
		string updateSongDuration();
		string updateAlbum();
		string updatePlaylist();
		string updateArtistName();
		string updateArtistAge();
		string updateArtistEmailId();

		string deleteSong();
		string deleteAlbum();
		string deleteArtist();
		string deletePlaylist();

	private:
		string getChildValue(const char* parentTag, int parentIndex, const char* childTag, int childIndex);
		string getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex);
		int getRootElementCount(const char* rootElementTag);
		int getChildCount(const char* parentTag, int parentIndex, const char* childTag);
		string getChildByAttribute(const char* parentTag, const char* childTag, const char* attributevalue);
		int checkUserInput();
		string getChildByName(const char* parentTag, const char* childTag, const char* childValue);
		int getID(const char* parentTag, const char* childTag);
		string setId(const char* parentTag, const char* childTag);
	};

#endif
