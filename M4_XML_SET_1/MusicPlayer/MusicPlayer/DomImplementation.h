#pragma once

#include "XMLDom.h"

class DomImplementation
{
public:
	DomImplementation();
	~DomImplementation();
	void DisplaySongs()
private:
	XMLDom* doc;
	string value;
};

