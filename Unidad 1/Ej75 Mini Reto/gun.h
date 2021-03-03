#ifndef GUN_H_
#define GUN_H_

typedef struct
{
    int size_cargador;
    int bullets;
} gun_t;

gun_t *arma_ctor(int size_cargador);
int balas_del_arma(gun_t* this);
void arma_dctor(gun_t *this);
void recargar(gun_t *this, int bullets);
void disparar(gun_t *this);

#endif // !GUN_H_
