# Projeto e Análise de Algoritmos


Implementação de uma Fila Estática Circular Heterogênea Genérica Tipada em C


A Generic Static Circular Heterogeneous Typed Queue in C

Using:
- Debian GNU/Linux 10 (buster)
- gcc (Debian 8.3.0-6) 8.3.0

#

Distributed under the GNU General Public License v3.0. See [LICENSE](../LICENSE) for more information.

## Implementação

Esta fila aceitas os seguintes elementos:
    
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

A conversão é feita através do método _Generic disponível a partir do C11.
A inicialização da fila recebe o número máximo de elementos da fila.  
Métodos disponíveis:
1. initQueue - Recebe como argumento o número de elementos da fila.
2. isEmptyQueue: Retorna true se a fila estiver vazia.
3. isFullQueue: Retorna true se a fila estiver cheia.
4. sizeQueue: Retorna o número de elementos na fila.
5. enQueue: Adiciona um elemento na fila. Retorna um 1 para SUCESSO e 2 para FRACASSO.
6. deQueue: Remove um elemento na fila. Retorna um 1 para SUCESSO e 2 para FRACASSO.
7. deQueueAndGet: Remove um elemento na fila e retorna o elemento no pointeiro `void*` recebido. Retorna um 1 para SUCESSO e 2 para FRACASSO.
8. deQueueTyped: Remove um elemento na fila para o tipo passado e retorna um ponteiro para o elemento removido ou `NULL` se falhar.
9. nextQueueType: Retorna um inteiro pro tipo do proximo elemento da fila.
10. getTypeName: Retorna uma texto para o inteiro do tipo passado.
11. destroyQueue: Desaloca a fila e destroy seu elementos.

## Testes

O arquivo `Aplicacao.c` conta com um teste:
### testGenericQueue:
1.  Alimenta a fila com elementos de um array de ints com 5 elementos, depois remove 2 elementos. 
2. Adicionas mais 2 inteiros. 
3. Adiciona um Double. 
4. Adicionar um Char.
5. Tenta adicionar um tipo não reconhecido (Que deve falhar)
6. Adiciona um array de chars (string)
7. Remove 3 elementos sem guardar o retorno
8. Remove um elemento int através de pointeiro e imprime
9. Remove um elemento tipado de int e imprime
10. Remove um elemento tipado de double e imprime
11. Remove um elemento tipado de char e imprime
12. Remove um elemento tipado de char* e imprime
13. Adiciona dois elemento do tipo pPilha
14. Remove um elemento do tipo pPilha e desempilha os valores
15. Destroi a fila (deixando uma pilha sem remover, para ser destruida junto com fila).


## Commands:

Na pasta raiz execute:
```sh
gcc -Wall -ggdb3 -I . Aplicacao.c Pilha.c -o Aplicacao

valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  ./Aplicacao
```
## Sobre:
- Agradecimento ao Prof. Dr. Mauricio Aronne Pillon por disponilizar a implementação de pilha.
- Projetos desenvolvido para o curso de Pós-Graduação em Computação Aplicada na Universidade Estadual do Estado de Santa Catarina


Contato: @rafaeldescio