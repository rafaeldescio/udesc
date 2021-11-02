#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

#define SUCESSO 1
#define FRACASSO 0

int main(int argc, char **argv) {
    int op, numero,prior;
    int *vLido, *vOrdenado=NULL;
    int elementos;
    vsort bubble, select, insert;

    fscanf(stdin, "%i", &elementos);
    printf("Número de elementos: %i\n", elementos);
    printf("Vetor de Entrada:\n\t\t\t");
    vLido = (int *) malloc (elementos*sizeof(int));
    for (int i=0; i < elementos; i++) {
       fscanf(stdin, "%i", &vLido[i]);
       printf ("%d ", vLido[i]);
    }

    // Bubble Sort
    bubble.vEntrada = vLido;
    bubble.nro_elementos = elementos;
    if (bubblesort(&bubble)) {
      printf("\nBubble SUCESSO\n \
              \tNúmero de trocas: %d\n \
              \tNúmero de comparações: %d \n \
              \tVetor Ordenado:\n\t\t", \
              bubble.nro_trocas, bubble.nro_comparacoes);
      for (int i=0; i < elementos; i++) {
        printf ("%d ", bubble.vOrdenado[i]);
      }
    } else {
      printf("\nFRACASSO\n");
    }
    free(bubble.vOrdenado);

    // Select Sort
    select.vEntrada = vLido;
    select.nro_elementos = elementos;
    if (selectsort(&select)) {
      printf("\nSelect SUCESSO\n \
              \tNúmero de trocas: %d\n \
              \tNúmero de comparações: %d \n \
              \tVetor Ordenado:\n\t\t", \
              select.nro_trocas, select.nro_comparacoes);
      for (int i=0; i < elementos; i++) {
        printf ("%d ", select.vOrdenado[i]);
      }
    } else {
      printf("\nFRACASSO\n");
    }
    free(select.vOrdenado);


    // insert Sort
    insert.vEntrada = vLido;
    insert.nro_elementos = elementos;
    if (insertsort(&insert)) {
      printf("\nInsert SUCESSO\n \
              \tNúmero de trocas: %d\n \
              \tNúmero de comparações: %d \n \
              \tVetor Ordenado:\n\t\t", \
              insert.nro_trocas, insert.nro_comparacoes);
      for (int i=0; i < elementos; i++) {
        printf ("%d ", insert.vOrdenado[i]);
      }
    } else {
      printf("\nFRACASSO\n");
    }
    free(insert.vOrdenado);

    printf("\n");

    free(vLido);

    return 0;
}
