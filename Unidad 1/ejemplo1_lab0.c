#include <stdio.h>
#include <unistd.h>
//
//Comentario
char saludo[10] = "hola mundo";
char nombre[50];
int main (){
    printf("Ingrese su nombre por favor\n");
    scanf("%s",nombre);
    printf("%s, acaba de compilar un %s \n",nombre, saludo);
}