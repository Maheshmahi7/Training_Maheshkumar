#pragma once

#ifndef Airport_HEADER
#define Airport_HEADER

#include "Aeroplane.h"
#include<vector>
#include<time.h>
#include<ctime>


using namespace std;

class Airport
{
private:
	Aeroplane aeroplane;
	time_t requestedTime;
	time_t requestCleared;
	int requestType;
	string status;
	string runway;


public:
	Airport();
	~Airport();
	void setRequestType(int);
	int getRequestType();
	void setAeroplane(Aeroplane);
	Aeroplane getAeroplane();
	void setRequestedTime(time_t);
	time_t getRequestedTime();
	void setRequestCleared(time_t);
	time_t getRequestCleared();
	void setStatus(string);
	string getStatus();
	void setRunway(string);
	string getRunway();

};

#endif