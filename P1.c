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
Sources: 
https://stackoverflow.com/questions/16254092/how-to-loop-user-input-and-copy-it-to-file-until-exit-string-in-entered-using
https://www.youtube.com/watch?v=17gp5DJEyiw&t=2s&ab_channel=Programiz
https://www.youtube.com/watch?v=qZ1oQLu7M5Y&ab_channel=Competer
https://www.tutorialspoint.com/cprogramming/c_while_loop.htm
https://psu.instructure.com/courses/2189855/discussion_topics/14618839?module_item_id=35303569
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
	//variable below for user's input message
	char message[4096];

	int shm_fd;
	void *ptr;
	
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

	//loops forever for some reason so we have a break statement later
	while (message!="end")
	{
	//Reset memory
    //memset(message, 0, 4096);

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	 
	 //Asks for user input of a word
	printf("enter line to be added to the Shared memory location:");
	scanf("%s", &message);
	
	//prints messages and a new line
	sprintf(ptr,"%s\n",message);
	ptr += strlen(message)+1;
	
	
	//breaks if the user types in end
   if (strcmp(message , "end") == 0 || strcmp(message , "end\n") == 0)
   break;
	
	}

	return 0;
}