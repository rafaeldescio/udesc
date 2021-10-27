#include "ABB_privado.h"

// #define ENABLE_DEBUG_LOG  1
#ifdef ENABLE_DEBUG_LOG
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define LOG_D(fmt, args...)              \
  {                                      \
    printf("D:");                        \
    fprintf(stdout, fmt, ##args);        \
  }
#define LOG_E(fmt, args...)              \
  {                                      \
    printf(ANSI_COLOR_RED "E:" );        \
    fprintf(stdout, fmt, ##args);        \
    printf(ANSI_COLOR_RESET);            \
  }
#else
#define LOG_D(fmt, args...) // it does nothing
#define LOG_E(fmt, args...) // it does nothing
#endif


TreeElement newElement(void *val, size_t typesize, TreeElement left, TreeElement right){
  TreeElement newElem = malloc(sizeof(struct tree_element));
  void *destAddr = malloc(typesize);
  memcpy(destAddr, val, typesize);
  newElem->element = destAddr;
  newElem->typesize = typesize;
  newElem->left = left;
  newElem->right = right;
  return newElem;
}

 int criaABB(ppABB abb, size_t element_size){
  LOG_D("Starting a empty tree. \n" );
  (*abb) = malloc(sizeof(struct bsTree));
  if((*abb) == NULL){
    LOG_E("Failed to create a new tree");
    return FAILURE;
  }
  (*abb)->root = NULL;
  (*abb)->element_size = element_size;
  return SUCCESS;
}


int testaVaziaABB(pABB s) {
  if (s == NULL){
		return FAILURE;
  }
	if (s->root == NULL){
		return SUCCESS;
  }
  return FAILURE;
}


int _compareInsert(TreeElement el1, TreeElement el2, int (*compareFunc)(void*, void*) ){
  int ret = compareFunc(el2->element, el1->element);
  LOG_D("Testing element %d\n", ret);
  if (ret < 0) {
    if (el1->left != NULL) {
      return _compareInsert(el1->left, el2, compareFunc);
    } else {
      LOG_D("Inserted left\n");
      el1->left = el2;
      el2->parent = el1;
      return SUCCESS;
    }
  } 
  if (ret > 0) {
    if (el1->right != NULL) {
      return _compareInsert(el1->right, el2, compareFunc);
    } else {
      LOG_D("Inserted right\n");
      el1->right = el2;
      el2->parent = el1;
      return SUCCESS;
    }
  }
  LOG_D("Value already exists -> %d\n", ret);
  return FAILURE;
}

int insereABB(pABB s, void *element, int (*compareFunc)(void*, void*)) {
  // Verifica se os parâmetros estão vazios. Retorna um erro caso esteja.
  if ( s == NULL || element == NULL) {
    LOG_E("Invalid insert element.\n");
    return FAILURE;
  }

  TreeElement new_element = newElement(element, s->element_size, NULL, NULL);
  if(s->root == NULL){
    LOG_D("Root element added\n");
    s->root = new_element;
  } else {
    LOG_D("Adding new\n");
    TreeElement elT = s->root;
    int ret = _compareInsert(elT, new_element, compareFunc);
    if(ret != SUCCESS){
      free(new_element->element);
      free(new_element);
      return FAILURE;
    }
  }
  return SUCCESS;
}

int findSucessor(TreeElement rootElement, TreeElement* successor){
  LOG_D("Finding successor\n");
  (*successor) = rootElement->right;
  while((*successor) != NULL && (*successor)->left != NULL){
    (*successor) = (*successor)->left;
  }
  return SUCCESS;
}

int _internalDeleteNode(pABB s, TreeElement rootElement, TreeElement* retElement, void* delete_element, int (*compareFunc)(void*, void*)) {
  if(rootElement == NULL){
    return FAILURE;
  }
  
  int retResult = compareFunc(rootElement->element, delete_element);

  // Node value is less than the deleted element. Go right
  if(retResult < 0){
    // No subtree right - Element not found
    if(rootElement->right == NULL){
      return FAILURE;
    }
    int ret = _internalDeleteNode(s, rootElement->right, retElement, delete_element, compareFunc);
    if(ret == SUCCESS){
      rootElement->right = (*retElement);
      (*retElement) = rootElement;
    }
    return ret;
  }

  // Node value is greater than the deleted element. Go left
  if(retResult > 0){
    // No subtree left - Element not found
    if(rootElement->left == NULL){
      return FAILURE;
    }
    int ret = _internalDeleteNode(s, rootElement->left, retElement, delete_element, compareFunc);
    if(ret == SUCCESS){
      rootElement->left = (*retElement);
      (*retElement) = rootElement;
    }
    return ret;
  }

  // Found the node
  if(retResult == 0){
    // Node has no child
    if(rootElement->left == NULL && rootElement->right == NULL){
      free(rootElement->element);
      free(rootElement);
      rootElement = NULL;
      (*retElement) = NULL;
      return SUCCESS;
    }else if(rootElement->left == NULL){
      //Node has no child left
      TreeElement right = rootElement->right;
      (*retElement) = right;
      free(rootElement->element);
      free(rootElement);
      rootElement = NULL;
      return SUCCESS;
    }else if(rootElement->right == NULL){
      //Node has no child right
      TreeElement left = rootElement->left;
      (*retElement) = left;
      free(rootElement->element);
      free(rootElement);
      rootElement = NULL;
      return SUCCESS;
    } else {
      //Node has two children
      TreeElement* successor = malloc(sizeof(TreeElement*));
      findSucessor(rootElement, successor);
      if((*successor) != NULL){
        memcpy(rootElement->element, (*successor)->element, s->element_size);
        _internalDeleteNode(s, rootElement->right, retElement, (*successor)->element, compareFunc);
        rootElement->right = *retElement;
        (*retElement) = rootElement;
      }
      free(successor);
      return SUCCESS;
    }
  }
  return FAILURE;
}

int findNode(TreeElement rootElement, void* delete_element, int (*compareFunc)(void*, void*), TreeElement* nodeFound){
  if(rootElement == NULL){
    return FAILURE;
  }
  int retResult = compareFunc(rootElement->element, delete_element);
  if(retResult < 0){
    return findNode(rootElement->right, delete_element, compareFunc, nodeFound);
  }
  if(retResult > 0){
    return findNode(rootElement->left, delete_element, compareFunc, nodeFound);
  }
  if(retResult == 0){
    (*nodeFound) = rootElement;
    return SUCCESS;
  }
  (*nodeFound) = NULL;
  return FAILURE;
}
int buscaABB(pABB s, void* find_element, int (*compareFunc)(void*, void*)){
  if(s == NULL){
    return FAILURE;
  }
  if(testaVaziaABB(s) == SUCCESS){
    return FAILURE;
  }
  TreeElement *nodeFound = malloc(sizeof(TreeElement*));
  *nodeFound = NULL;
  findNode(s->root, find_element, compareFunc, nodeFound);
  if((*nodeFound) == NULL){
    free(nodeFound);
    return FAILURE;
  }
  memcpy(find_element, (*nodeFound)->element, s->element_size);
  free(nodeFound);
  return SUCCESS;
}
int removeABB(pABB s, void* delete_element, int (*compareFunc)(void*, void*) ){
  if(s == NULL){
    return FAILURE;
  }
  if(testaVaziaABB(s)){
    return FAILURE;
  }
  if(delete_element == NULL){
    return FAILURE;
  }
  TreeElement* retElement = malloc(sizeof(TreeElement*));
  int ret = _internalDeleteNode(s, s->root, retElement, delete_element, compareFunc);
  if(ret == SUCCESS){
    s->root = *retElement;
  }
  free(retElement);
  return ret;
}

int destroyElement(TreeElement el){
  if(el == NULL){
    return SUCCESS;
  }
  TreeElement leftElement  = el->left;
  TreeElement rightElement = el->right;
  if(leftElement != NULL){
    destroyElement(leftElement);
  }
  if(rightElement != NULL){
    destroyElement(rightElement);
  }
  free(el->element);
  el->element = NULL;
  free(el);
  el = NULL;
  return SUCCESS;
}
int reiniciaABB(pABB s) {
  if(s == NULL){
    return FAILURE;
  }
  destroyElement(s->root);
  s->root = NULL;
  return SUCCESS;
}

int destroiABB(ppABB s) {
  if((*s) == NULL){
    return FAILURE;
  }
  reiniciaABB((*s));
  free((*s));
  (*s) = NULL;
  return SUCCESS;
}

int goLeftPos(TreeElement el, void (*printFunc)(void*)){
  
  TreeElement leftElement = el->left;
  TreeElement rightElement = el->right;
  if(leftElement != NULL){
    goLeftPos(leftElement, printFunc);
  }
  if(rightElement != NULL){
    goLeftPos(rightElement, printFunc);
  }
  printFunc(el->element);
  return SUCCESS;
}
int percursoPosOrdem(pABB s, void (*printFunc)(void*)){
  if(s == NULL){
    return FAILURE;
  }
  if(testaVaziaABB(s) == SUCCESS){
    return FAILURE;
  }
  TreeElement rootElement = s->root;
 
  if(rootElement->left != NULL){
    goLeftPos(rootElement->left, printFunc);
  }
  if(rootElement->right != NULL){
    goLeftPos(rootElement->right, printFunc);
  }
  printFunc(rootElement->element);
  return SUCCESS;
}

int goLeftPre(TreeElement el, void (*printFunc)(void*)){
  
  TreeElement leftElement = el->left;
  TreeElement rightElement = el->right;
  printFunc(el->element);
  if(leftElement != NULL){
    goLeftPre(leftElement, printFunc);
  }
  if(rightElement != NULL){
    goLeftPre(rightElement, printFunc);
  }
  return SUCCESS;
}

int percursoPreOrdem(pABB s, void (*printFunc)(void*)){
  if(s == NULL){
    return FAILURE;
  }
  if(testaVaziaABB(s) == SUCCESS){
    return FAILURE;
  }

  TreeElement rootElement = s->root;

  printFunc(rootElement->element);
  if(rootElement->left != NULL){
    goLeftPre(rootElement->left, printFunc);
  }
  if(rootElement->right != NULL){
    goLeftPre(rootElement->right, printFunc);
  }
  return SUCCESS;
}

int goLeft(TreeElement el, void (*printFunc)(void*)){
  
  TreeElement leftElement = el->left;
  TreeElement rightElement = el->right;
  if(leftElement != NULL){
    goLeft(leftElement, printFunc);
  }
  printFunc(el->element);
  if(rightElement != NULL){
    goLeft(rightElement, printFunc);
  }
  return SUCCESS;
}
int percursoEmOrdem(pABB s, void (*printFunc)(void*)){
  if(s == NULL){
    return FAILURE;
  }
  if(testaVaziaABB(s) == SUCCESS){
    return FAILURE;
  }

  TreeElement rootElement = s->root;

  if(rootElement->left != NULL){
    goLeft(rootElement->left, printFunc);
  }
  printFunc(rootElement->element);
  if(rootElement->right != NULL){
    goLeft(rootElement->right, printFunc);
  }
  return SUCCESS;
}