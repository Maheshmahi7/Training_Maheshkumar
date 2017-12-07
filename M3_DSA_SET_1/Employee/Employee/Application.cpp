#include "Company.h"
#include "Employee.h"
#include<iostream>
#include<conio.h>
#include<vector>

/*Main method*/
using namespace std;

void main(){
	//local variable decalaration
	char choice = 'n';

	string department,status;

	unsigned int empId,year;

	Company company;
	//label for creating employee
CREATEEMPLOYEE:
	//loop for creating employee 
	do{
	
		company.createEmployee();
		cout << "Want to Add more Employee?(y/n)";
		cin >> choice;
	} while (choice == 'y' || choice=='Y');
	//statement to clear the console screen
	system("cls");
	//loop for getting the user command to run the application
	do{
		int value;
		cout << "1.Want to create new Employee" << endl;
		cout << "2.name of Employee of a particular year" << endl;
		cout << "3.Employee details of highest pay in a department" << endl;
		cout << "4.All details of all Employee" << endl;
		cout << "5.Update Employee pay by 5%" << endl;
		cout << "6.Employee to bench" << endl;
		cout << "7.Assign Bench employee to project" << endl;
		cout << "8.Exit" << endl;
		cin >> value;
		system("cls");
		switch (value){
		case 1: goto CREATEEMPLOYEE;//jumping statement
			break;
		case 2:
			cout << "Enter the Year" << endl;
			cin >> year;
			company.getByYear(year);
			break;
		case 3: 
			cout << "Enter the department"<<endl;
			cin >> department;
			company.getHighestPayinDepartment(department);
			break;
		case 4: company.display();
			break;
		case 5:
			cout << "Enter the Employee id" << endl;
			cin >> empId;
			status = company.updatePayById(empId);
			cout << status << endl;
			break;
		case 7:
			status = company.removeBenchEmployee();
			cout << status << endl;
			break;
		case 6:
			cout << "Enter the Employee id" << endl;
			cin >> empId;
			status = company.benchEmployee(empId);
			cout << status << endl;
			break;
		case 8: exit(0);//exiting the application
			
		default:
			cout << "Invalid value Enter correct value" << endl;
			break;
		}

	} while (true);

	//statement to clear the console after exiting
	cin.clear();
	//statement to hold the console for viewing the output
	cin.ignore(1000, '\n');
	cin.get();
}