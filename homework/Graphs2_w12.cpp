//BFS
#include <vector>
using namespace std;

// Implementación de una clase básica de cola (Queue)
class Queue {
private:
    vector<int> data;
    int start = 0; // Índice de inicio para evitar el desplazamiento en el vector

public:
    // Agrega un elemento al final de la cola
    void add(int value) {
        data.push_back(value);
    }

    // Devuelve el elemento en el frente de la cola
    int extract() {
        return data[start];
    }

    // Elimina el elemento en el frente de la cola
    void remove() {
        start++;
        // Cuando el índice de inicio llega a la mitad del vector, limpiamos el espacio no usado
        if (start > data.size() / 2) {
            data.erase(data.begin(), data.begin() + start);
            start = 0;
        }
    }

    // Comprueba si la cola está vacía
    bool empty() {
        return start >= data.size();
    }
};

// Clase que representa un grafo usando una lista de adyacencia
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjList;

public:
    // Constructor para inicializar el grafo
    Graph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    // Función para agregar una arista entre dos nodos
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Para grafo no dirigido
    }

    // Función BFS que realiza el recorrido desde un nodo inicial y devuelve el orden de visita
    vector<int> BFS(int start) {
        vector<int> result; // Vector para almacenar el orden de los nodos visitados
        vector<bool> visited(numVertices, false);
        Queue q;

        visited[start] = true;
        q.add(start);

        while (!q.empty()) {
            int x = q.extract();
            q.remove();
            result.push_back(x); // Agregar el nodo visitado al resultado

            // Explorar todos los nodos adyacentes
            for (int j : adjList[x]) {
                if (!visited[j]) {
                    visited[j] = true;
                    q.add(j);
                }
            }
        }

        return result;
    }

    // Función para realizar BFS en todos los componentes del grafo y devolver el recorrido completo
    vector<vector<int>> BFSAll() {
        vector<vector<int>> allComponents; // Almacena el recorrido de todos los componentes
        vector<bool> visited(numVertices, false);

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                vector<int> component = BFS(i); // Realizar BFS desde el nodo no visitado
                for (int node : component) { // Marcar todos los nodos del componente como visitados
                    visited[node] = true;
                }
                allComponents.push_back(component); // Agregar el componente al resultado
            }
        }

        return allComponents;
    }
};
//DFS
#include <vector>
using namespace std;

// Clase que representa un grafo usando una lista de adyacencia
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjList;

    // Función recursiva para realizar DFS desde un nodo específico
    void DFSUtil(int i, vector<bool>& visited, vector<int>& result) {
        visited[i] = true;          // Marca el nodo como visitado
        result.push_back(i);         // Agrega el nodo al resultado

        // Explora todos los nodos adyacentes
        for (int j : adjList[i]) {
            if (!visited[j]) {
                DFSUtil(j, visited, result);  // Llama recursivamente para el nodo adyacente no visitado
            }
        }
    }

public:
    // Constructor para inicializar el grafo
    Graph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    // Función para agregar una arista entre dos nodos
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Para grafo no dirigido
    }

    // Función principal para realizar DFS en todos los componentes del grafo
    vector<vector<int>> DFSAll() {
        vector<bool> visited(numVertices, false);
        vector<vector<int>> allComponents;

        // Realiza DFS en cada componente no visitado del grafo
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                vector<int> component;
                DFSUtil(i, visited, component); // Realiza DFS desde el nodo no visitado
                allComponents.push_back(component); // Agrega el componente al resultado
            }
        }

        return allComponents;
    }
};

//Dijkstra

#include <vector>
using namespace std;

const int INF = 1e9; // Un valor suficientemente grande para representar "infinito"

