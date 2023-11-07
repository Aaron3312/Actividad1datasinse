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

using namespace std;


//declaramos la estructura arco que contiene el inicio y el final del arco

struct Arco
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
    Graph(int I)
    {
        number_of_vertices = I;
        Adj_Lists = new list<int>[I];
        visited = new bool[I];
    }
    ~Graph()
    {
        delete[] Adj_Lists;
        delete[] visited;
    }
    void printGraph();
    void printGraphM();

    void ResetVisited();
    void DFS(int);
    void BFS(int);
    void DFSM(int);
    void BFSM(int);
    void loadGraph(int, vector<Arco> &);
};
void Graph::loadGraph(int s, vector<Arco> &vecArcos)
{
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
void Graph::printGraph()
{
    for (int i = 0; i < this->number_of_vertices; i++)
    {
        cout << "\nVertex " << i << ":";
        for (auto x : this->Adj_Lists[i])
            cout << "-> " << x;
        cout << endl;
    }
}
void Graph::printGraphM()
{
    for (int i = 0; i < this->number_of_vertices; i++)
    {
        cout << "\nVertex " << i << ":";
        for (int j = 0; j < this->number_of_vertices; j++)
            cout << AdjMatrix[i][j] << " ";
        cout << endl;
    }
}
void Graph::ResetVisited()
{
    for (int i = 0; i < number_of_vertices; i++)
        visited[i] = false;
}
void Graph::DFS(int vertex)
{
    this->visited[vertex] = true;
    list<int> adjVertex = this->Adj_Lists[vertex];
    cout << vertex << " ";
    for (auto i : adjVertex)
        if (!this->visited[i])
            DFS(i);
}
void Graph::DFSM(int vertex)
{
    visited[vertex] = true;
    cout << vertex << " ";
    for (int i = 0; i < number_of_vertices; i++)
    {
        if (AdjMatrix[vertex][i] && !visited[i])
        {
            DFSM(i);
        }
    }
}
void Graph::BFS(int startVertex)
{
    visited[startVertex] = true;
    list<int> queue;
    queue.push_back(startVertex);
    while (!queue.empty())
    {
        int currVertex = queue.front();
        cout << currVertex << " ";
        queue.pop_front();
        for (auto i : Adj_Lists[currVertex])
        {
            if (!visited[i])
            {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}
void Graph::BFSM(int startVertex)
{
    visited[startVertex] = true;
    list<int> queue;
    queue.push_back(startVertex);
    while (!queue.empty())
    {
        int currVertex = queue.front();
        cout << currVertex << " ";
        queue.pop_front();
        for (int i = 0; i < number_of_vertices; i++)
        {
            if (AdjMatrix[currVertex][i] && !visited[i])
            {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}
int main()
{
    int Vertices = 6;
    Graph G(Vertices);
    vector<Arco> vecArcos = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {2, 4}, {3, 5}, {2, 5}};
    G.loadGraph(Vertices, vecArcos);
    cout << "DFS Lista: " << endl;
    G.DFS(2);
    G.ResetVisited();
    cout << endl
         << "DFS AdjMatrix: " << endl;
    G.DFSM(2);
    G.ResetVisited();
    cout << endl
         << "BFS Lista: " << endl;
    G.BFS(2);
    G.ResetVisited();
    cout << endl
         << "BFS AdjMatrix: " << endl;
    G.BFS(2);
    G.ResetVisited();
    G.printGraph();
    G.printGraphM();
    return 0;
}