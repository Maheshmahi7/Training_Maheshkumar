#include "AirportDAO.h"




AirportDAO::AirportDAO()
{

}


AirportDAO::~AirportDAO()
{
}

void AirportDAO::start(){

}


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
	approval();
}



void AirportDAO::request(Airport airport){
	if (airport.getRequestType == 0){
			landing.enqueue(airport);
	}
	else if (airport.getRequestType == 1){
		takeoff.enqueue(airport);
	}
}

void AirportDAO::approval(){

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
		else if (flag2 == 0){
			airport = landing.dequeue();
			time_t now;
			airport.setRequestCleared(now);
			airport.setStatus("Landed");
			airport.setStatus("Runway 2");
			arrived.push_back(airport);
			flag2 = 1;
		}
	}
	else if (!takeoff.isEmpty){
		if (flag1 == 0){
			airport = takeoff.dequeue();
			time_t now;
			airport.setRequestCleared(now);
			airport.setStatus("Departed");
			airport.setStatus("Runway 1");
			departured.push_back(airport);
			flag1 = 1;
		}
		else if (flag2 == 0){
			airport = takeoff.dequeue();
			time_t now;
			airport.setRequestCleared(now);
			airport.setStatus("departed");
			airport.setStatus("Runway 2");
			departured.push_back(airport);
			flag2 = 1;
		}
	}

}







