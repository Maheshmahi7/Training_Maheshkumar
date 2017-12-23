#pragma once

#ifndef Request_HEADER
#define Request_HEADER

#include "Aeroplane.h"
#include<vector>
#include<time.h>
#include<ctime>


using namespace std;

class Request
{
private:
	int requestId;
	string aeroplaneId;
	time_t requestedTime;
	time_t requestCleared;
	int requestType;
	string status;
	string runway;


public:
	Request();
	~Request();
	void setRequestId(int);
	int getRequestId();
	void setRequestType(int);
	int getRequestType();
	void setAeroplaneId(string);
	string getAeroplaneId();
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