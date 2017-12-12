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

	float HRA;

	float basic;

	float allowance;

	float PF;

	float net;

	float gratuity;

	float gross;


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
	void setHRA(float hra);
	float getHRA();
	void setBasic(float basic);
	float getBasic();
	void setAllowance(float allowance);
	float getAllowance();
	void setPF(float pf);
	float getPF();
	void setNet(float net);
	float getNet();
	void setGratuity(float gratuity);
	float getGratuity();
	void setGross(float gross);
	float getGross();

};

#endif