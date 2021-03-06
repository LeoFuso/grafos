#include "grafo.h"

/*
 Visita todos os vértices possíveis de se chegar dado um [ verticeOrigem ]
 marcando-os como visitados, usando o algoritmo de Busca em Profundidade
*/
void busca_profundidade (TGrafo *, unsigned int, int *);

/*
 * Função de comparação utilizada pela
 * implementação do QuickSort.
 *
 * Realiza a comparação entre inteiros simples
 */
int int_qsort_comparator (const void *c1, const void *c2);

TGrafo *
produce_grafo (unsigned int qtd_vertices)
{
    TGrafo *g;

    g = (TGrafo *) calloc (1, sizeof (TGrafo));
    g->qtd_vertices = qtd_vertices;
    g->qtd_arestas = 0;

    /* Aloca um vetor de lista de adjacências */
    g->lista_adjacencias = (TNo **) calloc (qtd_vertices, sizeof (TNo *));
    return g;
}

int
insert_aresta (TGrafo *g, unsigned int v, unsigned int w)
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
        printf ("VÉRTICES [ %d, %d ] SÃO REPETIDOS\n", v, w);
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
            printf ("VÉRTICES [ %d, %d ] JÁ INSERIDOS\n", v, w);
            return 1;
        }

        ant = aux; /* guarda o anterior */
        aux = aux->proximo; /* anda para frente */
    }

    novo = (TNo *) calloc (1, sizeof (TNo));
    novo->vertice = w;
    novo->proximo = aux;

    /* Se ant == NULL ou a lista está vazia ou devo inserir no início */
    if (ant == NULL)
    {
        g->lista_adjacencias[v] = novo;
    }
    else
    {
        ant->proximo = novo;
    }

    /* Atualiza o número de arestas */
    g->qtd_arestas++;

    printf ("ARESTA [ %d, %d ] INSERIDA\n", v, w);

    return 0;
}

int
remove_aresta (TGrafo *g, unsigned int v, unsigned int w)
{
    TNo *aux;
    TNo *ant;

    int arestaEncontrada = 0;
    int verticesIguais = 0;

    verticesIguais = v == w;
    if (verticesIguais)
    {
        printf ("VÉRTICES [ %d, %d ] SÃO REPETIDOS\n", v, w);
        return 1;
    }

    ant = NULL;
    aux = g->lista_adjacencias[v];

    /* Não encontrou baseado em V */
    if (aux == NULL)
    {
        free(aux);
        return 1;
    }

    /* Se existe aux e aux != NULL */
    while (aux && aux->vertice < w)
    {
        ant = aux; /* guarda o anterior */
        aux = aux->proximo; /* anda para frente */
    }

    /* Não encontrou baseado em W */
    if (aux == NULL)
    {
        return 1;
    }

    /*
    * Se o grafo já tem a aresta
    * [ v - w ], a função deve removê-la.
    */
    arestaEncontrada = aux->vertice == w;
    if (!arestaEncontrada)
    {
        return 1;
    }

    if (ant == NULL && aux->proximo != NULL)
    {
        g->lista_adjacencias[v] = aux->proximo;
    }

    if (ant == NULL && aux->proximo == NULL)
    {
        g->lista_adjacencias[v] = NULL;
    }

    if (ant != NULL)
    {
        ant->proximo = aux->proximo;
    }

    g->qtd_arestas--;
    free (aux); /* Libera memória */

    printf ("ARESTA [ %d, %d ] REMOVIDA\n", v, w);
    return 0;
}

void
show (TGrafo *g)
{
    unsigned int i;
    printf ("\nVértices [ %d ] e Arestas [ %d ]\n\n", g->qtd_vertices, g->qtd_arestas);
    for (i = 0; i < g->qtd_vertices; i++)
    {
        TNo *aux;
        printf ("Vértice [ %d ] -> ", i);

        /* para cada entrada da lista pega o início da lista */
        aux = g->lista_adjacencias[i];

        /* enquanto não chegar ao final da lista */
        while (aux != NULL)
        {
            printf ("%d ", aux->vertice);
            aux = aux->proximo;
        }
        printf ("\n");
    }
    printf ("\n");
}

void free_graph (TGrafo *g)
{
    unsigned int i;
    for (i = 0; i < g->qtd_vertices; i++)
    {
        TNo *ant;
        TNo *aux;

        /* para cada entrada da lista pega o início da lista */
        aux = g->lista_adjacencias[i];

        /* enquanto não chegar ao final da lista */
        while (aux != NULL)
        {
            ant = aux;
            aux = aux->proximo;
            free (ant);
        }
    }
    free (g->lista_adjacencias);
    free (g);
}

unsigned int
grau_entrada (TGrafo *g, unsigned int w)
{
    TNo *aux = NULL;
    unsigned int controle = g->qtd_vertices;
    unsigned int grau_de_entrada = 0;

    unsigned int i;
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
grau_saida (TGrafo *g, unsigned int w)
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
    unsigned int i;
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

unsigned int
is_caminho_simples (TGrafo *g, const int *seq, unsigned int k)
{
    unsigned int isCaminho;
    isCaminho = is_caminho (g, seq, k);
    if (!isCaminho)
    {
        return 0;
    }

    /* cast to pointer */
    unsigned int caminho_size = k + 1;
    int *caminho = (void *) seq;
    qsort (caminho, caminho_size, sizeof (int), int_qsort_comparator);

    unsigned int i;
    for (i = 0; i < k; i++)
    {
        int current_position = caminho[i];
        int next_position = caminho[i + 1];

        int caminhoNaoSimples = current_position == next_position;
        if (caminhoNaoSimples)
            return 0;
    }

    return 1;
}
unsigned int
existe_caminho (TGrafo *g, int v, int w)
{

    int *visitados = (int *) calloc (g->qtd_vertices, sizeof (int));
    busca_profundidade (g, v, visitados);

    unsigned int result = visitados[w];
    free (visitados);

    return result;
}

void
busca_profundidade (TGrafo *G, unsigned int verticeOrigem, int *visitados)
{

    /* Marca o vértice origem como visitado */
    visitados[verticeOrigem] = 1;

    TNo *w;
    w = G->lista_adjacencias[verticeOrigem];

    /* Para cada vértice [ w ] adjacente ao vértice de origem faça */
    while (w)
    {

        /* Se [ w ] não foi visitado então */
        int naoVisitado = !visitados[w->vertice];
        if (naoVisitado)
        {
            unsigned int novaOrigem = w->vertice;
            busca_profundidade (G, novaOrigem, visitados);
        }

        /* Adentra mais o grafo */
        w = w->proximo;
    }
}

int
int_qsort_comparator (const void *c1, const void *c2)
{
    const int o1 = *(const int *) c1;
    const int o2 = *(const int *) c2;

    return o1 - o2;
}