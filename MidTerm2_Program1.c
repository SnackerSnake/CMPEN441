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
*  Assignment : Midterm 2
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>



//--------------------------------------------------
//Queue and list operations headers

typedef struct node{
    int data;
    struct node * next;
    struct node * previous;
}node;

typedef struct ListInfo{
    int count;
    node * list;
}ListInfo;

void Delete(ListInfo *H, int value);
void insert(ListInfo *H, node *n);
void DisplayList(ListInfo *H);
 node * Pop(ListInfo *S);
 
 
//-----------------------------------------------------
 
#define SIZE 5

int end_time = 0;
int Max_Num = -1;

//Queue Semaphores 
sem_t Sem_Empty_Slots;   //Counting semaphore holding number of empty slots
sem_t Sem_Full_Slots;    //Counting semaphore holding number of full slost


pthread_mutex_t Lock_QPrime; //Lock to shared variable input
pthread_t Prime_t;

ListInfo QPrime;

void * Prime_Thread(void * args);

//_______________________________________________
// Main function
//          Display prime numbers from the queue
//_______________________________________________

int main(){
    
    int result;

    result = sem_init(&Sem_Empty_Slots,0,5); //Initialize to 5 empty slots
    if (result != 0) {
        perror("Semaphore no Created failed\n");
        exit(EXIT_FAILURE);
    }
    
    result = sem_init(&Sem_Full_Slots,0,0);  //Initialize to 0 full slots
    if (result != 0) {
        perror("Semaphore no Created failed\n");
        exit(EXIT_FAILURE);
    }
    
    node * tmp;
    QPrime.list = NULL;
    QPrime.count = 0;
    
    
    printf("What The Max value to find all prime number to ?\n");
    scanf("%d",&Max_Num);

    
    //Start the prime thread. 
    result = pthread_create(&Prime_t,NULL,Prime_Thread,NULL);
    
    if (result != 0) {
        perror("Prime Thread Creation failed\n");
        exit(EXIT_FAILURE);
    }
        
   
    //_______________________________________________
    // Display numbers in the queue.
    //_______________________________________________
    
    do{
        sem_wait(&Sem_Full_Slots);  //Wait for a prime number to be added. [1]
         pthread_mutex_lock(&Lock_QPrime); //Lock Mutex [2]
        
        
         tmp = Pop(&QPrime);
        if(tmp != NULL)
            printf(">>>Main>>> Prime number > %d \n",tmp->data);
            
            
       pthread_mutex_unlock(&Lock_QPrime); //unlock Mutex [3]

        //Continue till all prime numbers are displayed. 
        
    }while(end_time != 1 || QPrime.count > 0); 

        
        
    // Wait for the prime thread to exist. 
   pthread_join(Prime_t,NULL); //Join the Prime_Thread Function
    
    if (result != 0) { //Check if the join was successful. 
        perror("Thread Join Faild \n");
        exit(EXIT_FAILURE);
    }
    
}


//_______________________________________________
// Prime Thread:
//      Find primes and adds it to the queue
//_______________________________________________

void * Prime_Thread(void * args){
    
    node *tmp;
    int i,j;
    
    for(i=2 ; i<=Max_Num ;i++){
         if(i == Max_Num)   end_time = 1;
        
        for(j=2;j<=i;j++){
            if(i%j == 0){
                break;
            }
        }
        
        
        if(j==i){ //prime
        sem_wait(&Sem_Empty_Slots);  //Wait for an emplty spot [4]
          pthread_mutex_lock(&Lock_QPrime);         // Lock Mutex [5]
        
        tmp = malloc(sizeof(node));
        tmp->data = i;
        
        insert(&QPrime,tmp);
        QPrime.count++;
        printf(">> Inserted A Number %d ",tmp->data);
        //DisplayList(&QPrime);
       sem_post(&Sem_Empty_Slots);  //indicate an extra prime was added [6]
        
          pthread_mutex_unlock(&Lock_QPrime);// Unlock Mutex [7]
        
        }
   
    }
    end_time = 1;
    sem_post(&Sem_Full_Slots);
    pthread_exit(0);
}


//_______________________________________________
//_______________________________________________
//_______________________________________________
///Queue and List Operations 
//_______________________________________________
//_______________________________________________


 
void DisplayList(ListInfo *H){
    
    node *ptr ;
    
    if(H == NULL){
        printf("ListInfo does not contain a list\n");
        return;
    }
    ptr = H->list;
    
    if(ptr == NULL){
        printf("List is Empty.\n");
        return;
    }
    
    printf("Linked List Contain the following values :\n");  
    
    while(ptr != NULL){
        printf("Node value %d \n", ptr->data);
        ptr = ptr->next;
      }
}

void insert(ListInfo *H, node *n){
    if(H == NULL || n == NULL ){
        return;
    }
    if(H->list == NULL){
        H->list = n;
        n->next = NULL;
        n->previous = NULL;
        return;
    }
    
    node *ptr = H->list;
    
    while(ptr != NULL && ptr->next != NULL)
        ptr = ptr->next;
        
    if(ptr != NULL){
        ptr->next = n;
        n->previous = ptr;
        n->next = NULL;

    }else{
        
    }
    
    
    return;
}

//delete the node
void Delete(ListInfo *H, int value){
    node * ptr;
    
    if(H == NULL)
        return;
        
    ptr = H->list;
    
    while( ptr != NULL && ptr->next != NULL ){
        if( ptr->data == value)
            break;
            
        ptr = ptr->next;
    }

    if(ptr != NULL && ptr->data == value){
        
        //Special case, where the node to remove is the first in the list.
        if( H->list == ptr){
            H->list = ptr->next;
             printf("Ptr Value to remove %d",ptr->data);
             printf("Ptr Value next to remove %p",ptr->next);
             if(ptr == NULL)
             printf("Ptr Value next to remove %d",ptr->data);
        }
        
        if( ptr->previous != NULL)
            ptr->previous->next = ptr->next;
        
        if(ptr->next != NULL)
            ptr->next->previous = ptr->previous;
        
        H->count--;
        //free(ptr);
    }
        
    return;
}


 node * Pop(ListInfo *S){
     
     if(S== NULL){
         perror("No Queue to Pop");         return NULL;
     }
     
     if(S->list == NULL){
         perror("Empty Queue, Nothing to remove");
         return NULL;
     }
     
     node *ptr = S->list;
     Delete(S,ptr->data);

     return ptr;

 }