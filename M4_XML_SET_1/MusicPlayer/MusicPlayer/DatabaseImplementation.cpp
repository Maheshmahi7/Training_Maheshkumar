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

SQLHANDLE DatabaseImplementation::select(SQLHANDLE SqlHandle, SQLWCHAR* Query, char* name, int age)
{
	SQLINTEGER cbValue = SQL_NTS;
	SQLRETURN retcode;
	char sqlName[50];
	int sqlAge;
	retcode = SQLPrepare(SqlHandle, Query, SQL_NTS);
	strcpy_s(sqlName, _countof(sqlName), name);
	sqlAge = age;
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlAge, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name), 0, sqlName, 0, &cbValue);
	return (SQL_SUCCESS != SQLExecute(SqlHandle)) ? 0 : SqlHandle;
}

SQLHANDLE DatabaseImplementation::select(SQLHANDLE SqlHandle, SQLWCHAR* Query, char* name1, char* name2)
{
	SQLINTEGER cbValue = SQL_NTS;
	SQLRETURN retcode;
	char sqlName1[50],sqlName2[50];
	retcode = SQLPrepare(SqlHandle, Query, SQL_NTS);
	strcpy_s(sqlName1, _countof(sqlName1), name1);
	strcpy_s(sqlName2, _countof(sqlName2), name2);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name1), 0, sqlName1, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name2), 0, sqlName2, 0, &cbValue);
	return (SQL_SUCCESS != SQLExecute(SqlHandle)) ? 0 : SqlHandle;
}

SQLHANDLE DatabaseImplementation::select(SQLHANDLE SqlHandle, SQLWCHAR* Query, char* name1, int age, char* name2)
{
	SQLINTEGER cbValue = SQL_NTS;
	SQLRETURN retcode;
	int sqlAge;
	char sqlName1[50], sqlName2[50];
	retcode = SQLPrepare(SqlHandle, Query, SQL_NTS);
	strcpy_s(sqlName1, _countof(sqlName1), name1);
	sqlAge = age;
	strcpy_s(sqlName2, _countof(sqlName2), name2);
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name1), 0, sqlName1, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlAge, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(name2), 0, sqlName2, 0, &cbValue);
	return (SQL_SUCCESS != SQLExecute(SqlHandle)) ? 0 : SqlHandle;
}

SQLHANDLE DatabaseImplementation::select(SQLHANDLE SqlHandle, SQLWCHAR* Query, int id)
{
	SQLINTEGER cbValue = SQL_NTS;
	SQLRETURN retcode;
	int sqlId;
	retcode = SQLPrepare(SqlHandle, Query, SQL_NTS);
	sqlId = id;
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId, 0, &cbValue);
	return (SQL_SUCCESS != SQLExecute(SqlHandle)) ? 0 : SqlHandle;
}

SQLHANDLE DatabaseImplementation::select(SQLHANDLE SqlHandle, SQLWCHAR* Query, int id1, int id2)
{
	SQLINTEGER cbValue = SQL_NTS;
	SQLRETURN retcode;
	int sqlId1, sqlId2;
	retcode = SQLPrepare(SqlHandle, Query, SQL_NTS);
	sqlId1 = id1;
	sqlId2 = id2;
	retcode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId1, 0, &cbValue);
	retcode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sqlId2, 0, &cbValue);
	return (SQL_SUCCESS != SQLExecute(SqlHandle)) ? 0 : SqlHandle;
}


void DatabaseImplementation::displaySongs()
{
	vector<string> songName;
	songName = getSongs();
	char* name;
	int Size = songName.size();
	for (int i = 0; i < Size; i++)
	{
		name = (char*)songName[i].c_str();
		displaySongByName(name);
	}
}

void DatabaseImplementation::displayArtists()
{
	vector<string> artistName;
	artistName = getArtists();
	char* name;
	int Size = artistName.size();
	for (int i = 0; i < Size; i++)
	{
		name = (char*)artistName[i].c_str();
		displayArtistsSongByName(name);
		displayArtistsAlbumByName(name);
	}
}

void DatabaseImplementation::displayAlbums()
{
	vector<string> albumName;
	albumName = getAlbums();
	char* name;
	int Size = albumName.size();
	for (int i = 0; i < Size; i++)
	{
		name = (char*)albumName[i].c_str();
		displayAlbumsSongByName(name);
		displayAlbumsArtistByName(name);
	}
}

