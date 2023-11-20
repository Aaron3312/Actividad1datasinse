#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>


using namespace std;

struct ParrafoYPuerto // se crea la estructura tipo NODO
{
    vector<int> ips; // numeros de ips
    string texto;    // texto del parrafo
};


struct Entra
{
    vector<int> numeros;
    string texto;
};

struct Node
{
    int num;
    int acum;
    vector<string> renglones;
    Node(int a) : num(a), acum(1) {}
};

class Graph
{
private:
    int numVertices;
    list<int> *adjLists;
    bool *visited;
    set<Node> Nodos;


public:
    Graph(int V)
    {
        numVertices = V;
        adjLists = new list<int>[V];
        visited = new bool[V];
    }
    ~Graph()
    {
        delete[] adjLists;
        delete[] visited;
    }
    void printGraph();
    void loadGraph(vector<Entra>);
    void heapify(vector<Node>, int, int);
    vector<Node> listaHeap();
    void printMayores();
};

void GetLinesAndIntFromIpTXT(string bitacore, int &counts, vector<Entra> &ParrafoYPuertoVector)
{ // con base en el string que le introducimos es el nombre del archivo
    ifstream bitacora(bitacore);

    if (!bitacora.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
    }

    std::string texto;
    // std::regex ipRegex("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
    // std::regex ipRegex("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+):(\\d+)");
    std::regex ipRegex("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
    string linea;

    while (getline(bitacora, texto))
    { // se lee linea por linea el archivo

        std::smatch match;
        linea = texto;

        while (regex_search(texto, match, ipRegex))
        { // se busca la ip en la linea

            // si match 1 es null entonces se le asigna un 192
            ParrafoYPuertoVector.push_back({{stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])}, linea});
            printf("IPINVECTOR: %d.%d.%d.%d\n", ParrafoYPuertoVector[counts].numeros[0], ParrafoYPuertoVector[counts].numeros[1], ParrafoYPuertoVector[counts].numeros[2], ParrafoYPuertoVector[counts].numeros[3]);

            texto = match.suffix();
            counts++;
            cout << "counts: " << counts << endl;
        }
    }
    bitacora.close();
}

void Graph::loadGraph(vector<Entra> vecEntradas)
{
    set<pair<int, int>> visitedPairs;
    set<int> visitedInv;
    for (const auto &entrada : vecEntradas)
    {
        for (size_t i = 0; i < entrada.numeros.size() - 1; ++i)
        {
            pair<int, int> currentPair = {entrada.numeros[i], entrada.numeros[i + 1]};
            set<int> currentInv = {entrada.numeros[i]};

            if (visitedPairs.find(currentPair) == visitedPairs.end())
            {
                this->adjLists[entrada.numeros[i]].push_back(entrada.numeros[i + 1]);
                visitedPairs.insert(currentPair);
            }
            if (visitedInv.find(entrada.numeros[i]) == visitedInv.end())
            {
                Node *currentNode = new Node(entrada.numeros[i]);
                currentNode->renglones.push_back(entrada.texto);
                Nodos.insert(*currentNode);
                visitedInv.insert(entrada.numeros[i]);
            }
            else
            {
                auto it = Nodos.find(Node(entrada.numeros[i]));

                if (it != Nodos.end())
                {
                    Node tempNode = *it;
                    tempNode.acum += 1;
                    tempNode.renglones.push_back(entrada.texto);
                    Nodos.erase(it);
                    Nodos.insert(tempNode);
                }
            }
        }
    }
}
void Graph::printGraph()
{
    for (int i = 0; i < this->numVertices; i++)
    {
        cout << "\nVertex " << i << ":";
        for (auto x : this->adjLists[i])
            cout << "-> " << x;
        cout << endl;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//Funcion que crea una lista con los 10 nodos con el mayor valor de acum
vector<Node> Graph::listaHeap()
{
    vector<Node> listaMayores;
    for (auto i : Nodos)
    {
        if (listaMayores.size() < 10)
        {
            listaMayores.push_back(i);
            int n = listaMayores.size();
            heapify(listaMayores, n, listaMayores.size() - 1);
        }
        else
        {
            if (i.acum > listaMayores[0].acum)
            {
                listaMayores[0] = i;
                int n = listaMayores.size();
                heapify(listaMayores, n, 0);
            }
        }
    }
}

void Graph::heapify(vector<Node> listaMayores, int n, int i)
{
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;
    if (izq < n && listaMayores[izq].acum > listaMayores[mayor].acum)
    {
        mayor = izq;
    }
    if (der < n && listaMayores[der].acum > listaMayores[mayor].acum)
    {
        mayor = der;
    }
    if (mayor != i)
    {
        swap(listaMayores[i], listaMayores[mayor]);
        heapify(listaMayores, n, mayor);
    }
}

void Graph::printMayores()
{
    auto listaMayores = listaHeap();
    for (int i = 0; i < 10; i++)
    {
        cout << "IP segment: " << listaMayores[i].num << ",  Out-degree value: " << listaMayores[i].acum << endl;
    }
}

int main()
{
    vector<Entra> ParrafoYPuertoVector;
    int counts = 0;
    string bitacore = "bitacoraCorta.txt";
    GetLinesAndIntFromIpTXT(bitacore, counts, ParrafoYPuertoVector);

    Graph g(5);
    vector<Entra> entradas = {{{1, 2, 3, 1, 2}, "Texto1"}, {{0, 4}, "Texto2"}, {{2, 4, 2, 4}, "Texto3"}};
    g.loadGraph(entradas);
    g.printGraph();
    return 0;
}