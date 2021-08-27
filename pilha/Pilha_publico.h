#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Stack {
  int length;
  void *storage;
  int element_size;
  int capacity;
} Stack;

/* Inicializa a pilha */
/* Recebe o tamanho de cada elemento como parametro. */
Stack* init(int element_size);

/* Verifica se a pilha está vazia. */
/* Retorna um true se estive vazia. */
bool isEmpty(Stack *s);

/* Verifica se a pilha está cheia */
/* Retorna um true se estive cheia. */
bool isFull(Stack *s);

/* Retorna o número de elementos na pilha. */
int size(Stack *s);

/* Insere um elemento no topo da pilha. */
/* Retorna um ponteiro para o elemento se inserido, NULL caso contrário. */
void* push(Stack *s, void *elem);

/* Remove um elemento do topo da pilha. */
/* Retorna um ponteiro para o elemento removido */
void* pop(Stack *s);

/* Retorna um ponteiro para o elemento no topo sem remover ele da pilha. */
void* top(Stack *s);

/* Desaloca a memoria que foi alocada para a pilha. */
void destroy(Stack *s);