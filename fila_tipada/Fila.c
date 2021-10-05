#include "Fila_privado.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
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
int _privateDeQueue(Queue s){
  void* return_element = malloc(sizeof(void*));
  deQueueOriginal(s, return_element);
  free(return_element);
  return SUCCESS;
}

int privateDeQueueTyped(Queue s, void* return_element, TypeName typename){
  
  if(isEmptyQueue(s)){
    return FAILURE;
  }
  LOG_D("Removendo o elemento do inicio. \n");

  QueueElement element = s->storage[s->front]; 
  if(element->typename != typename){
    LOG_D("Type is different [%d] != [%d]\n", element->typename, typename);
    return FAILURE;
  }
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
int deQueueOriginal(Queue s, void* return_element){
  
  if(isEmptyQueue(s)){
    return FAILURE;
  }
  LOG_D("Removendo o elemento do inicio. \n");

  QueueElement element = s->storage[s->front]; 
  // if((deQueueTyped(element, element->typesize, element->typename) == FAILURE)){
  //   return FAILURE;
  // }
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

TypeName nextQueueType(Queue s){
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

void _destroyCustom(Queue s ){
  int nt = nextQueueType(s);
  // special treatment when we have a custom type
  if(nt == TYPENAME_CUSTOM_STACK) {
    destroipilha(s->storage[s->front]->element);
  } 
}
void destroyQueue(Queue s) {
 
  for(int i = 0; i < s->max_elements; i++){
     _destroyCustom(s);
     _privateDeQueue(s);
  }
  free(s->storage);
  s->front = -1;
  s->rear = -1;
  free(s);
}
int enQueueInt(Queue s, int element) {
  return enQueueOriginal(s, &element, sizeof(int), TYPE_NAME(element));
}

int enQueueDouble(Queue s, double element) {
  return enQueueOriginal(s, &element, sizeof(double), TYPENAME_DOUBLE);
}

int enQueueChar(Queue s, char element) {
  return enQueueOriginal(s, &element, sizeof(char), TYPE_NAME(element));
}

int enQueueCharVector(Queue s, char* element) {
  LOG_D("Elemento char vector %s %ld\n", element, sizeof(char*));
  LOG_D("Type name: %d\n", TYPE_NAME(element));
  return enQueueOriginal(s, &element, sizeof(char*), TYPE_NAME(element));

}

int enQueuePPilha(Queue s, pPilha element){
  LOG_D("Elemento char vector %s %ld\n", element, sizeof(char*));
  LOG_D("Type name: %d\n", TYPE_NAME(element));
  return enQueueOriginal(s, &element, sizeof(char*), TYPE_NAME(element));
}
int enQueueInvalid(Queue s, void *element){
  LOG_D("Elemento Inválido\n");
  return FAILURE;
}

double deQueueDouble(Queue s, double element){
  double j = 0;
  deQueueOriginal(s, &j);
  return j;
}

int deQueueInt(Queue s, int element){
  int j = 0;
  deQueueOriginal(s, &j);
  return j;
}

char deQueueChar(Queue s, char element){
  char j = 0;
  deQueueOriginal(s, &j);
  return j;
}

char* deQueueCharVector(Queue s, char* element){
  char* j = 0;
  deQueueOriginal(s, &j);
  return j;
}

int deQueueInvalid(Queue s, char* a){
  return FAILURE;
}
char** dqCharVector(Queue s){
  char** el = malloc(sizeof(char**));
  int ret = privateDeQueueTyped(s, el, TYPENAME_POINTER_TO_CHAR);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

char* dqChar(Queue s){
  char* el = malloc(sizeof(char));
  int ret = privateDeQueueTyped(s, el, TYPENAME_CHAR);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

signed char* dqSignedChar(Queue s){
  signed char* el = malloc(sizeof(signed char));
  int ret = privateDeQueueTyped(s, el, TYPENAME_SIGNED_CHAR);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

unsigned char* dqUnsignedChar(Queue s){
  unsigned char* el = malloc(sizeof(unsigned char));
  int ret = privateDeQueueTyped(s, el, TYPENAME_UNSIGNED_CHAR);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

int* dqInt(Queue s){
  int *el = malloc(sizeof(int));
  int ret = privateDeQueueTyped(s, el, TYPENAME_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

long int* dqLongInt(Queue s){
  long int *el = malloc(sizeof(long int));
  int ret = privateDeQueueTyped(s, el, TYPENAME_LONG_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

unsigned long int* dqUnsignedLongInt(Queue s){
  unsigned long int *el = malloc(sizeof(unsigned long int));
  int ret = privateDeQueueTyped(s, el, TYPENAME_UNSIGNED_LONG_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

unsigned long long int* dqUnsignedLongLongInt(Queue s){
  unsigned long long int *el = malloc(sizeof(unsigned long long int));
  int ret = privateDeQueueTyped(s, el, TYPENAME_UNSIGNED_LONG_LONG_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

long long int* dqLongLongInt(Queue s){
  long long int *el = malloc(sizeof(long long int));
  int ret = privateDeQueueTyped(s, el, TYPENAME_LONG_LONG_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

unsigned int* dqUnsignedInt(Queue s){
  unsigned int *el = malloc(sizeof(unsigned int));
  int ret = privateDeQueueTyped(s, el, TYPENAME_UNSIGNED_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

short int* dqShortInt(Queue s){
  short int *el = malloc(sizeof(short int));
  int ret = privateDeQueueTyped(s, el, TYPENAME_SHORT_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

unsigned short int* dqUnsignedShortInt(Queue s){
  unsigned short int *el = malloc(sizeof(unsigned short int));
  int ret = privateDeQueueTyped(s, el, TYPENAME_UNSIGNED_SHORT_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

float* dqFloat(Queue s){
  float *el = malloc(sizeof(float));
  int ret = privateDeQueueTyped(s, el, TYPENAME_FLOAT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

double* dqDouble(Queue s){
  double *el = malloc(sizeof(double));
  int ret = privateDeQueueTyped(s, el, TYPENAME_DOUBLE);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

long double* dqLongDouble(Queue s){
  long double *el = malloc(sizeof(long double));
  int ret = privateDeQueueTyped(s, el, TYPENAME_LONG_DOUBLE);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

int** dqIntPointer(Queue s){
  int** el = malloc(sizeof(int**));
  int ret = privateDeQueueTyped(s, el, TYPENAME_POINTER_TO_INT);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

void* dqVoidPointer(Queue s){
  void* el = malloc(sizeof(void*));
  int ret = privateDeQueueTyped(s, el, TYPENAME_POINTER_TO_VOID);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}

pPilha dqCustomStack(Queue s){
  pPilha el = malloc(sizeof(pPilha));
  int ret = privateDeQueueTyped(s, el, TYPENAME_CUSTOM_STACK);
  if (ret == SUCCESS) {
    return el;
  }
  free(el);
  return NULL;
}
void* __privateDeQueueTyped(Queue s, TypeName t){
  switch (t) {
  case TYPENAME_INT:
    return dqInt(s);
  case TYPENAME_UNSIGNED_INT:
    return dqUnsignedInt(s);
  case TYPENAME_LONG_INT:
    return dqLongInt(s);
  case TYPENAME_LONG_LONG_INT:
    return dqLongLongInt(s);
  case TYPENAME_UNSIGNED_LONG_INT:
    return dqUnsignedLongInt(s);
  case TYPENAME_UNSIGNED_LONG_LONG_INT:
    return dqUnsignedLongLongInt(s);
  case TYPENAME_SHORT_INT:
    return dqShortInt(s);
  case TYPENAME_UNSIGNED_SHORT_INT:
    return dqUnsignedShortInt(s);
  case TYPENAME_FLOAT: ;
    return dqFloat(s);
  case TYPENAME_DOUBLE: ;
    return dqDouble(s);
  case TYPENAME_LONG_DOUBLE: ;
    return dqLongDouble(s);
  case TYPENAME_CHAR:
    return dqChar(s);
  case TYPENAME_SIGNED_CHAR:
    return dqSignedChar(s);
  case TYPENAME_UNSIGNED_CHAR:
    return dqUnsignedChar(s);
  case TYPENAME_POINTER_TO_CHAR:
    return dqCharVector(s);
  case TYPENAME_POINTER_TO_VOID:
    return dqVoidPointer(s);
  case TYPENAME_POINTER_TO_INT:
    return dqIntPointer(s);
  case TYPENAME_CUSTOM_STACK:
    return dqCustomStack(s);
  default:
    LOG_D("Element did not match type");
    return NULL;
  }
}


char* getTypeName(TypeName t){
  switch (t){
    case TYPENAME_BOOL:
     return "bool";
    case TYPENAME_UNSIGNED_CHAR:
      return "unsigned char";
    case TYPENAME_CHAR:
      return "char";
    case TYPENAME_SIGNED_CHAR:
      return "signed char";
    case TYPENAME_SHORT_INT:
      return "short int";
    case TYPENAME_UNSIGNED_SHORT_INT:
      return "unsigned short int";
    case TYPENAME_INT:
      return "int";
    case TYPENAME_UNSIGNED_INT:
     return "unsigned int";
    case TYPENAME_LONG_INT:
      return "long int";
    case TYPENAME_UNSIGNED_LONG_INT:
      return "unsigned long int";
    case TYPENAME_LONG_LONG_INT:
      return "long long int";
    case TYPENAME_UNSIGNED_LONG_LONG_INT:
      return "unsigned long long int";
    case TYPENAME_FLOAT:
      return "float";
    case TYPENAME_DOUBLE:
      return "double";
    case TYPENAME_LONG_DOUBLE:
      return "long double";
    case TYPENAME_POINTER_TO_CHAR:
      return "pointer to char";
    case TYPENAME_POINTER_TO_LONG:
      return "pointer to long";
    case TYPENAME_POINTER_TO_VOID:
      return "pointer to void";
    case TYPENAME_POINTER_TO_INT:
      return "pointer to int";
    case TYPENAME_CUSTOM_STACK:
      return "custom stack";
    case TYPENAME_UNKNOWN:
    default:
      return "unknown";
  }
}

