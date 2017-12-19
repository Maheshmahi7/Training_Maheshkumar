#pragma once
#pragma warning(disable : 4996)

#ifndef RequestDAO_HEADER
#define RequestDAO_HEADER

#include "Request.h"
#include "MyQueue.h"
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <fstream>

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
	void calculateAverageWaitingTime(int);
	void requestCompleted(Request,string,string,time_t);
	int checkUserInput();
	void checkFlag();
	void randomX();
	int random();
};

#endif