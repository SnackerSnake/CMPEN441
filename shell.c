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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    
int pid;
int executeOrderSixtySix = 0;
long sum;
int status;
int endParent;

   while(1){
       pid = fork();

       //This is the the child.
       if (pid == 0) {
            char command[100];
            
            printf("$");
            scanf("%s",command);
            
            if(strcmp(command,"End")==0)
                status=99;
                
            int executeOrderSixtySix=execve(command, NULL, NULL);
            
            if(executeOrderSixtySix==-1 && strcmp(command,"End")!=0){
                printf("This an error message. You did a messy wessy. uwu!\n");
               }
       }

       //This is the the parent.
       if ((endParent = waitpid (pid, &status, 0)) == -1){
           
              if(status==99){
                  
                  kill(pid,SIGSTOP);
                  
                  kill(getpid(),SIGSTOP);
                  
                            }
       }

}

return 0;
}