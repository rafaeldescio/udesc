#include "FEC_privado.h"

#ifdef ENABLE_DEBUG_LOG
#define LOG_D(fmt, args...) \
  {                           \
    printf("D:");             \
    fprintf(stdout, fmt, ##args);        \
  }
#else
#define LOG_D(fmt, args...) // faz nada
#endif

QueueElement newElement(void *val, size_t typesize, TypeName typename){
  QueueElement newElem = malloc(sizeof(struct queue_element));
  void *destAddr = malloc(typesize);
  memcpy(destAddr, val, typesize);
  newElem->element = destAddr;
  newElem->typesize = typesize;
  newElem->typename = typename;
  return newElem;
}

Queue initQueue( size_t max_elements){
  LOG_D("Iniciando fila vazia. \n" );
  if(max_elements <=0 ) {
    return NULL;
  }
  Queue s = malloc(sizeof(struct queue));
  s->front = -1;
  s->rear = -1;
  s->max_elements = max_elements;
  s->storage = malloc(max_elements * sizeof(QueueElement));
  return s;
}

bool isFullQueue(Queue s) {
  return (s->front == s->rear+1) || (s->front == 0 && s->rear == s->max_elements -1 );
}

bool isEmptyQueue(Queue s) {
  return (s->front == -1);
}

int sizeQueue(Queue s) {
  return s->max_elements;
}

int enQueueOriginal(Queue s, void *element, size_t typesize, TypeName typename) {
  // Verifica se os parâmetros estão vazios. Retorna um erro caso esteja.
  if ( s == NULL || element == NULL) {
    LOG_D("Falha ao adicionar na fila, verifique os parametros passados.\n");
    return FAILURE;
  }

  // Valida se a fila está cheia.
  if (isFullQueue(s)) {
    LOG_D("A fila está cheia.\n");
    return FAILURE;
  }

  LOG_D("Adicionando um novo elemento. Capacidade atual: %ld , %ld \n", s->rear, s->front);

  if (s->front == -1) {
    // Fila vazia
    s->front = 0;
  } 
  
  s->rear = (s->rear +1) % s->max_elements;
  QueueElement new_element = newElement(element, typesize, typename);
  s->storage[s->rear] = new_element;
  return SUCCESS;
}

int deQueueGeneric(Queue s, void* return_element){
  LOG_D("Removing element at begin \n");
  if(isEmptyQueue(s)){
    return FAILURE;
  }
  QueueElement element = s->storage[s->front]; 
  if (s->front  == s->rear) {
    s->front = -1;
    s->rear = -1;
  } else {
    s->front = (s->front + 1) % s->max_elements;
  }
  memcpy(return_element, element->element, element->typesize);
  free(element->element);
  free(element);
  return SUCCESS;
}

int deQueueOriginal(Queue s, void* return_element, TypeName typename){
  LOG_D("Called original dequeue\n");
  if(isEmptyQueue(s)){
    return FAILURE;
  }
  // Checking type
  TypeName t = nextQueueType(s);
  if(t != typename){
    return FAILURE;
  }
  return deQueueGeneric(s, return_element);
}

int nextQueueType(Queue s){
  if (s->front == -1) {
    return TYPENAME_UNKNOWN;
  }
  QueueElement e = s->storage[s->front];
  return e->typename;
}

void *peek(Queue s, size_t position) {
  // Verifica se a fila está vazia antes de verificar o topo.
  if (s->front == -1) {
    return NULL;
  }
  return s->storage[position]->element;
}

void _destroyCustom(Queue s ) {
  int nt = nextQueueType(s);
  // special treatment when we have a custom type
  if(nt == TYPENAME_CUSTOM_STACK) {
    destroipilha(s->storage[s->front]->element);
  } 
}

int _destroyNextElement(Queue s){
  void* return_element = malloc(sizeof(void*));
  deQueueGeneric(s, return_element);
  free(return_element);
  return SUCCESS;
}

void destroyQueue(Queue s) {
 
  for(int i = 0; i < s->max_elements; i++){
     _destroyCustom(s);
     _destroyNextElement(s);
  }
  free(s->storage);
  s->front = -1;
  s->rear = -1;
  free(s);
}

