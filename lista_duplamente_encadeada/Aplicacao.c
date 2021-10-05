#include "Aplicacao.h"
typedef struct TestStruct * pTestStruct;
struct TestStruct {
  char* test_data;
} ;

/**
%c	Character
%d	Signed integer
%e or %E	Scientific notation of floats
%f	Float values
%g or %G	Similar as %e or %E
%hi	Signed integer (short)
%hu	Unsigned Integer (short)
%i	Unsigned integer
%l or %ld or %li	Long
%lf	Double
%Lf	Long double
%lu	Unsigned int or unsigned long
%lli or %lld	Long long
%llu	Unsigned long long
%o	Octal representation
%p	Pointer
%s	String
%u	Unsigned int
%x or %X	Hexadecimal representation
%n	Prints nothing
%%	Prints % character
*/

void printTypeSpecifier(void* el, int t){
  switch (t){
    case TYPENAME_UNSIGNED_CHAR:
    case TYPENAME_CHAR:
    case TYPENAME_SIGNED_CHAR:
      printf("[%c]", *((char*) el));
      break;
    case TYPENAME_SHORT_INT:
      printf("[%hi]", *((short int*) el));
      break;
    case TYPENAME_UNSIGNED_SHORT_INT:
      printf("[%hu]", *((unsigned short int*) el));
      break;
    case TYPENAME_INT:
      printf("[%d]", *(( int*) el));
      break;
    case TYPENAME_UNSIGNED_INT:
      printf("[%i]", *(( unsigned int*) el));
      break;
    case TYPENAME_LONG_INT:
      printf("[%ld]", *(( long int*) el));
      break;
    case TYPENAME_UNSIGNED_LONG_INT:
      printf("[%lu]", *((unsigned long int*) el));
      break;
    case TYPENAME_LONG_LONG_INT:
      printf("[%lld]", *((long long int*) el));
      break;
    case TYPENAME_UNSIGNED_LONG_LONG_INT:
      printf("[%llu]", *((unsigned long long int*) el));
      break;
    case TYPENAME_FLOAT:
      printf("[%f]", *((float*) el));
      break;
    case TYPENAME_DOUBLE:
      printf("[%lf]", *((double*) el));
      break;
    case TYPENAME_LONG_DOUBLE:
      printf("[%Lf]", *((long double*) el));
      break;
    case TYPENAME_POINTER_TO_CHAR:
      printf("[%s]", *((char**) el));
      break;
    case TYPENAME_POINTER_TO_VOID:
      printf("[%p]", el);
      break;
    case TYPENAME_POINTER_TO_INT:
      printf("[%d]", **((int**)el));
      break;
    case TYPENAME_CUSTOM_STACK:
      printf("[%p]", el);
      break;
    case TYPENAME_CUSTOM_STRUCT:
      printf("[%s]", (*(pTestStruct*) el)->test_data);
      break;
    case TYPENAME_UNKNOWN:
    default:
      printf("desconhecido");
  }
}

void printAll(void* element, TypeName type, size_t position){
  printf("Posicao %lu: ", position);
  printTypeSpecifier(element, type);
  printf("\n");
}

