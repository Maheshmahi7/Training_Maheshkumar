
#include <iostream>
#include <cstdlib>
#include <thread>
#include "RequestDAO.h"
#include <time.h>

using namespace std;


void menu();
void create(RequestDAO);
int checkUserInput();
RequestDAO requestDAO;

void main(){
	int value;
	system("cls");
	requestDAO.startSimulation();
	RequestDAO request;
	while (requestDAO.endSimulation())
	{
		menu();
		cin >> value;
		if (cin.fail())
		{
			value = checkUserInput();
		}
		
		system("cls");
		switch (value)
		{
		case 1:
			create(request);
			break;
		case 2:
			break;
		default:
			cout << "Enter the correct value" << endl;
			break;
		}
		requestDAO.checkFlag();
	}
	
	requestDAO.summary();

	cin.clear();
	cin.ignore(1000, '\n');
	cin.get();
}

/*Method for showing the available functionality in the system*/
void menu()
{
	cout << "***********************************************" << endl;
	cout << "1.To create request" << endl;
	cout << "2.Exit" << endl;
	cout << "***********************************************" << endl;
}

/*Thread method for invoking the request*/
void create(RequestDAO request)
{
	thread requestT(&RequestDAO::createRequest, request);
	requestT.join();
}

/*Method to validate the user input.*/
int checkUserInput()
{
	int input;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cout << "Enter the correct value" << endl;
			cin >> input;
		}
		else if (!cin.fail()) {
			return input;
			break;
		}
	}
}