#include "Company.h"
#include<iostream>

string emp_id,name, sex, address, EmailId, department, position, currentProject,status;

long int phoneNumber;

unsigned int id = 101, birthDate, birthMonth, birthYear, joiningDate, joiningMonth, joiningYear, HRA, basic, PF, gross, index,net,allowance,gratuity;

bool check;

Employee employee;

SearchEmployee searchEmployee;

Company::Company()
{
}


Company::~Company()
{
}

/*Method to create Employees*/
string Company::createEmployee(){
		cout << "**************SYSTEM IS CASE SENSITIVE USE UPPER CASE OR LOWER CASE*************" << endl;
		cout << "Enter the employee details" << endl;
		emp_id = "EMP" + to_string(id);
		employee.setId(emp_id);
		id++;
			cout << "Employee name:" << endl;
			cin >> name;
			employee.setName(name);
		SEX:
			cout << "Employee Sex(MALE/FEMALE/TRANSGENDER)" << endl;
			cin >> sex;
			check = checkSex(sex);
			if (check){
				employee.setSex(sex);
			}
			else
			{
				cout << "Enter valid gender" << endl;
				goto SEX;
			}
			cout << "Enter Date of Birth:" << endl;
		BYEAR:
			cout << "Year:" << endl;
			cin >> birthYear;
			if (cin.fail())
			{
				birthYear = checkUserInput();
			}
			if (checkBirthYear(birthYear)){
				employee.setBirthYear(birthYear);
			}
			else
			{
				cout << "You are retired or not eligible for this company." << endl;
				cout << "If you think your are eligible enter valid";
				goto BYEAR;
			}
		BMONTH:
			cout << "Month(1-12):" << endl;
			cin >> birthMonth;
			if (cin.fail())
			{
				birthMonth = checkUserInput();
			}
			if (checkMonth(birthMonth)){
				employee.setBirthMonth(birthMonth);
			}
			else
			{
				cout << "Enter valid month" << endl;
				goto BMONTH;
			}
		BDATE:
			cout << "Date:" << endl;
			cin >> birthDate;
			if (cin.fail())
			{
				birthDate = checkUserInput();
			}
			check = checkDate(birthDate, birthMonth, birthYear);
			if (check){
				employee.setBirthDate(birthDate);
			}
			else
			{
				cout << "Enter valid Date" << endl;
				goto BDATE;
			}
			cout << "Enter Date of Joining:" << endl;
		JYEAR:
			cout << "Year:" << endl;
			cin >> joiningYear;
			if (cin.fail())
			{
				joiningYear = checkUserInput();
			}
			if (checkJoiningYear(joiningYear, birthYear)){
				employee.setJoiningYear(joiningYear);
			}
			else
			{
				cout << "Your not eligible for this company" << endl;
				goto JYEAR;
			}
		JMONTH:
			cout << "Month(1-12):" << endl;
			cin >> joiningMonth;
			if (cin.fail())
			{
				joiningMonth = checkUserInput();
			}
			if (checkMonth(joiningMonth)){
				employee.setJoiningMonth(joiningMonth);
			}
			else
			{
				cout << "Enter valid month" << endl;
				cin.clear();
				goto JMONTH;
			}
		JDATE:
			cout << "Date:" << endl;
			cin >> joiningDate;
			if (cin.fail())
			{
				joiningDate = checkUserInput();
			}
			if (checkDate(joiningDate, joiningMonth, joiningYear)){
				employee.setJoiningDate(joiningDate);
			}
			else
			{
				cout << "Enter valid date" << endl;
				goto JDATE;
			}
			cout << "Employee address" << endl;
			cin >> address;
			employee.setAddress(address);
			cout << "Employee Phone number" << endl;
			cin >> phoneNumber;
			if (cin.fail())
			{
				phoneNumber = checkUserPhoneNumber();
			}
			employee.setPhoneNumber(phoneNumber);
		EMAIL:
			cout << "Employee Email Id" << endl;
			cin >> EmailId;
			if (checkEmailId(EmailId)){
				employee.setEmailId(EmailId);
			}
			else
			{
				cout << "Enter valid Email must contain @domain.com" << endl;
				goto EMAIL;
			}
		DEPARTMENT:
			cout << "Employee department" << endl;
			cout << "List of departments are:" << '\n' << "DEVELOPMENT, TESTING, HR, IT" << endl;
			cin >> department;
			check = checkDepartment(department);
			if (check){
				employee.setDepartment(department);
			}
			else
			{
				cout << "Enter valid Department" << endl;
				goto DEPARTMENT;
			}
		POSITION:
			cout << "Employee position" << endl;
			cout << "List of positions are:" << '\n' << "DEVELOPER, TESTER, ADMIN, TEAMLEAD, HR" << endl; 
			cin >> position;
			check = checkPosition(position);
			if (check){
				employee.setPosition(position);
			}
			else
			{
				cout << "Enter valid position" << endl;
				goto POSITION;
			}

			cout << "Employee Current Project Name or Bench" << endl;
			cin >> currentProject;
			employee.setCurrentProject(currentProject);
			cout << "Employee Basic Salary" << endl;
			cin >> basic;
			if (cin.fail())
			{
				basic = checkUserInput();
			}
			employee.setBasic(basic);

			employee = calculateSalary(employee);


		//assigning employee object to vector
		employeeV.push_back(employee);

		if (((employee.getCurrentProject()).compare("BENCH")) == 0 || ((employee.getCurrentProject()).compare("bench")) == 0){
			status = bench.enqueue(employee);
			return status;
		}
		else
		{
			return "Successfully added";
		}

		
}


