#pragma once
#pragma warning(disable : 4996)

#ifndef Airport_HEADER
#define Airport_HEADER

#include "Request.h"
#include "MyQueue.h"
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;


class Airport
{

public:
	Airport();
	~Airport();

	void startSimulation();
	bool endSimulation();
	void summary();
	void createRequest();
	void checkFlag();
	int random();

private:
	Request request;
	Aeroplane aeroplane;
	vector<Aeroplane> aeroplaneV;

	MyQueue landing;
	MyQueue depature;

	vector<Request> arrived;
	vector<Request> departured;

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

	double averageLandingWaitingTime = 0;
	double averageTakeoffWaitingTime = 0;

	int flagWaitingTime;
	int timeElapse;

	void response(Request);
	void land();
	void takeoff();
	void getLandingWaitingTime(time_t, time_t);
	void getTakeoffWaitingTime(time_t, time_t);
	void calculateAverageWaitingTime(int);
	void requestCompleted(Request, string, string, time_t);
};

#endif