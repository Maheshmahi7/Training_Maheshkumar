#include "DatabaseImplementation.h"


DatabaseImplementation::DatabaseImplementation()
{
	DatabaseConnection::Instantiate();
}


DatabaseImplementation::~DatabaseImplementation()
{
}

SQLHANDLE DatabaseImplementation::select(SQLHANDLE SqlHandle, SQLWCHAR* Query)
{
	return (SQL_SUCCESS != SQLExecDirect(SqlHandle, Query, SQL_NTS)) ? 0 : SqlHandle;
}

SQLHANDLE DatabaseImplementation::select(SQLHANDLE SqlHandle, SQLWCHAR* Query, char* name)
{
	SQLINTEGER cbValue = SQL_NTS;
	SQLRETURN retcode;
	char sqlName[50];
	retcode = SQLPrepare(SqlHandle, Query, SQL_NTS);
	strcpy_s(sqlName, _countof(sqlName), name);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	return (SQL_SUCCESS != SQLExecute(SqlHandle)) ? 0 : SqlHandle;
}

void DatabaseImplementation::displaySongs(){
	vector<string> songName;
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, L"select * from song order by song.name"))){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		SQLINTEGER id;
		char name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(SqlHandle) == SQL_SUCCESS){
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			if (id != 0){
				SQLGetData(SqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);
				songName.push_back(name);
			}
		}
		displaySongByName(songName);
	}
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
}


void DatabaseImplementation::displaySongByName(vector<string> songName){
	char* name;
	int Size = songName.size();
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	for (int i = 0; i < Size; i++)
	{
		name = (char*)songName[i].c_str();
		SQLHANDLE SqlHandle = NULL;
		SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
		if (!(SqlHandle = select(SqlHandle, L"select song.name,song.duration,artist.name, album.name from song join song_artist on song.id = song_artist.song_id join artist on song_artist.artist_id = artist.Id  join album_song on album_song.song_id = song.Id join album on album_song.album_id = album.Id where song.name = ? order by song.name", name))){
			cout << "Error querying SQL Server";
			cout << "\n";
			return;
		}
		else {

			//declare output variable and pointer
			SQLCHAR sName[50], duration[50], artist_name[50], album_name[50];
			SQLINTEGER ptrSqlVersion;
			SQLFetch(SqlHandle);
			SQLGetData(SqlHandle, 1, SQL_CHAR, sName, 50, &ptrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, duration, 50, &ptrSqlVersion);
			SQLGetData(SqlHandle, 3, SQL_CHAR, artist_name, 50, &ptrSqlVersion);
			SQLGetData(SqlHandle, 4, SQL_CHAR, album_name, 50, &ptrSqlVersion);
			if (_strcmpi(name, (char*)sName) == 0){
				cout << "\nSong:\n\n";
				cout << "***************************************************************" << endl;
				cout << "Name: " << sName << endl << "Duration: " << duration << endl;
				cout << "Album:" << endl << '\t' << album_name << endl;
				cout << "Artists:" << endl;
				cout << '\t' << artist_name << endl;
				while (SQLFetch(SqlHandle) == SQL_SUCCESS) {

					SQLGetData(SqlHandle, 3, SQL_CHAR, artist_name, 50, &ptrSqlVersion);

					cout << '\t' << artist_name << endl;
				}
				cout << "***************************************************************" << endl;
			}
			else
			{
				cout << "No songs is found by the entered name" << endl;
			}
		}
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	}
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}


void DatabaseImplementation::displayAlbums(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, L"select * from Album order by Album.name"))){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {

		//declare output variable and pointer
		vector<string> albumName;
		SQLINTEGER id;
		char name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(SqlHandle) == SQL_SUCCESS){
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			if (id != 0){
				SQLGetData(SqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);
				albumName.push_back(name);
			}
		}
		displayAlbumByName(albumName);
	}
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
}


