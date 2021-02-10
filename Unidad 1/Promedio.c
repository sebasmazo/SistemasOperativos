#include <stdio.h>
#define long_arr 100
int array[long_arr];
int main(void){
    int i, promedio = 0 ;
    for(i=0;i<long_arr;i++){
        array[i] = i;
        promedio += array[i];
    }
    printf("Array[]: {");
    for(i=0;i<long_arr; i++){
        printf("array[%d]: %d}\n",i,array[i]);
    }
    printf("Suma total = %d ; Promedio = %d\n", promedio , promedio/long_arr);

}
