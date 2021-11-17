#ifndef _ArLis_PRIVADO_H_
#define _ArLis_PRIVADO_H_

#include "ArLis.h"
#include "ArLisEx.h"
#include "libs/LDSE.h"
#include "libs/LDSEEx.h"
#include <stdio.h>

typedef struct NoArLis{
    //void *dados;
    pLDSE lista;
    struct NoArLis *pai;
    struct NoArLis *esquerda;
    struct NoArLis *centro;
    struct NoArLis *direita;
}NoArLis;


typedef struct ArLis{
    int tamInfo;
    struct NoArLis *raiz;
    pLDSE bufLista;
}ArLis;

typedef struct NoArLis *pNoArLis, **ppNoArLis;
int insere_recursivo(NoArLis *no, NoArLis *novo, int (* cmp)(void *p1, void *p2));
int remove_recursivo(NoArLis *no, void *item);
void percorreArLis(NoArLis *pa, void (* processa)(void *p));
int buscaPalArLis(NoArLis *pa, void *item);
void apagaNo(NoArLis *p);

#endif
