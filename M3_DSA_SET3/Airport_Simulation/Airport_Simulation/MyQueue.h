#ifndef MyQueue_HEADER
#define MyQueue_HEADER

#include<iostream>
#include<vector>
#include "Request.h"
#pragma once

using namespace std;

class MyQueue
{
public:
	MyQueue();
	~MyQueue();
	string enqueue(Request);
	Request dequeue();
	void display();
	bool isEmpty();
private:
	int rear;
	int front;
	vector<Request> elements;
};

#endif