// Name: Aaron Hernandez Jimenez - A01642529
// Date: 04-11-2023
// Act 4.1 - Grafo: sus representaciones y sus recorridos - SEG0702A

// Instrucciones:
// Individually, create a Graph class with the variables number of vertices, number of edges, Adj Matrix, Adj list

// And the next class function:LoadGraph (Randomly fill the Adjacency Matrix / list) Input: number of vertices (n), number of edges (m)
// Adjacency Matrix / list with m connections must match.

// The application must ask the user for the
// number of vertices (n), the number of edges (m)

/*DFS (Print the Depth-Fist Search Path)
Input: Initial node
Apply to both Adjacency matrix and list, must match
(same initial node). All vertex must be shown.
• BFS (Print the Breadth-Fist Search Path)
Input: Initial node
Apply to both Adjacency matrix and list, must match
(same initial node). All vertex must be shown.
*/

#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <time.h>


using namespace std;


//declaramos la estructura arco que contiene el inicio y el final del arco

struct Arc //se crea la estructura tipo NODO
{
    int start, end;
};

//declaramos la clase grafo que contiene el numero de vertices, una lista de adyacencia, una matriz de adyacencia y un arreglo de visitados
class Graph
{
private: //se declaran las variables privadas de la clase grafo
    int number_of_vertices; //numero de vertices
    int number_of_edges; //numero de arcos
    list<int> *Adj_Lists;
    bool AdjMatrix[100][100];
    bool *visited;

public:
    Graph(int I) //constructor default de la clase grafo
    {
        number_of_vertices = I; 
        Adj_Lists = new list<int>[I]; //se crea una lista de adyacencia
        visited = new bool[I]; //se crea un arreglo de visitados
    }
    ~Graph() //destructor default de la clase grafo 
    {
        delete[] Adj_Lists; //se borra la lista de adyacencia
        delete[] visited; //se borra el arreglo de visitados
    }

    void graphPrint(); 
    void GraphMPrint();
    void VisitedReset();
    void DFS(int);
    void BFS(int);
    void DFSM(int);
    void BFSM(int);
    void LoadGraph(int, vector<Arc> &);
};

void Graph::LoadGraph(int s, vector<Arc> &vecArcos) //se declara la funcion LoadGraph que recibe el numero de vertices y un vector de arcos
{
    this->number_of_vertices = s; 
    this->number_of_edges = vecArcos.size();
    for (int i = 0; i < this->number_of_vertices; i++)
        visited[i] = false;
    for (int i = 0; i < this->number_of_vertices; i++)
        Adj_Lists[i].clear();
    for (int i = 0; i < this->number_of_vertices; i++)
        for (int j = 0; j < this->number_of_vertices; j++)
            AdjMatrix[i][j] = false;
    for (auto i : vecArcos)
    {
        this->Adj_Lists[i.start].push_back(i.end);
        this->Adj_Lists[i.end].push_back(i.start);
    }
    for (int i = 0; i < this->number_of_vertices; i++)
    {
        for (int j = 0; j < this->number_of_vertices; j++)
            AdjMatrix[i][j] = 0;
        cout << endl;
    }

    for (auto j : vecArcos)
    {
        AdjMatrix[j.start][j.end] = true;
        AdjMatrix[j.end][j.start] = true;
    }
}

void Graph::graphPrint() // se declara la funcion graphPrint que imprime la lista de adyacencia
{
    for (int i = 0; i < this->number_of_vertices; i++)
    {
        cout << "\nVertex " << i << ":"; //se imprime el vertice
        for (auto x : this->Adj_Lists[i]) //se imprime la lista de adyacencia
            cout << "-> " << x;
        cout << endl;
}
}


void Graph::GraphMPrint() //se declara la funcion GraphMPrint que imprime la matriz de adyacencia 
{
    cout << "  ";
    for (int i = 0; i < this->number_of_vertices; i++)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < this->number_of_vertices; i++)
    {
        cout << i << " ";
        for (int j = 0; j < this->number_of_vertices; j++)
            cout << AdjMatrix[i][j] << " ";
        cout << endl;
    }
}


