#include<stdio.h>
#include<conio.h>
int Larger(int number[50],int largestNumber);
//global variable
int array[50],size,i,largestNumber;
//main function
void main(){
clrscr();
printf("\nEnter the size of the array\n" );
START:
scanf("%d",&size);
if(size>0){
printf("\nEnter the array elements\n");
for(i=0;i<size;i++){
scanf("%d",&array[i]);
}
largestNumber=array[0];
if(size>1){
largestNumber=Larger(array,largestNumber);
}
printf("Largest Number is:%d",largestNumber);
}
else{
printf("\nsize cannot be less then 1\n Enter the correct size\n	");
goto START;
}
getch();
}
//methid for fing the largest number
int Larger(int number[],int largestNumber){
     for(i=0;i<size;i++){
     if(largestNumber<number[i]){
      largestNumber=Larger(number,number[i]);
     }
     }
return largestNumber;
}