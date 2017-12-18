#include "Request.h"


Request::Request()
{
}


Request::~Request()
{
}


/*Getter and setter methods*/

void Request::setRequestType(int type)
{
	this->requestType = type;
}
int Request::getRequestType()
{
	return this->requestType;
}
void Request::setAeroplane(Aeroplane plane){
	this->aeroplane = plane;
}
Aeroplane Request::getAeroplane()
{
	return this->aeroplane;
}
void Request::setRequestedTime(time_t time)
{
	this->requestedTime = time;
}
time_t Request::getRequestedTime()
{
	return this->requestedTime;
}
void Request::setRequestCleared(time_t time)
{
	this->requestCleared = time;
}
time_t Request::getRequestCleared()
{
	return this->requestCleared;
}
void Request::setStatus(string status)
{
	this->status = status;
}
string Request::getStatus()
{
	return this->status;
}
void Request::setRunway(string runway)
{
	this->runway = runway;
}
string Request::getRunway()
{
	return this->runway;
}