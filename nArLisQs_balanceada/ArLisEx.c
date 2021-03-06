#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ArLis_privado.h"
#define true 1
#define false 0


int criarContador(CounterArLis ** c){
    (*c) = (CounterArLis *)malloc(sizeof(CounterArLis));
    if((*c) == NULL)
        return false;
    (*c)->arrayInsere = malloc(sizeof(int));
    (*c)->sizeArrayInsere = 1;
    (*c)->insere = 0;
    (*c)->indexInsere = 0;
    (*c)->arrayRemove = malloc(sizeof(int));
    (*c)->sizeArrayRemove = 1;
    (*c)->remove = 0;
    (*c)->indexRemove = 0;
    (*c)->arrayPercorre = malloc(sizeof(int));
    (*c)->sizeArrayPercorre = 1;
    (*c)->percorre = 0;
    (*c)->indexPercorre = 0;
    (*c)->arrayBuscaNivel = malloc(sizeof(int));
    (*c)->sizeArrayBuscaNivel = 1;
    (*c)->buscaNivel = 0;
    (*c)->indexBuscaNivel = 0;
    (*c)->contagemLista = 0;
    return true;
}

int criaArLisBal(ppArLis pp, int tamInfo){
    /* aloca descritor */
	(*pp) = (ArLis *)malloc(sizeof(ArLis));
    if( (*pp) == NULL)
    	return false;
    if(criaLDSE(&(*pp)->bufLista, tamInfo) == false){
        return false;
    }
    if(criarContador(&(*pp)->contador) == false){
        return false;
    }
	(*pp)->tamInfo = tamInfo ;
	(*pp)->raiz = NULL;
	return true;
}

int reiniciaContadorArLis(CounterArLis* c){
	if( c == NULL)
		return false;
	free(c->arrayInsere);
    free(c->arrayRemove);
    free(c->arrayPercorre);
    free(c->arrayBuscaNivel);
    c->arrayInsere = malloc(sizeof(int));
    c->arrayInsere[0] = 0;
    c->sizeArrayInsere = 1;
    c->insere = 0;
    c->indexInsere = 0;
    c->arrayRemove = malloc(sizeof(int));
    c->sizeArrayRemove = 1;
    c->remove = 0;
    c->indexRemove = 0;
    c->arrayPercorre = malloc(sizeof(int));
    c->sizeArrayPercorre = 1;
    c->percorre = 0;
    c->indexPercorre = 0;
    c->arrayBuscaNivel = malloc(sizeof(int));
    c->sizeArrayBuscaNivel = 1;
    c->buscaNivel = 0;
    c->indexBuscaNivel = 0;
    c->contagemLista = 0;
    return true;
}
int destroiContadorArLis(CounterArLis** c){
	if( (*c) == NULL)
		return false;
	free((*c)->arrayInsere);
    free((*c)->arrayRemove);
    free((*c)->arrayPercorre);
    free((*c)->arrayBuscaNivel);
	free((*c));
	(*c) = NULL;
    return true;
}

int destroiNo(ppNoArLis c){
    if((*c) == NULL){
        return true;
    }
    destroiNo(&(*c)->esquerda);
    destroiNo(&(*c)->centro);
    destroiNo(&(*c)->direita);
    destroiLDSE(&(*c)->lista);
    destroiContadorArLis(&(*c)->contador);
    free((*c));
    (*c) = NULL;
    return true;
}

int reiniciaArLisBal(pArLis p){
	NoArLis *aux, *left, *right, *middle;

	if(p == NULL)
		return false;

	/* caminha pela arvore e desaloca todos os n???s */
	destroiNo(&p->raiz);
    reiniciaContadorArLis(p->contador);
    reiniciaLDSE(p->bufLista);
	return true;
}

int destroiArLisBal(ppArLis pp){
	if( (*pp) == NULL)
		return false;
    imprimeRelatorio((*pp));
    reiniciaArLisBal((*pp));
    destroiContadorArLis(&(*pp)->contador);
    destroiLDSE(&(*pp)->bufLista);
    free((*pp)->bufLista);
    free((*pp)->contador);
	free((*pp));
    (*pp) = NULL;
    return true;
}

