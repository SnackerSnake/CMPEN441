#include<stdio.h>
#include<string.h>

//By David Hernandez

void verticalTable();

void horizontalTable();

void verticalTableInside();

void horizontalTableInside();

int main(){
   //char *word = "Transistors";
   //char *word = "Teen Titans";
   char *word = "Rick and Morty";
   //char *word = "word";
   //char *word = "!@#$%*()";
   //char *word= "testingreallybiginputbecauseimcurious";
   
   verticalTableInside(word);
   
   printf("\n\n");

   horizontalTableInside(word);
   
   return 0;
   
   
}

//this function makes the top and bottom of the vertical table
void verticalTable(){
   int index;
   
   printf("+");
   
   for(index=1;index<=5;index++)
   {
      printf("-");
   }
   
   printf("+");
   
   for(index=1;index<=4;index++)
   {
      printf("-");
   }
   
   printf("+");
   
   for(index=1;index<=5;index++)
   {
      printf("-");
   }
   
   printf("+");
  
}

//this function makes the top and bottom of the horizontal table
void horizontalTable(int length){
   int index,jndex;
   
   printf("+");
   
   for(index=1;index<=7;index++){
       printf("-");
   }
   
   for(index=1;index<=length;index++){
       printf("+");
    for(jndex=1;jndex<=5;jndex++){
       printf("-");
                                 }
   }
   
    printf("+");
}

//this function makes all of the inside parts the vertical table (index, char letter, and ascii number)
void verticalTableInside(char *input){
    
   int index;
   int length=strlen(input);
   
   verticalTable();
   
   printf("\n|index|char|ascii|\n");
   
   verticalTable();
   
   printf("\n");
   
   for(index=0;index<length;index++) {
    printf("| %2.1d | %c | %3.1d |\n",index,input[index],(int)input[index]);  
    }
   
   verticalTable();
    
}

//this function makes all of the inside parts the horizontal table (index, char letter, and ascii number)
void horizontalTableInside(char *input){
    
    int length=strlen(input);
    int index;
    
   horizontalTable(length);

   printf("\n| index |");
   
   for(index=0;index<length;index++) {
    printf(" %2.1d |",index);
    }
    
   printf("\n");
   printf("| char  |");
   
   for(index=0;index<length;index++) {
       printf("  %c |",input[index]);
   }
   
   printf("\n");
   printf("| ascii |");
   
   for(index=0;index<length;index++){
       printf("%3.2d |",(int)input[index]);
   }
   
   printf("\n");
   
   horizontalTable(length);
    
}