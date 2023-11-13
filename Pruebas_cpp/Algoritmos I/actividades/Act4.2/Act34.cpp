#include <iostream>
#include <list>
#include <vector>
#include <deque>
using namespace std;

struct Nums
{
    int num, rep;
};

class Graph
{
private:
    int numVertices, ant, sig;
    list<int> *Adj_list;
    bool Matriz[100][100];
    bool *visited;
    vector<Nums> numVecs;

public:
    Graph(int V)
    {
        numVertices = V;
        Adj_list = new list<int>[V];
        visited = new bool[V];
    }
    ~Graph()
    {
        delete[] Adj_list;
        delete[] visited;
    }
    void printGraph();
    void printGraphM();
    bool IsTree();
    void ResetVisited();
    void DFSM(int);
    void BFSM(int);
    void LoadGraph(int);
    void topologicalSort();
    void topologicalSortAux(int, deque<int> &);
    bool isBipartite(int);
};

void Graph::LoadGraph(int s)
{
    ResetVisited();
    numVecs.clear();
    for (int i = 0; i < this->numVertices - 1; i++)
    {
        numVecs.push_back({i, 0});
        for (int j = 0; j < this->numVertices - 1; j++)
            Matriz[i][j] = 0;
    }
    for (int i = 0; i < (s); i++)
    {
        ant = rand() % (s);
        sig = rand() % (s);
        if (ant != sig)
        {
            numVecs[ant].rep = 1;
            numVecs[sig].rep = 1;
        }
        cout << ant << " " << sig << endl;
        if (sig > ant)
        {
            Matriz[sig][ant] = 1;
        }
        else if (ant > sig)
        {
            Matriz[ant][sig] = 1;
        }
    }
    for (int i = 0; i < this->numVertices - 1; i++)
    {
        if (numVecs[i].rep == 0 && numVecs[i].num != numVecs[s - 1].num)
        {
            Matriz[i + 1][i] = 1;
        }
        else if (numVecs[i].rep == 0 && numVecs[i].num == numVecs[s - 1].num)
        {
            Matriz[i][i - 1] = 1;
        }
    }
}

bool Graph::IsTree()
{
    ResetVisited();
    int arco = 0;
    int vertices = 0;
    for (int i = 0; i < this->numVertices; i++)
    {
        for (int j = 0; j < this->numVertices; j++)
        {
            if (Matriz[i][j] == 1)
            {
                arco += 1;
                if (!visited[i])
                {
                    vertices += 1;
                    visited[i] = true;
                }
                if (!visited[j])
                {
                    vertices += 1;
                    visited[j] = true;
                }
            }
        }
    }
    return (arco == vertices - 1);
}

void Graph::topologicalSortAux(int v, deque<int> &vecN)
{
    visited[v] = true;

    for (int i = 0; i < numVertices; i++)
    {
        if (Matriz[v][i] == 1 && !visited[i])
        {
            topologicalSortAux(i, vecN);
        }
    }

    vecN.push_front(v);
}

void Graph::topologicalSort()
{
    deque<int> vecN;
    ResetVisited();

    for (int i = 0; i < numVertices; i++)
    {
        if (!visited[i])
        {
            topologicalSortAux(i, vecN);
        }
    }

    cout << "Orden topologico:" << endl;

    while (!vecN.empty())
    {
        cout << vecN.front();
        vecN.pop_front();
        if (!vecN.empty())
        {
            cout << ", ";
        }
    }
    cout << endl;
}

bool Graph::isBipartite(int startVertex)
{
    ResetVisited();
    vector<int> color(numVertices, -1);
    visited[startVertex] = true;
    color[startVertex] = 0;

    list<int> queue;
    queue.push_back(startVertex);

    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop_front();

        for (int u = 0; u < numVertices; u++)
        {
            if (Matriz[v][u] == 1)
            {
                if (!visited[u])
                {
                    visited[u] = true;
                    color[u] = !color[v];
                    queue.push_back(u);
                }
                else if (color[v] == color[u])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void Graph::printGraphM()
{
    for (int i = 0; i < this->numVertices; i++)
    {
        cout << "\nVertex " << i << ":";

        for (int j = 0; j < this->numVertices; j++)
            cout << Matriz[i][j] << " ";
        cout << endl;
    }
}

void Graph::ResetVisited()
{
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
}

void Graph::DFSM(int vertex)
{
    visited[vertex] = true;
    cout << vertex << " ";

    for (int i = 0; i < numVertices; i++)
    {
        if (Matriz[vertex][i] && !visited[i])
        {
            DFSM(i);
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

        for (int i = 0; i < numVertices; i++)
        {
            if (Matriz[currVertex][i] && !visited[i])
            {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}

int main()
{
    int Vertices = 10;
    Graph G(Vertices);
    Graph F(Vertices);
    Graph H(Vertices);
    Graph I(Vertices);
    G.LoadGraph(Vertices);
    G.printGraphM();
    G.topologicalSort();
    cout << G.IsTree() << endl;
    cout << G.isBipartite(9) << endl;
    cout << endl
         << endl;
    return 0;
}