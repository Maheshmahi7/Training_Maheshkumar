#include <iostream>
#include <cstdlib>
#include <thread>
#include "RequestDAO.h"
#include <time.h>
#include <future>

using namespace std;

void menu();
int checkUserInput();
RequestDAO requestDAO;
void asyncCheckingEnd();
void asyncGetUserInput();
void asyncAutomatic();
bool check = true;
int requestTime = 0;

void main(){
	int choice;
	LOOP:
	cout << "1.Automatic Simulation." << endl;
	cout << "2.Manual Simulation." << endl;
	cout << "3.Exit." << endl;
	cout << "Enter your choice:" << endl;
	cin >> choice;
	if (cin.fail()){
		choice = checkUserInput();
	}
	system("cls");
	requestDAO.startSimulation();
	async(asyncCheckingEnd);
	switch (choice)
	{
	case 1:
		async(asyncAutomatic);
		break;
	case 2:
		async(asyncGetUserInput);
		break;
	case 3:
		exit(0);
	default:
		cout << "Enter Correct value(1-3):" << endl;
		goto LOOP;
		break;
	}
	while (check)
	{

	}
	//fut.wait_for(chrono::seconds(20));
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
void asyncCheckingEnd() {
	while (1)
	{
		if (!requestDAO.endSimulation())
		{
			check = false;
		}
		this_thread::sleep_for(chrono::seconds(1));
		requestDAO.checkFlag();
	}
}

/*Thread method to get input from the user*/
void asyncGetUserInput() {
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
			requestDAO.createRequest();
			break;
		default:
			cout << "Enter the correct value" << endl;
			break;
		}
		this_thread::sleep_for(chrono::seconds(10));
	} 
}

/*Thread Method for automatic Input*/
void asyncAutomatic(){
	while (check)
	{
		time_t now = time(0);
		struct tm ltm = *localtime(&now);
		int random = (requestDAO.random() % 10);
		if (requestTime == 0){
			cout << "Request Created:" << endl;
			requestDAO.createRequest();
			requestTime = (ltm.tm_min + random) % 60;
		}
		else if (requestTime == ltm.tm_min){
			cout << "Request Created:" << endl; 
			requestDAO.createRequest();
			requestTime = (ltm.tm_min + random) % 60;
		}
		this_thread::sleep_for(chrono::seconds(8));
	}
}