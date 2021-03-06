#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
typedef struct{
    char clave[20];
    int valor;
}dato;
int main(int argc, char const *argv[])
{
    int aux = 0, valor1, validacion;
    char clave1[20];
    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL)
    {
        printf("No se puede abrir %s\n", argv[1]);
        exit(8);
    }
    while (fscanf(in_file, "%s %d", clave1, &valor1) == 2) //Validar archivo para requisitos 
    {
        aux++;
        if(valor1>1000 || valor1 <-1000){
            validacion = 1;
            break;
        }
    }
    rewind(in_file);
    if(validacion ==1){
        printf("Dato en linea %d no cumple con los requisitos\n", aux);
        return 0;
    }
    if (aux<=100)
    {   
        FILE *on_file = fopen(argv[2],"w");
        dato *p_dato = (dato*)malloc(sizeof(dato)*aux);
        for (int i = 0; i < aux; i++)
        {
            fscanf(in_file,"%s %d",clave1, &valor1);
            strcpy(p_dato[i].clave, clave1);
            p_dato[i].valor = valor1;
        }
        quicksort(p_dato, 0, aux -1);
        for (int i = aux - 1; i >= 0; i--)
        {
            fprintf(on_file, "%s %d\n", p_dato[i].clave, p_dato[i].valor);
        }

        free(p_dato);
        fclose(on_file);
    }else{
        printf("Este archivo tiene más de 100 lineas");
    }
    fclose(in_file);
    return 0;
}
void quicksort(dato *array, int izquierda, int derecha) //Metodo de ordenacion
{
    if (izquierda < derecha)
    {
        int indiceParticion = particion(array, izquierda, derecha);
        quicksort(array, izquierda, indiceParticion);
        quicksort(array, indiceParticion + 1, derecha);
    }
}




void intercambiar(dato *a, dato *b)
{
    dato temporal = *a;
    *a = *b;
    *b = temporal;
}
int particion(dato *array, int izquierda, int derecha)
{
    dato pivote = array[izquierda];
    while (1)
    {
        while (array[izquierda].valor < pivote.valor)
        {
            izquierda++;
        }
        while (array[derecha].valor > pivote.valor)
        {
            derecha--;
        }
        if (izquierda >= derecha)
        {
            return derecha;
        }
        else
        {
            intercambiar(&array[izquierda], &array[derecha]);
            izquierda++;
            derecha--;
        }
    }
}