int criaNo(pLDSE* list, ppNoArLis parent, ppNoArLis node){
    (*node) = (NoArLis *)malloc(sizeof(NoArLis));
    if ((*node) == NULL){
        return false;
    }
    if(criarContador(&(*node)->contador) == false){
        return false;
    }

    (*node)->lista = (*list);
    (*node)->pai = (*parent);
    (*node)->esquerda = NULL;
    (*node)->centro = NULL;
    (*node)->direita = NULL;
    return true;
}

int emptyChildNode(pArLis p, NoArLis** node){
    if((*node) == NULL){
        return true;
    }
    p->contador->remove++;
    (*node)->contador->remove++;
    if( (*node)->esquerda != NULL){
        (*node)->esquerda->contador->remove++;
        return false;
    }
    if(  (*node)->centro != NULL){
        (*node)->centro->contador->remove++;
        return false;
    }
    if( (*node)->direita != NULL){
        (*node)->direita->contador->remove++;
        return false;
    }
    return true;
}

int getLowLevelFreeNode(pArLis p, ppNoArLis node, int* height,  ppNoArLis* parent, ppNoArLis* child)
{
    
    (p->contador)->insere++;
    if ((*node) == NULL) {
        (*height) = 0;
        (*child) = node;
        return true;
    } else {
        ((*node)->contador)->insere++;
        ppNoArLis pLeft_child, pLeft_parent, pMiddle_child, pMiddle_parent, pRight_child, pRight_parent;
        pLeft_parent = pMiddle_parent = pRight_parent = node;
        int left_height = 0, middle_height = 0, right_height = 0;
        //  printf("antes %p %p\n", &(*pLeft_child));
        getLowLevelFreeNode(p, &(*node)->esquerda, &left_height, &pLeft_parent, &pLeft_child);
        getLowLevelFreeNode(p, &(*node)->centro, &middle_height, &pMiddle_parent, &pMiddle_child);
        getLowLevelFreeNode(p, &(*node)->direita, &right_height, &pRight_parent, &pRight_child);
       
        if (left_height <= middle_height && left_height <= right_height) {
            // printf("selecionado da esquerda %p %p\n", &(*node)->esquerda, &(*pLeft_child));
             (*child) = pLeft_child;
             (*parent) = pLeft_parent;
             (*height) = (left_height + 1);
             return true;

        }
        if (middle_height <= left_height && middle_height <= right_height) {
            // printf("selecionado do meio %p %p\n", &(*node)->centro, &(*pMiddle_child));
            (*child) = pMiddle_child;
            (*parent) = pMiddle_parent;
            (*height) = (middle_height + 1);
            return true;
        }
        // printf("selecionado do direita %p %p\n", &(*node)->direita, &(*pRight_child));
        (*child) = pRight_child;
        (*parent) = pRight_parent;
        (*height) = (right_height + 1);
        return true;
    }
}
int maxHeight(pArLis p, NoArLis* node, int type)
{
    if(type == 0){
        p->contador->buscaNivel++;
    }else if(type == 1){
        p->contador->remove++;
    } else if(type == 2){
        p->contador->percorre++;
    }
 
    if (node == NULL)
        return 0;
    else {
        if(type == 0){
            (node->contador)->buscaNivel++;
        }else if(type == 1){
            (node->contador)->remove++;
        } else if(type == 2){
            (node->contador)->percorre++;
        }
        int left_height = maxHeight(p, node->esquerda, type);
        int middle_height = maxHeight(p, node->centro, type);
        int right_height = maxHeight(p, node->direita, type);
        // printf("%p node left %d\n", node, left_height);
        // printf("%p node middle %d\n", node, middle_height);
        // printf("%p node right %d\n", node, right_height);
       
        if (left_height >= middle_height && left_height >= right_height) {
            return (left_height + 1);
        }
        if (middle_height >= left_height && middle_height >= right_height) {
            return (middle_height + 1);
        }
        return (right_height + 1);
    }
}
int _internalInsereBalanceado(pArLis p, pLDSE* list, NoArLis* parent, NoArLis** node )
{   
    int ret = false;
    // ?? Raiz
    if ((*node) == NULL)
    {
        return criaNo(list, &parent, node);
    }
    pNoArLis pNo = NULL;
    ppNoArLis ppParent = &pNo;
    ppNoArLis ppChild = NULL;
    int height = 0;
    getLowLevelFreeNode(p, node, &height, &ppParent, &ppChild);
    if((*ppParent) == NULL){
        return criaNo(list, &parent, ppChild);
    } else{
        return criaNo(list, ppParent, ppChild);
    }
}


