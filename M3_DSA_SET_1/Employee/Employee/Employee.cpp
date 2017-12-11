#include "Employee.h"


Employee::Employee()
{
}


Employee::~Employee()
{
}

/*Getter and Setter methods for the class Employee variables*/

void Employee::setId(string id){
	this->id = id;
}


string Employee::getId(){

	return this->id;

}

void Employee::setName(string name){

	this->name = name;

}

string Employee::getName(){

	return this->name;

}

void Employee::setSex(string sex){

	this->sex = sex;

}

string Employee::getSex(){

	return this->sex;

}

void Employee::setAddress(string address){

	this->address = address;

}

string Employee::getAddress(){

	return this->address;

}

void Employee::setPhoneNumber(long int phoneNumber){

	this->phoneNumber = phoneNumber;

}

long int Employee::getPhoneNumber(){

	return this->phoneNumber;

}

void Employee::setEmailId(string emailId){

	this->EmailId = emailId;

}

string Employee::getEmailId(){

	return this->EmailId;

}

void Employee::setBirthDate(int date){

	this->birthDate = date;

}

int Employee::getBirthDate(){

	return this->birthDate;

}

void Employee::setBirthMonth(int month){

	this->birthMonth = month;

}

int Employee::getBirthMonth(){

	return this->birthMonth;

}

void Employee::setBirthYear(int year){

	this->birthYear = year;

}

int Employee::getBirthYear(){

	return this->birthYear;

}

void Employee::setJoiningDate(int date){

	this->joiningDate = date;

}

int Employee::getJoiningDate(){

	return this->joiningDate;

}

void Employee::setJoiningMonth(int month){

	this->joiningMonth = month;

}

int Employee::getJoiningMonth(){

	return this->joiningMonth;

}

void Employee::setJoiningYear(int year){

	this->joiningYear = year;

}

int Employee::getJoiningYear(){

	return this->joiningYear;

}
void Employee::setDepartment(string department){

	this->department = department;

}

string Employee::getDepartment(){

	return this->department;

}

void Employee::setPosition(string position){

	this->position = position;

}

string Employee::getPosition(){

	return this->position;

}

void Employee::setCurrentProject(string currentProject){

	this->currentProject = currentProject;

}

string Employee::getCurrentProject(){

	return this->currentProject;

}

void Employee::setHRA(int hra){

	this->HRA = hra;

}

int Employee::getHRA(){

	return this->HRA;

}

void Employee::setBasic(int basic){

	this->basic = basic;

}

int Employee::getBasic(){

	return this->basic;

}

void Employee::setAllowance(int allowance){

	this->allowance = allowance;

}

int Employee::getAllowance(){

	return this->allowance;

}

void Employee::setPF(int pf){

	this->PF = pf;

}

int Employee::getPF(){

	return this->PF;

}

void Employee::setNet(int net){

	this->net = net;

}

int Employee::getNet(){

	return this->net;

}

void Employee::setGratuity(int gratuity){

	this->gratuity = gratuity;

}

int Employee::getGratuity(){

	return this->gratuity;

}

void Employee::setGross(int gross){

	this->gross = gross;

}

int Employee::getGross(){

	return this->gross;

}
