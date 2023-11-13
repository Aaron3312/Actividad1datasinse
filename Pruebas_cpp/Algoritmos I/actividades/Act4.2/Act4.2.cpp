// Name: Aaron Hernandez Jimenez - A01642529
// Date: 11-11-2023
// Act 4.2 - Grafos: Algoritmos complementarios

#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <time.h>
#include <random>

using namespace std;

struct numbers
{
    int Number, Repetition; // Number = number, Repetition = repetitions
};

class Graph // Graph class
{           // Private variables
private:
    int number_of_vertices, ant, sig;
    list<int> *Adj_list;
    bool Matrix[100][100];
    bool *visited;
    vector<numbers> numVecs;
    // Public variables
public:
    Graph(int V) // Constructor
    {
        number_of_vertices = V;
        Adj_list = new list<int>[V];
        visited = new bool[V]; // Visited array
    }
    ~Graph() // Destructor
    {
        delete[] Adj_list;
        delete[] visited;
    }

    void printGraph();                          // Prints the graph
    void printGraphM();                         // Prints the graph in matrix form
    bool IsTree();                              // Checks if the graph is a tree
    void ResetVisited();                        // Resets the visited array
    void DFSM(int);                             // DFS in matrix form
    void BFSM(int);                             // BFS in matrix form
    void LoadGraph(int);                        // Loads the graph
    void topologicalSort();                     // Topological sort
    void topologicalSortAux(int, deque<int> &); // Auxiliar function for topological sort
    bool isBipartite(int);                      // Checks if the graph is bipartite
    void DFS(int);                              // DFS in list form

}; // End of Graph class


// su complejidad es O(n^2)
void Graph::LoadGraph(int V) // Loads the graph 
{
    ResetVisited();                                        // Resets the visited array
    numVecs.clear();                                       // Clears the vector
    for (int i = 0; i < this->number_of_vertices - 1; i++) // For loop to fill the vector
    {
        numVecs.push_back({i, 0}); // Pushes back the numbers and repetitions
        for (int j = 0; j < this->number_of_vertices - 1; j++)
            Matrix[i][j] = 0; // Fills the matrix with 0's
    }
    for (int i = 0; i < (V); i++) // For loop to fill the graph
    {
        ant = rand() % (V); // Random number
        sig = rand() % (V); // Random number

        if (ant != sig)     // If the numbers are different
        {
            Adj_list[ant].push_back(sig); // Pushes back the number
            Adj_list[sig].push_back(ant); // Pushes back the number
            Matrix[ant][sig] = 1;         // Fills the matrix with 1's
            Matrix[sig][ant] = 1;         // Fills the matrix with 1's
        }
    }
}


//la complejidad de esta funcion es O(n^2)
void Graph::printGraph() // Prints the graph
{
    for (int i = 0; i < this->number_of_vertices; i++) // For loop to print the graph
    {
        cout << "Vertex " << i << ":";
        for (auto x : this->Adj_list[i])
        {
            cout << "-> " << x;
        }
        cout << endl;
    }
}

