#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    char clave[20];
    int valor,aux=0;
    __pid_t hijo1,hijo2;
    if(argc == 4){
        printf("Proceso principal %d\n",(int)getpid());
        for (int i = 1; i <3; i++){
            if(i==1){
                hijo1 = fork();
                if(hijo1==0){
                    printf("Proceso hijo %d nro: %d \n", (int)getpid(),i);
                    execv("./p1",argv);
                }
                
            }if(i==2){
                hijo2=fork();
                if (hijo2 == 0)
                {
                    printf("Proceso hijo %d %d \n", (int)getpid(), i);
                    execv("./p2", argv);
                }
                
            }
        }
        wait(NULL);
        wait(NULL);
    }else{
        printf("Faltan argumentos para ejecutar el programa");
        return 0;
    }
    FILE *in_file = fopen(argv[1], "r");
    FILE *in_file1 = fopen(argv[2], "r");
    FILE *in_file2 = fopen(argv[3], "r");
    if (in_file1 == NULL || in_file2 == NULL)
    {
        printf("No se puede abrir %s o %s\n", argv[2], argv[3]);
        exit(8);
    }
    while (fscanf(in_file, "%s %d", clave, &valor) == 2)
    {
        aux++;
    }
    
    printf("\nArchivo generado por p1\n");
    for (int i = 0; i < aux; i++)
    {
        fscanf(in_file1, "%s %d", clave, &valor);
        printf("%s %d\n", clave, valor);
    }
    printf("\nArchivo generado por p2\n");
    for (int i = 0; i < aux; i++)
    {
        fscanf(in_file2, "%s %d", clave, &valor);
        printf("%s %d\n", clave, valor);
    }
    printf("%d",aux);
    fclose(in_file1);
    fclose(in_file2);
    return 0;
}