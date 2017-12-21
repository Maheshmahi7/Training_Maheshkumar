#ifndef Company_HEADER
#define Company_HEADER

#pragma once
#include<vector>
#include "QueueEmployee.h"
#include "Employee.h"
#include "SearchEmployee.h"



class Company 
{

public:

	Company();
	~Company();
	string createEmployee();
	void display();
	void getHighestPayinDepartment(string );
	void getByYear(int );
	string updatePayById(string );
	string benchEmployee(string );
	string removeBenchEmployee();
	int checkUserInput();
	void viewBench();
	bool checkId(string);
	bool checkJoiningYear(int);
	bool checkDepartment(string);

	
private:
	Employee calculateSalary(Employee);
	bool checkPosition(string);
	long int checkUserPhoneNumber();
	bool checkSex(string);
	bool checkEmailId(string);
	bool checkDate(int, int, int);
	bool checkMonth(int);
	bool checkBirthYear(int);
	bool checkJoiningYear(int, int);
	float checkBasic();
	void display(string );

	vector<Employee> employeeV;

	QueueEmployee bench;

};

#endif