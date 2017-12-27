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
bool checkSimulation = true;

/*Main method*/
void main(){
	int userChoice, count = 0;
	while (checkSimulation)
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
			airport.startSimulation();												//statement to start the simulation	
			thread automaticRequest(generateAutomaticRequest);						//thread for creating automatic request
			thread endSimulation(checkingSimulationEnd);							//thread for checking whether the simulation end is reached and runway is free or not
			automaticRequest.join();												//statement to join the threads
			endSimulation.join();													//statement to join the threads
			break;
		}
		case 2:
		{
			airport.startSimulation();												//statement to start the simulation	
			thread manualRequest(generateManualRequest);							//thread for creating manual request
			thread endSimulation(checkingSimulationEnd);							//thread for checking whether the simulation end is reached and runway is free or not
			manualRequest.join();													//statement to join the threads
			endSimulation.join();													//statement to join the threads	
			break;
		}
		case 3:
		{
			exit(0);																//exit statement to exit on user will
		}
		default:
		{
			cout << "Enter Correct value(1-3): " << endl;
			break;
		}
		}
	}
	airport.summary();																//method for displaying the simulation result
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
	while (checkSimulation)
	{
		if (!airport.endSimulation())
		{
			checkSimulation = false;												//set checkSimulation to flase when simulation end to stop all running threads
		}
		airport.checkRunway();														//method to check whether runway is free or not
		this_thread::sleep_for(chrono::seconds(8));									//statement to put the current thread to sleep for particular period
	}
}

/*Thread method to get input from the user*/
void generateManualRequest() {
	int value;
	while (checkSimulation){
		menu();
		cin >> value;																//user will give input as 1 if he/she whats to create request
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
		this_thread::sleep_for(chrono::seconds(5));									//statement to put the current thread to sleep for particular period
	}
}

/*Thread Method for automatic Input*/
void generateAutomaticRequest(){
	int requestTime = 0;
	while (checkSimulation)
	{
		time_t now = time(0);
		struct tm ltm = *localtime(&now);
		int random = (airport.random() % 10);
		if (requestTime == ltm.tm_min || requestTime == 0){							//if request time is equal to correct time then request will be created
			cout << "Request Created:" << endl;
			airport.createRequest();
			requestTime = (ltm.tm_min + random) % 60;								//setting request time to random value;
		}
		this_thread::sleep_for(chrono::seconds(5));									//statement to put the current thread to sleep for particular period
	}
}
