#include "dynamicarray.h" 
#include<iostream>


using namespace std;

DynamicArray::DynamicArray() {
	size = 1;
	array = new Employee[size];
	

}


DynamicArray::DynamicArray(int initSize) {
	size = initSize;
	array = new Employee[size];

}


DynamicArray::DynamicArray(const DynamicArray &original) {
	size = original.size;
	array = new Employee[size];
	for (int i = 0; i < size; i++) {
		array[i] = original.array[i];

	}

}


DynamicArray::~DynamicArray() {
	delete[] array;

}




void DynamicArray::insert(Employee value) {

	if (k >= size){
		resize((size + 1));
	}
	array[k] = value;
	k++;
}


/*void DynamicArray::remove(int id) {
	int a = 0;
	for (int j = 0; j < size; j++){
		Employee employee = get(j);
		if (employee.getId == id){
			a = j;
		}
		if (a > 0){
			array[a] = array[a + 1];
			a++;
		}
	}
	if (a>0){
		resize((size - 1));
		k--;
	}
}

*/
Employee DynamicArray::get(int index){
	return array[index];
}

/*Employee DynamicArray::getById(int id) {
	for (int j = 0; j < size; j++){
		Employee employee = DynamicArray::get(j);
		if (employee.getId == id){
			return employee;
		}
	}
}
*/

int DynamicArray::getSize() {
	return size;

}


void DynamicArray::resize(int newSize) {
	Employee *temp;
	temp = new Employee[newSize];
	for (int i = 0; i < (newSize); i++) {
		temp[i] = array[i];

	}
	delete[] array;
	Employee *array = new Employee[newSize];
	array = temp;
	size = newSize;
	delete[] temp;

}


/*bool DynamicArray::operator==(DynamicArray a)  {
if (a.size != size) return false;


for (int i = 0; i < (a.size); i++) {
if (a[i] != array[i]) return false;

}

}

/*
bool DynamicArray::operator!=(DynamicArray a)  {
if (a.size != size) return true;

for (int i = 0; i < (a.size); i++) {
if (a[i] != array[i]) return true;
}

}

string &DynamicArray::operator[](int index) {
if ((index - 1) > size) {
resize(index + 1);

}
return array[index]; // returned as a reference

}*/
