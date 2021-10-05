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
  LOG_D("Next type is %s \n", getTypeName(t));
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

char* getTypeName(int t){
  switch (t){
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

// ###############################################################################
// Enqueue methods
// ###############################################################################

int enQueueInt(Queue s, int element) {
  return enQueueOriginal(s, &element, sizeof(int), TYPE_NAME(element));
}

int enQueueUnsignedInt(Queue s, unsigned int element) {
  return enQueueOriginal(s, &element, sizeof(unsigned int), TYPE_NAME(element));
}

int enQueueFloat(Queue s, float element) {
  return enQueueOriginal(s, &element, sizeof(float), TYPE_NAME(element));
}

int enQueueShortInt(Queue s, short int element) {
  return enQueueOriginal(s, &element, sizeof(short int), TYPE_NAME(element));
}

int enQueueUnsignedShortInt(Queue s, unsigned short int element) {
  return enQueueOriginal(s, &element, sizeof(unsigned short int), TYPE_NAME(element));
}

int enQueueLongInt(Queue s, long int element) {
  return enQueueOriginal(s, &element, sizeof( long int), TYPE_NAME(element));
}

int enQueueUnsignedLongInt(Queue s, unsigned long int element) {
  return enQueueOriginal(s, &element, sizeof(unsigned long int), TYPE_NAME(element));
}

int enQueueLongLongInt(Queue s, long long int element) {
  return enQueueOriginal(s, &element, sizeof(long long int), TYPE_NAME(element));
}

int enQueueUnsignedLongLongInt(Queue s, unsigned long long int element) {
  return enQueueOriginal(s, &element, sizeof(unsigned long int), TYPE_NAME(element));
}

int enQueueLong(Queue s, long element) {
  return enQueueOriginal(s, &element, sizeof(long), TYPENAME_FLOAT);
}

int enQueueDouble(Queue s, double element) {
  return enQueueOriginal(s, &element, sizeof(double), TYPENAME_DOUBLE);
}

int enQueueLongDouble(Queue s, long double element) {
  return enQueueOriginal(s, &element, sizeof(long double), TYPENAME_LONG_DOUBLE);
}

int enQueueChar(Queue s, char element) {
  return enQueueOriginal(s, &element, sizeof(char), TYPE_NAME(element));
}

int enQueueSignedChar(Queue s, signed char element) {
  return enQueueOriginal(s, &element, sizeof(signed char), TYPE_NAME(element));
}
int enQueueUnsignedChar(Queue s, unsigned char element) {
  return enQueueOriginal(s, &element, sizeof(signed char), TYPE_NAME(element));
}

int enQueuePointerToVoid(Queue s, void* element) {
  return enQueueOriginal(s, &element, sizeof(void*), TYPENAME_POINTER_TO_VOID);
}

int enQueuePointerToInt(Queue s, int* element) {
  return enQueueOriginal(s, &element, sizeof(int*), TYPENAME_POINTER_TO_INT);
}

int enQueuePointerToChar(Queue s, char* element) {
  LOG_D("Type name: %d\n", TYPE_NAME(element));
  return enQueueOriginal(s, &element, sizeof(char*), TYPE_NAME(element));
}

int enQueueCustomStack(Queue s, pPilha element){
  LOG_D("Type name: %d\n", TYPE_NAME(element));
  return enQueueOriginal(s, &element, sizeof(pPilha), TYPE_NAME(element));
}

int enQueueInvalid(Queue s, void *element){
  LOG_D("Elemento Inválido\n");
  return FAILURE;
}


// ###############################################################################
// Dequeue methods
// ###############################################################################


int deQueueDouble(Queue s, double* element){
  LOG_D("Trying remove double\n");
  return deQueueOriginal(s, element, TYPENAME_DOUBLE);
}

int deQueueLongDouble(Queue s, long double* element){
  LOG_D("Trying remove long double\n");
  return deQueueOriginal(s, element, TYPENAME_LONG_DOUBLE);
}

int deQueueFloat(Queue s, float* element){
  LOG_D("Trying remove float\n");
  return deQueueOriginal(s, element, TYPENAME_FLOAT);
}

int deQueueInt(Queue s, int* element){
  LOG_D("Trying remove int\n");
  return deQueueOriginal(s, element, TYPENAME_INT);
}

int deQueueUnsignedInt(Queue s, unsigned int* element){
  LOG_D("Trying remove unsigned int\n");
  return deQueueOriginal(s, element, TYPENAME_UNSIGNED_INT);
}

int deQueueShortInt(Queue s, short int* element){
  LOG_D("Trying remove short int\n");
  return deQueueOriginal(s, element, TYPENAME_SHORT_INT);
}

int deQueueUnsignedShortInt(Queue s, unsigned short int* element){
  LOG_D("Trying remove unsigned short int\n");
  return deQueueOriginal(s, element, TYPENAME_UNSIGNED_SHORT_INT);
}

int deQueueLongInt(Queue s,  long int* element){
  LOG_D("Trying remove long int\n");
  return deQueueOriginal(s, element, TYPENAME_LONG_INT);
}

int deQueueLongLongInt(Queue s, long long int* element){
  LOG_D("Trying remove long long int\n");
  return deQueueOriginal(s, element, TYPENAME_LONG_LONG_INT);
}

int deQueueUnsignedLongInt(Queue s, unsigned long int* element){
  LOG_D("Trying remove unsigned long int\n");
  return deQueueOriginal(s, element, TYPENAME_UNSIGNED_LONG_INT);
}

int deQueueUnsignedLongLongInt(Queue s, unsigned long long int* element){
  LOG_D("Trying remove unsigned long long int\n");
  return deQueueOriginal(s, element, TYPENAME_UNSIGNED_LONG_LONG_INT);
}

int deQueueChar(Queue s, char* element){
  LOG_D("Trying remove char signed\n");
  return deQueueOriginal(s, element, TYPENAME_CHAR);
}

int deQueueSignedChar(Queue s, signed char* element){
  LOG_D("Trying remove unsigned char\n");
  return deQueueOriginal(s, element, TYPENAME_SIGNED_CHAR);
}

int deQueueUnsignedChar(Queue s, unsigned char* element){
  LOG_D("Trying remove unsigned char\n");
  return deQueueOriginal(s, element, TYPENAME_UNSIGNED_CHAR);
}

int deQueuePointerToChar(Queue s, char** element){
  LOG_D("Trying remove pointer to char\n");
  return deQueueOriginal(s, element, TYPENAME_POINTER_TO_CHAR);
}

int deQueuePointerToInt(Queue s, int** element){
  LOG_D("Trying remove pointer to int\n");
  return deQueueOriginal(s, element, TYPENAME_POINTER_TO_INT);
}

int deQueuePointerToVoid(Queue s, void** element){
  LOG_D("Trying remove pointer to void\n");
  return deQueueOriginal(s, element, TYPENAME_POINTER_TO_VOID);
}

int deQueueCustomStack(Queue s, pPilha* element){
  LOG_D("Trying remove pPilha\n");
  return deQueueOriginal(s, element, TYPENAME_CUSTOM_STACK);
}


int deQueueInvalid(Queue s, void* a){
  printf("Removendo invalid\n");
  return FAILURE;
}