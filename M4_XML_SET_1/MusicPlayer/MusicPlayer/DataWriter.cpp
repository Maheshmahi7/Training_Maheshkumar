#include "DataWriter.h"
#include<iostream>


DataWriter::DataWriter()
{
}


DataWriter::~DataWriter()
{
}

string DataWriter::insertIntoSongIntoDB(){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	string result;
	SQLRETURN retcode;
	SQLCHAR sqlName[50], sqlDuration[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	char* duration = new char();
	char* album = new char();
	cin.get();
	cout << "Enter the Song Name:" << endl;
	cin.getline(name, 50);
	cout << "Enter the Song Duration:" << endl;
	cin.getline(duration, 50);
	cout << "Enter the Album name:" << endl;
	cin.getline(album, 50);
	cout << endl;
	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO SONG(NAME,DURATION) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(duration), 0, sqlDuration, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlDuration, _countof(sqlDuration), duration);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion failed";
	}
	else {
		int temp;
		char* artistName = new char();
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		if (rowCount > 0){
			result = insertIntoAlbumSongs(album, name);
			cout << "Enter No of Artist Contributed" << endl;
			cin >> temp;
			if (cin.fail()){
				temp = checkUserInput();
			}
			cin.get();
			for (int i = 0; i < temp; i++){
				cout << "Enter the " << i + 1 << " Artist name:" << endl;
				cin.getline(artistName, 50);
				result = insertIntoSongArtist(artistName, name);
			}
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return result;
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Insertion Failed";
		}
	}
}

string DataWriter::insertIntoSongIntoDB(char* name){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	string result;
	SQLRETURN retcode;
	SQLCHAR sqlName[50], sqlDuration[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* duration = new char();
	cin.get();
	cout << "Enter the Song Duration:" << endl;
	cin.getline(duration, 50);
	cout << endl;
	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO SONG(NAME,DURATION) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(duration), 0, sqlDuration, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlDuration, _countof(sqlDuration), duration);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion Failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		if (rowCount > 0){
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Inserted Successfully";
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Insertion Failed";
		}

	}
}

string DataWriter::insertIntoAlbumIntoDB(){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	cin.get();
	cout << "Enter the Album Name:" << endl;
	cin.getline(name, 50);
	cout << endl;
	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO ALBUM(NAME) VALUES(?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		string result;
		if (rowCount > 0){
			int temp;
			char *albumSong = new char();
			cout << "Enter the number Songs in the Album" << endl;
			cin >> temp;
			if (cin.fail()){
				temp = checkUserInput();
			}
			cin.get();
			for (int i = 0; i < temp; i++){
				cout << "Enter the " << i + 1 << " Song Name" << endl;
				cin.getline(albumSong, 50);
				result = insertIntoAlbumSongs(name, albumSong);
			}
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return result;
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Insertion failed";
		}
	}
}

string DataWriter::insertIntoAlbumIntoDB(char* name){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO ALBUM(NAME) VALUES(?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion failed ";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		if (rowCount > 0){
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Inserted successfully";
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Insertion Failed";
		}

	}
}

string DataWriter::insertIntoArtistIntoDB(){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	SQLRETURN retcode;
	SQLCHAR sqlName[50], sqlAge[50], sqlEmailId[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	char* age = new char();
	char* emailId = new char();
	cin.get();
	cout << "Enter the Artist Name:" << endl;
	cin.getline(name, 50);
	cout << "Enter the Artist Age:" << endl;
	cin.getline(age, 50);
	cout << "Enter the Artist Email Id" << endl;
	cin.getline(emailId, 50);
	cout << endl;
	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO ARTIST(NAME,AGE,EMAIL_ID) VALUES(?,?,?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(age), 0, sqlAge, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(emailId), 0, sqlEmailId, 0, &cbValue);
	cout << strlen(name) << endl << strlen(age) << endl << strlen(emailId) << endl;
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlAge, _countof(sqlAge), age);
	strcpy_s((char*)sqlEmailId, _countof(sqlEmailId), emailId);
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion Failed\n";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		string result;
		if (rowCount > 0){
			int temp;
			char* artistSong = new char();
			cout << "Enter No of Songs Contributed" << endl;
			cin >> temp;
			if (cin.fail()){
				temp = checkUserInput();
			}
			cin.get();
			for (int i = 0; i < temp; i++){
				cout << "Enter the " << i + 1 << " Song name:" << endl;
				cin.getline(artistSong, 50);
				result = insertIntoSongArtist(name, artistSong);
			}
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return result;
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Insertion Failed";
		}
	}
}