class Graph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjList; // Lista de adyacencia con pares (destino, peso)

    // Encuentra el nodo con la distancia mínima no visitado
    int minDistance(const vector<int>& distances, const vector<bool>& visited) {
        int minDist = INF;
        int minIndex = -1;

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && distances[i] < minDist) {
                minDist = distances[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

public:
    // Constructor para inicializar el grafo
    Graph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    // Función para agregar una arista entre dos nodos con un peso
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Para grafo no dirigido
    }

    // Implementación del algoritmo de Dijkstra
    vector<int> dijkstra(int start) {
        vector<int> distances(numVertices, INF); // Distancias mínimas desde el nodo inicial
        vector<bool> visited(numVertices, false); // Marcador de nodos visitados
        vector<int> parent(numVertices, -1); // Para rastrear el camino mínimo

        distances[start] = 0;

        for (int count = 0; count < numVertices - 1; count++) {
            int u = minDistance(distances, visited);
            if (u == -1) break; // Si no se encontró un nodo, salimos

            visited[u] = true;

            // Actualiza las distancias de los nodos adyacentes
            for (auto [v, weight] : adjList[u]) {
                if (!visited[v] && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    parent[v] = u; // Guarda el nodo predecesor para reconstruir el camino
                }
            }
        }

        return distances; // Devuelve las distancias mínimas desde el nodo inicial
    }

    // Función adicional para devolver el camino mínimo a un nodo objetivo
    vector<int> getPath(int target, const vector<int>& parent) {
        vector<int> path;
        for (int v = target; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

//what a mess i made up?
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if(connections.size() < n - 1){
            return -1;
        };

        

        //lista de adyacencia
        vector<vector<int>> graph(n);
        for(auto& conn : connections){
            int a = conn[0], b = conn[1];
            graph[b].push_back(a);
            graph[a].push_back(b);
        }

        //componentes
        vector<bool> visited(n,false);
        int components = 0;

        //contamos los componentes
        for(int i = 0; i < n; i++){
            if(!visited[i]){
                DFS(i,graph,visited);    
                components++;
            }
        }
        return components - 1;      
    }
        
private:

    void DFS(int node, vector<vector<int>>& graph, vector<bool>& visited){
        visited[node] =true;
        for(int neighbor:graph[node]){
            if(!visited[neighbor]){
                DFS(neighbor, graph, visited);
            }
        }

    }

};

//i pulled out the nana
#include <iostream>
#include <vector>
using namespace std;

// Definición de la estructura de un nodo de árbol binario
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Función auxiliar para obtener la secuencia de hojas de un árbol
void getLeafSequence(TreeNode* root, vector<int>& leaves) {
    if (root == NULL) return;
    
    // Si el nodo es hoja, agregar su valor a la secuencia
    if (root->left == NULL && root->right == NULL) {
        leaves.push_back(root->val);
    }
    
    // Recorrer los subárboles izquierdo y derecho
    getLeafSequence(root->left, leaves);
    getLeafSequence(root->right, leaves);
}

// Función principal para verificar si dos árboles son similares en sus hojas
bool leafSimilar(TreeNode* root1, TreeNode* root2) {
    vector<int> leaves1, leaves2;
    
    // Obtener las secuencias de hojas de ambos árboles
    getLeafSequence(root1, leaves1);
    getLeafSequence(root2, leaves2);
    
    // Comparar las secuencias de hojas
    return leaves1 == leaves2;
}

// Ejemplo de uso
int main() {
    // Crear el primer árbol binario
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(5);
    root1->right = new TreeNode(1);
    root1->left->left = new TreeNode(6);
    root1->left->right = new TreeNode(2);
    root1->left->right->left = new TreeNode(7);
    root1->left->right->right = new TreeNode(4);
    root1->right->left = new TreeNode(9);
    root1->right->right = new TreeNode(8);

    // Crear el segundo árbol binario
    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(5);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(6);
    root2->left->right = new TreeNode(7);
    root2->right->left = new TreeNode(4);
    root2->right->right = new TreeNode(2);
    root2->right->right->left = new TreeNode(9);
    root2->right->right->right = new TreeNode(8);

    // Verificar si los árboles son similares en sus hojas
    if (leafSimilar(root1, root2)) {
        cout << "Los árboles son similares en sus hojas." << endl;
    } else {
        cout << "Los árboles NO son similares en sus hojas." << endl;
    }

    return 0;
}

//afterhours aint no 
#include <iostream>
#include <vector>
using namespace std;

// Estructura para el Union Find (Disjoint Set Union - DSU)
class UnionFind {
public:
    vector<int> parent, rank;

    // Constructor para inicializar el Union Find
    UnionFind(int n) {
        parent.resize(n + 1); // Ya que los nodos están etiquetados desde 1 a n
        rank.resize(n + 1, 0); // Inicializamos el rango a 0

        // Cada nodo es su propio padre inicialmente
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    // Función para encontrar el representante del conjunto de un nodo
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Función para unir dos nodos
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        // Si los nodos ya están en el mismo conjunto, no hacemos nada
        if (rootX != rootY) {
            // Unir los dos conjuntos según el rango (rank)
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n);

        // Iteramos sobre las aristas para encontrar la arista redundante
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            // Si ambos nodos ya están conectados, significa que esta arista es redundante
            if (uf.find(u) == uf.find(v)) {
                return edge;
            }
            // Unir los dos nodos
            uf.unite(u, v);
        }

        // En teoría, no deberíamos llegar aquí porque siempre habrá una arista redundante
        return {};
    }
};

// Ejemplo de uso
int main() {
    Solution solution;

    // Ejemplo 1
    vector<vector<int>> edges1 = {{1, 2}, {1, 3}, {2, 3}};
    vector<int> result1 = solution.findRedundantConnection(edges1);
    cout << "Arista redundante: [" << result1[0] << ", " << result1[1] << "]" << endl;

    // Ejemplo 2
    vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    vector<int> result2 = solution.findRedundantConnection(edges2);
    cout << "Arista redundante: [" << result2[0] << ", " << result2[1] << "]" << endl;

    return 0;
}


