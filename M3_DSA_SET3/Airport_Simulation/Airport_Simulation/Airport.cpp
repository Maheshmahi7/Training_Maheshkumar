#include "Airport.h"

int requestId = 0, id;

Airport::Airport(){}

Airport::~Airport(){}

/*Method for strating the simulation and set the ending time*/
void Airport::startSimulation(){
	string temp;
	ifstream f("SimulationVariable.txt");
	f >> temp >> runwayWaitingTime >> temp >> timeElapse;
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
void Airport::createRequest()
{
	int type;
	id = id + random() + requestId;
	Aeroplane aeroplane;
	Request request;
	string planeid = "ASW" + to_string(id);
	aeroplane.setAeroplaneNumber(planeid);
	aeroplane.setAeroplaneName(planeid);
	aeroplane.setAeroplaneCapacity(250);
	aeroplane.setAeroplaneType("PASSENGER");
	aeroplaneV.push_back(aeroplane);
	requestId++;
	request.setRequestId(requestId);
	request.setAeroplaneId(planeid);
	time_t now = time(0);
	request.setRequestedTime(now);
	type = random() % 2;
	request.setRequestType(type);
	cout << type << endl;
	cout << "Request Id: " << setfill('0') << request.getRequestId() << endl;
	(!type) ? cout << "Landing Request" << endl : cout << "Takeoff Request" << endl;
	response(request);
}

/*Method to identify the type of request recieved*/
void Airport::response(Request request){
	if (!request.getRequestType()){
		landing.enqueue(request);
		cout << "Request Id: " << request.getRequestId() << " added to the landing queue" << endl;
		cout << endl;
		land();
	}
	else if (request.getRequestType()){
		depature.enqueue(request);
		cout << "Request Id: " << request.getRequestId() << " added to the takeoff queue" << endl;
		cout << endl;
		takeoff();
	}
}

/*Method for approving the landing*/
void Airport::land(){
	Request request;
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	if (!landing.isEmpty()){
		if (!runway1){
			runway1OccupidTime = (ltm.tm_min);
			request = landing.dequeue();
			requestCompleted(request, "Landed", "Runway 1", now);
			runway1 = 1;
		}
	}
	if (!landing.isEmpty()){
		if (!runway2){
			runway2OccupidTime = (ltm.tm_min);
			request = landing.dequeue();
			requestCompleted(request, "Landed", "Runway 2", now);
			runway2 = 1;
		}
	}
}

/*Method for approving the takeoff*/
void Airport::takeoff(){
	Request request;
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	if (landing.isEmpty()){
		if (!depature.isEmpty()){
			if (!runway1){
				runway1OccupidTime = (ltm.tm_min);
				request = depature.dequeue();
				requestCompleted(request, "Departed", "Runway 1", now);
				runway1 = 1;
			}
		}
		if (!depature.isEmpty()){
			if (!runway2){
				runway2OccupidTime = (ltm.tm_min);
				request = depature.dequeue();
				requestCompleted(request, "Departed", "Runway 2", now);
				runway2 = 1;
			}
		}
	}
	else
	{
		land();
	}
}
/*Method to put the completed request into its appropriate vector*/
void Airport::requestCompleted(Request request, string status, string runway, time_t time){
	request.setRequestCleared(time);
	request.setStatus(status);
	request.setRunway(runway);
	if (!request.getRequestType()){
		getLandingWaitingTime(request.getRequestedTime(), request.getRequestCleared());
		arrived.push_back(request);
	}
	else if (request.getRequestType()){
		getTakeoffWaitingTime(request.getRequestedTime(), request.getRequestCleared());
		departured.push_back(request);
	}
	cout << "************************************" << endl;
	cout << "Request Id: " << request.getRequestId() << " Served" << endl;
	cout << "Aeroplane: " << request.getAeroplaneId() << " " << request.getStatus() << " Successfully" << endl;
	cout << "************************************" << endl;
}



/*Method to check whether the simulation time limit reached or not*/
bool Airport::endSimulation(){

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
void Airport::checkRunway(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	int min = (ltm.tm_min);
	if (runway1){
		runway1WaitingTime = (runway1OccupidTime + runwayWaitingTime) % 60;
		if (min == (runway1WaitingTime)){
			runway1 = 0;
			takeoff();
		}
	}
	if (runway2){
		runway2WaitingTime = (runway2OccupidTime + runwayWaitingTime) % 60;
		if (min == (runway2WaitingTime)){
			runway2 = 0;
			takeoff();
		}
	}
}

/*Method to get landing waiting time*/
void Airport::getLandingWaitingTime(time_t requestedTime, time_t clearedTime){
	averageLandingWaitingTime = averageLandingWaitingTime + difftime(clearedTime, requestedTime);
}

/*Method to get takeoff waiting time*/
void Airport::getTakeoffWaitingTime(time_t requestedTime, time_t clearedTime){
	averageTakeoffWaitingTime = averageTakeoffWaitingTime + difftime(clearedTime, requestedTime);
}

/*Method to calculate the average waiting time of the request*/
void Airport::calculateAverageWaitingTime(int waitingTime){
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
void Airport::summary(){
	if (!arrived.empty()){
		cout << "No of Aeroplanes Landed: " << setfill('0') << arrived.size() << endl;
		cout << endl;
		if (!landing.isEmpty()){
			cout << "Unserved Landing request: " << setfill('0') << landing.getSize() << endl;
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
		cout << "No Landing Request to serve" << endl;
		cout << endl;
	}
	if (!departured.empty()){
		cout << "No of Aeroplanes Departed: " << setfill('0') << departured.size() << endl;
		cout << endl;
		if (!depature.isEmpty()){
			cout << "Unserved Takeoff request: " << setfill('0') << depature.getSize() << endl;
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
		cout << "No Takeoff Request to serve" << endl;
		cout << endl;
	}
}

/*Method to set random value to aeroplane*/
int Airport::random(){
	time_t now = time(0);
	struct tm ltm = *localtime(&now);
	return (ltm.tm_sec % 25);
}
