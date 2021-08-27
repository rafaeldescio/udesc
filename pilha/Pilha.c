#include "Pilha_privado.h"


static const int init_size = 2;
static const int max_size = 16;

Stack *init(int element_size){
  LOG_D("Iniciando pilha vazia para %d elementos. Tamanho do elemento %d bytes. \n", init_size, element_size);
  Stack *s = malloc(sizeof(Stack));
  s->element_size = element_size;
  s->length = 0;
  s->capacity = init_size;
  s->storage = malloc(init_size * element_size);
  return s;
}

bool isFull(Stack *s) {
  return (s->length >= max_size);
}

bool isEmpty(Stack *s) {
  return (s->length == 0);
}

int size(Stack *s) {
  return s->length;
}

void *push(Stack *s, void *element) {
  if ( s == NULL || element == NULL) {
    LOG_D("Falha ao adicionar na pilha, verifique os parametros passados.\n");
    return NULL;
  }

  if (isFull(s)) {
    LOG_D("A pilha está cheia.\n");
    return NULL;
  }
  ++s->length;
  LOG_D("Adicionando um novo elemento. Capacidade atual: %d  \n", s->capacity);
  // Soma a contagem da pilha e verifica se não excedeu a capacidade, se não houver espaco, aumenta a capacidade
  if (s->capacity < s->length) {
    void *old_storage = s->storage; // Salva uma cópia, caso o realloc falhe
    LOG_D("Limite da pilha atingido. Dobrando a capacidade... \n");
    s->capacity *= 2; // Dobra o tamanho da pilha alocada
   
    if (((s)->storage = realloc(s->storage, s->capacity * s->element_size)) == NULL) {
      LOG_D("Falha ao aumentar a capacidade da pilha");
      free( old_storage );  // libera o bloco original
      exit(1);
    }
    LOG_D("Nova capacidade: %d  \n", s->capacity);
  }

  void *destAddr;
  // Verificar se deve fazer cast para CHAR --> (char *) s->storage + s->length * s->element_size;
  destAddr = s->storage + s->length * s->element_size;
  memcpy(destAddr, element, s->element_size);
 
  return element;
}

void* pop(Stack *s){
  void *element_address = top(s);
  LOG_D("Removendo o elemento do topo. \n");
  if (element_address == NULL) {
    return NULL;
  }
  s->length--;
  return element_address;
}

void *get(Stack *s, int position) {
  void *source = s->storage + position * s->element_size;
  void *element_address = malloc(s->element_size);
  memcpy(element_address, source, s->element_size);
  return element_address;
}

void *top(Stack * s) {
  if (s->length == 0) {
    return NULL;
  }
  return get(s, s->length);
}

void destroy(Stack * s) {
  free(s->storage);
  s->length = 0;
  s->capacity = 0;
}