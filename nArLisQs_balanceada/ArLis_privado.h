#ifndef _ArLis_PRIVADO_H_
#define _ArLis_PRIVADO_H_

#include "ArLis.h"
#include "ArLisEx.h"
#include "libs/LDSE.h"
#include "libs/LDSEEx.h"
#include <stdio.h>

typedef struct CounterArLis{
    int insere;
    int remove;
    int percorre;
    int buscaNivel;
    int contagemLista;
    int indexInsere;
    int indexRemove;
    int indexPercorre;
    int indexBuscaNivel;
    int* arrayInsere;
    int* arrayRemove;
    int* arrayPercorre;
    int* arrayBuscaNivel;
    int sizeArrayInsere;
    int sizeArrayRemove;
    int sizeArrayPercorre;
    int sizeArrayBuscaNivel;
} CounterArLis;

typedef struct NoArLis{
    //void *dados;
    pLDSE lista;
    struct NoArLis *pai;
    struct NoArLis *esquerda;
    struct NoArLis *centro;
    struct NoArLis *direita;
    struct CounterArLis *contador;
}NoArLis;


typedef struct ArLis{
    int tamInfo;
    struct NoArLis *raiz;
    pLDSE bufLista;
    struct CounterArLis *contador;
}ArLis;

typedef struct NoArLis *pNoArLis, **ppNoArLis;
int insere_recursivo(NoArLis *no, NoArLis *novo, int (* cmp)(void *p1, void *p2));
int remove_recursivo(NoArLis *no, void *item);
void percorreArLis(NoArLis *pa, void (* processa)(void *p));
int buscaPalArLis(NoArLis *pa, void *item);
void apagaNo(NoArLis *p);

#endif
