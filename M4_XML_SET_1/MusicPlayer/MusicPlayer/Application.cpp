
#include <string>
#include <iostream>
#include "XMLDom.h"

void main(){

	string value;
	int choice;
		
	XMLDom* doc = new XMLDom("./MusicPlayerData.xml");
	if (doc) {

		while (true)
		{

			cout << "1. Display Songs" << endl;
			cout << "2. Display Artists" << endl;
			cout << "3. Dispaly Albums" << endl;
			cout << "4. Dispaly Playlists" << endl;
			cout << "5. Exit" << endl;
			cin >> choice;
			system("cls");
			switch (choice)
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
				exit(0);
			}
			default:{
				cout << "Enter Correct value" << endl;
				break;
			}
			}
		}
	}
		delete doc;


	cin.ignore(1000, '\n');
	cin.get();
}
