# Projeto e Análise de Algoritmos


Implementação de uma Fila Estática Circular Heterogênea Genérica em C


A Generic Static Circular Heterogeneous Queue in C

Using:
- Debian GNU/Linux 10 (buster)
- gcc (Debian 8.3.0-6) 8.3.0

#

Distributed under the GNU General Public License v3.0. See [LICENSE](../LICENSE) for more information.

## Implementação

A inicialização da fila recebe o número máximo de elementos da fila.  

1. init - Recebe como argumento o tamanho do elemento e o número de elementos da pilha.
2. isEmpty: Retorna true se a pilha estiver vazia.
3. isFull: Retorna true se a pilha estiver cheia.
4. size: Retorna o número de elementos na pilha.
5. push: Adiciona um elemento na pilha. Retorna `NULL` se a pilha já estiver cheia.
6. pop: Retira e retorna o elemento do topo da pilha. Retorna `NULL` se a pilha estiver vazia.
7. top: Retorna o elemento do topo da pilha. Retorna `NULL` Se a pilha estiver vazia.
8. destroy: Desaloca a pilha e retorna os indicadores de tamanho atual e capacidade para 0.

## Testes

O arquivo `Aplicacao.c` conta com três testes:

1. testIntegerQueue: Alimenta a fila com elementos de um array de strings e depois os remove da fila. Compara os elementos que foram adicionados com os que foram removidos.
2. testStringQueue: Alimenta a fila com elementos de um array de ints e depois os remove da fila. Compara os elementos que foram adicionados com os que foram removidos.
3. testStackQueue: Alimenta a fila com elementos de uma Pilha depois os remove da fila.
5. Habitar os logs. Descomente a linha  // #define ENABLE_DEBUG_LOG  
6. Commands:


```sh
gcc -Wall -ggdb3 -I . Aplicacao.c Pilha.c -o Aplicacao

valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  ./Aplicacao
```