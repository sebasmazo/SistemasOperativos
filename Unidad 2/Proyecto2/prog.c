#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


typedef struct{
    char nombre[20];
    char ocupacion[20];
    int edad;
}dato;
typedef struct 
{
    int aux;
    FILE *on_file;
    dato *dato;
}parametro;
void quicksort();
int particion();
void InvertirOrden(void *parametros)
{
    parametro *x = (parametro *)parametros;
    for (int i = x->aux - 1; i >= 0; i--)
    {
        fprintf(x->on_file, "%s %s %d \n", x->dato[i].nombre, x->dato[i].ocupacion, x->dato[i].edad);
    }
    fclose(x->on_file);
    return NULL;
}


int main(int argc, char const *argv[]) //HILO 1: ORDEN INVERSO, HILO 2: ORDEN ALFABETICO
{
    char nombre1[20],ocupacion1[20];
    int aux=0, edad1;
    pthread_t hilo1, hilo2;
    parametro p1,p2;
    FILE *in_file = fopen(argv[1],"r");
    if (in_file == NULL)
    {
        printf("No se puede abrir %s\n", argv[1]);
        exit(8);
    }
    while (fscanf(in_file,"%s %s %d", nombre1, ocupacion1, &edad1) == 3)
    {
        aux++;
        if (edad1<0)
        {
            printf("Edad invalida \n");
            return 0;
        }
    }
    if(aux>100){
        printf("Nro de lineas invalido");
        return 0;
    }
    rewind(in_file);
    dato *pdato = (dato *)malloc(sizeof(dato) * aux);
    FILE *on_file1 = fopen(argv[2], "r");
    FILE *on_file2 = fopen(argv[3], "r");
    for (int i = 0; i < aux; i++)
    {
        fscanf(in_file,"%s %s %d", nombre1,ocupacion1,&edad1);
        strcpy(pdato[i].nombre,nombre1);
        strcpy(pdato[i].ocupacion,ocupacion1);
        pdato[i].edad = edad1;
    }
    printf("Estructura \n");
    for (int i = 0; i < aux; i++)
    {
        printf("%s %s %d \n", pdato[i].nombre ,pdato[i].ocupacion, pdato[i].edad);
    }
    printf("\n");
    p1.on_file = on_file1;
    p1.aux = aux;
    p1.dato = pdato;

    p2.on_file = on_file2;
    p2.aux = aux;
    p2.dato = (dato *)malloc(sizeof(dato)*aux);
    for (int i = 0; i < aux; i++)
    {
        p2.dato[i] = pdato[i];
    }
    
    pthread_create(&hilo1,NULL,(void *)InvertirOrden,&p1);
    printf("Hilo 1 Creado \n");
    pthread_create(&hilo2, NULL, (void *)InvertirOrden, &p2);
    printf("Hilo 2 Creado \n");
    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);
    
    on_file1 = fopen(argv[2],"r");
    if (on_file1 == NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    printf("Hilo 1: \n");
    for (int i = 0; i < aux; i++)
    {
        fscanf(on_file1, "%s %s %d", nombre1,ocupacion1,&edad1);
        printf("%s %s %d \n",nombre1,ocupacion1,edad1);
    }
    on_file2 = fopen(argv[3], "r");
    printf("Salida del hilo 2\n");
    for (int i = 0; i < aux; i++)
    {
        fscanf(on_file2, "%s %s %d", nombre1, ocupacion1, &edad1);
        printf("%s %s %d\n", nombre1, ocupacion1, edad1);
    }
    fclose(in_file);
    fclose(on_file1);
    fclose(on_file2);
    free(pdato);
    free(p2.dato);
    return 0;
}

    