string DataWriter::insertIntoArtistIntoDB(char* name){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	SQLRETURN retcode;
	SQLCHAR sqlName[50], sqlAge[50], sqlEmailId[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* age = new char();
	char* emailId = new char();
	cin.get();
	cout << "Enter the Artist Age:" << endl;
	cin.getline(age, 50);
	cout << "Enter the Artist Email Id" << endl;
	cin.getline(emailId, 50);
	cout << endl;
	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO ARTIST(NAME,AGE,EMAIL_ID) VALUES(?,?,?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(age), 0, sqlAge, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(emailId), 0, sqlEmailId, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlAge, _countof(sqlAge), age);
	strcpy_s((char*)sqlEmailId, _countof(sqlEmailId), emailId);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion Failed\n";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		if (rowCount > 0){
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Inserted Successfully";
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Insertion Failed";
		}

	}
}

string DataWriter::insertIntoPlaylistIntoDB(){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	string result, input;
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	cin.get();
	cout << "Enter the Playlist Name:" << endl;
	getline(cin, input);
	strcpy(name, input.c_str());
	cout << endl;
	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO PLAYLIST(NAME) VALUES(?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		if (rowCount > 0){
			int temp;
			string temp1;
			char* songName = new char();
			cout << "Enter the Number of Songs to add in the Playlist:" << endl;
			cin >> temp;
			if (cin.fail()){
				temp = checkUserInput();
			}

			cin.get();
			for (int i = 0; i < temp; i++){
				cout << "Enter the " << i << " Song Name" << endl;
				getline(cin, temp1);
				strcpy(songName, temp1.c_str());
				result = insertIntoSongPlaylist(name, songName);
				cout << result << endl;
				if (result.compare("Insertion failed") == 0){
					i--;
				}
			}
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return result;
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Insertion Failed";
		}
	}
}

int DataWriter::getSongIdByname(char* name){
	SQLHANDLE sqlHandle1 = NULL;
	sqlHandle1 = con.createConnection();
	SQLINTEGER ptrSqlVersion, songId;
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	retcode = SQLPrepare(sqlHandle1, (SQLWCHAR*)L"select song.id from Song where Song.Name = ?", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle1);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
		return -1;
	}
	else {
		while (SQLFetch(sqlHandle1) == SQL_SUCCESS){
			SQLGetData(sqlHandle1, 1, SQL_INTEGER, &songId, 0, &ptrSqlVersion);
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
	return songId;
}

int DataWriter::getAlbumIdByname(char* name){
	SQLHANDLE sqlHandle1 = NULL;
	sqlHandle1 = con.createConnection();
	SQLINTEGER ptrSqlVersion;
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	SQLINTEGER albumId;
	retcode = SQLPrepare(sqlHandle1, (SQLWCHAR*)L"select album.id from Album where Album.Name= ?", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle1);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
		return -1;
	}
	else {
		SQLFetch(sqlHandle1);
		SQLGetData(sqlHandle1, 1, SQL_INTEGER, &albumId, 0, &ptrSqlVersion);
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
	return albumId;
}

int DataWriter::getArtistIdByname(char* name){
	SQLHANDLE sqlHandle1 = NULL;
	sqlHandle1 = con.createConnection();
	SQLINTEGER ptrSqlVersion;
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	SQLINTEGER artistId;
	retcode = SQLPrepare(sqlHandle1, (SQLWCHAR*)L"SELECT artist.id FROM ARTIST WHERE ARTIST.NAME= ?", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle1);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
		cout << "\n";
		return -1;
	}
	else {
		SQLFetch(sqlHandle1);
		SQLGetData(sqlHandle1, 1, SQL_INTEGER, &artistId, 0, &ptrSqlVersion);
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
	return artistId;
}

int DataWriter::getPlaylistIdByname(char* name){
	SQLHANDLE sqlHandle1 = NULL;
	sqlHandle1 = con.createConnection();
	SQLINTEGER ptrSqlVersion;
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	SQLINTEGER playlistId;
	retcode = SQLPrepare(sqlHandle1, (SQLWCHAR*)L"SELECT playlist.id FROM PLAYLIST WHERE PLAYLIST.NAME= ?", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(sqlHandle1);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
		return -1;
	}
	else {
		SQLFetch(sqlHandle1);
		SQLGetData(sqlHandle1, 1, SQL_INTEGER, &playlistId, 0, &ptrSqlVersion);
	}
	SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle1);
	return playlistId;
}


