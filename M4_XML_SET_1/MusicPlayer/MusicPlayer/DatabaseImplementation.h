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
	string result(SQLHANDLE, string);
	int getId(SQLHANDLE);
	int checkUserInput();

	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query,char* name);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query, char* name1, char* name2);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query, char* name, int age);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query, char* name1, int age, char* name2);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query, int id1);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query, int id1, int id2);

	vector<string> getSongs();
	vector<string> getAlbums();
	vector<string> getPlaylists();
	vector<string> getArtists();

	void displaySongByName(char* name);
	void displayAlbumsSongByName(char* name);
	void displayAlbumsArtistByName(char* name);
	void displayPlaylistByName(char* name);
	void displayArtistsAlbumByName(char* name);
	void displayArtistsSongByName(char* name);

	string insertIntoAlbumSongs(char*, char*);
	string insertIntoSongArtist(char*, char*);
	string insertIntoSongPlaylist(char*, char*);

	int getSongIdByname(char*);
	int getArtistIdByname(char*);
	int getAlbumIdByname(char*);
	int getPlaylistIdByname(char*);

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

