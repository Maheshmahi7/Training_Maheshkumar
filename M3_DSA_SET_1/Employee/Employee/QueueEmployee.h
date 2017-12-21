#ifndef QueueEmployee_HEADER
#define QueueEmployee_HEADER

#include "Employee.h"
#include<iostream>
#include<vector>
#pragma once

using namespace std;

class QueueEmployee
{
public:
	QueueEmployee();
	~QueueEmployee();
	string enqueue(string);
	string dequeue();
	bool isEmpty();
	vector<string> getQueue();
private:
	vector<string> benchV;
	int rear;
};

#endif