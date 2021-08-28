#include "Pilha_publico.h"
#include "Aplicacao_privado.h"

struct TestStruct {
  char* test_data;
};

void printInt ( int y, void* x ) {
  printf("Posicao:  %d - Elemento: %d\n", y, *((int *) x));
}

void printString ( int y, void* x ) {
  printf("Posicao:  %d - Elemento: %s\n", y, *((char **) x));
}

void printTestStruct ( int y, void* x ) {
  printf("Posicao:  %d - Elemento: %s\n", y, ((struct TestStruct *) x)->test_data);
}

void testStruckStack(){
  printf("Testando Pilha de TestStruct: \n");
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
  struct TestStruct ts1 = { .test_data = "teste struct 01" };
  struct TestStruct ts2 = { .test_data = "teste struct 02" };
  struct TestStruct ts3 = { .test_data = "teste struct 03" };
  struct TestStruct arr_structs[] = {ts1, ts2, ts3};

  int num_elems = sizeof(arr_structs) / sizeof(arr_structs[0]);

  // Cria um nova pilha para TestStruct
  Stack stack_of_structs = init(sizeof(arr_structs[0]), num_elems);

  // Adiciona os elementos do array na pilha
  for (int i = 0; i < num_elems; i++) {
    printf("Adicionando: %s \n",  (arr_structs + i)->test_data);
    push(stack_of_structs, arr_structs + i);
  }
  printf("\nImprimindo a pilha:\n");
  printStack(printTestStruct, stack_of_structs);
  printf("\n\n");
  printf("Removendo da Pilha de TestStruct: \n");
  // Remove os elementos da pilha
  struct TestStruct *removed_struct;
  while ((removed_struct = pop(stack_of_structs)) != NULL) {
    printf("Removido: %s \n", removed_struct->test_data);
  }
  printf("Pilha esta vazia: %s \n", isEmpty(stack_of_structs) ? "Sim" : "Não");
  // Destroi a pilha
  destroy(stack_of_structs);
  // #OBS1
  // free(ts1);
  // free(ts2);
  // free(ts3);
}

void testIntegerStack(){
  printf("Testando Pilha de Inteiros\n");
  // Cria um array de inteiros
  int arr_int[] = {11, 222, 33, 44, 55};
  int num_elems = sizeof(arr_int) / sizeof(arr_int[0]);

  // Cria um nova pilha para inteiros
  Stack stack_of_ints = init(sizeof(arr_int[0]), num_elems);

  // Adiciona os elementos do array na pilha
  for (int i = 0; i < num_elems; i++) {
    printf("Adicionando: %d \n",  *(arr_int + i));
    push(stack_of_ints, arr_int + i);
  }
  printf("\nImprimindo a pilha:\n");
  printStack(printInt, stack_of_ints);
  printf("\n\n");
  printf("Removendo da Pilha de Inteiros: \n");
  // Remove os elementos da pilha
  int *removed_int;
  while ((removed_int = pop(stack_of_ints)) != NULL) {
    printf("Removido: %d \n", *removed_int);
  }
  printf("Pilha esta vazia: %s \n", isEmpty(stack_of_ints) ? "Sim" : "Não");
  // Destroi a pilha
  destroy(stack_of_ints);
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

void testUserStack(){
  // Exemplo apresentando em sala
  long long int x, n;
  printf("Digite um inteiro decimal positivo: \n");
  scanf("\n%lld", &n);
  Stack P = init(sizeof(long long int), 64);
  while (n != 0) {
    x = n % 2;
    printf("Num: %lld, Bit: %lld \n", n, x);
    printf("Adicionando: %lld\n", x);
    push(P, &x);
    n = n / 2;
  }
  printf("Correspondente ao binário : \n");
  // Outra forma de remover
  // int *removed_int;
  // while ((removed_int = pop(P)) != NULL)
  // {
  //   printf("%d", *removed_int);
  // }
  while (!isEmpty(P)) {
      x = *((long *) pop(P));
      printf(" %lld", x);
  }
  printf("\n\n");
  destroy(P);
}

int main(int argc, char* argv[]) {
  printf("---------------------------------------\n");
  testStruckStack();
  // ------------------------------------------------------
  printf("\n\n");
  printf("---------------------------------------\n");
  // ------------------------------------------------------
  testIntegerStack();
  // ------------------------------------------------------
  printf("\n\n");
  printf("---------------------------------------\n");
  // ------------------------------------------------------
  testStringStack();
  // ------------------------------------------------------
  printf("\n\n");
  printf("---------------------------------------\n");
  // ------------------------------------------------------
  testUserStack();
  return 0;
}