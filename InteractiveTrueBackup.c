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

typedef struct node {
    int id;            // id for the process
    int val;           // time duration for the process
    struct node *next; // next process
} nodetype;

struct arg_struct {
    int arg1;
    int arg2;
};

nodetype *enqueue(nodetype *rear) {
    nodetype *p;
    int m, n;
    printf("Enter an ID and a value for a node to add to the list, Enter -1 to stop:");
    scanf("%d %d", &n, &m);
    if (n == -1) return NULL;
    p = (nodetype *)malloc(sizeof(nodetype));
    if (p != NULL) {
        p->id = n;
        p->val = m;
        if (rear == NULL)
            rear = p;
        else {
            rear->next = p;
            rear = p;
        }
        rear->next = NULL;
    } 
    else {
        printf("Failed to allocate memory.");
        return rear;
    }
    return rear;
}
void * round_robin(void * arg) {
    struct arg_struct *args = arg;
    nodetype *p=(nodetype *) args->arg1;
    int z= (int *) args->arg2;
    
    nodetype *temp = p;
    nodetype *temp2;

    while (p != NULL) {
        temp2 = p;
        while (temp2 != NULL) {
            printf("Current Node %d :time value before %d, after quantum %d\n", temp2->id, temp2->val, (temp2->val) - z);
            temp2->val = (temp2->val) - z;
            temp2 = temp2->next;
        }

        for (int i = 0; i < 20; i++) printf("#");
        printf("\n");

        temp = p;
        temp2 = p->next;

        // for start element
        while (temp->val <= 0) {
            //remove it
            printf("Job with ID %d and time %d will be removed.\n", temp->id, temp->val);
            free(temp);

            if (temp2 == NULL) {
                // no elements are remaining
                p = NULL;
                break;
            }

            // new value
            temp = temp2;
            p = temp2;

            temp2 = temp->next;
        }
        // rest of the elements
        while (temp2 != NULL) {
            // removing temp2 if val is less
            if (temp2->val <= 0) {
                // remove temp2
                temp->next = temp2->next;
                printf("Job with ID %d and time %d will be removed.\n", temp2->id, temp2->val);
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

//need to print id and val
    while (current != NULL) {
        printf("Node ID %d ", current->id);
        printf("with value ");
        printf("%d\n", current->val);
        current = current->next;
    }
    }
    
int main() {
    nodetype *first = NULL, *last = NULL;
    
    pthread_t firstThread; 

    printf("Round Robin simulation program\n");

    int q;
    
    
    
    printf("Enter a quantum Value to be used:");
    scanf("%d", &q);

    /* taking values */
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
    
    struct arg_struct args;
    args.arg1 = first;
    args.arg2 = q;
    
    pthread_create(&firstThread, NULL, &round_robin, (void *)&args);
    
    //round_robin(first, q);
    
    pthread_join(firstThread, NULL);
    
    printf("\n\nRoundRobin:: All Jobs Completed");
    return 0;
}