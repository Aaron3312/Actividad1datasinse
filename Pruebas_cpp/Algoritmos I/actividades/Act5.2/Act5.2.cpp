//Act 5.1- Individual implementation of operations on 
//Aaron Hernandez Jimenez A01642529
//Individually, create a Hash table class with the variables table size, fixed-size lists or int array (as applicable).
//You must propose a hash function (that avoids collisions as best as possible) using chaining (list array) and an open address collision resolution: quadratic probing (int array). 

//Test each test case for each collision resolution method through the insert() function.

//• Insert ()
//Input: Integer value
//Inserts the element at the calculated position (hash value)
//Print the total number of collisions in each test case.

#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <fstream>
#include <regex>
#include <vector>
#include <sstream>



using namespace std;
struct Entra
{
    vector<int> numeros;
    string texto;
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
            // printf("IPINVECTOR: %d.%d.%d.%d\n", ParrafoYPuertoVector[counts].numeros[0], ParrafoYPuertoVector[counts].numeros[1], ParrafoYPuertoVector[counts].numeros[2], ParrafoYPuertoVector[counts].numeros[3]);

            texto = match.suffix();
            counts++;
            // cout << "counts: " << counts << endl;
        }
    }
    bitacora.close();
}


// Hash table implementation in C++
class HashTable{
    private:
        int capacity;
        int qAcum = 0, cAcum = 0;
        list<int> *table1;
        vector<int*> table2;
    public: //constructor
        HashTable(int V){
            int size = getPrime(V);
            this->capacity = size;
            table1 = new list<int>[capacity];
            table2.resize(capacity, nullptr);
        }
        ~HashTable(){ //destructor
            delete []table1;
            for (int i = 0; i < capacity; ++i) {
            if (table2[i] != nullptr) {
                delete table2[i];
            }
        }
            cout<<"\nDestructor: HashTable deleted.\n";
        } //end destructor
        bool checkPrime(int);
        int getPrime(int);

        void insertItem(int);
        int hashFunction(int);
        int qHashFunction(int, int);
        void quadratic(int);
        void displayHash(int);
};
 //end class

 //function to check prime number
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

//function to return prime number
int HashTable::getPrime(int n){
    if (n % 2 == 0)
        n++;
    while (!checkPrime(n)){
        n += 2;
    }
    return n;
}

//  function to calculate index in hash table
int HashTable::hashFunction(int key){
    return (key % capacity);
}
//  function to calculate index in hash table
int HashTable::qHashFunction(int key, int i){
    return ((key + i*i) % capacity);
}
//  function to insert key into hash table
void HashTable::insertItem(int data){
    int index = hashFunction(data);
    if (table1[index].empty() == false){
        ++cAcum;
    }
    table1[index].push_back(data);
}
//  function to display hash table
void HashTable::quadratic(int data) {
    int index = qHashFunction(data, 0);
    int i = 1;
    while (table2[index] != nullptr) {
        index = qHashFunction(data, i);
        if (i == 1){
            qAcum++;
        }
        i++;
    }
    table2[index] = new int(data);
}

//  function to display hash table
void HashTable::displayHash(int op){
if (op == 1){
    for(int i = 0; i < capacity; i++){
        cout << "table1["<<i<<"]";
        for (auto x : table1[i])
            cout << " --> "<<x;
        cout << endl;        
    }
    cout <<"Numero de colisiones: "<<cAcum<< endl;  
} else{
    for(int i = 0; i < capacity; i++){
            cout << "table2["<<i<<"]"<<" --> ";
        if (table2[i] != nullptr) {
            cout << *table2[i]<< endl;
        } else {
            cout << "nullptr "<< endl;
        }
    }
    cout <<"Numero de colisiones: "<<qAcum<< endl;  
    cout << endl;
}       
}

// Driver program
int main(){
    //metemos datos al azar
    // declaramos el vector de ParrafoYPuertoVector y counts
    vector<Entra> ParrafoYPuertoVector;
    int counts = 0;                                                  // numero de lineas del archivo
    string bitacore = "bitacora.txt";                                // nombre del archivo de lectura, normalmente usamos bitacoraCorta.txt para pruebas
    GetLinesAndIntFromIpTXT(bitacore, counts, ParrafoYPuertoVector); 

    int size = counts;
    int data[size];
    for (int i = 0; i < size; i++){
        data[i] = ParrafoYPuertoVector[i].numeros[0];
    }
    
    HashTable Hq(size); // Create a HashTable of size 7
    HashTable Hc(size); 

    for (int i = 0; i < size; i++){ // Inserting elements into Hash Table1
        Hc.insertItem(data[i]);
    }
    for (int i = 0; i < size; i++){
        Hq.quadratic(data[i]);
    }
    Hq.displayHash(2);
    Hc.displayHash(1);
    //the complexity of the hash table is O(1) because it is a direct access structure
    return 0;
}