#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int min = atoi(argv[1]);
    for (int i = 2; i < argc; i++)
    {
        if(min>atoi(argv[i])){
            min = atoi(argv[i]);
        }
    }
    printf("Minimo: %d\n",min);
    
    return 0;
}
