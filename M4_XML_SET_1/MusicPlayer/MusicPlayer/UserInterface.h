#pragma once

#include <iostream>
#include <string>

using namespace std;

class UserInterface
{
public:
	virtual void displaySongs() = 0;
	virtual void displayAlbums() = 0;
	virtual void displayPlaylists() = 0;
	virtual void displayArtists() = 0;

	virtual string insertSong() = 0;
	virtual string insertAlbum() = 0;
	virtual string insertPlaylist() = 0;
	virtual string insertArtist() = 0;

	virtual string updateSongName() = 0;
	virtual string updateSongDuration() = 0;
	virtual string updateAlbum() = 0;
	virtual string updatePlaylist() = 0;
	virtual string updateArtistName() = 0;
	virtual string updateArtistAge() = 0;
	virtual string updateArtistEmailId() = 0;

	virtual string deleteSong() = 0;
	virtual string deleteAlbum() = 0;
	virtual string deleteArtist() = 0;
	virtual string deletePlaylist() = 0;
};