void DatabaseImplementation::displayAlbumByName(vector<string> albumName){
	SQLINTEGER ptrSqlVersion;
	char* name;
	int Size = albumName.size();
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	for (int i = 0; i < Size; i++)
	{
		SQLHANDLE SqlHandle = NULL;
		SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
		name = (char*)albumName[i].c_str();
		if (!(SqlHandle = select(SqlHandle, L"select distinct Album.Name as album,Song.Name as Song from Album join Album_Song on album.id = Album_Song.album_id join Song on Song.Id = Album_Song.song_id where Album.Name = ? order by album.Name", name))){
			cout << "Error querying SQL Server";
			cout << "\n";
			return;
		}
		else {

			//declare output variable and pointer
			SQLCHAR aName[50], song_name[50];
			SQLFetch(SqlHandle);
			SQLGetData(SqlHandle, 1, SQL_CHAR, aName, 50, &ptrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
			if (_strcmpi(name, (char*)aName) == 0){
				cout << "\nAlbum:\n\n";
				cout << "***************************************************************" << endl;
				cout << "Name: " << aName << endl;
				cout << "Songs:" << endl;
				cout << '\t' << song_name << endl;
				while (SQLFetch(SqlHandle) == SQL_SUCCESS)
				{
					SQLGetData(SqlHandle, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
					cout << '\t' << song_name << endl;
				}
			}
			else
			{
				cout << "No Artist is found by the entered name" << endl;
			}
		}
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
		if (!(SqlHandle = select(SqlHandle, L"Select distinct Album.Name as album,Artist.Name as Artist from Album join Album_Song on album.id = Album_Song.album_id join Song_Artist on Song_Artist.song_id = Album_Song.song_id join Artist on Artist.Id = Song_Artist.artist_id where Album.Name = ? order by album.Name", name))){
			cout << "Error querying SQL Server";
			cout << "\n";
			return;
		}
		else {

			//declare output variable and pointer
			SQLCHAR aName[50], artist_name[50];
			cout << "Artists:" << endl;
			while (SQLFetch(SqlHandle) == SQL_SUCCESS){
				SQLGetData(SqlHandle, 1, SQL_CHAR, aName, 50, &ptrSqlVersion);
				SQLGetData(SqlHandle, 2, SQL_CHAR, artist_name, 50, &ptrSqlVersion);
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
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	}
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

void DatabaseImplementation::displayPlaylists(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, L"select * from Playlist order by Playlist.Name"))){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {
		vector<string> playlistName;
		//declare output variable and pointer
		SQLINTEGER id;
		char name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(SqlHandle) == SQL_SUCCESS){
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);
			playlistName.push_back(name);
		}
		displayPlaylistByName(playlistName);
	}
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
}

void DatabaseImplementation::displayPlaylistByName(vector<string> playlistName){
	char* name;
	int Size = playlistName.size();
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	for (int i = 0; i < Size; i++)
	{
		SQLHANDLE SqlHandle = NULL;
		SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
		name = (char*)playlistName[i].c_str();
		if (!(SqlHandle = select(SqlHandle, L"select Playlist.Name,Song.Name from Song join Song_Playlist on Song.Id = Song_Playlist.song_id join Playlist on playlist.Id = Song_Playlist.playlist_id where Playlist.Name = ? order by Playlist.Name", name))){
			cout << "Error querying SQL Server";
			cout << "\n";
			return;
		}
		else {

			//declare output variable and pointer
			SQLCHAR pName[50], song_name[50];
			SQLINTEGER ptrSqlVersion;
			SQLFetch(SqlHandle);
			SQLGetData(SqlHandle, 1, SQL_CHAR, pName, 50, &ptrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
			if (_strcmpi(name, (char*)pName) == 0){
				cout << "\nPlaylist:\n\n";
				cout << "***************************************************************" << endl;
				cout << "Name: " << name << endl;
				cout << "Songs:" << endl;
				cout << '\t' << song_name << endl;
				while (SQLFetch(SqlHandle) == SQL_SUCCESS) {

					SQLGetData(SqlHandle, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);

					cout << '\t' << song_name << endl;
				}
				cout << "***************************************************************" << endl;
			}
			else
			{
				cout << "No songs is found by the entered name" << endl;
			}
		}
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	}
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

void DatabaseImplementation::displayArtists(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, L"select * from Artist order by Artist.Name"))){
		cout << "Error querying SQL Server";
		cout << "\n";
		return;
	}
	else {
		vector<string> artistName;
		//declare output variable and pointer
		SQLINTEGER id;
		char name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(SqlHandle) == SQL_SUCCESS){
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			if (id != 0){
				SQLGetData(SqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);
				artistName.push_back(name);
			}
		}
		displayArtistByName(artistName);
	}
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
}


