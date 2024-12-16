#include <stdio.h>
#include <stdlib.h>

//representa uma aresta do grafo
typedef struct {
    int origem, destino, peso;
} Aresta;

// cria um grafo
typedef struct {
    int vertices, arestas;
    Aresta* listaArestas;
} Grafo;

// união busca (Union-Find)

typedef struct {
    int pai;    //representante do conjunto;
    int rank;   // auxiliar na união
} Subconjunto;

// função para criar um grafo
Grafo* criarGrafo(int vertices, int arestas)    {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->vertices = vertices;
    grafo->arestas = arestas;
    grafo->listaArestas = (Aresta*)malloc(arestas * sizeof(Aresta));
    return grafo;
}

// encontrar o representante do conjunto
int encontrar (Subconjunto subconjuntos[], int i)    {
    if (subconjuntos[i].pai != i)   {
        subconjuntos[i].pai = encontrar (subconjuntos, subconjuntos[i].pai);
    }
    return subconjuntos[i].pai;
}

// unir dois conjuntos(vertices) de forma eficiente ()
void unir (Subconjunto subconjuntos[], int x, int y)    {
    int raizX = encontrar (subconjuntos, x); // 
    int raizY = encontrar (subconjuntos, y); //

    if (subconjuntos[raizX].rank < subconjuntos[raizY].rank){
        // raizX tendo o menor rank torna-se filho do raizY
        subconjuntos[raizX].pai = raizY; 
    } else if (subconjuntos[raizX].rank > subconjuntos[raizY].rank) {
        //raizY tem rank menor, então se torna filho de raizX
        subconjuntos[raizY].pai = raizX;
    } else {
        // Os ranks são iguais então tem que escolher um para ser o pai
        // raizY se torna filho de raizX, e o rank de raizX é incrementado
        subconjuntos[raizY].pai = raizX;
        subconjuntos[raizX].rank++;
    }
}

// Compara as arestas pelo peso
int comparar(const void* a, const void* b)  {
    Aresta* arestaA = (Aresta*)a;
    Aresta* arestaB = (Aresta*)b;
    return arestaA->peso - arestaB->peso;
}

// algoritmo de Kruskal
void kruskal (Grafo* grafo) {
    int vertices = grafo->vertices;
    Aresta resultado[vertices-1]; //AGM
    int e = 0; //contador para o resultado
    int i = 0; // indice para as arestas ordenadas

    // ordena as arestas pelo peso
    qsort(grafo->listaArestas, grafo->arestas, sizeof(Aresta), comparar);

    //ciar subconjuntos
    Subconjunto* subconjuntos = (Subconjunto*)malloc(vertices * sizeof (Subconjunto));
    for (int v = 0; v < vertices; v++)  {
        subconjuntos[v].pai = v;
        subconjuntos[v].rank = 0;
    }

    // processar as arestas
    while (e < vertices - 1 && i < grafo->arestas)  {
        Aresta proximaAresta = grafo->listaArestas[i++];

        int x = encontrar(subconjuntos, proximaAresta.origem);
        int y = encontrar(subconjuntos, proximaAresta.destino);

        //Se nao formar ciclo, adiciona ao resultado
        if (x != y) {
            resultado[e++] = proximaAresta;
            unir(subconjuntos,x, y);
        }
    }

    //imprimir o resultado
    printf ("Arestas na Arvore Geradora Minima:\n");
    printf ("Origem\t\tDestino\t\tPeso\n");
    printf ("----------------------------------------\n");
    for (i = 0; i < e; i++) {
        printf("%d\t\t%d\t\t%d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);
    }

    free(subconjuntos);
}

int main() {
    int vertices = 6; // Número de vértices
    int arestas = 10;  // Número de arestas
    Grafo* grafo = criarGrafo(vertices, arestas);

    // Adicionar arestas
    // algoritmo_Kruskal.png
    // vertices = 4     arestas = 5    
    /* 
    grafo->listaArestas[0] = (Aresta){0, 1, 10};
    grafo->listaArestas[1] = (Aresta){0, 2, 6};
    grafo->listaArestas[2] = (Aresta){0, 3, 5};
    grafo->listaArestas[3] = (Aresta){1, 3, 15};
    grafo->listaArestas[4] = (Aresta){2, 3, 4};
    */

    // algoritmo_Kruskal2.png
    // vertices = 6     arestas = 10
    grafo->listaArestas[0] = (Aresta){0, 1, 6};
    grafo->listaArestas[1] = (Aresta){0, 2, 1};
    grafo->listaArestas[2] = (Aresta){0, 3, 5};
    grafo->listaArestas[3] = (Aresta){1, 2, 2};
    grafo->listaArestas[4] = (Aresta){1, 4, 5};
    grafo->listaArestas[5] = (Aresta){2, 3, 2};
    grafo->listaArestas[6] = (Aresta){2, 4, 6};
    grafo->listaArestas[7] = (Aresta){2, 5, 4};
    grafo->listaArestas[8] = (Aresta){3, 5, 3};
    grafo->listaArestas[9] = (Aresta){4, 5, 3};




    kruskal(grafo);

    free(grafo->listaArestas);
    free(grafo);

    return 0;
}





