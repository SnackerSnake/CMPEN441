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
*  PSU Email  : dah5825
*  Assignment : M5 Lab Producer and Consumer (Shared Memory)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main()
{
	const int SIZE = 4096;
	char *name = "OS";
	//char *message= "";
	char message[4096];

	int shm_fd;
	void *ptr;
	
	while (message!="end")
	{
	//Reset memory
    //memset(message, 0, 4096);
    printf("After:");
	printf(message);
	printf("\n");

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	 
	printf("enter line to be added to the Shared memory location:");
	scanf("%s", &message);
	
	printf("Before:");
	printf(message);
	printf("\n");
	 
	sprintf(ptr,"%s\n",message);
	ptr += strlen(message)+1;
	
	
	
   if (strcmp(message , "end") == 0 || strcmp(message , "end\n") == 0)
   break;
	
	}

	return 0;
}