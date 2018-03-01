#include "UserInterfaceFactory.h"
#include "DatabaseImplementation.h"
#include "XmlParser.h"
 
UserInterface* UserInterfaceFactory::Create(string type)
{
	UserInterface* userInterface = NULL;
	if (type == XML)
	{
		userInterface = new XmlParser();
	}
	else if (type == DATABASE)
	{
		userInterface = new DatabaseImplementation();
	}
	return userInterface;
}