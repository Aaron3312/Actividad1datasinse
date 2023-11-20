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

// struct Entra sirve para guardar los datos de las lineas del archivo
struct Entra
{
    vector<int> numeros;
    string texto;
};

// struct Node sirve para crear los nodos del grafo
struct Node
{
    int num;
    int acum;
    vector<string> renglones;
    Node(int a) : num(a), acum(1) {}

    // Implementación del operador <
    bool operator<(const Node &other) const
    {
        // Comparar primero por acum y luego por num si acum es igual
        if (acum == other.acum)
        {
            return num < other.num;
        }
        return acum < other.acum;
    }
};

// Implement comparison logic here.
// For example, if Node has an 'id' member, you can do:
// return id < other.id;

// clase grafo con sus metodos y atributos que sirven para crear el grafo
class Graph
{
private:
    int numVertices;
    list<int> *adjLists;
    bool *visited;
    vector<Node> Nodos; // Cambiado de set a vector
    vector<Node> listaMayores;

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
    void heapify(vector<Node> &, int, int);
    void listaHeap();    // Mi parte
    void printMayores(); // Mi parte
    void InIP();         // Mi parte
    void GenerateArchiveResults();
};

// funcion que lee el archivo y guarda los datos en un vector de structs con complejidad O(n)
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
            // printf("IPINVECTOR: %d.%d.%d.%d\n", ParrafoYPuertoVector[counts].numeros[0], ParrafoYPuertoVector[counts].numeros[1], ParrafoYPuertoVector[counts].numeros[2], ParrafoYPuertoVector[counts].numeros[3]);

            texto = match.suffix();
            counts++;
            // cout << "counts: " << counts << endl;
        }
    }
    bitacora.close();
}

// funcion que carga el grafo con los datos del vector de structs con complejidad O(n^2)
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
                Nodos.push_back(*currentNode); // Cambiado de insert a push_back
                visitedInv.insert(entrada.numeros[i]);
            }
            else
            {
                auto it = find_if(Nodos.begin(), Nodos.end(), [&](const Node &n)
                                  { return n.num == entrada.numeros[i]; });

                if (it != Nodos.end())
                {
                    Node &tempNode = *it;
                    tempNode.acum += 1;
                    tempNode.renglones.push_back(entrada.texto);
                }
            }
        }
    }
}

// funcion que imprime el grafo con complejidad O(n)
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

// funcion que crea una lista con los 10 nodos con el mayor valor de acum con complejidad O(n)
void Graph::listaHeap()
{
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

// funcion que ordena la lista de los 10 nodos con mayor valor de acum con complejidad O(n)
void Graph::heapify(vector<Node> &listaMayores, int n, int i)
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

// funcion que imprime la lista de los 10 nodos con mayor valor de acum con complejidad O(1)
void Graph::printMayores()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "IP segment: " << listaMayores[i].num << ",  Out-degree value: " << listaMayores[i].acum << endl;
    }
}

// funcion que imprime el vertice con mayor valor de acum y sus ips con complejidad O(1)
void Graph::InIP()
{
    cout << "Vertice con mayor out-degree: " << listaMayores[0].num << endl;
    cout << "IPs con el vertice con mayor out-degree: " << endl;
    for (int i = 0; i < listaMayores[0].renglones.size(); i++)
    {
        cout << listaMayores[0].renglones[i] << endl;
    }
}

// funcion que genera el archivo de resultados con complejidad O(1)
void Graph::GenerateArchiveResults()
{
    ofstream results;
    results.open("output.txt");
    results << "Vertice con mayor out-degree: " << listaMayores[0].num << endl;
    // tambien incluimos la lista de los 10 nodos con mayor valor de acum
    results << "\nLista de los 10 nodos con mayor valor de acum: " << endl;
    for (int i = 0; i < 10; i++)
    {
        results << "IP segment: " << listaMayores[i].num << ",  Out-degree value: " << listaMayores[i].acum << endl;
    }
    results << "\nIPs con el vertice con mayor out-degree: " << endl;
    for (int i = 0; i < listaMayores[0].renglones.size(); i++)
    {
        results << listaMayores[0].renglones[i] << endl;
    }

    results.close();
}

int main()
{
    // declaramos el vector de ParrafoYPuertoVector y counts
    vector<Entra> ParrafoYPuertoVector;
    int counts = 0;                                                  // numero de lineas del archivo
    string bitacore = "bitacora.txt";                                // nombre del archivo de lectura, normalmente usamos bitacoraCorta.txt para pruebas
    GetLinesAndIntFromIpTXT(bitacore, counts, ParrafoYPuertoVector); // leemos el archivo y guardamos los datos en el vector de structs ParrafoYPuertoVector
    // imprimimos todos los vectores (unicamente utilizable para usos del desarrollo)
    /*
    for (int i = 0; i < counts; i++){
        cout << "IP: " << ParrafoYPuertoVector[i].numeros[0] << "." << ParrafoYPuertoVector[i].numeros[1] << "." << ParrafoYPuertoVector[i].numeros[2] << "." << ParrafoYPuertoVector[i].numeros[3] << endl;
        cout << "Texto: " << ParrafoYPuertoVector[i].texto << endl;
    }*/

    Graph g(999);                      // creamos el grafo con 999 vertices cada segmento de ip es un vertice por lo que el maximo es 999
    g.loadGraph(ParrafoYPuertoVector); // cargamos el grafo con los datos del vector de structs ParrafoYPuertoVector
    g.printGraph();                    // imprimimos el grafo
    g.listaHeap();                     // creamos la lista de los 10 nodos con mayor valor de acum
    g.printMayores();                  // imprimimos la lista de los 10 nodos con mayor valor de acum
    g.InIP();                          // imprimimos el vertice con mayor valor de acum y sus ips
    g.GenerateArchiveResults();        // generamos el archivo de resultados

    return 0;
}