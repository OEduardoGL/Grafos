#include <bits/stdc++.h>  
using namespace std;  
#define INF 0x3f3f3f3f // A distância para outros vértices é inicializada como infinita  

typedef pair<int, int> iPair;
struct Graph
    {  
    int V; // Número de vértices no gráfico  
    list<pair<int, int>>* adj; // Guardando Vértice e Peso

    Graph(int V)  
    {  
        this->V = V;   
        adj = new list<iPair>[V]; // Alocar espaços para os vértices
    }
    void addEdge(int u, int v, int w); // Adicionar arestas para o grafo
    void shortestPathingraph(int s); // Definindo o vértice de origem
};

void Graph::addEdge(int u, int v, int w) // Adicionar aresta
{  
    adj[u].push_back(make_pair(v, w)); // Fazendo um par de vértice e peso e adicionando a lista  
    adj[v].push_back(make_pair(u, w)); // Adicionando o oposto
}  

void Graph::shortestPathingraph(int origem)
{  
    // Criando uma fila de prioridade
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;  
    vector<int> dist(V, INF); // Todas as distâncias da origem são infinitas
    pq.push(make_pair(0, origem)); // Inserindo o vértice de origem na fila
    dist[origem] = 0;
    while (!pq.empty()) {  
        int u = pq.top().second;  
        pq.pop();  
        // 'i' é usado para obter todos os vértices adjacentes de um vértice  
        list<pair<int, int>>::iterator i;  
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {    
            int v = (*i).first;  
            int weight = (*i).second;  
    
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }  
        }  
    }  
    printf("Vértice \tDistância da origem\n");
    for (int i = 0; i < V; ++i)  
        printf("   %d \t\t\t %d\n", i, dist[i]);
}  
int main()  
{
    int V, qtd_arest, vert_1, vert_2, peso;  
	char a[10];
    char b;
	scanf("%d %d", &V, &qtd_arest);
    struct Graph* grafo = new Graph(V); //  Chamada de função para criar o objeto Grafo
    
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

    	grafo->addEdge(vert_1, vert_2, peso);
   	}
    grafo->shortestPathingraph(0); // Chamada de Função para encontrar o menor caminho, tendo '0' como o vértice inicial
    printf("\nPara definir o vértice de origem, modifique o parâmetro \nna chamada da função 'g.shortestPathingraph(x)'\n");

    delete grafo;
    
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