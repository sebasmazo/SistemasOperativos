#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    __pid_t hijo1, hijo2, hijo3;
    printf("Proceso principal: %d\n",(int)getpid());

    for (int i = 0; i <4; i++)
    {
        if(i==1){
            hijo1 = fork();
            if (hijo1==0)
            {
                execv("./promedio",argv);
            }
        }
        if (i == 2)
        {
            hijo2 = fork();
            if (hijo2 == 0)
            {
                execv("./max", argv);
            }
        }
        if (i == 3)
        {
            hijo3 = fork();
            if (hijo3 == 0)
            {
                execv("./min", argv);
            }
        }
    }
    
    return 0;
}
