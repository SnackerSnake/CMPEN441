#include<stdio.h>

#define TOTALBLOCK 64 /*it is how many blocks we are allowed to ask for – here just 64*/

static char Mem[TOTALBLOCK]; /*memory from where code allocate space we consider it as memory of Size 128KB.*/
static unsigned long bit_field = 0; /*this bit-field keep the record of allocated blocks*/

int* Mallocate(int x) {/*function that allocate space  here x is in KB*/

    if (x > 128) /*for memory greater than 128 KB */
    {
        perror("\nb_alloc error: block size is larger \n");
        return NULL;
    }

    int number_of_unit = (x + 1) / 2;                       /*number of units in X KB, here we assume each unit of 2 KB*/
    unsigned long mask = 0x1;                               /* mask represent the required continupus memory space*/
    for (long i = 1; i < number_of_unit; i++)
    {
        mask = mask << (long)1;
        mask |= 1;
    }

    for (long i = 0; i <= TOTALBLOCK - number_of_unit; i++) /*search the bit-field for available space*/
    {

        if ((bit_field & (mask << i)) == 0)
        {
            bit_field |= (mask << i);//set
            //printf("\nb_alloc index = %ld\n", i);         /* debug */
            return  (int*)(&Mem[i]);                  /* return the address  */
        }

    }
    perror("\nb_alloc error: no sufficient  block space\n");
    return NULL;
}

void Free(int x, int size)                              /* function that deallocate space from memory here 'x' is starting address and 'size' is the Size of space in KB  */
{
    int index = (int)(((char*)x - Mem));          /* address difference indicate index of unit in memory  */
    
    //check wheather correct addresss has been sent
    if (index >= 0 && index <= 64)   /*  address difference would be in 0<=  <=64*/
    {

        int no_of_units = (size + 1) / 2;                   /* number of units to dealloacte */
        unsigned long mask = (0x1 << index);
        for (unsigned long i = 0; i < no_of_units; i++)
            bit_field &= ~(mask << i);                        /* dealloacte each units */

    }
    else {
        perror("\nb_dealloc error: no such block index exist\n");

    }
}

int main()
{
    printf("%u\n", Mallocate(4));  // allocate 4 KB of space in Memory
    printf("%u\n", Mallocate(2));
    printf("%u\n", Mallocate(4));
    // Free(6295650, 3);     //  '6295650' this is just an example  change it according to Mallocate()
    return 0;
}