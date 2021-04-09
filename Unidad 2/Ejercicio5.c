#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int enteros[argc-1], min, max;
    float promedio = 0;
    for (int i = 1; i < argc; i++)
    {
        enteros[i-1] = atoi(argv[i]);
        promedio = enteros[i-1] + promedio;
    }
    printf("%f \n", promedio/(argc-1) ); //Promedio
    min = enteros[0];
    max = enteros[0];
    for (int i = 1; i < argc-1; i++)
    {
        if(min > enteros[i]){
            min = enteros[i];
        }else if (max< enteros[i])
        {
            max = enteros[i];
        }
    }
    printf("Minimo: %d", min);
    printf("Maximo: %d \n", max);
}
