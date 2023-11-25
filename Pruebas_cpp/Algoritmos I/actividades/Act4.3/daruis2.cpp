#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

// Definición de la estructura que representa una entrada de registro
struct LogEntry {
    vector<int> ipAddress; // Dirección IP representada como una lista de enteros
    string logText;        // Texto del registro
};

// Definición de la estructura que representa un nodo de la red
struct NetworkNode {
    int segment;            // Segmento de IP asociado al nodo
    int occurrences;        // Número de ocurrencias
    vector<string> logLines; // Líneas de registro asociadas al nodo

    NetworkNode(int seg) : segment(seg), occurrences(1) {}

    // Sobrecarga del operador de comparación para ordenar nodos
    bool operator<(const NetworkNode &other) const {
        if (occurrences == other.occurrences) {
            return segment < other.segment;
        }
        return occurrences < other.occurrences;
    }
};

// Clase que representa un grafo de la red
class NetworkGraph {
private:
    int numVertices;      // Número de vértices en el grafo
    list<int> *adjacencyLists; // Listas de adyacencia para representar conexiones entre nodos
    bool *visited;        // Arreglo para marcar nodos visitados durante el procesamiento
    vector<NetworkNode> nodes; // Vector de nodos representando los segmentos de IP
    vector<NetworkNode> topNodes; // Vector de los nodos con mayores ocurrencias

public:
    // Constructor
    NetworkGraph(int V) {
        numVertices = V;
        adjacencyLists = new list<int>[V];
        visited = new bool[V];
    }

    // Destructor
    ~NetworkGraph() {
        delete[] adjacencyLists;
        delete[] visited;
    }

    // Funciones de la clase

    // Construye el grafo a partir de las entradas de registro
    void constructGraph(vector<LogEntry>);

    // Muestra la estructura del grafo
    void displayGraph();

    // Construye un montículo con los nodos de mayor ocurrencia
    void buildTopNodesHeap();

    // Función auxiliar para mantener la propiedad de montículo
    void heapifyTopNodes(vector<NetworkNode> &topNodes, int n, int i);

    // Muestra los nodos con mayores ocurrencias
    void printTopNodes();

    // Muestra el nodo con mayor ocurrencia y sus registros asociados
    void printTopNodeAndLogs();

    // Genera un archivo de resultados con información sobre el grafo
    void generateResultsFile();
};

// Lee las entradas de registro desde un archivo de texto
void readLogEntriesFromTxtFile(string filename, int &SD3, vector<LogEntry> &logEntries) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open the file" << endl;
    }

    std::string logText;
    std::regex ipRegex("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
    string logLine;

    // Lee cada línea del archivo
    while (getline(file, logText)) {
        std::smatch match;
        logLine = logText;

        // Busca direcciones IP en la línea
        while (regex_search(logText, match, ipRegex)) {
            // Almacena la entrada de registro en la estructura correspondiente
            logEntries.push_back({{stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])}, logLine});
            logText = match.suffix();
            SD3++;
        }
    }
    file.close();
}

// Construye el grafo a partir de las entradas de registro
void NetworkGraph::constructGraph(vector<LogEntry> logEntries) {
    set<pair<int, int>> visitedPairs;
    set<int> visitedSegments;

    for (const auto &entry : logEntries) {
        for (size_t i = 0; i < entry.ipAddress.size() - 1; ++i) {
            pair<int, int> currentPair = {entry.ipAddress[i], entry.ipAddress[i + 1]};
            set<int> currentSegment = {entry.ipAddress[i]};

            // Evita duplicados en las listas de adyacencia
            if (visitedPairs.find(currentPair) == visitedPairs.end()) {
                this->adjacencyLists[entry.ipAddress[i]].push_back(entry.ipAddress[i + 1]);
                visitedPairs.insert(currentPair);
            }

            // Maneja la construcción de nodos y ocurrencias
            if (visitedSegments.find(entry.ipAddress[i]) == visitedSegments.end()) {
                NetworkNode *currentNode = new NetworkNode(entry.ipAddress[i]);
                currentNode->logLines.push_back(entry.logText);
                nodes.push_back(*currentNode);
                visitedSegments.insert(entry.ipAddress[i]);
            } else {
                auto it = find_if(nodes.begin(), nodes.end(), [&](const NetworkNode &node) {
                    return node.segment == entry.ipAddress[i];
                });

                if (it != nodes.end()) {
                    NetworkNode &tempNode = *it;
                    tempNode.occurrences += 1;
                    tempNode.logLines.push_back(entry.logText);
                }
            }
        }
    }
}

