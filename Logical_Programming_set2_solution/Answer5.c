#include<conio.h>
#include<stdio.h>
//Global variable
int binary[10];
int length=-1;
//method to convert decimal to binary
void decimalToBinary(int decimal){
	int j;
	while (decimal>0){
	length++;
	binary[length]=decimal%2;   //calculate binary value
	decimal=decimal/2;
	}
	printf("\nbinary number \t");
	for(j=length;j>=0;j--)
	printf("%d",binary[j]);

}
//method to convert binary to decimal
void binaryToDecimal(){
int i,base=2,decimal=0;
 for(i=length;i>=0;i--){
 decimal=decimal*base+binary[i];
 }
printf("\nDecimal number \t%d",decimal);
}
//method to invert the bits according to user input
void invert(int position ,int bits){
	int arr_pos,j=1;
	for(arr_pos=length-position+1;j<=bits;arr_pos--){
		if(binary[arr_pos]==1)
			binary[arr_pos]=0;    //byte is changed
		else
			binary[arr_pos]=1;
	j++;
	}
	printf("\nbinary after change\t");
	for(j=length;j>=0;j--)
	printf("%d",binary[j]);
	binaryToDecimal();
}
//main function
void main(){
	int decimal=0;
	int position=0;
	int bits=0;
	clrscr();
	printf("\nEnter decimal number\t");
	scanf("%d",&decimal);
	if(decimal>0){
	decimalToBinary(decimal);
	}
	printf("\nEnter position\t");
	scanf("%d",&position);
	printf("Enter no of bits\t");
	scanf("%d",&bits);
	if((position>=0)&(bits>0)){
	invert(position,bits);
	}
	getch();
}