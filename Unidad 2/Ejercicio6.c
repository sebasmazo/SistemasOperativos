#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    __pid_t hijo;
    int factorial = 1;
    
    printf("Proceso padre: %d \n", (int)getpid());
    for (int i = 0; i < 3; i++)
    {
        hijo = fork();
        if(hijo==0){
            printf("Hijo %d",i);
            break;
        }
    }
    if(hijo == 0){
        printf("Proceso: %d \n", (int)getpid());
        for (int i = 1; i <= 10; i++)
        {
            factorial = factorial*i;
            printf("Factorial(%d) == %d \n",i,factorial);
        }
        wait(NULL);
        wait(NULL);
        wait(NULL);
    }
    
}