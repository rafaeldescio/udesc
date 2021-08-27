#include "Pilha_publico.h"

// #define ENABLE_DEBUG_LOG    // disable DEBUG_LOG


#ifdef ENABLE_DEBUG_LOG
#define LOG_D(fmt, args...) \
  {                           \
    printf("D:");             \
    fprintf(stdout, fmt, args);        \
  }
#else
#define LOG_D(fmt, args...) // faz nada
#endif



/* Retorna um ponteiro para o elemento da posicão sem remover ele da pilha. */
void *get(Stack *s, int position);
