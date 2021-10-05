#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#if __STDC__ != 1 || __STDC_VERSION__ < 201112L
#error "Versão do compilador não suporta _Generic"
#endif

#ifndef _FILA_PUBLICO_H
#define _FILA_PUBLICO_H

typedef struct queue *Queue;
typedef enum t_typename TypeName ;

/* Inicializa a fila */
/* Recebe o tamanho da fila como parametro. */
Queue initQueue(size_t max_elements);

/* Verifica se a fila está vazia. */
/* Retorna um true se estive vazia. */
bool isEmptyQueue(Queue s);

/* Verifica se a fila está cheia */
/* Retorna um true se estive cheia. */
bool isFullQueue(Queue s);

/* Retorna a capacidade da fila. */
int sizeQueue(Queue s);

/* Insere um elemento no topo da fila. */
#define enQueue(q, X) privateEnQueue(q, X)


/* Remove um elemento do final da fila. */
#define deQueue(q) _privateDeQueue(q)
#define deQueueTyped(q, t) __privateDeQueueTyped(q, t)
/* Desaloca a memoria que foi alocada para a fila. */
#define deQueueAndGet(q, t) deQueueOriginal(q, t)

/* Retorna um ponteiro para o elemento proximo elemento sem remover ele da fila. */
void *peek(Queue s, size_t position);

TypeName nextQueueType(Queue s);
/* Desaloca a memoria que foi alocada para a fila. */
void destroyQueue(Queue s);

char* getTypeName(TypeName t);
#endif