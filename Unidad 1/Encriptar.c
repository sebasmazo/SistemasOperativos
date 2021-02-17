#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE[40];
const char OUTPUT_FILE[40];

//Funciones para encriptar
void NOT(FILE *IN_FILE, FILE *OUT_FILE)
{

    int ch;
    while (1)
    {
        ch = fgetc(IN_FILE);
        if (ch == EOF)
        {
            break;
        }
        ch = ~ch;
        fputc(ch, OUT_FILE);
    }
}
void XOR(FILE *IN_FILE, FILE *OUT_FILE)
{

    int ch;
    while (1)
    {
        ch = fgetc(IN_FILE);
        if (ch == EOF)
        {
            break;
        }
        ch = ch ^ 0xFF;
        fputc(ch, OUT_FILE);
    }
}

int main(){
    int opcion;
    printf("Ingrese el archivo de origen \n");
    scanf("%s", INPUT_FILE);
    printf("Ingrese el archivo de salida \n");
    scanf("%s", OUTPUT_FILE);
    FILE *in_file = fopen(INPUT_FILE, "r");
    FILE *on_file = fopen(OUTPUT_FILE, "w");
    if (in_file == NULL || on_file == NULL)
    {
        printf("No se puede abrir un archivo");
        exit(EXIT_FAILURE);
    }
    printf("Desea encriptar por XOR (1) o NOT(2)");
    scanf("%d", &opcion);
    if(opcion == 1){
        XOR(in_file, on_file);
    }else{
        NOT(in_file, on_file);
    }
}




