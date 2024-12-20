#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 20 // Número máximo de vértices

// Função para encontrar o vértice com a menor distância ainda não visitado
int distancia_minima(int distancia[], bool visitado[], int vert) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vert; v++) {
        if (!visitado[v] && distancia[v] <= min) {
            min = distancia[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Função para imprimir o caminho mínimo e seu custo total
void imprimir_caminho(int parente[], int destino, int source) {
    if (destino == source) {
        printf("%d", source);
        return;
    }
    if (parente[destino] == -1) {
        printf("Caminho nao encontrado.");
        return;
    }
    imprimir_caminho(parente, parente[destino], source);
    printf(" -> %d", destino);
}

// Algoritmo de Dijkstra para encontrar o caminho mínimo entre dois vértices
void algoritmo_dijkstra(int grafo[MAX_VERTICES][MAX_VERTICES], int vert, int source, int destino) {
    int distancia[vert]; // Distância mínima do vértice source para os outros
    bool visitado[vert]; // Marca os vértices já visitados
    int parente[vert];   // Guarda o caminho

    // Inicializar as distâncias e estados dos vértices
    for (int i = 0; i < vert; i++) {
        distancia[i] = INT_MAX;
        visitado[i] = false;
        parente[i] = -1;
    }

    distancia[source] = 0; // A distância do vértice inicial para ele mesmo é 0

    // Processar cada vértice
    for (int count = 0; count < vert - 1; count++) {
        int u = distancia_minima(distancia, visitado, vert);

        visitado[u] = true;

        /*percorre todos os vértices adjacentes ao vértice u (o vértice de menor distância atual). Ele:
        Verifica se cada vértice adjacente pode ser alcançado a partir de u e se é possível melhorar a distância mínima para esse vértice.
        Atualiza a menor distância conhecida e o caminho para os vértices adjacentes, se necessário.
        Esse processo é o relaxamento das arestas, que é o mecanismo principal para encontrar os menores caminhos no algoritmo de Dijkstra.*/
        for (int v = 0; v < vert; v++) {
            if (!visitado[v] && grafo[u][v] > 0 && distancia[u] != INT_MAX &&
                distancia[u] + grafo[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + grafo[u][v];
                parente[v] = u;
            }
        }
    }

    // Mostrar o resultado
    printf("Caminho minimo entre %d e %d: ", source, destino);
    if (distancia[destino] == INT_MAX) {
        printf("nao ha caminho disponivel.\n");
    } else {
        imprimir_caminho(parente, destino, source);
        printf("\nCusto total: %d\n", distancia[destino]);
    }
}

int main() {
    int vert, source, destino;
    int grafo[MAX_VERTICES][MAX_VERTICES];

    printf("Digite o numero de vertices (1 a %d): ", MAX_VERTICES);
    scanf("%d", &vert);

    if (vert < 1 || vert > MAX_VERTICES) {
        printf("Numero de vertices invalido! Deve estar entre 1 e %d.\n", MAX_VERTICES);
        return 1;
    }

    printf("Digite a matriz de adjacencia (%dx%d) com pesos positivos (0 para ausencia de aresta):\n", vert, vert);
    for (int i = 0; i < vert; i++) {
        for (int j = 0; j < vert; j++) {
            scanf("%d", &grafo[i][j]);
            if (grafo[i][j] < 0) {
                printf("Pesos negativos nao sao permitidos.\n");
                return 1;
            }
        }
    }

    printf("Digite o vertice de origem (0 a %d): ", vert - 1);
    scanf("%d", &source);

    printf("Digite o vertice de destino (0 a %d): ", vert - 1);
    scanf("%d", &destino);

    if (source < 0 || source >= vert || destino < 0 || destino >= vert) {
        printf("Vertices invalidos! Devem estar entre 1 e %d.\n", vert - 1);
        return 1;
    }

    algoritmo_dijkstra(grafo, vert, source, destino);

return 0;

}