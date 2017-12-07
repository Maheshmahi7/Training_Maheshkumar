#ifndef QueueEmployee_HEADER
#define QueueEmployee_HEADER
#define MAX_SIZE 10

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
	string enqueue(Employee employee);
	string dequeue();
	
	void display();
	bool isEmpty();
	bool isFull();
private:
	vector<Employee> benchV;
	int rear, front;
};

#endif