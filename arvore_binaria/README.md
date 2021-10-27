# Projeto e Análise de Algoritmos


Implementação de uma Arvore de Busca Binaria em C


A Binary Search Tree in C

Using:
- Debian GNU/Linux 11 (bullseye)
- gcc (Debian 10.2.1-6) 10.2.1

#

Distributed under the GNU General Public License v3.0. See [LICENSE](../LICENSE) for more information.

## Implementação

A inicialização da arvore recebe um ponteiro para pointeiro e o tamanho dos elementos quer serão inseridos .  
Métodos disponíveis:
1. initQueue - Recebe como argumento o número de elementos da fila.
2. isEmptyQueue: Retorna true se a fila estiver vazia.
3. isFullQueue: Retorna true se a fila estiver cheia.
4. sizeQueue: Retorna o número de elementos na fila.
5. enQueue: Adiciona um elemento na fila. Retorna 1 para SUCESSO e 0 para FRACASSO.
6. deQueue: Remove um elemento da fila e retonar no pointeiro passado. Retorna 1 para SUCESSO e 0 para FRACASSO.
9. nextQueueType: Retorna um inteiro pro tipo do proximo elemento da fila.
10. getTypeName: Retorna uma texto para o inteiro correpondente ao tipo passado.
11. destroyQueue: Desaloca a fila e destroy seu elementos.

#

## Exemplo simples de uso
```c
char charValue = 'c';
int intValue = 10;
float floatValue = 99.9;
Queue queue = initQueue(3);

enQueue(queue, charValue);
enQueue(queue, intValue);
enQueue(queue, floatValue);

deQueue(queue, &charValue);
deQueue(queue, &intValue);
deQueue(queue, &floatValue);

destroyQueue(queue);
```

#

## Testes

O arquivo `Aplicacao.c` conta com um teste:
### testGenericQueue:
1.  Alimenta a fila com elementos de um array de ints com 5 elementos, depois remove 2 elementos. 
2. Adicionas mais 2 inteiros. 
3. Adiciona um Double. 
4. Adicionar um Char.
5. Tenta adicionar um tipo não reconhecido (Que deve falhar)
6. Adiciona um array de chars (string)
7. Remove 3 elementos tipado int
8. Remove um elemento tipado int e imprime
9. Remove um elemento tipado de int e imprime
10. Remove um elemento tipado de double e imprime
11. Remove um elemento tipado de char e imprime
12. Remove um elemento tipado de char* e imprime
13. Adiciona dois elemento do tipo pPilha
14. Remove um elemento do tipo pPilha e desempilha os valores
15. Destroi a fila (deixando um elemento pilha sem remover, para ser destruido junto com fila).


## Commands:

Na pasta raiz execute:
```console
user@debian:~$ gcc -Wall -ggdb3 -I . ABB.c Aplicacao.c pilha.o -o aplicacao

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