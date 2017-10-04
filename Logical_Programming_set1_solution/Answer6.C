#include<stdio.h>
#include<conio.h>
int SumOfNumber(int x);
void main(){
int n,result;
clrscr();
START:
printf("\nEnter the number");
scanf("%d",&n);//user input
if(n>0){ //positive validation
result=SumOfNumber(n);}
else{
printf("\nEnter Positive Number");
goto START;}
printf("\nThe Sum of digits=%d",result);
getch();}
 /* method will calculate the sum of digits entered by the user  */
int SumOfNumber(int x){
int rem,sum=0;
while(x!=0){
rem=x%10;
sum=sum+rem;
x=x/10;}
return sum;}