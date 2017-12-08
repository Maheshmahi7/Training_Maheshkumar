#include "QueueEmployee.h"

/*Constructor to initialize the rear and front value*/
QueueEmployee::QueueEmployee()
{
	rear = -1;
	front = 0;
}


QueueEmployee::~QueueEmployee()
{
}

/*Enqueue method to add the employee to the queue*/
string QueueEmployee::enqueue(Employee employee){ 
	if (!this->isFull()){
		benchV.push_back(employee);
		++rear;
		return "Successfull added";
	}
	else{
		return "Bench Full";
	}
}

/*Dequeue method to remove the first added employee in the bench*/
string QueueEmployee::dequeue(){
	if (!this->isEmpty()){
		string id = benchV[front++].getId();
		benchV.erase(benchV.begin());
		return id;
	}
	else{
		return "-1";
	}
}

/*Display method to dispaly employee in the bench*/
void QueueEmployee::display(){ 
	if (!this->isEmpty()){ 
		cout << "************************************************" << endl;
		for (int k = front; k <= rear; k++)  {
			cout << "Employee Id: " << '\t' << benchV[k].getId() << endl;
			cout << "Employee name" << '\t' << benchV[k].getName() << endl;
			cout << "Employee Sex" << '\t' << benchV[k].getSex() << endl;
			cout << "Employee Date of birth" << '\t' << benchV[k].getBirthDate() << '/' << benchV[k].getBirthMonth() << '/' << benchV[k].getBirthYear() << endl;
			cout << "Employee Joining date" << '\t' << benchV[k].getJoiningDate() << '/' << benchV[k].getJoiningMonth() << '/' << benchV[k].getJoiningYear() << endl;
			cout << "Employee address" << '\t' << benchV[k].getAddress() << endl;
			cout << "Employee Phone number" << '\t' << benchV[k].getPhoneNumber() << endl;
			cout << "Employee Email Id" << '\t' << benchV[k].getEmailId() << endl;
			cout << "Employee department" << '\t' << benchV[k].getDepartment() << endl;
			cout << "Employee position" << '\t' << benchV[k].getPosition() << endl;
			cout << "Employee Current project / Bench" << '\t' << benchV[k].getCurrentProject() << endl;
			cout << "Employee HRA" << '\t' << benchV[k].getHRA() << endl;
			cout << "Employee Basic" << '\t' << benchV[k].getBasic() << endl;
			cout << "Employee PF" << '\t' << benchV[k].getPf() << endl;
			cout << "Employee Gross" << '\t' << benchV[k].getGross() << endl;
			cout << "************************************************" << endl;
		}
	} else{
		cout << "Bench is Empty" << endl; 
	} 
}


/*method to check the queue is empty or not*/
bool QueueEmployee::isEmpty(){ 
	if (front>rear){ 
		return true; 
	} else{ 
		return false; 
	} 
}

/*method to check the queue is full or not*/
bool QueueEmployee::isFull(){
	if (benchV.size() >= MAX_SIZE){ 
		return true; 
	} else{
		return false; 
	} 
}
