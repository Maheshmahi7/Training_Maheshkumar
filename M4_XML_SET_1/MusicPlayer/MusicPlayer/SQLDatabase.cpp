#include"SQLDatabase.h"

SQLDatabase::SQLDatabase(){

}
SQLDatabase::~SQLDatabase(){

}

void SQLDatabase::userUI(){
	string result;
	int choice;

	while (true){
		menu();
		cin >> choice;
		if (cin.fail()){
			choice = checkUserInput();
		}
		system("cls");
		/*switch statement to execute based on user choice*/
		switch (choice){
		case 1:{
			/*creating instance for reading the xml file from memory*/
			int readChoice;
			DataReader readDb;
			bool readLoop = true;
			while (readLoop)
			{
				readMenu();
				cin >> readChoice;
				if (cin.fail()){
					readChoice = checkUserInput();
				}
				system("cls");
				switch (readChoice)
				{
				case 1:{
					readDb.displaySongsFromDB();
					break;
				}
				case 2:{
					readDb.displayArtistsFromDB();
					break;
				}
				case 3:{
					readDb.displayAlbumsFromDB();
					break;
				}
				case 4:{
					readDb.displayPlaylistsFromDB();
					break;
				}
				case 5:{
					readLoop = false;
					break;
				}
				default:{
					cout << "Enter Correct value" << endl;
					break;
				}
				}
			}
			break;
		}
		case 2:{
			/*creating instance for writing into xml file in the memory*/
			DataWriter writeDb;
			int writeChoice;
			bool writeLoop = true;
			while (writeLoop){
				writeMenu();
				cin >> writeChoice;
				if (cin.fail()){
					writeChoice = checkUserInput();
				}
				system("cls");
				switch (writeChoice){
				case 1:{
					result = writeDb.insertIntoSongIntoDB();
					cout << result << endl;
					break;
				}
				case 2:{
					result = writeDb.insertIntoArtistIntoDB();
					cout << result << endl;
					break;
				}
				case 3:{
					result = writeDb.insertIntoAlbumIntoDB();
					cout << result << endl;
					break;
				}
				case 4:{
					result = writeDb.insertIntoPlaylistIntoDB();
					cout << result << endl;
					break;
				}
				case 5:{
					writeLoop = false;
					break;
				}
				default:{
					cout << "Enter correct value" << endl;
					break;
				}
				}
			}
			break;
		}
		case 3:{
			DataWriter writeDb;
			int deleteChoice;
			bool deleteLoop = true;
			while (deleteLoop){
				deleteMenu();
				cin >> deleteChoice;
				if (cin.fail()){
					deleteChoice = checkUserInput();
				}
				system("cls");
				switch (deleteChoice){
				case 1:{
					result = writeDb.deleteSong();
					cout << result << endl;
					break;
				}
				case 2:{
					result = writeDb.deleteArtist();
					cout << result << endl;
					break;
				}
				case 3:{
					result = writeDb.deleteAlbum();
					cout << result << endl;
					break;
				}
				case 4:{
					result = writeDb.deletePlaylist();
					cout << result << endl;
					break;
				}
				case 5:{
					deleteLoop = false;
					break;
				}
				default:{
					cout << "Enter correct value" << endl;
					break;
				}
				}
			}
			break;
		}
		case 4:{
			DataWriter writeDb;
			int updateChoice;
			bool updateLoop = true;
			while (updateLoop){
				updateMenu();
				cin >> updateChoice;
				if (cin.fail()){
					updateChoice = checkUserInput();
				}
				system("cls");
				switch (updateChoice){
				case 1:{
					result = writeDb.updateSongName();
					cout << result << endl;
					break;
				}
				case 2:{
					result = writeDb.updateSongDuration();
					cout << result << endl;
					break;
				}
				case 3:{
					result = writeDb.updateArtistName();
					cout << result << endl;
					break;
				}
				case 4:{
					result = writeDb.updateArtistAge();
					cout << result << endl;
					break;
				}
				case 5:{
					result = writeDb.updateArtistEmailId();
					cout << result << endl;
					break;
				}
				case 6:{
					result = writeDb.updateAlbum();
					cout << result << endl;
					break;
				}
				case 7:{
					result = writeDb.updatePlaylist();
					cout << result << endl;
					break;
				}
				case 8:{
					updateLoop = false;
					break;
				}
				default:{
					cout << "Enter correct value" << endl;
					break;
				}
				}
			}
			break;
		}
		case 5:{
			exit(0);
		}
		default:{
			cout << "Enter correct value" << endl;
			break;
		}
		}
	}
}



/*Main menu for getting user choice*/
void SQLDatabase::menu(){
	cout << "1.Read Music Player" << endl;
	cout << "2.Add items to Music Player" << endl;
	cout << "3.Delete Items from Music Player" << endl;
	cout << "4.Update Items from Music Player" << endl;
	cout << "5.Exit" << endl;
}

/*read menu to read from database on user choice*/
void SQLDatabase::readMenu(){
	cout << "1. Display Songs" << endl;
	cout << "2. Display Artists" << endl;
	cout << "3. Dispaly Albums" << endl;
	cout << "4. Dispaly Playlists" << endl;
	cout << "5. Go Back" << endl;
}
/*write menu to write into database on user choice*/
void SQLDatabase::writeMenu(){
	cout << "1.Add Song" << endl;
	cout << "2.Add Artist" << endl;
	cout << "3.Add Album" << endl;
	cout << "4.Create Playlist" << endl;
	cout << "5.Go Back" << endl;
}

/*delete menu to delete from database on user choice*/
void SQLDatabase::deleteMenu(){
	cout << "1.Delete Song" << endl;
	cout << "2.Delete Artist" << endl;
	cout << "3.Delete Album" << endl;
	cout << "4.Delete Playlist" << endl;
	cout << "5.Go Back" << endl;
}

void SQLDatabase::updateMenu(){
	cout << "1.Update Song Name" << endl;
	cout << "2.Update Song Duration" << endl;
	cout << "3.Update Artist Name" << endl;
	cout << "4.Update Artist Age" << endl;
	cout << "5.Update Artist Email Id" << endl;
	cout << "6.Update Album Name" << endl;
	cout << "7.Update Playlist Name" << endl;
	cout << "8.Go Back" << endl;
}
/*method to validate user input of type integer*/
int SQLDatabase::checkUserInput() {
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
