#ifndef MyQueue_HEADER
#define MyQueue_HEADER

#include<iostream>
#include<vector>
#include "Airport.h"
#pragma once

using namespace std;

class MyQueue
{
public:
	MyQueue();
	~MyQueue();
	string enqueue(Airport);
	Airport dequeue();
	void display();
	bool isEmpty();
private:
	vector<Airport> elements;
	int rear, front;
};

#endif