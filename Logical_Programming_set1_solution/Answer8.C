#include<stdio.h>
#include<conio.h>
void login(int p);
int getUserId(int userId);
// global variable
int uid[]={1,2,3,47,10};
int pwd[]={123,345,567,934,894};
int id,x;
void main(){
clrscr();
/* label to point to the starting of the code */
START:
printf("\nEnter the User Id\t");
/* get user id from the user*/
scanf("%d",&id);
/* check whether given id is not of negative value */
if(id>0){
	x=getUserId(id);
/* check the returned id is valid or not if not valid then
we label it back to start */
	if(uid[x]==id){
		login(x);
	}else{
		clrscr();
		printf("\nInvalid User Id");
		goto START;}
}else{
	clrscr();
	printf("\nEnter Correct User id");
	goto START;}
getch();}
/* to find the user id is available in the array if available
  then that index value is returned*/
int getUserId(int userId){
int i;
for(i=0;i<sizeof(uid);i++){
	if(uid[i]==userId){
		return i;}}}
/* password is entered by user and its is validated if
wrong ask user to enter the password again.  */
void login(int p){
int j=0,pass;
printf("\nEnter the password\t");
	LOOP:
	scanf("%d",&pass); //input from user
	if(pass>0){    //postive validation
	if(pwd[p]==pass){   //password validation
	printf("\nWelcome %d",uid[p]);
	}else {
	j=j+1;
	if(j==3){
	printf("\nAll 3 attempts failed. Try again after some times.");
	}else{
	printf("\nRe-Enter the password\t");
	goto LOOP;}}}
	else{
	printf("\nEnter the password correctly");
	goto LOOP;}}