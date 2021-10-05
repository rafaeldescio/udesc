#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
// Verifica se o compilador é compativel
#if __STDC__ != 1 || __STDC_VERSION__ < 201112L
#error "Versão do compilador não suporta _Generic"
#endif
#include "pilha_publico.h"

// #define ENABLE_DEBUG_LOG 1 // habilitar o debug

#ifndef _LIST_PUBLICO_H
#define _LIST_PUBLICO_H

typedef struct List *pList, **ppList;

// -------------------------------------------------------------------------------------------------------------------
// TYPE
// -------------------------------------------------------------------------------------------------------------------

typedef enum t_typename TypeName ;
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
    TYPENAME_CUSTOM_STRUCT, // Elemento customizado da aplicacao.c, adicionado tambem no TYPE_ENUM
    TYPENAME_UNKNOWN
};

#define TYPE_NUM(X) _Generic((X),                            \
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
    pTestStruct: TYPENAME_CUSTOM_STRUCT,                     \
    default: TYPENAME_UNKNOWN)

// -------------------------------------------------------------------------------------------------------------------
// LIST METHODS
// -------------------------------------------------------------------------------------------------------------------

/* Inicializa a lista */
int initList(ppList l);

/* Desaloca a memoria que foi alocada para a lista. */
int destroyList(ppList l);

/* Reinicia a lista */
int resetList(ppList l);

/* Verifica se a lista está vazia. */
/* Retorna um true se estive vazia. */
bool isEmptyList(pList l);

/* Retorna a tamanho da lista. */
int sizeList(pList l);

// -------------------------------------------------------------------------------------------------------------------
// PEEK
// -------------------------------------------------------------------------------------------------------------------

int peekListPosition(pList s, size_t position, void *element, TypeName typename);
int peekListTail(pList s, void *element, TypeName typename);
int peekListHead(pList s, void *element, TypeName typename);

/* Retorna um ponteiro para o proximo elemento sem remover ele da lista. */
#define peekAtList(q, p, X) peekListPosition(q, p, X, TYPE_NUM(*X))

/* Retorna um ponteiro para o ultimo elemento sem remover ele da lista. */
#define peekLastList(q, X) peekListTail(q, X, TYPE_NUM(*X))

/* Retorna um ponteiro para o ultimo elemento sem remover ele da lista. */
#define peekFirstList(q, X) peekListHead(q, X, TYPE_NUM(*X))

// -------------------------------------------------------------------------------------------------------------------
// ADD
// -------------------------------------------------------------------------------------------------------------------

int addListPosition(pList s, size_t position, void* element,  size_t typesize, TypeName t);
int addListTail(pList s, void *element, size_t typesize, TypeName typename);
int addListHead(pList s, void *element, size_t typesize, TypeName typename);


/* Insere um elemento no fim da lista. */
#define pushList(q, X) \
({ \
    typeof(X) y = X; \
    addListTail(q, &y, sizeof(X), TYPE_NUM(X)); \
})

/* Insere um elemento no inicio da lista. */

#define unshiftList(q, X) \
({ \
    typeof(X) y = X; \
    addListHead(q, &y, sizeof(X), TYPE_NUM(X)); \
})

/* Insere um elemento da lista na posicao passada. */
#define addAtList(q, p, X)\
({ \
    typeof(X) y = X; \
    addListPosition(q, p, &y, sizeof(X), TYPE_NUM(X)); \
})

// -------------------------------------------------------------------------------------------------------------------
// REMOVE
// -------------------------------------------------------------------------------------------------------------------

int removeListPosition(pList s, size_t position, void* a, TypeName t);
int removeListHead(pList s, void* a, TypeName t);
int removeListTail(pList s, void* a, TypeName t);

/* Remove um elemento do inicio da lista. */
#define shiftList(q, Y) removeListHead(q, Y, TYPE_NUM(*Y))

/* Remove um elemento do inicio da lista. */
#define popList(q, Y) removeListTail(q, Y, TYPE_NUM(*Y))

/* Remove um elemento da lista na posicao passada. */
#define removeAtList(q, p, Y) removeListPosition(q, p, Y, TYPE_NUM(*Y))

// -------------------------------------------------------------------------------------------------------------------
// PRINT
// -------------------------------------------------------------------------------------------------------------------
void printList(pList s, void (* print)(void *e, TypeName t, size_t p));
void printListReverse(pList s, void (* print)(void *e, TypeName t, size_t p));

// -------------------------------------------------------------------------------------------------------------------
// Extra
// -------------------------------------------------------------------------------------------------------------------

int getTypeAtList(pList s, size_t position);

#endif