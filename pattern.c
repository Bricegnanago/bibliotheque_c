#include<stdio.h>
#include <stdlib.h>
#define LEN 10
int main(int argc, char const *argv[])
{

    for(int i = 0; i < LEN-5; i++){
        for(int i = 0; i < LEN-5; i++){
            printf("\t");
        }
        
        for(int i = 0; i < LEN+10; i++){
            printf("*");
        }
        printf("\n");
    }
    
    return 0;
}