void Graph::VisitedReset() //se declara la funcion VisitedReset que reinicia el arreglo de visitados
{
    for (int i = 0; i < this->number_of_vertices; i++) //se recorre el arreglo de visitados
        visited[i] = false;       //se reinicia el arreglo de visitados
}

void Graph::DFS(int vertex) //se declara la funcion DFS que recibe un vertice
{
    visited[vertex] = true; //se marca el vertice como visitado
    cout << vertex << " "; //se imprime el vertice
    for (auto i : Adj_Lists[vertex]) //se recorre la lista de adyacencia
    {
        if (!visited[i]) //si el vertice no ha sido visitado
        {
            DFS(i); //se llama a la funcion DFS
        }
    }
}

void Graph::DFSM(int vertex) //se declara la funcion DFSM que recibe un vertice
{
    visited[vertex] = true; //se marca el vertice como visitado
    cout << vertex << " "; //se imprime el vertice
    for (int i = 0; i < number_of_vertices; i++) //se recorre la matriz de adyacencia
    {
        if (AdjMatrix[vertex][i] && !visited[i]) //si el vertice no ha sido visitado
        {
            DFSM(i); //se llama a la funcion DFSM
        }
    }

}

void Graph::BFS(int VertexStart) //se declara la funcion BFS que recibe un vertice
{
    visited[VertexStart] = true; //se marca el vertice como visitado
    list<int> queue; //se crea una lista
    queue.push_back(VertexStart); //se agrega el vertice a la lista
    while (!queue.empty()) //mientras la lista no este vacia
    {
        int currVertex = queue.front(); //se guarda el vertice de enfrente de la lista
        cout << currVertex << " "; //se imprime el vertice
        queue.pop_front(); //se elimina el vertice de enfrente de la lista
        for (auto i : Adj_Lists[currVertex]) //se recorre la lista de adyacencia
        {
            if (!visited[i]) //si el vertice no ha sido visitado
            {
                visited[i] = true; //se marca el vertice como visitado
                queue.push_back(i); //se agrega el vertice a la lista
            }
        }
    }
    
}

void Graph::BFSM(int VertexStart) //se declara la funcion BFSM que recibe un vertice
{
    visited[VertexStart] = true; //se marca el vertice como visitado
    list<int> queue; //se crea una lista
    queue.push_back(VertexStart); //se agrega el vertice a la lista
    while (!queue.empty()) //mientras la lista no este vacia
    {
        int currVertex = queue.front(); //se guarda el vertice de enfrente de la lista
        cout << currVertex << " "; //se imprime el vertice
        queue.pop_front(); //se elimina el vertice de enfrente de la lista
        for (int i = 0; i < number_of_vertices; i++) //se recorre la matriz de adyacencia
        {
            if (AdjMatrix[currVertex][i] && !visited[i]) //si el vertice no ha sido visitado
            {
                visited[i] = true; //se marca el vertice como visitado
                queue.push_back(i); //se agrega el vertice a la lista
            }
        }
    }
}

int main() //funcion main
{
    
    int Vertices = 7; //se declara el numero de vertices
    Graph G(Vertices); //se crea un objeto de la clase grafo
    vector<Arc> vecArcos = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}}; //se crea un vector de arcos

    G.LoadGraph(Vertices, vecArcos); //se llama a la funcion LoadGraph
    cout << "DFS Lista: " << endl; //se imprime el recorrido DFS de la lista
    G.DFS(3);
    G.VisitedReset();
    cout << endl
         << "DFS AdjMatrix: " << endl;
    G.DFSM(3); //se imprime el recorrido DFS de la matriz
    G.VisitedReset();
    cout << endl
         << "BFS Lista: " << endl;
    G.BFS(3); //se imprime el recorrido BFS de la lista
    G.VisitedReset();
    cout << endl
         << "BFS AdjMatrix: " << endl;
    G.BFS(3); //se imprime el recorrido BFS de la lista
    G.VisitedReset(); //se reinicia el arreglo de visitados
    G.graphPrint(); //se imprime la lista de adyacencia
    G.GraphMPrint(); //se imprime la matriz de adyacencia


    return 0;
}