// Muestra la estructura del grafo
void NetworkGraph::displayGraph() {
    cout << "Graph Structure:" << endl;
    for (int i = 0; i < this->numVertices; i++) {
        cout << "Vertex " << i << ": ";
        if (this->adjacencyLists[i].empty()) {
            cout << "No connections";
        } else {
            for (auto neighbor : this->adjacencyLists[i]) {
                cout << neighbor << " ";
            }
        }
        cout << endl;
    }
}


// Construye un montículo con los nodos de mayor ocurrencia
void NetworkGraph::buildTopNodesHeap() {
    for (const auto &currentNode : nodes) {
        if (topNodes.size() < 10) {
            topNodes.push_back(currentNode);
            push_heap(topNodes.begin(), topNodes.end());
        } else if (currentNode.occurrences > topNodes[0].occurrences) {
            pop_heap(topNodes.begin(), topNodes.end());
            topNodes.back() = currentNode;
            push_heap(topNodes.begin(), topNodes.end());
        }
    }
}


// Función auxiliar para mantener la propiedad de montículo
void NetworkGraph::heapifyTopNodes(vector<NetworkNode> &topNodes, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && topNodes[left].occurrences > topNodes[largest].occurrences) {
        largest = left;
    }
    if (right < n && topNodes[right].occurrences > topNodes[largest].occurrences) {
        largest = right;
    }
    if (largest != i) {
        swap(topNodes[i], topNodes[largest]);
        heapifyTopNodes(topNodes, n, largest);
    }
}

// Muestra los nodos con mayores ocurrencias
void NetworkGraph::printTopNodes() {
    for (int i = 0; i < 10; i++) {
        cout << "IP Segment: " << topNodes[i].segment << ", Occurrences: " << topNodes[i].occurrences << endl;
    }
}

// Muestra el nodo con mayor ocurrencia y sus registros asociados
void NetworkGraph::printTopNodeAndLogs() {
    cout << "Vertex with the highest occurrences: " << topNodes[0].segment << endl;
    cout << "Logs with the vertex with the highest occurrences: " << endl;
    for (int i = 0; i < topNodes[0].logLines.size(); i++) {
        cout << topNodes[0].logLines[i] << endl;
    }
}

// Genera un archivo de resultados con información sobre el grafo
void NetworkGraph::generateResultsFile() {
    ofstream results;
    results.open("output.txt");
    results << "Vertex with the highest occurrences: " << topNodes[0].segment << endl;
    results << "\nList of the top 10 nodes with the highest occurrences: " << endl;
    for (int i = 0; i < 10; i++) {
        results << "IP Segment: " << topNodes[i].segment << ", Occurrences: " << topNodes[i].occurrences << endl;
    }
    results << "\nLogs with the vertex with the highest occurrences: " << endl;
    for (int i = 0; i < topNodes[0].logLines.size(); i++) {
        results << topNodes[0].logLines[i] << endl;
    }

    results.close();
}

int main() {
    // Declaración de variables
    vector<LogEntry> logEntries;
    string filename = "bitacora.txt";

    // Creación de un grafo de red y procesamiento de datos
    NetworkGraph network(999);
    int SD3 = 0;
    // Lectura de entradas de registro desde un archivo
    readLogEntriesFromTxtFile(filename, SD3, logEntries);

    // Construcción del grafo
    network.constructGraph(logEntries);

    // Visualización de la estructura del grafo
    network.displayGraph();

    // Construcción del montículo con los nodos de mayor ocurrencia
    network.buildTopNodesHeap();

    // Impresión de los nodos con mayores ocurrencias
    network.printTopNodes();

    // Impresión del nodo con mayor ocurrencia y sus registros asociados
    network.printTopNodeAndLogs();

    // Generación de un archivo de resultados con información sobre el grafo
    network.generateResultsFile();

    return 0;
}

