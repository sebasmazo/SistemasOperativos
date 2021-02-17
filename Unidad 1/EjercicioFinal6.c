/*
Realice un programa que permita calcular
el promedio ponderado obtenido por un
estudiante en el semestre, considerando:
1.El programa debe solicitar el número de
materias vistas en el semestre.
2.Debe preguntar el nombre de la materia.
3.Debe preguntar la nota obtenida.
4.Debe solicitar el número de créditos.
5.Al final, debe mostrar una tabla con
tantas filas como materias y con 3
columnas indicando el nombre de la
materia, la nota y el número de créditos.
6.También debe reportar el promedio
ponderado.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void LlenarDatosMaterias();
void ImprimirDatosMaterias();
void CalcularPromedio();
void LiberarMemoria();
char (*memoriaMaterias)[30]; //Array de punteros
char stringBuf[30];
double *bufferNotas; //Puntero Notas
int *bufferCreditos; //Puntero Creditos
int nro_materias, nota_obtenida, nro_creditos, contador_materias, promedio_ponderado;
double promedio;
int main()
{
    printf("Ingrese el numero de materias que ve por semestre");
    scanf("%d", &nro_materias);
    getc(stdin);
    memoriaMaterias = (char(*)[30])malloc(sizeof(char[30]) * nro_materias);
    bufferNotas = (double *)malloc(sizeof(double) * nro_materias);
    bufferCreditos = (int *)malloc(sizeof(int) * nro_materias);
    LlenarDatosMaterias();
    printf("oe");
}
void LlenarDatosMaterias()
{
    for (contador_materias = 0; contador_materias < nro_materias; contador_materias++)
    {
        printf("Ingrese el nombre de la materia nro %d \n", contador_materias);
        gets((char *)(memoriaMaterias + contador_materias));
        printf("Ingrese la nota de la materia nro %d \n", contador_materias);
        scanf("%lf", (double *)(bufferNotas + contador_materias));
        getc(stdin);
        printf("Nro de creditos de la materia nro %d \n", contador_materias);
        scanf("%d", (int *)(bufferCreditos + contador_materias));
        getc(stdin);
    }
    ImprimirDatosMaterias();
    CalcularPromedio();
    LiberarMemoria();
}
void ImprimirDatosMaterias()
{
    printf("|Nombre |Nota         |Creditos| \n");
    for (contador_materias = 0; contador_materias < nro_materias; contador_materias++)
    {
        printf("|%7.7s|%4.11f|%8d| \n", (char *)(memoriaMaterias + contador_materias), *(bufferNotas + contador_materias), *(bufferCreditos + contador_materias));
    }
}
void CalcularPromedio()
{
    promedio_ponderado = 0;
    nro_creditos = 0;
    for (contador_materias = 0; contador_materias < nro_materias; contador_materias++)
    {
        promedio_ponderado += (*(bufferNotas + contador_materias)) * (*(bufferCreditos + contador_materias));
        nro_creditos += *(bufferCreditos + contador_materias);
    }
    printf("Promedio = %d \n", promedio_ponderado/nro_creditos); 
}
void LiberarMemoria()
{
    free(memoriaMaterias);
    free(bufferNotas);
    free(bufferCreditos);
}
