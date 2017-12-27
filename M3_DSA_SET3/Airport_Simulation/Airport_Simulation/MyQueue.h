#ifndef MyQueue_HEADER
#define MyQueue_HEADER
#pragma warning(disable : 4996)


#include<iostream>
#include<vector>
#include "Request.h"
#include<iomanip>
#pragma once

using namespace std;
/*
  
*/
class MyQueue
{
public:
	MyQueue();
	~MyQueue();
	string enqueue(Request);
	Request dequeue();
	void display();
	bool isEmpty();
	int getSize();


private:
	vector<Request> elements;
};

#endif