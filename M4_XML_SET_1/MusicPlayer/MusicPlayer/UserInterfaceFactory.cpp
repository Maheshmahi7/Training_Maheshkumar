#include "UserInterfaceFactory.h"
#include "DatabaseImplementation.h"
#include "XmlParser.h"
 
UserInterface* UserInterfaceFactory::Create(string type)
{
	if (type == "XML")
	{
		return new XmlParser();
	}
	else if (type == "Database")
	{
		return new DatabaseImplementation();
	}
}