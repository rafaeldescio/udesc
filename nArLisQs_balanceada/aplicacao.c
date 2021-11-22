#include <stdlib.h>
#include "aplicacao.h"

#define SUCESSO 1
#define FRACASSO 0

void imprime(void *p)
{
  //printf("%p", *(p));
  //imprimeInt((pLDSE) p);
  //printf("(");
  imprimeChar((pLDSE) p);
  //printf(")");
}

// void imprime(void *p)
// {
//   printf("%c", *((char *)p));
// }

// int comparaString(void *dado1, void *dado2)
// {
//   char* s1 = *((char *)dado1);
//   char* s2 = *((char *)dado2);
//   return n1 - n2;
// }

int comparaDados(void *dado1, void *dado2)
{
  int n1 = *((int *)dado1);
  int n2 = *((int *)dado2);
  return n1 - n2;
}

// ***************************   ***************************
//
// ***************************   ***************************
void inputData (pArLis ptr, char **argv) {
  char *bufrb = NULL;
  FILE *ptrfile = NULL;
  int total=0;
  int cont = 0;
  int valor = 0;

  // Le o arquivo do enigma completo, caracter a caracter.
  ptrfile = fopen(argv[1],"rb");
  if (ptrfile==NULL) {
    printf("ERRO: Abertura de arquivo\n");
    assert(1);
  }

  bufrb = malloc(sizeof(char));
  while (bufrb!=NULL) {
    if (!fread(bufrb,sizeof(char),1,ptrfile)) {
      // printf("ERRO: fread (%d)\n", valor);
      // if((insereArLis(ptr, &valor, comparaDados))){
      //    total++;
      // }
      bufrb=NULL;
    } else {
      // printf("Buffer %.25s\n", bufrb);
      //int letra = (int)bufrb[0];
      //printf("{%c,%d}", bufrb[0], bufrb[0]);
      switch (cont) {
        case 0:
          //printf("%c%d", bufrb[0], atoi(bufrb));
          //printf("C1 %c",bufrb[0]);
          valor = 100*atoi(bufrb);
          cont++;
          break;
        case 1:
          //printf("C2 %c",bufrb[0]);
          valor = valor+10*atoi(bufrb);
          cont++;
          break;
        case 2:
          //printf("C3 %c",bufrb[0]);
          valor = valor+atoi(bufrb);
          cont++;
          break;
        default:
          printf("ERRO\n");
      }
      //printf("%c%d", bufrb[0], atoi(bufrb));
      if (cont > 2) {
         //int nvalor = 0;
         printf("%c", (char)valor);
         cont = 0;
         //printf("%ld", strtol((char*)valor,NULL,10));
         if((insereArLisBal(ptr, &valor, comparaDados))){
            total++;
         }
      }
  }}
  free(bufrb);
  //printf("\n");
}


// ***************************   ***************************
//
// ***************************   ***************************
int main(int argc, char **argv){
  int op, numero,prior;
  pArLis ptr;
  int novo;
  char remover[100];
  char buscar[100];

  if (argc <= 1) {
    //printf ("ERRO: ./aplicacao <int0> <int1> ... <intN> <char0> <char1> ... <charN> \n");
    printf ("ERRO: ./aplicacao <filename> \n");
    return 1;
  }

  if((criaArLisBal(&ptr, sizeof(int)))==FRACASSO) {
    printf("Erro na criação da arvore\n");
    exit(1);
  }

  inputData(ptr, argv);
  printf("\n**************\n");
  printf("**************\n");

  strcpy(buscar, "PAA!");
  if(buscaArLis(ptr, &buscar)){
    printf("Buscado com sucesso (%s)\n", buscar);
  } else {
    printf("Erro na busca da palavra (%s)\n", buscar);
  }

  strcpy(buscar, "Sondagem");
  if(buscaArLis(ptr, &buscar)){
    printf("Buscado com sucesso (%s)\n", buscar);
  } else {
    printf("Erro na busca da palavra (%s)\n", buscar);
  }

  strcpy(buscar, "2");
  if(buscaArLis(ptr, &buscar)){
    printf("Buscado com sucesso (%s)(%d)\n", buscar, FRACASSO);
  } else {
    printf("Erro na busca da palavra (%s)\n", buscar);
  }

  strcpy(buscar, "novo");
  if(buscaArLis(ptr, &buscar)){
    printf("Buscado com sucesso (%s)\n", buscar);
  } else {
    printf("Erro na busca da palavra (%s)\n", buscar);
  }

  strcpy(buscar, "fingidor.");
  if(buscaArLis(ptr, &buscar)){
    printf("Buscado com sucesso (%s)\n", buscar);
  } else {
    printf("Erro na busca da palavra (%s)\n", buscar);
  }

  strcpy(buscar, "bem,");
  if(buscaArLis(ptr, &buscar)){
    printf("Buscado com sucesso (%s)\n", buscar);
  } else {
    printf("Erro na busca da palavra (%s)\n", buscar);
  }


  strcpy(remover, "de");
  if(removeArLisBal(ptr, &remover)){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }

  strcpy(remover, "um");
  if(removeArLisBal(ptr, &remover)){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }

  strcpy(remover, "O");
  if((removeArLisBal(ptr, &remover))){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }

  strcpy(remover, "completamente");
  if((removeArLisBal(ptr, &remover))){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }

  strcpy(remover, "calhas");
  if((removeArLisBal(ptr, &remover))){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }

  strcpy(remover, "acontecimento");
  if((removeArLisBal(ptr, &remover))){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }

  strcpy(remover, "Nunca");
  if(removeArLisBal(ptr, &remover)){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }

  strcpy(remover, "Nunca");
  if(removeArLisBal(ptr, &remover)){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }

  strcpy(remover, "pedra");
  if(removeArLisBal(ptr, &remover)){
    printf("Removido com sucesso (%s)\n", remover);
  } else {
    printf("Erro na remocao (%s)\n", remover);
  }


  printf("**************\n");
  printf("**************\n");

  printf("\nImpressao ArLis (traduzida): ");
  percursoArLisBal(ptr, imprime);
  nivelArLis(ptr);
  imprimeRelatorio(ptr);
  printf("\n");

  destroiArLisBal(&ptr);
  return 0;
}