int _insereArLisBal(pArLis p, void *novo, int (* cmp)(void *p1, void *p2)){

    if( p->bufLista == NULL){
        pLDSE tempList;
        int retLdse = criaLDSE(&tempList, sizeof(p->tamInfo));    
        if(retLdse == false) {
            return false;
        }
        p->bufLista = tempList;

    }
    int space = 32, new_line = 10, max_val = 123;
    if (cmp(novo, &new_line) != 0 && (cmp(novo, &space) < 0 || cmp(novo, &max_val) > 0)) {
        // printf("\nFalha ao inserir - Valor inv??lido [%d]\n", *((int*)novo));
        return false;
    }
    int ret = insereFim(p->bufLista, novo);
    
    if (cmp(novo, &space) == 0 ||  cmp(novo, &new_line) == 0) {
        ret = _internalInsereBalanceado(p, &p->bufLista, NULL, &p->raiz);
        p->bufLista = NULL;
    }
 
    return ret;
}

int insereArLisBal(pArLis p, void *novo, int (* cmp)(void *p1, void *p2)){
    CounterArLis* contador = p->contador;
    int currentInsereCount = contador->insere;
    int ret = _insereArLisBal(p, novo, cmp);
    int diff = contador->insere - currentInsereCount;
    int idx = 0;
    if(diff > 0) {
        idx = contador->indexInsere++;
        if(idx >= contador->sizeArrayInsere ){
            contador->sizeArrayInsere *= 2;
            contador->arrayInsere = realloc( contador->arrayInsere, contador->sizeArrayInsere * sizeof(int));
        }
        contador->arrayInsere[idx] = diff;
    }
    return ret;
}

int execHeight(pArLis p, NoArLis* node, int compHeight, int height, void (* processa)(void *p))
{
    (p->contador)->percorre++;
    if (node == NULL)
        return 0;
    else {
        ((node)->contador)->percorre++;
        if(compHeight == height){
            processa(node->lista);
        }
        // ignora os n??veis superiores
        if(compHeight > height){
            return 0;
        }

        int left_height = execHeight(p, node->esquerda, compHeight+1, height, processa);
        int middle_height = execHeight(p,node->centro,  compHeight+1, height, processa);
        int right_height = execHeight(p, node->direita, compHeight+1, height, processa);
        if (left_height <= middle_height && left_height <= right_height) {
            return (left_height + 1);
        }
        if (middle_height <= left_height && middle_height <= right_height) {
            return (middle_height + 1);
        }
        return (right_height + 1);       
    }
}


int _percursoArLisBal(pArLis pa, void (* processa)(void *p)){

    int ret = true;
    int max_height = maxHeight(pa, pa->raiz, 2);
    printf("\n");
    for(int i = 0;  i < max_height ; i++){
        execHeight(pa, pa->raiz, 0, i, processa);
    }
    return true;
}

int percursoArLisBal(pArLis pa, void (* processa)(void *p)){
    CounterArLis* contador = pa->contador;
    int currentPercorreCount = contador->percorre;
    int ret = _percursoArLisBal(pa, processa);
    int diff = contador->percorre - currentPercorreCount;
    int idx = contador->indexPercorre++;
    if(idx >= contador->sizeArrayPercorre ){
        contador->sizeArrayPercorre *= 2;
        contador->arrayPercorre = realloc( contador->arrayPercorre, contador->sizeArrayPercorre * sizeof(int));
    }
    contador->arrayPercorre[idx] = diff;
    return ret;
}

