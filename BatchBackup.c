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

typedef struct node{
    int id,val;
    struct node *next;
}nodetype;
int n=0;
void* fcfs(void * arg){
    nodetype *p = (nodetype *) arg;
    
    printf("\n\nFCFS Job Order:\n");
    printf("FCFS Jobs will be executed in the order they arrived:\n");
    printf("Linked List Contain the following values:\n");
    while(p!=NULL){
        printf("Node ID %d with value %d\n",p->id,p->val);
        p=p->next;
    }
    printf("FCFS Done\n\n");
}
nodetype* enqueue(nodetype *rear){
    nodetype *p;
    int m;
    printf("\nEnter an ID and a value for a node to add to the list, Enter -1 to stop: ");
    scanf("%d %d",&n,&m);
    if(n==-1)
        return rear;
    p=(nodetype *)malloc(sizeof(nodetype));
    if(p!=NULL){
        p->id=n;
        p->val=m;
        if(rear==NULL)
            rear=p;
        else{
            rear->next=p;
            rear=p;
        }
        rear->next=NULL;
    }
    return rear;
}
void* sjf(void * arg){
    nodetype *f= (nodetype *) arg;
    
    nodetype *current=f,*index = NULL;  
    int temp;  
    if(f==NULL) {  
        return NULL;  
    }  
    else {  
        while(current != NULL) {  
            index = current->next;  
            while(index != NULL) {  
                if(current->val > index->val) {  
                    temp = current->val;  
                    current->val = index->val;  
                    index->val = temp;
                    temp = current->id;
                    current->id = index->id;
                    index->id=temp;
                }  
                index = index->next;  
            }  
            current = current->next;  
        }      
    }
    printf("\nSJF Jobs Order:\n");
    while(f!=NULL){
        printf("Shortest Job to Run next is with ID: %d and Time %d\n",f->id,f->val);
        f=f->next;
    }
    printf("SJF: All Jobs Completed");
}


int main(){
    pthread_t firstThread; 
    pthread_t secondThread; 
    nodetype *first=NULL,*last=NULL;
    
    while(n!=-1){
        last=enqueue(last);
        if(first==NULL)
            first=last;
    }
    
    pthread_create(&firstThread, NULL, fcfs, &*first);
    
    fcfs(first);
    
    pthread_join(firstThread, NULL);
   
    pthread_create(&secondThread, NULL, sjf, &*first);
    
    sjf(first);
    
    pthread_join(secondThread, NULL);
    
    printf("\nAll Threads completed");
    return 0;
}