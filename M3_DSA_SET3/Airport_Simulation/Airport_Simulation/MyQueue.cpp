#include "MyQueue.h"


/*Constructor to initialize the rear and front value*/

MyQueue::MyQueue(){}


MyQueue::~MyQueue(){}

/*Enqueue method to add the employee to the queue*/
string MyQueue::enqueue(Request request){
	elements.push_back(request);
	return "Successfull added";
}

/*Dequeue method to remove the first added employee in the bench*/
Request MyQueue::dequeue(){
	if (!isEmpty()){
		Request id = elements[0];
		elements.erase(elements.begin());
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
		if (elements[0].getRequestType() == 0){
			cout << "Landing Pending Request Details" << endl;
		}
		else
		{
			cout << "Takeoff Pending Request Details" << endl;
		}
		for (int k = 0; k < elements.size(); k++)  {
			struct tm ltm;
			cout << "Requested Id:" << setw(2) << elements[k].getRequestId() << endl;
			cout << "Requested Aeroplane Name:" << setw(2) << elements[k].getAeroplaneId() << endl;
			time_t time = elements[k].getRequestedTime();
			ltm = *localtime(&time);
			cout << "Requested Time:" << setw(2) << setfill('0') << (ltm.tm_hour) << ":" << setfill('0') << (ltm.tm_min) << ":" << setfill('0') << (ltm.tm_sec) << endl;
			cout << "************************************************" << endl;
		}
		cout << endl;
	}
	else{
		cout << "Bench is Empty" << endl;
		cout << endl;
	}
}


/*method to check the queue is empty or not*/
bool MyQueue::isEmpty(){
	return elements.empty();
}

int MyQueue::size(){
	return elements.size();
}
