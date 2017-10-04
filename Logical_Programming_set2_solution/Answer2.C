#include<stdio.h>
#include<conio.h>
void count(char word);
//Global variable
char line,word[150];
int i,vowels=0,consonants=0,digits=0,spaces=0;
//main function
void main(){
 clrscr();
 printf("\nEnter a line of string:");
 scanf("%[^\n]",word);
 for(i=0;word[i]!='\0';++i){
 count(word[i]);
 }
 printf("\nVowels: %d",vowels);
 printf("\nConsonants: %d",consonants);
 printf("\nDigits: %d",digits);
 printf("\nSpaces: %d",spaces);
 getch();
}
//method for finding the type of character
void count(char line){
      if(line=='a' || line=='e'|| line=='i' || line=='o'|| line=='u' || line=='A'|| line=='E' || line=='I'|| line=='O' || line=='U' ){
      ++vowels;
      }else if((line>='a' && line<='z') || (line>='A' && line<='Z')){
      ++consonants;
      }else if(line>='0' && line<='9'){
      ++digits;
      }else if(line==' '){
      ++spaces;
    }
}