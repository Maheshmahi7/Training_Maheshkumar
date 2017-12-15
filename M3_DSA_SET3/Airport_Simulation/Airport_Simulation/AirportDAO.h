#pragma once
#pragma warning(disable : 4996)

#ifndef AirportDAO_HEADER
#define AirportDAO_HEADER

#include "Airport.h"
#include "MyQueue.h"
#include <stdlib.h>
#include <vector>

using namespace std;


class AirportDAO
{
private:
	Airport airport;
	Aeroplane aeroplane;
	int flag1=0, flag2=0;
	int flag1Time, flag2Time;
	MyQueue landing, depature;
	vector<Airport> arrived, departured;

public:
	AirportDAO();
	~AirportDAO();

	void startSimulation();
	bool endSimulation();
	void summary();
	void createRequest();
	void request(Airport);
	void land();
	void takeoff();
	void getLandingWaitingTime(time_t,time_t);
	void getTakeoffWaitingTime(time_t, time_t);
	void calculateAverageWaitingTime();
	int checkUserInput();
	void checkFlag();
};

#endif