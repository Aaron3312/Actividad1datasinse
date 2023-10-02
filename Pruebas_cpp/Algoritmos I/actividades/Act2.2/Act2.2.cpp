// Name: Aaron Hernandez Jimenez - A01642529
// Date: 01-10-2023
// Act 2.2 - Verificación de las funcionalidades de una estructura de datos lineal (cola de prioridad)
// Instrucciones:
//En forma individual verifica la pertinencia de una estructura de datos en cuanto al seguimiento de la especificación de la interfaz para 
//una Cola de prioridad, una estructura de datos lineal: 

//Dependiendo la estructura de datos lineal deberán crear las operaciones CRUD (Create, Read (buscar), Update, Delete) elementos en la
// estructura de datos. Algunas operaciones no aplican para ciertas estructura de datos 

#include <iostream>

using namespace std;

struct Node //se crea la estructura tipo NODO
{
    int id; //numero que tendra cada nodo
    int priority; //prioridad cada nodo
};

class PriorQueue{ //se declaran las variables y funciones de la clase Lista doblemente ligada
private:
    Node *PQ;
    int N, NumNodes, valor, prior, coord;
public:
    PriorQueue(int size){
        N=size;
        PQ = new Node[size];
        NumNodes = -1;
    }
    ~PriorQueue(){
        delete[] PQ;
    }

    void Enqueue(int, int);
    Node *Dequeue();
    Node *Dequeue(int);
    int Peek();
    void Display(int);
    void Display();
    void Update(int,int,int);
};

void PriorQueue::Enqueue(int x, int prioridad){
    if (NumNodes == N-1){ //Si la cantidad de nodos es igual a la cantidad maxima
        cout << "Cola llena" << endl;
        return;
    }
    NumNodes++; //Se agrega uno a la cantidad de nodos

    PQ[NumNodes].id = x; //se le dan los valores al nuevo nodo
    PQ[NumNodes].priority = prioridad;
}

void PriorQueue::Display(int idx){ //imprimir los datos de un nodo especifico
    cout << PQ[idx].id;
    cout << "(" << PQ[idx].priority <<")\n\n";
}
void PriorQueue::Display(){ //imprimir los datos de todos los nodos
    cout << "Elements: ";
    for (int i = 0; i <= NumNodes; i++){
        cout << PQ[i].id;
        cout << "(" << PQ[i].priority <<")  ";
    }
    cout<<endl<<endl;
}

int PriorQueue::Peek(){
    if (NumNodes == -1){ //Si la cantidad de nodos es 0 cola vacia
        cout<<"Cola vacia"<<endl;
        return -1;
    }
    valor = PQ[0].id; //se guardan los valores dep primer nodo
    prior = PQ[0].priority;
    for (int i = 0; i <= NumNodes; i++){ //se recorren todos los nodos
        if (PQ[i].priority == prior){ //si la prioridad es igual
            if (valor < PQ[i].id){ //se checa cuan valor es mayor
                valor = PQ[i].id;//se guarda el nuevo valor y la coordenada
                coord = i;
            }
        }
        else if (PQ[i].priority > prior){//si la prioridad es mayor
            prior = PQ[i].priority;//se guardan todos los datos
            valor = PQ[i].id;
            coord = i;
        }
    }
    return coord;
}

Node *PriorQueue::Dequeue(){
    if (NumNodes == -1){//Si la cantidad de nodos es 0 cola vacia
        cout<<"Cola vacia"<<endl;
        return NULL;
    }
    Node *Aux;
    valor = PQ[0].id; //se guardan los valores dep primer nodo
    prior = PQ[0].priority;
    for (int i = 0; i <= NumNodes; i++){ //Se repiten los pasos de la funcoon anterior para obtener los datos buscados
        if (PQ[i].priority == prior){
            if (valor < PQ[i].id){
                valor = PQ[i].id;
            }
        }
        else if (PQ[i].priority > prior){
            prior = PQ[i].priority;
            valor = PQ[i].id;
        }
    }
    Aux = &PQ[NumNodes]; //Se guarda la direccion del ultimo nodo disponible
    if (coord =! NumNodes){ //Si el nodo obtenido no es el ultimo
        for (int i = coord; i <= NumNodes-1; i++){//recorre los nodos a partir de nodo obtenido hacia atras
            PQ[i] = PQ[i+1];
        }
    }
    PQ[NumNodes].id = valor;//se cambian los datos del ultimo nodo (ahora repetido) a los datos del obtenido
    PQ[NumNodes].priority = prior;
    NumNodes -= 1; //se recorre el limite de nodos, excluyendo el ultimo
    cout<<"Valor eliminado: "<< Aux->id<<" ("<<Aux->priority<<")"<<endl;
    return Aux;
}
Node *PriorQueue::Dequeue(int indx){
    if (NumNodes == -1){//Si la cantidad de nodos es 0 cola vacia
        cout<<"Cola vacia"<<endl;
        return NULL;
    }
    Node *Aux = &PQ[NumNodes];//Se guarda la direccion del ultimo nodo disponible
    valor = PQ[indx].id; //Se guardan los datos del nodo obtenido
    prior = PQ[indx].priority;
    if (indx =! NumNodes){//Si el nodo obtenido no es el ultimo
        for (int i = indx; i <= NumNodes-1; i++){//recorre los nodos a partir de nodo obtenido hacia atras
            PQ[i] = PQ[i+1];
        }
    }
    PQ[NumNodes].id = valor;//se cambian los datos del ultimo nodo (ahora repetido) a los datos del obtenido
    PQ[NumNodes].priority = prior;
    NumNodes -= 1;//se recorre el limite de nodos, excluyendo el ultimo
    cout<<"Valor eliminado: "<< Aux->id<<" ("<<Aux->priority<<")"<<endl;
    return Aux;
}

void PriorQueue::Update(int indx, int v, int p){
    if (NumNodes == -1){//Si la lista esta vacia
        cout<<"Cola vacia"<<endl;
        return;
    } else if (indx > NumNodes){ //si el nodo buscado supera al numero de nodos
        cout<<"Dato no valido"<<endl;
        return;
    }
    PQ[indx].id = v; //se cambian los valores respectivamente
    PQ[indx].priority = p;
}

int main(){
    PriorQueue P(5);
    Node *Ejem;

    P.Enqueue(3,1);
    P.Enqueue(4,2);
    P.Enqueue(5,1);
    P.Enqueue(6,1);
    P.Enqueue(7,1);
    P.Display();

    int indx = P.Peek();
    P.Display(indx);

    Ejem = P.Dequeue();
    cout<<Ejem->id<<endl;
    P.Display();

    P.Update(3,9,4);
    P.Display();
    Ejem = P.Dequeue();
    P.Display();
}