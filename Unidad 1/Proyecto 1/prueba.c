#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int cedula;
    char nombre[30];
    int semestre;
} estudiante;

typedef struct
{
    char nombre[30];
    int numRegistros;
    int size;
    estudiante *registro;
} bdActual;

char checkOf(FILE *archivo)
{ //Obra de Manguito uwu
    char ch;
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    return ch;
}

bdActual bd;
bdActual *pbd = &bd;

int main(void)
{
    char comando[10];
    char par1[30];
    int par2;
    int par3;
    do
    {
        printf("Ingrese el comando:\n");
        scanf("%s", comando);
        if (strcmp(comando, "mkdb") == 0)
        {
            fscanf(stdin, "%s %d", par1, &par2);
            mkdb(par1, par2);
            printf("Se contruyo con exito la BD %s\n", par1);
        }
        else if (strcmp(comando, "loaddb") == 0)
        {
            fscanf(stdin, "%s", par1);
            FILE *in_file = fopen(par1, "r");
            if (in_file == NULL)
                printf("No se puede abrir %s\n", par1);
            else
            {
                loaddb(in_file);
                fclose(in_file);
            }
        }
        else if (strcmp(comando, "savedb") == 0)
        {
            fscanf(stdin, "%s", par1);
            FILE *on_file = fopen(par1, "w+");
            if (on_file == NULL)
                printf("No se puede abrir %s\n", par1);
            else
            {
                savedb(on_file);
                fclose(on_file);
            }
        }
        else if (strcmp(comando, "readall") == 0)
        {
            readall();
        }
        else if (strcmp(comando, "readsize") == 0)
        {
            readsize();
        }
        else if (strcmp(comando, "mkreg") == 0)
        {
            fscanf(stdin, "%d %s %d", &par2, par1, &par3);
            mkreg(par2, par1, par3);
        }
        else if (strcmp(comando, "readreg") == 0)
        {
            fscanf(stdin, "%d", &par2);
            readreg(par2);
        }
        getc(stdin);

    } while (strcmp(comando, "exit") != 0);
    printf("Quiere salvar la BD? (Con el comando)\n");
    scanf("%s", comando);

    if (strcmp(comando, "savedb") == 0)
    {
        fscanf(stdin, "%s", par1);
        FILE *on_file = fopen(par1, "w+");
        if (on_file == NULL)
            printf("No se puede abrir %s\n", par1);
        else
        {
            savedb(on_file);
            fclose(on_file);
        }
    }
    getc(stdin);
    free(pbd->registro);
    free(pbd);
    return 0;
}

void mkdb(char name[30], int size)
{
    strcpy(pbd->nombre, name);
    pbd->numRegistros = size;
    pbd->registro = (estudiante *)malloc(sizeof(estudiante) * size);
    pbd->size = 0;
}

void loaddb(FILE *in_file)
{
    char ch;
    char name[30], people[30];
    int size, ced, sem, actual;
    fscanf(in_file, "%s %d %d", name, &size, &actual);

    strcpy(pbd->nombre, name);
    pbd->numRegistros = size;
    pbd->size = actual;
    pbd->registro = (estudiante *)malloc(sizeof(estudiante) * size);
    for (int i = 0; i < pbd->size; i++)
    {
        fscanf(in_file, "%d %s %d", &ced, people, &sem);
        pbd->registro[i].cedula = ced;
        strcpy(pbd->registro[i].nombre, people);
        pbd->registro[i].semestre = sem;
    }
    printf("Se cargo con exito la BD %s\n", pbd->nombre);
}

void savedb(FILE *on_file)
{
    fprintf(on_file, "%s %d %d\n", pbd->nombre, pbd->numRegistros, pbd->size);
    for (int i = 0; i < pbd->size; i++)
    {
        fprintf(on_file, "%d %s %d\n", pbd->registro[i].cedula, pbd->registro[i].nombre, pbd->registro[i].semestre);
    }
    printf("Se guardo correctamente la BD\n");
}

void mkreg(int ced, char nombre[30], int semestre)
{
    if (pbd->size == pbd->numRegistros)
    {
        printf("La base de datos ya esta en su capacidad total\n");
        return;
    }
    for (int i = 0; i < pbd->size; i++)
    {
        if (pbd->registro[i].cedula == ced)
        {
            printf("Ya hay un registro con este numero de cedula\n");
            return;
        }
    }

    int i = pbd->size;
    pbd->registro[i].cedula = ced;
    strcpy(pbd->registro[i].nombre, nombre);
    pbd->registro[i].semestre = semestre;
    pbd->size = ++i;
    printf("Se registro correctamente la informacion\n");
}

void readall()
{
    printf("Base de datos: %s\n", pbd->nombre);
    for (int i = 0; i < pbd->size; i++)
    {
        printf("%d %s %d\n", pbd->registro[i].cedula, pbd->registro[i].nombre, pbd->registro[i].semestre);
    }
}

void readsize()
{
    printf("Base de datos: %s, numero de registros: %d\n", pbd->nombre, pbd->size);
}

void readreg(int par2)
{
    for (int i = 0; i < pbd->size; i++)
    {
        if (pbd->registro[i].cedula == par2)
        {
            printf("%d %s %d\n", pbd->registro[i].cedula, pbd->registro[i].nombre, pbd->registro[i].semestre);
            return;
        }
    }
    printf("No se encontro el registro\n");
}