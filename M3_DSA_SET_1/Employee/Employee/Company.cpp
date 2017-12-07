#include "Company.h"
#include<iostream>

string name, sex, address, phoneNumber, EmailId, department, position, currentProject="Bench";

unsigned int id = 101, birthDate, birthMonth, birthYear, joiningDate, joiningMonth, joiningYear, HRA, basic, PF, gross, index;

bool check;

size_t found[10];

Employee employee;

SearchEmployee searchEmployee;

Company::Company()
{
}


Company::~Company()
{
}

/*Method to create Employees*/
void Company::createEmployee(){

		cout << "Enter the employee details" << endl;
		employee.setId(id);
		id++;
		cout << "Employee name" << endl;
		cin>> name;
		employee.setName(name);
		SEX:
		cout << "Employee Sex" << endl;
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
		BDATE:
		cout << "Employee Date of birth(day)" << endl;
		cin >> birthDate;
		check = checkDate(birthDate);
		if (check){
			employee.setBirthDate(birthDate);
		}
		else
		{
			cout << "Enter valid Date" << endl;
			goto BDATE;
		}
		BMONTH:
		cout << "Date of birth(month)" << endl;
		cin >> birthMonth;
		if (checkMonth(birthMonth)){
			employee.setBirthMonth(birthMonth);
		}
		else
		{
			cout << "Enter valid month" << endl;
			goto BMONTH;
		}
		BYEAR:
		cout << "Date of birth(year)" << endl;
		cin >> birthYear;
		if (checkYear(birthYear)){
			employee.setBirthYear(birthYear);
		}
		else
		{
			cout << "Enter valid year" << endl;
			goto BYEAR;
		}
		JDATE:
		cout << "Employee Joining date" << endl;
		cin >> joiningDate;
		if (checkDate(joiningDate)){
			employee.setJoiningDate(joiningDate);
		}
		else
		{
			cout << "Enter valid date" << endl;
			goto JDATE;
		}
		JMONTH:
		cout << "Joining month" << endl;
		cin >> joiningMonth;
		if (checkMonth(joiningMonth)){
			employee.setJoiningMonth(joiningMonth);
		}
		else
		{
			cout << "Enter valid month" << endl;
			cin.clear();
			goto JMONTH;
		}
		JYEAR:
		cout << "Joining year" << endl;
		cin >> joiningYear;
		if (checkYear(joiningYear)){
			employee.setJoiningYear(joiningYear);
		}
		else
		{
			cout << "Enter valid year" << endl;
			goto JYEAR;
		}
		cout << "Employee address" << endl;
		cin >> address;
		employee.setAddress(address);
		cout << "Employee Phone number" << endl;
		cin >> phoneNumber;
		employee.setPhoneNumber(phoneNumber);
		EMAIL:
		cout << "Employee Email Id" << endl;
		cin >> EmailId;
		if (checkEmailId(EmailId)){
			employee.setEmailId(EmailId);
		}
		else
		{
			cout << "Enter valid Email" << endl;
			goto EMAIL;
		}
		DEPARTMENT:
		cout << "Employee department" << endl;
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

		cout << "Employee Current Project Name or Bench" <<endl;
		cin >> currentProject;
		employee.setCurrentProject(currentProject);

		cout << "Employee HRA" << endl;
		cin >> HRA;
		employee.setHRA(HRA);
		cout << "Employee Basic" << endl;
		cin >> basic;
		employee.setBasic(basic);
		cout << "Employee PF" << endl;
		cin >> PF;
		employee.setPF(PF);
		cout << "Employee Gross" << endl;
		cin >> gross;
		employee.setGross(gross);
		//assigning employee object to vector
		employeeV.push_back(employee);
}



