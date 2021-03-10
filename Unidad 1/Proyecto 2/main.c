#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Atributos globales
char comando[10];
char aux1[30];
int aux2,aux3;
//Estructuras, Clases
typedef struct{
    int Cedula;
    char Nombre[30];
    int Semestre;
}estudiante;
typedef struct 
{
    char nombre[30];
    int nroreg;
    int size;
    estudiante *reg;
} DataBase;
typedef struct 
{
    DataBase *bdaux;
    DataBase *bdactual;
    int size;
    int valiterator;
} ListaBaseDeDatos;

//Funciones lista
ListaBaseDeDatos * listaprincipal;
void LiberarMemoria(){
    for (int j = 0; j < listaprincipal->size; j++)
    {
        free(listaprincipal->bdactual[j].reg);
    }
    free(listaprincipal ->bdactual);
    
    
}
ListaBaseDeDatos * ListaCtor(){
    ListaBaseDeDatos *lista1 = malloc(sizeof(ListaBaseDeDatos));
    lista1->bdaux = (DataBase*) malloc(sizeof(DataBase)*30);
    lista1->bdactual = malloc(sizeof(DataBase));
    lista1 -> size = 0;
    lista1->valiterator = 0;
    return lista1;
}
int main(void)  //REHACER
{
    listaprincipal = ListaCtor();
    char comando[10];
    char aux1[30];
    int aux2;
    int aux3;
    do
    {
        printf("Ingrese el comando:\n");
        scanf("%s", comando);

        if (strcmp(comando, "mdb") == 0)
        {
            fscanf(stdin, "%s %d", aux1, &aux2);
            mdb(aux1, aux2);
        }
        else if (strcmp(comando, "ldb") == 0)
        {
            fscanf(stdin, "%s", aux1);
            FILE *in_file = fopen(aux1, "r");
            if (in_file == NULL)
                printf("No se puede abrir %s\n", aux1);
            else
            {
                ldb(in_file);
                fclose(in_file);
            }
        }
        else if (strcmp(comando, "lsdbs") == 0)
        {
            lsdbs();
        }
        else if (strcmp(comando, "sdb") == 0)
        {
            fscanf(stdin, "%s", aux1);
            sdb(aux1);
        }
        else if (strcmp(comando, "gdb") == 0)
        {
            gdb();
        }
        else if (strcmp(comando, "svdb") == 0)
        {
            svdb();
        }
        else if (strcmp(comando, "radb") == 0)
        {
            radb();
        }
        else if (strcmp(comando, "rsdb") == 0)
        {
            rsdb();
        }
        else if (strcmp(comando, "mreg") == 0)
        {
            fscanf(stdin, "%d %s %d", &aux2, aux1, &aux3);
            mreg(aux2, aux1, aux3);
        }
        else if (strcmp(comando, "rr") == 0)
        {
            fscanf(stdin, "%d", &aux2);
            rr(aux2);
        }
        getc(stdin);

    } while (strcmp(comando, "exit") != 0);
    if (listaprincipal->valiterator == 1)
    {
        printf("BD Activa: %s. ¿Quiere salvar la BD? (SI o NO)\n", listaprincipal->bdaux->nombre);
        scanf("%s", comando);
        if (strcmp(comando, "SI") == 0)
            svdb();
    }
    LiberarMemoria();
}

