#include "RequestDAO.h"

int startingHour; 
int startingMin;
int startingSec;
int endingHour;
int endingMin;
int endingSec;

int flag1WTime;
int flag2WTime;
int flag1 = 0;
int flag2 = 0;
int flag1Time;
int flag2Time;

int type;
int id = 1234;

int averageLandingWaitingTime = 0;
int averageTakeoffWaitingTime = 0;

Request request;
Aeroplane aeroplane;

int flagWaitingTime = 1;
int timeElapse = 3;

MyQueue landing;
MyQueue depature;

vector<Request> arrived;
vector<Request> departured;


RequestDAO::RequestDAO(){}

RequestDAO::~RequestDAO(){}

/*Method to set random value to aeroplane*/
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
			requestCompleted(request, "Landed", "Runway 1", now);
			flag1 = 1;
		}
	}
	if(!landing.isEmpty()){
		if (flag2 == 0){
			flag2Time = (1 + ltm.tm_min);
			request = landing.dequeue();
			requestCompleted(request, "Landed", "Runway 2", now);
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
				requestCompleted(request, "Departed", "Runway 1", now);
				flag1 = 1;
			}
		}
		if(!depature.isEmpty()){
			if (flag2 == 0){
				flag2Time = (1 + ltm.tm_min);
				request = depature.dequeue();
				requestCompleted(request, "Departed", "Runway 2", now);
				flag2 = 1;
			}
		}
	}
	else
	{
		land();
	}
}
/*Method to put the completed request into its appropriate vector*/
void RequestDAO::requestCompleted(Request request, string status, string runway,time_t time){
	request.setRequestCleared(time);
	request.setStatus(status);
	request.setRunway(runway);
	if (request.getRequestType() == 0){
		getLandingWaitingTime(request.getRequestedTime(), request.getRequestCleared());
		arrived.push_back(request);
	}
	else if (request.getRequestType() == 1){
		getTakeoffWaitingTime(request.getRequestedTime(), request.getRequestCleared()); 
		departured.push_back(request);
	}
}



/*Method to check whether the simulation time limit reached or not*/
bool RequestDAO::endSimulation(){
	
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	endingSec = startingSec;
		endingMin = startingMin + (endingSec / 60) + timeElapse;
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
	averageLandingWaitingTime = averageLandingWaitingTime + difftime(clearedTime, requestedTime);
}

/*Method to get takeoff waiting time*/
void RequestDAO::getTakeoffWaitingTime(time_t requestedTime, time_t clearedTime){
	averageTakeoffWaitingTime = averageTakeoffWaitingTime + difftime(clearedTime, requestedTime);
}

/*Method to calculate the average waiting time of the request*/
void RequestDAO::calculateAverageWaitingTime(int waitingTime){
	int hours, minutes, seconds;
		seconds = waitingTime % 60;
		waitingTime = waitingTime / 60;
		minutes = waitingTime % 60;
		waitingTime = waitingTime / 60;
		hours = waitingTime % 24;
		cout << "Average Waiting Time: " << setw(2) << setfill('0') << hours << ":" << setfill('0') << minutes << ":" << setfill('0') << seconds << endl;
}



/*Method to display the final result of the simualtion*/
void RequestDAO::summary(){
	cout << "No of Aeroplanes Landed: " << setw(2) << arrived.size() << endl;
	cout << "No of Aeroplanes Departed: " << setw(2) << departured.size() << endl;
	if (!landing.isEmpty()){
		cout << "Unserved Landing request" << setw(2) << landing.size() << endl;
	}
	else
	{
		cout << "All Landing Request are served" << endl;
	}
	if (!depature.isEmpty()){
		cout << "Unserved Takeoff request" << setw(2) << depature.size() << endl;
	}
	else
	{
		cout << "All Takeoff Request are served" << endl;
	}
	if (arrived.size() != 0){
		averageLandingWaitingTime = averageLandingWaitingTime / arrived.size();
		calculateAverageWaitingTime(averageLandingWaitingTime);
	}
	if (departured.size() != 0){
		averageTakeoffWaitingTime = averageTakeoffWaitingTime / departured.size();
		calculateAverageWaitingTime(averageTakeoffWaitingTime);
	}
	landing.display();
	depature.display();
}
