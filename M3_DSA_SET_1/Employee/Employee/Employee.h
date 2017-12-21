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

	void setId(string );
	string getId();
	void setName(string );
	string getName();
	void setSex(string );
	string getSex();
	void setAddress(string );
	string getAddress();
	void setPhoneNumber(long int );
	long int getPhoneNumber();
	void setEmailId(string );
	string getEmailId();
	void setBirthDate(int );
	int getBirthDate();
	void setBirthMonth(int );
	int getBirthMonth();
	void setBirthYear(int );
	int getBirthYear();
	void setJoiningDate(int );
	int getJoiningDate();
	void setJoiningMonth(int );
	int getJoiningMonth();
	void setJoiningYear(int );
	int getJoiningYear();
	void setDepartment(string );
	string getDepartment();
	void setPosition(string );
	string getPosition();
	void setCurrentProject(string );
	string getCurrentProject();
	void setHRA(float );
	float getHRA();
	void setBasic(float );
	float getBasic();
	void setAllowance(float );
	float getAllowance();
	void setPF(float );
	float getPF();
	void setNet(float );
	float getNet();
	void setGratuity(float );
	float getGratuity();
	void setGross(float );
	float getGross();

};

#endif