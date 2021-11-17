
#include "LDSE.h"

typedef struct LDSE{
    struct NoLDSE *inicio;
    int tamanho_info;
}LDSE;

typedef struct NoLDSE{
    void *dados;
    struct NoLDSE *proximo;
    int tipo;
}NoLDSE;