void DatabaseImplementation::displayPlaylists()
{
	vector<string> playlistName;
	playlistName = getPlaylists();
	char* name;
	int Size = playlistName.size();
	for (int i = 0; i < Size; i++)
	{
		name = (char*)playlistName[i].c_str();
		displayPlaylistByName(name);
	}
}


vector<string> DatabaseImplementation::getSongs(){
	vector<string> songName;
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_SONGS))){
		cout << "Error querying SQL Server";
		cout << "\n";
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
	}
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	return songName;
}

void DatabaseImplementation::displaySongByName(char* name){
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_SONG_BY_NAME, name))){
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
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

vector<string> DatabaseImplementation::getAlbums(){
	SQLHANDLE SqlHandle = NULL;
	vector<string> albumName;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_ALBUMS))){
		cout << "Error querying SQL Server";
		cout << "\n";
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
				albumName.push_back(name);
			}
		}
	}
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	return albumName;
}

void DatabaseImplementation::displayAlbumsSongByName(char* name){
	SQLINTEGER ptrSqlVersion;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_ALBUM_SONG_BY_NAME, name))){
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
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

void DatabaseImplementation::displayAlbumsArtistByName(char* name){
	SQLINTEGER ptrSqlVersion;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_ALBUM_ARTIST_BY_NAME, name))){
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
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

vector<string> DatabaseImplementation::getPlaylists(){
	SQLHANDLE SqlHandle = NULL;
	vector<string> playlistName;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_PLAYLISTS))){
		cout << "Error querying SQL Server";
		cout << "\n";
	}
	else {
		//declare output variable and pointer
		SQLINTEGER id;
		char name[50];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(SqlHandle) == SQL_SUCCESS){
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &id, 50, &ptrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, name, 50, &ptrSqlVersion);
			playlistName.push_back(name);
		}
	}
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	return playlistName;
}

void DatabaseImplementation::displayPlaylistByName(char* name){
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_PLAYLIST_BY_NAME, name))){
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
			cout << "Name: " << pName << endl;
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
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

vector<string> DatabaseImplementation::getArtists(){
	SQLHANDLE SqlHandle = NULL;
	vector<string> artistName;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_ARTISTS))){
		cout << "Error querying SQL Server";
		cout << "\n";
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
				artistName.push_back(name);
			}
		}
	}
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	return artistName;
}

void DatabaseImplementation::displayArtistsSongByName(char* name){
	SQLINTEGER ptrSqlVersion;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_ARTIST_SONG_BY_NAME, name))){
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
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

void DatabaseImplementation::displayArtistsAlbumByName(char* name){
	SQLINTEGER ptrSqlVersion;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	if (!(SqlHandle = select(SqlHandle, GET_ARTIST_ALBUM_BY_NAME, name))){
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
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}



string DatabaseImplementation::insertSong(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string status;
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
	if (!(SqlHandle = select(SqlHandle, INSERT_SONG, name, duration))){
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		status = "Insertion failed";
	}
	else {
		int temp;
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
		}
		else{
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			status = "Insertion Failed";
		}
	}
	return status;
}

string DatabaseImplementation::insertIntoSongIntoDB(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* duration = new char();
	cin.get();
	cout << "Enter the Song Duration:" << endl;
	cin.getline(duration, 50);	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, INSERT_SONG, name, duration), "Insertion");
}

string DatabaseImplementation::insertAlbum(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string status;
	char* name = new char();
	cin.get();
	cout << "Enter the Album Name:" << endl;
	cin.getline(name, 50);
	cout << endl;
	if (!(SqlHandle = select(SqlHandle, INSERT_ALBUM, name))){
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		status = "Insertion failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(SqlHandle, &rowCount);
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
				status = insertIntoAlbumSongs(name, albumSong);
			}
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		}
		else{
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			status = "Insertion failed";
		}
	}
	return status;
}

string DatabaseImplementation::insertIntoAlbumIntoDB(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, INSERT_ALBUM, name), "Insertion");
}

