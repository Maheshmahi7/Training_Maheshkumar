#include "UserUI.h"
#include "DatabaseImplementation.h"
#include "XmlParser.h"


void UserUI::userOption()
{
	system("cls");
	int choice;
	UserInterface* userInterface;
	while (true)
	{
		mainMenu();
		cin >> choice;
		if (cin.fail() || 1 > choice || choice > 3){
			choice = checkUserInput(3);
		}
		system("cls");
		switch (choice){
		case 1:{
			exit(0);
		}
		case 2:{
			userInterface = UserInterfaceFactory::Create("XML");
			option(userInterface);
			break;
		}
		case 3:{
			userInterface = UserInterfaceFactory::Create("Database");
			option(userInterface);
			break;
		}
		default:{
			cout << "Enter Correct value" << endl;
			break;
		}
		}
	}
}

void UserUI::option(UserInterface* userInterface)
{
	int choice, count = 1;
	while (true){
		if (dynamic_cast<DatabaseImplementation*>(userInterface))
		{
			databaseMenu();
			count = 5;
		}
		else if (dynamic_cast<XmlParser*>(userInterface))
		{
			xmlMenu();
			count = 3;
		}
		cin >> choice;
		if (cin.fail() || 1 > choice || choice > count){
			choice = checkUserInput(count);
		}
		system("cls");
		/*switch statement to execute based on user choice*/
		switch (choice){
		case 1:{
			exit(0);
		}
		case 2:{
			reader(userInterface);
			break;
		}
		case 3:{
			writer(userInterface);
			break;
		}
		case 4:{
			deleter(userInterface);
			break;
		}
		case 5:{
			updater(userInterface);
			break;
		}
		default:{
			cout << "Enter correct value" << endl;
			break;
		}
		}
	}
}


void UserUI::mainMenu()
{
	cout << "View/Write Music Player from " << endl;
	cout << "1.Exit" << endl;
	cout << "2.XML File" << endl;
	cout << "3.Database" << endl;
}

/*Main menu for getting user choice*/
void UserUI::databaseMenu(){
	cout << "1.Exit" << endl;
	cout << "2.Read Music Player" << endl;
	cout << "3.Add items to Music Player" << endl;
	cout << "4.Delete Items from Music Player" << endl;
	cout << "5.Update Items from Music Player" << endl;
}

/*Main menu for getting user choice*/
void UserUI::xmlMenu(){
	cout << "1.Exit" << endl;
	cout << "2.Read Music Player" << endl;
	cout << "3.Add items to Music Player" << endl;
}

/*read menu to read from database on user choice*/
void UserUI::readMenu(){
	cout << "1. Go Back" << endl;
	cout << "2. Display Songs" << endl;
	cout << "3. Display Artists" << endl;
	cout << "4. Dispaly Albums" << endl;
	cout << "5. Dispaly Playlists" << endl;
}
/*write menu to write into database on user choice*/
void UserUI::writeMenu(){
	cout << "1.Go Back" << endl;
	cout << "2.Add Song" << endl;
	cout << "3.Add Artist" << endl;
	cout << "4.Add Album" << endl;
	cout << "5.Create Playlist" << endl;
}

/*delete menu to delete from database on user choice*/
void UserUI::deleteMenu(){
	cout << "1.Go Back" << endl;
	cout << "2.Delete Song" << endl;
	cout << "3.Delete Artist" << endl;
	cout << "4.Delete Album" << endl;
	cout << "5.Delete Playlist" << endl;
}

void UserUI::updateMenu(){
	cout << "1.Go Back" << endl;
	cout << "2.Update Song Name" << endl;
	cout << "3.Update Song Duration" << endl;
	cout << "4.Update Artist Name" << endl;
	cout << "5.Update Artist Age" << endl;
	cout << "6.Update Artist Email Id" << endl;
	cout << "7.Update Album Name" << endl;
	cout << "8.Update Playlist Name" << endl;
}



