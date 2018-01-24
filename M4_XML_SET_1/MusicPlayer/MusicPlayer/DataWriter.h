#pragma once
#include "connectionDB.h"

class DataWriter
{
public:
	DataWriter();
	~DataWriter();

	string insertIntoSongIntoDB();
	string insertIntoAlbumIntoDB();
	string insertIntoPlaylistIntoDB();
	string insertIntoArtistIntoDB();



private:
	connectionDB con;
	string insertIntoAlbumSongs(char*, char*);
	string insertIntoSongArtist(char*, char*);
	string insertIntoSongPlaylist(char*, char*);
	int getSongIdByname(char*);
	int getArtistIdByname(char*);
	int getAlbumIdByname(char*);
	int getPlaylistIdByname(char*);
	int checkUserInput();
	string insertIntoSongIntoDB(char*);
	string insertIntoAlbumIntoDB(char*);
	string insertIntoArtistIntoDB(char*);
};

