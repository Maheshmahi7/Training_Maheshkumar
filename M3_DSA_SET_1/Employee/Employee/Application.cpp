#include "Company.h"
#include "Employee.h"
#include<iostream>
#include<conio.h>
#include<vector>
#include<exception>

/*Main method*/
using namespace std;

void main(){
	//local variable decalaration
	char choice = 'n';

	string department,status,empId;

	unsigned int year;

	Company company;
	//label for creating employee
CREATEEMPLOYEE:
	//loop for creating employee 
	do{
		try{
			status = company.createEmployee();
			cout << status << endl;
		}
		catch (exception e){
			cerr << "Exception Caught" << e.what() << endl;
		}
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
		cout << "8.View Benched Employee" << endl;
		cout << "9.Exit" << endl;
		cin >> value;
		if (cin.fail())
		{
			value = company.checkUserInput();
		}
		system("cls");
		switch (value){
		case 1: goto CREATEEMPLOYEE;//jumping statement
			break;
		case 2:
			YEAR:
			cout << "Enter the Year" << endl;
			cin >> year;
			if (cin.fail())
			{
				year = company.checkUserInput();
			}

			if (company.checkJoiningYear(year)){
				company.getByYear(year);
			}
			else
			{
				cout << "Enter valid joining year"<<endl;
				goto YEAR;
			}
			break;
		case 3: 
			DEPARTMENT:
			cout << "Enter the department"<<endl;
			cin >> department;
			if (company.checkDepartment(department)){
				company.getHighestPayinDepartment(department);
			}
			else
			{
				cout << "Enter valid department:" << endl;
				goto DEPARTMENT;
			}
			break;
		case 4: company.display();
			break;
		case 5:
			UPDATE:
			cout << "Enter the Employee id(UPPER CASE)" << endl;
			cin >> empId;
			if (company.checkId(empId)){
				status = company.updatePayById(empId);
				cout << status << endl;
			}
			else
			{
				cout << "Enter valid Employee Id:" << endl;
				goto UPDATE;
			}
			break;
		case 7:
			status = company.removeBenchEmployee();
			cout << status << endl;
			break;
		case 6:
			BENCH:
			cout << "Enter the Employee id(UPPER CASE)" << endl;
			cin >> empId;
			if (company.checkId(empId)){
				status = company.benchEmployee(empId);
			cout << status << endl;
			}
			else
			{
				cout << "Enter valid Employee Id:" << endl;
				goto BENCH;
			}
			break;
		case 9: exit(0);//exiting the application
		case 8:
			company.viewBench();
			break;
			
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