void testGenericList(){
  printf("Testando Fila de Generica\n");
  // Cria um array de inteiros
  int arr_int[] = {11, 222, 33, 44, 55};
  
  int num_elems = sizeof(arr_int) / sizeof(arr_int[0]);
  int ret = 0;

  // Variaveis para guardarmos os retornos
  int retInt = 0;
  char charRet = 'z';
  char* stringRet = "zxy";

  // Cria um nova lista
  pList genericList;
  initList(&genericList);

  // Adiciona os elementos do array de inteiros na fila
  for (int i = 0; i < num_elems; i++) {
    printf("Adicionando: %d \n",  *(arr_int + i));
    int val = arr_int[i];
    pushList(genericList, val);    
  }
  printList(genericList, printAll);
  
  printf("\n\nVamos remover alguns elementos da Fila: \n");

  // Remove os elementos da fila
  
  ret = shiftList(genericList, &retInt);
  if(ret)
    printf("Removido elemento: [%d] \n", retInt);    
  
  // Descomentente para remover um invalido,
  // ret = peekAtList(genericList, -1, &retInt);
  //

  ret = peekAtList(genericList, 1, &retInt);
  if(ret)
    printf("Retornado: [%d] \n", retInt);  

  ret = removeAtList(genericList, 0, &retInt);
  if(ret)
    printf("Removido posicao 0: [%d] \n", retInt);  

  printf("Resetando a lista\n");
  resetList(&genericList);
  printf("Lista resetada\n");
  printList(genericList, printAll);
  
  printf("\n\nAdicionando novos elementos na Fila: \n");
  int new_number = 66;
  int new_number2 = 77;
  double new_number3 = 929.1;
  char new_char = 'y';
  char* new_char_vector = "abc";
  
  ret = pushList(genericList, new_number);
  if (ret)
    printf("Valor adicionado [%d]\n", new_number);
  pushList(genericList, new_number2);
  if (ret)
    printf("Valor adicionado [%d]\n", new_number2);
  pushList(genericList, new_number3);
  if (ret)
    printf("Valor adicionado [%f]\n", new_number3);
  pushList(genericList, new_char);
  if (ret)
    printf("Valor adicionado [%c]\n", new_char);
  
  printList(genericList, printAll);

  printf("\nTentando adicionar um elemento criado na aplicacao.c: \n");
  
  // Cria um elemento struct, que vai ser ignorado
  struct TestStruct ts1 = { .test_data = "teste struct 01" };

  ret = pushList(genericList, &ts1);
  printf("Adicionou: %s \n\n", ret ? "Sim" : "Não");
  
  printf("Voltamos adicionar elementos validos, agora um string: \n");
  ret = pushList(genericList, new_char_vector);
  if (ret)
    printf("Valor adicionado [%s]\n", new_char_vector);\
  int oT = 923932;
  ret = addAtList(genericList, 3, oT);
  if (ret)
    printf("Valor adicionado na posicao 3: [%d]\n", oT);\
  printList(genericList, printAll);
  //
  // Comeca a remover os elementos
  //

  printList(genericList, printAll);

  printf("\nRemovendo um elemento tipados.\n");
  // Remove usando a funcao tipada, retornando o valor retornado
  ret = shiftList(genericList, &retInt);
  if(ret){
    printf("Removido Typed Int: [%d] \n", retInt);
  } else {
    printf("Falha ao remover o int\n");
    exit(1);
  }

  // Remove usando a funcao tipada, retornando o valor retornado
  ret = shiftList(genericList, &retInt);
  if(ret){
    printf("Removido Typed Int: [%d] \n", retInt);
  } else {
    printf("Falha ao remover o int\n");
    exit(1);
  }

  double doubleRet;
  ret = shiftList(genericList, &doubleRet);
  if (ret){
    printf("Removido Typed Double: [%lf] \n", doubleRet);
  } else {
    printf("Falha ao remover o double\n");
    exit(1);
  }

  ret = shiftList(genericList, &retInt);
  if (ret){
    printf("Removido Typed Int: [%d] \n", retInt);
  } else {
    printf("Falha ao remover o int\n");
    exit(1);
  }
  ret = shiftList(genericList, &charRet);
  if (ret){
    printf("Removido Typed Char: [%c] \n", charRet);
  } else {
    printf("Falha ao remover o char\n");
    exit(1);
  }
  printList(genericList, printAll);
  ret = popList(genericList, &stringRet);
  if (ret){
    printf("Removido Typed Char Pointer: [%s] \n", stringRet);
  } else {
    printf("Falha ao remover a string\n");
    exit(1);
  }
  
  printf("Fila esta vazia: %s \n", isEmptyList(genericList) ? "Sim" : "Não");

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

  // Adiciona a primeira pilha no comeco da lista
  ret = unshiftList(genericList, P);
  printf("\nPilha adicionada: %s\n", ret ? "Sim" : "Não");

  // Adiciona a segunda pilha no final da lista
  ret = pushList(genericList, P2);
  printf("Pilha adicionada: %s\n", ret ? "Sim" : "Não");

  // Remove uma das pilhas da fila
  // Cria outro pPilha para guardar os valores retornados
  pPilha retpPilhaRet;
  printList(genericList, printAll);
  ret = shiftList(genericList, &retpPilhaRet);
  if (ret){
    printf("Removido pPilha Pointer: [%p] \n", retpPilhaRet);
  } else {
    printf("Falha ao remover a pilha\n");
    exit(1);
  }

  int valor = 0;

  if(retpPilhaRet != NULL){

    for (int i=0; i < 5; i++) {
      ret = topo(retpPilhaRet, &arr_of_int);
      if (!ret)
      printf ("ERRO topo ...\n");
      else
      printf ("OK topo %d\n", valor);

      ret = desempilha(retpPilhaRet, &valor);
      if (!ret)
      printf ("ERRO desempilha ...\n");
      else
      printf ("OK desempilha %d...\n", valor);
    }
    destroipilha(&retpPilhaRet);
    free(retpPilhaRet);
  }

  printf("\nFila esta vazia: %s \n", isEmptyList(genericList) ? "Sim" : "Não");
  printf("\nChama o destrutor.\n");

  // Destroi a fila
  destroyList(&genericList);

  printf("\nFila esta vazia: %s \n", isEmptyList(genericList) ? "Sim" : "Não");
  
  // Destroi a pilha que não foi usada
  destroipilha(&P2);
  free(P2);

  printf("\nFim do processo, lista destruida e toda de memoria desalocada.");
}

