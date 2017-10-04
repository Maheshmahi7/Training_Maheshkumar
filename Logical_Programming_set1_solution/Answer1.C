#include<stdio.h>
#include<conio.h>
void SimpleInterest(int x,int y,int z);
void main(){
int p,r,n;
clrscr();
LOOP:
printf("\nEnter the value of p,n and r");
scanf("%d%d%d",&p,&n,&r);   //user input
if(p>0 && n>0 && r>0){   //positive validation
SimpleInterest(p,n,r);}
else{
printf("\nEnter Positive Value");
goto LOOP;}
getch();}
/* this method calculate the simple interest for the user input  */
void SimpleInterest(int x, int y, int z){
float si=(x*y*z)/100;
printf("\nPrincple=%d,\nNo of Years=%d,\nRate of Interest=%d",x,y,z);
printf("\nSimple Interset=%5.2f",si);}