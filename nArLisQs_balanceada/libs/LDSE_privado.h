
#include "LDSE.h"

typedef struct CounterLDSE{
    int compara;
} CounterLDSE;

typedef struct LDSE{
    struct NoLDSE *inicio;
    int tamanho_info;
    struct CounterLDSE *contador;
}LDSE;

typedef struct NoLDSE{
    void *dados;
    struct NoLDSE *proximo;
    int tipo;
    struct CounterLDSE *contador;
}NoLDSE;