//la complejidad de esta funcion es O(n^2)
void Graph::printGraphM() // Prints the graph in matrix form
{
    for (int i = 0; i < this->number_of_vertices - 1; i++) // For loop to print the graph
    {
        for (int j = 0; j < this->number_of_vertices - 1; j++)
        {
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
}


//la complejidad de esta funcion es O(n)
void Graph::ResetVisited() // Resets the visited array
{
    for (int i = 0; i < number_of_vertices; i++)
    {
        visited[i] = false;
    }
}

//la complejidad de esta funcion es O(n^2)
void Graph::DFSM(int v) // DFS in matrix form
{
    visited[v] = true; // Sets the vertex as visited
    cout << v << " ";  // Prints the vertex
    for (int i = 0; i < number_of_vertices; i++)
    {
        if (Matrix[v][i] == 1 && (!visited[i])) // If the vertex is not visited
        {
            DFSM(i); // Calls the function again
        }
    }
}


//la complejidad de esta funcion es O(n^2)
void Graph::BFSM(int startVertex) // BFS in matrix form
{
    visited[startVertex] = true; // Sets the vertex as visited
    list<int> queue;             // Creates a queue
    queue.push_back(startVertex); // Pushes back the vertex
    while (!queue.empty())        // While the queue is not empty
    {
        startVertex = queue.front(); // Sets the vertex as the front of the queue
        cout << startVertex << " ";  // Prints the vertex
        queue.pop_front();           // Pops the front of the queue
        for (int i = 0; i < number_of_vertices; i++)
        {
            if (Matrix[startVertex][i] == 1 && (!visited[i])) // If the vertex is not visited
            {
                visited[i] = true; // Sets the vertex as visited
                queue.push_back(i); // Pushes back the vertex
            }
        }
    }
}


//la complejidad de esta funcion es O(n^2)
bool Graph::IsTree() // Checks if the graph is a tree
{
    ResetVisited(); // Resets the visited array
    int count = 0;  // Counter
    for (int i = 0; i < number_of_vertices; i++)
    {
        if (!visited[i]) // If the vertex is not visited
        {
            DFSM(i); // Calls the function
            count++; // Increases the counter
        }
    }
    if (count == 1) // If the counter is 1
    {
        return true; // Returns true
    }
    else
    {
        return false; // Returns false
    }
}


//la complejidad de esta funcion es O(n^2)
void Graph::topologicalSort() // Topological sort
{
    ResetVisited(); // Resets the visited array
    deque<int> q;   // Creates a deque
    for (int i = 0; i < number_of_vertices; i++)
    {
        if (!visited[i]) // If the vertex is not visited
        {
            topologicalSortAux(i, q); // Calls the function
        }
    }
    while (!q.empty()) // While the deque is not empty
    {
        cout << q.back() << " "; // Prints the back of the deque
        q.pop_back();            // Pops the back of the deque
    }
}

//la complejidad de esta funcion es O(n^2)
void Graph::topologicalSortAux(int v, deque<int> &q) // Auxiliar function for topological sort
{
    visited[v] = true; // Sets the vertex as visited
    for (int i = 0; i < number_of_vertices; i++)
    {
        if (Matrix[v][i] == 1 && (!visited[i])) // If the vertex is not visited
        {
            topologicalSortAux(i, q); // Calls the function
        }
    }
    q.push_front(v); // Pushes back the vertex
}


//la complejidad de esta funcion es O(n^2)
bool Graph::isBipartite(int startVertex) // Checks if the graph is bipartite
{
    ResetVisited(); // Resets the visited array
    vector<int> color(number_of_vertices, -1); // Creates a vector
    visited[startVertex] = true;               // Sets the vertex as visited
    color[startVertex] = 0;                    // Sets the color of the vertex
    list<int> queue;                           // Creates a queue
    queue.push_back(startVertex);              // Pushes back the vertex
    while (!queue.empty())                     // While the queue is not empty
    {
        startVertex = queue.front(); // Sets the vertex as the front of the queue
        queue.pop_front();           // Pops the front of the queue
        for (int i = 0; i < number_of_vertices; i++)
        {
            if (Matrix[startVertex][i] == 1 && (!visited[i])) // If the vertex is not visited
            {
                visited[i] = true; // Sets the vertex as visited
                color[i] = 1 - color[startVertex]; // Sets the color of the vertex
                queue.push_back(i); // Pushes back the vertex
            }
            else if (Matrix[startVertex][i] == 1 && color[i] == color[startVertex]) // If the vertex is visited and the color is the same
            {
                return false; // Returns false
            }
        }
    }
    return true; // Returns true
}

//la complejidad de esta funcion es O(n^2)
void Graph::DFS(int v) // DFS in list form
{
    visited[v] = true; // Sets the vertex as visited
    cout << v << " ";  // Prints the vertex
    for (auto i : Adj_list[v])
    {
        if (!visited[i]) // If the vertex is not visited
        {
            DFS(i); // Calls the function
        }
    }
}

int main(){
// the aplication must ask the user for the number of vertices and only that
// the program must generate a random graph with the number of vertices given by the user
// hacemos que el valor de random cambie con el tiempo
    srand(time(NULL));


    int V; // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> V; // User input
    Graph g(V); // Creates a graph
    g.LoadGraph(V); // Loads the graph
    cout << endl;
    cout << "Graph in list form:" << endl;
    g.printGraph(); // Prints the graph in list form
    cout << endl;
// the program must print if the graph is a tree or not
    if (g.IsTree()) // If the graph is a tree
    {
        cout << "The graph is a tree" << endl; // Prints the graph is a tree
    }
    else // If the graph is not a tree
    {
        cout << "The graph is not a tree" << endl; // Prints the graph is not a tree
    }

// the program must print the topological sort of the graph
    cout << "Topological sort:" << endl;
    g.topologicalSort(); // Prints the topological sort of the graph
    cout << endl;
// the program must print if the graph is bipartite or not
    if (g.isBipartite(0)) // If the graph is bipartite
    {
        cout << "The graph is bipartite" << endl; // Prints the graph is bipartite
    }
    else // If the graph is not bipartite
    {
        cout << "The graph is not bipartite" << endl; // Prints the graph is not bipartite
    }

}; 

