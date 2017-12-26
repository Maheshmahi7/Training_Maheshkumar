#include <iostream>
#include <thread>
#include "Airport.h"
#include <time.h>

using namespace std;

void menu();
int checkUserInput();
Airport airport;
void checkingSimulationEnd();
void generateManualRequest();
void generateAutomaticRequest();
bool check = true;

void main(){
	int userChoice, count = 0;
	while (true)
	{
		cout << "1.Automatic Simulation." << endl;
		cout << "2.Manual Simulation." << endl;
		cout << "3.Exit." << endl;
		cout << "Enter your choice:" << endl;
		cin >> userChoice;
		if (cin.fail()){
			userChoice = checkUserInput();
		}
		system("cls");
		switch (userChoice){
		case 1:
		{
			airport.startSimulation();
			thread automatic(generateAutomaticRequest);
			thread end(checkingSimulationEnd);
			automatic.detach();
			end.detach();
			count = 1;
			break;
		}
		case 2:
		{
			airport.startSimulation();
			thread manual(generateManualRequest);
			thread end(checkingSimulationEnd);
			manual.detach();
			end.detach();
			count = 1;
			break;
		}
		case 3:
		{
			exit(0);
		}
		default:
		{
			cout << "Enter Correct value(1-3): " << endl;
			break;
		}
		}
		if (count == 1){
			break;
		}
	}
	while (check)
	{

	}
	airport.summary();
	cin.clear();
	cin.ignore(1000,'\n');
	cin.get();
}

/*Method for showing the available functionality in the system*/
void menu()
{
	cout << "***********************************************" << endl;
	cout << "1.To create request" << endl;
	cout << "***********************************************" << endl;
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

/*Thread Method to check the runway status and end of simulation*/
void checkingSimulationEnd() {
	while (check)
	{
		if (!airport.endSimulation())
		{
			check = false;
		}
		airport.checkRunway();
		this_thread::sleep_for(chrono::seconds(8));
	}
}

/*Thread method to get input from the user*/
void generateManualRequest() {
	int value;
	while (check){
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
			airport.createRequest();
			break;
		default:
			cout << "Enter the correct value" << endl;
			break;
		}
		this_thread::sleep_for(chrono::seconds(5));
	}
}

/*Thread Method for automatic Input*/
void generateAutomaticRequest(){
	int requestTime = 0;
	while (check)
	{
		time_t now = time(0);
		struct tm ltm = *localtime(&now);
		int random = (airport.random() % 10);
		if (requestTime == ltm.tm_min || requestTime == 0){
			cout << "Request Created:" << endl;
			airport.createRequest();
			requestTime = (ltm.tm_min + random) % 60;
		}
		this_thread::sleep_for(chrono::seconds(5));
	}
}
