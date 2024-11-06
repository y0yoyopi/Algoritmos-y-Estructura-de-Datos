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

