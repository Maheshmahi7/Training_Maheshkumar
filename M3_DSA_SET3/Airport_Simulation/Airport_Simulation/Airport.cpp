#include "Airport.h"


Airport::Airport()
{
}


Airport::~Airport()
{
}


/*Getter and setter methods*/

void Airport::setRequestType(int type)
{
	this->requestType = type;
}
int Airport::getRequestType()
{
	return this->requestType;
}
void Airport::setAeroplane(Aeroplane plane){
	this->aeroplane = plane;
}
Aeroplane Airport::getAeroplane()
{
	return this->aeroplane;
}
void Airport::setRequestedTime(time_t time)
{
	this->requestedTime = time;
}
time_t Airport::getRequestedTime()
{
	return this->requestedTime;
}
void Airport::setRequestCleared(time_t time)
{
	this->requestCleared = time;
}
time_t Airport::getRequestCleared()
{
	return this->requestCleared;
}
void Airport::setStatus(string status)
{
	this->status = status;
}
string Airport::getStatus()
{
	return this->status;
}
void Airport::setRunway(string runway)
{
	this->runway = runway;
}
string Airport::getRunway()
{
	return this->runway;
}