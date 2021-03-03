#include "gun.h"
#include <stdlib.h>
#include <stdio.h>

gun_t *arma_ctor(int size_cargador)
{
    gun_t *g = malloc(sizeof(gun_t));
    g->bullets = 0;
    return g;
}

void arma_dctor(gun_t *this)
{
    free(this);
}
int balas_del_arma(gun_t *this){
    return this->bullets;
}
void recargar(gun_t *this, int bullets)
{
    if (bullets < 0 || bullets+this->bullets<=this->size_cargador)
    {
        printf("No se puede recargar este numero de balas\n");
        return;
    }
    this->bullets = this->bullets + bullets;
}

void disparar(gun_t *this)
{
    if (this->bullets == 0)
    {
        printf("No tiene balas\n");
        return;
    }
    this->bullets = this->bullets - 1;
    printf("Disparo realizado, balas restantes: %d\n", this->bullets);
    
}
