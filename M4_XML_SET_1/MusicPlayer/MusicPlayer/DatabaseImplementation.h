#pragma once
#include "DatabaseConnection.h"
#include "UserInterface.h"
#include <vector>

using namespace std;

class DatabaseImplementation:public UserInterface
{
public:
	DatabaseImplementation();
	~DatabaseImplementation();

	void displaySongs();
	void displayAlbums();
	void displayPlaylists();
	void displayArtists();

	string insertSong();
	string insertAlbum();
	string insertPlaylist();
	string insertArtist();

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
	string result(SQLRETURN, SQLHANDLE, string);
	int getId(SQLRETURN, SQLHANDLE);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query,char* name);

	void displaySongByName(vector<string>);
	void displayAlbumByName(vector<string>);
	void displayPlaylistByName(vector<string>);
	void displayArtistByName(vector<string>);

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

