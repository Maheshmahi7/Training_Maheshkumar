#include "AirportDAO.h"

AirportDAO::AirportDAO()
{

}


AirportDAO::~AirportDAO()
{
}

/*Method for strating the simulation time*/
void AirportDAO::startSimulation(){

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
	time_t now;
	airport.setRequestedTime(now);
	int type = rand() % 2;
	airport.setRequestType(type);
	request(airport);
}

/*Method to identify the type of request recieved*/
void AirportDAO::request(Airport airport){
	if (airport.getRequestType == 0){
			landing.enqueue(airport);
			land();
	}
	else if (airport.getRequestType == 1){
		depature.enqueue(airport);
		takeoff();
	}
}

/*Method for approving the landing*/
void AirportDAO::land(){

	if (!landing.isEmpty){
		if (flag1 == 0){
			airport = landing.dequeue();
			time_t now;
			airport.setRequestCleared(now);
			airport.setStatus("Landed");
			airport.setStatus("Runway 1");
			arrived.push_back(airport);
			flag1 = 1;
		}
	}
	if(!landing.isEmpty()){
		if (flag2 == 0){
			airport = landing.dequeue();
			time_t now;
			airport.setRequestCleared(now);
			airport.setStatus("Landed");
			airport.setStatus("Runway 2");
			arrived.push_back(airport);
			flag2 = 1;
		}
	}
}

/*Method for approving the takeoff*/
void AirportDAO::takeoff(){
	if (landing.isEmpty()){
		if (!depature.isEmpty){
			if (flag1 == 0){
				airport = depature.dequeue();
				time_t now;
				airport.setRequestCleared(now);
				airport.setStatus("Departed");
				airport.setStatus("Runway 1");
				departured.push_back(airport);
				flag1 = 1;
			}
		}
		if(!depature.isEmpty()){
			if (flag2 == 0){
				airport = depature.dequeue();
				time_t now;
				airport.setRequestCleared(now);
				airport.setStatus("departed");
				airport.setStatus("Runway 2");
				departured.push_back(airport);
				flag2 = 1;
			}
		}
	}
}

/*Method to check whether the simulation time limit reached or not*/
bool AirportDAO::endSimulation(){
	return true;
}

/*Method to display the final result of the simualtion*/
void AirportDAO::summary(){

}



