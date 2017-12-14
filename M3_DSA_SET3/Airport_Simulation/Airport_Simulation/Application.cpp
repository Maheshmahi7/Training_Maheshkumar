
#include <iostream>
#include <cstdlib>
#include <thread>
#include "AirportDAO.h"

using namespace std;


void menu();
void create(AirportDAO);
int checkUserInput();

void main(){
	int value;
	AirportDAO airportDAO;
	system("cls");
	airportDAO.start();
	while (true)
	{
		menu();
		cin >> value;
		if (cin.fail())
		{
			value = checkUserInput();
		}
		AirportDAO *airportDAO = new AirportDAO();
		switch (value)
		{
		case 1: 	
			create(*airportDAO);
			break;
		case 2:
			exit(0);
		default:
			cout << "Enter the correct value" << endl;
			break;
		}
	}
	

	cin.clear();
	cin.ignore(1000, '\n');
	cin.get();
}


void menu()
{
	cout << "***********************************************" << endl;
	cout << "1.To create request" << endl;
	cout << "2.Exit" << endl;
	cout << "***********************************************" << endl;
}

void create(AirportDAO airportDao)
{
	thread request(&AirportDAO::createRequest,airportDao);
	request.join();
}

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