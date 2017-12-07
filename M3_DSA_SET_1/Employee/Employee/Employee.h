#ifndef Employee_HEADER
#define Employee_HEADER


#include<string>

using namespace std;

class Employee{

private:
	int id;

	string name;

	int birthDate;

	int birthMonth;

	int birthYear;

	string sex;

	int joiningDate;

	int joiningMonth;

	int joiningYear;

	string address;

	string phoneNumber;

	string EmailId;

	string department;

	string position;

	string currentProject;

	int HRA;

	int basic;

	int PF;

	int gross;


public:

	Employee();

	~Employee();

	void setId(int id);
	int getId();
	void setName(string name);
	string getName();
	void setSex(string sex);
	string getSex();
	void setAddress(string address);
	string getAddress();
	void setPhoneNumber(string phoneNumber);
	string getPhoneNumber();
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
	void setPF(int pf);
	int getPf();
	void setGross(int gross);
	int getGross();

};

#endif