Employee Company::calculateSalary(Employee employee){
	HRA = (employee.getBasic() * 10) / 100;
	employee.setHRA(HRA);
	PF = (employee.getBasic() * 8.3) / 100;;
	employee.setPF(PF);
	allowance = (employee.getBasic() * 6.6) / 100;
	employee.setAllowance(allowance);
	net = (employee.getBasic() + employee.getHRA() + employee.getAllowance() - employee.getPF());
	employee.setNet(net);
	gratuity = ((employee.getBasic()*4.8) / 100) * 12;
	employee.setGratuity(gratuity);
	gross = ((employee.getNet() * 12) + (employee.getPF() * 12 *2) + (employee.getGratuity()));
	employee.setGross(gross);
	return employee;
}



/*Method to fing the Highest pay in a particular department*/
void Company::getHighestPayinDepartment(string department){
	vector<Employee> departmentV;
	int highestPay;
	string id;
	for (int index = 0; index < (employeeV.size()); index++){
		if (employeeV[index].getDepartment() == department){
			departmentV.push_back(employeeV[index]);
		}
	}
	//setting the first employee in the vector departmentV as highestpay
	if (departmentV.size() > 0){
		highestPay = departmentV[0].getGross();
		id = departmentV[0].getId();
		for (int index = 0; index < (departmentV.size()); index++){
			if (departmentV[index].getGross() > highestPay){
				highestPay = departmentV[index].getGross();
				id = departmentV[index].getId();
			}
		}
		//displaying the Employee details with highest salary
		display(id);
	}
	else
	{
		cout << "No Employee available in the department "<<department<<endl;
	}
}

/*Method to get list of Employees Joined in a particular year*/
void Company::getByYear(int year){
	vector<Employee> yearV;
	for (int index = 0; index < employeeV.size(); index++){
		if (employeeV[index].getJoiningYear() == year){
			yearV.push_back(employeeV[index]);
		}
	}
	//displaying the employee name of the given year
	if (yearV.size() > 0){
		cout << "************************************************" << endl;
		for (int k = 0; k < yearV.size(); k++){
			cout << "Employee Id: " << '\t' << yearV[k].getId() << '\t' << "Employee Name:" << '\t' << yearV[k].getName() << endl;
		}
		cout << "************************************************" << endl;
	}
	else
	{
		cout << "No Employee joined in the year "<<year<<endl;
	}

}

/*Method to Update A Employee Pay by 5%*/
string Company::updatePayById(string id){
	index = searchEmployee.interpolation_search(employeeV, employeeV.size(), id);
	if (index != -1){
		int temp = employeeV[index].getBasic();
		temp += (temp * 5) / 100;
		employeeV[index].setBasic(temp);
		employeeV[index] = calculateSalary(employeeV[index]);
		return "Updated Successfully";
	}
	else
	{
		return "Check the Employee id you have entered";
	}
}