int getHeightLevelNode(pArLis p, ppNoArLis node, char* word, int* height,  ppNoArLis* parent, ppNoArLis* child, int (* processa)(pLDSE p, char *palavra))
{   
    
    (p->contador)->remove++;
    if((*node) == NULL){
        (*child) = NULL;
        return false;
    }
    ((*node)->contador)->remove++;
    // printf("comparando palavra %s %d\n", word, processa((*node)->lista, word));
    (p->contador)->contagemLista++;

    if (processa((*node)->lista, word) == true) {
        (*height) = 0;
        (*child) = node;
        return true;
    } else {
        ppNoArLis pLeft_child, pLeft_parent, pMiddle_child, pMiddle_parent, pRight_child, pRight_parent;
        pLeft_parent = pMiddle_parent = pRight_parent = node;
        int left_height = 0, middle_height = 0, right_height = 0;
        //  printf("antes %p %p\n", &(*pLeft_child));
        int ret_left = getHeightLevelNode(p, &(*node)->esquerda, word, &left_height, &pLeft_parent, &pLeft_child, processa);
        int ret_middle = getHeightLevelNode(p, &(*node)->centro, word, &middle_height, &pMiddle_parent, &pMiddle_child, processa);
        int ret_right = getHeightLevelNode(p, &(*node)->direita, word, &right_height, &pRight_parent, &pRight_child, processa);
        // printf("-> %p node left %d\n", node, left_height);
        // printf("-> %p node middle %d\n", node, middle_height);
        // printf("-> %p node right %d\n", node, right_height);
        if (ret_right == true && right_height >= middle_height && right_height >= left_height) {
            // printf("selecionado da esquerda %p %p\n", &(*node)->esquerda, &(*pLeft_child));
             (*child) = pRight_child;
             (*parent) = pRight_parent;
             (*height) = (right_height + 1);
             return ret_right;

        }
        if (ret_middle == true && middle_height >= left_height && middle_height >= right_height) {
            // printf("selecionado do meio %p %p\n", &(*node)->centro, &(*pMiddle_child));
            (*child) = pMiddle_child;
            (*parent) = pMiddle_parent;
            (*height) = (middle_height + 1);
            return ret_middle;
        }
        // printf("selecionado do direita %p %p\n", &(*node)->direita, &(*pRight_child));
        if(ret_left == true){
            (*child) = pLeft_child;
            (*parent) = pLeft_parent;
            (*height) = (left_height + 1);
            return ret_left;
        }
        return false;
    }
}

int getRemovableWithNoChild(pArLis p, NoArLis* node, ppNoArLis* maxNode, int height, int* max_height)
{
    if (node == NULL)
        return 0;
    else {
        (p)->contador->remove++;
        (node)->contador->remove++;
        int left_height = getRemovableWithNoChild(p, node->esquerda, maxNode, height+1, max_height);
        int middle_height = getRemovableWithNoChild(p, node->centro, maxNode, height+1, max_height);
        int right_height = getRemovableWithNoChild(p, node->direita, maxNode, height+1, max_height);
        // printf("%p node left %d\n", node, left_height);
        // printf("%p node middle %d\n", node, middle_height);
        // printf("%p node right %d\n", node, right_height);
        if (right_height >= middle_height && right_height >= left_height) {
            // printf(" no da direita elegido %d\n\n", height);
            if(node->direita != NULL && height >= (*max_height) && emptyChildNode(p, &node->direita)){
                (*maxNode) = &node->direita;
                (*max_height) = (right_height + 1);
            }
            return (right_height + 1);
        }
        if (middle_height <= left_height && middle_height <= right_height) {
            // printf(" no da meio elegido %d\n\n", height);
            if(node->centro != NULL && height >= (*max_height) && emptyChildNode(p, &node->centro)){
                (*maxNode) = &node->centro;
                (*max_height) = (middle_height + 1);
            }
            return (middle_height + 1);
        }

        // printf(" no da esquerda elegido %d\n\n", height);
        if (node->esquerda != NULL && height >= (*max_height) && emptyChildNode(p, &node->esquerda)){
            (*maxNode) = &node->esquerda;
            (*max_height) = (left_height + 1);
        }
        return (left_height + 1);
    }
}
int removeRebalancearArvore(pArLis p, pNoArLis root, ppNoArLis remove_node, int max_height){
    pNoArLis max_node = NULL;
    ppNoArLis ppmax_node = &max_node;
    int max = 0;
    // Busca o n?? com mais alto n??vel sem filhos
    int h = getRemovableWithNoChild(p, root, &ppmax_node, 0, &max);
    
    p->contador->remove++;
    if((*ppmax_node) != NULL){
        (*ppmax_node)->contador->remove++;
        // Troca o n?? de mais alto n??vel, com o n?? que vai ser removido
        destroiLDSE(&(*remove_node)->lista);
        destroiContadorArLis(&(*remove_node)->contador);
        (*remove_node)->lista = (*ppmax_node)->lista;
        (*remove_node)->contador = (*ppmax_node)->contador;
        // memcpy((*remove_node)->lista, (*ppmax_node)->lista, sizeof(pLDSE));
        // memcpy((*remove_node)->contador, (*ppmax_node)->contador, sizeof(pLDSE));
        free((*ppmax_node));
        (*ppmax_node) = NULL;
        return true;
    }
    return false;
}

