#pragma once

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
	int checkUserInput();
};

#endif