/*Method to Bench a working Employee*/
string Company::benchEmployee(string id){
	index = searchEmployee.interpolation_search(employeeV, employeeV.size(), id);
	if (index != -1){
		if (((employeeV[index].getCurrentProject()).compare("BENCH"))==0 || ((employeeV[index].getCurrentProject()).compare("bench"))==0){
			return "Employee is already in bench";
		}
		else
		{
			employeeV[index].setCurrentProject("BENCH");
			status = bench.enqueue(employeeV[index]);
			return status;
		}
	}
	else
	{
		return "Employee not Found";
	}
	
}

/*Method to Assign Project to Bench Employee*/
string Company::removeBenchEmployee(){
	string project;
	cout << "Enter the Project assigned to the Employee" << endl;
	cin >> project;
		emp_id = bench.dequeue();
		if (emp_id.compare("-1")!=0){
			index = searchEmployee.interpolation_search(employeeV, employeeV.size(), emp_id);
			employeeV[index].setCurrentProject(project);
			return "Removed from Bench";
		}
		else{
			return "Bench is empty";
		}


}

/*Method to view the Employee in the bench*/
void Company::viewBench(){
	bench.display();
}


/*Method to Display evey Employee details in the Application*/
void Company::display(){
	cout << "************************************************" << endl;
	for (int k = 0; k < employeeV.size(); k++){
		cout << "Employee Id: " << '\t' << employeeV[k].getId() << endl;
		cout << "Employee name" << '\t' << employeeV[k].getName() << endl;
		cout << "Employee Sex" << '\t' << employeeV[k].getSex() << endl;
		cout << "Employee Date of birth" << '\t' << employeeV[k].getBirthDate() << '/' << employeeV[k].getBirthMonth() << '/' << employeeV[k].getBirthYear() << endl;
		cout << "Employee Joining date" << '\t' << employeeV[k].getJoiningDate() << '/' << employeeV[k].getJoiningMonth() << '/' << employeeV[k].getJoiningYear() << endl;
		cout << "Employee address" << '\t' << employeeV[k].getAddress() << endl;
		cout << "Employee Phone number" << '\t' << employeeV[k].getPhoneNumber() << endl;
		cout << "Employee Email Id" << '\t' << employeeV[k].getEmailId() << endl;
		cout << "Employee department" << '\t' << employeeV[k].getDepartment() << endl;
		cout << "Employee position" << '\t' << employeeV[k].getPosition() << endl;
		cout << "Employee Current project / Bench" << '\t' << employeeV[k].getCurrentProject() << endl;
		cout << "Employee Basic" << '\t' << employeeV[k].getBasic() << endl;
		cout << "Employee HRA" << '\t' << employeeV[k].getHRA() << endl; 
		cout << "Employee ALLOWANCE" << '\t' << employeeV[k].getAllowance() << endl; 
		cout << "Employee PF" << '\t' << employeeV[k].getPF() << endl;
		cout << "Employee NET" << '\t' << employeeV[k].getNet() << endl; 
		cout << "Employee GRATUITY" << '\t' << employeeV[k].getGratuity() << endl; 
		cout << "Employee Gross" << '\t' << employeeV[k].getGross() << endl;
		cout << "************************************************" << endl;
	}
}


/*Method to Display only particular Employee details*/
void Company::display(string id){
	
	index = searchEmployee.interpolation_search(employeeV, employeeV.size(), id);
		cout << "************************************************" << endl;
		cout << "Employee Id: " << '\t' << employeeV[index].getId() << endl;
		cout << "Employee name" << '\t' << employeeV[index].getName() << endl;
		cout << "Employee Sex" << '\t' << employeeV[index].getSex() << endl;
		cout << "Employee Date of birth" << '\t' << employeeV[index].getBirthDate() << '/' << employeeV[index].getBirthMonth() << '/' << employeeV[index].getBirthYear() << endl;
		cout << "Employee Joining date" << '\t' << employeeV[index].getJoiningDate() << '/' << employeeV[index].getJoiningMonth() << '/' << employeeV[index].getJoiningYear() << endl;
		cout << "Employee address" << '\t' << employeeV[index].getAddress() << endl;
		cout << "Employee Phone number" << '\t' << employeeV[index].getPhoneNumber() << endl;
		cout << "Employee Email Id" << '\t' << employeeV[index].getEmailId() << endl;
		cout << "Employee department" << '\t' << employeeV[index].getDepartment() << endl;
		cout << "Employee position" << '\t' << employeeV[index].getPosition() << endl;
		cout << "Employee Current project / Bench" << '\t' << employeeV[index].getCurrentProject() << endl;
		cout << "Employee Basic" << '\t' << employeeV[index].getBasic() << endl;
		cout << "Employee HRA" << '\t' << employeeV[index].getHRA() << endl;
		cout << "Employee ALLOWANCE" << '\t' << employeeV[index].getAllowance() << endl;
		cout << "Employee PF" << '\t' << employeeV[index].getPF() << endl;
		cout << "Employee NET" << '\t' << employeeV[index].getNet() << endl;
		cout << "Employee GRATUITY" << '\t' << employeeV[index].getGratuity() << endl;
		cout << "Employee Gross" << '\t' << employeeV[index].getGross() << endl;
		cout << "************************************************" << endl;
}

