
#if __STDC__ != 1 || __STDC_VERSION__ < 201112L
#error "Versão do compilador não suporta _Generic"
#endif
#include "pilha_publico.h"
#ifndef _FILA_PUBLICO_H
#define _FILA_PUBLICO_H

typedef struct queue *Queue;

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

/* Retorna um ponteiro para o elemento proximo elemento sem remover ele da fila. */
void *peek(Queue s, size_t position);

int nextQueueType(Queue s);

/* Desaloca a memoria que foi alocada para a fila. */
void destroyQueue(Queue s);

enum t_typename {
    TYPENAME_UNSIGNED_CHAR,
    TYPENAME_CHAR,
    TYPENAME_SIGNED_CHAR,
    TYPENAME_SHORT_INT,
    TYPENAME_UNSIGNED_SHORT_INT,
    TYPENAME_INT,
    TYPENAME_UNSIGNED_INT,
    TYPENAME_LONG_INT,
    TYPENAME_UNSIGNED_LONG_INT,
    TYPENAME_LONG_LONG_INT,
    TYPENAME_UNSIGNED_LONG_LONG_INT,
    TYPENAME_FLOAT,
    TYPENAME_DOUBLE,
    TYPENAME_LONG_DOUBLE,
    TYPENAME_POINTER_TO_CHAR,
    TYPENAME_POINTER_TO_VOID,
    TYPENAME_POINTER_TO_INT,
    TYPENAME_CUSTOM_STACK,
    TYPENAME_UNKNOWN
};
typedef enum t_typename TypeName ;

#define TYPE_NAME(X) _Generic((X),                           \
    unsigned char: TYPENAME_UNSIGNED_CHAR,                   \
    char: TYPENAME_CHAR,                                     \
    signed char: TYPENAME_SIGNED_CHAR,                       \
    short int: TYPENAME_SHORT_INT,                           \
    unsigned short int: TYPENAME_UNSIGNED_SHORT_INT,         \
    int: TYPENAME_INT,                                       \
    unsigned int: TYPENAME_UNSIGNED_INT,                     \
    long int: TYPENAME_LONG_INT,                             \
    unsigned long int: TYPENAME_LONG_INT,                    \
    long long int : TYPENAME_LONG_LONG_INT,                  \
    unsigned long long int : TYPENAME_UNSIGNED_LONG_LONG_INT,\
    float: TYPENAME_FLOAT,                                   \
    double: TYPENAME_DOUBLE,                                 \
    long double: TYPENAME_LONG_DOUBLE,                       \
    char *: TYPENAME_POINTER_TO_CHAR,                        \
    void *: TYPENAME_POINTER_TO_VOID,                        \
    int *: TYPENAME_POINTER_TO_INT,                          \
    pPilha: TYPENAME_CUSTOM_STACK,                           \
    default: TYPENAME_UNKNOWN)


int enQueueOriginal(Queue s, void *element, size_t element_size, TypeName typename);
int deQueueOriginal(Queue s, void* return_element, TypeName typename);
#define enQueue(q, X) \
({ \
    typeof(X) y = X; \
    enQueueOriginal(q, &y, sizeof(X), TYPE_NAME(X)); \
})

/* Remove um elemento do final da fila. */
#define deQueue(q, Y) deQueueOriginal(q, Y, TYPE_NAME(*Y))

#endif