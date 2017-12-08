#include "SearchEmployee.h"


SearchEmployee::SearchEmployee()
{
}


SearchEmployee::~SearchEmployee()
{
}


/*Method to implement the interpolation search*/
int SearchEmployee::interpolation_search(vector<Employee> searchV, int size, string key)
{
	key.erase(0,3);
	int id = stoi(key);
	int low = 0;
	int high = size - 1;
	int mid;
	//loop execute untill the key is found
	while ((stoi(searchV[high].getId().erase(0, 3)) != stoi(searchV[low].getId().erase(0, 3))) && (id >= stoi(searchV[low].getId().erase(0, 3))) && (id <= stoi(searchV[high].getId().erase(0, 3)))) {
		mid = low + ((id - stoi(searchV[low].getId().erase(0, 3))) * (high - low) / (stoi(searchV[high].getId().erase(0, 3)) - stoi(searchV[low].getId().erase(0, 3))));

		//if statement to check whether given key is greater or lesser than middle element
		if (stoi(searchV[mid].getId().erase(0, 3)) < id)
			low = mid + 1;
		else if (id < stoi(searchV[mid].getId().erase(0, 3)))
			high = mid - 1;
		else
			return mid;
	}
	//if statement to check the key is available in the lower index
	if (id == stoi(searchV[low].getId().erase(0, 3)))
		return low;
	else
		return -1;
}