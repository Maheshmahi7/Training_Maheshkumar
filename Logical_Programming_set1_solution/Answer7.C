#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int ATM(int x);
/* Global variable  */
int amount,tens=0,fiftys=0,hundreds=0,rem;
void main(){
int p;
clrscr();
START:
/* Enter the money to withdraw  */
printf("\nEnter the money to withdraw in 10, 50 and 100 Denominations\t");
scanf("%d",&amount);
if(amount>0){ //positive validation
int p=ATM(amount);
if(p==0){ // checking enter amount is valid or not
goto START;}}
else{
printf("\nEntered amount cannot be dispensed\n");
goto START;}
getch();}
/* method to calculate the denomination for the user input  */
int ATM(int x){
if((x%10)==0){
rem=x%100;
x=x-rem;
if(rem>50){
fiftys=1;
rem=rem-50;
tens=rem/10;}
else{
tens=rem/10;}
hundreds=amount/100;
printf("\nTen=%d * 10 =%d\nFifty=%d * 50=%d\nHundred=%d * 100=%d\nTotal=%d",tens,(tens*10),fiftys,(fiftys*50),hundreds,(hundreds*100),amount);
return 1;}
else{
printf("\nEntered amount cannot be dispensed\n");
return 0;}}