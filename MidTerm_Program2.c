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
*  Name       :  David Hernandez
*  PSU Email  : dah5825@psu.edu
*  Assignment : Midterm
*/

#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>

int fact(int x){
	//__________________________________________________________
	//##########################################################
	//  Complete the following section : 
	//##########################################################
	// Write the code that will calculate factorial of x
		if (x == 0)  {
    return 1;  
	}
  else  {
    return(x * fact(x-1));  
  }
  	//##########################################################
	//  End of section
	//##########################################################
    //__________________________________________________________
}
void main() {
    int p_c[2];
    int c_p[2];
    int x;
    int tmp;
    
    pipe(p_c);
    pipe(c_p);
    
    pid_t pid = fork();
   
   
       
		
	//__________________________________________________________
	//##########################################################
	//  Complete the statements in following section : 
	//##########################################################
    //Check if the process is the child process. 
		// if it is the child process, read the number sent from  
		//    the parent process into the pipe .
		
		if( pid==0 ){		//Child 
		close( c_p[0] ) ; //close the read end in c_p
        close(  p_c[1]   ); //close the write end in p_c
   
 
      
        
        do{
            read(p_c[0], tmp, sizeof(tmp)	);
            
            if(x!=-1){
                tmp = fact(x);
                write( c_p[1] , tmp ,sizeof( tmp)); //need to do
            }
        }while(x!= -1);
        close(  p_c[1]  ); //close the write end in p_c
        close(  c_p[0]   ); //close the read end  in c_p
		
		
	//##########################################################
	//  End of section
	//##########################################################
    //__________________________________________________________
        
    }else if(pid > 0){
        
		//__________________________________________________________
		//##########################################################
		//  Complete the statements in following section : 
		//##########################################################
		//parent
		
        close(   p_c[1]    ); //close the write end in p_c
        close(  c_p[0]     ); //close the read end  in c_p
        
        do{
            printf("Enter a number to calculate factorial:");
            scanf("%d",&x);
           
            write(  c_p[1]      ,  tmp     ,sizeof( tmp)); //need to do
            
        
        if(x == -1)
            break;
            
            // Read the factorial result from the c_p pipe in tmp variable 
            read( p_c[0]    ,   tmp  ,sizeof( tmp)); //need to do
             
            printf("Result = %d\n",tmp);
            
        }while(x!= -1);
        
        close(  c_p[0] ); //close the read end in c_p
        close(   p_c[1] ); //close the write end in p_c
        wait();         // wait for the child to exit
    }else{
        printf("Error Forking\n");
        
    }
    
    
}