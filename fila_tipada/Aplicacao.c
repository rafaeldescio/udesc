#include "Aplicacao.h"

struct TestStruct2 {
  char* test_data;
};

void testGenericQueue(){
  printf("Testando Fila de Generica\n");
  // Cria um array de inteiros
  int arr_int[] = {11, 222, 33, 44, 55};
  int num_elems = sizeof(arr_int) / sizeof(arr_int[0]);
  int ret = 0;
  // Variaveis para guardarmos os retornos
  int retInt = 0;
  char charRet = 'z';
  char* stringRet = "zxy";
  // Cria um nova fila generica com 8 posicoes
  Queue queue_of_generics = initQueue(8);

  int size = sizeQueue(queue_of_generics);
  printf("\nCriado uma fila de tamanho: %d\n\n", size);

  // Adiciona os elementos do array de inteiros na fila
  for (int i = 0; i < num_elems; i++) {
    printf("Adicionando: %d \n",  *(arr_int + i));
    int val = arr_int[i];
    enQueue(queue_of_generics, val);    
  }
  printf("Fila esta cheia: %s \n", isFullQueue(queue_of_generics) ? "Sim" : "Não");
  printf("\n\nVamos remover alguns elementos da Fila: \n");

  // Remove os elementos da fila
  
  // Remove atraves de um pointeiro, e guarda o valor
  ret = deQueue(queue_of_generics, &retInt);
  if(ret)
    printf("Removido elemento: [%d] \n", retInt);    

  ret = deQueue(queue_of_generics, &retInt);
  if(ret)
    printf("Removido elemento: [%d] \n", retInt);  

  printf("Fila esta cheia: %s \n", isFullQueue(queue_of_generics) ? "Sim" : "Não");

  printf("\n\nAdicionando novos elementos na Fila: \n");
  int new_number = 66;
  int new_number2 = 77;
  double new_number3 = 929.1;
  char new_char = 'y';
  char* new_char_vector = "abc";
  
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
  
  
  printf("Voltamos adicionar elementos validos, agora um string: \n");
  ret = enQueue(queue_of_generics, new_char_vector);
  if (ret)
    printf("Valor adicionado [%s]\n", new_char_vector);\

  //
  // Comeca a remover os elementos
  //

  // Remove sem guardar o retorno
  printf("\nRemovendo um elemento e guardando o retorno.\n");

  ret = deQueue(queue_of_generics, &retInt);
  printf("Removido com sucesso: %s \n", ret ? "Sim" : "Não");
  ret = deQueue(queue_of_generics, &retInt);
  printf("Removido com sucesso: %s \n", ret ? "Sim" : "Não");
  ret = deQueue(queue_of_generics, &retInt);
  printf("Removido com sucesso: %s \n", ret ? "Sim" : "Não");
  
  

  ret = deQueue(queue_of_generics, &retInt);
  if(ret){
    printf("Removido Typed Int: [%d] \n", retInt);
  } else {
    printf("Falha ao remover o int\n");
    exit(1);
  }
  printf("\nRemovendo um elemento tipados.\n");
  // Remove usando a funcao tipada, retornando o valor retornado
  ret = deQueue(queue_of_generics, &retInt);
  if(ret){
    printf("Removido Typed Int: [%d] \n", retInt);
  } else {
    printf("Falha ao remover o int\n");
    exit(1);
  }

  int t = nextQueueType(queue_of_generics);
  double doubleRet;
  ret = deQueue(queue_of_generics, &doubleRet);
  if (ret){
    printf("Removido Typed Double: [%lf] \n", doubleRet);
  } else {
    printf("Falha ao remover o double\n");
    exit(1);
  }

  t = nextQueueType(queue_of_generics);
  
  ret = deQueue(queue_of_generics, &charRet);
  if (ret){
    printf("Removido Typed Char: [%c] \n", charRet);
  } else {
    printf("Falha ao remover o char\n");
    exit(1);
  }

  t = nextQueueType(queue_of_generics);
  ret = deQueue(queue_of_generics, &stringRet);
  if (ret){
    printf("Removido Typed Char Pointer: [%s] \n", stringRet);
  } else {
    printf("Falha ao remover a string\n");
    exit(1);
  }
  
  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_generics) ? "Sim" : "Não");

  printf("\nAdicionando duas pPilhas:\n");
  pPilha P, P2;
  // Cria a primeira pilha
  criapilha(&P, num_elems, sizeof(int));
  int arr_of_int[] = {1, 2, 3, 4, 5};
  for (int i=0; i < num_elems; i++) {
    ret = empilha(P,&arr_of_int[i]);
    printf ("Empilha (%d)\n", arr_of_int[i]);
  }
  
  // Cria a segunda pilha
  criapilha(&P2, num_elems, sizeof(int));

  // Enfilera a primeira pilha
  ret = enQueue(queue_of_generics, P);
  printf("Pilha adicionada: %s\n", ret ? "Sim" : "Não");

  // Enfilera a segunda pilha
  ret = enQueue(queue_of_generics, P2);
  printf("Pilha adicionada: %s\n", ret ? "Sim" : "Não");

  printf("Fila esta vazia: %s \n", isEmptyQueue(queue_of_generics) ? "Sim" : "Não");

  // Remove uma das pilhas da fila
  // Cria outra pilha para guardar os valores retornados
  pPilha ppilhaRet;
  // criapilha(&ppilhaRet, num_elems, sizeof(int));
  t = nextQueueType(queue_of_generics);

  ret = deQueue(queue_of_generics, &ppilhaRet);
  if (ret){
    printf("Removido pPilha Pointer: [%p] \n", ppilhaRet);
  } else {
    printf("Falha ao remover a pilha\n");
    exit(1);
  }

  int valor = 0;

  if(ppilhaRet != NULL){

    for (int i=0; i < 5; i++) {
      ret = topo(ppilhaRet,&arr_of_int);
      if (!ret)
      printf ("ERRO topo ...\n");
      else
      printf ("OK topo %d\n", valor);

      ret = desempilha(ppilhaRet,&valor);
      if (!ret)
      printf ("ERRO desempilha ...\n");
      else
      printf ("OK desempilha %d...\n", valor);
    }
    destroipilha(&ppilhaRet);
    free(ppilhaRet);
  }

  printf("\nIgnora a ultima pilha que deve ser desalocado no destrutor\n");
  printf("\nFila esta vazia: %s \n", isEmptyQueue(queue_of_generics) ? "Sim" : "Não");
  printf("\nChama o destrutor destrutor.\n");

  // Destroi a fila
  destroyQueue(queue_of_generics);
  printf("\nFim do processo, fila destruida e toda de memoria desalocada.");
}
/*
 * Um funcao simples para fins de exemplicacao
 */
void testSimpleQueue(){
  unsigned char charValue = 'c';
  int intValue = 10;
  int* pInt = &intValue;
  float floatValue = 99.9;
  double doubleValue = 99.9;
  Queue queue = initQueue(5);

  enQueue(queue, charValue);
  enQueue(queue, intValue);
  enQueue(queue, pInt);
  enQueue(queue, floatValue);
  enQueue(queue, doubleValue);

  deQueue(queue, &charValue);
  enQueue(queue, &intValue);
  deQueue(queue, &pInt);
  deQueue(queue, &floatValue);
  deQueue(queue, &doubleValue);
  destroyQueue(queue);
}

int main(int argc, char* argv[]) {
  testSimpleQueue();
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