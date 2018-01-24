#pragma once
#include "DataWriter.h"
#include "DataReader.h"
#include<iostream>


class SQLDatabase
{
public:
	SQLDatabase();
	~SQLDatabase();
	void userUI();
private:
	void menu();
	void readMenu();
	void writeMenu();
	int checkUserInput();

};