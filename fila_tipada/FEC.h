
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

char* getTypeName(int t);

/* Insere um elemento no topo da fila. */
int enQueueDouble(Queue s, double element);
int enQueueLongDouble(Queue s, long double element);
int enQueueInt(Queue s, int element);
int enQueueUnsignedInt(Queue s, unsigned int element);
int enQueueUnsignedShortInt(Queue s, unsigned short int element);
int enQueueShortInt(Queue s, short int element);
int enQueueLongInt(Queue s, long int element);
int enQueueLongLongInt(Queue s, long long int element);
int enQueueUnsignedLongInt(Queue s, unsigned long int element);
int enQueueUnsignedLongLongInt(Queue s, unsigned long long int element);
int enQueueFloat(Queue s, float element);
int enQueueChar(Queue s, char element);
int enQueueSignedChar(Queue s, signed char element);
int enQueueUnsignedChar(Queue s, unsigned char element);
int enQueuePointerToChar(Queue s, char *element);
int enQueuePointerToVoid(Queue s, void* element);
int enQueuePointerToInt(Queue s, int* element);
int enQueueCustomStack(Queue s, pPilha element);
int enQueueInvalid(Queue s, void *X);

/* Remove um elemento do final da fila. */
int deQueueFloat(Queue s, float* a);
int deQueueDouble(Queue s, double* a);
int deQueueLongDouble(Queue s, long double* a );
int deQueueInt(Queue s, int* a);
int deQueueUnsignedInt(Queue s, unsigned int* a);
int deQueueShortInt(Queue s, short int* a);
int deQueueUnsignedShortInt(Queue s, unsigned short int* a);
int deQueueLongInt(Queue s, long int* a);
int deQueueLongLongInt(Queue s, long long int* a);
int deQueueUnsignedLongInt(Queue s, unsigned long int* a);
int deQueueUnsignedLongLongInt(Queue s, unsigned long long int* a);
int deQueueChar(Queue s, char* a);
int deQueueUnsignedChar(Queue s, unsigned char* a);
int deQueueSignedChar(Queue s, signed char* a);
int deQueuePointerToChar(Queue s, char** element);
int deQueuePointerToInt(Queue s, int** element);
int deQueuePointerToVoid(Queue s, void** element);
int deQueueCustomStack(Queue s, pPilha* element);
int deQueueInvalid(Queue s, void* a);

/* Insere um elemento no topo da fila. */
#define enQueue(q, X) _Generic((X),                    \
    double: enQueueDouble,                             \
    long double: enQueueLongDouble,                    \
    int: enQueueInt,                                   \
    unsigned int: enQueueUnsignedInt,                  \
    short int: enQueueShortInt,                        \
    unsigned short int: enQueueUnsignedShortInt,       \
    long int: enQueueLongInt,                          \
    unsigned long int: enQueueUnsignedLongInt,         \
    long long int: enQueueLongLongInt,                 \
    unsigned long long int: enQueueUnsignedLongLongInt,\
    float: enQueueFloat,                               \
    char: enQueueChar,                                 \
    signed char: enQueueSignedChar,                    \
    unsigned char: enQueueUnsignedChar,                \
    char *: enQueuePointerToChar,                      \
    void *: enQueuePointerToVoid,                      \
    int *: enQueuePointerToInt,                        \
    pPilha: enQueueCustomStack,                        \
    default: enQueueInvalid)(q, X)

/* Remove um elemento do final da fila. */
#define deQueue(q, Y) _Generic((Y),                     \
    double*: deQueueDouble,                             \
    long double*: deQueueLongDouble,                    \
    int*: deQueueInt,                                   \
    unsigned int*: deQueueUnsignedInt,                  \
    short int*: deQueueShortInt,                        \
    unsigned short int*: deQueueUnsignedShortInt,       \
    long int*: deQueueLongInt,                          \
    unsigned long int*: deQueueUnsignedLongInt,         \
    long long int*: deQueueLongLongInt,                 \
    unsigned long long int*: deQueueUnsignedLongLongInt,\
    float*: deQueueFloat,                               \
    char*: deQueueChar,                                 \
    signed char*: deQueueSignedChar,                    \
    unsigned char*: deQueueUnsignedChar,                \
    char **: deQueuePointerToChar,                      \
    int **: deQueuePointerToInt,                        \
    void **: deQueuePointerToVoid,                      \
    pPilha *: deQueueCustomStack,                       \
    default: deQueueInvalid)(q, Y)

#endif