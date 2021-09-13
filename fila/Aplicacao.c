#include "Fila_publico.h"
#include "Pilha_publico.h"
#include "Aplicacao_privado.h"

struct TestStruct2 {
  char* test_data;
};

void printInt ( int y, void* x ) {
  printf("Posicao:  %d - Elemento: %d\n", y, *((int *) x));
}

void printString ( int y, void* x ) {
  printf("Posicao:  %d - Elemento: %s\n", y, *((char **) x));
}

void printTestStruct ( int y, void* x ) {
  printf("Posicao:  %d - Elemento: %s\n", y, ((struct TestStruct2 *) x)->test_data);
}

void testStruckQueue(){
  printf("Testando Fila de TestStruct: \n");
  // Cria um array de structs

  // Exemplo com ponteiros -> Deve ser desallocado no final do processo
  // #OBS1
  /*
    struct TestStruct *ts1 = malloc(sizeof(struct TestStruct));
    ts1->test_data = "teste struct 01";
    struct TestStruct *ts2 = malloc(sizeof(struct TestStruct));
    ts2->test_data = "teste struct 02";
    struct TestStruct *ts3 = malloc(sizeof(struct TestStruct));
    ts3->test_data = "teste struct 03";
    struct TestStruct arr_structs[] = {*ts1, *ts2, *ts3};
    */

  // Com inicializacao designada
  struct TestStruct2 ts1 = { .test_data = "teste struct 01" };
  struct TestStruct2 ts2 = { .test_data = "teste struct 02" };
  struct TestStruct2 ts3 = { .test_data = "teste struct 03" };
  struct TestStruct2 arr_structs[] = {ts1, ts2, ts3};

  int num_elems = sizeof(arr_structs) / sizeof(arr_structs[0]);

  // Cria um nova fila para TestStruct
  Queue queue_of_structs = initQueue(num_elems);

  // Adiciona os elementos do array na fila
  for (int i = 0; i < num_elems; i++) {
    printf("Adicionando: %s \n",  (arr_structs + i)->test_data);
    enQueue(queue_of_structs, arr_structs + i, sizeof(arr_structs + i));
  }
  printf("\nImprimindo a fila:\n");
  printQueue(printTestStruct, queue_of_structs);
  printf("\n\n");
  printf("Removendo da Fila de TestStruct: \n");
  // Remove os elementos da fila
  struct TestStruct2 *removed_struct;
  while ((removed_struct = deQueue(queue_of_structs)) != NULL) {
    printf("Removido: %s \n", removed_struct->test_data);
    free(removed_struct);
  }
  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_structs) ? "Sim" : "Não");
  // Destroi a fila
  destroyQueue(queue_of_structs);
  // #OBS1
  // free(ts1);
  // free(ts2);
  // free(ts3);
}

void testIntegerQueue(){
  printf("Testando Fila de Inteiros\n");
  // Cria um array de inteiros
  int arr_int[] = {11, 222, 33, 44, 55};
  int num_elems = sizeof(arr_int) / sizeof(arr_int[0]);

  // Cria um nova fila para inteiros
  Queue queue_of_ints = initQueue(num_elems);

  // Adiciona os elementos do array na fila
  for (int i = 0; i < num_elems; i++) {
    printf("Adicionando: %d \n",  *(arr_int + i));
    enQueue(queue_of_ints, arr_int + i, sizeof(arr_int + i));
  }
  printf("\nImprimindo a fila:\n");
  // printQueue(printInt, queue_of_ints);
  printf("\n\n");
  printf("Removendo da Fila de Inteiros: \n");
  // Remove os elementos da fila
  int *removed_int;
  while ((removed_int = deQueue(queue_of_ints)) != NULL) {
    printf("Removido: %d \n", *removed_int);
    free(removed_int);
  }
  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_ints) ? "Sim" : "Não");
  // Destroi a fila
  destroyQueue(queue_of_ints);
}

void testStringQueue() {
  printf("Testando Fila de Strings\n");
  // Cria um array de strings
  char *arr_chars[] = {"abc", "defghf", "ghi", "jlk", "mno"};
  int num_elems = sizeof(arr_chars) / sizeof(arr_chars[0]);

  // Cria um nova fila para inteiros
  Queue queue_of_chars = initQueue(2);

  // Adiciona os elementos do array na fila
  for (int i = 0; i < num_elems; i++) {
    printf("Fila esta cheia: %s \n", isFullQueue(queue_of_chars) ? "Sim" : "Não");
    if(!isFullQueue(queue_of_chars)){
      printf("Adicionando: %s \n", *(arr_chars + i));
      enQueue(queue_of_chars, arr_chars + i, sizeof(arr_chars + i));
    } else {
      printf("Descartando: %s \n", *(arr_chars + i));
    }
  }
  printf("\n");
  printf("\nImprimindo a fila:\n");
  printQueue(printString, queue_of_chars);
  printf("\n\n");
  printf("Removendo da Fila de Strings: \n");
  // Remove os elementos da fila
  char **removed_char;
  while ((removed_char = deQueue(queue_of_chars)) != NULL) {
    printf("Removido: %s \n", *removed_char);
    free(removed_char);
  }
  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_chars) ? "Sim" : "Não");
  // Destroi a fila
  destroyQueue(queue_of_chars);
}

