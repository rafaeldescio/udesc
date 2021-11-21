#include <stdlib.h>
#include <stdio.h>
#define SUCESSO 1
#define FRACASSO 0


typedef struct LDSE *pLDSE, **ppLDSE;

int criaLDSE(ppLDSE pp, int tamanho_info);
int destroiLDSE(ppLDSE pp);
int reiniciaLDSE(pLDSE p);

int insereInicio(pLDSE p, void *elemento);
int insereFim(pLDSE p, void *elemento);
int inserePosicao(pLDSE p, int N, void *elemento);

int removeInicio(pLDSE p, void *elemento);
int removeFim(pLDSE p, void *elemento);
int removePosicao(pLDSE p, int N, void *elemento);

int buscaInicio(pLDSE p, void *elemento);
int buscaFim(pLDSE p, void *elemento);
int buscaPosicao(pLDSE p, int N, void *elemento);

int testaVazia(pLDSE p);
int contaElementos(pLDSE p);
void imprimeInt(pLDSE p);
void imprimeChar(pLDSE p);
void imprimeCharFilter(pLDSE p, int word_size, int filter);
void imprimeCharFilterFile(pLDSE p, int word_size, int filter, FILE* f);
int comparaLista2Palavra(pLDSE p, char *palavra);
int pegaContagemLista(pLDSE p, int* valor);
int pegaContagemPorPosicao(pLDSE p, int N, int* valor);