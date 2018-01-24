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
					cout << "Song Added" << endl;
					break;
				}
				case 2:{
					result = writeDb.insertIntoArtistIntoDB();
					cout << "Artist Added" << endl;
					break;
				}
				case 3:{
					result = writeDb.insertIntoAlbumIntoDB();
					cout << "Album Added" << endl;
					break;
				}
				case 4:{
					result = writeDb.insertIntoPlaylistIntoDB();
					cout << "Playlist Created" << endl;
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
	cout << "3.Exit" << endl;
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
