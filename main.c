#include <stdio.h>
#include "grafo.h"

void
caminho_auxiliar(TGrafo *g, const int *caminho, unsigned int limiteCaminho)
{
    printf("CAMINHO CANDIDATO [ ");
    unsigned int caminhoIndex;
    for (caminhoIndex = 0; caminhoIndex < limiteCaminho + 1; caminhoIndex++)
    {
        printf(" %d", caminho[caminhoIndex]);
    }

    unsigned int isCaminhoResult = is_caminho(g, caminho, limiteCaminho);
    if (isCaminhoResult)
        printf(" ] É VÁLIDO\n");
    else
        printf(" ] NÃO É VÁLIDO\n");
}

void
caminho_simples_auxiliar(TGrafo *g, const int *caminho, unsigned int limiteCaminho)
{
    printf("CAMINHO CANDIDATO [ ");
    unsigned int caminhoIndex;
    for (caminhoIndex = 0; caminhoIndex < limiteCaminho + 1; caminhoIndex++)
    {
        printf(" %d", caminho[caminhoIndex]);
    }

    unsigned int isCaminhoResult = is_caminho_simples(g, caminho, limiteCaminho);
    if (isCaminhoResult)
        printf(" ] É UM CAMINHO SIMPLES\n");
    else
        printf(" ] NÃO É UM CAMINHO SIMPLES\n");
}

int
main()
{
    TGrafo *g;
    g = produce_grafo(6);

    insert_aresta(g, 0, 4);
    insert_aresta(g, 0, 2);
    insert_aresta(g, 2, 4);
    insert_aresta(g, 4, 5);
    insert_aresta(g, 4, 1);
    insert_aresta(g, 5, 1);
    insert_aresta(g, 1, 2);
    insert_aresta(g, 0, 3);
    insert_aresta(g, 3, 4);
    insert_aresta(g, 3, 5);

    show(g);

    printf("\n");
    unsigned int grau_entrada_vertice = 3;
    unsigned int grau_entrada = indeg(g, grau_entrada_vertice);
    printf("GRAU DE ENTRADA DO VÉRTICE [ %d ]: %d\n", grau_entrada_vertice, grau_entrada);

    unsigned int grau_saida_vertice = 0;
    unsigned int grau_saida = outdeg(g, grau_saida_vertice);
    printf("GRAU DE SAÍDA DO VÉRTICE [ %d ]: %d\n", grau_saida_vertice, grau_saida);

    int caminho[] = {0, 2, 1, 3};
    unsigned int limiteCaminho = 3;
    caminho_auxiliar(g, caminho, limiteCaminho);

    int outroCaminho[] = {0, 3, 4, 5, 1, 2};
    unsigned int limiteOutroCaminho = 5;
    caminho_auxiliar(g, outroCaminho, limiteOutroCaminho);
    caminho_simples_auxiliar(g, outroCaminho, limiteOutroCaminho);

    int terceiroCaminho [] = {0, 4, 1, 2, 4};
    unsigned int limiteTerceiroCaminho = 4;
    caminho_simples_auxiliar(g, terceiroCaminho, limiteTerceiroCaminho);


    return 0;
}