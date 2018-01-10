
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "XMLDom.h"

void main(){

	string value;
	XMLDom* doc;
		
		
	doc = new XMLDom("./MusicPlayerData.xml");
	if (doc) {
		for (int i = 0; i < doc->getChildCount("music_player", 0, "songs"); i++) {
			cout << "Music Player " << endl;
			for (int j = 0; j < doc->getChildCount("songs",0,"song"); j++ ){
				cout << "\t Songs          " << j + 1;
				value = doc->getChildAttribute("songs", 0, "song", j, "ID");
				cout << "\t Song ID        " << value.c_str() << endl;
				value = doc->getChildValue("song", j, "song_name", 0);
				cout << "\t Song Name      " << value.c_str() << endl; 
				value = doc->getChildValue("song", j, "duration", 0);
				cout << "\t Song Duration  " << value.c_str() << endl;
				value = doc->getChildValue("song", j, "song_album", 0);
				cout << "\t Song Album     " << value.c_str() << endl;
				cout << "\t Artists:" << endl;
				for (int k = 0; k < doc->getChildCount("song_artists", 0, "song_artist"); k++) {
					value = doc->getChildValue("song_artists", k, "song_artist", 0);
				cout << "\t \t Song Artist    " << value.c_str() << endl;
				}
			}
			/*for (int j = 0; j < doc->getChildCount(); j++){

			}*/
		}
		cout << "Root Element count: " << doc->getRootElementCount("song") << endl;
		delete doc;
	}


/*		 doc = new XMLDom("./bookstore.xml");
	if (doc) {
		for (int i = 0; i < doc->getChildCount("bookstore", 0, "book"); i++) {
			printf("Book %d\n", i + 1);
			value = doc->getChildAttribute("bookstore", 0, "book", i, "category");
			printf("book category   - %s\n", value.c_str());
			value = doc->getChildValue("book", i, "title", 0);
			printf("book title      - %s\n", value.c_str());
			value = doc->getChildAttribute("book", i, "title", 0, "lang");
			printf("book title lang - %s\n", value.c_str());
			value = doc->getChildValue("book", i, "author", 0);
			printf("book author     - %s\n", value.c_str());
			value = doc->getChildValue("book", i, "year", 0);
			printf("book year       - %s\n", value.c_str());
			value = doc->getChildValue("book", i, "price", 0);
			printf("book price      - %s\n", value.c_str());
		}
		delete doc;
	}
	*/
	cin.ignore(1000, '\n');
	cin.get();
}
