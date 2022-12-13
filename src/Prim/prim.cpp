#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 
// Estrutura para representar um nó na lista de adjacências
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};
 
// Estrutura para representar uma lista de adjacências
struct AdjList {
    struct AdjListNode*
        head;
};
 
// Estrutura para representar um grafo
struct Graph {
    int V;
    struct AdjList* array;
};
 
// Função para criar um novo nó na lista de adjacência
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
// Função para criar um gráfico de V vértices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Criar um vetor de adjacência. Tamanho da matriz será V
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
 
    // Inicializando a lista de adjacência como vazio
    int i = 0;
    while(i < V){
        graph->array[i].head = NULL;
        i++;
    }
    
    return graph;
}
 
// Adiciona uma aresta a um gráfico não direcionado
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // Adicione uma aresta da origem ao destino
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Como o gráfico não é direcionado, fazemos o caminho inverso
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// Estrutura para representar um nó de heap mínima
struct MinHeapNode {
    int v;
    int key;
};
 
// Estrutura para representar uma heap mínima
struct MinHeap {
    int size;
    int capacity;
    int* pos;
    struct MinHeapNode** array;
};
 
// Função para criar um novo nó da heap mínima
struct MinHeapNode* newMinHeapNode(int v, int key)
{
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}
 
// Função para criar uma heap mínima
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(
        capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// Função para trocar dois nós na heap mínima
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// Função de execução da heap
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key) smallest = left;
 
    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key) smallest = right;
    
    // Identifica e realiza as modificações dos nós da heap mínima
    if (smallest != idx) { 
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];
 
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// Função para verificar se a heap está vazia
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Função para extrair o nó mínimo da heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    struct MinHeapNode* root = minHeap->array[0];
 
    // Inverte o nó raíz com o último nó, e depois reorganiza a heap
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Função para diminuir o key value de um vértice V
void decreaseKey(struct MinHeap* minHeap, int v, int key)
{
    int i = minHeap->pos[v];
 
    minHeap->array[i]->key = key;
 
    // Loop para percorrer a árvore enquanto não for ordenada
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}
 
// Função de para verificar se um vértice 'v' está na heap mínima ou não
bool isInMinHeap(struct MinHeap* minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}
 
// Função para printar a árvore geradora mínima
void printArr(int arr[], int n)
{
    printf("\nÁrvore Geradora Mínima do Grafo:\n");
    for (int i = 1; i < n; ++i)
        printf("%d - %d\n", arr[i], i);
}
 
// Função principal que constrói a árvore geradora mínima
void PrimMST(struct Graph* graph)
{
    int V = graph->V; // Recebe o número de vértices do grafo
    int parent[V]; // Array para armazenar a árvore geradora mínima
    int key[V]; // Key value usados ​​para escolher a aresta de peso mínimo
 
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Key value de todos os vértices inicializa como infinito (exceto o 0)
    for (int v = 1; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }
 
    // O key value do primeiro vértice inicializa com 0
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;
 
    minHeap->size = V;
 
    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);

        int u = minHeapNode->v;
 
        // Percorre os vértices adjacentes e atualiza seus keys values
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
 
            if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) {
                key[v] = pCrawl->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    printArr(parent, V);
}

int main()
{
    int V, qtd_arest, vert_1, vert_2, peso;  
	char a[10];
    char b;
	scanf("%d %d", &V, &qtd_arest);

    struct Graph* graph = createGraph(V); // Chamada de Função para criar o grafo

    printf("Grafo:\n");

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

        printf("%d - %d, peso: %d\n", vert_1, vert_2, peso);

    	addEdge(graph, vert_1, vert_2, peso);
   	}
 
    PrimMST(graph);

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