void FuncDisponibles()
{
    printf("Lista de funciones disponibles: \n -mdb nombre tamaño \n -ldb nombre \n -lsdbs nombre \n -gdb \n -sdb nombre \n -svdb  \n -radb \n -rsdb \n -mreg Cedula Nombre Semestre \n -rr cedula \n -exit \n");
}
//Funciones comportamiento programa
void mdb(char nombredb[40],int size){
    for (int i = 0; i < listaprincipal->size; i++)
    {
        if(strcmp(listaprincipal->bdactual[i].nombre,nombredb) == 0){
            printf("BD ya existente");
            return;
        }
    }
    strcpy(listaprincipal ->bdactual[listaprincipal->size].nombre,nombredb);
    listaprincipal ->bdactual[listaprincipal->size].nroreg = size;
    listaprincipal ->bdactual[listaprincipal->size].reg = (estudiante *)malloc(sizeof(estudiante)*size);
    listaprincipal ->bdactual[listaprincipal->size].size=0;
    listaprincipal ->size = listaprincipal -> size+1;
    printf("DataBase creada exitosamente \n");
}
void ldb(FILE *in_file){
    char nombre[30], nombreestudiante[30];
    int cedula,semestre,size,sizedblist;
    fscanf(in_file, "%s %d %d", nombre, &size, &sizedblist);
    if (strcmp(nombre, "") == 0 || size == 0 )
    {
        printf("no se pudo crear la BD \n");
        return;
    }
    strcpy(listaprincipal -> bdactual[listaprincipal->size].nombre, nombre);
    listaprincipal ->bdactual[listaprincipal->size].nroreg = size;
    listaprincipal ->bdactual[listaprincipal->size].size = sizedblist;
    listaprincipal -> bdactual[listaprincipal ->size].reg = (estudiante *)malloc(sizeof(estudiante)*size);
    for (int i = 0; i < listaprincipal ->bdactual[listaprincipal -> size].size; i++)
    {
        fscanf(in_file,"%d %s %d", &cedula, &nombreestudiante, &semestre);
        listaprincipal ->bdactual[listaprincipal->size].reg[i].Cedula = cedula;
        strcpy(listaprincipal->bdactual[listaprincipal->size].reg[i].Nombre,nombreestudiante);
        listaprincipal->bdactual[listaprincipal->size].reg[i].Semestre = semestre;
    }
    printf("Base de datos cargada exitosamente \n");
    listaprincipal ->size = listaprincipal->size+1;
}
void lsdbs(){
    printf("Bases de datos disponibles: %d \n", listaprincipal->size);
    for (int i = 0; i < listaprincipal->size; i++)
    {
        printf("DataBase actual: %s , Tamaño: %d , Registros: %d \n",listaprincipal->bdactual[i].nombre,listaprincipal->bdactual[i].nroreg,listaprincipal->bdactual[i].size);
    }
}
void sdb(char name[30]){
    for (int i = 0; i < listaprincipal->size; i++)
    {
        if(strcmp(listaprincipal->bdactual[i].nombre,name)==0){
            listaprincipal->bdaux = listaprincipal->bdactual +i;
            listaprincipal->valiterator=1;
        }
    }
    if(listaprincipal->valiterator!=1){
        printf("DataBase no existente \n");
    }
}
void gdb(){
    if(listaprincipal->valiterator!=1){
        printf("Primero seleccione una database\n");
        return;
    }
    printf("DataBase activa; Nombre: %s, Tamaño: %d, Reg disponibles: %d \n", listaprincipal->bdaux->nombre, listaprincipal->bdaux->nroreg,(listaprincipal->bdaux->nroreg - listaprincipal->bdactual->size));
}
void svdb(){    //Error
    if(listaprincipal->valiterator != 1){
        printf("Primero seleccione una database\n");
        return;
    }
    char output_name[30];
    strcpy(output_name,listaprincipal->bdaux->nombre);
    FILE *on_file = fopen(strcat(output_name,".txt"),"w+");
    if(on_file == NULL){
        printf("Error al abrir archivo %s\n",output_name);
        return;
    }
    fprintf(on_file,"%s %d %d \n",listaprincipal->bdaux->nombre, listaprincipal->bdaux->nroreg,listaprincipal->bdaux->size);
    for (int i = 0; i <listaprincipal->bdaux->size; i++)
    {
        fprintf(on_file, "%d %s %d\n", listaprincipal->bdaux->reg[i].Cedula, listaprincipal->bdaux->reg[i].Nombre, listaprincipal->bdaux->reg[i].Semestre);
        printf("DataBase guardada exitosamente \n");
    }
    
}
void radb(){
    if (listaprincipal->valiterator != 1)
    {
        printf("Primero seleccione una database\n");
        return;
    }
    for (int i = 0; i < listaprincipal->bdaux->size; i++)
    {
        printf("%d %s %d \n", listaprincipal->bdaux->reg[i].Cedula, listaprincipal->bdaux->reg[i].Nombre, listaprincipal->bdaux->reg[i].Semestre);
    }
}
void rsdb(){
    if (listaprincipal->valiterator != 1)
    {
        printf("Primero seleccione una database\n");
        return;
    }
    printf("DataBase: %s, Reg actuales: %d\n", listaprincipal->bdaux->nombre,listaprincipal->bdaux->size);
}
void mreg(int cedula, char nombre[30], int semestre){   //Error
    if (listaprincipal->valiterator != 1)
    {
        printf("Primero seleccione una database\n");
        return;
    }
    if(listaprincipal->bdaux->size == listaprincipal->bdaux->nroreg){
        printf("Base de datos llena \n");
        return;
    }
    for (int i = 0; i < listaprincipal->bdaux->size; i++)
    {
        if(listaprincipal->bdaux->reg[i].Cedula == cedula){
            printf("Cedula ya existente \n");
        }
    }
    int x = listaprincipal->bdaux->size;
    listaprincipal->bdactual->reg[x].Cedula = cedula;
    strcpy(listaprincipal->bdaux->reg[x].Nombre,nombre );
    listaprincipal->bdaux->reg[x].Semestre=semestre;
    listaprincipal ->bdaux->size= ++x;
    printf("Informacion registrada \n");
}
void rr(int paramCedula){
    if (listaprincipal->valiterator != 1)
    {
        printf("Primero seleccione una database\n");
        return;
    }
    for (int i = 0; i < listaprincipal->bdaux->size; i++)
    {
        if(listaprincipal->bdaux->reg[i].Cedula == paramCedula){
            printf(" %d %s %d \n", listaprincipal->bdaux->reg[i].Cedula, listaprincipal->bdaux->reg[i].Nombre, listaprincipal->bdaux->reg[i].Semestre);
            return;
        }
    }
    printf("Registro no encontrado");
    
}