#ifndef _ArLisEx_INTERFACE_H_
#define _ArLisEx_INTERFACE_H_

#define SUCESSO 1
#define FRACASSO 0

typedef struct ArLis *pArLis, **ppArLis;

int insereArLisBal(pArLis p, void *novo, int (* cmp)(void *p1, void *p2));
int removeArLisBal(pArLis p, void *item);
int percursoArLisBal(pArLis pa, void (* processa)(void *p));
#endif
