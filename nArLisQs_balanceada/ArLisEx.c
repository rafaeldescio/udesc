#include <stdlib.h>
#include <string.h>
#include "ArLis_privado.h"
#define true 1
#define false 0


int criaNo(pLDSE* list, ppNoArLis parent, ppNoArLis node){
    (*node) = (NoArLis *)malloc(sizeof(NoArLis));
    if ((*node) == NULL){
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
    if( (*node)->esquerda == NULL && (*node)->centro == NULL &&  (*node)->direita == NULL){
        return true;
    }
    return false;
}

int getLowLevelFreeNode(ppNoArLis node, int* height,  ppNoArLis* parent, ppNoArLis* child)
{
    if ((*node) == NULL) {
        (*height) = 0;
        (*child) = node;
        return true;
    } else {
        ppNoArLis pLeft_child, pLeft_parent, pMiddle_child, pMiddle_parent, pRight_child, pRight_parent;
        pLeft_parent = pMiddle_parent = pRight_parent = node;
        int left_height = 0, middle_height = 0, right_height = 0;
        //  printf("antes %p %p\n", &(*pLeft_child));
        getLowLevelFreeNode(&(*node)->esquerda, &left_height, &pLeft_parent, &pLeft_child);
        getLowLevelFreeNode(&(*node)->centro, &middle_height, &pMiddle_parent, &pMiddle_child);
        getLowLevelFreeNode(&(*node)->direita, &right_height, &pRight_parent, &pRight_child);
       
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
int maxHeight(NoArLis* node)
{
    if (node == NULL)
        return 0;
    else {
        int left_height = maxHeight(node->esquerda);
        int middle_height = maxHeight(node->centro);
        int right_height = maxHeight(node->direita);
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
int insereBaleanceado(pLDSE* list, NoArLis* parent, NoArLis** node )
{
    int ret = false;
    // é Raiz
    if ((*node) == NULL)
    {
        return criaNo(list, &parent, node);
    }
    pNoArLis pNo = NULL;
    ppNoArLis ppParent = &pNo;
    ppNoArLis ppChild = NULL;
    int height = 0;
    getLowLevelFreeNode(node, &height, &ppParent, &ppChild);
    if((*ppParent) == NULL){
        int ret = criaNo(list, &parent, ppChild);
        return ret;
    } else{
        return criaNo(list, ppParent, ppChild);
    }
    return ret;
}

int insereArLisBal(pArLis p, void *novo, int (* cmp)(void *p1, void *p2)){

    if( p->bufLista == NULL){
        pLDSE tempList = malloc(sizeof(pLDSE));
        if(tempList == NULL){
            return false;
        }
        int retLdse = criaLDSE(&tempList, sizeof(p->tamInfo));    
        if(retLdse == false) {
            return false;
        }
        p->bufLista = tempList;

    }
    int space = 32, new_line = 10, max_val = 123;
    if (cmp(novo, &new_line) != 0 && (cmp(novo, &space) < 0 || cmp(novo, &max_val) > 0)) {
        // printf("\nFalha ao inserir - Valor inválido [%d]\n", *((int*)novo));
        return false;
    }
    int ret = insereFim(p->bufLista, novo);
    
    if (cmp(novo, &space) == 0 ||  cmp(novo, &new_line) == 0) {
        ret = insereBaleanceado(&p->bufLista, NULL, &p->raiz);
        p->bufLista = NULL;
        // int currentHeight = maxHeight(p->raiz);
        // printf("\nCurrent height %d\n", currentHeight);
    }
 
    return ret;
}

int execHeight(NoArLis* node, int compHeight, int height, void (* processa)(void *p))
{
    if (node == NULL)
        return 0;
    else {
        if(compHeight == height){
            processa(node->lista);
        }
        //ignora os níveis superiores
        if(compHeight > height){
            return 0;
        }

        int left_height = execHeight(node->esquerda, compHeight+1, height, processa);
        int middle_height = execHeight(node->centro,  compHeight+1, height, processa);
        int right_height = execHeight(node->direita, compHeight+1, height, processa);
        if (left_height <= middle_height && left_height <= right_height) {
            return (left_height + 1);
        }
        if (middle_height <= left_height && middle_height <= right_height) {
            return (middle_height + 1);
        }
        return (right_height + 1);       
    }
}
int percursoArLisBal(pArLis pa, void (* processa)(void *p)){

    int ret = true;
    int max_height = maxHeight(pa->raiz);
    printf("\n");
    for(int i = 0;  i <= max_height ; i++){
        execHeight(pa->raiz, 0, i, processa);
    }
    return true;
    
}

int getHeightLevelNode(ppNoArLis node, char* word, int* height,  ppNoArLis* parent, ppNoArLis* child, int (* processa)(pLDSE p, char *palavra))
{   
    if((*node) == NULL){
        (*child) = NULL;
        return false;
    }
    
    // printf("comparando palavra %s %d\n", word, processa((*node)->lista, word));
    if (processa((*node)->lista, word) == true) {
        (*height) = 0;
        (*child) = node;
        return true;
    } else {
        ppNoArLis pLeft_child, pLeft_parent, pMiddle_child, pMiddle_parent, pRight_child, pRight_parent;
        pLeft_parent = pMiddle_parent = pRight_parent = node;
        int left_height = 0, middle_height = 0, right_height = 0;
        //  printf("antes %p %p\n", &(*pLeft_child));
        int ret_left = getHeightLevelNode(&(*node)->esquerda, word, &left_height, &pLeft_parent, &pLeft_child, processa);
        int ret_middle = getHeightLevelNode(&(*node)->centro, word, &middle_height, &pMiddle_parent, &pMiddle_child, processa);
        int ret_right = getHeightLevelNode(&(*node)->direita, word, &right_height, &pRight_parent, &pRight_child, processa);
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

int removeChildNode(ppNoArLis ppChild){
    reiniciaLDSE((*ppChild)->lista);
    free((*ppChild));
    (*ppChild) = NULL;
}

int getMaxHeightNoWithNoChild(NoArLis* node, ppNoArLis* maxNode, int height, int* max_height)
{
    if (node == NULL)
        return 0;
    else {
        int left_height = getMaxHeightNoWithNoChild(node->esquerda, maxNode, height+1, max_height);
        int middle_height = getMaxHeightNoWithNoChild(node->centro, maxNode, height+1, max_height);
        int right_height = getMaxHeightNoWithNoChild(node->direita, maxNode, height+1, max_height);
        // printf("%p node left %d\n", node, left_height);
        // printf("%p node middle %d\n", node, middle_height);
        // printf("%p node right %d\n", node, right_height);
        if (right_height >= middle_height && right_height >= left_height) {
            // printf(" no da direita elegido %d\n\n", height);
            if(node->direita != NULL && height >= (*max_height) && emptyChildNode(&node->direita)){
                (*maxNode) = &node->direita;
                (*max_height) = (right_height + 1);
            }
            return (right_height + 1);
        }
        if (middle_height <= left_height && middle_height <= right_height) {
            // printf(" no da meio elegido %d\n\n", height);
            if(node->centro != NULL && height >= (*max_height) && emptyChildNode(&node->centro)){
                (*maxNode) = &node->centro;
                (*max_height) = (middle_height + 1);
            }
            return (middle_height + 1);
        }

        // printf(" no da esquerda elegido %d\n\n", height);
        if (node->esquerda != NULL && height >= (*max_height) && emptyChildNode(&node->esquerda)){
            (*maxNode) = &node->esquerda;
            (*max_height) = (left_height + 1);
        }
        return (left_height + 1);
    }
}
int rebalancearArvore(pNoArLis root, ppNoArLis remove_node, int max_height){
    pNoArLis max_node = NULL;
    ppNoArLis ppmax_node = &max_node;
    int max = 0;
    // Busca o nó com mais alto nível sem filhos
    int h = getMaxHeightNoWithNoChild(root, &ppmax_node, 0, &max);
    // printf("max %p %d %d\n", (*ppmax_node), h, max);
    
    if((*ppmax_node) != NULL){
        printf("max %p %p %p\n", (*ppmax_node), (*remove_node), (*ppmax_node)->lista);
        imprimeChar((*ppmax_node)->lista);
        printf("\n\n");
        imprimeChar((*remove_node)->lista);
        printf("\n\n");
    
        // Troca o nó de mais alto nível, com o nó que vai ser removido
        reiniciaLDSE((*remove_node)->lista);
        (*remove_node)->lista = (*ppmax_node)->lista;
        free((*ppmax_node));
        (*ppmax_node) = NULL;
        return true;
    }
    return false;
}

int removeBaleanceado(char* word, int max_height, NoArLis** root )
{
    int ret = false;
    if ((*root) == NULL)
    {
        return true;
    }
    pNoArLis pNo = NULL, pChild = NULL;
    ppNoArLis ppParent = &pNo;
    ppNoArLis ppChild = &pChild;
    int height = 0;
    ret = getHeightLevelNode(root, word, &height, &ppParent, &ppChild, comparaLista2Palavra);
    // printf("ret2 %d %p\n\n", ret, (*ppChild));
    if(ret == false ||  (*ppChild) == NULL){
        return false;
    }
    // printf("Rmoving child %p %d %d\n\n", (*ppChild), height, max_height);
    if(emptyChildNode(ppChild) == true && height == (max_height-1 )){
        // Está no último nivel e não tem filhos, apenas remove.
        removeChildNode(ppChild);
        return ret;
    }
    return rebalancearArvore((*root), ppChild, max_height);
   
    
}
int removeArLisBal(pArLis p, void *item){
    int max_height = maxHeight(p->raiz);
    return removeBaleanceado(item, max_height, &p->raiz);
}