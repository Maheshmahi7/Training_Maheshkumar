#include<iostream>
#include "Avl_treeDAO.h"

using namespace std;

void main(){

	string status;

	Avl_treeDAO avlTreeDAO;

	/*Looping statement for User Interface*/
	while (true){
		int value;
		cout << "1.Insert into Tree" << endl;
		cout << "2.Mirror of the Tree" << endl;
		cout << "3.No of product in a given price" << endl;
		cout << "4.Display Tree" << endl;
		cout << "5.Exit" << endl;
		cin >> value;
		/*User input validation*/
		if (cin.fail())
		{
			value = avlTreeDAO.checkUserInput();
		}
		system("cls");
		switch (value){
		case 1: status = avlTreeDAO.insert();//Calling Insert function
				cout << status << endl;
				break;
		case 2: avlTreeDAO.mirrorTree();//Calling mirror function
					break;
		case 3: avlTreeDAO.getNoOfProduct();//Calling get no of product function
					   break;
		case 4: avlTreeDAO.display();//Calling display function
				break;
			case 5: exit(0);//exiting the application
			default:
				cout << "Invalid value Enter correct value" << endl;
				break;
			}
	}	
	cin.ignore(100, '\n');
	cin.get();
}