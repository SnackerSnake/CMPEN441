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
*  Assignment : M4 Lab: POSIX Threads
*
*  Sources:
*  https://www.geeksforgeeks.org/loops-in-c-and-cpp/
*  https://www.geeksforgeeks.org/functions-that-are-executed-before-and-after-main-in-c/#:~:text=With%20GCC%20family%20of%20C,executed%20after%20main()%20ends.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int length =5; //length of the arrayMeesaGonnaSort

// Declaration of function to sort the array which will run on thread
void *SortArrayFunction (void *inputArray);

//main method

int main() {

    int arrayMeesaGonnaSortMain[length], index;

    int continueOrNot;

    pthread_t id; 

   
    do {

        printf("Enter 5 numbers: ");

        for (index = 0; index < length; ++index)
            scanf("%d", &arrayMeesaGonnaSortMain[index]);

        //Handles threads for sorting.
        pthread_create(&id, NULL, SortArrayFunction, (void *)&arrayMeesaGonnaSortMain);
        pthread_join(id, NULL);

        
        //Asking the user if they will continue or not.
        printf("\nWould you like to continue ? Enter (0) Yes, (1) No : ");
        scanf("%d", &continueOrNot);

  

    } while (continueOrNot == 0);

    return 0;

}

void *SortArrayFunction (void *inputArray){
    
    //loop variables
    int index,jndex,temporary;
    int *arrayMeesaGonnaSort = (int *)inputArray; //array variable

     //Sorting foor loops

     for (index = 0; index < length; ++index) {

            for (jndex = index + 1; jndex < length; ++jndex) {

                if (arrayMeesaGonnaSort[index] > arrayMeesaGonnaSort[jndex])

                {

                    temporary = arrayMeesaGonnaSort[index];

                    arrayMeesaGonnaSort[index] = arrayMeesaGonnaSort[jndex];

                    arrayMeesaGonnaSort[jndex] = temporary;

                }

            }

        }

        //For loop for printing the array.
        printf("Sort Array: ");
        for (index = 0; index < length-1; ++index) {

            printf("%d, ", arrayMeesaGonnaSort[index]);

        }

            printf("%d ", arrayMeesaGonnaSort[4]);


       
    //This return will return us from the thread.
    return NULL; 

}