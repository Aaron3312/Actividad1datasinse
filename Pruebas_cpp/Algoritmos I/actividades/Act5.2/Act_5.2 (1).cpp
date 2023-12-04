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
    Nodo(){port = -1; acum = 0; }
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
void HashTable::insertItem(Nodo data){
    int index = hashFunction(data.port);
    if (table1[index].empty() == false){
        ++cAcum;
    }
    //si el puerto ya existe en ese indice se agrega el renglon a la lista de renglones y se aumenta el acumulador
    if (table1[index].back().port == data.port && table1[index].empty() == false){
        table1[index].back().renglones.push_back(data.renglones[0]);
        table1[index].back().acum++;
    } else{
        table1[index].push_back(data);
    }
}

//funcion para mostrar la tabla
void HashTable::displayHash(){
    for(int i = 0; i < capacity; i++){
        cout << i;
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

int main(){
    vector<ParrafoYPuerto> ParrafoYPuertoVector;
    int counts = 0;
    string bitacore = "bitacora.txt";
    GetLinesAndPortFromTxT(bitacore, counts, ParrafoYPuertoVector);

    int size = counts;

    HashTable Hc(size); 

    for (int i = 0; i < size; i++){ // Inserting elements into Hash Table1
        Nodo temp;
        temp.port = ParrafoYPuertoVector[i].port;
        temp.renglones.push_back(ParrafoYPuertoVector[i].texto);
        Hc.insertItem(temp);
    
    }
    Hc.displayHash();
    //the complexity of the hash table is O(1) because it is a direct access structure
    return 0;
}