string DatabaseImplementation::insertArtist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	int age;
	string status;
	char* name = new char();
	char* emailId = new char();
	cin.get();
	cout << "Enter the Artist Name:" << endl;
	cin.getline(name, 50);
	cout << "Enter the Artist Email Id" << endl;
	cin.getline(emailId, 50);
	cout << "Enter the Artist Age:" << endl;
	cin >> age;
	if (cin.fail()){
		age = checkUserInput();
	}
	if (!(SqlHandle = select(SqlHandle, INSERT_ARTIST, name, age, emailId))){
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		status = "Insertion Failed";
	}
	else {
		SQLINTEGER rowCount;
		SQLRowCount(SqlHandle, &rowCount);
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
		}
		else{
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			status = "Insertion Failed";
		}
	}
	return status;
}

string DatabaseImplementation::insertIntoArtistIntoDB(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	int age;
	char* emailId = new char();
	cin.get();
	cout << "Enter the Artist Email Id" << endl;
	cin.getline(emailId, 50);	
	cout << "Enter the Artist Age:" << endl;
	cin >> age;
	if (cin.fail()){
		age = checkUserInput();
	}
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, INSERT_ARTIST, name, age, emailId), "Insertion");
}

string DatabaseImplementation::insertPlaylist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string status, input;
	char* name = new char();
	cin.get();
	cout << "Enter the Playlist Name:" << endl;
	getline(cin, input);
	strcpy(name, input.c_str());
	cout << endl;
	if (!(SqlHandle = select(SqlHandle, INSERT_PLAYLIST, name))){
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		status = "Insertion failed";
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
				status = insertIntoSongPlaylist(name, songName);
				if (status.compare("Insertion failed") == 0){
					i--;
				}
			}
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		}
		else{
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			status = "Insertion Failed";
		}
	}
	return status;
}



int DatabaseImplementation::getSongIdByname(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return getId(SqlHandle = select(SqlHandle, GET_SONG_ID_BY_NAME, name));
}

int DatabaseImplementation::getAlbumIdByname(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return getId(SqlHandle = select(SqlHandle, GET_ALBUM_ID_BY_NAME, name));
}

int DatabaseImplementation::getArtistIdByname(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return getId(SqlHandle = select(SqlHandle, GET_ARTIST_ID_BY_NAME, name));
}

int DatabaseImplementation::getPlaylistIdByname(char* name){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return getId(SqlHandle = select(SqlHandle, GET_PLAYLIST_ID_BY_NAME, name));
}



string DatabaseImplementation::insertIntoAlbumSongs(char* albumName, char* songName){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string status;
	int songId, albumId;
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
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, INSERT_ALBUM_SONG, songId, albumId), "Insertion");

}

string DatabaseImplementation::insertIntoSongPlaylist(char* playlistName, char*songName){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	int songId, playlistId;
	string status;
	songId = getSongIdByname(songName);
	if (songId < 0){
		cout << "Song is Not avilable" << endl;
		status = "Insertion failed";
	}
	else
	{
		playlistId = getPlaylistIdByname(playlistName);
		if (playlistId < 0){
			cout << "Playlist is Not avilable" << endl;
			status = "Insertion failed";
		}
		else
		{
			SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
			status = result(SqlHandle = select(SqlHandle, INSERT_SONG_PLAYLIST, playlistId, songId), "Insertion");
		}
	}
	return status;
}

string DatabaseImplementation::insertIntoSongArtist(char* artistName, char* songName){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string status;
	int songId, artistId;
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
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, INSERT_SONG_ARTIST, songId, artistId), "Insertion");
}



string DatabaseImplementation::updateSongName(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* oldname = new char();
	char* newName = new char();
	cin.get();
	cout << "Enter the Song Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the new name" << endl;
	cin.getline(newName, 50);
	cout << endl;
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, UPDATE_SONG_NAME, newName, oldname), "Updation");
}

string DatabaseImplementation::updateSongDuration(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* name = new char();
	char* duration = new char();
	cin.get();
	cout << "Enter the Song Name you want to update:" << endl;
	cin.getline(name, 50);
	cout << "Enter the new song duration" << endl;
	cin.getline(duration, 50);
	cout << endl;
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, UPDATE_SONG_DURATION, duration, name), "Updation");
}

string DatabaseImplementation::updateAlbum(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* oldname = new char();
	char* newName = new char();
	cin.get();
	cout << "Enter the Album Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the new name" << endl;
	cin.getline(newName, 50);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, UPDATE_ALBUM_NAME, newName, oldname), "Updation");
}

