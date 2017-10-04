#include<stdio.h>
#include<conio.h>
void modifyEmployee();
void displayEmployee();
void deleteEmployee();
void changeFile();
//structure for employee
struct employee{
char name[20],phoneNo[50],designation[50];
}e[5];
//main function
void main(){
int choice,i=0,size;
char leave='n';
FILE *fp=fopen("employee.txt","a+");//file open statement
clrscr();
printf("\nEnter the number of employee\n");
scanf("%d",&size);
if(size>0){
printf("\nEnter the Name, Phone Number and Designation\n");
for(i=0;i<size;i++){
	scanf("%s %s %s",&e[i].name,&e[i].phoneNo,&e[i].designation);
	fprintf(fp,"%s %s %s\n",e[i].name,e[i].phoneNo,e[i].designation);
}
fprintf(fp,"%s %s %s",'0','0','0');
while(leave!='y'){
clrscr();
printf("\n1.If you want to delete record");
printf("\n2.If you want to modifiy record");
printf("\n3.Display employee record");
printf("\n4.Exit\n");
scanf("%d",&choice);
switch(choice){
case 1: deleteEmployee();
displayEmployee();
break;
case 2: modifyEmployee();
displayEmployee();
break;
case 3: displayEmployee();
break;
case 4: leave='y';
break;
default: printf("\nEnter valid number");
break;
}
if(leave!='y'){
printf("\nDo you want to exit(y/n)\n");
scanf("%s",&leave);
}
}
fclose(fp);
remove("employee.txt");
getch();
}
}
//method to modify exisiting records
void modifyEmployee(){
char name[50],designation[50],phoneNo[50];
int i=0;
FILE *fp=fopen("employee.txt","r");
FILE *temp=fopen("temp.txt","w");
printf("\nEnter the employee name\n");
scanf("%s",&name);
while(!feof(fp)){
	fscanf(fp,"%s %s %s",e[i].name,e[i].phoneNo,e[i].designation);
	if(strcmp(e[i].name,name)==0){
		printf("\nEnter the data to be modifiyed: Phonenumber and Designation\n");
		scanf("%s %s",&phoneNo,&designation);
		strcpy(e[i].name,name);
		strcpy(e[i].phoneNo,phoneNo);
		strcpy(e[i].designation,designation);
		}
	fprintf(temp,"%s %s %s\n",e[i].name,e[i].phoneNo,e[i].designation);
	i++;
}
remove("employee.txt");
fclose(fp);
fclose(temp);
changeFile();
}
//method to display the employee details from file
void displayEmployee(){
int i=0;
FILE *fp=fopen("employee.txt","r");
if(fp!=NULL){
while(!feof(fp)){
fscanf(fp,"%s %s %s",e[i].name,e[i].phoneNo,e[i].designation);
printf("%s %s %s\n",e[i].name,e[i].phoneNo,e[i].designation);
i++;
}
}else{
printf("\nFile not found");
}
fclose(fp);
}
//method to delete particular employee record in the file
void deleteEmployee(){
char name[50];
int i=0;
FILE *fp=fopen("employee.txt","r");
FILE *temp=fopen("temp.txt","w");
printf("\nEnter the employee name\n");
scanf("%s",&name);
while(!feof(fp)){
	fscanf(fp,"%s %s %s",e[i].name,e[i].phoneNo,e[i].designation);
	if(strcmp(e[i].name,name)==0){
	strcpy(e[i].name,'0');
	strcpy(e[i].phoneNo,'0');
	strcpy(e[i].designation,'0');
	fprintf(temp,"%s %s %s\n",e[i].name,e[i].phoneNo,e[i].designation);
	} else{
	fprintf(temp,"%s %s %s\n",e[i].name,e[i].phoneNo,e[i].designation);
	}
	i++;
}
remove("employee.txt");
fclose(fp);
fclose(temp);
changeFile();
}
//method for chnaging employee details from temp.txt to employee.txt
void changeFile(){
int i=0;
FILE *fp=fopen("employee.txt","w");
FILE *temp=fopen("temp.txt","r");
while(!feof(temp)){
fscanf(temp,"%s %s %s",e[i].name,e[i].phoneNo,e[i].designation);
fprintf(fp,"%s %s %s\n",e[i].name,e[i].phoneNo,e[i].designation);
i++;
}
remove("temp.txt");
fclose(temp);
fclose(fp);
}