int UserUI::checkUserInput(int count) 
{
	int input = 0;
	while (1)
	{
		if (cin.fail() || 1 > input || input > count)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cout << "Enter Correct Input" << endl;
			cin >> input;
		}
		else if (!cin.fail() && 1 < input || input < count) {
			return input;
			break;
		}
	}
}
void UserUI::reader(UserInterface* userInterface)
{
	/*creating instance for reading the xml file from memory*/
	int readChoice;
	bool readLoop = true;
	while (readLoop)
	{
		readMenu();
		cin >> readChoice;
		if (cin.fail() || 1 > readChoice || readChoice > 5){
			readChoice = checkUserInput(5);
		}
		system("cls");
		switch (readChoice)
		{
		case 1:{
			readLoop = false;
			break;
		}
		case 2:{
			userInterface->displaySongs();
			break;
		}
		case 3:{
			userInterface->displayArtists();
			break;
		}
		case 4:{
			userInterface->displayAlbums();
			break;
		}
		case 5:{
			userInterface->displayPlaylists();
			break;
		}
		default:{
			cout << "Enter Correct value" << endl;
			break;
		}
		}
	}
}

void UserUI::writer(UserInterface* userInterface)
{
	/*creating instance for writing into xml file in the memory*/
	string result;
	int writeChoice;
	bool writeLoop = true;
	while (writeLoop){
		writeMenu();
		cin >> writeChoice;
		if (cin.fail() || 1 > writeChoice || writeChoice > 5){
			writeChoice = checkUserInput(5);
		}
		system("cls");
		switch (writeChoice){
		case 1:{
			writeLoop = false;
			break;
		}
		case 2:{
			result = userInterface->insertSong();
			cout << result << endl;
			break;
		}
		case 3:{
			result = userInterface->insertArtist();
			cout << result << endl;
			break;
		}
		case 4:{
			result = userInterface->insertAlbum();
			cout << result << endl;
			break;
		}
		case 5:{
			result = userInterface->insertPlaylist();
			cout << result << endl;
			break;
		}
		default:{
			cout << "Enter correct value" << endl;
			break;
		}
		}
	}
}

void UserUI::deleter(UserInterface* userInterface)
{
	string result;
	int deleteChoice;
	bool deleteLoop = true;
	while (deleteLoop){
		deleteMenu();
		cin >> deleteChoice;
		if (cin.fail() || 1 > deleteChoice || deleteChoice > 5){
			deleteChoice = checkUserInput(5);
		}
		system("cls");
		switch (deleteChoice){
		case 1:{
			deleteLoop = false;
			break;
		}
		case 2:{
			result = userInterface->deleteSong();
			cout << result << endl;
			break;
		}
		case 3:{
			result = userInterface->deleteArtist();
			cout << result << endl;
			break;
		}
		case 4:{
			result = userInterface->deleteAlbum();
			cout << result << endl;
			break;
		}
		case 5:{
			result = userInterface->deletePlaylist();
			cout << result << endl;
			break;
		}
		default:{
			cout << "Enter correct value" << endl;
			break;
		}
		}
	}
}


void UserUI::updater(UserInterface* userInterface)
{
	string result;
	int updateChoice;
	bool updateLoop = true;
	while (updateLoop){
		updateMenu();
		cin >> updateChoice;
		if (cin.fail() || 1 > updateChoice || updateChoice > 8){
			updateChoice = checkUserInput(8);
		}
		system("cls");
		switch (updateChoice){
		case 1:{
			updateLoop = false;
			break;
		}
		case 2:{
			result = userInterface->updateSongName();
			cout << result << endl;
			break;
		}
		case 3:{
			result = userInterface->updateSongDuration();
			cout << result << endl;
			break;
		}
		case 4:{
			result = userInterface->updateArtistName();
			cout << result << endl;
			break;
		}
		case 5:{
			result = userInterface->updateArtistAge();
			cout << result << endl;
			break;
		}
		case 6:{
			result = userInterface->updateArtistEmailId();
			cout << result << endl;
			break;
		}
		case 7:{
			result = userInterface->updateAlbum();
			cout << result << endl;
			break;
		}
		case 8:{
			result = userInterface->updatePlaylist();
			cout << result << endl;
			break;
		}
		default:{
			cout << "Enter correct value" << endl;
			break;
		}
		}
	}
}