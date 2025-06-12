#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Códigos de cor terminal
#define RED_TEXT "\033[1;31m"
#define BLUE_TEXT "\033[1;34m"
#define GREEN_TEXT "\033[1;32m"
#define RESET_TEXT "\033[0m"

// Estrutura para representar um nó na lista de adjacência
typedef struct Elemento {
    int vertice;
    struct Elemento* prox;
} Elemento;

// Estrutura para representar o dígrafo
typedef struct Grafo {
    int num_vertices;
    Elemento** adj; // Array de ponteiros para as listas de adjacência
} Grafo;

// Estrutura para a pilha (usada na DFS)
typedef struct Pilha {
    Elemento* topo; // Ponteiro para o topo da pilha
    int tamanho;    // Tamanho atual da pilha
} Pilha;

// Estrutura para a fila (usada na BFS)
typedef struct Fila {
    Elemento *inicio;
    Elemento *fim;
    int tamanho;
} Fila;

// Protótipos das funções
Grafo* criar_grafo(int num_vertices);
void adicionar_aresta(Grafo* grafo, int origem, int destino);
void imprimir_grafo(Grafo* grafo);

// Funções da Pilha
Pilha* criar_pilha();
int push(Pilha* pilha, int vertice);
int pop(Pilha* pilha);
bool pilha_vazia(Pilha* pilha);
void libera_pilha(Pilha* pilha);
void imprime_pilha(Pilha* pilha);

// Funções da Fila
Fila* criar_fila();
int enfileira(Fila* fila, int vertice);
int desenfileira(Fila* fila);
bool fila_vazia(Fila* fila);
void libera_fila(Fila* fila);

// Funções de Busca
void DFS(Grafo* grafo, int vertice_inicial);
void BFS(Grafo* grafo, int vertice_inicial);

// Funções de Busca com Destino (Parte Opcional)
void DFS_com_destino(Grafo* grafo, int vertice_inicial, int vertice_destino);
void BFS_com_destino(Grafo* grafo, int vertice_inicial, int vertice_destino);

#endif