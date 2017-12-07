#ifndef SearchEmployee_HEADER
#define SearchEmployee_HEADER

#include "Company.h"
#pragma once
class SearchEmployee
{
public:
	SearchEmployee();
	~SearchEmployee();
	int interpolation_search(vector<Employee> employee, int size, int key);

};

#endif