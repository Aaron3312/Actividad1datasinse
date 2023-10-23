// Name: Aaron Hernandez Jimenez - A01642529
// Date: 16-10-2023
// Act 3.2 - Árbol Heap: Implementando una fila priorizada
// Instrucciones:
/*Realiza en forma individual una clase en C++ llamada "priority_queue" que tenga
las siguientes operaciones utilizando un heap y simulando una fila priorizada de
enteros con prioridad de valor mayor.

Todas las funcionalidades deberán de estar correctamente alineadas y documentadas.
Como parte de la docuementación deberá incluirse la complejidad de cada una de ellas.
*/

#include <iostream>
#include <vector>

using namespace std;

// Clase priority_queue declarada como template
class priority_queue
{
private:
    vector<int> vect;
    int index;

public:
    priority_queue();
    ~priority_queue();
    void heapify(vector<int> &, int);
    int Top();
    bool Empty();
    void DeleteAll();
    void Pop();
    void Push(int);
    int Size();
};

// Constructor por default para inicializar el vector y el index
priority_queue::priority_queue()
{
    vect = {};
    index = 0;
}

// Destructor para eliminar todos los elementos del vector
priority_queue::~priority_queue()
{
    DeleteAll();
}

// Funcion Heapify para ordenar el vector y mantener la propiedad de heap
// en el peor de los casos recorre todo por lo que es O(n)
void priority_queue::heapify(vector<int> &heepTree, int index)
{
    int size = heepTree.size();
    int largest = index;
    int l = 2 * index + 1;
    int r = 2 * index + 2;

    if (l < size && heepTree[l] > heepTree[largest])
        largest = l;
    if (r < size && heepTree[r] > heepTree[largest])
        largest = r;
    if (largest != index)
    {
        swap(heepTree[index], heepTree[largest]);
        heapify(heepTree, largest);
    }
}
// Funcion Swap para intercambiar los valores de dos variables
// es como una extension de la funcion heapify por lo que es O(1)

void swap(int &a, int &b)
{
    // unicamente cambia los valores, es interesante recordar el hecho del amperson para el paso por referencia
    int temp = a;
    a = b;
    b = temp;
}

//Funcion Push para insertar un dato en el vector y mantener la propiedad de heap de 
//La función coloca el nuevo valor al final del vector y a partir de ahí 
//empieza a subir por el nuevo valor y aplicándole Heapify si es necesario, 
//pero como no vuelve a recorrer todo el vector es O(log n)

void priority_queue::Push(int data)
{
    vect.push_back(data);
    int index = vect.size() - 1;
    int parent = (index - 1) / 2;
    while (index > 0 && vect[parent] < vect[index])
    {
        swap(vect[index], vect[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// Función Pop para eliminar el dato con mayor prioridad del vector y mantener la propiedad de heap de maximos
// su complejidad es O(n) ya que en el peor de los casos recorre todo el vector
void priority_queue::Pop()
{
    int size = vect.size();
    if (size == 0)
    {
        cout << "El vector esta vacio" << endl;
        return;
    }
    vect[0] = vect[size - 1];
    vect.pop_back();
    heapify(vect, 0);
}

// Función Top para obtener el dato con mayor prioridad del vector y mantener la propiedad de heap de maximos
// su complejidad es O(1) ya que unicamente regresa el primer elemento del vector
int priority_queue::Top()
{
    if (vect.size() != 0)
    {
        return vect[0];
    }
    cout << "El vector esta vacio ";
    return -1;
}

// Función Empty para verificar si el vector esta vacio o no, en caso de estar vacio regresa true, en caso contrario regresa false
// su complejidad es O(1) ya que unicamente verifica si el tamaño del vector es 0
bool priority_queue::Empty()
{
    if (vect.size() == 0)
        return true;
    else
        return false;
}

// Función Size para obtener el tamaño del vector y regresarlo como un entero
// su complejidad es O(1) ya que unicamente regresa el tamaño del vector
int priority_queue::Size()
{
    return vect.size();
}

// Funcion DelleteAll para eliminar todos los elementos del vector
// su complejidad es O(1) ya que unicamente elimina todos los elementos del vector
void priority_queue::DeleteAll()
{
    vect.clear();
}

// Funcion main para probar las funciones de la clase priority_queue, con los 4 casos de prueba solicitados
int main()
{
    //generamos 4 casos de prueba para verificar el funcionamiento de la clase priority_queue necesarios para en cada uno probar una funcion
    priority_queue pq;
    cout << "Caso de prueba 1: " << endl;
    cout << "El vector esta vacio? " << pq.Empty() << endl;
    cout << "El tamano del vector es: " << pq.Size() << endl;
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl;
    cout << "Eliminando el elemento con mayor prioridad: " << endl;
    pq.Pop();
    cout << "Eliminando todos los elementos del vector: " << endl;
    pq.DeleteAll();
    cout << "El vector esta vacio? " << pq.Empty() << endl;
    cout << "El tamano del vector es: " << pq.Size() << endl;
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl << endl;


    cout << "Caso de prueba 2: " << endl;
    pq.Push(1);
    pq.Push(2);
    pq.Push(3);
    pq.Push(4);
    pq.Push(5);
    pq.Push(6);
    pq.Push(7);
    pq.Push(8);
    pq.Push(9);
    pq.Push(10);
    cout << "El vector esta vacio? " << pq.Empty() << endl;
    cout << "El tamano del vector es: " << pq.Size() << endl;
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl;
    cout << "Eliminando el elemento con mayor prioridad: " << endl;
    pq.Pop();
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl;
    cout << "Eliminando todos los elementos del vector: " << endl;
    pq.DeleteAll();
    cout << "El vector esta vacio? " << pq.Empty() << endl;
    cout << "El tamano del vector es: " << pq.Size() << endl;
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl << endl;


    cout << "Caso de prueba 3: " << endl;
    pq.Push(10);
    pq.Push(9);
    pq.Push(8);
    pq.Push(7);
    pq.Push(6);
    pq.Push(5);
    pq.Push(4);
    pq.Push(3);
    pq.Push(2);
    pq.Push(1);
    cout << "El vector esta vacio? " << pq.Empty() << endl;
    cout << "El tamano del vector es: " << pq.Size() << endl;
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl;
    cout << "Eliminando el elemento con mayor prioridad: " << endl;
    pq.Pop();
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl;
    cout << "Eliminando todos los elementos del vector: " << endl;
    pq.DeleteAll();
    cout << "El vector esta vacio? " << pq.Empty() << endl;
    cout << "El tamano del vector es: " << pq.Size() << endl;
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl << endl;


    cout << "Caso de prueba 4: " << endl;
    pq.Push(1);
    pq.Push(3);
    pq.Push(5);
    pq.Push(7);
    pq.Push(9);
    pq.Push(10);
    pq.Push(8);
    pq.Push(6);
    pq.Push(4);
    pq.Push(2);
    cout << "El vector esta vacio? " << pq.Empty() << endl;
    cout << "El tamano del vector es: " << pq.Size() << endl;
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl;
    cout << "Eliminando el elemento con mayor prioridad: " << endl;
    pq.Pop();
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl;
    cout << "Eliminando todos los elementos del vector: " << endl;
    pq.DeleteAll();
    cout << "El vector esta vacio? " << pq.Empty() << endl;
    cout << "El tamano del vector es: " << pq.Size() << endl;
    cout << "El elemento con mayor prioridad es: " << pq.Top() << endl << endl;



    return 0;
}
