# Projeto e Análise de Algoritmos


Implementação de uma Lista Dinamica Heterogênea Genérica Tipada em C


A Generic Dinamic Heterogeneous Typed List in C

Using:
- Debian GNU/Linux 11 (bullseye)
- gcc (Debian 10.2.1-6) 10.2.1

#

Distributed under the GNU General Public License v3.0. See [LICENSE](../LICENSE) for more information.

## Implementação

Esta lista aceitas os seguintes elementos:
    
    unsigned char
    char
    signed char
    short int
    unsigned short int
    int:
    unsigned int
    long int
    unsigned long int
    long long int 
    unsigned long long int
    float
    double
    long double
    char *
    void *
    int *
    pPilha

Para adicionar um outro elemento, edite o LDDE.h e adicione um valor para o elemento no enum `t_typename` e referencie o elemento na macro `TYPE_NUM`. Veja o exemplo de TestStruct.

A conversão é feita através do método _Generic disponível a partir do C11.

Métodos disponíveis:
1. initList - Recebe como argumento o número de elementos da lista.
2. isEmptyList: Retorna true se a lista estiver vazia.
4. sizeList: Retorna o número de elementos na lista.
5. pushList: Adiciona um elemento no fim da lista. Retorna 1 para SUCESSO e 0 para FRACASSO.
6. popList: Remove um elemento do fim da lista e retonar no pointeiro passado. Retorna 1 para SUCESSO e 0 para FRACASSO.
7. unshiftList: Adiciona um elemento no inicia da lista. Retorna 1 para SUCESSO e 0 para FRACASSO.
8. shiftList: Remove um elemento do fim da lista e retonar no pointeiro passado. Retorna 1 para SUCESSO e 0 para FRACASSO.
9. addAtList: Adiciona um elemento no lista na posicao. Retorna 1 para SUCESSO e 0 para FRACASSO.
10. removeAtList: Remove um elemento da lista da posicao e retonar no pointeiro passado. Retorna 1 para SUCESSO e 0 para FRACASSO.
11. peekAtList: Pega um elemento da lista na posicao e retonar no pointeiro passado. Retorna 1 para SUCESSO e 0 para FRACASSO.
12. peekFirstList: Pega um elemento no inicio da lista e retonar no pointeiro passado. Retorna 1 para SUCESSO e 0 para FRACASSO.
13. peekLastList: Pega um elemento no fim da lista e retonar no pointeiro passado. Retorna 1 para SUCESSO e 0 para FRACASSO.
14. destroyList: Desaloca a lista e destroy seu elementos.
15. getTypeAtList: Retorna o tipo do elemento na posicao.
16. printList: Imprime a lista na ordem ascendente de acordo com a funcao passada.
17. printListReverse: Imprime a lista na ordem descendente de acordo com a funcao passada.
#

## Exemplo simples de uso
```c
pList list;
char charValue = 'c';
int intValue = 10;
float floatValue = 99.9;
initQueue(&list);

pushList(list, charValue);
pushList(list, intValue);
pushList(list, floatValue);

popList(list, &floatValue);
popList(list, &intValue);
popList(list, &charValue);

destroyList(&list);
```

#

## Testes

O arquivo `Aplicacao.c` conta com um teste testGenericQueue e testSimpleList

### Habilitar o debug:

Defina a variavel ENABLE_DEBUG_LOG.
```c
#define ENABLE_DEBUG_LOG 1 
```

## Commands:

Na pasta raiz execute:
```console
user@debian:~$ gcc -Wall -ggdb3 -I . FEC.c Aplicacao.c pilha.o -o aplicacao

user@debian:~$ valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  ./aplicacao

```
ou
```console
user@debian:~$ make
user@debian:~$ ./aplicacao
```

## Sobre:
- Feito com base na biblioteca na função cbrt da biblioteca <math.h>
- Agradecimento ao Prof. Dr. Mauricio Aronne Pillon por disponilizar a implementação de pilha.
- Projetos desenvolvido para o curso de Pós-Graduação em Computação Aplicada na Universidade Estadual do Estado de Santa Catarina (UDESC)


Contato: @rafaeldescio