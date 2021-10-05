#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "FEC.h"
#include "pilha_publico.h"

#ifndef _FILA_PRIVADO_H
#define _FILA_PRIVADO_H

#define FAILURE 0
#define SUCCESS 1

// #define ENABLE_DEBUG_LOG 1   // disable DEBUG_LOG

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


struct queue_element {
  // Conteudo do elemento armazenado
  void *element;
  size_t typesize;
  TypeName typename;
};

typedef struct queue_element * QueueElement;
typedef struct queue * Queue;
struct queue {
  // Índice do elemento no inicio da fila.
  size_t front;
  // Índice do elemento no fim da fila.
  size_t rear;
  // É o número máximo de itens na fila. Passado no init.
  size_t max_elements;
  // É o conteúdo da fila.
  QueueElement *storage;

};

int enQueueOriginal(Queue s, void *element, size_t element_size, TypeName typename);
int deQueueOriginal(Queue s, void* return_element, TypeName typename);
int _destroyNextElement(Queue s);
void _destroyCustom(Queue s );

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


#endif