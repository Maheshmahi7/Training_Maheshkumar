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
	void createEmployee();
	void display();
	void display(string id);
	void getHighestPayinDepartment(string department);
	void getByYear(int year);
	string updatePayById(string id);
	string benchEmployee(string id);
	string removeBenchEmployee();
	void viewBench();
	bool checkId(string);
	bool checkDate(int,int,int);
	bool checkMonth(int);
	bool checkBirthYear(int);
	bool checkJoiningYear(int,int);
	bool checkJoiningYear(int);
	bool checkSex(string);
	bool checkEmailId(string);
	bool checkDepartment(string);
	bool checkPosition(string);
	
private:
	vector<Employee> employeeV;

	QueueEmployee bench;

};

#endif