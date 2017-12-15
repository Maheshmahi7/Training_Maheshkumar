#include "AirportDAO.h"

int startingHour, startingMin, startingSec, endingHour, endingMin, endingSec, flagWaitingTime;

time_t averageLandingWaitingTime = 0, averageTakeoffWaitingTime = 0;

AirportDAO::AirportDAO()
{

}


AirportDAO::~AirportDAO()
{
}

/*Method for strating the simulation time*/
void AirportDAO::startSimulation(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	startingHour = (1 + ltm.tm_hour);
	startingMin = (1 + ltm.tm_min);
	startingSec = (1 + ltm.tm_sec);

}

/*Method for creating the request based on thread response*/
void AirportDAO::createRequest()
{
	int id = rand() % 50 + 1111;
	string planeid = "ASW" + to_string(id);
	aeroplane.setAeroplaneNumber(planeid);
	aeroplane.setAeroplaneName(planeid);
	aeroplane.setAeroplaneCapacity(250);
	aeroplane.setAeroplaneType("PASSENGER");
	airport.setAeroplane(aeroplane);
	time_t now = time(0);
	airport.setRequestedTime(now);
	int type = rand() % 2;
	airport.setRequestType(type);
	request(airport);
}

/*Method to identify the type of request recieved*/
void AirportDAO::request(Airport airport){
	if (airport.getRequestType() == 0){
			landing.enqueue(airport);
			land();
	}
	else if (airport.getRequestType() == 1){
		depature.enqueue(airport);
		takeoff();
	}
}

/*Method for approving the landing*/
void AirportDAO::land(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);

	if (!landing.isEmpty()){
		if (flag1 == 0){
			flag1Time = (1 + ltm.tm_sec);
			airport = landing.dequeue();
			airport.setRequestCleared(now);
			getLandingWaitingTime(airport.getRequestedTime(), airport.getRequestCleared());
			airport.setStatus("Landed");
			airport.setRunway("Runway 1");
			arrived.push_back(airport);
			cout << arrived.size() << endl;
			flag1 = 1;
		}
	}
	if(!landing.isEmpty()){
		if (flag2 == 0){
			flag2Time = (1 + ltm.tm_sec);
			airport = landing.dequeue();
			airport.setRequestCleared(now);
			getLandingWaitingTime(airport.getRequestedTime(), airport.getRequestCleared()); 
			airport.setStatus("Landed");
			airport.setRunway("Runway 2");
			arrived.push_back(airport);
			cout << arrived.size() << endl;
			flag2 = 1;
		}
	}
}

/*Method for approving the takeoff*/
void AirportDAO::takeoff(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	if (landing.isEmpty()){
		if (!depature.isEmpty()){
			if (flag1 == 0){
				flag1Time = (1 + ltm.tm_sec);
				airport = depature.dequeue();
				airport.setRequestCleared(now);
				getTakeoffWaitingTime(airport.getRequestedTime(), airport.getRequestCleared());	airport.setStatus("Departed");
				airport.setRunway("Runway 1");
				departured.push_back(airport);
				//cout << departured.size() << endl;
				flag1 = 1;
			}
		}
		if(!depature.isEmpty()){
			if (flag2 == 0){
				flag2Time = (1 + ltm.tm_sec);
				airport = depature.dequeue();
				airport.setRequestCleared(now);
				getTakeoffWaitingTime(airport.getRequestedTime(), airport.getRequestCleared()); 
				airport.setStatus("departed");
				airport.setRunway("Runway 2");
				departured.push_back(airport);
				cout << departured.size() << endl;
				flag2 = 1;
			}
		}
	}
	else
	{
		land();
	}
}

/*Method to check whether the simulation time limit reached or not*/
bool AirportDAO::endSimulation(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	endingSec = startingSec;
		endingMin = startingMin + (endingSec / 60) + 2;
		endingSec = endingSec % 60;
		endingHour = startingHour + (endingMin / 60);
		endingMin = endingMin % 60;
		endingHour = endingHour % 24;

		if ((1 + ltm.tm_hour) == endingHour){
			if ((1 + ltm.tm_min) == endingMin){
				if ((1 + ltm.tm_sec) < endingSec){
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		
}

/*Method to reallocated the runway using flags*/
void AirportDAO::checkFlag(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	flagWaitingTime = 30;
	if (flag1 == 1){
		flag1Time = (flag1Time + flagWaitingTime) % 60;
		if ((1 + ltm.tm_sec) == (flag1Time + 1)){
			flag1 = 0;
			takeoff();
		}
	}
	if (flag2 == 1){
		flag2Time = (flag2Time + flagWaitingTime) % 60;
		if ((1 + ltm.tm_sec) == (flag2Time + 1)){
			flag2 = 0;
			takeoff();
		}
	}
}

/*Method to get landing waiting time*/
void AirportDAO::getLandingWaitingTime(time_t requestedTime, time_t clearedTime){
	averageLandingWaitingTime = averageLandingWaitingTime + difftime(requestedTime, clearedTime);
}

/*Method to get takeoff waiting time*/
void AirportDAO::getTakeoffWaitingTime(time_t requestedTime, time_t clearedTime){
	averageTakeoffWaitingTime = averageTakeoffWaitingTime + difftime(requestedTime, clearedTime);
}

void AirportDAO::calculateAverageWaitingTime(){
	tm ltm;
	int hours = 0, minutes = 0, seconds = 0, temp;
	if (arrived.size() != 0){
		ltm = *localtime(&averageLandingWaitingTime);
		hours = (1 + ltm.tm_hour);
		minutes = (1 + ltm.tm_min);
		seconds = (1 + ltm.tm_sec);
		temp = (minutes * 60) + (hours * 3600) + seconds;
		temp = temp / arrived.size();
		seconds = temp % 60;
		temp = temp / 60;
		minutes = temp % 60;
		temp = temp / 60;
		hours = temp % 60;
	}
	cout << "Average Waiting Time Landing: " << hours << ":" << minutes << ":" << seconds << endl;
	if (departured.size() != 0){
		ltm = *localtime(&averageTakeoffWaitingTime);
		hours = (1 + ltm.tm_hour);
		minutes = (1 + ltm.tm_min);
		seconds = (1 + ltm.tm_sec);
		temp = (minutes * 60) + (hours * 3600) + seconds;
		temp = temp / arrived.size();
		seconds = temp % 60;
		temp = temp / 60;
		minutes = temp % 60;
		temp = temp / 60;
		hours = temp % 60;
	}
	cout << "Average Waiting Time Takeoff: " << hours << ":" << minutes << ":" << seconds << endl;
}



/*Method to display the final result of the simualtion*/
void AirportDAO::summary(){
	cout << "No of Aeroplanes Landed: " << arrived.size() << endl;
	cout << "No of Aeroplanes Departed: " << departured.size() << endl;
	calculateAverageWaitingTime();
}
