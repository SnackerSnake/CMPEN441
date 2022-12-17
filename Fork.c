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
*  Name       : David Hernandez
*  PSU Email  : dah5825@psu.edu
*  Assignment : Report
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    
    fork();
    
    if (fork() == 0){
    printf("This is a child process.\n");
    }
    else {
    printf("This is a parent process.\n");
    }
    
    return 0;

}