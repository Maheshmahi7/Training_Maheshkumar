#include "Company.h"
#include<iostream>

string emp_id, status;

int index;

float HRA, basic, PF, gross, net, allowance, gratuity;

SearchEmployee searchEmployee;


Company::Company()
{
}


Company::~Company()
{
}

/*Method to create Employees*/
string Company::createEmployee(){
	Employee employee;

	string name, sex, address, EmailId, department, position, currentProject;

	long int phoneNumber;

	unsigned int id = 101, birthDate, birthMonth, birthYear, joiningDate, joiningMonth, joiningYear;

	cout << "**************SYSTEM IS CASE SENSITIVE USE UPPER CASE OR LOWER CASE*************" << endl;
	cout << "Enter the employee details" << endl;
	emp_id = "EMP" + to_string(id);
	employee.setId(emp_id);
	id++;
	cout << "Employee name:" << endl;
	cin >> name;
	employee.setName(name);
	cout << "Employee Sex(MALE/FEMALE/TRANSGENDER)" << endl;
	cin >> sex;
	while (true)
	{
		if (checkSex(sex)){
			employee.setSex(sex);
			break;
		}
		else
		{
			cout << "Enter valid gender" << endl;
			cin >> sex;
		}
	}
	cout << "Enter Date of Birth:" << endl;
	cout << "Year:" << endl;
	cin >> birthYear;
	if (cin.fail())
	{
		birthYear = checkUserInput();
	}
	while (true)
	{
		if (checkBirthYear(birthYear)){
			employee.setBirthYear(birthYear);
			break;
		}
		else
		{
			cout << "You are retired or not eligible for this company." << endl;
			cout << "If you think your are eligible enter valid" << endl;
			cin >> birthYear;
			if (cin.fail())
			{
				birthYear = checkUserInput();
			}
		}
	}
			cout << "Month(1-12):" << endl;
			cin >> birthMonth;
			if (cin.fail())
			{
				birthMonth = checkUserInput();
			}
			while (true)
			{
				if (checkMonth(birthMonth)){
					employee.setBirthMonth(birthMonth);
					break;
				}
				else
				{
					cout << "Enter valid month" << endl;
					cin >> birthMonth;
					if (cin.fail())
					{
						birthMonth = checkUserInput();
					}
				}
			}
			cout << "Date:" << endl;
			cin >> birthDate;
			if (cin.fail())
			{
				birthDate = checkUserInput();
			}
			while (true)
			{
				if (checkDate(birthDate, birthMonth, birthYear)){
					employee.setBirthDate(birthDate);
					break;
				}
				else
				{
					cout << "Enter valid Date" << endl;
					cin >> birthDate;
					if (cin.fail())
					{
						birthDate = checkUserInput();
					}
				}
			}
			cout << "Enter Date of Joining:" << endl;
			cout << "Year:" << endl;
			cin >> joiningYear;
			if (cin.fail())
			{
				joiningYear = checkUserInput();
			}
			while (true)
			{
				if (checkJoiningYear(joiningYear, birthYear)){
					employee.setJoiningYear(joiningYear);
					break;
				}
				else
				{
					cout << "Your not eligible for this company" << endl;
					cin >> joiningYear;
					if (cin.fail())
					{
						joiningYear = checkUserInput();
					}
				}
			}
			cout << "Month(1-12):" << endl;
			cin >> joiningMonth;
			if (cin.fail())
			{
				joiningMonth = checkUserInput();
			}
			while (true)
			{
				if (checkMonth(joiningMonth)){
					employee.setJoiningMonth(joiningMonth);
					break;
				}
				else
				{
					cout << "Enter valid month" << endl;
					cin >> joiningMonth;
					if (cin.fail())
					{
						joiningMonth = checkUserInput();
					}
				}
			}
			cout << "Date:" << endl;
			cin >> joiningDate;
			if (cin.fail())
			{
				joiningDate = checkUserInput();
			}
			while (true)
			{
				if (checkDate(joiningDate, joiningMonth, joiningYear)){
					employee.setJoiningDate(joiningDate);
					break;
				}
				else
				{
					cout << "Enter valid date" << endl;
					cin >> joiningDate;
					if (cin.fail())
					{
						joiningDate = checkUserInput();
					}
				}
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
			cout << "Employee Email Id" << endl;
			cin >> EmailId;
			while (true)
			{
				if (checkEmailId(EmailId)){
					employee.setEmailId(EmailId);
					break;
				}
				else
				{
					cout << "Enter valid Email must contain @domain.com" << endl;
					cin >> EmailId;
				}
			}
			cout << "Employee department" << endl;
			cout << "List of departments are:" << '\n' << "DEVELOPMENT, TESTING, HR, IT" << endl;
			cin >> department;
			while (true)
			{
				if (checkDepartment(department)){
					employee.setDepartment(department);
					break;
				}
				else
				{
					cout << "Enter valid Department" << endl;
					cin >> department;
				}
			}
			cout << "Employee position" << endl;
			cout << "List of positions are:" << '\n' << "ENGINEER, TESTER, ADMIN, TEAMLEAD, MANAGER" << endl; 
			cin >> position;
			while (true)
			{
	
				if (checkPosition(position)){
					employee.setPosition(position);
					break;
				}
				else
				{
					cout << "Enter valid position" << endl;
					cin >> position;
				}
			}
			cout << "Employee Current Project Name or Bench" << endl;
			cin >> currentProject;
			employee.setCurrentProject(currentProject);
			cout << "Employee Basic Salary" << endl;
			cin >> basic;
			if (cin.fail())
			{
				basic = checkBasic();
			}
			employee.setBasic(basic);

			employee = calculateSalary(employee);


		//assigning employee object to vector
		employeeV.push_back(employee);

		if (((employee.getCurrentProject()).compare("BENCH")) == 0 || ((employee.getCurrentProject()).compare("bench")) == 0){
			status = bench.enqueue(employee.getId());
			return status;
		}
		else
		{
			return "Successfully added";
		}

		
}

/*Method to calculate salary of the employee*/
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
	if (employeeV.size()>0){
		vector<Employee> departmentV;
		float highestPay;
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
			cout << "No Employee available in the department " << department << endl;
		}
	}
	else
	{
		cout << "Enter Employee details:" << endl;
	}
}

