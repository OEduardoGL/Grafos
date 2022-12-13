#include <bits/stdc++.h>
 
// Estrutura para representar os pesos nas arestas do Grafo
struct Edge {
    int src, dest, weight;
};
 
// Estrutura do Grafo
struct Graph {
    int V, E;

    struct Edge* edge;
};
 
// Cria Grafo com V vértices e E arestas
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}
 
// Função utilizada para printar a solução
void printArr(int dist[], int n)
{
    printf("Vértice \tDistância da origem\n");
    for (int i = 0; i < n; ++i)
        printf("   %d \t\t\t %d\n", i, dist[i]);

}
 
// Função principal para encontrar a menor distância da origem para todos os vértices do grafo
void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
 
    // Inicializa a distância da origem para os outros vértices como infinito
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;
 
    // Percorre todas as arestas |V| - 1 vezes. Um caminho mais curto simples da 
    //origem até qualquer outro vértice pode ter no máximo |V| - 1 arestas
    for (int i = 1; i <= V-1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX
                && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
 
    // Verificação de ciclos de pesos negativos
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX
            && dist[u] + weight < dist[v]) {
            printf("Grafo contém ciclos com pesos negativos\n");
            return;
        }
    }
 
    printArr(dist, V);
 
    return;
}

int main()
{
    int V, qtd_arest, vert_1, vert_2, peso;  
	char a[10];
    char b;
	scanf("%d %d", &V, &qtd_arest);

    struct Graph* graph = createGraph(V, qtd_arest); //  Chamada de função para criar o objeto Grafo
    
	for(int i = 0; i < qtd_arest; i++)
	{
    	scanf("%d %d", &vert_1, &vert_2);
        b = getchar();
        if(b == ' ')
        {
            scanf(" %[^\n]s", a);
            peso = atoi(a);
        }
        else peso = 1;

    	graph->edge[i].src = vert_1;
        graph->edge[i].dest = vert_2;
        graph->edge[i].weight = peso;
   	}
 
    BellmanFord(graph, 0);

    delete graph;
 
    return 0;
}

/*
    Exemplo de Entrada Para O Programa:
    6 8
    0 1 5
    0 2 4
    0 3 2
    0 5 6
    1 3 1
    1 4 7
    2 4 6
    3 5 1
*/