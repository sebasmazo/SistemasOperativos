#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int enteros[argc-1], min;
    float promedio = 0;
    for (int i = 1; i < argc; i++)
    {
        enteros[i-1] = atoi(argv[i]);
        promedio = enteros[i-1] + promedio;
    }
    printf("%f \n", promedio/(argc-1) ); //Promedio
    for (int i = 0; i < enteros.; i++)
    {
        min = enteros[i]
    }
    
}
