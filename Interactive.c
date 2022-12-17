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
*https://www.learn-c.org/en/Linked_lists
*https://stackoverflow.com/questions/1352749/multiple-arguments-to-function-called-by-pthread-create
*/

#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>

//Defining a node
typedef struct node {
    int ID;            
    int value;           
    struct node *next; 
} nodetype;

//Defining two arguments (or inputs) for pthreads
struct arg_struct {
    int arg1;
    int arg2;
};

//Get that data from user
nodetype *enqueue(nodetype *rear) {
    nodetype *pointy;
    int mTempValue, nTempValue;
    printf("Enter an ID and a value for a node to add to the list, Enter -1 to stop:");
    scanf("%d %d", &nTempValue, &mTempValue);
    if (nTempValue == -1) return NULL;
    pointy = (nodetype *)malloc(sizeof(nodetype));
    if (pointy != NULL) {
        pointy->ID = nTempValue;
        pointy->value = mTempValue;
        if (rear == NULL)
            rear = pointy;
        else {
            rear->next = pointy;
            rear = pointy;
        }
        rear->next = NULL;
    } 
    else {
        printf("Failed to allocate memory.");
        return rear;
    }
    return rear;
}

//Round Robin Function algorithm 
void * round_robin(void * arg) {
    struct arg_struct *args = arg;
    nodetype *pointyRobin=(nodetype *) args->arg1;
    int zeNodeValue= (int *) args->arg2;
    
    nodetype *temp = pointyRobin;
    nodetype *temp2;

    while (pointyRobin != NULL) {
        temp2 = pointyRobin;
        while (temp2 != NULL) {
            printf("Current Node %d :time value before %d, after quantum %d\n", temp2->ID, temp2->value, (temp2->value) - zeNodeValue);
            temp2->value = (temp2->value) - zeNodeValue;
            temp2 = temp2->next;
        }

        for (int i = 0; i < 20; i++) printf("#");
        printf("\n");

        temp = pointyRobin;
        temp2 = pointyRobin->next;

        // The start element
        while (temp->value <= 0) {
            //Eh, remove it
            printf("Job with ID %d and time %d will be removed.\n", temp->ID, temp->value);
            free(temp);

            if (temp2 == NULL) {
                // Hmm, no elements are remaining.
                pointyRobin = NULL;
                break;
            }

            //Hey, new value.
            temp = temp2;
            pointyRobin = temp2;

            temp2 = temp->next;
        }
        // Here are the rest of the elements.
        while (temp2 != NULL) {
            // Remove temp2 if value is less than or equal to 0.
            if (temp2->value <= 0) {
                // Remove temp2.
                temp->next = temp2->next;
                printf("Job with ID %d and time %d will be removed.\n", temp2->ID, temp2->value);
                free(temp2);
                temp2 = temp->next;
                continue;
            }
            temp = temp->next;
            temp2 = temp->next;
        }

        for (int i = 0; i < 20; i++) printf("#");
        printf("\nIteration completed, RoundRobin Will Start from begining of the list\n\n");
    }
}

void printList(nodetype * head) {
    nodetype * current = head;

//We print ID and value.
    while (current != NULL) {
        printf("Node ID %d ", current->ID);
        printf("with value ");
        printf("%d\n", current->value);
        current = current->next;
    }
    }
    
int main() {
    //Variables we need
    nodetype *first = NULL, *last = NULL;
    
    pthread_t firstThread; 

    printf("Round Robin simulation program\n");

    int quantumValue;
    
    
    
    printf("Enter a quantum Value to be used:");
    scanf("%d", &quantumValue);

    /* Take the value inputs from the user.*/
    while (1) {
        nodetype *temp = enqueue(last);
        if (temp == NULL)
            break;
        else
            last = temp;
        if (first == NULL) first = last;
    }
    printf("\n\n");
    
    printf("RoundRobin Will Start on the following List:\n");
    printf("Linked List Contain the following values:\n");
    printList(first);
    printf("\n");
    
    //Variables for two arguments for pthread
    struct arg_struct args;
    args.arg1 = first;
    args.arg2 = quantumValue;
    
    //Do the round robin function
    pthread_create(&firstThread, NULL, &round_robin, (void *)&args);
    
    //round_robin(first, quantumValue);
    
    //Exit
    pthread_join(firstThread, NULL);
    
    printf("\n\nRoundRobin:: All Jobs Completed");
    return 0;
}