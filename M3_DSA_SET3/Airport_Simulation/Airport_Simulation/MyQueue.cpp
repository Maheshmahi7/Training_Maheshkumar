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
		for (int k = front; k <= rear; k++)  {

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

