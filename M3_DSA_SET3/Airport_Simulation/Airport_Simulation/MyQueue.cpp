#include "MyQueue.h"


/*Constructor to initialize the rear and front value*/

MyQueue::MyQueue()
{
	this->rear = -1;
	this->front = 0;
}


MyQueue::~MyQueue()
{
}

/*Enqueue method to add the employee to the queue*/

string MyQueue::enqueue(Request request){
	elements.push_back(request);
	this->rear++;
	return "Successfull added";
}

/*Dequeue method to remove the first added employee in the bench*/
Request MyQueue::dequeue(){
	if (!isEmpty()){
		Request id = elements[0];
		elements.erase(elements.begin());
		this->front++;
		if (isEmpty()){
			this->rear = -1;
			this->front = 0;
		}
		return id;
	}
	else{
		cout << "MyQueue is Empty" << endl;
	}
}

/*Display method to dispaly employee in the bench*/

void MyQueue::display(){
	if (!this->isEmpty()){
		cout << "************************************************" << endl;
		if (elements[this->front].getRequestType() == 0){
			cout << "Landing Pending Request Details" << endl;
		}
		else
		{
			cout << "Takeoff Pending Request Details" << endl;
		}
		for (int k = this->front; k <= this->rear; k++)  {
			struct tm ltm;
			cout << "Requested Aeroplane Name:" << setw(2) << elements[k].getAeroplane().getAeroplaneName() << endl;
			cout << "Requested Aeroplane Number:" << setw(2) << elements[k].getAeroplane().getAeroplaneNumber() << endl;
			cout << "Requested Aeroplane Capacity:" << setw(2) << elements[k].getAeroplane().getAeroplaneCapacity() << endl;
			cout << "Requested Aeroplane Type:" << setw(2) << elements[k].getAeroplane().getAeroplaneType() << endl;
			time_t time = elements[k].getRequestedTime();
			ltm = *localtime(&time);
			cout << "Requested Time:" << setw(2) << (ltm.tm_hour) << ":" << (ltm.tm_min) << ":" << (ltm.tm_sec) << endl;
			cout << "************************************************" << endl;
		}
	}
	else{
		cout << "Bench is Empty" << endl;
	}
}


/*method to check the queue is empty or not*/
bool MyQueue::isEmpty(){
	if (this->front>this->rear){
		return true;
	}
	else{
		return false;
	}
}

int MyQueue::size(){
	return elements.size();
}