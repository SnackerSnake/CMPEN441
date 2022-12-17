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
*  Assignment : M9 Lab: Bitmaps
References: https://discover.cs.ucsb.edu/commonerrors/error/2018.xml
*/

#include <stdio.h>
#include <stdlib.h>

#define TOTALBLOCK 64 //Amount of blocks we can ask for

static char Mem[TOTALBLOCK]; //Memory of size 128KB; space allocated
static unsigned long bit_field = 0; 

int* Mallocate(int x) {

    if (x > 128) //If greater than 128 KB
    {
        perror("\nb_alloc error: block size is larger \n");
        return ((void *)0);
    }

    int numberOfUnit = (x + 1) / 2;                      
    unsigned long mask = 0x1;                               
    for (long index = 1; index < numberOfUnit; index++)
    {
        mask = mask << (long)1;
        mask |= 1;
    }

    for (long index = 0; index <= TOTALBLOCK - numberOfUnit; index++) 
    {

        if ((bit_field & (mask << index)) == 0)
        {
            bit_field |= (mask << index);
            
            return  (int*)(&Mem[index]);      //Allocate the units           
        }

    }
    perror("\nb_alloc error: no sufficient  block space\n");
    return ((void *)0);
}

void Free(int address, int size)                              
{
    int index = (int)(((char*)address - Mem));          
    
    //Check if the correct addresss has been sent.
    if (index >= 0 && index <= 64)  
    {

        int no_of_units = (size + 1) / 2;                   
        unsigned long mask = (0x1 << index);
        for (unsigned long jindex = 0; jindex < no_of_units; jindex++)
            bit_field &= ~(mask << jindex);                            //Disallocate the units   

    }
    else {
        perror("\nb_dealloc error: no such block index exist\n");

    }
}

//Convert int to binary and print it.
void Print_Binary(unsigned int Value){
    
    int i;
    unsigned int Mask = 1;
    
    Mask = Mask << 31;
    
    for(i=0; i<32; i++){
        
        if((Mask & Value) == 0){
            printf("0");
        }else{
            printf("1");
        }
        Mask = Mask >> 1;
    }
    printf("\n");
}

int main()
{
    int firstPrint = Mallocate(4); // Allocate 4 KB of space in Memory
    printf("%u\n", firstPrint);  
    Print_Binary(firstPrint);
    
    Free(6295648, 4); //FREEDOM
    
    int secondPrint = Mallocate(2);
    printf("%u\n", secondPrint);
    Print_Binary(secondPrint);
    
    Free(6295651, 2);
    
    int thirdPrint = Mallocate(4);
    printf("%u\n", thirdPrint);
    Print_Binary(thirdPrint);
    
    Free(6295651, 3); 
    
    int fourthPrint = Mallocate(4);
    printf("%u\n", fourthPrint);
    Print_Binary(fourthPrint);
    
    printf("\n");
    printf("Actual code done. Rest is test code for binary because the instructions said to include it.");
    printf("\n");
    
    
    // This function is only to showcase how to use the Print_Binary function. 
    //Test cases to show case how to use.
    unsigned int x = 0xFFFFFFFF;
    Print_Binary(x);
    
    x =0 ;
    Print_Binary(x);
    
    printf("\n");
    
    x=0xFFFF0000;
    Print_Binary(x);
    
    printf("\n");
        
    x=0x0000FFFF;
    Print_Binary(x);
    
    printf("\n");
    
    x=0xFF00FF00;
    Print_Binary(x);
    
    printf("\n");
    
    x=0x00FF00FF;
    Print_Binary(x);
    
    printf("\n");
        
    x=0xF0F0F0F0;
    Print_Binary(x);
    return 0;
}