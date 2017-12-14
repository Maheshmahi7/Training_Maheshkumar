#pragma once

#ifndef Aeroplane_HEADER
#define Aeroplane_HEADER

#include<iostream>
#include<string>

using namespace std;

class Aeroplane
{

private:
	string areoplaneNumber;
	string areoplaneName;
	int areoplaneCapacity;
	string areoplaneType;


public:
	Aeroplane();
	~Aeroplane();

	void setAeroplaneNumber(string);
	string getAeroplaneNumber();
	void setAeroplaneName(string);
	string getAeroplaneName();
	void setAeroplaneCapacity(int);
	int getAeroplaneCapacity();
	void setAeroplaneType(string);
	string getAeroplaneType();

};

#endif