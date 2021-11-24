# Projeto e Análise de Algoritmos


Implementação de uma Arvore ternária com Lista Simplesmente encadeada em C


A Ternary Tree with Linked List in C

Using:
- Debian GNU/Linux 11 (bullseye)
- gcc (Debian 10.2.1-6) 10.2.1

#

Distributed under the GNU General Public License v3.0. See [LICENSE](../LICENSE) for more information.

## Implementação

Cria uma arvore balanceada inserindo os nós folhas, na sequencia: esquerda, centro, direita.
A remocão ocorre apagando o nó caso esse esteja no último nível, ou substituindo o nó a ser removido por um nó do último nível, ou seja, substitui por um nó que não tem filhos.
O método de percorrer visita todos os nós do nível mais baixo para o mais alto, imprimindo todos os nós de mesmo nível na sequencia da esquerda para direita.


Métodos disponíveis:
1. criaArLisBal - Criar uma nova ArLis.
2. insereArLisBal: Insere um novo caracter na lista atual, se o caracter, for espaco ou nova linha, salva a lista atual em um nó da arvore, e reinicia a lista.
4. removeArLisBal: Remove um nó árvore no qual a lista corresponda a palavra passada.
5. percursoArLisBal: Percorre a árvore executando o método passado em cada nó.
6. nivelArLis: Retorna um inteiro com o nível da lista.
7. imprimeRelatorio: Criar um arquivo `report_file.log` com os dados de comparacões e uma impressão da árvore.
8. destroiArLisBal: Destroi a ArLis.

#

## Exemplo simples de uso
```c
int comparaDados(void *dado1, void *dado2)
{
  int n1 = *((int *)dado1);
  int n2 = *((int *)dado2);
  return n1 - n2;
}

pArLis arlis;
int intValue = 33;
criaArLisBal(&arlis, sizeof(int));

insereArLisBal(arlis, &intValue, comparaDados);

destroiArLisBal(&arlis);
```

#

## Commands:

Na pasta raiz execute:
```console
user@debian:~$ gcc -Wall -ggdb3 -ggdb3 -c libs/LDSE.c -o libs/LDSE.o
user@debian:~$ gcc -Wall -ggdb3 -c ArLisEx.c -o ArLisEx.o
user@debian:~$ gcc -Wall -ggdb3 -I . aplicacao.c ArLisEx.o ArLis.o libs/LDSE.o libs/LDSEEx.o -o aplicacao

user@debian:~$ valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  ./aplicacao

```
ou
```console
user@debian:~$ make
user@debian:~$ ./aplicacao <filename>
```

## Sobre:
- Projetos desenvolvido para o curso de Pós-Graduação em Computação Aplicada na Universidade Estadual do Estado de Santa Catarina (UDESC)


Contato: @rafaeldescio