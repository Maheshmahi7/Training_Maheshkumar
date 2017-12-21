#include "QueueEmployee.h"

/*Constructor to initialize the rear and front value*/
QueueEmployee::QueueEmployee()
{
	rear = -1;
}


QueueEmployee::~QueueEmployee()
{
}

/*Enqueue method to add the employee to the queue*/
string QueueEmployee::enqueue(string employee){ 
		benchV.push_back(employee);
		++rear;
		return "Successfull added";
}

/*Dequeue method to remove the first added employee in the bench*/
string QueueEmployee::dequeue(){
	if (!this->isEmpty()){
		string id = benchV[0];
		benchV.erase(benchV.begin());
		return id;
	}
	else{
		return "-1";
	}
}

/*method to return queue*/
vector<string> QueueEmployee::getQueue(){
	return benchV;
}


/*method to check the queue is empty or not*/
bool QueueEmployee::isEmpty(){ 
	return (rear<0);
}

