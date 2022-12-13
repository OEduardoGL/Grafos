#include<iostream>
#include<vector>
#include<stack>
using namespace std;

vector<int> arr1[51];
vector<int> arr2[51];

int visited[51];
int visited2[51];
stack<int> st;
int r;

//DFS para percorrer o grafo
void DFS(int node){
    visited[node]=1;
    for(int child: arr1[node]){
        if(visited[child]!=1) DFS(child);
    }
    st.push(node);
}

//DFS para percorrer o grafo modificado
void DFS2(int node){
    printf("%d ", node);
    visited2[node]=1;
    for(int child: arr2[node]){
        if(visited2[child]!=1) DFS2(child);
    }
}
int main(){

    int n_vert, n_aresta, x, y;

    //x e y são os caminhos entre si
    scanf("%d %d", &n_vert, &n_aresta);
    while(n_aresta--){
        scanf("%d %d", &x, &y);

        arr1[x].push_back(y);
        arr2[y].push_back(x);
    }

    DFS(0);
    printf("Componentes fortemente conexos:");
    while(!st.empty()){
        int k=st.top();
        st.pop();
        if(visited2[k]!=1){
            r++;
            printf("\n");
            DFS2(k);
        }
    }
    printf("\n");
    printf("Total de componentes fortemente conexos = %d\n", r);

    return 0;
}

/*
    Exemplo de Entradas Para O Programa:
    8 10
    0 1
    1 2
    2 0
    2 3
    3 4
    4 5
    5 6
    6 7
    6 4
    4 7
*/