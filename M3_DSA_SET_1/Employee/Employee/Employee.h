#ifndef Employee_HEADER
#define Employee_HEADER


#include<string>

using namespace std;

class Employee{

private:
	string id;

	string name;

	int birthDate;

	int birthMonth;

	int birthYear;

	string sex;

	int joiningDate;

	int joiningMonth;

	int joiningYear;

	string address;

	long int phoneNumber;

	string EmailId;

	string department;

	string position;

	string currentProject;

	int HRA;

	int basic;

	int allowance;

	int PF;

	int net;

	int gratuity; 

	int gross;


public:

	Employee();

	~Employee();

	void setId(string id);
	string getId();
	void setName(string name);
	string getName();
	void setSex(string sex);
	string getSex();
	void setAddress(string address);
	string getAddress();
	void setPhoneNumber(long int phoneNumber);
	long int getPhoneNumber();
	void setEmailId(string emailId);
	string getEmailId();
	void setBirthDate(int date);
	int getBirthDate();
	void setBirthMonth(int month);
	int getBirthMonth();
	void setBirthYear(int year);
	int getBirthYear();
	void setJoiningDate(int date);
	int getJoiningDate();
	void setJoiningMonth(int month);
	int getJoiningMonth();
	void setJoiningYear(int year);
	int getJoiningYear();
	void setDepartment(string department);
	string getDepartment();
	void setPosition(string position);
	string getPosition();
	void setCurrentProject(string currentProject);
	string getCurrentProject();
	void setHRA(int hra);
	int getHRA();
	void setBasic(int basic);
	int getBasic();
	void setAllowance(int allowance);
	int getAllowance();
	void setPF(int pf);
	int getPF();
	void setNet(int net);
	int getNet();
	void setGratuity(int gratuity);
	int getGratuity();
	void setGross(int gross);
	int getGross();

};

#endif