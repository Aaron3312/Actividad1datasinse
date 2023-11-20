#include <iostream>
#include <list>
#include <vector>
#include <set>
using namespace std;

struct Entra{
    vector<int> numeros;
    string texto;
};

struct Node{
    int num;
    int acum = 1;
    vector<string> renglones;
    Node(int a):num(a){}
};

class Graph{
private:
    int numVertices;
    list<int> *adjLists;
    bool *visited;
    set<Node> Nodos;
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
};

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

int main(){
    Graph g(5);
    vector<Entra> entradas = {{{1, 2, 3, 1, 2}, "Texto1"}, {{0, 4}, "Texto2"}, {{2, 4,2,4}, "Texto3"}};
    g.loadGraph(entradas);
    g.printGraph();
    return 0;
}