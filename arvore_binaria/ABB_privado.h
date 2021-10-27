#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ABB.h"

#ifndef _ABB_PRIVADO_H
#define _ABB_PRIVADO_H

#define FAILURE 0
#define SUCCESS 1

typedef struct tree_element * TreeElement;
struct tree_element {
  // Conteudo do elemento armazenado
  void *element;
  size_t typesize;
  TreeElement left;
  TreeElement right;
  TreeElement parent;
};


struct bsTree {
  size_t element_size;
  // É o elemento raiz
  TreeElement root;

};


#endif