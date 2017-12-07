#include "SearchEmployee.h"


SearchEmployee::SearchEmployee()
{
}


SearchEmployee::~SearchEmployee()
{
}

/*Method to implement the interpolation search*/
int SearchEmployee::interpolation_search(vector<Employee> searchV, int size, int key)
{
	int low = 0;
	int high = size - 1;
	int mid;
	//loop execute untill the key is found
	while ((searchV[high].getId() != searchV[low].getId()) && (key >= searchV[low].getId()) && (key <= searchV[high].getId())) {
		mid = low + ((key - searchV[low].getId()) * (high - low) / (searchV[high].getId() - searchV[low].getId()));

		//if statement to check whether given key is greater or lesser than middle element
		if (searchV[mid].getId() < key)
			low = mid + 1;
		else if (key < searchV[mid].getId())
			high = mid - 1;
		else
			return mid;
	}
	//if statement to check the key is available in the lower index
	if (key == searchV[low].getId())
		return low;
	else
		return -1;
}