int _removeArLisBal(pArLis p, char* word, int max_height, NoArLis** root )
{
    
    int ret = false;
    if ((*root) == NULL)
    {
        return false;
    }
    
    pNoArLis pNo = NULL, pChild = NULL;
    ppNoArLis ppParent = &pNo;
    ppNoArLis ppChild = &pChild;
    int height = 0;
    ret = getHeightLevelNode(p, root, word, &height, &ppParent, &ppChild, comparaLista2Palavra);
    // printf("ret2 %d %p\n\n", ret, (*ppChild));
    if(ret == false ||  (*ppChild) == NULL){
        return false;
    }
    // printf("Rmoving child %p %d %d\n\n", (*ppChild), height, max_height);
    if(emptyChildNode(p, ppChild) == true && height == (max_height-1 )){
        // Est?? no ??ltimo nivel e n??o tem filhos, apenas remove.
        return destroiNo(ppChild);
    }
    return removeRebalancearArvore(p,(*root), ppChild, max_height);
   
    
}

int removeArLisBal(pArLis p, void *item){
    CounterArLis* contador = p->contador;
    int max_height = maxHeight(p, p->raiz, 1);
    int currentRemoveCount = contador->remove;
    int ret = _removeArLisBal(p, item, max_height, &p->raiz);
    int idx = contador->indexRemove++;
    if(idx >= contador->sizeArrayRemove ){
        contador->sizeArrayRemove *= 2;
        contador->arrayRemove = realloc( contador->arrayRemove, contador->sizeArrayRemove * sizeof(int));
    }
    contador->arrayRemove[idx] = contador->remove - currentRemoveCount;
    return ret;
}

int nivelArLis(pArLis p){
    CounterArLis* contador = p->contador;
    int currentNivelCount = contador->buscaNivel;
    int ret = maxHeight(p, p->raiz, 0);
    int idx = contador->indexBuscaNivel++;
    if(idx >= contador->sizeArrayBuscaNivel ){
        contador->sizeArrayBuscaNivel *= 2;
        contador->arrayBuscaNivel = realloc( contador->arrayBuscaNivel, contador->sizeArrayBuscaNivel * sizeof(int));
    }
    contador->arrayBuscaNivel[idx] = contador->buscaNivel - currentNivelCount;
    return ret;
}

/** extra **/

int maxHeightWithWord(NoArLis* node, int* word_size)
{
    if (node == NULL)
        return 0;
    else {       
        int left_height = maxHeightWithWord(node->esquerda, word_size);
        int middle_height = maxHeightWithWord(node->centro, word_size);
        int right_height = maxHeightWithWord(node->direita, word_size);
        if(node->esquerda != NULL){
            int left_word_size = contaElementos((node->esquerda)->lista);
            if((*word_size) < left_word_size){
             (*word_size) = left_word_size;
            }
        }
         if(node->centro != NULL){
            int center_word_size = contaElementos((node->centro)->lista);
            if((*word_size) < center_word_size){
             (*word_size) = center_word_size;
            }
        }
           if(node->direita != NULL){
            int right_word_size = contaElementos((node->direita)->lista);
            if((*word_size) < right_word_size){
             (*word_size) = right_word_size;
            }
        }
        // printf("%p node left %d\n", node, left_height);
        // printf("%p node middle %d\n", node, middle_height);
        // printf("%p node right %d\n", node, right_height);
        if (left_height >= middle_height && left_height >= right_height) {
            return (left_height + 1);
        }
        if (middle_height >= left_height && middle_height >= right_height) {
            return (middle_height + 1);
        }
        return (right_height + 1);
    }
}

