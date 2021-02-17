#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE[40];
const char OUTPUT_FILE[40];

char (*pos1)[20];
float *pos2;
int *pos3;
float promedio = 0;
int matGan = 0;
int matPer = 0;
int totCreditos = 0;

char validarArchivo(FILE *);
char validarArchivo(FILE *archivo)
{
    char ch;
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    return ch;
}

int main(){
    int nMaterias = 0;
    char ch;
    //FLUJO DE ENTRADA ARCHIVOS
    printf("Ingrese el archivo de origen \n");
    scanf("%s", INPUT_FILE);
    printf("Ingrese el archivo de salida \n");
    scanf("%s", OUTPUT_FILE);
    FILE *in_file = fopen(INPUT_FILE, "r");
    FILE *on_file = fopen(OUTPUT_FILE, "w");
    
    char s1[20], s2[20], s3[20], m[20];

    if(in_file == NULL || on_file == NULL){
        printf("No se puede abrir un archivo");
        exit(EXIT_FAILURE);
    }

    fprintf(on_file,"Materia Nota Creditos\n");
    
    while (ch != EOF)
    {
        fscanf(in_file, "%s %s %s %s %s %s", s1, m, s2, m, s3, m);
        nMaterias++;
        ch = validarArchivo(in_file);
    }
    pos1 = (char(*)[20])malloc(sizeof(char[20]) * nMaterias); //Nombre materias
    pos2 = (float *)malloc(sizeof(float) * nMaterias); //Notas
    pos3 = (int *)malloc(sizeof(int) * nMaterias); //Creditos
    rewind(in_file);
    for (size_t i = 0; i < nMaterias; i++)
    {   
        fscanf(in_file,"%s %s %s %f %s %d ", s1, (char *)(pos1 + i), s2 , (float *)(pos2 + i), s3, (int *)(pos3 + i));
    }
    for (size_t i = 0; i < nMaterias; i++)
    {
        totCreditos += *(pos3 + i);
        promedio += *(pos2 + i);
    }
    fprintf(on_file, "Informacion materias \n");
    fprintf(on_file,"MATERIA | NOTA | CREDITOS \n");
    for(size_t i = 0; i<nMaterias; i++){
        fprintf(on_file," %s,  %1f, %d \n", (char *)(pos1 + i),  *(pos2 + i), *(pos3+i));
        if (*(pos2 + i) > 3.0){
            matGan += 1;
        }
        else{
            matPer += 1;
        }
    }
    fprintf(on_file, "Informacion general semestre \n");
    fprintf(on_file, "Total materias %d\nTotal ganadas %d\nTotal perdidas %d\n", nMaterias, matGan, matPer);
    fprintf(on_file, "Promedio: %f, Total de creditos: %d\n", promedio / nMaterias, totCreditos);
    
    printf("Creditos: %d \n" , totCreditos );
    printf("nMaterias: %d \n", nMaterias );
    free(pos1);
    free(pos2);
    free(pos3);
    return 0;
}
