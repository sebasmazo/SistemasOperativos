#ifndef PLAYER_H_
#define PLAYER_H_
#include "gun.h"

typedef struct
{
    char name[20];
    gun_t *gun;
} player_t;

player_t *player_ctor(char name[20]);
void player_dtor(player_t *this);
void recoger_arma(player_t *this, gun_t *gun);
void soltar_arma(player_t *this);


#endif