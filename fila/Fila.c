#include "Fila_privado.h"

#ifdef ENABLE_DEBUG_LOG
#define LOG_D(fmt, args...) \
  {                           \
    printf("D:");             \
    fprintf(stdout, fmt, ##args);        \
  }
#else
#define LOG_D(fmt, args...) // faz nada
#endif

QueueElement newElement(void *val, size_t element_size){
  QueueElement newElem = malloc(sizeof(struct queue_element));
  void *destAddr = malloc(element_size);
  memcpy(destAddr, val, sizeof(element_size));
  newElem->element = destAddr;
  newElem->element_size = element_size;
  return newElem;
}

Queue initQueue( size_t max_elements){
  LOG_D("Iniciando fila vazia. \n");
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

void privateEnQueue(Queue s, void* element, size_t element_size) {
    
  if (s->front == -1) {
    // Fila vazia
    s->front = 0;
  } 
  
  s->rear = (s->rear +1) % s->max_elements;
  QueueElement new_element = newElement(element, element_size);
  s->storage[s->rear] = new_element;
}

void enQueue(Queue s, void *element, size_t element_size) {
  printf("adding %zu, %d\n", s->rear, *((int*) element));
  // Verifica se os parâmetros estão vazios. Retorna um erro caso esteja.
  if ( s == NULL || element == NULL) {
    LOG_D("Falha ao adicionar na fila, verifique os parametros passados.\n");
    return ;
  }

  // Valida se a fila está cheia.
  if (isFullQueue(s)) {
    LOG_D("A fila está cheia.\n");
    return ;
  }

  LOG_D("Adicionando um novo elemento. Capacidade atual: %ld , %ld \n", s->rear, s->front);

  privateEnQueue(s, element, element_size);
}
void *privateDeQueue (Queue s){
  LOG_D("Removendo o elemento do inicio. \n");

  QueueElement element = s->storage[s->front]; 
  if (s->front  == s->rear) {
    s->front = -1;
    s->rear = -1;
  } else {
    s->front = (s->front + 1) % s->max_elements;
  }
  void *destAddr = malloc(element->element_size);
  memcpy(destAddr, element->element, sizeof(element->element_size));
  free(element->element);
  free(element);
  return destAddr;
}

void *deQueue(Queue s){
  if(isEmptyQueue(s)){
    return NULL;
  }
  return privateDeQueue(s);
}

void *peek(Queue s, size_t position) {
  // Verifica se a fila está vazia antes de verificar o topo.
  if (s->front == -1) {
    return NULL;
  }
  return s->storage[position]->element;
}

void destroyQueue(Queue s) {
  for(int i = 0; i < s->max_elements; i++){
    void* p = deQueue(s);
    free(p);
  }
  free(s->storage);
  s->front = -1;
  s->rear = -1;
  free(s);
}

void printQueue(void (*f)(int, void*), Queue s){
  for ( int i = 0 ; i < s->max_elements ; i++ ) {
    QueueElement source = s->storage[i];
    (*f)(i, source->element);
  }
}