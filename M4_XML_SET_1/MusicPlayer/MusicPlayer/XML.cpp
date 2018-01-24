#include "XML.h"


XML::XML()
{
	XMLPlatformUtils::Initialize();
	Dom = new XMLDom();
	Dom->createParser();
	DomDoc = Dom->getDomDoc();
}


XML::~XML()
{
	XMLPlatformUtils::Terminate();
}

void XML::userUI(){
	int choice;

	/*loop to get the user input and perform respective operations*/
	/*calling the parser to parse the xml file*/
	if (DomDoc){
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
				XMLDomReader* doc = new XMLDomReader(DomDoc);
				int readChoice;
				if (doc) {
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
							doc->displaySongs();
							break;
						}
						case 2:{
							doc->displayArtists();
							break;
						}
						case 3:{
							doc->displayAlbums();
							break;
						}
						case 4:{
							doc->displayPlaylists();
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
				}
				else
				{
					cout << "The Xml file is not available" << endl;
				}
				break;
			}
			case 2:{
				/*creating instance for writing into xml file in the memory*/
				XMLDomWritter* doc = new XMLDomWritter(DomDoc);
				int writeChoice;
				if (doc) {
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
							DomDoc = doc->addElementSong();
							cout << "Song Added" << endl;
							break;
						}
						case 2:{
							DomDoc = doc->addElementArtist();
							cout << "Artist Added" << endl;
							break;
						}
						case 3:{
							DomDoc = doc->addElementAlbum();
							cout << "Album Added" << endl;
							break;
						}
						case 4:{
							DomDoc = doc->createPlaylist();
							cout << "Playlist Created" << endl;
							break;
						}
						case 5:{
							writeLoop = false;
							doc->addElementToFile();
							break;
						}
						default:{
							cout << "Enter correct value" << endl;
							break;
						}
						}
					}
				}
				else
				{
					cout << "The Xml file is not avilable" << endl;
				}
				break;
			}
			case 3:{
				exit(0);
			}
			default:
				cout << "Enter correct value" << endl;
				break;
			}

		}
	}
	else
	{
		cout << "File is not available" << endl;
	}
}

/*Main menu for getting user choice*/
void XML::menu(){
	cout << "1.Read Music Player" << endl;
	cout << "2.Add items to Music Player" << endl;
	cout << "3.Exit" << endl;
}

/*read menu to read the xml file on user choice*/
void XML::readMenu(){
	cout << "1. Display Songs" << endl;
	cout << "2. Display Artists" << endl;
	cout << "3. Dispaly Albums" << endl;
	cout << "4. Dispaly Playlists" << endl;
	cout << "5. Go Back" << endl;
}
/*write menu to write into xml based on user choice*/
void XML::writeMenu(){
	cout << "1.Add Song" << endl;
	cout << "2.Add Artist" << endl;
	cout << "3.Add Album" << endl;
	cout << "4.Create Playlist" << endl;
	cout << "5.Go Back" << endl;

}

/*method to validate user input of type integer*/
int XML::checkUserInput() {
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
