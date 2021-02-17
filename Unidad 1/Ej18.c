#include <stdio.h>

void PrintArr(char *, int);

int main(){
    int pos1, pos2;
    printf("Ingrese longitud del arreglo \n" );
    scanf("%d[^\n]", &pos1);
    getc(stdin);
    char array [pos1];
    for(int i = 0; i<pos1; i++){
        printf("Ingrese dato en la posicion %d \n");
        scanf("%d[^\n]", (array+i));
        getc(stdin);
    }
    PrintArr(array,pos1);


    //Editar arreglo
    printf("Ingrese la posicion que quiere cambiar");
    scanf("%d[^\n], &pos2");
    getc(stdin);
    if(pos2 >= 1 && pos2<=pos1){
        printf("Valor: \n");
        scanf("%c",(array+pos2-1) );
        getc(stdin);
        PrintArr(array,pos1);
    }else{
        printf("Posicion invalida \n");
    }
    return 0;
}
void PrintArr(char * array, int pos){
    for (int i = 0; i < pos; i++)
    {
        printf("%c  ", *(array+i));
    }
    printf("\n");
    
}