string DataWriter::insertIntoAlbumSongs(char* albumName, char* songName){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	string result;
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS;
	SQLINTEGER songId, albumId, sqlSong, sqlAlbum;
	songId = getSongIdByname(songName);
	if (songId < -1){
		int choice;
		cout << "Song is Not avilable" << endl;
		cout << "1.Create new Song" << endl;
		cout << "2.No Song" << endl;
		cin >> choice;
		if (cin.fail()){
			choice = checkUserInput();
		}
		if (choice == 1){
			result = insertIntoSongIntoDB(songName);
			songId = getSongIdByname(songName);
			cout << result << endl;
		}
		else{
			cout << "You selected No Song" << endl;
			songId = getSongIdByname("None");
		}
	}
	albumId = getAlbumIdByname(albumName);
	if (albumId < -1){
		int choice;
		cout << "Album is Not avilable" << endl;
		cout << "1.Create new Album" << endl;
		cout << "2.No Album Name" << endl;
		cin >> choice;
		if (cin.fail()){
			choice = checkUserInput();
		}
		if (choice == 1){
			result = insertIntoAlbumIntoDB(albumName);
			albumId = getAlbumIdByname(albumName);
			cout << result << endl;
		}
		else{
			cout << "You selected No album" << endl;
			albumId = getAlbumIdByname("None");
		}
	}
	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO ALBUM_SONG(SONG_ID,ALBUM_ID) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlSong, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlAlbum, 0, &cbValue);
	sqlSong = songId;
	sqlAlbum = albumId;
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		if (rowCount > 0){
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Inserted Successfully\n";
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
			return "Insertion failed\n";
		}
	}

}


string DataWriter::insertIntoSongPlaylist(char* playlistName, char*songName){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	string result;
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS;
	SQLINTEGER songId, playlistId, sqlSong, sqlPlaylist;
	do{
		songId = getSongIdByname(songName);
		if (songId < 0){
			cout << "Song is Not avilable" << endl;
			return "Insertion failed";
		}
	} while (songId < 0);
	playlistId = getPlaylistIdByname(playlistName);

	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO SONG_PLAYLIST(PLAYLIST_ID,SONG_ID) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlPlaylist, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlSong, 0, &cbValue);
	sqlSong = songId;
	sqlPlaylist = playlistId;
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion Failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		if (rowCount > 0){
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);

			return "Inserted Successfully\n";
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);

			return "Insertion failed\n";
		}
	}
}

string DataWriter::insertIntoSongArtist(char* artistName, char* songName){
	SQLHANDLE sqlHandle = NULL;
	sqlHandle = con.createConnection();
	string result;
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS;
	SQLINTEGER songId, artistId, sqlSong, sqlArtist;
	songId = getSongIdByname(songName);
	if (songId < -1){
		int choice;
		cout << "Song is Not avilable" << endl;
		cout << "1.Create new Song" << endl;
		cout << "2.No Song" << endl;
		cin >> choice;
		if (cin.fail()){
			choice = checkUserInput();
		}
		if (choice == 1){
			result = insertIntoSongIntoDB(songName);
			songId = getSongIdByname(songName);
			cout << result << endl;
		}
		else{
			cout << "You selected No Song" << endl;
			songId = getSongIdByname("None");
		}
	}
	artistId = getArtistIdByname(artistName);
	if (artistId < -1){
		int choice;
		cout << "Artist is Not avilable" << endl;
		cout << "1.Create new Artist" << endl;
		cout << "2.No Artist" << endl;
		cin >> choice;
		if (cin.fail()){
			choice = checkUserInput();
		}
		if (choice == 1){
			result = insertIntoArtistIntoDB(artistName);
			artistId = getArtistIdByname(artistName);
			cout << result << endl;
		}
		else{
			cout << "You selected No Artist" << endl;
			artistId = getArtistIdByname("None");
		}
	}

	retcode = SQLPrepare(sqlHandle, (SQLWCHAR*)L"INSERT INTO SONG_ARTIST(SONG_ID,ARTIST_ID) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(sqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlSong, 0, &cbValue);
	retcode = SQLBindParameter(sqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlArtist, 0, &cbValue);
	sqlSong = songId;
	sqlArtist = artistId;
	retcode = SQLExecute(sqlHandle);
	if (SQL_SUCCESS != retcode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);
		return "Insertion failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(sqlHandle, &rowCount);
		if (rowCount > 0){
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);

			return "Inserted Successfully\n";
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, sqlHandle);

			return "Insertion failed\n";
		}
	}
}


/*method to validate user input of type integer*/
int DataWriter::checkUserInput() {
	int input;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cin >> input;
		}
		else if (!cin.fail()) {
			return input;
			break;
		}
	}
}