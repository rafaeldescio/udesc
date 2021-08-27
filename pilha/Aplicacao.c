#include "Pilha_publico.h"

void testIntegerStack(){
  printf("---------------------------------------\n");
  printf("Testando Pilha de Inteiros\n");
  // Cria um array de inteiros
  int arr_int[] = {11, 222, 33, 44, 55};
  int num_elems = sizeof(arr_int) / sizeof(arr_int[0]);

  // Cria um nova pilha para inteiros
  Stack *stack_of_ints = init(sizeof(arr_int[0]));

  // Adiciona os elementos do array na pilha
  int *added_int;
  for (int i = 0; i < num_elems; i++) {
    added_int = push(stack_of_ints, arr_int + i);
    if (added_int != NULL)
      printf("Adicionado: %d, %d \n", *added_int, *(arr_int + i));
  }
  printf("\n");
  // Remove os elementos da pilha
  int *removed_int;
  while ((removed_int = pop(stack_of_ints)) != NULL) {
    printf("Removido: %d \n", *removed_int);
  }
  printf("Fila esta vazia: %s \n", isEmpty(stack_of_ints) ? "Sim" : "Não");
  // Destroi a pilha
  destroy(stack_of_ints);
}

void testStringStack() {
  printf("---------------------------------------\n");
  printf("Testando Pilha de Strings\n");
  // Cria um array de strings
  char *arr_chars[] = {"abc", "def", "ghi", "jlk", "mno"};
  int num_elems = sizeof(arr_chars) / sizeof(arr_chars[0]);

  // Cria um nova pilha para inteiros
  Stack *stack_of_chars = init(sizeof(arr_chars[0]));

  // Adiciona os elementos do array na pilha
  char **added_char;
  for (int i = 0; i < num_elems; i++) {
    added_char = push(stack_of_chars, arr_chars + i);
    if (added_char != NULL)
      printf("Adicionado: %s, %s \n", *added_char, *(arr_chars + i));
  }
  printf("\n");
  // Remove os elementos da pilha
  char **removed_char;
  while ((removed_char = pop(stack_of_chars)) != NULL) {
    printf("Removido: %s \n", *removed_char);
  }
  printf("Fila esta vazia: %s \n", isEmpty(stack_of_chars) ? "Sim" : "Não");
  // Destroi a pilha
  destroy(stack_of_chars);
  printf("---------------------------------------\n");
}

void testUserStack(){
  
  int x, n;
  printf("Digite um inteiro decimal positivo: \n");
  scanf("\n%d", &n);
  Stack *P = init(sizeof(int));
  while (n != 0) {
    x = n % 2;
    printf("Num: %d, Bit: %d \n", n, x);
    int *y = push(P, &x);
    if(y != NULL)
      printf("Adicionado: %d\n", *y);
    n = n / 2;
  }
  printf("Correspondente ao binário : \n");
  int *removed_int;
  while ((removed_int = pop(P)) != NULL)
  {
    printf("%d", *removed_int);
  }
  while (!isEmpty(P)) {
      x = *((int *) pop(P));
      printf("Removido: %d\n ", x);
  }
  printf("\n\n");
}

int main(int argc, char* argv[]) {
  testIntegerStack();
  // ------------------------------------------------------
  printf("\n\n");
  // ------------------------------------------------------
  testStringStack();

  testUserStack();
  return 0;
}