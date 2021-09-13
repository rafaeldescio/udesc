#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef _FILA_PUBLICO_H
#define _FILA_PUBLICO_H

typedef struct queue * Queue;

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
void enQueue(Queue s, void *element, size_t element_size);

/* Remove um elemento do final da fila. */
/* Retorna um ponteiro para o elemento removido */
void *deQueue(Queue s);

/* Retorna um ponteiro para o elemento proximo elemento sem remover ele da fila. */
void *peek(Queue s, size_t position);

/* Desaloca a memoria que foi alocada para a fila. */
void destroyQueue(Queue s);

/* Imprime os elementos um a um, usando a funcao passada que recebe como parametro a posicao e um ponteiro pra o elemento. */
void printQueue(void (*f)(int, void*), Queue s);

#endif