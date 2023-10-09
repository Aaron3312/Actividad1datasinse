// Name: Aaron Hernandez Jimenez - A01642529
// Date: 01-10-2023
// Act 2.2 - Verificación de las funcionalidades de una estructura de datos lineal (cola de prioridad)
// Instrucciones:
// En forma individual verifica la pertinencia de una estructura de datos en cuanto al seguimiento de la especificación de la interfaz para
// una Cola de prioridad, una estructura de datos lineal:

// Dependiendo la estructura de datos lineal deberán crear las operaciones CRUD (Create, Read (buscar), Update, Delete) elementos en la
//  estructura de datos. Algunas operaciones no aplican para ciertas estructura de datos

#include <iostream>

using namespace std;

struct Nodo //se crea la estructura tipo NODO
{
    int id;
    int priority;
};

class PriorQueue //se declara la clase PriorQueue
{ 
private:
    Nodo *PQ;
    int Id, Prioridad, Cord, Size, NumeroNodes;

public: //se declaran las funciones de la clase
    PriorQueue(int size)
    {
        Size = size;
        PQ = new Nodo[size];
        NumeroNodes = -1;
    }
    ~PriorQueue()
    {
        delete[] PQ;
    }

    void Enqueue(int, int);
    Nodo *Dequeue();
    Nodo *Dequeue(int);
    int Peek();
    void Display(int);
    void Display();
    void Update(int, int, int);
};

void PriorQueue::Enqueue(int x, int prioridad) //se declara la funcion Enqueue
{
    if (NumeroNodes == Size - 1)
    { 
        cout << "Cola llena" << endl; //si la cola esta llena
        return;
    }
    NumeroNodes++;

    PQ[NumeroNodes].id = x; //se le asigna el valor al nodo de id que es equivalente al numero de la ip en la bitacora
    PQ[NumeroNodes].priority = prioridad; //se le asigna el valor al nodo de prioridad que es equivalente al numero de la ip en la bitacora
}

void PriorQueue::Display(int idx) //se declara la funcion Display
{ 
    cout << PQ[idx].id; //se imprime el valor del nodo
    cout << "(" << PQ[idx].priority << ")\n\n"; //se imprime el valor del nodo
}
void PriorQueue::Display() //se declara la funcion Display
{ 
    cout << "Elementos: ";
    for (int i = 0; i <= NumeroNodes; i++) //se imprime el valor del nodo
    {
        cout << PQ[i].id;
        cout << "(" << PQ[i].priority << ")  ";
    }
    cout << endl
         << endl;
}

int PriorQueue::Peek() //se declara la funcion Peek
{
    if (NumeroNodes == -1)
    { 
        cout << "Empty list" << endl; //si la cola esta vacia
        return -1;
    }
    Id = PQ[0].id; 
    Prioridad = PQ[0].priority;
    for (int i = 0; i <= NumeroNodes; i++) //se revisa de nodo en nodo hasta que el valor del nuevo nodo sea mas grande
    { 
        if (PQ[i].priority == Prioridad) //si el valor del nodo inicial es mayor al nuevo
        {
            if (Id < PQ[i].id)
            {                    
                Id = PQ[i].id;
                Cord = i;
            }
        }
        else if (PQ[i].priority > Prioridad) //si el valor del nodo final es menor al nuevo
        {                           
            Prioridad = PQ[i].priority; 
            Id = PQ[i].id;
            Cord = i;
        }
    }
    return Cord;
}

Nodo *PriorQueue::Dequeue() //se declara la funcion Dequeue
{
    if (NumeroNodes == -1)
    { 
        cout << "Cola vacia" << endl;
        return NULL;
    }
    Nodo *Aux;
    Id = PQ[0].id; 
    Prioridad = PQ[0].priority;
    for (int i = 0; i <= NumeroNodes; i++)//se revisa de nodo en nodo hasta que el valor del nuevo nodo sea mas grande
    { 
        if (PQ[i].priority == Prioridad)
        {
            if (Id < PQ[i].id)
            {
                Id = PQ[i].id;
            }
        }
        else if (PQ[i].priority > Prioridad) //si el valor del nodo final es menor al nuevo
        {
            Prioridad = PQ[i].priority;
            Id = PQ[i].id;
        }
    }
    Aux = &PQ[NumeroNodes];
    if (Cord = !NumeroNodes)
    { 
        for (int i = Cord; i <= NumeroNodes - 1; i++)
        { 
            PQ[i] = PQ[i + 1];
        }
    }
    PQ[NumeroNodes].id = Id; 
    PQ[NumeroNodes].priority = Prioridad;
    NumeroNodes -= 1; 
    cout << "Deleted value: " << Aux->id << " (" << Aux->priority << ")" << endl; //se imprime el valor del nodo
    return Aux; //se regresa el valor del nodo
}
Nodo *PriorQueue::Dequeue(int indx) //se declara la funcion Dequeue
{
    if (NumeroNodes == -1)
    { 
        cout << "empty list" << endl;
        return NULL;
    }
    Nodo *Aux = &PQ[NumeroNodes];
    Id = PQ[indx].id;       
    Prioridad = PQ[indx].priority; //se le asigna el valor al nodo de prioridad que es equivalente al numero de la ip en la bitacora
    if (indx = !NumeroNodes)
    { 
        for (int i = indx; i <= NumeroNodes - 1; i++) //se revisa de nodo en nodo hasta que el valor del nuevo nodo sea mas grande
        { 
            PQ[i] = PQ[i + 1];
        }
    }
    PQ[NumeroNodes].id = Id; 
    PQ[NumeroNodes].priority = Prioridad; //se le asigna el valor al nodo de prioridad que es equivalente al numero de la ip en la bitacora
    NumeroNodes -= 1; 
    cout << "Deleted Value: " << Aux->id << " (" << Aux->priority << ")" << endl; //se imprime el valor del nodo
    return Aux;
}

void PriorQueue::Update(int indx, int v, int p) //se declara la funcion Update
{
    if (NumeroNodes == -1) //si la cola esta vacia
    { 
        cout << "Empty list" << endl;
        return;
    }
    else if (indx > NumeroNodes) //si el valor del nodo inicial es mayor al nuevo
    { 
        cout << "Invalid date" << endl;
        return;
    }
    PQ[indx].id = v; 
    PQ[indx].priority = p;
}

int main()
{
    PriorQueue P(5); //se declara la cola de prioridad
    Nodo *Ejem;

    P.Enqueue(4, 1);
    P.Enqueue(7, 2);
    P.Enqueue(5, 4); //se le asigna el valor al nodo de prioridad que es equivalente al numero de la ip en la bitacora
    P.Enqueue(2, 3);
    P.Display();

    int indx = P.Peek(); //se le asigna el valor al nodo de prioridad que es equivalente al numero de la ip en la bitacora
    P.Display(indx);

    Ejem = P.Dequeue(); 
    cout << Ejem->id << endl;
    P.Display();

    P.Update(7, 4, 5); 
    P.Display();
    Ejem = P.Dequeue();
    P.Display();
}