#include <stdio.h>
#include <unistd.h>

int main(void){
    double operando1,operando2;
    char operacion;
    
    do{
        printf("\nIngrese el operando 1\n");
        scanf("%lf", &operando1);
        printf("Ingrese el operando 2 \n");
        scanf("%lf", &operando2);

        
        printf("Ingrese la operacion que desea hacer (+,-,*), q si desea salir del programa\n");
        scanf("%s", &operacion);

        switch (operacion)
        {
        case '+':
            printf("%f + %f = %f", operando1, operando2, operando1 + operando2);
            break;
        case '-':
            printf("%f - %f = %f", operando1, operando2, operando1 - operando2);
            break;
        case '*':
            printf("%f * %f = %f", operando1, operando2, operando1 * operando2);
            break;
        case 'q':
            break;

        default:
            printf("Opcion incorrecta");
            break;
        }
    }while(operacion != 'q');
        
    
    printf("Fin programa");
    
}