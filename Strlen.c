/*
*  PLAGIARISM STATEMENT
*    I certify that this assignment/report is my own work, based on my personal
*    study and/or research and that I have acknowledged all material and sources
*    used in its preparation, whether they be books, articles, reports, lecture 
notes, online sources
*    and any other kind of document, electronic or personal communication. I also
*    certify that this assignment/report has not previously been submitted for
*    assessment in any other unit, except where specific permission has been 
granted
*    from all unit coordinators involved, or at any other time in this unit, and 
that I
*    have not copied in part or whole or otherwise plagiarised the work of other
*    students and/or persons.
*
*  Name       :  David A. Hernandez
*  PSU Email  : dah5825@psu.edu
*  Assignment : M3 Lab: The Fork System Call
Sources: 
https://www.youtube.com/watch?v=oLjN6jAg-sY&ab_channel=ProgrammingKnowledge2
https://flaviocopes.com/c-array-length/
https://docs.microsoft.com/en-us/cpp/c-language/cpp-integer-limits?view=msvc-170
https://scanftree.com/programs/c/to-find-factorial-of-a-number-using-c-program/
https://stackoverflow.com/questions/57331815/how-can-i-make-a-word-as-variable-in-c
https://www.programiz.com/c-programming/c-if-else-statement
https://www.tutorialspoint.com/cprogramming/c_data_types.htm
https://www.programmingsimplified.com/c/program/print-string
https://stackoverflow.com/questions/2844/how-do-you-format-an-unsigned-long-long-int-using-printf
*/

#include<stdio.h>
#include<string.h>

int main(){
    char inputString[1000];
    int stringLength;
    int index;
    
    printf("Enter a word or words: ");
    scanf("%s", inputString);

    for (stringLength = 0; inputString[stringLength] != '\0'; ++stringLength);
    
    printf("String Length: %d", stringLength);
    printf("\n");
  
  return 0;
}