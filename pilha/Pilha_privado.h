#include "Pilha_publico.h"
#ifndef _PILHA_PRIVADO_H
#define _PILHA_PRIVADO_H
// #define ENABLE_DEBUG_LOG    // disable DEBUG_LOG

struct stack {
  // Índice do elemento do topo da pilha.
  size_t length;
  // É o conteúdo da pilha.
  void *storage;
  // É o tamanho de cada elemento da pilha em bytes. Passado no init.
  size_t element_size;
  // É a quantidade de itens alocados na pilha.
  size_t capacity;
  // É o número máximo de itens na pilha. Passado no init.
  int max_elements;
};

/* Retorna um ponteiro para o elemento da posicão sem remover ele da pilha. */
void *get(struct stack *s, int position);

#endif
