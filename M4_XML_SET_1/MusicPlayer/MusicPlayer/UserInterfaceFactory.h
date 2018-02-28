#pragma once
#include <iostream>
#include "UserInterface.h"

using namespace std;

class UserInterfaceFactory
{
public:
	static UserInterface* Create(string type);
};

