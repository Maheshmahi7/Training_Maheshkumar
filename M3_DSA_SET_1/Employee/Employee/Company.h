#ifndef Company_HEADER
#define Company_HEADER

#pragma once
#include<vector>
#include<queue>
#include "Employee.h"
#include "SearchEmployee.h"



class Company 
{

public:

	Company();
	~Company();
	void createEmployee();
	void display();
	void display(int id);
	void getHighestPayinDepartment(string department);
	void getByYear(int year);
	string updatePayById(int id);
	string benchEmployee(int id);
	string removeBenchEmployee();
	bool checkDate(int);
	bool checkMonth(int);
	bool checkYear(int);
	bool checkSex(string);
	bool checkEmailId(string);
	bool checkDepartment(string);
	bool checkPosition(string);
	
private:
	vector<Employee> employeeV;

	queue<Employee> bench;

};

#endif