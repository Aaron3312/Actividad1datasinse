#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <fstream>
#include <regex>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>

using namespace std;

struct Nodo{
    int port, acum;
    vector <string> renglones;
    Nodo(){port = -1; acum = 1; }
};

using namespace std;

struct ParrafoYPuerto 
{
    int port; // numero que tendra cada puerto
    string texto; //texto del parrafo
};

void GetLinesAndPortFromTxT(string bitacore, int &counts,vector<ParrafoYPuerto> &ParrafoYPuertoVector)
{ // con base en el string que le introducimos es el nombre del archivo
    ifstream bitacora(bitacore);

    if (!bitacora.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
    }

    std::string texto;
    std::regex ipRegex("(\\d{4,5})");;
    string linea;

    while (getline(bitacora, texto))
    { // se lee linea por linea el archivo

        smatch match;
        linea = texto;
        while (regex_search(texto, match, ipRegex))
        { // se busca la ip en la linea
            string Port = match[0];
            texto = match.suffix();
            ParrafoYPuertoVector.push_back({stoi(Port),linea});
            counts++;
        }

    }
            bitacora.close();

}

class HashTable{
    private:
        int capacity;
        int cAcum = 0;
        list<Nodo> *table1;
        //vector de nodos donde se guardaran los 5 mas repetidos
        vector<Nodo> topPorts;

    public:
        HashTable(int V){
            int size = getPrime(V);
            this->capacity = size;
            table1 = new list<Nodo>[capacity];
        }
        ~HashTable(){
            delete []table1;
            for (int i = 0; i < capacity; ++i) {
        }
            cout<<"\nDestructor: HashTable deleted.\n";
        }
        bool checkPrime(int);
        int getPrime(int);
        void insertItem(Nodo);
        int hashFunction(int);
        void displayHash();
        void getTopPorts(int n);
        void displayTopPorts();

};

//funcion para verificar si es primo
bool HashTable::checkPrime(int n){
    if(n == 1 || n == 0)
        return false;

    int sqr_root = sqrt(n);
    for (int i = 2; i <= sqr_root; i++){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

//funcion para obtener el numero primo mas cercano
int HashTable::getPrime(int n){
    if (n % 2 == 0)
        n++;
    while (!checkPrime(n)){
        n += 2;
    }
    return n;
}

//funcion para obtener el indice de la tabla
int HashTable::hashFunction(int key){
    return (key % capacity);
}

//funcion para insertar en la tabla
void HashTable::insertItem(Nodo data) {
    int index = hashFunction(data.port);
    
    // Si la lista en el índice no está vacía
    if (!table1[index].empty()) {
        // Si el puerto ya existe en ese índice
        if (table1[index].back().port == data.port) {
            // Agrega el renglón a la lista de renglones y aumenta el acumulador
            table1[index].back().renglones.push_back(data.renglones[0]);
            table1[index].back().acum++;
            return;  // Salir de la función después de la inserción exitosa
        }
    }

    // Si el puerto no existe en ese índice, simplemente agrega el nuevo Nodo
    table1[index].push_back(data);
}

//funcion para mostrar la tabla
void HashTable::displayHash(){
    for(int i = 0; i < capacity; i++){
        cout << i <<  "--> ";
        for (auto x : table1[i]){
            cout << " --> " << x.port << " --> " << x.acum << " --> ";
            int tamaño = x.renglones.size();
            for (int j = 0; j < tamaño; j++){
                cout << x.renglones[j] << " --> ";
            }
        }
        cout << endl;
    
    }
        
} 

void HashTable::getTopPorts(int n) {
    topPorts.clear();  // Limpiar el vector antes de almacenar nuevos nodos
    
    for (int i = 0; i < capacity; i++) {
        for (const auto& node : table1[i]) {
            topPorts.push_back(node);
        }
    }

    // Ordenar el vector en función del acumulador de forma descendente
    sort(topPorts.begin(), topPorts.end(), [](const auto& a, const auto& b) {
        return a.acum > b.acum;
    });

    // Conservar solo los primeros N nodos con mayor acumulador
    topPorts.resize(min(n, static_cast<int>(topPorts.size())));
}

void HashTable::displayTopPorts() {
    cout << "\nTop 5 Puertos mas repetidos:\n";
    for (const auto& node : topPorts) {
        cout << "Puerto: " << node.port << ", Acum: " << node.acum << ", Renglones: ";
        for (const auto& renglon : node.renglones) {
            cout << renglon << " ";
        }
        cout << endl;
    }
}

int main(){
    vector<ParrafoYPuerto> ParrafoYPuertoVector;
    int counts = 0;
    string bitacore = "bitacora.txt";
    GetLinesAndPortFromTxT(bitacore, counts, ParrafoYPuertoVector);

    cout << "Numero de renglones: " << counts << endl;
    int size = counts/5;
    cout << "Tamaño de la tabla: " << size << endl;
    HashTable Hc(size); 

    for (int i = 0; i < counts; i++){ // Inserting elements into Hash Table1
        Nodo temp;
        temp.port = ParrafoYPuertoVector[i].port;
        temp.renglones.push_back(ParrafoYPuertoVector[i].texto);
        Hc.insertItem(temp);
    
    }
    //Hc.displayHash();
    //the complexity of the hash table is O(1) because it is a direct access structure



    // Obtener y mostrar los 5 nodos con el acumulador más grande
    Hc.getTopPorts(5);
    Hc.displayTopPorts();

    return 0;
}