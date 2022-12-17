#include<stdio.h>

void Print_Binary(unsigned int Value);

int main(){
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
}


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