#include "Employee.h"

class DynamicArray {

public:
	DynamicArray();
	DynamicArray(int initSize);
	DynamicArray(const DynamicArray &original);
	~DynamicArray();


	void insert(Employee employee);
	//void remove(int id);
	Employee get(int index);
	//Employee getById(int id);


	int getSize();
	void resize(int newSize);

	int &operator[](int index);
	//bool operator==(DynamicArray);
	//bool operator!=(DynamicArray);

private:
	int size;
	Employee *array;
	int k = 0;

};
