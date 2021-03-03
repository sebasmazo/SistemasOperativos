#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void mkdb(char name[30], int size);
void FuncDisponibles();
void loaddb(FILE *in_file);
void savedb(FILE *On_File);
void mkreg(int ced, char nombre[30], int semestre);
void readall();
void readreg(int param);
void readsize(); 
typedef struct
{
    int cedula;
    char nombre[30];
    int semestre;
} estudiante;
typedef struct
{
    char nombre[30];
    int nroreg;
    int size;
    estudiante *registro;
} DataBase;


DataBase bd;
DataBase *pbd = &bd;

int main(void)
{
    char comando[10];
    int paramnum;
    char paramstr[30];
    int par3;
    
    printf("Bienvenido al CRUD de la base de datos\n");
    FuncDisponibles();
    do
    {
        printf("Ingrese la funcion que desea usar\n");
        scanf("%s", comando);
        
        if (strcmp(comando,"mkdb") == 0)
        {
            fscanf(stdin, "%s %d", paramstr,&paramnum);
            mkdb(paramstr,paramnum);
            printf("DBA Construida\n");
        }else if (strcmp(comando,"loaddb")== 0)
        {
            fscanf(stdin, "%s", paramstr);
            FILE *Inp_File = fopen(paramstr, "r");
            if(Inp_File == NULL){
                printf("No se puede arbrir el archivo\n");
            }else{
                loaddb(Inp_File);
                fclose(Inp_File);
            }
        }else if (strcmp(comando,"savedb")== 0)
        {
            fscanf(stdin,"%s", paramstr);
            FILE *Out_File = fopen(paramstr, "w+");
            if(Out_File == NULL){
                printf("No se puede abrir la DBA\n");
            }
            savedb(Out_File);
            fclose(Out_File);
        }else if (strcmp(comando,"readall")== 0)
        {
            readall();
        }else if (strcmp(comando,"readsize")== 0)
        {
            readsize();
        }else if (strcmp(comando,"mkreg")== 0)
        {
            fscanf(stdin, "%d %s %d", &paramnum, paramstr, &par3);
            mkreg(paramnum,paramstr,par3);
        }else if (strcmp(comando,"readreg"))
        {
            fscanf(stdin, "%d", &paramnum);
            readreg(paramnum);
        }
        

    }while (strcmp(comando, "exit") != 0);
    
}
void FuncDisponibles(){
    printf("Lista de funciones disponibles: \n -mkdb nombre tamaño \n -loaddb nombre \n -savedb nombre \n -readall \n -readsize \n -mkreg cedula nombre semestre \n -readreg cedula \n -exit \n");
}

void mkdb(char name[30], int size){
    strcpy(pbd ->nombre, name);
    pbd->nroreg = size;
    pbd->registro = (estudiante *)malloc(sizeof(estudiante)*size);
    pbd->size = 0;
}
void loaddb(FILE *in_file){
    char ch;
    char name[30], people[30];
    int size,ced,sem,actual;
    fscanf(in_file, "%s %d %d", name, &size, &actual);
    strcpy(pbd->nombre,name);
    pbd->nroreg = size;
    pbd ->registro= (estudiante*)malloc(sizeof(estudiante)*size);
    for (int i=0; i<pbd->size;i++)
    {
        fscanf(in_file, "%d %s %d", &ced, people, &sem);
        pbd->registro[i].cedula = ced;
        strcpy(pbd -> registro[i].nombre,people);
        pbd->registro[i].semestre = sem;
    }
    printf("Se cargo satisfactoriamente la base de datos \n");
}
void savedb(FILE *On_File){
    fprintf(On_File, "%s %d %d\n", pbd->nombre,pbd->nroreg,pbd->size);
    for(int i=0; i<pbd->size;i++){
        fprintf(On_File, "%d %s %d\n",pbd ->registro[i].cedula,pbd->registro[i].nombre,pbd->registro[i].semestre);
    }
    printf("Se guardo la DataBase\n");
}
void mkreg(int ced, char nombre[30],int semestre){
    if(pbd->size ==pbd->nroreg){
        printf("La base de datos esta llena\n");
        return;
    }
    for (int i = 0; i < pbd->size; i++)
    {
        if(pbd->registro[i].cedula == ced){
            printf("La cedula ya se encuentra registrada\n");
            return;
        }
    }
    int i = pbd->size;
    pbd -> registro[i].cedula = ced;
    strcpy(pbd->registro[i].nombre,nombre);
    pbd->registro[i].semestre = semestre;
    pbd->size=++i;
    printf("Informacion registrada.\n");
}
void readall(){
    for (int i = 0; i < pbd->size; i++)
    {
        printf("%d %s %d\n", pbd->registro[i].cedula,pbd->registro[i].nombre,pbd->registro[i].semestre);
    }
}
void readsize(){
    printf("numero de registros: %d\n", pbd->size);
}
void readreg(int param){

    for (int i = 0; i < pbd->size; i++)
    {
        if(pbd ->registro[i].cedula == param){
            printf("%d %s %d\n", pbd->registro[i].cedula,pbd->registro[i].nombre,pbd->registro[i].semestre);
            return;
        }
    }
    printf("Cedula no encontrada\n");
}
