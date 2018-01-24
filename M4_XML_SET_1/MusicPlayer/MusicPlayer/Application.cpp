#include "XML.h"
#include "SQLDatabase.h"

void menu();
int checkUserInput();

void main(){
	int choice;
	bool loop = true;
	while (loop){
		menu();
		cin >> choice;
		if (cin.fail()){
			choice = checkUserInput();
		}
		system("cls");
		switch (choice){
		case 1:{
			XML xml;
			xml.userUI();
			loop = false;
			break;
		}
		case 2:{
			SQLDatabase db;
			db.userUI();
			loop = false;
			break;
		}
		case 3:{
			exit(0);
		}
		default:{
			cout << "Enter Correct value" << endl;
			break;
		}
		}
	}

	cin.get();
	cin.ignore(1000, '\n');
}

void menu(){
	cout << "View/Write Music Player from " << endl;
	cout << "1.XML File" << endl;
	cout << "2.Database" << endl;
	cout << "3.Exit" << endl;
}


int checkUserInput() {
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