int imprimeContadorNo(pArLis pa, pNoArLis node, FILE* f){
    if(node == NULL){
        return false;
    }

    imprimeCharFilterFile(node->lista, 20, 10, f);
    fprintf(f," -> [%d]", (node->contador)->insere);
    fprintf(f,"  [%d]", (node->contador)->remove);
    fprintf(f,"  [%d]", (node->contador)->percorre);
    fprintf(f,"  [%d]\n", (node->contador)->buscaNivel);
    if(node->esquerda != NULL){
        imprimeContadorNo(pa, node->esquerda, f);
    }
    if(node->centro != NULL){
        imprimeContadorNo(pa, node->centro, f);
    }
    if(node->direita != NULL){
        imprimeContadorNo(pa, node->direita, f);
    }
    return true;
}

int imprimePorTentativa(pArLis pa, FILE* f){
    fprintf(f,"\n###################################################\n\n");
    
    fprintf(f,"Contagem de comparacoes por execucao do metodo de insercao\n");
    CounterArLis* contador = pa->contador;
    int indexInsere = contador->indexInsere;
    fprintf(f,"Tentativa [x] -> [total] \n");
    for(int i; i< indexInsere; i++){
        fprintf(f,"Tentativa  [%d] -> [%d]\n", i, contador->arrayInsere[i]);
    }
    fprintf(f,"\n\n");
    fprintf(f,"Contagem de comparacoes por execucao do metodo de remocao\n");
    int indexRemove = contador->indexRemove;
    fprintf(f,"Tentativa [x] -> [total]  \n");
    for(int i; i < indexRemove; i++){
        fprintf(f,"Tentativa  [%d] -> [%d]\n", i, contador->arrayRemove[i]);
    }

    fprintf(f,"\n\n");
    fprintf(f,"Contagem de comparacoes por por execucao do metodo de percorrer\n");
    int indexPercorre = contador->indexPercorre;
    fprintf(f,"Tentativa [x] -> [total]  \n");
    for(int i; i< indexPercorre; i++){
        fprintf(f,"Tentativa  [%d] -> [%d]\n", i, contador->arrayPercorre[i]);
    }
    return true;
}
int imprimeContadorNoLista(pArLis pa, pNoArLis node, FILE* f){
    if(node == NULL || node->lista == NULL){
        return false;
    }
    int contagem = 0, ret  =0;
    ret = pegaContagemLista(node->lista, &contagem);
    if(ret == true){
        fprintf(f,"\n");
        imprimeCharFilterFile(node->lista, 20, 10, f);
        fprintf(f," -> [%d]", contagem);
    }
    fprintf(f,"\n");
    if(node->esquerda != NULL){
        imprimeContadorNoLista(pa, node->esquerda, f);
    }
    if(node->centro != NULL){
        imprimeContadorNoLista(pa, node->centro, f);
    }
    if(node->direita != NULL){
        imprimeContadorNoLista(pa, node->direita, f);
    }
    return true;
}

int imprimeContadorNoANoLista(pArLis pa, pNoArLis node, FILE* f){
    if(node == NULL || node->lista == NULL){
        return false;
    }
    int contagem = 0, ret  =0;
    int tamanhoLista = contaElementos(node->lista);
    fprintf(f,"\n");
    fprintf(f,"  Contagem de comparacoes nos n??s por posicao da lista ");
    imprimeCharFilterFile(node->lista, 20, 10, f);
    fprintf(f,": \n");
    for(int i =0; i < tamanhoLista; i++ ){
        fprintf(f,"\n");
        ret = pegaContagemPorPosicao(node->lista, i, &contagem);
        if(ret == true){
            fprintf(f,"     [%d] -> [%d]", i, contagem);
        }
    }
    if(node->esquerda != NULL){
        imprimeContadorNoANoLista(pa, node->esquerda, f);
    }
    if(node->centro != NULL){
        imprimeContadorNoANoLista(pa, node->centro, f);
    }
    if(node->direita != NULL){
        imprimeContadorNoANoLista(pa, node->direita, f);
    }
    return true;
}