/*
 * Um funcao simples para fins de exemplicacao
 */
void testSimpleList(){
  unsigned char charValue = 'c';
  int intValue = 10;
  int* pInt = &intValue;
  float floatValue = 99.9;
  double doubleValue = 99.9;
  pList list;
  initList(&list);

  pushList(list, charValue);
  pushList(list, intValue);
  pushList(list, pInt);
  pushList(list, floatValue);
  pushList(list, doubleValue);

  shiftList(list, &charValue);
  shiftList(list, &intValue);
  shiftList(list, &pInt);
  shiftList(list, &floatValue);
  shiftList(list, &doubleValue);

  isEmptyList(list);

  pushList(list, charValue);
  pushList(list, intValue);
  pushList(list, pInt);
  pushList(list, floatValue);
  pushList(list, doubleValue);

  popList(list, &doubleValue);
  popList(list, &floatValue);
  popList(list, &pInt);
  popList(list, &intValue);
  popList(list, &charValue);

  unshiftList(list, charValue);
  unshiftList(list, intValue);
  unshiftList(list, pInt);
  unshiftList(list, floatValue);
  unshiftList(list, doubleValue);

  printList(list, printAll);
  
  shiftList(list, &doubleValue);
  shiftList(list, &floatValue);
  shiftList(list, &pInt);
  shiftList(list, &intValue);
  shiftList(list, &charValue);

  pushList(list, charValue);
  pushList(list, intValue);
  pushList(list, pInt);
  pushList(list, floatValue);
  pushList(list, doubleValue);

  char* stringValue = "string value";
  addAtList(list, 2, stringValue);
  printList(list, printAll);
  printListReverse(list, printAll);
  
  peekAtList(list, 2, &stringValue);
  printf("peek %s\n", stringValue);
  peekFirstList(list, &charValue);
  printf("peek %c\n", charValue);
  peekLastList(list, &doubleValue);
  printf("peek %lf\n", doubleValue);
  size_t size = sizeList(list);
  printf("Tamanho da lista %ld \n\n", size);

  resetList(&list);

  size = sizeList(list);
  printf("Tamanho da lista %ld \n\n", size);

  destroyList(&list);
}

int main(int argc, char* argv[]) {
  testSimpleList();
  printf("\n\n");
  printf("---------------------------------------\n");
  // ------------------------------------------------------
  testGenericList();
  // ------------------------------------------------------
  printf("\n\n");
  printf("---------------------------------------\n");
  printf("---------------------------------------\n");
  return 0;
}