void testIntegerQueue2(){
  printf("Testando Fila de Inteiros\n");
  // Cria um array de inteiros
  int arr_int[] = {11, 222, 33, 44, 55};
  int num_elems = sizeof(arr_int) / sizeof(arr_int[0]);

  // Cria um nova fila para inteiros
  Queue queue_of_ints = initQueue(num_elems);

  // Adiciona os elementos do array na fila
  for (int i = 0; i < num_elems; i++) {
    printf("Adicionando: %d \n",  *(arr_int + i));
    enQueue(queue_of_ints, arr_int + i, sizeof(arr_int + i));    
  }
  printf("Fila esta cheia: %s \n", isFullQueue(queue_of_ints) ? "Sim" : "Não");
  printf("\nImprimindo a fila:\n");
  printQueue(printInt, queue_of_ints);
  printf("\n\n");
  printf("Removendo da Fila de Inteiros: \n");
  // Remove os elementos da fila
  int *removed_int =  deQueue(queue_of_ints);
  printf("Removido: %d \n", *removed_int);
  free(removed_int);
  removed_int = deQueue(queue_of_ints);
  printf("Removido: %d \n", *removed_int);
  printf("Fila esta cheia: %s \n", isFullQueue(queue_of_ints) ? "Sim" : "Não");
  free(removed_int);
  int new_number = 66;
  enQueue(queue_of_ints, &new_number, sizeof(int*));
  int new_number2 = 77;
  enQueue(queue_of_ints, &new_number2, sizeof(int*));
  while ((removed_int = deQueue(queue_of_ints)) != NULL) {
    printf("Removido: %d \n", *removed_int);
    free(removed_int);
  }
  
  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_ints) ? "Sim" : "Não");
  // Destroi a fila
  destroyQueue(queue_of_ints);
}

void testStringStack() {
  printf("Testando Pilha de Strings\n");
  // Cria um array de strings
  char *arr_chars[] = {"abc", "def", "ghi", "jlk", "mno"};
  int num_elems = sizeof(arr_chars) / sizeof(arr_chars[0]);

  // Cria um nova pilha para inteiros
  Stack stack_of_chars = init(sizeof(arr_chars[0]), 2);

  // Adiciona os elementos do array na pilha
  for (int i = 0; i < num_elems; i++) {
    printf("Pilha esta cheia: %s \n", isFull(stack_of_chars) ? "Sim" : "Não");
    if(!isFull(stack_of_chars)){
      printf("Adicionando: %s \n", *(arr_chars + i));
      push(stack_of_chars, arr_chars + i);
    } else {
       printf("Descartando: %s \n", *(arr_chars + i));
    }
  }
  printf("\n");
  printf("\nImprimindo a pilha:\n");
  printStack(printString, stack_of_chars);
  printf("\n\n");
  printf("Testando Pilha de Inteiros\n");
  // Cria um array de inteiros
  int arr_int[] = {11, 222, 33, 44, 55};
  int num_ints = sizeof(arr_int) / sizeof(arr_int[0]);

  // Cria um nova pilha para inteiros
  Stack stack_of_ints = init(sizeof(arr_int[0]), num_ints);

  // Adiciona os elementos do array na pilha
  for (int i = 0; i < num_ints; i++) {
    printf("Adicionando: %d \n",  *(arr_int + i));
    push(stack_of_ints, arr_int + i);
  }
  printf("\nImprimindo a pilha:\n");
  printStack(printInt, stack_of_ints);
  printf("\n\n");
  printf("\nCriando uma fila de pilhas:\n");
  printf("\n\n");
  // Adiciona os elementos em uma fila
  Queue queue_of_stacks = initQueue(2);
  printf("Adicionando pilha de chars\n");
  enQueue(queue_of_stacks, &stack_of_chars, sizeof(Stack *));
  printf("Adicionando pilha de ints\n");
  enQueue(queue_of_stacks, &stack_of_ints, sizeof(Stack *));
  printf("Removendo uma fila de ints\n");
  Stack *removed_stack = deQueue(queue_of_stacks);
  printf("Imprimindo a pilha de ints\n");
  printStack(printString, *removed_stack);
  free(removed_stack);
  printf("Removendo uma fila de chars \n");
  removed_stack = deQueue(queue_of_stacks);
  printf("Imprimindo a pilha de chars\n");
  printStack(printInt, *removed_stack);
  free(removed_stack);
  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_stacks) ? "Sim" : "Não");
  destroyQueue(queue_of_stacks);

  printf("\nRemovendo da Pilha de Inteiros: \n");
  // Remove os elementos da pilha
  int *removed_int;
  while ((removed_int = pop(stack_of_ints)) != NULL) {
    printf("Removido: %d \n", *removed_int);
  }
  printf("Pilha esta vazia: %s \n", isEmpty(stack_of_ints) ? "Sim" : "Não");
  // Destroi a pilha
  destroy(stack_of_ints);
  printf("Removendo da Pilha de Strings: \n");
  // Remove os elementos da pilha
  char **removed_char;
  while ((removed_char = pop(stack_of_chars)) != NULL) {
    printf("Removido: %s \n", *removed_char);
  }
  printf("Pilha esta vazia: %s \n", isEmpty(stack_of_chars) ? "Sim" : "Não");
  // Destroi a pilha
  destroy(stack_of_chars);
}

int main(int argc, char* argv[]) {
  printf("---------------------------------------\n");\
  testStringStack();
  testStruckQueue();
  // ------------------------------------------------------
  printf("\n\n");
  printf("---------------------------------------\n");
  // ------------------------------------------------------
  testIntegerQueue2();
  // ------------------------------------------------------
  printf("\n\n");
  printf("---------------------------------------\n");
  // ------------------------------------------------------
  testStringQueue();
  // ------------------------------------------------------
  printf("\n\n");
  printf("---------------------------------------\n");
  return 0;
}