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
*  Assignment : M6 Lab: Scheduling algorithms implementations
* Sources: https://www.youtube.com/watch?v=uA8X5zNOGw8&t=213s&ab_channel=JacobSorber
* https://www.youtube.com/watch?v=It0OFCbbTJE&ab_channel=JacobSorber
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//Defines what nodes are
typedef struct node{
    int ID,value;
    struct node *next;
}nodetype;
int nodey=0;

//First Come First Served algorithm function
void* firstComeFirstServed(void * arg){
    nodetype *pointy = (nodetype *) arg;
    
    printf("\n\nFCFS Job Order:\n");
    printf("FCFS Jobs will be executed in the order they arrived:\n");
    printf("Linked List Contain the following values:\n");
    while(pointy!=NULL){
        printf("Node ID %d with value %d\n",pointy->ID,pointy->value);
        pointy=pointy->next;
    }
    printf("FCFS Done\n\n");
}

//Function for user input
nodetype* enqueue(nodetype *rear){
    nodetype *pointy;
    int mtemp;
    printf("\nEnter an ID and a value for a node to add to the list, Enter -1 to stop: ");
    scanf("%d %d",&nodey,&mtemp);
    if(nodey==-1)
        return rear;
    pointy=(nodetype *)malloc(sizeof(nodetype));
    if(pointy!=NULL){
        pointy->ID=nodey;
        pointy->value=mtemp;
        if(rear==NULL)
            rear=pointy;
        else{
            rear->next=pointy;
            rear=pointy;
        }
        rear->next=NULL;
    }
    return rear;
}

//Shortest Job First algorithm function
void* shortestJobFirst(void * arg){
    nodetype *ftemp= (nodetype *) arg;
    
    nodetype *current=ftemp,*index = NULL;  
    int temp;  
    if(ftemp==NULL) {  
        return NULL;  
    }  
    else {  
        while(current != NULL) {  
            index = current->next;  
            while(index != NULL) {  
                if(current->value > index->value) {  
                    temp = current->value;  
                    current->value = index->value;  
                    index->value = temp;
                    temp = current->ID;
                    current->ID = index->ID;
                    index->ID=temp;
                }  
                index = index->next;  
            }  
            current = current->next;  
        }      
    }
    printf("\nSJF Jobs Order:\n");
    while(ftemp!=NULL){
        printf("Shortest Job to Run next is with ID: %d and Time %d\n",ftemp->ID,ftemp->value);
        ftemp=ftemp->next;
    }
    printf("SJF: All Jobs Completed");
}


int main(){
    //variables we'll need
    pthread_t firstThread; 
    pthread_t secondThread; 
    nodetype *first=NULL,*last=NULL;
    
    while(nodey!=-1){
        last=enqueue(last);
        if(first==NULL)
            first=last;
    }
    
    //creating first thread for first come first served
    pthread_create(&firstThread, NULL, firstComeFirstServed, &*first);
    
    //firstComeFirstServed(first);
    
    //ending first thread
    pthread_join(firstThread, NULL);
   
   //creating second thread for shortest job first
    pthread_create(&secondThread, NULL, shortestJobFirst, &*first);
    
    //shortestJobFirst(first);
    
    //ending second thread
    pthread_join(secondThread, NULL);
    
    printf("\nAll Threads completed");
    return 0;
}