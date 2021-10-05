#include "Fila_publico.h"
#include "pilha_publico.h"
#include <stdbool.h>
#if __STDC__!=1 || __STDC_VERSION__ < 201112L
#error "Versão do compilador não suporta _Generic"
#endif
#ifndef _FILA_PRIVADO_H
#define _FILA_PRIVADO_H

#define FAILURE 0
#define SUCCESS 1
enum t_typename {
    TYPENAME_BOOL,
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
    TYPENAME_POINTER_TO_LONG,
    TYPENAME_POINTER_TO_VOID,
    TYPENAME_POINTER_TO_INT,
    TYPENAME_CUSTOM_STACK,
    TYPENAME_UNKNOWN
};

// #define ENABLE_DEBUG_LOG    // disable DEBUG_LOG
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

/* Adiciona um novo elemento na fila. */
int enQueueOriginal(Queue s, void *element, size_t element_size, TypeName typename);

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
    pPilha: TYPENAME_CUSTOM_STACK,                          \
    default: TYPENAME_UNKNOWN)

int enQueueDouble(Queue s, double element);
int enQueueInt(Queue s, int element);
int enQueueChar(Queue s, char element);
int enQueueCharVector(Queue s, char *element);
int enQueuePPilha(Queue s, pPilha element);
int enQueueInvalid(Queue s, void *X);

#define privateEnQueue(q, X) _Generic((X),             \
    double: enQueueDouble,                             \
    int: enQueueInt,                                   \
    char: enQueueChar,                                 \
    char *: enQueueCharVector,                         \
    pPilha: enQueuePPilha,                             \
    default: enQueueInvalid)(q, X)

int deQueueOriginal(Queue s, void* return_element);
int deQueueInvalid(Queue s, char* a);
double deQueueDouble(Queue s, double a);
int deQueueInt(Queue s, int a);
char deQueueChar(Queue s, char a);
char* deQueueCharVector(Queue s, char* element);
int _privateDeQueue(Queue s);
void* __privateDeQueueTyped(Queue s, TypeName t);

#endif