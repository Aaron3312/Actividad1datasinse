#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

struct node
{
    int vertex;
    struct node *next;
};

class priority_queue
{
private:
    vector<int> vect;
    int index;

public:
    priority_queue();
    ~priority_queue();
    void heapify(vector<int> &, int);
    int Top();
    bool Empty();
    void DeleteAll();
    void Pop();
    void Push(int);
    int Size();
};

// Constructor por default para inicializar el vector y el index
priority_queue::priority_queue()
{
    vect = {};
    index = 0;
}

// Destructor para eliminar todos los elementos del vector
priority_queue::~priority_queue()
{
    DeleteAll();
}

// Funcion Heapify para ordenar el vector y mantener la propiedad de heap
// en el peor de los casos recorre todo por lo que es O(n)
void priority_queue::heapify(vector<int> &heepTree, int index)
{
    int size = heepTree.size();
    int largest = index;
    int l = 2 * index + 1;
    int r = 2 * index + 2;

    if (l < size && heepTree[l] > heepTree[largest])
        largest = l;
    if (r < size && heepTree[r] > heepTree[largest])
        largest = r;
    if (largest != index)
    {
        swap(heepTree[index], heepTree[largest]);
        heapify(heepTree, largest);
    }
}
// Funcion Swap para intercambiar los valores de dos variables
// es como una extension de la funcion heapify por lo que es O(1)

void swap(int &a, int &b)
{
    // unicamente cambia los valores, es interesante recordar el hecho del amperson para el paso por referencia
    int temp = a;
    a = b;
    b = temp;
}

// Funcion Push para insertar un dato en el vector y mantener la propiedad de heap de
// La función coloca el nuevo valor al final del vector y a partir de ahí
// empieza a subir por el nuevo valor y aplicándole Heapify si es necesario,
// pero como no vuelve a recorrer todo el vector es O(log n)

void priority_queue::Push(int data)
{
    vect.push_back(data);
    int index = vect.size() - 1;
    int parent = (index - 1) / 2;
    while (index > 0 && vect[parent] < vect[index])
    {
        swap(vect[index], vect[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// Función Pop para eliminar el dato con mayor prioridad del vector y mantener la propiedad de heap de maximos
// su complejidad es O(n) ya que en el peor de los casos recorre todo el vector
void priority_queue::Pop()
{
    int size = vect.size();
    if (size == 0)
    {
        cout << "El vector esta vacio" << endl;
        return;
    }
    vect[0] = vect[size - 1];
    vect.pop_back();
    heapify(vect, 0);
}

// Función Top para obtener el dato con mayor prioridad del vector y mantener la propiedad de heap de maximos
// su complejidad es O(1) ya que unicamente regresa el primer elemento del vector
int priority_queue::Top()
{
    if (vect.size() != 0)
    {
        return vect[0];
    }
    cout << "El vector esta vacio ";
    return -1;
}

// Función Empty para verificar si el vector esta vacio o no, en caso de estar vacio regresa true, en caso contrario regresa false
// su complejidad es O(1) ya que unicamente verifica si el tamaño del vector es 0
bool priority_queue::Empty()
{
    if (vect.size() == 0)
        return true;
    else
        return false;
}

// Función Size para obtener el tamaño del vector y regresarlo como un entero
// su complejidad es O(1) ya que unicamente regresa el tamaño del vector
int priority_queue::Size()
{
    return vect.size();
}

// Funcion DelleteAll para eliminar todos los elementos del vector
// su complejidad es O(1) ya que unicamente elimina todos los elementos del vector
void priority_queue::DeleteAll()
{
    vect.clear();
}

// Graph class (containing attributes, methods, and functions)
class Graph
{
private:
    int numVertex;
    list<int> *Adj_list;
    bool *visited;

public:
    // Constructor
    Graph(int V)
    {
        numVertex = V;
        Adj_list = new list<int>[V];
        visited = new bool[V];
    };

    ~Graph()
    {
        delete[] Adj_list;
        delete[] visited;
    };

    void addEdge(int s, int d)
    {
        this->Adj_list[s].push_back(d);
        this->Adj_list[d].push_back(s);
    };

    void loadGraph() // esta funcion te tiene que generar un grafo de v vertices y E aristas aleatoriamente
    {
        for (int i = 0; i < this->numVertex; i++)
        {
            cout << "Vertex " << i << ":";
            for (auto x : this->Adj_list[i])
            {
                cout << "-> " << x;
            }
            cout << endl;
        }
    };

    void resetVisited()
    {
        for (int i = 0; i < numVertex; i++)
        {
            visited[i] = false;
        }
    };

    bool isTree()
    {
        resetVisited();
        return !hasCycle(0, -1) && isConnected();
    }

    bool hasCycle(int vertex, int parent)
    {
        visited[vertex] = true;
        for (auto i : Adj_list[vertex])
        {
            if (!visited[i])
            {
                if (hasCycle(i, vertex))
                {
                    return true;
                }
            }
            else if (i != parent)
            {
                return true;
            }
        }
        return false;
    }

    bool isConnected()
    {
        for (int i = 0; i < numVertex; i++)
        {
            if (!visited[i])
            {
                return false;
            }
        }
        return true;
    }

    void topologicalSort()
    {
        resetVisited();
        stack<int> s;
        for (int i = 0; i < numVertex; i++)
        {
            if (!visited[i])
            {
                topologicalSortUtil(i, s);
            }
        }
        cout << "\nTopological Sort:\n";
        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }
    }

    void topologicalSortUtil(int vertex, stack<int> &s)
    {
        visited[vertex] = true;
        for (auto i : Adj_list[vertex])
        {
            if (!visited[i])
            {
                topologicalSortUtil(i, s);
            }
        }
        s.push(vertex);
    }

    bool bipartiteGraph()
    {
        vector<int> color(numVertex, -1);

        for (int i = 0; i < numVertex; ++i)
        {
            if (color[i] == -1)
            {
                if (!bipartiteGraphUtil(i, color))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool bipartiteGraphUtil(int vertex, vector<int> &color)
    {
        color[vertex] = 1;

        priority_queue q;
        q.Push(vertex);

        while (!q.Empty())
        {
            int u = q.Top();
            q.Pop();

            for (auto v : Adj_list[u])
            {
                if (color[v] == -1)
                {
                    color[v] = 1 - color[u];
                    q.Push(v);
                }
                else if (color[v] == color[u])
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    int vertex, edge, a, b;
    cout << "Enter number of vertices:\n";
    cin >> vertex;
    cout << "Enter number of edges:\n";
    cin >> edge;

    Graph G(vertex);

    for (int i = 0; i < edge; i++)
    {
        cout << "For edge #" << i + 1 << endl;
        cout << "Enter value a: ";
        cin >> a;
        cout << "Enter value b: ";
        cin >> b;
        G.addEdge(a, b);
    }

    cout << "\nGraph:\n";
    G.loadGraph();

    cout << "\nIs Tree: " << (G.isTree() ? "Yes" : "No") << "\n";

    G.topologicalSort();

    cout << "\n\nIs Bipartite Graph: " << (G.bipartiteGraph() ? "Yes" : "No") << "\n\n";

    return 0;
}
