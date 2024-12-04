#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void algoritmo_dijkstra (); 
int distancia_minima(int vert, int distancia[], bool CMN[]);
void imprimir (int vert, int distancia[]);


int main()  {
    int vert = 0;    
    printf ("Digite o numero de vertices (entre 1 e 20 (inclusive)): ");
    scanf ("%d", &vert);

    int grafico[vert][vert] = {
        {}
    };

    algoritmo_dijkstra(grafico,0);
}



int distancia_minima(int vert, int distancia[], bool CMN[]) { //CMN = conjunto de menor caminho (que inicia em 0, ou seja, ainda sem o menor caminho)
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vert; v++)
        if (!CMN[v] && distancia[v] <= min) {
            min = distancia[v];
            minIndex = v;
        }
}



void algoritmo_dijkstra(int grafico[vert][vert], int ini) {
    int distancia[vert]; // guarda a menor distancia do ini
    int CMN[vert]; // V se o vertice i estiver no menor caminho ja encontrado
    
    

    
}


// Funcao para imprimir as distancias do vertice de origem
void imprimir (int vert, int distancia[])  {
    printf("Vertice \t Distancia da Origem\n");
    for (int i = 0; i < vert; i++) {
        printf("%d \t\t %d\n", i, distancia[i]);
    }
}






