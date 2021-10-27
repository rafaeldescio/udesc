
#ifndef _ABB_PUBLICO_H
#define _ABB_PUBLICO_H

typedef struct bsTree *pABB, **ppABB;


/* Inicializa a arvore */
int criaABB(ppABB p, size_t element_size);

/* Desaloca a memoria que foi alocada para a arvore. */
int destroiABB(ppABB s);

/* Desaloca a memoria que foi alocada para a arvore e inicia uma nova */
int reiniciaABB(pABB s);

/* Insere um novo elemento na arvore */
int insereABB(pABB s, void *element, int (*compareFunc)(void*, void*));

/* Remove um elemento da arvore */
int removeABB(pABB s, void* delete_element, int (*compareFunc)(void*, void*));

/* Busca um elemento na arvore */
int buscaABB(pABB s, void* find_element, int (*compareFunc)(void*, void*));

/* Verifica se a arvore está vazia. */
int testaVaziaABB(pABB s);


int percursoEmOrdem(pABB s, void (*printFunc)(void*));

int percursoPreOrdem(pABB s, void (*printFunc)(void*));

int percursoPosOrdem(pABB s, void (*printFunc)(void*));

#endif