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

struct Entra{
    vector<int> numeros;
    string texto;
};

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
        if (acum == other.acum) {
            return num < other.num;
        }
        return acum < other.acum;
    }
};


        // Implement comparison logic here.
        // For example, if Node has an 'id' member, you can do:
        // return id < other.id;

class Graph{
private:
    int numVertices;
    list<int> *adjLists;
    bool *visited;
    set<Node> Nodos;
    vector<Node> listaMayores;
public:
    Graph(int V){
        numVertices = V;
        adjLists = new list<int>[V];
        visited = new bool[V];

    }
    ~Graph(){
        delete[] adjLists;
        delete[] visited;
    }
    void printGraph();
    void loadGraph(vector<Entra>);
    void heapify(vector<Node>&, int, int);
    void listaHeap();                       //Mi parte
    void printMayores();                    //Mi parte
    void InIP();                            //Mi parte
    
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
            //printf("IPINVECTOR: %d.%d.%d.%d\n", ParrafoYPuertoVector[counts].numeros[0], ParrafoYPuertoVector[counts].numeros[1], ParrafoYPuertoVector[counts].numeros[2], ParrafoYPuertoVector[counts].numeros[3]);

            texto = match.suffix();
            counts++;
            //cout << "counts: " << counts << endl;
        }
    }
    bitacora.close();
}

void Graph::loadGraph(vector<Entra> vecEntradas){
    set<pair<int, int>> visitedPairs;
    set<int> visitedInv;
    for (const auto &entrada : vecEntradas){
        for (size_t i = 0; i < entrada.numeros.size() - 1; ++i){
            pair<int, int> currentPair = {entrada.numeros[i], entrada.numeros[i + 1]};
            set<int> currentInv = {entrada.numeros[i]};

            if (visitedPairs.find(currentPair) == visitedPairs.end()){
                this->adjLists[entrada.numeros[i]].push_back(entrada.numeros[i + 1]);
                visitedPairs.insert(currentPair);
            }
            if (visitedInv.find(entrada.numeros[i]) == visitedInv.end()){
                Node *currentNode = new Node(entrada.numeros[i]);
                currentNode->renglones.push_back(entrada.texto);
                Nodos.insert(*currentNode);
                visitedInv.insert(entrada.numeros[i]);
            }
            else{
                auto it = Nodos.find(Node(entrada.numeros[i]));

                if (it != Nodos.end()) {
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
void Graph::printGraph(){
    for (int i = 0; i< this->numVertices; i++){
        cout << "\nVertex " << i << ":";
        for (auto x : this->adjLists[i])
            cout << "-> " << x;
        cout<<endl;        
    }
}
//---------------------------------------------------------------------Mi parte---------------------------------------------------------------------//
//funcion que crea una lista con los 10 nodos con el mayor valor de acum
void Graph::listaHeap(){
    for (auto i: Nodos){
        if(listaMayores.size()<10){
            listaMayores.push_back(i);
            int n = listaMayores.size();
            heapify(listaMayores, n, listaMayores.size()-1);
        }
        else{
            if(i.acum>listaMayores[0].acum){
                listaMayores[0]=i;
                int n = listaMayores.size();
                heapify(listaMayores, n, 0);
            }
        }
    }
}


void Graph::heapify(vector<Node> &listaMayores, int n, int i){
    int mayor = i;
    int izq = 2*i+1;
    int der = 2*i+2;
    if(izq<n && listaMayores[izq].acum>listaMayores[mayor].acum){
        mayor = izq;
    }
    if(der<n && listaMayores[der].acum>listaMayores[mayor].acum){
        mayor = der;
    }
    if(mayor!=i){
        swap(listaMayores[i], listaMayores[mayor]);
        heapify(listaMayores, n, mayor);
    }
}

void Graph::printMayores(){
    for(int i=0; i<10; i++){
        cout<<"IP segment: "<<listaMayores[i].num<<",  Out-degree value: "<<listaMayores[i].acum<<endl;
    }
}

void Graph::InIP(){
    cout<<"Vertice con mayor out-degree: "<<listaMayores[0].num<<endl;
    cout<<"IPs con el vertice con mayor out-degree: "<<endl;
    for(int i=0; i<listaMayores[0].renglones.size(); i++){
        cout<<listaMayores[0].renglones[i]<<endl;
    }
}
//---------------------------------------------------------------------Mi parte fin---------------------------------------------------------------------//
int main(){

    vector<Entra> ParrafoYPuertoVector;
    int counts = 0;
    string bitacore = "bitacora.txt";
    GetLinesAndIntFromIpTXT(bitacore, counts, ParrafoYPuertoVector);
    //imprimimos todos los vectores
    /*
    for (int i = 0; i < counts; i++){
        cout << "IP: " << ParrafoYPuertoVector[i].numeros[0] << "." << ParrafoYPuertoVector[i].numeros[1] << "." << ParrafoYPuertoVector[i].numeros[2] << "." << ParrafoYPuertoVector[i].numeros[3] << endl;
        cout << "Texto: " << ParrafoYPuertoVector[i].texto << endl;
    }*/


    Graph g(999);

    g.loadGraph(ParrafoYPuertoVector);
    g.printGraph();
    g.listaHeap();
    g.printMayores();
    g.InIP();
    return 0;
    

}