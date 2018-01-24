#include "DataReader.h"


DataReader::DataReader()
{
}


DataReader::~DataReader()
{
}


void DataReader::displaySongsFromDB(){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	if (SQL_SUCCESS != SQLExecDirect(sqlHandle, (SQLWCHAR*)L"select * from Song order by Song.Name", SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLINTEGER id;
		SQLCHAR name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(sqlHandle) == SQL_SUCCESS){
			SQLGetData(sqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			if (id != 0){
				SQLGetData(sqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);
				displaySongByName((char*)name);
			}
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
}


void DataReader::displaySongByName(char* name){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();

	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;

	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"select distinct song.Name,song.Duration,Artist.Name, Album.Name from Song join Song_Artist on Song.Id = Song_Artist.song_id join Artist on Song_Artist.artist_id = Artist.Id  join Album_Song on Album_Song.song_id = Song.Id join Album on Album_Song.album_id = Album.Id where Song.Name = ? order by Song.Name", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLCHAR sName[50], duration[50], artist_name[50], album_name[50];
		SQLINTEGER ptrSqlVersion;
		SQLFetch(sqlHandle);
		SQLGetData(sqlHandle, 1, SQL_CHAR, sName, 50, &ptrSqlVersion);
		SQLGetData(sqlHandle, 2, SQL_CHAR, duration, 50, &ptrSqlVersion);
		SQLGetData(sqlHandle, 3, SQL_CHAR, artist_name, 50, &ptrSqlVersion);
		SQLGetData(sqlHandle, 4, SQL_CHAR, album_name, 50, &ptrSqlVersion);
		if (_strcmpi(name, (char*)sName) == 0){
			cout << "\nSong:\n\n";
			cout << "***************************************************************" << endl;
			cout << "Name: " << name << endl << "Duration: " << duration << endl;
			cout << "Album:" << endl << '\t' << album_name << endl;
			cout << "Artists:" << endl;
			cout << '\t' << artist_name << endl;
			while (SQLFetch(sqlHandle) == SQL_SUCCESS) {

				SQLGetData(sqlHandle, 3, SQL_CHAR, artist_name, 50, &ptrSqlVersion);

				cout << '\t' << artist_name << endl;
			}
			cout << "***************************************************************" << endl;
		}
		else
		{
			cout << "No songs is found by the entered name" << endl;
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);

}


void DataReader::displayAlbumsFromDB(){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	if (SQL_SUCCESS != SQLExecDirect(sqlHandle, (SQLWCHAR*)L"select * from Album order by Album.name", SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLINTEGER id;
		SQLCHAR name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(sqlHandle) == SQL_SUCCESS){
			SQLGetData(sqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			if (id != 0){
				SQLGetData(sqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);
				displayAlbumByName((char*)name);
			}
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
}


void DataReader::displayAlbumByName(char* name){
	SQLHANDLE sqlHandle = NULL;
	SQLHANDLE sqlHandle1 = NULL;
	sqlHandle = con.createConnection();
	sqlHandle1 = con.createConnection();

	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	SQLINTEGER ptrSqlVersion;

	retcode = SQLPrepare(sqlHandle1, (SQLWCHAR*)L"select distinct Album.Name as album,Song.Name as Song from Album join Album_Song on album.id = Album_Song.album_id join Song on Song.Id = Album_Song.song_id where Album.Name = ? order by album.Name", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle1);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLCHAR aName[50], song_name[50];
		SQLFetch(sqlHandle1);
		SQLGetData(sqlHandle1, 1, SQL_CHAR, aName, 50, &ptrSqlVersion);
		SQLGetData(sqlHandle1, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
		if (_strcmpi(name, (char*)aName) == 0){
			cout << "\nAlbum:\n\n";
			cout << "***************************************************************" << endl;
			cout << "Name: " << aName << endl;
			cout << "Songs:" << endl;
			cout << '\t' << song_name << endl;
			while (SQLFetch(sqlHandle1) == SQL_SUCCESS)
			{
				SQLGetData(sqlHandle1, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
				cout << '\t' << song_name << endl;
			}
		}
		else
		{
			cout << "No Artist is found by the entered name" << endl;
		}
	}

	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"Select distinct Album.Name as album,Artist.Name as Artist from Album join Album_Song on album.id = Album_Song.album_id join Song_Artist on Song_Artist.song_id = Album_Song.song_id join Artist on Artist.Id = Song_Artist.artist_id where Album.Name = ? order by album.Name", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLCHAR aName[50], artist_name[50];
		cout << "Artists:" << endl;
		while (SQLFetch(sqlHandle) == SQL_SUCCESS){
			SQLGetData(sqlHandle, 1, SQL_CHAR, aName, 50, &ptrSqlVersion);
			SQLGetData(sqlHandle, 2, SQL_CHAR, artist_name, 50, &ptrSqlVersion);
			if (_strcmpi(name, (char*)aName) == 0){
				cout << '\t' << artist_name << endl;
			}
			else
			{
				cout << "No Artist is found by the entered name" << endl;
			}
		}
		cout << "***************************************************************" << endl;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
}

void DataReader::displayPlaylistsFromDB(){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	if (SQL_SUCCESS != SQLExecDirect(sqlHandle, (SQLWCHAR*)L"select * from Playlist order by Playlist.Name", SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLINTEGER id;
		SQLCHAR name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(sqlHandle) == SQL_SUCCESS){
			SQLGetData(sqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			SQLGetData(sqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);

			displayPlaylistByName((char*)name);
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
}

void DataReader::displayPlaylistByName(char* name){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();

	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;

	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"select Playlist.Name,Song.Name from Song join Song_Playlist on Song.Id = Song_Playlist.song_id join Playlist on playlist.Id = Song_Playlist.playlist_id where Playlist.Name = ? order by Playlist.Name", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLCHAR pName[50], song_name[50];
		SQLINTEGER ptrSqlVersion;
		SQLFetch(sqlHandle);
		SQLGetData(sqlHandle, 1, SQL_CHAR, pName, 50, &ptrSqlVersion);
		SQLGetData(sqlHandle, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
		if (_strcmpi(name, (char*)pName) == 0){
			cout << "\nPlaylist:\n\n";
			cout << "***************************************************************" << endl;
			cout << "Name: " << name << endl;
			cout << "Songs:" << endl;
			cout << '\t' << song_name << endl;
			while (SQLFetch(sqlHandle) == SQL_SUCCESS) {

				SQLGetData(sqlHandle, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);

				cout << '\t' << song_name << endl;
			}
			cout << "***************************************************************" << endl;
		}
		else
		{
			cout << "No songs is found by the entered name" << endl;
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
}

void DataReader::displayArtistsFromDB(){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	if (SQL_SUCCESS != SQLExecDirect(sqlHandle, (SQLWCHAR*)L"select * from Artist order by Artist.Name", SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLINTEGER id;
		SQLCHAR name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(sqlHandle) == SQL_SUCCESS){
			SQLGetData(sqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			if (id != 0){
				SQLGetData(sqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);
				displayArtistByName((char*)name);
			}
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
}


void DataReader::displayArtistByName(char* name){
	SQLHANDLE sqlHandle = NULL;
	SQLHANDLE sqlHandle1 = NULL;
	sqlHandle = con.createConnection();
	sqlHandle1 = con.createConnection();

	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	SQLINTEGER ptrSqlVersion;

	retcode = SQLPrepare(sqlHandle1, (SQLWCHAR*)L"select distinct Artist.Name as Artist,Song.Name as Song from Artist join Song_Artist on Song_Artist.artist_id = Artist.Id join Song on Song_Artist.song_id = song.Id where Artist.Name = ? order by Artist.Name", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle1);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLCHAR aName[50], song_name[50];
		SQLFetch(sqlHandle1);
		SQLGetData(sqlHandle1, 1, SQL_CHAR, aName, 50, &ptrSqlVersion);
		SQLGetData(sqlHandle1, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
		if (_strcmpi(name, (char*)aName) == 0){
			cout << "\nArtist:\n\n";
			cout << "***************************************************************" << endl;
			cout << "Name: " << aName << endl;
			cout << "Songs:" << endl;
			cout << '\t' << song_name << endl;
			while (SQLFetch(sqlHandle1) == SQL_SUCCESS)
			{
				SQLGetData(sqlHandle1, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
				cout << '\t' << song_name << endl;
			}
		}
		else
		{
			cout << "No Artist is found by the entered name" << endl;
		}
	}

	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"select distinct Artist.Name as Artist, Album.Name as Album from Artist join Song_Artist on Song_Artist.artist_id = Artist.Id join Album_Song on Album_Song.song_id = Song_Artist.song_id join Album on Album.Id = Album_Song.album_id where Artist.Name = ? order by Artist.Name", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLCHAR aName[50], album_name[50];
		cout << "Albums:" << endl;
		while (SQLFetch(sqlHandle) == SQL_SUCCESS){
			SQLGetData(sqlHandle, 1, SQL_CHAR, aName, 50, &ptrSqlVersion);
			SQLGetData(sqlHandle, 2, SQL_CHAR, album_name, 50, &ptrSqlVersion);
			if (_strcmpi(name, (char*)aName) == 0){
				cout << '\t' << album_name << endl;
			}
			else
			{
				cout << "No Artist is found by the entered name" << endl;
			}
		}
		cout << "***************************************************************" << endl;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);

}


