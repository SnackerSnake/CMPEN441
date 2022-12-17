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
*  Assignment : M8 Lab: Deadlock with threads
References: https://psu.instructure.com/courses/2189855/pages/m8-deadlock-model-and-conditions?module_item_id=35303623
https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
because idk how to do random numbers in C

https://www.tutorialspoint.com/cprogramming/c_scope_rules.htm
*/

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//First function for handling the first thread
void *Thread_One(void *param);
//Second function for handling the first thread
void *Thread_Two(void *param);

//Mutex lock variables we need for later
pthread_mutex_t first_mutex, second_mutex;


int firstRandomNumber; //This is V1
int secondRandomNumber; //This is V2
//int thirdRandomNumber; //test code

int main(){
    pthread_t threadIDOne, threadIDTwo; 
    pthread_attr_t attributeOne, attributeTwo; 
    
    /*//test code
    srand(time(NULL));
    printf("test:\n");
    int thirdRandomNumber = rand()%1000; 
    printf("%d", thirdRandomNumber);
   */ //test code
    
    //Initiliaze mutex
    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);

    //Start thread attributes
    pthread_attr_init(&attributeOne);
    pthread_attr_init(&attributeTwo);

    //Create first thread
    pthread_create(&threadIDOne, &attributeOne, Thread_One, NULL);

    //Create second thread
    pthread_create(&threadIDTwo, &attributeTwo, Thread_Two, NULL);

    // Wait for the threads to finish
    pthread_join(threadIDOne, NULL);
    pthread_join(threadIDTwo, NULL);
}

//First thread function
void *Thread_One(void *param){
    
    pthread_mutex_lock(&first_mutex);
    
    pthread_mutex_lock(&second_mutex);
    
    srand(time(NULL));
    int firstRandomNumber= rand(); //This is V1
    printf("Thread One\n");
    printf("%d", secondRandomNumber); //This is V2
    printf("\n");
    
    pthread_mutex_unlock(&first_mutex);
    
    pthread_mutex_unlock(&second_mutex);

    
    pthread_exit(0);
}

//Second thread function
void *Thread_Two(void *param){
    
    pthread_mutex_lock(&second_mutex);
    
    pthread_mutex_lock(&first_mutex);
    
    srand(time(NULL));
    printf("Thread Two\n");
    int secondRandomNumber = rand(); //This is V2
    printf("%d", firstRandomNumber); //This is V1
    printf("\n");

    pthread_mutex_unlock(&second_mutex);
    
    pthread_mutex_unlock(&first_mutex);


    pthread_exit(0);
}