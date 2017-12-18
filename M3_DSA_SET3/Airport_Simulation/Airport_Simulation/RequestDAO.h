#pragma once
#pragma warning(disable : 4996)

#ifndef RequestDAO_HEADER
#define RequestDAO_HEADER

#include "Request.h"
#include "MyQueue.h"
#include <stdlib.h>
#include <vector>

using namespace std;


class RequestDAO
{

public:
	RequestDAO();
	~RequestDAO();

	void startSimulation();
	bool endSimulation();
	void summary();
	void createRequest();
	void response(Request);
	void land();
	void takeoff();
	void getLandingWaitingTime(time_t,time_t);
	void getTakeoffWaitingTime(time_t, time_t);
	void calculateAverageWaitingTime();
	int checkUserInput();
	void checkFlag();
	void random();
};

#endif