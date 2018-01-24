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

	string deleteAlbumSongBySong(int);
	string deleteSongArtistBySong(int);
	string deleteSongPlaylistBySong(int);
	string deleteAlbumSongByAlbum(int);
	string deleteSongArtistByArtist(int);
	string deleteSongPlaylistByPlaylist(int);

};

