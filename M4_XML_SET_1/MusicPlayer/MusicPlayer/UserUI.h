#pragma once
#include <iostream>
#include <string>
#include "UserInterface.h"
#include "UserInterfaceFactory.h"

using namespace std;


class UserUI
{
private:
	void mainMenu();
	void option(UserInterface*);
	int checkUserInput(int);
	void databaseMenu();
	void xmlMenu();
	void readMenu();
	void writeMenu();
	void deleteMenu();
	void updateMenu();
	void reader(UserInterface*);
	void writer(UserInterface*);
	void deleter(UserInterface*);
	void updater(UserInterface*);
public:
	void userOption();
};

