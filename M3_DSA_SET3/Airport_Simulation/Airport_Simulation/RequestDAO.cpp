#include "RequestDAO.h"

int startingHour; 
int startingMin;
int startingSec;
int endingHour;
int endingMin;
int endingSec;
int flagWaitingTime = 1;
int flag1WTime;
int flag2WTime;

time_t averageLandingWaitingTime = 0;
time_t averageTakeoffWaitingTime = 0;

Request request;
Aeroplane aeroplane;

int flag1 = 0;
int flag2 = 0;
int flag1Time;
int flag2Time;

MyQueue landing;
MyQueue depature;

vector<Request> arrived;
vector<Request> departured;

int type;
int id=1234;

RequestDAO::RequestDAO()
{

}


RequestDAO::~RequestDAO()
{
}

void RequestDAO::random(){
	type = id % 2;
	id++;
}


/*Method for strating the simulation time*/
void RequestDAO::startSimulation(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	startingHour = (1 + ltm.tm_hour);
	startingMin = (1 + ltm.tm_min);
	startingSec = (1 + ltm.tm_sec);

}

/*Method for creating the request based on thread response*/
void RequestDAO::createRequest()
{
	random();
	string planeid = "ASW" + to_string(id);
	aeroplane.setAeroplaneNumber(planeid);
	aeroplane.setAeroplaneName(planeid);
	aeroplane.setAeroplaneCapacity(250);
	aeroplane.setAeroplaneType("PASSENGER");
	request.setAeroplane(aeroplane);
	time_t now = time(0);
	request.setRequestedTime(now);

	request.setRequestType(type);
	response(request);
}

/*Method to identify the type of request recieved*/
void RequestDAO::response(Request request){
	if (request.getRequestType() == 0){
			landing.enqueue(request);
			land();
	}
	else if (request.getRequestType() == 1){
		depature.enqueue(request);
		takeoff();
	}
}

/*Method for approving the landing*/
void RequestDAO::land(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);

	if (!landing.isEmpty()){
		if (flag1 == 0){
			flag1Time = (1 + ltm.tm_min);
			request = landing.dequeue();
			request.setRequestCleared(now);
			getLandingWaitingTime(request.getRequestedTime(), request.getRequestCleared());
			request.setStatus("Landed");
			request.setRunway("Runway 1");
			arrived.push_back(request);
			flag1 = 1;
		}
	}
	if(!landing.isEmpty()){
		if (flag2 == 0){
			flag2Time = (1 + ltm.tm_min);
			request = landing.dequeue();
			request.setRequestCleared(now);
			getLandingWaitingTime(request.getRequestedTime(), request.getRequestCleared()); 
			request.setStatus("Landed");
			request.setRunway("Runway 2");
			arrived.push_back(request);
			flag2 = 1;
		}
	}
}

/*Method for approving the takeoff*/
void RequestDAO::takeoff(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	if (landing.isEmpty()){

		if (!depature.isEmpty()){

			if (flag1 == 0){
				flag1Time = (1 + ltm.tm_min);
				request = depature.dequeue();
				request.setRequestCleared(now);
				getTakeoffWaitingTime(request.getRequestedTime(), request.getRequestCleared());	request.setStatus("Departed");
				request.setRunway("Runway 1");
				departured.push_back(request);
				flag1 = 1;
			}

		}

		if(!depature.isEmpty()){

			if (flag2 == 0){
				flag2Time = (1 + ltm.tm_min);
				request = depature.dequeue();
				request.setRequestCleared(now);
				getTakeoffWaitingTime(request.getRequestedTime(), request.getRequestCleared()); 
				request.setStatus("departed");
				request.setRunway("Runway 2");
				departured.push_back(request);
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
bool RequestDAO::endSimulation(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	endingSec = startingSec;
		endingMin = startingMin + (endingSec / 60) + 3;
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
void RequestDAO::checkFlag(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	int min = (1 + ltm.tm_min);
	if (flag1 == 1){
		flag1WTime = (flag2Time + flagWaitingTime) % 60;
		if ( min == (flag1WTime)){
			flag1 = 0;
			takeoff();
		}
	}
	if (flag2 == 1){
		flag2WTime = (flag2Time + flagWaitingTime) % 60;
		if (min == (flag2WTime)){
			flag2 = 0;
			takeoff();
		}
	}
}

/*Method to get landing waiting time*/
void RequestDAO::getLandingWaitingTime(time_t requestedTime, time_t clearedTime){
	averageLandingWaitingTime = averageLandingWaitingTime + difftime(requestedTime, clearedTime);
}

/*Method to get takeoff waiting time*/
void RequestDAO::getTakeoffWaitingTime(time_t requestedTime, time_t clearedTime){
	averageTakeoffWaitingTime = averageTakeoffWaitingTime + difftime(requestedTime, clearedTime);
}

void RequestDAO::calculateAverageWaitingTime(){
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
void RequestDAO::summary(){
	cout << "No of Aeroplanes Landed: " << arrived.size() << endl;
	cout << "No of Aeroplanes Departed: " << departured.size() << endl;
	//calculateAverageWaitingTime();
}
