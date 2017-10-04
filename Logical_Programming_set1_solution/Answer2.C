#include<stdio.h>
#include<conio.h>
void OddEven(int p);
void main()
{int n;
clrscr();
START:
printf("\nEnter the number of elements to display\t");
scanf("%d",&n);//user input
if(n>0){ // positive validation
OddEven(n);
}else{
printf("\nEnter Positive Number");
goto START;}
getch();}
/* this method will print the odd odd even even odd odd ....
series for the user input  */
void OddEven(int p){
int i,count=1,y=0,x=1;
for(i=1;count<=p;i++){
	if((i%2)==x){
		printf("%d\t",i);
		y=y+1;
		count=count+1;}
	if(y==2){
		if(x==1){x=0;}
		else{x=1;}
		y=0;}}}