#include <stdio.h>
#include <stdint.h>

uint8_t arrayCommon(int32_t *arr1, int32_t arr1Size, int32_t *arr2, int32_t arr2Size, int32_t *arrRes, int32_t arrResSize);

int main() {
    int32_t arr1Size, arr2Size;

    //PRIMER VECTOR
    printf("Tamaño primer vector");
    scanf("%d[^\n]", &arr1Size);
    getc(stdin);
    int32_t Array1[arr1Size];
    printf("Llenar vector con elementos: \n");
    for(int32_t i = 0; i<arr1Size; i++){
        printf("Elemento: %d \n", i);
        scanf("%d[^\n]", (Array1 + i));
        getc(stdin);
    }

    //SEGUNDO VECTOR
    printf("Ingrese tamaño segundo vector");
    scanf("%d[^\n]", &arr2Size);
    getc(stdin);
    int32_t Array2[arr2Size];
    printf("Elementos 2do vector: \n");
    for(int32_t i = 0; i<arr2Size; i++){
        scanf("%d[^\n]", (Array2 + i));
        getc(stdin);
    }

    //VECTOR RESULTADO
    int32_t arrRessize;
    if(arr1Size < arr2Size){
        arrRessize = arr1Size;
    }
    else{
        arrRessize = arr2Size;
    }
    int32_t ArrayResultado[arrRessize];
    uint8_t resultado = arrayCommon(Array1, arr1Size,Array2,arr2Size,ArrayResultado,arrRessize);
    printf("Se encontraron %d elementos en comun \n", resultado);
    printf("Arreglo de elementos comunes:\n ");
    for(int32_t i = 0; i<arrRessize;i++){
        printf("%d", *(ArrayResultado + i));
    }
    return 0;
}
uint8_t arrayCommon(int32_t *arr1, int32_t arr1Size, int32_t *arr2, int32_t arr2Size, int32_t *arrRes, int32_t arrResSize)
{
    uint8_t comunes = 0;
    int z;
    for(int32_t i = 0; i<arr1Size; i++){
        z=0;
        for(int32_t j = 0; j<arr2Size; j++){
            if(*(arr1+i) == *(arr2 + j)){
                z = 1;
                break;
            }
        }
        if(z == 1){
            for(int32_t j = 0; j<arrResSize; j++){
                if(*(arr1 + i) == *(arrRes + j))
                z==0;
                break;
            }
            if(z == 1){
                int32_t* PuntArray = arrRes;
                PuntArray += comunes;
                *PuntArray = *(arr1 + i);
                comunes++;
            }
        }
    }
    return comunes;
}