/*Method to fing the Highest pay in a particular department*/
void Company::getHighestPayinDepartment(string department){
	vector<Employee> departmentV;
	int highestPay,id;
	for (int index = 0; index < (employeeV.size()); index++){
		if (employeeV[index].getDepartment() == department){
			departmentV.push_back(employeeV[index]);
		}
	}
	//setting the first employee in the vector departmentV as highestpay
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

/*Method to get list of Employees Joined in a particular year*/
void Company::getByYear(int year){
	vector<Employee> yearV;
	for (int index = 0; index < employeeV.size(); index++){
		if (employeeV[index].getJoiningYear() == year){
			yearV.push_back(employeeV[index]);
		}
	}
	//displaying the employee name of the given year
	cout << "************************************************" << endl;
	for (int k = 0; k < yearV.size(); k++){
		cout << "Employee Id: " << '\t' << yearV[k].getId() << '\t' << "Employee Name:" << '\t' << yearV[k].getName() << endl;
	}
	cout << "************************************************" << endl;

}

/*Method to Update A Employee Pay by 5%*/
string Company::updatePayById(int id){
	index = searchEmployee.interpolation_search(employeeV, employeeV.size(), id);
			int temp = employeeV[index].getGross();
			temp += (temp * 5) / 100;
			employeeV[index].setGross(temp);
			return "Updated Successfully";
}

/*Method to Bench a working Employee*/
string Company::benchEmployee(int id){
	index = searchEmployee.interpolation_search(employeeV, employeeV.size(), id);
	employeeV[index].setCurrentProject("Bench");
		bench.push(employeeV[index]);
		return "Added sucessfully";
	
}

/*Method to Assign Project to Bench Employee*/
string Company::removeBenchEmployee(){
	if (!bench.empty()){
		int id=bench.front().getId();
		index = searchEmployee.interpolation_search(employeeV, employeeV.size(), id);
		employeeV[index].setCurrentProject("Project");
		bench.pop();
		return "Removed Sucessfully";
	}
	else
	{
		return "Bench is empty";
	}

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
		cout << "Employee HRA" << '\t' << employeeV[k].getHRA() << endl;
		cout << "Employee Basic" << '\t' << employeeV[k].getBasic() << endl;
		cout << "Employee PF" << '\t' << employeeV[k].getPf() << endl;
		cout << "Employee Gross" << '\t' << employeeV[k].getGross() << endl;
		cout << "************************************************" << endl;
	}
}


/*Method to Display only particular Employee details*/
void Company::display(int id){
	
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
		cout << "Employee HRA" << '\t' << employeeV[index].getHRA() << endl;
		cout << "Employee Basic" << '\t' << employeeV[index].getBasic() << endl;
		cout << "Employee PF" << '\t' << employeeV[index].getPf() << endl;
		cout << "Employee Gross" << '\t' << employeeV[index].getGross() << endl;
		cout << "************************************************" << endl;
}

/*Methods to validate the user input for date month year gender and email*/
bool Company::checkDate(int date){
	if (0 < date && date <= 31){
		return true;
	}
	else
	{
		return false;
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
bool Company::checkYear(int year){
	if (1950 <= year && year <= 2018){
		return true;
	}
	else
	{
		return false;
	}
}
bool Company::checkSex(string sex){
	found[0] = sex.find("MALE");
	found[1] = sex.find("male");
	found[2] = sex.find("FEMALE");
	found[3] = sex.find("female");
	found[4] = sex.find("TRANSGENDER");
	found[5] = sex.find("transgender");
	if (found[0] != std::string::npos || found[1] != std::string::npos){
		return true;
	}
	else if (found[2] != std::string::npos || found[3] != std::string::npos)
	{	
		return true;
	}
	else if (found[4] != std::string::npos || found[5] != std::string::npos)
	{	
		return true;
	}
	else
	{
		return false;
	}

}
bool Company::checkEmailId(string email){
	
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
	found[0] = department.find("DEVELOPMENT");
	found[1] = department.find("development");
	found[2] = department.find("TESTING");
	found[3] = department.find("testing");
	found[4] = department.find("HR");
	found[5] = department.find("hr");
	found[6] = department.find("IT");
	found[7] = department.find("it");
	found[8] = department.find("ADMIN");
	found[9] = department.find("admin");
	if (found[0] != std::string::npos || found[1] != std::string::npos){
		return true;
	}
	else if (found[2] != std::string::npos || found[3] != std::string::npos)
	{
		return true;
	}
	else if (found[4] != std::string::npos || found[5] != std::string::npos)
	{
		return true;
	}
	else if (found[6] != std::string::npos || found[7] != std::string::npos){
		return true;
	}
	else if (found[8] != std::string::npos || found[9] != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}

}


bool Company::checkPosition(string position){
	found[0] = position.find("ENGINEER");
	found[1] = position.find("engineer");
	found[2] = position.find("TESTER");
	found[3] = position.find("tester");
	found[4] = position.find("MANAGER");
	found[5] = position.find("manager");
	found[6] = position.find("TEAMLEAD");
	found[7] = position.find("teamlead");
	found[8] = position.find("ADMIN");
	found[9] = position.find("admin");
	if (found[0] != std::string::npos || found[1] != std::string::npos){
		return true;
	}
	else if (found[2] != std::string::npos || found[3] != std::string::npos)
	{
		return true;
	}
	else if (found[4] != std::string::npos || found[5] != std::string::npos)
	{
		return true;
	}
	else if (found[6] != std::string::npos || found[7] != std::string::npos){
		return true;
	}
	else if (found[8] != std::string::npos || found[9] != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}

}