void DatabaseImplementation::displayArtistByName(vector<string> artistName){
	SQLINTEGER ptrSqlVersion;
	char* name;
	int Size = artistName.size();
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	for (int i = 0; i < Size; i++)
	{
		SQLHANDLE SqlHandle = NULL;
		SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
		name = (char*)artistName[i].c_str();
		if (!(SqlHandle = select(SqlHandle, L"select distinct Artist.Name as Artist,Song.Name as Song from Artist join Song_Artist on Song_Artist.artist_id = Artist.Id join Song on Song_Artist.song_id = song.Id where Artist.Name = ? order by Artist.Name", name))){
			cout << "Error querying SQL Server";
			cout << "\n";
			return;
		}
		else {

			//declare output variable and pointer
			SQLCHAR aName[50], song_name[50];
			while (SQLFetch(SqlHandle) == SQL_SUCCESS){
				SQLGetData(SqlHandle, 1, SQL_CHAR, aName, 50, &ptrSqlVersion);
				SQLGetData(SqlHandle, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
				cout << "\nArtist:\n\n";
				cout << "***************************************************************" << endl;
				cout << "Name: " << aName << endl;
				if (_strcmpi(name, (char*)aName) == 0){
					cout << "Songs:" << endl;
					cout << '\t' << song_name << endl;
					while (SQLFetch(SqlHandle) == SQL_SUCCESS)
					{
						SQLGetData(SqlHandle, 2, SQL_CHAR, song_name, 50, &ptrSqlVersion);
						cout << '\t' << song_name << endl;
					}
				}
				else
				{
					cout << "No Artist is found by the entered name" << endl;
				}
			}
		}

		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
		if (!(SqlHandle = select(SqlHandle, L"select distinct Artist.Name as Artist, Album.Name as Album from Artist join Song_Artist on Song_Artist.artist_id = Artist.Id join Album_Song on Album_Song.song_id = Song_Artist.song_id join Album on Album.Id = Album_Song.album_id where Artist.Name = ? order by Artist.Name", name))){
			cout << "Error querying SQL Server";
			cout << "\n";
			return;
		}
		else {

			//declare output variable and pointer
			SQLCHAR aName[50], album_name[50];
			while (SQLFetch(SqlHandle) == SQL_SUCCESS){
				cout << "Albums:" << endl;
				SQLGetData(SqlHandle, 1, SQL_CHAR, aName, 50, &ptrSqlVersion);
				SQLGetData(SqlHandle, 2, SQL_CHAR, album_name, 50, &ptrSqlVersion);
				cout << '\t' << album_name << endl;
				if (_strcmpi(name, (char*)aName) == 0){
					while (SQLFetch(SqlHandle) == SQL_SUCCESS)
					{
						SQLGetData(SqlHandle, 2, SQL_CHAR, album_name, 50, &ptrSqlVersion);
						cout << '\t' << album_name << endl;
					}
				}
				else
				{
					cout << "No Artist is found by the entered name" << endl;
				}
				cout << "***************************************************************" << endl;
			}
		}
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	}
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

string DatabaseImplementation::insertSong(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
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
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO SONG(NAME,DURATION) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(duration), 0, sqlDuration, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlDuration, _countof(sqlDuration), duration);
	retcode = SQLExecute(SqlHandle);
	if (SQL_SUCCESS != retcode){		
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Insertion failed";
	}
	else {
		int temp;
		string status;
		char* artistName = new char();
		SQLINTEGER rowCount;
		SQLRowCount(SqlHandle, &rowCount);
		if (rowCount > 0){
			status = insertIntoAlbumSongs(album, name);
			cout << "Enter No of Artist Contributed" << endl;
			cin >> temp;
			if (cin.fail()){
				temp = checkUserInput();
			}
			cin.get();
			for (int i = 0; i < temp; i++){
				cout << "Enter the " << i + 1 << " Artist name:" << endl;
				cin.getline(artistName, 50);
				status = insertIntoSongArtist(artistName, name);
			}
			
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return status;
		}
		else{
			
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return "Insertion Failed";
		}
	}
}

string DatabaseImplementation::insertIntoSongIntoDB(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlName[50], sqlDuration[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* duration = new char();
	cin.get();
	cout << "Enter the Song Duration:" << endl;
	cin.getline(duration, 50);
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO SONG(NAME,DURATION) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(duration), 0, sqlDuration, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlDuration, _countof(sqlDuration), duration);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Insertion");
}

string DatabaseImplementation::insertAlbum(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	cin.get();
	cout << "Enter the Album Name:" << endl;
	cin.getline(name, 50);
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO ALBUM(NAME) VALUES(?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(SqlHandle);
	if (SQL_SUCCESS != retcode){		
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Insertion failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(SqlHandle, &rowCount);
		
		if (rowCount > 0){
			int temp;
			string status;
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
				status = insertIntoAlbumSongs(name, albumSong);
			}
			
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return status;
		}
		else{
			
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return "Insertion failed";
		}
	}
}

string DatabaseImplementation::insertIntoAlbumIntoDB(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO ALBUM(NAME) VALUES(?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Insertion");
}

string DatabaseImplementation::insertArtist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
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
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO ARTIST(NAME,AGE,EMAIL_ID) VALUES(?,?,?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(age), 0, sqlAge, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(emailId), 0, sqlEmailId, 0, &cbValue);
	cout << strlen(name) << endl << strlen(age) << endl << strlen(emailId) << endl;
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlAge, _countof(sqlAge), age);
	strcpy_s((char*)sqlEmailId, _countof(sqlEmailId), emailId);
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	retcode = SQLExecute(SqlHandle);
	if (SQL_SUCCESS != retcode){
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Insertion Failed\n";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(SqlHandle, &rowCount);
		string status;
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
				status = insertIntoSongArtist(name, artistSong);
			}
			
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return status;
		}
		else{
			
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return "Insertion Failed";
		}
	}
}

