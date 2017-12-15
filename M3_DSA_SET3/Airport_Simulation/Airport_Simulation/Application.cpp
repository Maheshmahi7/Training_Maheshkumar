
#include <iostream>
#include <cstdlib>
#include <thread>
#include "AirportDAO.h"
#include <time.h>

using namespace std;


void menu();
void create(AirportDAO);
int checkUserInput();
AirportDAO airportDAO;

void main(){
	int value;
	system("cls");
	airportDAO.startSimulation();
	AirportDAO *airport=new AirportDAO();
	while (airportDAO.endSimulation())
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
			create(*airport);
			break;
		case 2:
			break;
		default:
			cout << "Enter the correct value" << endl;
			break;
		}
		airportDAO.checkFlag();
	}
	
	airportDAO.summary();

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
void create(AirportDAO airport)
{
	thread request(&AirportDAO::createRequest, airport);
	request.join();
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