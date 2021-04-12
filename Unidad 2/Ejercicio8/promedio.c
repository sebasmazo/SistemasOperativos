#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int enteros[argc - 1];
    float promedio = 0;
    for (int i = 1; i < argc; i++)
    {
        enteros[i - 1] = atoi(argv[i]);
        promedio = enteros[i - 1] + promedio;
    }
    printf("Promedio: %f \n", promedio / (argc - 1)); //Promedio
    return 0;
}
