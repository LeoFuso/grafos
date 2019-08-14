#include "grafo.h"

TGrafo *
produce_grafo(unsigned int qtd_vertices)
{
    TGrafo *g;

    g = (TGrafo *) calloc(1, sizeof(TGrafo));
    g->qtd_vertices = qtd_vertices;
    g->qtd_arestas = 0;

    /* Aloca um vetor de lista de adjacências */
    g->lista_adjacencias = (TNo **) calloc(qtd_vertices, sizeof(TNo *));
    return g;
}

int
insert_aresta(TGrafo *g, unsigned int v, unsigned int w)
{
    TNo *novo;
    TNo *aux;
    TNo *ant;

    int parRepetido = 0;
    int verticesIguais = 0;

    ant = NULL;
    aux = g->lista_adjacencias[v];

    verticesIguais = v == w;
    if (verticesIguais)
    {
        printf("VÉRTICES [ %d, %d ] SÃO REPETIDOS\n", v, w);
        return 1;
    }

    /* Se existe aux e aux != NULL */
    while (aux && aux->vertice <= w)
    {
        /*
         * Se o grafo já tem a aresta
         * [ v - w ], a função não faz nada.
         */
        parRepetido = aux->vertice == w;
        if (parRepetido)
        {
            printf("VÉRTICES [ %d, %d ] JÁ INSERIDOS\n", v, w);
            return 1;
        }

        ant = aux; /* guarda o anterior */
        aux = aux->proximo; /* anda para frente */
    }

    novo = (TNo *) calloc(1, sizeof(TNo));
    novo->vertice = w;
    novo->proximo = aux;

    /* Se ant == NULL ou a lista está vazia ou devo inserir no início */
    if (ant == NULL)
        g->lista_adjacencias[v] = novo;
    else
        ant->proximo = novo;


    /* Atualiza o número de arestas */
    g->qtd_arestas++;

    return 0;
}

void
show(TGrafo *g)
{
    int i;
    printf("Vértices [ %d ] e Arestas [ %d ]\n\n", g->qtd_vertices, g->qtd_arestas);
    for (i = 0; i < g->qtd_vertices; i++)
    {
        TNo *aux;
        printf("Vértice [ %d ] -> ", i);

        /* para cada entrada da lista pega o início da lista */
        aux = g->lista_adjacencias[i];

        /* enquanto não chegar ao final da lista */
        while (aux != NULL)
        {
            printf("%d ", aux->vertice);
            aux = aux->proximo;
        }
        printf("\n");
    }
}

unsigned int
indeg(TGrafo *g, unsigned int w)
{
    int i;
    TNo *aux = NULL;
    int controle = g->qtd_vertices;
    unsigned int grau_de_entrada = 0;

    for (i = 0; i < controle; i++)
    {
        aux = g->lista_adjacencias[i];
        while (aux && aux->vertice)
        {
            if (aux->vertice == w)
            {
                grau_de_entrada++;
            }
            aux = aux->proximo; /* anda para frente */
        }
    }
    return grau_de_entrada;
}

unsigned int
outdeg(TGrafo *g, unsigned int w)
{
    TNo *aux = NULL;
    unsigned int grau_de_saida = 0;

    aux = g->lista_adjacencias[w];
    while (aux && aux->vertice)
    {
        grau_de_saida++;
        aux = aux->proximo; /* anda para frente */
    }
    return grau_de_saida;
}

unsigned int
is_caminho (TGrafo *g, const int *seq, unsigned int k)
{
    int i;
    for (i = 0; i < k; i++)
    {
        int v = seq[i];
        int w = seq[i + 1];

        /* a partir da entrada [ v ] verifica os seus adjacentes */
        TNo *aux = g->lista_adjacencias[v];
        while (aux && aux->vertice != w)
            aux = aux->proximo;

        /*
         * se  [ w ] não está na lista [ v ], não existe aresta e
         * consequentemente, não existe caminho
         */
        if (aux == NULL)
            return 0;

    }

    /* É caminho */
    return 1;
}
