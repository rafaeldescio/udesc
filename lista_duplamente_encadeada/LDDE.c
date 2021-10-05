#include "LDDE_privado.h"

#ifdef ENABLE_DEBUG_LOG
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define LOG_D(fmt, args...)              \
  {                                      \
    printf("D:");                        \
    fprintf(stdout, fmt, ##args);        \
  }
#define LOG_E(fmt, args...)              \
  {                                      \
    printf(ANSI_COLOR_RED "E:" );        \
    fprintf(stdout, fmt, ##args);        \
    printf(ANSI_COLOR_RESET);            \
  }
#else
#define LOG_D(fmt, args...) // it does nothing
#define LOG_E(fmt, args...) // it does nothing
#endif

// ###################################################################################################################
// PRIVATE METHODS
// ###################################################################################################################

pElement newElement(void *val, pElement previous, pElement next,  size_t typesize, TypeName typename){
  pElement newElem = malloc(sizeof(struct list_element));
  void *destAddr = malloc(typesize);
  if(newElem == NULL || destAddr==NULL) {
    LOG_E("Failed to alloc a new element");
    exit(2);
  }
  memcpy(destAddr, val, typesize);
  newElem->element = destAddr;
  newElem->previous_element = previous;
  newElem->next_element = next;
  newElem->typesize = typesize;
  newElem->typename = typename;
  return newElem;
}

pElement peekElementAtPosition(pList s, size_t position){
  if (position < 0 || position > s->size) {
    return NULL;
  }
  pElement el = s->head;
  for(size_t i = 0; i < s->size; i++){
    if(i == position) break;
    el = el->next_element;
  }
  return el;
}

int getTypeAtList(pList s, size_t position){
  pElement el = peekElementAtPosition(s, position);
  if (el == NULL) {
    LOG_E("Element not found at %ld\n", position)
    return FAILURE;
  }
  return el->typename;
}

void destroyElement(pElement el){
  free(el->element);
  free(el);
}

// ###################################################################################################################
// PUBLIC METHODS
// ###################################################################################################################

int initList(ppList l){
  LOG_D("Creating a empty list. \n" );
  (*l) = malloc(sizeof(struct List));
  if((*l) == NULL){
    LOG_E("Failed to create a new list");
    return FAILURE;
  }
  (*l)->head = NULL;
  (*l)->tail = NULL;
  (*l)->size = 0;
  return SUCCESS;
}

int destroyList(pList* l) {
  LOG_D("Destroying list. \n" );
  pElement el = (*l)->head;
  pElement next = (*l)->head;
  for(size_t i = 0; i < (*l)->size; i++){
    el = next;
    next = el->next_element;
    destroyElement(el);
  }
  (*l)->head = NULL;
  (*l)->tail = NULL;
  (*l)->size = 0;
  free((*l));
  *l = NULL;
  return SUCCESS;
}

int resetList(pList* l){
  LOG_D("Resetting list. \n" );
  pElement el = (*l)->head;
  pElement next = (*l)->head;
  for(size_t i = 0; i < (*l)->size; i++){
    el = next;
    next = el->next_element;
    destroyElement(el);
  }
  (*l)->head = NULL;
  (*l)->tail = NULL;
  (*l)->size = 0;
  return SUCCESS;
}

bool isEmptyList(pList s) {
  if(s == NULL){
    return true;
  }
  LOG_D("Is empty size: %ld\n", s->size)
  return (s->size == 0);
}

int sizeList(pList s) {
   if(s == NULL){
    LOG_E("Invalid list size\n");
    exit(2);
  }
  return s->size;
}


// -------------------------------------------------------------------------------------------------------------------
// PEEK
// -------------------------------------------------------------------------------------------------------------------

int peekListPosition(pList s, size_t position, void *element, TypeName typename){
  if (position < 0 || position > s->size) {
    LOG_E("Invalid peek position at %ld\n", position)
    return FAILURE;
  }
  pElement el = peekElementAtPosition(s, position);
  if (el == NULL) {
    LOG_E("Element not found at %ld\n", position)
    return FAILURE;
  }
  if(el->typename != typename){
    LOG_E("Invalid type of element at %ld\n", position)
    return FAILURE;
  }
  memcpy(element, el->element, el->typesize );
  return SUCCESS;
}

int peekListTail(pList s, void *element, TypeName typename){
  if(s->tail == NULL){
    LOG_E("Element peek tail not found\n");
    return FAILURE;
  }
  if(s->tail->typename != typename){
    LOG_E("Invalid peek type of element tail\n")
    return FAILURE;
  }
  memcpy(element, s->tail->element, s->tail->typesize );
  return SUCCESS;
}

int peekListHead(pList s, void *element, TypeName typename){
  if(s->head == NULL){
    LOG_E("Element peek head not found\n");
    return FAILURE;
  }
  if(s->head->typename != typename){
    LOG_E("Invalid peek type of element head\n")
    return FAILURE;
  }
  memcpy(element, s->head->element, s->head->typesize );
  return SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------
// ADD
// -------------------------------------------------------------------------------------------------------------------

int addListPosition(pList s,  size_t position, void *element, size_t typesize, TypeName typename){
  pElement el = peekElementAtPosition(s, position);
  if(el == NULL){
    if(position < 0){
     return  addListHead(s, element, typesize, typename);
    }
    if(position > s->size){
     return  addListTail(s, element, typesize, typename);
    }
    LOG_E("Add element failed\n")
    return FAILURE;
  }
  pElement previous = el->previous_element;
  pElement new_element = newElement(element, previous, el, typesize, typename);
  el->previous_element = new_element;
  if(previous != NULL){
    previous->next_element = new_element;
  }
  s->size++;
  return SUCCESS;
}

int addListHead(pList s, void *element, size_t typesize, TypeName typename){
  if(s->head == NULL){
    LOG_D("Adding first element\n");
    pElement new_element = newElement(element, NULL, NULL, typesize, typename);
    s->head = s->tail = new_element;
  } else {
    pElement new_element = newElement(element, NULL, s->head, typesize, typename);
    s->head->previous_element = new_element;
    s->head = new_element;
  }
  s->size++;
  return SUCCESS;
}

int addListTail(pList s, void *element, size_t typesize, TypeName typename){
  if(s->tail == NULL){
    LOG_D("Adding first element\n");
    pElement new_element = newElement(element, NULL, NULL, typesize, typename);
    s->head = s->tail = new_element;
  } else {
    pElement new_element = newElement(element, s->tail, NULL, typesize, typename);
    s->tail->next_element = new_element;
    s->tail = new_element;
  }
  s->size++;
  return SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------
// REMOVE
// -------------------------------------------------------------------------------------------------------------------

int removeListTail(pList s,void *element, TypeName typename){
   if(s->tail == NULL){
    LOG_E("Tail element not found\n");
    return FAILURE;
  } 
  pElement previous = s->tail->previous_element;
  pElement current_tail = s->tail;
  if(current_tail->typename != typename){
    LOG_E("Invalid type of tail element %d != %d\n", current_tail->typename, typename);
    return FAILURE;
  }
  s->tail = previous;
  if(s->tail != NULL){
    s->tail->next_element = NULL;
  }
  memcpy(element, current_tail->element, current_tail->typesize);
  free(current_tail->element);
  free(current_tail);
  
  if(--s->size == 0){
    LOG_D("Removing last element\n");
    s->tail = s->head = NULL;
  }
  return SUCCESS;
}

int removeListHead(pList s, void *element, TypeName typename){
   if(s->head == NULL){
    LOG_E("Head element not found\n");
    return FAILURE;
  } 
  pElement next = s->head->next_element;
  pElement current_head = s->head;
  if(current_head->typename != typename){
    LOG_E("Invalid type of head element %d != %d\n", current_head->typename, typename);
    return FAILURE;
  }
  s->head = next;
  if(s->head != NULL){
    s->head->previous_element = NULL;
  }
  memcpy(element, current_head->element, current_head->typesize);
  free(current_head->element);
  free(current_head);
  if(--s->size == 0){
    LOG_D("Removing last element\n");
    s->tail = s->head = NULL;
  }
  return SUCCESS;
}

int removeListPosition(pList s, size_t position, void *element, TypeName typename){
  pElement el = peekElementAtPosition(s, position);
  if(el == NULL){
    LOG_E("Element not found at %ld\n", position);
    return FAILURE;
  }
  if(el->typename != typename){
    LOG_E("Invalid type of element\n");
    return FAILURE;
  }
  pElement previous = el->previous_element;
  pElement next = el->next_element;
  if(previous != NULL){
    previous->next_element = next;
  }
  if(next != NULL){
    next->previous_element = previous;
  }
  if(position == 0){
    s->head = next;
  }
  if(position == --s->size){
    s->tail = previous;
  }
  memcpy(element, el->element, el->typesize );
  free(el->element);
  free(el);
  return SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------
// PRINT
// -------------------------------------------------------------------------------------------------------------------

void printList(pList s, void (* print)(void *e, TypeName t, size_t p)){
  pElement el = s->head;
  printf("Imprimindo list de ascendente\n");
  printf("Tamanho atual: %ld\n", s->size);
  for(size_t i = 0; i < s->size; i++){
    printf("typename %d %ld\n", el->typename, i);
    print(el->element, el->typename, i);
    el = el->next_element;
  }
  printf("\n");
}

void printListReverse(pList s, void (* print)(void *e, TypeName t, size_t p)){
  pElement el = s->tail;
  printf("Imprimindo list de descendente\n");
  printf("Tamanho atual: %ld\n", s->size);
  for(size_t i = s->size; i > 0; i--){
    print(el->element, el->typename, (i-1));
    el = el->previous_element;
  }
  printf("\n");
}