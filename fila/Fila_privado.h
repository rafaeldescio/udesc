#include "Fila_publico.h"
#ifndef _FILA_PRIVADO_H
#define _FILA_PRIVADO_H
// #define ENABLE_DEBUG_LOG    // disable DEBUG_LOG
struct queue_element {
  // Conteudo do elemento armazenado
  void *element;
  size_t element_size;
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
void privateEnQueue(Queue s,  void *element, size_t element_size);
#endif