string DatabaseImplementation::insertIntoArtistIntoDB(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
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
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO ARTIST(NAME,AGE,EMAIL_ID) VALUES(?,?,?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(age), 0, sqlAge, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(emailId), 0, sqlEmailId, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlAge, _countof(sqlAge), age);
	strcpy_s((char*)sqlEmailId, _countof(sqlEmailId), emailId);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Insertion");
}

string DatabaseImplementation::insertPlaylist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
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
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO PLAYLIST(NAME) VALUES(?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(SqlHandle);
	if (SQL_SUCCESS != retcode){
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Insertion failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(SqlHandle, &rowCount);
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
			
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return result;
		}
		else{
			
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return "Insertion Failed";
		}
	}
}

int DatabaseImplementation::getSongIdByname(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"select song.id from Song where Song.Name = ?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return getId(retcode, SqlHandle);
}

int DatabaseImplementation::getAlbumIdByname(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"select album.id from Album where Album.Name= ?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return getId(retcode, SqlHandle);
}

int DatabaseImplementation::getArtistIdByname(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"SELECT artist.id FROM ARTIST WHERE ARTIST.NAME= ?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return getId(retcode, SqlHandle);
}

int DatabaseImplementation::getPlaylistIdByname(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"SELECT playlist.id FROM PLAYLIST WHERE PLAYLIST.NAME= ?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return getId(retcode, SqlHandle);
}


string DatabaseImplementation::insertIntoAlbumSongs(char* albumName, char* songName){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string status;
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
			status = insertIntoSongIntoDB(songName);
			songId = getSongIdByname(songName);
			cout << status << endl;
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
			status = insertIntoAlbumIntoDB(albumName);
			albumId = getAlbumIdByname(albumName);
			cout << status << endl;
		}
		else{
			cout << "You selected No album" << endl;
			albumId = getAlbumIdByname("None");
		}
	}
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO ALBUM_SONG(SONG_ID,ALBUM_ID) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlSong, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlAlbum, 0, &cbValue);
	sqlSong = songId;
	sqlAlbum = albumId;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Insertion");

}


string DatabaseImplementation::insertIntoSongPlaylist(char* playlistName, char*songName){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
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

	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO SONG_PLAYLIST(PLAYLIST_ID,SONG_ID) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlPlaylist, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlSong, 0, &cbValue);
	sqlSong = songId;
	sqlPlaylist = playlistId;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Insertion");
}

