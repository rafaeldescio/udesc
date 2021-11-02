#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

#define SUCESSO 1
#define FRACASSO 0

int bubblesort(vsort *st_bubble) {
  st_bubble->nro_comparacoes = 0;
  st_bubble->nro_trocas = 0;
  int *tempArr = malloc(sizeof(int)*st_bubble->nro_elementos);
  if(tempArr == NULL) {
    return FRACASSO;
  }
  memcpy(tempArr, st_bubble->vEntrada, sizeof(int)*st_bubble->nro_elementos);
  for(int i = (st_bubble->nro_elementos - 1); i > 0; i--) {
    for(int j =0; j < i; j++) {
      if(tempArr[j] > tempArr[j+1]) {
        int aux = tempArr[j];
        tempArr[j] = tempArr[j+1];
        tempArr[j+1] = aux;
        st_bubble->nro_trocas++;
      }
      st_bubble->nro_comparacoes++;
     }
  }
  st_bubble->vOrdenado = tempArr;
  return SUCESSO;
}

int selectsort(vsort *st_select) {
  st_select->nro_comparacoes = 0;
  st_select->nro_trocas = 0;
  int *tempArr = malloc(sizeof(int)*st_select->nro_elementos);
  if(tempArr == NULL) {
    return FRACASSO;
  }
  memcpy(tempArr, st_select->vEntrada, sizeof(int)*st_select->nro_elementos);
  for (int i = 0; i < (st_select->nro_elementos - 1); i++) {
    int x = i;
    for (int j = (i+1); j < st_select->nro_elementos; j++) {
      if(tempArr[j] < tempArr[x]){
        x = j;
      }
      st_select->nro_comparacoes++;
    }
    if( x != i) {
      int aux = tempArr[i];
      tempArr[i] = tempArr[x];
      tempArr[x] = aux;
      st_select->nro_trocas++;
    }
  }
  st_select->vOrdenado = tempArr;
  return SUCESSO;
}

int insertsort(vsort *st_insert) {
  st_insert->nro_comparacoes = 0;
  st_insert->nro_trocas = 0;
  int *tempArr = malloc(sizeof(int)*st_insert->nro_elementos);
  if(tempArr == NULL) {
    return FRACASSO;
  }
  memcpy(tempArr, st_insert->vEntrada, sizeof(int)*st_insert->nro_elementos);
  for (int i = 1; i < st_insert->nro_elementos; i++) {
    int key = tempArr[i];
    int j = i - 1;
    while (j >= 0 && tempArr[j] > key) {
        tempArr[j + 1] = tempArr[j];
        j--;
        st_insert->nro_comparacoes++; 
    }
    j++;
    if(i != j){
      tempArr[j] = key;
      st_insert->nro_trocas++;
    }
  }
  st_insert->vOrdenado = tempArr;
  return SUCESSO;
}
