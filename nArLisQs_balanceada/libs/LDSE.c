
#include "LDSE_privado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int criarLDSEContador(CounterLDSE ** c){
    (*c) = (CounterLDSE *)malloc(sizeof(CounterLDSE));
    if((*c) == NULL)
        return FRACASSO;
	(*c)->compara = 0;
    return SUCESSO;
}

/* Cria uma LDSE */
int criaLDSE(ppLDSE pp, int tamanho_info)
{
	/* aloca descritor */
	(*pp) = (LDSE *)malloc(sizeof(LDSE));
    if( (*pp) == NULL)
    	return FRACASSO;
	if(criarLDSEContador(&(*pp)->contador) == FRACASSO){
        return FRACASSO;
    }
	/* inicia atributos */
	(*pp)->tamanho_info = tamanho_info;
	(*pp)->inicio = NULL;

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/

int destroiLDSEContador(CounterLDSE** c){
	if((*c) == NULL)
		return FRACASSO;
	free((*c));
	(*c) = NULL;
	return SUCESSO;
}

/* Destroi uma LDSE */
int destroiLDSE(ppLDSE pp)
{
	if( (*pp) == NULL)
		return FRACASSO;

	/* reinicia e desaloca o descritor */
	reiniciaLDSE((*pp));
	destroiLDSEContador(&(*pp)->contador);
	free((*pp));
	(*pp) = NULL;

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


int reiniciaLDSEContador(CounterLDSE** c){
	if( (*c) == NULL)
		return FRACASSO;
	(*c)->compara = 0;
	return SUCESSO;
}

/* reinicia a LDSE, desalocando todos os dados */
int reiniciaLDSE(pLDSE p)
{
	NoLDSE *aux, *prox;

	if(p == NULL)
		return FRACASSO;

	/* caminha pela lista e desaloca todos os n�s */
	aux = p->inicio;
	while(aux != NULL){
		prox = aux->proximo;
		destroiLDSEContador(&aux->contador);
		free(aux->dados);
		free(aux);
		aux = prox;
	}

	p->inicio = NULL;

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


/* Testa se a LDSE est� vazia */
int testaVazia(pLDSE p)
{
	if(p == NULL)
		return FRACASSO;

	if(p->inicio == NULL)
		return SUCESSO;
	else
		return FRACASSO;

}


/*-------------------------------------------------------------------------*/


/* retorna a quantidade de elementos da LDSE */
int contaElementos(pLDSE p)
{
	if(p == NULL)
		return FRACASSO;

	int n = 0;
	NoLDSE *aux = p->inicio;

	/* conta os elementos da lista */
	while(aux != NULL){
		aux = aux->proximo;
		n++;
	}

	return n;
}


/*-------------------------------------------------------------------------*/


/* insere um elemento no in�cio da LDSE */
int insereInicio(pLDSE p, void *elemento)
{
	NoLDSE *novo;

	if(p == NULL)
		return FRACASSO;

	novo = (NoLDSE *)malloc(sizeof(NoLDSE));
	if(novo == NULL)
		return FRACASSO;
	novo->dados = (void *)malloc(p->tamanho_info);
	if(novo->dados == NULL){
		free(novo);
		return FRACASSO;
	}
	memcpy(novo->dados, elemento, p->tamanho_info);
	novo->proximo = NULL;

	novo->proximo = p->inicio;
	p->inicio = novo;
	if(criarLDSEContador(&(novo)->contador) == FRACASSO){
        return FRACASSO;
    }
	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


/* insere um elemento no final da LDSE */
int insereFim(pLDSE p, void *elemento)
{
	NoLDSE *novo, *fim;

	if(p == NULL)
		return FRACASSO;
	if(testaVazia(p))
		return insereInicio(p, elemento);

	novo = (NoLDSE *)malloc(sizeof(NoLDSE));
	if(novo == NULL)
		return FRACASSO;
	novo->dados = (void *)malloc(p->tamanho_info);
	if(novo->dados == NULL){
		free(novo);
		return FRACASSO;
	}
	memcpy(novo->dados, elemento, p->tamanho_info);
	novo->proximo = NULL;
	if(criarLDSEContador(&(novo)->contador) == FRACASSO){
        return FRACASSO;
    }
	fim = p->inicio;
	while(fim->proximo != NULL){
		fim = fim->proximo;
	}
	fim->proximo = novo;
	novo->proximo = NULL;

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


int inserePosicao(pLDSE p, int N, void *elemento)
{
	NoLDSE *aux, *anterior, *novo;
	int n;

	if(p == NULL)
		return FRACASSO;
	if(N > contaElementos(p))
		return insereFim(p, elemento);
	if(testaVazia(p) || N == 1)
		return insereInicio(p, elemento);

	novo = (NoLDSE *)malloc(sizeof(NoLDSE));
	if(novo == NULL)
		return FRACASSO;
	novo->dados = (void *)malloc(p->tamanho_info);
	if(novo->dados == NULL){
		free(novo);
		return FRACASSO;
	}
	if(criarLDSEContador(&(novo)->contador) == FRACASSO){
        return FRACASSO;
    }
	memcpy(novo->dados, elemento, p->tamanho_info);
	novo->proximo = NULL;

	anterior = p->inicio;
	aux = anterior->proximo;
	n = 2;
	while(n < N){
		anterior = aux;
		aux = aux->proximo;
		n++;
	}

	anterior->proximo = novo;
	novo->proximo = aux;

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


/* remove o primeiro elemento da LDSE */
int removeInicio(pLDSE p, void *elemento)
{
	NoLDSE *aux;

	if(p == NULL)
		return FRACASSO;
	if(testaVazia(p))
		return FRACASSO;

	aux = p->inicio;
	memcpy(elemento, aux->dados, p->tamanho_info);
	p->inicio = aux->proximo;
	destroiLDSEContador(&aux->contador);
	free(aux->dados);
	free(aux);

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


/* remove o �ltimo elemento da LDSE */
int removeFim(pLDSE p, void *elemento)
{
	NoLDSE *aux, *anterior;

	if(p == NULL)
		return FRACASSO;
	if(testaVazia(p))
		return FRACASSO;
	if(contaElementos(p) == 1)
		return removeInicio(p, elemento);

	anterior = p->inicio;
	aux = anterior->proximo;
	while(aux->proximo != NULL){
		anterior = aux;
		aux = aux->proximo;
	}

	memcpy(elemento, aux->dados, p->tamanho_info);
	destroiLDSEContador(&aux->contador);
	free(aux->dados);
	free(aux);
	anterior->proximo = NULL;

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


/* remove o en�simo elemento da LDSE */
int removePosicao(pLDSE p, int N, void *elemento)
{
	NoLDSE *aux, *anterior;
	int n;

	if(p == NULL)
		return FRACASSO;
	if(testaVazia(p))
		return FRACASSO;

	n = contaElementos(p);
	if(N > n)
		return FRACASSO;
	if(N == n)
		return removeFim(p, elemento);
	if(N == 1)
		return removeInicio(p, elemento);

	anterior = p->inicio;
	aux = anterior->proximo;
	n = 2;
	while(n < N){
		anterior = aux;
		aux = aux->proximo;
		n++;
	}

	/* desaloca os dados e atualiza encadeamento */
	memcpy(elemento, aux->dados, p->tamanho_info);
	anterior->proximo = aux->proximo;
	destroiLDSEContador(&aux->contador);
	free(aux->dados);
	free(aux);

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


/* busca o elemento no in�cio da LDSE */
int buscaInicio(pLDSE p, void *elemento)
{
	if(p == NULL)
		return FRACASSO;
	if(testaVazia(p))
		return FRACASSO;

	memcpy(elemento, p->inicio->dados, p->tamanho_info);

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


/* busca o elemento no final da LDSE */
int buscaFim(pLDSE p, void *elemento)
{
	NoLDSE *fim;

	if(p == NULL)
		return FRACASSO;
	if(testaVazia(p))
		return FRACASSO;

	fim = p->inicio;
	while(fim->proximo != NULL){
		fim = fim->proximo;
	}
	memcpy(elemento, fim->dados, p->tamanho_info);

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/

int buscaPosicao(pLDSE p, int N, void *elemento)
{
	NoLDSE *aux;
	int n;

	if(p == NULL)
		return FRACASSO;
	n = contaElementos(p);
	if(N > n || n == 0)
		return FRACASSO;

	aux = p->inicio;
	n = 1;
	while(n < N){
		aux = aux->proximo;
		n++;
	}
	memcpy(elemento, aux->dados, p->tamanho_info);

	return SUCESSO;
}


/*-------------------------------------------------------------------------*/


/* imprime os elementos na tela (s� funciona para inteiros) */
void imprimeInt(pLDSE p)
{
	NoLDSE *aux;
	int elemento;

	if(p == NULL)
		return;
	if(testaVazia(p))
		return;

	aux = p->inicio;
	while(aux != NULL){
        memcpy(&elemento, aux->dados, p->tamanho_info);
		printf("%i ", elemento);
		aux = aux->proximo;
	}

	return;
}


/* imprime os elementos na tela (s� funciona para inteiros) */
void imprimeChar(pLDSE p)
{
	NoLDSE *aux;
	int elemento;

	if(p == NULL)
		return;
	if(testaVazia(p))
		return;

	aux = p->inicio;
	while(aux != NULL){
        memcpy(&elemento, aux->dados, p->tamanho_info);
		printf("%c", elemento);
		aux = aux->proximo;
	}

	return;
}

// ----------------------------
// ----------- EXTRA ----------
// -- Printe node full size ---
// ----------------------------
void imprimeCharFilter(pLDSE p, int word_size, int filter)
{
	NoLDSE *aux;
	int elemento;

	if(p == NULL)
		return;
	if(testaVazia(p))
		return;
	word_size= word_size -2;
	aux = p->inicio;
	int size = contaElementos(p);
	int temp_word_size = 0;
	if(size < word_size){
		temp_word_size = word_size - size ;
	}
	int half_word = ceil(temp_word_size/2) +1;
	printf("[");
	for(int i = 1; i < half_word; i++){
		printf(" ");
	}
	int count = 0;

	while(aux != NULL){
        memcpy(&elemento, aux->dados, p->tamanho_info);
		if(elemento != filter){
			printf("%c", elemento);
			count++;
		}
		aux = aux->proximo;
	}

	for(int i = half_word+count; i <= word_size; i++){
		printf(" ");
	}
	printf("]");
	return;
}
void imprimeCharFilterFile(pLDSE p, int word_size, int filter, FILE* f)
{
	NoLDSE *aux;
	int elemento;

	if(p == NULL)
		return;
	if(testaVazia(p))
		return;
	word_size= word_size -2;
	aux = p->inicio;
	int size = contaElementos(p);
	int temp_word_size = 0;
	if(size < word_size){
		temp_word_size = word_size - size ;
	}
	int half_word = ceil(temp_word_size/2) +1;
	fprintf(f,"[");
	for(int i = 1; i < half_word; i++){
		fprintf(f," ");
	}
	int count = 0;

	while(aux != NULL){
        memcpy(&elemento, aux->dados, p->tamanho_info);
		if(elemento != filter){
			fprintf(f,"%c", elemento);
			count++;
		}
		aux = aux->proximo;
	}

	for(int i = half_word+count; i <= word_size; i++){
		fprintf(f," ");
	}
	fprintf(f,"]");
	return;
}
// Compara a palavra com as letras inseridas na lista
int comparaLista2Palavra(pLDSE p, char *palavra)
{
	NoLDSE *aux;
	int elemento;
	int ct=0;
	int flag=0;
	int flag2=0;

	int nlista = contaElementos(p);

	if(p == NULL)
		return FRACASSO;
	if(testaVazia(p))
		return FRACASSO;

	aux = p->inicio;
	(p->contador)->compara++;
	while(aux != NULL){
			(aux->contador)->compara++;
 		  // printf("busca (%s)", palavra);
			// imprimeChar(p);
			// if (ct == (nlista-1)) {
			// 	printf("OKOK (%d)", ct);
			// 	return SUCESSO;
			// }
			if ((*((char*)aux->dados) >= 33) && (*((char*)aux->dados) < 123)) {
				// printf("[%c,%c]", *((char*)aux->dados), palavra[ct]);

  			if (*((char*)aux->dados) == palavra[ct]) {
				  
					 flag++;
					 flag2++;
		       //printf("(%d/%d)[%c,%c]\n", flag, nlista-1, *((char*)aux->dados), palavra[ct]);
			 }
		}
			ct++;
		aux = aux->proximo;
	}
	if ((flag == nlista-1) && (flag2) && (flag == strlen(palavra))) {
	   return SUCESSO;
	} else {
		return FRACASSO;
	}
  //printf("OKOK {%d}", ct);

}

int pegaContagemLista(pLDSE p, int* valor){
	if(p->contador == NULL){
		(*valor) = 0;
		return FRACASSO;
	}
	(*valor) = p->contador->compara;
	return SUCESSO;
}

int pegaContagemPorPosicao(pLDSE p, int N, int* valor){
		NoLDSE *aux;
	int n;

	if(p == NULL)
		return FRACASSO;
	n = contaElementos(p);
	if(N > n || n == 0)
		return FRACASSO;

	aux = p->inicio;
	n = 1;
	while(n < N){
		aux = aux->proximo;
		n++;
	}
	if(aux->contador == NULL){
		return FRACASSO;
	}
	(*valor) = aux->contador->compara;
	return SUCESSO;
}