#pragma once
#include "connectionDB.h"

class DataReader
{
public:
	DataReader();
	~DataReader();
	void displaySongsFromDB();
	void displaySongByName(char*);

	void displayAlbumsFromDB();
	void displayAlbumByName(char*);

	void displayPlaylistsFromDB();
	void displayPlaylistByName(char*);

	void displayArtistsFromDB();
	void displayArtistByName(char*);
private:
	connectionDB con;

};