string DatabaseImplementation::insertIntoSongArtist(char* artistName, char* songName){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string status;
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
			status = insertIntoSongIntoDB(songName);
			songId = getSongIdByname(songName);
			cout << status << endl;
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
			status = insertIntoArtistIntoDB(artistName);
			artistId = getArtistIdByname(artistName);
			cout << status << endl;
		}
		else{
			cout << "You selected No Artist" << endl;
			artistId = getArtistIdByname("None");
		}
	}

	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"INSERT INTO SONG_ARTIST(SONG_ID,ARTIST_ID) VALUES(?,?)", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlSong, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlArtist, 0, &cbValue);
	sqlSong = songId;
	sqlArtist = artistId;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Insertion");
}

string DatabaseImplementation::updateSongName(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlNewName[50], sqlOldname[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* oldname = new char();
	char* newName = new char();
	cin.get();
	cout << "Enter the Song Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the new name" << endl;
	cin.getline(newName, 50);
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"update Song set Song.Name=? where name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(newName), 0, sqlNewName, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(oldname), 0, sqlOldname, 0, &cbValue);
	strcpy_s((char*)sqlNewName, _countof(sqlNewName), newName);
	strcpy_s((char*)sqlOldname, _countof(sqlOldname), oldname);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Updation");
}

string DatabaseImplementation::updateSongDuration(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlName[50], sqlDuration[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	char* duration = new char();
	cin.get();
	cout << "Enter the Song Name you want to update:" << endl;
	cin.getline(name, 50);
	cout << "Enter the new song duration" << endl;
	cin.getline(duration, 50);
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"update Song set Song.Duration=? where name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(duration), 0, sqlDuration, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	strcpy_s((char*)sqlDuration, _countof(sqlDuration), duration);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Updation");
}

string DatabaseImplementation::updateAlbum(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlNewName[50], sqlOldname[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* oldname = new char();
	char* newName = new char();
	cin.get();
	cout << "Enter the Album Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the new name" << endl;
	cin.getline(newName, 50);
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"update Album set Album.Name=? where name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(newName), 0, sqlNewName, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(oldname), 0, sqlOldname, 0, &cbValue);
	strcpy_s((char*)sqlNewName, _countof(sqlNewName), newName);
	strcpy_s((char*)sqlOldname, _countof(sqlOldname), oldname);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Updation");
}

string DatabaseImplementation::updatePlaylist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlNewName[50], sqlOldname[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* oldname = new char();
	char* newName = new char();
	cin.get();
	cout << "Enter the Playlist Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the new name" << endl;
	cin.getline(newName, 50);
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"update Playlist set Playlist.Name=? where name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(newName), 0, sqlNewName, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(oldname), 0, sqlOldname, 0, &cbValue);
	strcpy_s((char*)sqlNewName, _countof(sqlNewName), newName);
	strcpy_s((char*)sqlOldname, _countof(sqlOldname), oldname);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Updation");
}

string DatabaseImplementation::updateArtistName(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlNewName[50], sqlOldname[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* oldname = new char();
	char* newName = new char();
	cin.get();
	cout << "Enter the Artist Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the new name" << endl;
	cin.getline(newName, 50);
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"update Artist set Artist.Name=? where name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(newName), 0, sqlNewName, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(oldname), 0, sqlOldname, 0, &cbValue);
	strcpy_s((char*)sqlNewName, _countof(sqlNewName), newName);
	strcpy_s((char*)sqlOldname, _countof(sqlOldname), oldname);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Updation");
}

string DatabaseImplementation::updateArtistEmailId(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlEmailId[50], sqlOldname[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* oldname = new char();
	char* emailId = new char();
	cin.get();
	cout << "Enter the Artist Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the Email ID" << endl;
	cin.getline(emailId, 50);
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"update Artist set Artist.Email_id=? where name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(emailId), 0, sqlEmailId, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(oldname), 0, sqlOldname, 0, &cbValue);
	strcpy_s((char*)sqlEmailId, _countof(sqlEmailId), emailId);
	strcpy_s((char*)sqlOldname, _countof(sqlOldname), oldname);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Updation");
}

string DatabaseImplementation::updateArtistAge(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlOldname[50];
	SQLINTEGER cbValue = SQL_NTS, sqlAge;
	char* oldname = new char();
	cin.get();
	cout << "Enter the Artist Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the Age" << endl;
	cin >> sqlAge;
	cout << endl;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"update Artist set Artist.Age=? where name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlAge, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(oldname), 0, sqlOldname, 0, &cbValue);
	strcpy_s((char*)sqlOldname, _countof(sqlOldname), oldname);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Updation");
}


string DatabaseImplementation::deleteSong(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	cin.get();
	cout << "Enter the Song Name:" << endl;
	cin.getline(name, 50);
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from song where song.name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	SQLINTEGER songId;
	songId = getSongIdByname(name);
	deleteAlbumSongBySong(songId);
	deleteSongArtistBySong(songId);
	deleteSongPlaylistBySong(songId);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deleteAlbum(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	cin.get();
	cout << "Enter the Album Name:" << endl;
	cin.getline(name, 50);
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from Album where Album.name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	SQLINTEGER albumId;
	albumId = getAlbumIdByname(name);
	deleteAlbumSongByAlbum(albumId);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deleteArtist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	cin.get();
	cout << "Enter the Artist Name:" << endl;
	cin.getline(name, 50);
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from Artist where Artist.name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	SQLINTEGER artistId;
	artistId = getArtistIdByname(name);
	deleteSongArtistByArtist(artistId);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deletePlaylist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLCHAR sqlName[50];
	SQLINTEGER cbValue = SQL_NTS;
	char* name = new char();
	cin.get();
	cout << "Enter the Playlist Name:" << endl;
	cin.getline(name, 50);
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from playlist where playlist.name=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	strcpy_s((char*)sqlName, _countof(sqlName), name);
	SQLINTEGER playlistId;
	playlistId = getPlaylistIdByname(name);
	deleteSongPlaylistByPlaylist(playlistId);
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deleteAlbumSongBySong(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS, sqlId;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from Album_Song where Album_Song.song_id=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId, 0, &cbValue);
	sqlId = id;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deleteSongArtistBySong(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS, sqlId;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from Song_Artist where Song_Artist.song_id=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId, 0, &cbValue);
	sqlId = id;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deleteSongPlaylistBySong(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS, sqlId;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from Song_playlist where Song_Playlist.song_id=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId, 0, &cbValue);
	sqlId = id;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deleteAlbumSongByAlbum(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS, sqlId;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from Album_Song where Album_Song.album_id=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId, 0, &cbValue);
	sqlId = id;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deleteSongArtistByArtist(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS, sqlId;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from Song_Artist where Song_Artist.artist_id=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId, 0, &cbValue);
	sqlId = id;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::deleteSongPlaylistByPlaylist(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN retcode;
	SQLINTEGER cbValue = SQL_NTS, sqlId;
	retcode = SQLPrepare(SqlHandle, (SQLWCHAR*)L"delete from Song_playlist where Song_Playlist.playlist_id=?", SQL_NTS);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId, 0, &cbValue);
	sqlId = id;
	retcode = SQLExecute(SqlHandle);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(retcode, SqlHandle, "Deletion");
}

string DatabaseImplementation::result(SQLRETURN retCode, SQLHANDLE SqlHandle, string message)
{
	if (SQL_SUCCESS != retCode){
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		message = message + " Failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(SqlHandle, &rowCount);
		if (rowCount > 0){
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			message = message + " Successfully";
		}
		else{
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			message = message + " Failed";
		}
	}
	return message;
}

int DatabaseImplementation::getId(SQLRETURN retCode, SQLHANDLE SqlHandle)
{
	int playlistId;
	if (SQL_SUCCESS != retCode){
		cout << "Error querying SQL Server";
		cout << "\n";
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		playlistId = -1;
	}
	else {
		SQLINTEGER ptrSqlVersion;
		SQLFetch(SqlHandle);
		SQLGetData(SqlHandle, 1, SQL_INTEGER, &playlistId, 0, &ptrSqlVersion);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	}
	return playlistId;
}

/*method to validate user input of type integer*/
int DatabaseImplementation::checkUserInput() {
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
