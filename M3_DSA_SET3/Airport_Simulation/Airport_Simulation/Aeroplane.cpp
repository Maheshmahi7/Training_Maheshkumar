#include "Aeroplane.h"


Aeroplane::Aeroplane()
{
}


Aeroplane::~Aeroplane()
{
}



/*Getter and setter methods*/
void Aeroplane::setAeroplaneNumber(string number)
{
	this->areoplaneNumber = number;
}
string Aeroplane::getAeroplaneNumber()
{
	return this->areoplaneNumber;
}
void Aeroplane::setAeroplaneName(string name)
{
	this->areoplaneName = name;
}
string Aeroplane::getAeroplaneName()
{
	return this->areoplaneName;
}
void Aeroplane::setAeroplaneCapacity(int capacity)
{
	this->areoplaneCapacity = capacity;
}
int Aeroplane::getAeroplaneCapacity()
{
	return this->areoplaneCapacity;
}
void Aeroplane::setAeroplaneType(string type)
{
	this->areoplaneType = type;
}
string Aeroplane::getAeroplaneType()
{
	return this->areoplaneType;
}