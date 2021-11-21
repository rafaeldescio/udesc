#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ArLis_privado.h"
#define true 1
#define false 0

// Dúvidas: O que fazer nas funções recursivas que tem também função dinamica que depende do numero de elementos na LDSE?
// O que fazer com as funções do C (malloc, free e etc)? Devo pesquisar a complexidade delas e usar, ou considerar O(1)?
// O que fazer com as funções passadas dinamicamente? Não da pra saber a complexidade delas. Considerar linear?

int criarContador(CounterArLis ** c){
    (*c) = (CounterArLis *)malloc(sizeof(CounterArLis));
    if((*c) == NULL)
        return false;
    (*c)->arrayInsere = malloc(sizeof(int));
    (*c)->sizeArrayInsere = 1;
    (*c)->arrayRemove = malloc(sizeof(int));
    (*c)->sizeArrayRemove = 1;
    (*c)->arrayPercorre = malloc(sizeof(int));
    (*c)->sizeArrayPercorre = 1;
    return true;
}
int criaArLisBal(ppArLis pp, int tamInfo){
    /* aloca descritor */
	(*pp) = (ArLis *)malloc(sizeof(ArLis));
    if( (*pp) == NULL)
    	return FRACASSO;
    criaLDSE(&(*pp)->bufLista,tamInfo);
	(*pp)->tamInfo = tamInfo ;
	(*pp)->raiz = NULL;
    if(criarContador(&(*pp)->contador) == false){
        return false;
    }
	return true;
}
int criaNo(pLDSE* list, ppNoArLis parent, ppNoArLis node){
    (*node) = (NoArLis *)malloc(sizeof(NoArLis)); // c * 1
    if ((*node) == NULL){ // c * 1
        return false; // c * 1
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

int emptyChildNode(NoArLis** node){
    if((*node) == NULL){
        return true;
    }
    if( (*node)->esquerda == NULL && (*node)->centro == NULL &&  (*node)->direita == NULL){ // Melhor caso, c * 1. Pior caso, c * 3
        return true; // c * 1
    }
    return false; // c * 1
}

int getLowLevelFreeNode(pArLis p, ppNoArLis node, int* height,  ppNoArLis* parent, ppNoArLis* child)
{
    (p->contador)->insere++; // c * 1
    if ((*node) == NULL) { // c * 1
        (*height) = 0; // c * 1
        (*child) = node; // c * 1
        return true; // c * 1
    } else {
        ((*node)->contador)->insere++; // c * 1
        ppNoArLis pLeft_child, pLeft_parent, pMiddle_child, pMiddle_parent, pRight_child, pRight_parent; // c * 6
        pLeft_parent = pMiddle_parent = pRight_parent = node; // c * 3
        int left_height = 0, middle_height = 0, right_height = 0; // c * 3
        //  printf("antes %p %p\n", &(*pLeft_child));
        getLowLevelFreeNode(p, &(*node)->esquerda, &left_height, &pLeft_parent, &pLeft_child); // T(n/3)
        getLowLevelFreeNode(p, &(*node)->centro, &middle_height, &pMiddle_parent, &pMiddle_child); // T(n/3)
        getLowLevelFreeNode(p, &(*node)->direita, &right_height, &pRight_parent, &pRight_child); // T(n/3)
       
        if (left_height <= middle_height && left_height <= right_height) { // c * 1
            // printf("selecionado da esquerda %p %p\n", &(*node)->esquerda, &(*pLeft_child));
             (*child) = pLeft_child; // c * 1
             (*parent) = pLeft_parent; // c * 1
             (*height) = (left_height + 1); // c * 1
             return true; // c * 1

        }
        if (middle_height <= left_height && middle_height <= right_height) { // c * 1
            // printf("selecionado do meio %p %p\n", &(*node)->centro, &(*pMiddle_child));
            (*child) = pMiddle_child; // c * 1
            (*parent) = pMiddle_parent; // c * 1
            (*height) = (middle_height + 1); // c * 1
            return true; // c * 1
        }
        // printf("selecionado do direita %p %p\n", &(*node)->direita, &(*pRight_child));
        (*child) = pRight_child; // c * 1
        (*parent) = pRight_parent; // c * 1
        (*height) = (right_height + 1); // c * 1
        return true; // c * 1
        // Nessa função temos a árvore sendo dividida em 3 em toda iteração. Portanto
        // T(n) = 3T(n/3) + c
        // a = 3, b = 3, c = 0. Caso 1 do teorema mestre
        // log3 na base 3 = 1, que é maior que 0. Portanto
        // T(n) = Theta(n^logba) = Theta(n^log3 na base 3) = Theta(n)
    }
}
int maxHeight(NoArLis* node)
{
    if (node == NULL) // c * 1
        return 0; // c * 1
    else {
        // Dividiu a arvore original em 3 subarvores
        int left_height = maxHeight(node->esquerda); // T(n/3)
        int middle_height = maxHeight(node->centro); // T(n/3)
        int right_height = maxHeight(node->direita); // T(n/3)
        // printf("%p node left %d\n", node, left_height);
        // printf("%p node middle %d\n", node, middle_height);
        // printf("%p node right %d\n", node, right_height);
        if (left_height >= middle_height && left_height >= right_height) { // Melhor caso => c * 1, pior caso => c * 2
            return (left_height + 1); // c * 1
        }
        if (middle_height >= left_height && middle_height >= right_height) { // Melhor caso => c * 1, pior caso => c * 2
            return (middle_height + 1); // c * 1
        }
        return (right_height + 1); // c * 1
        // Nessa função temos a árvore sendo dividida em 3 em toda iteração. Portanto
        // T(n) = 3T(n/3) + c
        // a = 3, b = 3, c = 0. Caso 1 do teorema mestre
        // log3 na base 3 = 1, que é maior que 0. Portanto
        // T(n) = Theta(n^logba) = Theta(n^log3 na base 3) = Theta(n)
    }
}
int _internalInsereBalanceado(pArLis p, pLDSE* list, NoArLis* parent, NoArLis** node )
{   
    int ret = false;
    // é Raiz
    if ((*node) == NULL) // c * 1
    {
        return criaNo(list, &parent, node); // c * 1
    }
    pNoArLis pNo = NULL; // c * 1
    ppNoArLis ppParent = &pNo; // c * 1
    ppNoArLis ppChild = NULL; // c * 1
    int height = 0; // c * 1
    getLowLevelFreeNode(p, node, &height, &ppParent, &ppChild); // Theta(n)
    if((*ppParent) == NULL){ // c * 1
        return criaNo(list, &parent, ppChild); // c * 1
    } else{
        return criaNo(list, ppParent, ppChild); // c * 1
    }
}


int _insereArLisBal(pArLis p, void *novo, int (* cmp)(void *p1, void *p2)){

    if( p->bufLista == NULL){ // c * 1
        pLDSE tempList = malloc(sizeof(pLDSE)); // c * 1
        if(tempList == NULL){ // c * 1
            return false; // c * 1
        }
        int retLdse = criaLDSE(&tempList, sizeof(p->tamInfo)); // c * 1  
        if(retLdse == false) { // c * 1
            return false; // c * 1
        }
        p->bufLista = tempList; // c * 1

    }
    int space = 32, new_line = 10, max_val = 123; // c * 3 
    if (cmp(novo, &new_line) != 0 && (cmp(novo, &space) < 0 || cmp(novo, &max_val) > 0)) { // Melhor caso c * 1, pior caso c * 6, considerando que cmp é O(1)
        // printf("\nFalha ao inserir - Valor inválido [%d]\n", *((int*)novo));
        return false; // c * 1
    }
    int ret = insereFim(p->bufLista, novo); // Sendo k o número de elementos em bufLista, é O(k)
    
    if (cmp(novo, &space) == 0 ||  cmp(novo, &new_line) == 0) { // Melhor caso c * 2, pior caso c * 4, considerando que cmp é O(1)
        ret = _internalInsereBalanceado(p, &p->bufLista, NULL, &p->raiz); // Theta(n log n) + c
        p->bufLista = NULL;// c * 1
        // int currentHeight = maxHeight(p->raiz);
        // printf("\nCurrent height %d\n", currentHeight);
    }
    return ret; // c * 1
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
    (p->contador)->percorre++; // c * 1
    if (node == NULL) // c * 1
        return 0; // c * 1
    else {
        ((node)->contador)->percorre++; // c * 1
        if(compHeight == height){ // c * 1
            processa(node->lista); // f(k) * 1
        }
        //ignora os níveis superiores
        if(compHeight > height){ // c * 1
            return 0; // c * 1
        }

        int left_height = execHeight(p, node->esquerda, compHeight+1, height, processa); // T(n/3)
        int middle_height = execHeight(p,node->centro,  compHeight+1, height, processa); // T(n/3)
        int right_height = execHeight(p, node->direita, compHeight+1, height, processa); // T(n/3)
        if (left_height <= middle_height && left_height <= right_height) { // Melhor caso => c * 1, pior caso => c * 2
            return (left_height + 1);
        }
        if (middle_height <= left_height && middle_height <= right_height) { // Melhor caso => c * 1, pior caso => c * 2
            return (middle_height + 1); // c * 1
        }
        return (right_height + 1); // c * 1   
        // Nessa função temos a árvore sendo dividida em 3 em toda iteração, até que se atinja a altura desejada.
        // Aqui a complexidade é em uma função do parâmetro height. Nesse caso h. Para essa eq. n é o numero de nós processados.
        // T(n) = 3T(n/3) + O(1)
        // a = 3, b = 3 e c = 0 => Caso 1 teorema mestre
        // T(n) = Theta(n) 
        // O número de nós processados é, conforme PG (progressao geometrica), (3^h-1)/2, portanto:
        // T(h) = Theta((3^h-1)/2)
        // Somando com o processamento dos nós na última altura:
        // T(h) = Theta((3^h-1)/2) + 3^h*O(f(k))
    }
}


int _percursoArLisBal(pArLis pa, void (* processa)(void *p)){

    int ret = true; // c * 1
    int max_height = maxHeight(pa->raiz); // Theta(n log n)
    printf("\n"); // c * 1
    // O custo disso é representado por um somatório
    // Somatório de 0 até h de Theta((3^i-1)/2) + 3^i*O(f(k)), sendo h = log3 de n no pior caso, portanto
    // Somatório de 0 até log3 de n de Theta((3^i-1)/2) + 3^h*O(f(k)). Bastante custoso.
    for(int i = 0;  i <= max_height ; i++){
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
    
    if((*node) == NULL){ // c * 1
        (*child) = NULL; // c * 1
        return false; // c * 1
    }
    (p->contador)->remove++; // c * 1
    ((*node)->contador)->remove++; // c * 1
    // printf("comparando palavra %s %d\n", word, processa((*node)->lista, word));
    (p->contador)->contagemLista++; // c * 1
    if (processa((*node)->lista, word) == true) { // n * O(f(k)) sendo k o número de elementos na lista
        (*height) = 0; // c * 1
        (*child) = node; // c * 1
        return true; // c * 1
    } else {
        ppNoArLis pLeft_child, pLeft_parent, pMiddle_child, pMiddle_parent, pRight_child, pRight_parent; // c * 6;
        pLeft_parent = pMiddle_parent = pRight_parent = node; // c * 3
        int left_height = 0, middle_height = 0, right_height = 0; // c * 3
        //  printf("antes %p %p\n", &(*pLeft_child));
        int ret_left = getHeightLevelNode(p, &(*node)->esquerda, word, &left_height, &pLeft_parent, &pLeft_child, processa);
        int ret_middle = getHeightLevelNode(p, &(*node)->centro, word, &middle_height, &pMiddle_parent, &pMiddle_child, processa);
        int ret_right = getHeightLevelNode(p, &(*node)->direita, word, &right_height, &pRight_parent, &pRight_child, processa);
        // printf("-> %p node left %d\n", node, left_height);
        // printf("-> %p node middle %d\n", node, middle_height);
        // printf("-> %p node right %d\n", node, right_height);
        if (ret_right == true && right_height >= middle_height && right_height >= left_height) { // Melhor caso, c * 1. Pior caso, c * 3
            // printf("selecionado da esquerda %p %p\n", &(*node)->esquerda, &(*pLeft_child));
             (*child) = pRight_child; // c * 1
             (*parent) = pRight_parent; // c * 1
             (*height) = (right_height + 1); // c * 1
             return ret_right; // c * 1

        }
        if (ret_middle == true && middle_height >= left_height && middle_height >= right_height) { // Melhor caso, c * 1. Pior caso, c * 3
            // printf("selecionado do meio %p %p\n", &(*node)->centro, &(*pMiddle_child));
            (*child) = pMiddle_child; // c * 1
            (*parent) = pMiddle_parent; // c * 1
            (*height) = (middle_height + 1); // c * 1
            return ret_middle; // c * 1
        }
        // printf("selecionado do direita %p %p\n", &(*node)->direita, &(*pRight_child));
        if(ret_left == true){ // c * 1 
            (*child) = pLeft_child; // c * 1
            (*parent) = pLeft_parent; // c * 1
            (*height) = (left_height + 1); // c * 1
            return ret_left; // c * 1
        }
        return false; // c * 1
        // Nessa função temos a árvore sendo dividida em 3 em toda iteração. Portanto
        // T(n) = 3T(n/3) + c
        // a = 3, b = 3, c = 0. Caso 1 do teorema mestre
        // log3 na base 3 = 1, que é maior que 0. Portanto
        // T(n) = Theta(n^logba) = Theta(n^log3 na base 3) = Theta(n)
        // Adicionando a execução da função externa
        // T(n) = Theta(n) + n*O(f(k))
    }
}

int removeChildNode(ppNoArLis ppChild){
    reiniciaLDSE((*ppChild)->lista); // Sendo k o numero de elementos na LDSE, O(k);
    free((*ppChild)); // c * 1
    (*ppChild) = NULL; // c * 1
}

int getRemovableWithNoChild(pArLis p, NoArLis* node, ppNoArLis* maxNode, int height, int* max_height)
{
    (p)->contador->remove++; // c * 1
    if (node == NULL) // c * 1
        return 0;
    else {
        (node)->contador->remove++; // c * 1
        int left_height = getRemovableWithNoChild(p, node->esquerda, maxNode, height+1, max_height); // T(n/3)
        int middle_height = getRemovableWithNoChild(p, node->centro, maxNode, height+1, max_height); // T(n/3) 
        int right_height = getRemovableWithNoChild(p, node->direita, maxNode, height+1, max_height); // T(n/3)
        // printf("%p node left %d\n", node, left_height);
        // printf("%p node middle %d\n", node, middle_height);
        // printf("%p node right %d\n", node, right_height);
        if (right_height >= middle_height && right_height >= left_height) { // Melhor caso, c * 1. Piro caso, c * 2
            // printf(" no da direita elegido %d\n\n", height);
            if(node->direita != NULL && height >= (*max_height) && emptyChildNode(&node->direita)){ // Melhor caso, c * 1. Piro caso, c * 3
                (*maxNode) = &node->direita; // c * 1
                (*max_height) = (right_height + 1); // c * 1
            }
            return (right_height + 1); // c * 1
        }
        if (middle_height <= left_height && middle_height <= right_height) { // Melhor caso, c * 1. Pior caso, c * 2
            // printf(" no da meio elegido %d\n\n", height);
            if(node->centro != NULL && height >= (*max_height) && emptyChildNode(&node->centro)){ // Melhor caso, c * 1. Piro caso, c * 3
                (*maxNode) = &node->centro; // Melhor caso c * 1
                (*max_height) = (middle_height + 1); // Melhor caso c * 1
            }
            return (middle_height + 1); // Melhor caso c * 1
        }

        // printf(" no da esquerda elegido %d\n\n", height);
        if (node->esquerda != NULL && height >= (*max_height) && emptyChildNode(&node->esquerda)){ // Melhor caso, c * 1. Piro caso, c * 3
            (*maxNode) = &node->esquerda; // Melhor caso c * 1
            (*max_height) = (left_height + 1); // Melhor caso c * 1
        }
        return (left_height + 1); // Melhor caso c * 1
        // Nessa função temos a árvore sendo dividida em 3 em toda iteração. Portanto
        // T(n) = 3T(n/3) + c
        // a = 3, b = 3, c = 0. Caso 1 do teorema mestre
        // log3 na base 3 = 1, que é maior que 0. Portanto
        // T(n) = Theta(n^logba) = Theta(n^log3 na base 3) = Theta(n)
    }
}
int removeRebalancearArvore(pArLis p, pNoArLis root, ppNoArLis remove_node, int max_height){ // O(1) + O(k)
    pNoArLis max_node = NULL; // c * 1
    ppNoArLis ppmax_node = &max_node; // c * 1
    int max = 0; // c * 1
    // Busca o nó com mais alto nível sem filhos
    int h = getRemovableWithNoChild(p,root, &ppmax_node, 0, &max); // Theta(n)
    
    if((*ppmax_node) != NULL){ // c * 1
        imprimeChar((*ppmax_node)->lista); // O(k) sendo K o número de elementos da lista
        printf("\n\n"); // c * 1
        imprimeChar((*remove_node)->lista); // c * 1
        printf("\n\n"); // c * 1
    
        // Troca o nó de mais alto nível, com o nó que vai ser removido
        reiniciaLDSE((*remove_node)->lista); // Sendo k o numero de elementos na LDSE, O(k);
        (*remove_node)->lista = (*ppmax_node)->lista; // c * 1
        free((*ppmax_node)); // c * 1
        (*ppmax_node) = NULL; // c * 1
        return true; // c * 1
    }
    return false; // c * 1
}

int _removeArLisBal(pArLis p, char* word, int max_height, NoArLis** root )
{
    
    int ret = false; // c * 1
    if ((*root) == NULL) // c * 1
    {
        return true; // c * 1
    }
    pNoArLis pNo = NULL, pChild = NULL; // c * 1
    ppNoArLis ppParent = &pNo; // c * 1
    ppNoArLis ppChild = &pChild; // c * 1
    int height = 0; // c * 1
    ret = getHeightLevelNode(p, root, word, &height, &ppParent, &ppChild, comparaLista2Palavra); // T(n) = Theta(n) + n*O(f(k))
    // printf("ret2 %d %p\n\n", ret, (*ppChild));
    if(ret == false ||  (*ppChild) == NULL){ // No melhor caso c * 1, no pior caso c * 2
        return false; // c * 1
    }
    // printf("Rmoving child %p %d %d\n\n", (*ppChild), height, max_height);
    if(emptyChildNode(ppChild) == true && height == (max_height-1 )){ // No melhor caso c * 1, no pior caso c * 2
        // Está no último nivel e não tem filhos, apenas remove.
        removeChildNode(ppChild); // O(k) sendo k o número de itens na LDSE
        return ret; // c * 1
    }
    return removeRebalancearArvore(p,(*root), ppChild, max_height); // O(1) + O(k)
}

int removeArLisBal(pArLis p, void *item){
    CounterArLis* contador = p->contador;
    int max_height = maxHeight(p->raiz); // Theta(n)
    int currentRemoveCount = contador->remove;
    int ret = _removeArLisBal(p, item, max_height, &p->raiz); // Theta(n) + n*O(f(k)) + O(k)
    int idx = contador->indexRemove++;
    if(idx >= contador->sizeArrayRemove ){
        contador->sizeArrayRemove *= 2;
        contador->arrayRemove = realloc( contador->arrayRemove, contador->sizeArrayRemove * sizeof(int));
    }
    contador->arrayRemove[idx] = contador->remove - currentRemoveCount;
    return ret;
}


int nivelArLis(pArLis p){
    return maxHeight(p->raiz);
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
    fprintf(f,"  [%d]\n", (node->contador)->percorre);
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
    
    fprintf(f,"Contagem de comparacoes por insercao por tentativa\n");
    CounterArLis* contador = pa->contador;
    int indexInsere = contador->indexInsere;
    fprintf(f,"Tentativa [x] -> [total] \n");
    for(int i; i< indexInsere; i++){
        fprintf(f,"Tentativa  [%d] -> [%d]\n", i, contador->arrayInsere[i]);
    }
    fprintf(f,"\n\n");
    fprintf(f,"Contagem de comparacoes por remocao por tentativa\n");
    int indexRemove = contador->indexRemove;
    fprintf(f,"Tentativa [x] -> [total]  \n");
    for(int i; i< indexRemove; i++){
        fprintf(f,"Tentativa  [%d] -> [%d]\n", i, contador->arrayRemove[i]);
    }

    fprintf(f,"\n\n");
    fprintf(f,"Contagem de comparacoes por percurso por tentativa\n");
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
    fprintf(f,"  Contagem nos nós por posicao da lista ");
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
    fprintf(f,"Tentativas na lista [nó] -> [total]  \n");
    imprimeContadorNoLista(pa, pa->raiz,f);
    imprimeContadorNoANoLista(pa, pa->raiz, f);
    return true;
}

int imprimePorNo(pArLis pa, FILE* f){
    fprintf(f,"###################################################\n\n");
    fprintf(f,"[Conteudo do no] -> [insercoes] [remocoes] [percurso]\n\n");   
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
