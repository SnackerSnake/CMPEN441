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
*  Assignment : M7 Lab Synchronization and Mutual Exclusion
References: https://linux.die.net/man/7/sem_overview (Links to an external site.)
https://linux.die.net/man/7/pthreads (Links to an external site.)
https://www.man7.org/linux/man-pages/man3/usleep.3.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int stackArray [5] = {-1, -1, -1, -1, -1};
int topOfStacky = 0; 
pthread_mutex_t lock;
sem_t fullSlots, emptySlots;

void *randomizer (void *v) {
    for (int i = 0; i < 15; i++) {
        int val = rand () % 100 + 1;
        sem_wait (&emptySlots);                         // Wait till there are empty slots 
        pthread_mutex_lock (&lock);
        stackArray [topOfStacky++] = val; 
        pthread_mutex_unlock (&lock);
        sem_post (&fullSlots);                        // increase full slots 
        printf ("Randomizer Thread >> RAND generated %d << Done\n", val);
        fflush (stdin);
    }
    printf ("Completed producing ... Exit\n");
}
void *consumer (void *v) {
    for (int i = 0; i < 15; i++) {
        sem_wait (&fullSlots);                         // Wait till there are full slots 
        pthread_mutex_lock (&lock);
        int val = stackArray [--topOfStacky];
        stackArray [topOfStacky] = -1;
        pthread_mutex_unlock (&lock);
        sem_post (&emptySlots);                        // increase empty slots 
        printf ("CONSUME Thread >> RAND found %d << Done\n", val);
        fflush (stdin);
    }
    printf ("Completed consuming ... Exit\n");
}
int main()
{
    pthread_t randomThready, consumeThready;
    
    pthread_mutex_init (&lock, NULL);
    
    sem_init (&fullSlots, 0, 0);               // 0 slots full initially 
    sem_init (&emptySlots, 0, 5);              // 5 slots empty initially
    
    pthread_create (&randomThready, NULL, randomizer, NULL);
    pthread_create (&consumeThready, NULL, consumer, NULL);
    
    pthread_join (randomThready, NULL);
    pthread_join (consumeThready, NULL);

    pthread_mutex_destroy (&lock);
    
    sem_destroy (&fullSlots);
    
    sem_destroy (&emptySlots);
    return 0;
}