string DatabaseImplementation::updatePlaylist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* oldname = new char();
	char* newName = new char();
	cin.get();
	cout << "Enter the Playlist Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the new name" << endl;
	cin.getline(newName, 50);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, UPDATE_PLAYLIST_NAME, newName, oldname), "Updation");
}

string DatabaseImplementation::updateArtistName(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* oldname = new char();
	char* newName = new char();
	cin.get();
	cout << "Enter the Artist Name you want to update:" << endl;
	cin.getline(oldname, 50);
	cout << "Enter the new name" << endl;
	cin.getline(newName, 50);
	cout << endl;
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, UPDATE_ARTIST_NAME, newName, oldname), "Updation");
}

string DatabaseImplementation::updateArtistEmailId(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* name = new char();
	char* emailId = new char();
	cin.get();
	cout << "Enter the Artist Name you want to update:" << endl;
	cin.getline(name, 50);
	cout << "Enter the Email ID" << endl;
	cin.getline(emailId, 50);
	cout << endl;
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, UPDATE_ARTIST_EMAIL_ID, emailId, name), "Updation");
}

string DatabaseImplementation::updateArtistAge(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	int age;
	char* name = new char();
	cin.get();
	cout << "Enter the Artist Name you want to update:" << endl;
	cin.getline(name, 50);
	cout << "Enter the Age" << endl;
	cin >> age;
	cout << endl;
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, UPDATE_ARTIST_AGE, name, age), "Updation");
}



string DatabaseImplementation::deleteSong(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* name = new char();
	cin.get();
	cout << "Enter the Song Name:" << endl;
	cin.getline(name, 50);
	SQLINTEGER songId;
	songId = getSongIdByname(name);
	deleteAlbumSongBySong(songId);
	deleteSongArtistBySong(songId);
	deleteSongPlaylistBySong(songId);	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_SONG, name), "Deletion");
}

string DatabaseImplementation::deleteAlbum(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* name = new char();
	cin.get();
	cout << "Enter the Album Name:" << endl;
	cin.getline(name, 50);
	SQLINTEGER albumId;
	albumId = getAlbumIdByname(name);
	deleteAlbumSongByAlbum(albumId);
	
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_ALBUM, name), "Deletion");
}

string DatabaseImplementation::deleteArtist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* name = new char();
	cin.get();
	cout << "Enter the Artist Name:" << endl;
	cin.getline(name, 50);
	SQLINTEGER artistId;
	artistId = getArtistIdByname(name);
	deleteSongArtistByArtist(artistId);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_ARTIST, name), "Deletion");
}

string DatabaseImplementation::deletePlaylist(){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	char* name = new char();
	cin.get();
	cout << "Enter the Playlist Name:" << endl;
	cin.getline(name, 50);
	SQLINTEGER playlistId;
	playlistId = getPlaylistIdByname(name);
	deleteSongPlaylistByPlaylist(playlistId);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_PLAYLIST, name), "Deletion");
}



string DatabaseImplementation::deleteAlbumSongBySong(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_ALBUM_SONG_SONG, id), "Deletion");
}

string DatabaseImplementation::deleteSongArtistBySong(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_SONG_ARTIST_SONG, id), "Deletion");
}

string DatabaseImplementation::deleteSongPlaylistBySong(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_SONG_PLAYLIST_SONG, id), "Deletion");
}

string DatabaseImplementation::deleteAlbumSongByAlbum(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_ALBUM_SONG_ALBUM, id), "Deletion");
}

string DatabaseImplementation::deleteSongArtistByArtist(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_SONG_ARTIST_ARTIST, id), "Deletion");
}

string DatabaseImplementation::deleteSongPlaylistByPlaylist(int id){
	SQLHANDLE SqlHandle = NULL;
	SQLHANDLE SqlConnHandle = DatabaseConnection::get_connection_handler();
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
	return result(SqlHandle = select(SqlHandle, DELETE_SONG_PLAYLIST_PLAYLIST, id), "Deletion");
}



string DatabaseImplementation::result(SQLHANDLE SqlHandle, string message)
{
	if (!(SqlHandle)){
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
			message = "Entered name value does not exist";
		}
	}
	return message;
}

int DatabaseImplementation::getId(SQLHANDLE SqlHandle)
{
	int playlistId;
	if (!(SqlHandle)){
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
