#include "Pilha_privado.h"

#ifdef ENABLE_DEBUG_LOG
#define LOG_D(fmt, args...) \
  {                           \
    printf("D:");             \
    fprintf(stdout, fmt, ##args);        \
  }
#else
#define LOG_D(fmt, args...) // faz nada
#endif

static const size_t init_size = 2;

Stack init(size_t element_size, int max_elements){
  LOG_D("Iniciando pilha vazia para %zu elementos. Tamanho do elemento %zu bytes. \n", init_size, element_size);
  Stack s = malloc(sizeof(struct stack));
  s->element_size = element_size;
  s->length = 0;
  s->max_elements = max_elements;
  s->capacity = init_size;
  s->storage = malloc(init_size * element_size);
  return s;
}

bool isFull(Stack s) {
  return (s->length >= s->max_elements);
}

bool isEmpty(Stack s) {
  return (s->length == 0);
}

int size(Stack s) {
  return s->length;
}

void push(Stack s, void *element) {
  // Verifica se os parâmetros estão vazios. Retorna um erro caso esteja.
  if ( s == NULL || element == NULL) {
    LOG_D("Falha ao adicionar na pilha, verifique os parametros passados.\n");
    return ;
  }

  // Valida se a pilha está cheia.
  if (isFull(s)) {
    LOG_D("A pilha está cheia.\n");
    return ;
  }

  LOG_D("Adicionando um novo elemento. Capacidade atual: %zu  \n", s->capacity);

  // Soma a contagem da pilha e verifica se não excedeu a capacidade, se não houver espaco, aumenta a capacidade
  if (s->capacity <  (s->length + 1)) {
    void *old_storage = s->storage; // Salva uma cópia, caso o realloc falhe
    LOG_D("Limite da pilha atingido. Dobrando a capacidade... \n");
    s->capacity += 1;
    if (((s)->storage = realloc(s->storage, s->capacity * s->element_size)) == NULL) {
      LOG_D("Falha ao aumentar a capacidade da pilha");
      free( old_storage );  // libera o bloco original
      exit(1);
    }
    LOG_D("Nova capacidade: %zu  \n", s->capacity);
  }

  void *destAddr;
  // Verificar se deve fazer cast para CHAR --> (char *) s->storage + s->length * s->element_size;
  destAddr = s->storage + s->length++ * s->element_size;
  memcpy(destAddr, element, s->element_size);
}

void *pop(Stack s){
  if(isEmpty(s)){
    return NULL;
  }
  void *source = s->storage + (s->length-1) * s->element_size;
  LOG_D("Removendo o elemento do topo. \n");
  if (source == NULL ) {
    return NULL;
  }
  s->length--;
  return source;
}

void *get(Stack s, int position) {
  void *source = s->storage + position * s->element_size;
  // Copia o elemento da pilha pra uma variável local e retorna.
  void *element_address = malloc(s->element_size);
  memcpy(element_address, source, s->element_size);
  return element_address;
}

void *top(Stack s) {
  // Verifica se a pilha está vazia antes de verificar o topo.
  if (s->length == 0) {
    return NULL;
  }
  return get(s, s->length -1);
}

void destroy(Stack s) {
  free(s->storage);
  s->length = 0;
  s->capacity = 0;
  free(s);
}

void printStack(void (*f)(int, void*), Stack s){
  for ( int i = 0 ; i < s->length ; i++ ) {
    void *source = s->storage + i * s->element_size;
    (*f)(i, source);
  }
}