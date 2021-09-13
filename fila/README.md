# Projeto e Análise de Algoritmos


Implementação de uma Pilha Estática Homogênea Genérica em C


A Generic Static Stack in C

Using:
- Debian GNU/Linux 10 (buster)
- gcc (Debian 8.3.0-6) 8.3.0

#

Distributed under the GNU General Public License v3.0. See [LICENSE](../LICENSE) for more information.

## Implementação

A inicialização da pilha recebe o tamanho do elemento e o número máximo de elementos da pilha. No entanto, a memória não é totalmente alocada no início. Essa capacidade máxima é controlada pela variável `capacity` que é incrementada toda vez que o limite de `init_size` elementos é rompido.

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

1. testIntegerStack: Alimenta a pilha com elementos de um array de strings e depois os remove da pilha. Compara os elementos que foram adicionados com os que foram removidos.
2. testStringStack: Alimenta a pilha com elementos de um array de ints e depois os remove da pilha. Compara os elementos que foram adicionados com os que foram removidos.
3. testStruckStack: Alimenta a pilha com elementos de um array de Teststruct e depois os remove da pilha.
4. testUserStack: Recebe como input do usuário um int e printa a representação desse int em binário.
5. Habitar os logs. Descomente a linha  // #define ENABLE_DEBUG_LOG  
6. Commands:


```sh
gcc -Wall -ggdb3 -I . Aplicacao.c Pilha.c -o Aplicacao

valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  ./Aplicacao
```