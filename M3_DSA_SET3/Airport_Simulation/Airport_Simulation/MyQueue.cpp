#include "MyQueue.h"

/*Constructor to initialize the rear and front value*/

MyQueue::MyQueue()
{
	rear = -1;
	front = 0;
}


MyQueue::~MyQueue()
{
}

/*Enqueue method to add the employee to the queue*/

string MyQueue::enqueue(Airport airport){
	elements.push_back(airport);
	++rear;
	return "Successfull added";
}

/*Dequeue method to remove the first added employee in the bench*/
Airport MyQueue::dequeue(){
	if (!this->isEmpty()){
		Airport id = elements[front++];
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
		for (int k = front; k <= rear; k++)  {

		}
	}
	else{
		cout << "Bench is Empty" << endl;
	}
}


/*method to check the queue is empty or not*/
bool MyQueue::isEmpty(){
	if (front>rear){
		return true;
	}
	else{
		return false;
	}
}

