#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>

using namespace std;

struct Node // se crea la estructura tipo NODO
{
    long long int id; // numero que tendra cada nodo
    string texto;
    Node *ant; // punterio al nodo anterior
    Node *sig; // puntero al nodo siguiente
};

class ListaDoble
{ // se declaran las variables de la clase Lista doblemente ligada
private:
    Node *I, *F, *T, *N; // I es el nodo inicial, F es el nodo final, T es el nodo temporal y N es el nodo auxiliar

public:
    ListaDoble() : I(NULL) {}                // se inicializa el nodo inicial en NULL
    void create(string, long long int);      // se declaran las funciones de la clase
    void read(long long int, long long int); // se declaran las funciones de la clase
    void presentar_I();                      // presentar de inicio a final
    void presentar_F();                      // presentar de final a inicio
};

void ListaDoble::create(string txt, long long int x)
{
    T = new Node(); // Se declara T apuntando al nuevo nodo, dandole el valor que se quiere crear
    T->id = x;      // se le asigna el valor al nodo de id que es equivalente al numero de la ip en la bitacora
    T->texto = txt; // se le asigna el valor al nodo de texto que es equivalente al renglon de la linea en la bitacora
    T->sig = NULL;  // apunta a NULL porque aun no se coloca
    T->ant = NULL;  // apunta a NULL porque aun no se coloca (unicamente para verificar que no apunte a otra cosa!)

    if (I == NULL)
    {          // Si en el nodo inicial no hay nada
        I = T; // Los apuntadores inicial y final apuntan al nuevo nodo
        F = T;
    }
    else if (I->id > T->id)
    {               // Si el valor del nodo inicial es mayor al nuevo
        I->ant = T; // El apuntador de anterior del nodo inicial apunta al nuevo nodo
        T->sig = I; // El nuevo nodo apunta al Nodo inicial con el apuntador siguiente
        I = T;      // El nuevo nodo se vuelve el nodo inicial
    }
    else if (T->id > F->id)
    {               // si el valor del nodo final es menor al nuevo
        F->sig = T; // El puntero siguiente del nodo final apunta al nuevo nodo
        T->ant = F; // El puntero anterior del nuevo nodo apunta al nodo final
        F = T;      // El nuevo nodo se vuelve el final
    }
    else if (T->id > I->id && T->id < F->id)
    {          // Si el nuevo nodo es mayor al nodo inicial pero menor al final
        N = I; // Nodo N obtiene el valor del primer nodo
        while (N->id < T->id)
        { // se revisa de nodo en nodo hasta que el valor del nuevo nodo sea mas grande
            N = N->sig;
        }
        T->ant = N->ant; // Se reorganizan los apuntadores de los nodos anterior y siguiente de la localizacion a donde se quiere colocar
        T->sig = N;
        N->ant = T;
        N = T->ant;
        N->sig = T;
    }
}

void ListaDoble::read(long long int x, long long int y)
{
    ofstream archivo8("busquedaEnBitacora.txt");
    T = I; // El nodo es igual al primero
    cout << "BUSQUEDA:" << endl;
    if (I == NULL)
    { // si el primer nodo esta vacio
        cout << "Lista vacia" << endl;
    }
    while (T != NULL && T->id < x)
    { // Avanza de uno en uno hasta encontrar un valor igual o null al buscado
        T = T->sig;
    }
    if (T == NULL)
    { // si el valor encontrado termino siendo null
        cout << "Dato no encontrado" << endl;
        return;
    }
    else
    {
        while (T != NULL && T->id <= y)
        {
            cout << T->texto << endl;
            T = T->sig;
            archivo8 << T->texto << endl;
        }
    }
}

void ListaDoble::presentar_I()
{
    ofstream archivo4("nuevaBitacora.txt");
    T = I;
    while (T != NULL)
    { // Mientras el nodo no sea null se reproduciran todos los nodos de la lista desde el inicio
        cout << "Valor: " << T->texto << endl;
        archivo4 << T->texto << endl;
        T = T->sig;
    }
}

void ListaDoble::presentar_F()
{
    T = F;
    while (T != NULL)
    { // Mientras el nodo no sea null se reproduciran todos los nodos de la lista desde el final
        cout << "Valor: " << T->texto << endl;
        T = T->ant;
    }
}

long long int StringToLongInt(string input)
{
    stringstream sd(input);
    string segment;
    vector<int> ip_parts;
    while (getline(sd, segment, '.'))
    {
        ip_parts.push_back(stoi(segment));
    }
    long long int octeto1 = ip_parts[0];
    long long int octeto2 = ip_parts[1];
    long long int octeto3 = ip_parts[2];
    long long int octeto4 = ip_parts[3];
    long long int NumIP = (100000000 * octeto1) + (1000000 * octeto2) + (1000 * octeto3) + octeto4;
    return NumIP;
}

int main()
{
    vector<string> ipInicial;
    string ipFinal;
    // abrimos el archivo bitacoraCorta.txt
    ListaDoble Lista;
    Node *A;
    ifstream bitacora("bitacora.txt");

    if (!bitacora.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    std::string texto;
    std::regex ipRegex("\\b(?:[0-9]{1,3}\\.){3}[0-9]{1,3}\\b"); // como funciona esto de regex?
    string linea;

    while (getline(bitacora, texto))
    { // se lee linea por linea el archivo
        smatch match;
        linea = texto;

        while (regex_search(texto, match, ipRegex))
        { // se busca la ip en la linea
            // cout << "IP encontrada: " << match[0] << endl;
            string ip_str = match[0];

            long long int NumIP = StringToLongInt(ip_str);
            Lista.create(linea, NumIP);
            texto = match.suffix();
        }
    }
    bitacora.close();
    cout << "Presentar por el Inicio" << endl;
    Lista.presentar_I();
    string input;
    cout << "Ingrese una direccion IP en el formato xxx.xxx.xxx.xxx: ";
    cin >> input;
    long long int Inicio = StringToLongInt(input);

    cout << "Ingrese una direccion IP en el formato xxx.xxx.xxx.xxx: ";
    cin >> input;
    long long int Final = StringToLongInt(input);

    Lista.read(Inicio, Final);

    return 0;
}