int imprimeContadorLista(pArLis pa, FILE* f){
    CounterArLis* contador = pa->contador;
    fprintf(f,"###################################################\n\n");
    fprintf(f,"Comparacoes na lista [n??] -> [total]  \n");
    imprimeContadorNoLista(pa, pa->raiz,f);
    imprimeContadorNoANoLista(pa, pa->raiz, f);
    return true;
}

int imprimePorNo(pArLis pa, FILE* f){
    fprintf(f,"###################################################\n\n");
    fprintf(f,"[Comparacoes do n??] -> [insercoes] [remocoes] [percurso] [busca nivel]\n\n");   
    return imprimeContadorNo(pa, pa->raiz, f);
}

int _imprimeRelatorio(pArLis pa, FILE* f){
    fprintf(f,"\n\n###################################################\n");
    fprintf(f,"################# Relatorio ArLis #################\n");
    fprintf(f,"###################################################\n\n");
    CounterArLis *c = pa->contador;
    fprintf(f,"Numero de comparacoes para inserir arvore: %d\n", c->insere);
    fprintf(f,"Numero de comparacoes para remover arvore: %d\n", c->remove);
    fprintf(f,"Numero de comparacoes para percorrer arvore: %d\n", c->percorre);
    fprintf(f,"Numero de comparacoes para buscar nivel da arvore: %d\n", c->buscaNivel);
    fprintf(f,"Numero de comparacoes por palavra na lista: %d\n", c->contagemLista);
    fprintf(f,"\n\n");
    imprimePorNo(pa, f);
    fprintf(f,"\n\n");
    imprimePorTentativa(pa, f);
    fprintf(f,"\n\n");
    imprimeContadorLista(pa, f);
}


int execHeightWithWord(NoArLis* node, int pos, int compHeight, int height, int word_size, int max_height, FILE* f)
{
    if (node == NULL)
        return 0;
    else {
    
        int left_height = execHeightWithWord(node->esquerda, -1, compHeight+1, height, word_size, max_height, f);
        int middle_height = execHeightWithWord(node->centro, 0, compHeight+1, height, word_size, max_height, f);
        int right_height = execHeightWithWord(node->direita, 1, compHeight+1, height, word_size, max_height, f);
    
        if(compHeight == height){
            int s = 3;
            int y = (max_height - compHeight -1);
            if(y < 0){
                s = 1;
            } else {
                for (int i = 0; i < y ; ++i){
                    s *= 3;
                }
            }
            int x =  (word_size  * s) - word_size;
            for(int i = 0; i < (x/2); i++){
                fprintf(f," ");
            }
            imprimeCharFilterFile(node->lista, word_size, 10, f);
            for(int i = (x/2); i < x; i++){
                fprintf(f," ");
            }
        }
        if (left_height <= middle_height && left_height <= right_height) {
            return (left_height + 1);
        }
        if (middle_height <= left_height && middle_height <= right_height) {
            return (middle_height + 1);
        }
        return (right_height + 1);       
    }
}

int printTree(pArLis p, FILE* f){
    int word_size = 0;
    int max_height = maxHeightWithWord(p->raiz, &word_size);
    word_size+=1;
    fprintf(f,"\n\n\n\n#######################################################\n");
    fprintf(f,"################# Imprimindo a Arvore #################\n");
    fprintf(f,"#######################################################\n\n");
    fprintf(f,"\n\n");
    for(int i = 0;  i < max_height ; i++){
        execHeightWithWord(p->raiz, 0, 0, i, word_size, max_height-1, f);
        fprintf(f,"\n");
    }
    return true;
}

int writeToFile(pArLis pa){
    FILE *f = fopen("report_file.log", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return false;
    }
    int ret = _imprimeRelatorio(pa, f);
    printTree(pa, f);
    fclose(f);
    return ret;
}
int imprimeRelatorio(pArLis pa){
    return writeToFile(pa);
}
