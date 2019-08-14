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

int
main()
{
    TGrafo *g;
    g = produce_grafo(4);

    insert_aresta(g, 0, 1);
    insert_aresta(g, 0, 2);
    insert_aresta(g, 2, 1);
    insert_aresta(g, 2, 3);
    insert_aresta(g, 1, 3);
    insert_aresta(g, 0, 3);

    show(g);

    printf("\n");
    unsigned int grau_entrada_vertice = 3;
    unsigned int grau_entrada = indeg(g, grau_entrada_vertice);
    printf("GRAU DE ENTRADA DO VÉRTICE [ %d ]: %d\n", grau_entrada_vertice, grau_entrada);

    unsigned int grau_saida_vertice = 0;
    unsigned int grau_saida = outdeg(g, grau_saida_vertice);
    printf("GRAU DE SAÍDA DO VÉRTICE [ %d ]: %d\n", grau_saida_vertice, grau_saida);

    int caminho[4] = {0, 2, 1, 3};
    unsigned int limiteCaminho = 3;
    caminho_auxiliar(g, caminho, limiteCaminho);

    return 0;
}