/*Method to get list of Employees Joined in a particular year*/
void Company::getByYear(int year){
	if (employeeV.size() > 0){
		int count = 0;
		cout << "************************************************" << endl;
		for (int index = 0; index < employeeV.size(); index++){
			if (employeeV[index].getJoiningYear() == year){
				cout << "Employee Id: " << '\t' << employeeV[index].getId() << '\t' << "Employee Name:" << '\t' << employeeV[index].getName() << endl;
				count++;
			}
		}
		cout << "************************************************" << endl;
		if (count == 0)
		{
			cout << "No Employee joined in the year " << year << endl;
		}
	}
	else
	{
		cout << "Enter Employee details:" << endl;
	}
}

/*Method to Update A Employee Pay by 5%*/
string Company::updatePayById(string id){
	if (employeeV.size() > 0){
		index = searchEmployee.interpolation_search(employeeV, employeeV.size(), id);
		if (index != -1){
			float temp = employeeV[index].getBasic();
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
	else
	{
		return "Enter Employee details:";
	}
}

/*Method to Bench a working Employee*/
string Company::benchEmployee(string id){
	if (employeeV.size() > 0){
		index = searchEmployee.interpolation_search(employeeV, employeeV.size(), id);
		if (index != -1){
			if (((employeeV[index].getCurrentProject()).compare("BENCH")) == 0 || ((employeeV[index].getCurrentProject()).compare("bench")) == 0){
				return "Employee is already in bench";
			}
			else
			{
				employeeV[index].setCurrentProject("BENCH");
				status = bench.enqueue(employeeV[index].getId());
				return status;
			}
		}
		else
		{
			return "Employee not Found";
		}
	}
	else
	{
		return "Enter Employee details:";
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
	if (!bench.isEmpty()){
		vector<string> benchV = bench.getQueue();
		for (int index = 0; index < benchV.size(); index++){
			display(benchV[index]);
		}
	}
	else
	{
		cout << "Bench is Empty" << endl;
	}
}


/*Method to Display evey Employee details in the Application*/
void Company::display(){
	if (employeeV.size() > 0){
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
	else
	{
		cout << "Enter Employee details:" << endl;
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
	return (0 < month && month <= 12);
}
bool Company::checkBirthYear(int year){
	return (2018 - 58 <= year && year <= (2018 - 21));
}

bool Company::checkJoiningYear(int year,int bYear){
	return ((bYear + 21) <= year && year <= 2018);
}

bool Company::checkJoiningYear(int year){
	return (1980 <= year && year <= 2018);
}

bool Company::checkId(string id){
	size_t found[2];
	found[0] = id.find_first_of("EMP");
	return (found[0] != string::npos);
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
	return (found[0] != std::string::npos && found[1] != std::string::npos);
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

float Company::checkBasic() {
	float input;
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