/*Methods to validate the user input for date month year gender and email*/
bool Company::checkDate(int date,int month,int year){
	if (month == 2){
		if ((year % 4) != 0){
				if (0 < date && date <= 28){
					return true;
				}
				else
				{
					return false;
				}
		}
		else
		{
				if (0 < date && date <= 29){
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
		if (0 < date && date <= 31){
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11){
		if (0 < date && date <= 30){
			return true;
		}
		else
		{
			return false;
		}
	}

}
bool Company::checkMonth(int month){
	if (0 < month && month <= 12){
		return true;
	}
	else
	{
		return false;
	}
}
bool Company::checkBirthYear(int year){
	if (2018-58 <= year && year <= (2018 - 21)){
		return true;
	}
	else
	{
		return false;
	}
}

bool Company::checkJoiningYear(int year,int bYear){
	if ((bYear +21 ) <= year && year <= 2018){
		return true;
	}
	else
	{
		return false;
	}
}

bool Company::checkJoiningYear(int year){
	if (1980 <= year && year <= 2018){
		return true;
	}
	else
	{
		return false;
	}
}

bool Company::checkId(string id){
	size_t found[2];
	found[0] = id.find_first_of("EMP");
	if (found[0] != string::npos){
		return true;
	}
	else
	{
		return false;
	}
}

bool Company::checkSex(string sex){
	if ((sex.compare("MALE") == 0) || (sex.compare("male") == 0)){
		return true;
	}
	else if ((sex.compare("FEMALE") == 0) || (sex.compare("female") == 0))
	{	
		return true;
	}
	else if ((sex.compare("TRANSGENDER") == 0) || (sex.compare("transgender") == 0))
	{	
		return true;
	}
	else
	{
		return false;
	}

}
bool Company::checkEmailId(string email){
	size_t found[2];
	found[0] = email.find_first_of('@');
	found[1] = email.find_first_of('.');
	if (found[0] != std::string::npos && found[1] != std::string::npos){
		return true;
	}
	else
	{
		return false;
	}
}

bool Company::checkDepartment(string department){
	if ((department.compare("DEVELOPMENT") == 0) || (department.compare("development") == 0)){
		return true;
	}
	else if ((department.compare("TESTING") == 0) || (department.compare("testing") == 0))
	{
		return true;
	}
	else if ((department.compare("HR") == 0) || (department.compare("hr") == 0))
	{
		return true;
	}
	else if ((department.compare("IT") == 0) || (department.compare("it") == 0)){
		return true;
	}
	else if ((department.compare("ADMIN") == 0) || (department.compare("admin") == 0))
	{
		return true;
	}
	else
	{
		return false;
	}

}


bool Company::checkPosition(string position){
	if ((position.compare("ENGINEER") == 0) || (position.compare("engineer") == 0)){
		return true;
	}
	else if ((position.compare("TESTER") == 0) || (position.compare("tester") == 0))
	{
		return true;
	}
	else if ((position.compare("MANAGER") == 0) || (position.compare("manager") == 0))
	{
		return true;
	}
	else if ((position.compare("TEAMLEAD") == 0) || (position.compare("teamlead") == 0)){
		return true;
	}
	else if ((position.compare("ADMIN") == 0) || (position.compare("admin") == 0))
	{
		return true;
	}
	else
	{
		return false;
	}

}


int Company::checkUserInput() {
	int input;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cin >> input;
		}
		else if (!cin.fail()) {
			return input;
			break;
		}
	}
}


long int Company::checkUserPhoneNumber() {
	long int input;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cin >> input;
		}
		else if (!cin.fail()) {
			return input;
			break;
		}
	}
}