#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

struct LogEntry {
    vector<int> ipAddress;
    string logText;
};

struct NetworkNode {
    int segment;
    int occurrences;
    vector<string> logLines;

    NetworkNode(int seg) : segment(seg), occurrences(1) {}

    bool operator<(const NetworkNode &other) const {
        if (occurrences == other.occurrences) {
            return segment < other.segment;
        }
        return occurrences < other.occurrences;
    }
};

class NetworkGraph {
private:
    int numVertices;
    list<int> *adjacencyLists;
    bool *visited;
    vector<NetworkNode> nodes;
    vector<NetworkNode> topNodes;

public:
    NetworkGraph(int V) {
        numVertices = V;
        adjacencyLists = new list<int>[V];
        visited = new bool[V];
    }

    ~NetworkGraph() {
        delete[] adjacencyLists;
        delete[] visited;
    }

    void displayGraph();
    void constructGraph(vector<LogEntry>);
    void heapifyTopNodes(vector<NetworkNode> &, int, int);
    void buildTopNodesHeap();
    void printTopNodes();
    void printTopNodeAndLogs();
    void generateResultsFile();
};

void readLogEntriesFromTxtFile(string filename, int &count, vector<LogEntry> &logEntries) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open the file" << endl;
    }

    std::string logText;
    std::regex ipRegex("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
    string logLine;

    while (getline(file, logText)) {
        std::smatch match;
        logLine = logText;

        while (regex_search(logText, match, ipRegex)) {
            logEntries.push_back({{stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])}, logLine});
            logText = match.suffix();
            count++;
        }
    }
    file.close();
}

void NetworkGraph::constructGraph(vector<LogEntry> logEntries) {
    set<pair<int, int>> visitedPairs;
    set<int> visitedSegments;

    for (const auto &entry : logEntries) {
        for (size_t i = 0; i < entry.ipAddress.size() - 1; ++i) {
            pair<int, int> currentPair = {entry.ipAddress[i], entry.ipAddress[i + 1]};
            set<int> currentSegment = {entry.ipAddress[i]};

            if (visitedPairs.find(currentPair) == visitedPairs.end()) {
                this->adjacencyLists[entry.ipAddress[i]].push_back(entry.ipAddress[i + 1]);
                visitedPairs.insert(currentPair);
            }

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

void NetworkGraph::displayGraph() {
    for (int i = 0; i < this->numVertices; i++) {
        cout << "\nVertex " << i << ":";
        for (auto x : this->adjacencyLists[i])
            cout << "-> " << x;
        cout << endl;
    }
}

void NetworkGraph::buildTopNodesHeap() {
    for (auto i : nodes) {
        if (topNodes.size() < 10) {
            topNodes.push_back(i);
            int n = topNodes.size();
            heapifyTopNodes(topNodes, n, topNodes.size() - 1);
        } else {
            if (i.occurrences > topNodes[0].occurrences) {
                topNodes[0] = i;
                int n = topNodes.size();
                heapifyTopNodes(topNodes, n, 0);
            }
        }
    }
}

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


void NetworkGraph::printTopNodes() {
    for (int i = 0; i < 10; i++) {
        cout << "IP Segment: " << topNodes[i].segment << ", Occurrences: " << topNodes[i].occurrences << endl;
    }
}

void NetworkGraph::printTopNodeAndLogs() {
    cout << "Vertex with the highest occurrences: " << topNodes[0].segment << endl;
    cout << "Logs with the vertex with the highest occurrences: " << endl;
    for (int i = 0; i < topNodes[0].logLines.size(); i++) {
        cout << topNodes[0].logLines[i] << endl;
    }
}

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
    vector<LogEntry> logEntries;
    int count = 0;
    string filename = "bitacora.txt";
    readLogEntriesFromTxtFile(filename, count, logEntries);

    NetworkGraph network(999);
    network.constructGraph(logEntries);
    network.displayGraph();
    network.buildTopNodesHeap();
    network.printTopNodes();
    network.printTopNodeAndLogs();
    network.generateResultsFile();

    return 0;
}
