#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "LDDE.h"
#include "pilha_publico.h"

#ifndef _FILA_PRIVADO_H
#define _FILA_PRIVADO_H

#define FAILURE 0
#define SUCCESS 1

// #define ENABLE_DEBUG_LOG 1   // disable DEBUG_LOG

typedef struct list_element * pElement;

struct list_element {
  // Conteudo do elemento armazenado
  void *element;
  size_t typesize;
  TypeName typename;
  pElement previous_element;
  pElement next_element;
};

struct List {
  // Elemento no inicio da lista.
  pElement head;
  // Elemento no fim da lista.
  pElement tail;
  // É o número de itens na lista.
  size_t size;
};

pElement newElement(void *val, pElement previous, pElement next,  size_t typesize, TypeName typename);
pElement peekElementAtPosition(pList s, size_t position);
void destroyElement(pElement el);

#endif