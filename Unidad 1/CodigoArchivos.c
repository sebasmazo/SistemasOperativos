#include <stdio.h>
#include <stdlib.h>

char ArchivoOrigen[40];
char ArchivoDestino[40];

int main(void){
    FILE *orgFile;
    FILE *desFile;
    int ch;
    
    printf("Nombre archivo origen: ");
    scanf("%s", ArchivoOrigen);
    printf("Nombre archivo destino: ");
    scanf("%s", ArchivoDestino);

    orgFile = fopen(ArchivoOrigen, "r");
    if(orgFile == NULL){
        printf("Archivo no encontrado");
        exit(EXIT_FAILURE);
    }
    desFile = fopen(ArchivoDestino, "w");
    if(desFile == NULL){
        printf("Archivo destino no encontrado");
        exit(EXIT_FAILURE);
    }
    while (!feof(orgFile))
    {
        ch = fgetc(orgFile);
        if(ch != EOF){
            fputc(ch,desFile);
        }
    }
    fclose(orgFile);
    fclose(desFile);
    return 0;
    
}