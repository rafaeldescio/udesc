#ifndef _ArLis_INTERFACE_H_
#define _ArLis_INTERFACE_H_

#define SUCESSO 1
#define FRACASSO 0

typedef struct ArLis *pArLis, **ppArLis;

int criaArLis(ppArLis pp, int tamInfo);
int destroiArLis(ppArLis pp);
int reiniciaArLis(pArLis p);
int insereArLis(pArLis p, void *novo, int (* cmp)(void *p1, void *p2));
int buscaArLis(pArLis p, void *item);
int removeArLis(pArLis p, void *item);
int buscaArLis(pArLis p, void *item);
int testaVaziaArLis(pArLis p);
int percursoArLis(pArLis pa, void (* processa)(void *p));

#endif
