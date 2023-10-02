#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


struct Node //se crea la estructura tipo NODO
{
    int id; //numero que tendra cada nodo
    Node *ant; //punterio al nodo anterior
    Node *sig; //puntero al nodo siguiente
};

class ListaDoble{ //se declaran las variables de la clase Lista doblemente ligada
private:
Node *I,*F,*T,*N;

public:
    ListaDoble(): I(NULL){}
    void create(int);
    Node* read(int);
    void update(int, int);
    void del(int);
    void presentar_I();
    void presentar_F();
};

void ListaDoble::create(int x){
    T=new Node(); //Se declara T apuntando al nuevo nodo, dandole el valor que se quiere crear
    T->id=x;
    T->sig=NULL; //apunta a NULL porque aun no se coloca
    T->ant=NULL;

    if(I==NULL){ //Si en el nodo inicial no hay nada
        I=T; //Los apuntadores inicial y final apuntan al nuevo nodo
        F=T;
    } else if(I->id>T->id){ //Si el valor del nodo inicial es mayor al nuevo
        I->ant = T; //El apuntador de anterior del nodo inicial apunta al nuevo nodo
        T->sig = I; //El nuevo nodo apunta al Nodo inicial con el apuntador siguiente
        I = T; //El nuevo nodo se vuelve el nodo inicial
    } else if(T->id>F->id){ //si el valor del nodo final es menor al nuevo
        F->sig = T; //El puntero siguiente del nodo final apunta al nuevo nodo
        T->ant = F; //El puntero anterior del nuevo nodo apunta al nodo final
        F = T; //El nuevo nodo se vuelve el final
    } else if(T->id>I->id && T->id<F->id){ //Si el nuevo nodo es mayor al nodo inicial pero menor al final
        N=I; //Nodo N obtiene el valor del primer nodo
        while (N->id < T->id){ //se revisa de nodo en nodo hasta que el valor del nuevo nodo sea mas grande
            N = N->sig;
        }
        T->ant = N->ant; //Se reorganizan los apuntadores de los nodos anterior y siguiente de la localizacion a donde se quiere colocar
        T->sig = N;
        N->ant = T;
        N = T->ant;
        N->sig = T;
    }
}

Node* ListaDoble::read(int x){
    T=I; //El nodo es igual al primero

    if(I==NULL){ //si el primer nodo esta vacio
        cout<<"Lista vacia"<<endl;
    }
    while (T != NULL && T->id != x){ //Avanza de uno en uno hasta encontrar un valor igual o null al buscado
        T = T->sig;
    }
    
    if(T == NULL){ //si el valor encontrado termino siendo null
        cout<<"Dato no encontrado"<<endl;
    }
    return T;
}

void ListaDoble::del(int busq){
    T=read(busq); //Se busca el nodo a encontrar

    if (T == NULL){ //Si no se encontro el nodo
        cout<<"No se pudo completar la operacion"<<endl;
        return;
    }
    N = T->ant; //Reajusta las conexiones para que la lista siga funcionando
    N->sig = T->sig;
    N = T->sig;
    N->ant = T->ant;
    delete T; //Se borra el nodo
}

void ListaDoble::update(int x, int mod){ 
    del(x); //Como se quiere hacer una lista ordenada es mas sencillo borrar el nodo y volverlo a poner
    create(mod);
}

void ListaDoble::presentar_I(){
    T=I;
    while (T!=NULL){ //Mientras el nodo no sea null se reproduciran todos los nodos de la lista desde el inicio
        cout<<"Valor: "<<T->id<<endl;
        T=T->sig;
    }
}

void ListaDoble::presentar_F(){
    T=F;
    while (T!=NULL){ //Mientras el nodo no sea null se reproduciran todos los nodos de la lista desde el final
        cout<<"Valor: "<<T->id<<endl;
        T=T->ant;
    }
}

void obtenerIpDeBitacora(vector<string> &ip, string nombreArchivo){
    string linea;
    string ipTemporal;
    ifstream archivo(nombreArchivo);

    struct ipTemporals
    {
        string ip;
        int cantidad;
    };
    

    if (archivo.is_open()){
        while (getline(archivo, linea)){
            //la ip es el Sep 6 02:02:51 767.40.790.72:6336 Failed password for root the ip in this is 767.40.790.72 
            ipTemporal = linea.substr(15, 17);
            ip.push_back(ipTemporal);
        }
        archivo.close();
    }
    else{
        cout << "No se pudo abrir el archivo" << endl;
    }
}


int main(){
    
    string nombreArchivo = "bitacoraCorta.txt";
    vector<string> ip;
    obtenerIpDeBitacora(ip, nombreArchivo);
    for (int i = 0; i < 20; i++){
        cout << ip[i] << endl;
    }

    /*
    ListaDoble Lista;
    Node *A;
    for (int i = 1; i < 10; i++){
        Lista.create(i*10);
    }
    Lista.create(1);
    Lista.create(100);
    Lista.create(55);
    cout<<"Presentar por el Inicio"<<endl;
    Lista.presentar_I();
    cout<<"Presentar por el Final"<<endl;
    Lista.presentar_F();
    A = Lista.read(50);
    cout<<A->id<<endl;
    Lista.del(50);
    cout<<"Presentar Lista con el dato 50 eliminado"<<endl;
    Lista.presentar_F();
    Lista.update(30,35);
    cout<<"Presentar Lista con el valor 30 cambiado a 30"<<endl;
    Lista.presentar_F(); */
    return 0;
}
