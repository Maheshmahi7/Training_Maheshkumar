#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void DisplayByYear();
void DisplayByDepartment();
void SearchByCGPA();
void SearchByDepartmentCGPA();
void SearchByName();
void AllStudent();
void UpdateCGPA();
void DisplayStudent(int x);
//structure for students
struct student{
char name[50],department[50];
int id,year;
float cgpa;
}s[20];
//global variable
int choice,size,i;
//main function
void main(){
char leave='n';
float dummy=5.0f;
clrscr();
printf("\nEnter the number ofstudents\n");
scanf("%d",&size);
if(size>0){
printf("\nEnter the student details name,department,year,cgpa\n");
for(i=0;i<size;i++){
s[i].id=i+1;
s[i].cgpa=0.0f;
scanf("%s",&s[i].name);
scanf("%s",&s[i].department);
scanf("%d",&s[i].year);
scanf("%f",&dummy);
s[i].cgpa=dummy;
}
//loop for user UI
while(leave=='n'){
clrscr();
printf("\n1.Display Names of students from a particular year");
printf("\n2.Display Names of students from a particular department");
printf("\n3.Display all details of the student having the highest CGPA");
printf("\n4.Display all details of the student having the highest CGPA in a particular department");
printf("\n5.Dispaly all details of the student");
printf("\n6.Display all details of all student");
printf("\n7.Update CGPA of a student");
printf("\n8.Exit\n");
scanf("%d",&choice);
switch(choice){
  case 1: DisplayByYear();
  break;
  case 2: DisplayByDepartment();
  break;
  case 3: SearchByCGPA();
  break;
  case 4: SearchByDepartmentCGPA();
  break;
  case 5: SearchByName();
  break;
  case 6: AllStudent();
  break;
  case 7: UpdateCGPA();
  break;
  case 8: leave='y';
  break;
  default : printf("\nPlease Choice some option from above menu");
  break;
}
if(leave=='n'){
printf("\nDo you want to exit(y/n)\n");
scanf("%s",&leave);
}
}
getch();
}
}
//method for displaying students by year
void DisplayByYear(){
int year;
printf("\nEnter the Year:\t");
scanf("%d",&year);
for(i=0;i<size;i++){
if(year==s[i].year){
printf("\n%s",s[i].name);
}
}
}
//method for displaying students details by department
void DisplayByDepartment(){
char department[50];
printf("\nEnter the Department:\t");
scanf("%s",&department);
for(i=0;i<size;i++){
if(strcmp(department,s[i].department)==0){
printf("\n%s",s[i].name);
}
}
}
//search student with highest CGPA
void SearchByCGPA(){
int largest=0;
for(i=0;i<size;i++){
	if(s[largest].cgpa<s[i].cgpa){
		largest=i;
	}
}
printf("\nThe Student with highest CGPA:");
DisplayStudent(largest);
}
//search student with highest cgpa in particular department
void SearchByDepartmentCGPA(){
int largest=0,d[50],j=0,localSize;
char department[50];
printf("\nEnter the department to which the highest CGPA should be found\n");
scanf("%s",&department);
for (i=0;i<size;i++){
	if(strcmp(department,s[i].department)==0){
		d[j]=i;
		j++;
	}
}
largest=d[0];
localSize=j;
for(i=0;i<localSize;i++){
	if(s[largest].cgpa<s[d[i]].cgpa){
		largest=d[i];
	}
}
printf("\nThe Student with highest CGPA:");
DisplayStudent(largest);
}
//search student by name
void SearchByName(){
char name[50];
printf("\nEnter the Student Name:\t");
scanf("%s",&name);
for(i=0;i<size;i++){
if(strcmp(name,s[i].name)==0){
DisplayStudent(i);
}
}
}
//display all student records
void AllStudent(){
for(i=0;i<size;i++){
DisplayStudent(i);
}
}
//update particular students cgpa
void UpdateCGPA(){
char name[50];
printf("\nEnter the Student name to which the cgpa should be changed\n");
scanf("%s",&name);
for(i=0;i<size;i++){
if(strcmp(name,s[i].name)==0){
s[i].cgpa=s[i].cgpa+0.5;
DisplayStudent(i);
}
}
}
//display student records
void DisplayStudent(int x){
printf("\nId: %d\nName: %s\nDepartment: %s\nYear: %d\nCGPA: %.2f",s[x].id,s[x].name,s[x].department,s[x].year,s[x].cgpa);
}