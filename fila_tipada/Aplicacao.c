#define ENABLE_DEBUG_LOG 1
#include "Fila_publico.h"
#include "pilha_publico.h"
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

void testGenericQueue(){
  printf("Testando Fila de Generica\n");
  // Cria um array de inteiros
  int arr_int[] = {11, 222, 33, 44, 55};
  int num_elems = sizeof(arr_int) / sizeof(arr_int[0]);
  
  // Cria um nova fila generica com 8 posicoes
  Queue queue_of_generics = initQueue(8);

  // Adiciona os elementos do array de inteiros na fila
  for (int i = 0; i < num_elems; i++) {
    printf("Adicionando: %d \n",  *(arr_int + i));
    int val = arr_int[i];
    enQueue(queue_of_generics, val);    
  }
  printf("Fila esta cheia: %s \n", isFullQueue(queue_of_generics) ? "Sim" : "Não");
  printf("\n\nVamos remover alguns elementos da Fila: \n");

  // Remove os elementos da fila
  int removed_int = deQueue(queue_of_generics);

  printf("Removido: %d \n", removed_int);

  removed_int = deQueue(queue_of_generics);

  printf("Removido: %d \n", removed_int);
  printf("Fila esta cheia: %s \n", isFullQueue(queue_of_generics) ? "Sim" : "Não");

  printf("\n\nAdicionando novos elementos na Fila: \n");
  int new_number = 66;
  int new_number2 = 77;
  double new_number3 = 929.1;
  char new_char = 'y';
  char* new_char_vector = "abc";
  int ret = 0;
  ret = enQueue(queue_of_generics, new_number);
  if (ret)
    printf("Valor adicionado [%d]\n", new_number);
  enQueue(queue_of_generics, new_number2);
  if (ret)
    printf("Valor adicionado [%d]\n", new_number2);
  enQueue(queue_of_generics, new_number3);
  if (ret)
    printf("Valor adicionado [%f]\n", new_number3);
  enQueue(queue_of_generics, new_char);
  if (ret)
    printf("Valor adicionado [%c]\n", new_char);
  
  printf("Fila esta cheia: %s \n", isFullQueue(queue_of_generics) ? "Sim" : "Não");
  printf("\nTentando adicionar um elemento estranho: \n");
  
  // Cria um elemento desconhecido,que vai ser ignorado
  struct TestStruct2 ts1 = { .test_data = "teste struct 01" };
  struct TestStruct2 ts2 = { .test_data = "teste struct 02" };
  struct TestStruct2 ts3 = { .test_data = "teste struct 03" };
  struct TestStruct2 arr_structs[] = {ts1, ts2, ts3};
  ret = enQueue(queue_of_generics, arr_structs);
  printf("Resultado: Adicionou: %s \n\n", ret ? "Sim" : "Não");
  
  printf("Voltamos adicionar, agora um string: \n");
  ret = enQueue(queue_of_generics, new_char_vector);
  if (ret)
    printf("Valor adicionado [%s]\n", new_char_vector);\
    
  //
  // Comeca a remover os elementos
  //

  // Remove sem guardar o retorno
  ret = deQueue(queue_of_generics);
  printf("Removido com sucesso: %s \n", ret ? "Sim" : "Não");
  ret = deQueue(queue_of_generics);
  printf("Removido com sucesso: %s \n", ret ? "Sim" : "Não");
  ret = deQueue(queue_of_generics);
  printf("Removido com sucesso: %s \n", ret ? "Sim" : "Não");
  
  printf("\nRemovendo um elemento e guardando o retorno.\n");
  // Remove atraves de um pointeiro, e guarda o valor
  int retInt = 0;
  ret = deQueueAndGet(queue_of_generics, &retInt);
  if(ret == SUCCESS)
    printf("Removido elemento: [%d] \n", retInt);    

  printf("\nRemovendo um elemento tipados.\n");
  // Remove usando a funcao tipada, retornando o valor retornado
  int* ipointer;
  ipointer = (int*) deQueueTyped(queue_of_generics, TYPENAME_INT);
  printf("Removido Typed Int: [%d] \n", *ipointer);
  free(ipointer);

  int t = nextQueueType(queue_of_generics);
  printf("O tamanho do proximo elemento é: %d -> %s\n", t, getTypeName(t));
  double* dpointer;
  dpointer = deQueueTyped(queue_of_generics, TYPENAME_DOUBLE);
  if (dpointer != NULL){
    printf("Removido Typed Double: [%lf] \n", *dpointer);
    free(dpointer);
  }

  t = nextQueueType(queue_of_generics);
  printf("O tamanho do proximo elemento é: %d -> %s\n", t, getTypeName(t));
  char* cpointer;
  cpointer = (char*) deQueueTyped(queue_of_generics, TYPENAME_CHAR);
  if(cpointer != NULL){
    printf("Removido Typed Char: [%c] \n", *cpointer);
    free(cpointer);
  }

  char** spointer;
  t = nextQueueType(queue_of_generics);
  printf("O tamanho do proximo elemento é: %d -> %s\n", t, getTypeName(t));

  spointer = (char**) deQueueTyped(queue_of_generics, TYPENAME_POINTER_TO_CHAR);
  if(spointer != NULL){
    printf("Removido Typed Char Pointer: [%s] \n", *spointer);
    free(spointer);
  }
  
  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_generics) ? "Sim" : "Não");

  printf("\nAdicionando duas pPilhas:\n");
  pPilha P, P2;
  criapilha(&P, num_elems, sizeof(int));
  int arr_of_int[] = {1, 2, 3, 4, 5};
  for (int i=0; i < num_elems; i++) {
    ret = empilha(P,&arr_of_int[i]);
    printf ("Empilha (%d)\n", arr_of_int[i]);
  }

  criapilha(&P2, num_elems, sizeof(int));
  ret = enQueue(queue_of_generics, P);
  printf("Valor adicionado: %s\n", ret ? "Sim" : "Não");
  ret = enQueue(queue_of_generics, P2);
  printf("Valor adicionado: %s\n", ret ? "Sim" : "Não");
  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_generics) ? "Sim" : "Não");


  // Remove uma das pilhas da fila
  pPilha* ppilhapointer;
  t = nextQueueType(queue_of_generics);
  printf("O tamanho do proximo elemento é: %d -> %s\n", t, getTypeName(t));

  ppilhapointer =  deQueueTyped(queue_of_generics, TYPENAME_CUSTOM_STACK);
  printf("Removido Typed pPilha Pointer: [%p] \n", &ppilhapointer);
  int valor = 0;

  if(ppilhapointer != NULL){

    for (int i=0; i < 5; i++) {
      ret = topo(*ppilhapointer,&arr_of_int);
      if (!ret)
      printf ("ERRO topo ...\n");
      else
      printf ("OK topo %d\n", valor);

      ret = desempilha(*ppilhapointer,&valor);
      if (!ret)
      printf ("ERRO desempilha ...\n");
      else
      printf ("OK desempilha %d...\n", valor);
    }
    destroipilha(ppilhapointer);
    free(ppilhapointer);
  }

  printf("\nIgnora o ultimo valor e deve ser desalocado no destrutor\n");
  printf("\nFila esta vazia: %s \n", isEmptyQueue(queue_of_generics) ? "Sim" : "Não");
  printf("\nChama o destrutor destrutor.\n");
  // Destroi a fila
  destroyQueue(queue_of_generics);
  printf("\nFim do processo, fila destruida e toda de memoria desalocada.");
}

int main(int argc, char* argv[]) {
  printf("\n\n");
  printf("---------------------------------------\n");
  // ------------------------------------------------------
  testGenericQueue();
  // ------------------------------------------------------
  printf("\n\n");
  printf("---------------------------------------\n");
  printf("---------------------------------------\n");
  return 0;
}