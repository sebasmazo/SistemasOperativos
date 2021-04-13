#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

typedef struct dato
{
    char nombre[20];
    char ocupacion[20];
    int edad;
} dato;
struct parametro
{
    dato *punterodato;
    int aux;
    char salida[20];
};
void inverso(void *params)
{
    struct parametro *p = (struct parametro *)params;
    dato auxlinea;
    FILE *OUT_FILE;
    for (int a = 0; a < (p[0].aux / 2); a++)
    {
        auxlinea = p[0].punterodato[a];
        p[0].punterodato[a] = p[0].punterodato[p[0].aux - 1 - a];
        p[0].punterodato[p[0].aux - 1 - a] = auxlinea;
    }

    OUT_FILE = fopen(p[0].salida, "w");

    for (int i = 0; i < p[0].aux; i++)
    {
        fprintf(OUT_FILE, "%s %s %d\n", p[0].punterodato[i].nombre, p[0].punterodato[i].ocupacion, p[0].punterodato[i].edad);
    }
    fclose(OUT_FILE);
}
void orden(void *params)
{
    struct parametro *x = (struct parametro *)params;
    dato auxlinea;
    FILE *OUT_FILE;

    for (int a = 0; a < x[0].aux - 1; a++)
    {
        for (int b = a + 1; b < x[0].aux; b++)
        {
            if (strcmp(x[0].punterodato[a].ocupacion, x[0].punterodato[b].ocupacion) > 0)
            {
                auxlinea = x[0].punterodato[a];
                x[0].punterodato[a] = x[0].punterodato[b];
                x[0].punterodato[b] = auxlinea;
            }
        }
    }
    OUT_FILE = fopen(x[0].salida, "w");

    for (int i = 0; i < x[0].aux; i++)
    {
        fprintf(OUT_FILE, "%s %s %d\n", x[0].punterodato[i].nombre, x[0].punterodato[i].ocupacion, x[0].punterodato[i].edad);
    }
    fclose(OUT_FILE);
}
int main(int argc, char const *argv[])
{
    int nrolineas = 0, edad1;
    char nombre1[20], ocupacion1[20];

    dato *veclineas;
    dato *veclineas2;

    FILE *IN_FILE;
    FILE *IN_FILE2;
    FILE *IN_FILE3;
    IN_FILE = fopen(argv[1], "r");
    if (IN_FILE == NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    while (fscanf(IN_FILE, "%s %s %d", nombre1, ocupacion1, &edad1) == 3)
    {
        nrolineas++;
    }
    veclineas = (dato *)malloc(sizeof(dato) * nrolineas);
    veclineas2 = (dato *)malloc(sizeof(dato) * nrolineas);
    rewind(IN_FILE);
    for (int i = 0; i < nrolineas; i++)
    {
        fscanf(IN_FILE, "%s %s %d ", nombre1, ocupacion1, &edad1);
        strcpy(veclineas[i].nombre, nombre1);
        strcpy(veclineas[i].ocupacion, ocupacion1);
        veclineas[i].edad = edad1;

        strcpy(veclineas2[i].nombre, nombre1);
        strcpy(veclineas2[i].ocupacion, ocupacion1);
        veclineas2[i].edad = edad1;
    }
    struct parametro hilo1param;
    struct parametro hilo2param;
    hilo1param.punterodato = veclineas;
    hilo1param.aux = nrolineas;
    strcpy(hilo1param.salida, argv[2]);
    hilo2param.punterodato = veclineas2;
    hilo2param.aux = nrolineas;
    strcpy(hilo2param.salida, argv[3]);

    pthread_t hilos_id1;
    pthread_t hilos_id2;
    pthread_create(&hilos_id1, NULL, (void *)inverso, &hilo1param);
    pthread_create(&hilos_id2, NULL, (void *)orden, &hilo2param);
    pthread_join(hilos_id1, NULL);
    pthread_join(hilos_id2, NULL);

    IN_FILE2 = fopen(argv[2], "r");
    if (IN_FILE2 == NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    nrolineas = 0;
    while (fscanf(IN_FILE2, "%s %s %d", nombre1, ocupacion1, &edad1) == 3){
        nrolineas++;
    }
    rewind(IN_FILE2);
    printf("----------HILO 1----------- \n");
    for(int i=0;i<nrolineas;i++){
        fscanf(IN_FILE2, "%s %s %d \n", nombre1, ocupacion1, &edad1);
        printf("%s %s %d\n", nombre1, ocupacion1, edad1);
    }
    IN_FILE3 = fopen(argv[3], "r");
    if (IN_FILE3 == NULL)
    {
        printf("Se ha producido un error al abrir el archivo");
        exit(8);
    }
    printf("----------HILO 2-----------\n");
    for (int i = 0; i < nrolineas; i++)
    {
        fscanf(IN_FILE3, "%s %s %d \n", nombre1, ocupacion1, &edad1);
        printf("%s %s %d\n", nombre1, ocupacion1, edad1);
    }
        return 0;
}
