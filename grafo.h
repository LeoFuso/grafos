#ifndef GRAFO_H
#define GRAFO_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _TNo {
    unsigned int vertice;
    struct _TNo *proximo;
} TNo;

typedef struct {
    unsigned int qtd_vertices;
    int qtd_arestas;
    TNo **lista_adjacencias;
} TGrafo;

/*
 * Cria e devolve uma nova estrutura
 * TGrafo, inicializa os atributos da estrutura,
 * cria uma matriz de matriz de adjacências para
 * [ unsigned int ] vértices e zera os valores para arestas.
 */
TGrafo *produce_grafo (unsigned int);

/*
 * Cria uma aresta [ unsigned int a - unsigned int b] na
 * estrutura TGrafo.
 *
 * A função realiza a validação que [ unsigned int a ] e [ unsigned int b ]
 * são distintos, positivos e menores que [ g -> qtd_vertices ],
 * caso contrário, a função retorna '0'.
 *
 * Se o grafo já tem a aresta [ unsigned int a - unsigned int b ],
 * a função não faz nada e retorna '1'. Caso a inserção seja
 * bem sucedida, retorna '0'.
 *
 * Se a inserção dessa aresta causará um Ciclo, ele também não insere,
 * e retorna '1'.
 *
 * A função também atualiza a quantidade
 * de arestas na estrutura  TGrafo.
 */
int insert_aresta (TGrafo *, unsigned int, unsigned int);

/*
 * Calcula o grau de entrada de vértice
 * [ unsigned int ] em uma estrutura
 * TGrafo, se sucedida, retorna o seu grau de entrada.
 */
unsigned int indeg (TGrafo *, unsigned int);

/*
 * Calcula o grau de saída de um vértice
 * [ unsigned int ] em uma estrutura
 * TGrafo, se sucedida, retorna o seu grau de saída.
 */
unsigned int outdeg (TGrafo *, unsigned int);

/*
 * Verifica se uma sequência de vértices
 * na forma de um array é um caminho
 * válido na estrutura TGrafo criada.
 */
unsigned int is_caminho (TGrafo *, const int *, unsigned int);

unsigned int
is_caminho_simples(TGrafo *, const int *, unsigned int);

/*
 * Para cada vértice  [ g->vertice ] do grafo, esta função
 * imprime, em uma linha, todos os vértices
 * adjacentes à [ g->vertice ].
 */
void show (TGrafo *);

void free_graph (TGrafo *);

#endif //GRAFO_H
