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
int id;

int averageLandingWaitingTime = 0;
int averageTakeoffWaitingTime = 0;

Request request;
Aeroplane aeroplane;

int flagWaitingTime;
int timeElapse;


MyQueue landing;
MyQueue depature;

vector<Request> arrived;
vector<Request> departured;


RequestDAO::RequestDAO(){}

RequestDAO::~RequestDAO(){}


/*Method for strating the simulation and set the ending time*/
void RequestDAO::startSimulation(){
	ifstream f;
	f.open("SimulationVariable.txt");
	f >> flagWaitingTime >> timeElapse;
	f.close();
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	startingHour = (ltm.tm_hour);
	startingMin = (ltm.tm_min);
	startingSec = (ltm.tm_sec);

	endingSec = startingSec;
	endingMin = startingMin + (endingSec / 60) + timeElapse;
	endingSec = endingSec % 60;
	endingHour = startingHour + (endingMin / 60);
	endingMin = endingMin % 60;
	endingHour = endingHour % 24;

}

/*Method for creating the request based on thread response*/
void RequestDAO::createRequest()
{
	id = random();
	string planeid = "ASW" + to_string(id);
	aeroplane.setAeroplaneNumber(planeid);
	aeroplane.setAeroplaneName(planeid);
	aeroplane.setAeroplaneCapacity(250);
	aeroplane.setAeroplaneType("PASSENGER");
	request.setAeroplane(aeroplane);
	time_t now = time(0);
	request.setRequestedTime(now);
	type = random() % 2;
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
			flag1Time = (ltm.tm_min);
			request = landing.dequeue();
			requestCompleted(request, "Landed", "Runway 1", now);
			flag1 = 1;
		}
	}
	if(!landing.isEmpty()){
		if (flag2 == 0){
			flag2Time = (ltm.tm_min);
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
				flag1Time = (ltm.tm_min);
				request = depature.dequeue();
				requestCompleted(request, "Departed", "Runway 1", now);
				flag1 = 1;
			}
		}
		if(!depature.isEmpty()){
			if (flag2 == 0){
				flag2Time = (ltm.tm_min);
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

		if ((ltm.tm_hour) == endingHour){
			if ((ltm.tm_min) == endingMin){
				if ((ltm.tm_sec) < endingSec){
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		return true;		
}

/*Method to reallocated the runway using flags*/
void RequestDAO::checkFlag(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	int min = (ltm.tm_min);
	int hour = (ltm.tm_hour);
	int flag1WaitingHour;
	int flag2WaitingHour;
	if (flag1 == 1){
		flag1WTime = (flag2Time + flagWaitingTime);
		flag1WaitingHour = hour + (flag1WTime / 60);
		flag1WTime = flag1WTime % 60;
		if (hour == flag1WaitingHour){
			if (min == (flag1WTime)){
				flag1 = 0;
				takeoff();
			}
		}
	}
	if (flag2 == 1){
		flag2WTime = (flag2Time + flagWaitingTime);
		flag2WaitingHour = hour + (flag2WTime / 60);
		flag2WTime = flag2WTime % 60;
		if (hour == flag2WaitingHour){
			if (min == (flag2WTime)){
				flag2 = 0;
				takeoff();
			}
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
	int hours = 00, minutes = 00, seconds = 00;
		seconds = waitingTime % 60;
		waitingTime = waitingTime / 60;
		minutes = waitingTime % 60;
		waitingTime = waitingTime / 60;
		hours = waitingTime % 24;
		cout << "Average Waiting Time: " << setw(2) << setfill('0') << hours << ":" << setfill('0') << minutes << ":" << setfill('0') << seconds << endl;
		cout << endl;
}



/*Method to display the final result of the simualtion*/
void RequestDAO::summary(){
	if (!arrived.empty()){
		cout << "No of Aeroplanes Landed: " << setfill('0') << arrived.size() << endl;
		cout << endl;
		if (!landing.isEmpty()){
			cout << "Unserved Landing request: " << setfill('0') << landing.size() << endl;
			cout << endl;
			landing.display();
		}
		else
		{
			cout << "All Landing Request are served" << endl;
			cout << endl;
		}
		averageLandingWaitingTime = averageLandingWaitingTime / arrived.size();
		calculateAverageWaitingTime(averageLandingWaitingTime);
	}
	else
	{
		cout << "No Request to serve" << endl;
		cout << endl;
	}
	if (!departured.empty()){
		cout << "No of Aeroplanes Departed: " << setfill('0') << departured.size() << endl;
		cout << endl;
		if (!depature.isEmpty()){
			cout << "Unserved Takeoff request: " << setfill('0') << depature.size() << endl;
			cout << endl;
			depature.display();
		}
		else
		{
			cout << "All Takeoff Request are served" << endl;
			cout << endl;
		}
		averageTakeoffWaitingTime = averageTakeoffWaitingTime / departured.size();
		calculateAverageWaitingTime(averageTakeoffWaitingTime);
	}
	else
	{
		cout << "No Request to serve" << endl;
		cout << endl;
	}
}

/*Method to set random value to aeroplane*/
int RequestDAO::random(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	return (ltm.tm_sec % 25);
}