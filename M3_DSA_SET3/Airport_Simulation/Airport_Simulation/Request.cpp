#include "Request.h"


Request::Request()
{
}


Request::~Request()
{
}


/*Getter and setter methods*/

void Request::setRequestId(int id)
{
	this->requestId = id;
}
int Request::getRequestId()
{
	return this->requestId;
}
void Request::setRequestType(int type)
{
	this->requestType = type;
}
int Request::getRequestType()
{
	return this->requestType;
}
void Request::setAeroplaneId(string plane){
	this->aeroplaneId = plane;
}
string Request::getAeroplaneId()
{
	return this->aeroplaneId;
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