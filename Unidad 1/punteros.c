#include <stdio.h>
#include <unistd.h>
int main(){

    printf("Hola mundo");
    int var1 = 11;
    int var2 = 12;
    int *pvar1, *pvar2;
    pvar1 = &var1;
    pvar2 = &var2;
    printf("%s,%d\n ","\nValor puntero:" , *pvar1);
}