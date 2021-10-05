/* TDAPilha_publico.h */

typedef struct PE *pPilha, **ppPilha;

int criapilha(ppPilha pp, int tamanhoVetor, int tamanhoInfo);
int destroipilha(ppPilha pp);

int empilha(pPilha p, void *elemento);
int desempilha(pPilha p, void *elemento);

int reiniciapilha(pPilha p);
int topo(pPilha p, void *topo);



