#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
player_t *player_ctor(char name[20])
{
    player_t *p = malloc(sizeof(player_t));
    strcpy(p->name, name);
    printf("Hola %s\n", p->name);
    return p;
}

void player_dtor(player_t *this)
{
    free(this);
}

void recoger_arma(player_t *this, gun_t *gun)
{
    this->gun = gun;
    printf("Arma recogida satisfactoriamente \n");
}

void soltar_arma(player_t *this)
{
    arma_dctor(this->gun);
    printf("Ya perdio arma mi so\n");
}

