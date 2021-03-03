#include <stdio.h>
#include <stdlib.h>
#include "gun.h"
#include "player.h"

char name_player[20];

int main(int argc, char *argv[])
{
    player_t *player = player_ctor("Mazapo");
    gun_t* gun = arma_ctor(10);
    recoger_arma(player,gun);
    recargar(gun,10);
    for (int i = 0; i < 10; i++) //Disparar 10 veces
    {
        disparar(gun);
    }
    disparar(gun); //Disparar sin balas
    soltar_arma(player);
    player_dtor(player);
    
}
