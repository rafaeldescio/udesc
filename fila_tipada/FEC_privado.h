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

int _destroyNextElement(Queue s);
void _destroyCustom(Queue s );

#endif