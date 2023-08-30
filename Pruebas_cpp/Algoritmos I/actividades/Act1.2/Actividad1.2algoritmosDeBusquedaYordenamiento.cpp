// Name: Aaron Hernandez Jimenez - A01642529
// Date: 29/08/2023
// Description: Act 1.2 - Algoritmos de Búsqueda y Ordenamiento

// instrucciones:
// Realiza una aplicación en C++ en forma individual,
// en donde dado n numeros de entrada que son almacenados en un vector<int> realice las siguientes funciones de ordenamiento:

// Desde la aplicación deberá solicitar al usuario la cantidad de búsquedas que desea,
//  y por cada búsqueda deberá de solicitar el número que desea buscar y desplegará el índice donde
// se encuentra localizado o -1 en caso de que no se encuentre, la búsqueda deberá realizarla en ambos métodos (secuencial y binario).

// Todas las funcionalidades deberán de estar correctamente alineadas y documentadas.
// Como parte de la documentación deberá incluirse la complejidad de cada una de ellas.

#include <iostream>
#include <ctime>
#include <random>
using namespace std;

// ordenaInserción tiene un complejidad de O(n^2).
// Ordene en forma ascendente los datos con el método de Inserción
void ordenaInsercion(int arr[], int n)
{
    int auxiliar;
    for (int i = 1; i < n; i++)
    {
        auxiliar = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > auxiliar)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = auxiliar;
    }
}

// ordenaBurbuja Tiene una complejidad de O(n^2) porque tiene dos ciclos for anidados
void ordenaBurbuja(int arr[], int n)
{
    int aux; // en vez de utilizar swap() utilizamos una variable auxiliar para hacer el cambio de valores
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }
}

// ordenaMerge Tiene una complejidad de O(n*log(n)).
void ordenaMerge(int arr[], int izq, int derecho)
{
    if (izq < derecho)
    {
        // Encuentra el punto medio del arreglo
        int medio = izq + (derecho - izq) / 2;

        // Ordena la primera mitad y la segunda mitad
        ordenaMerge(arr, izq, medio);
        ordenaMerge(arr, medio + 1, derecho);

        // Combina las mitades ordenadas
        int n1 = medio - izq + 1;
        int n2 = derecho - medio;
        // Crear arreglos temporales
        int leftArray[n1];
        int rightArray[n2];
        // Copiar datos a los arreglos temporales leftArray[] y rightArray[]
        for (int i = 0; i < n1; i++)
        {
            leftArray[i] = arr[izq + i];
        }
        for (int i = 0; i < n2; i++)
        {
            rightArray[i] = arr[medio + 1 + i];
        }
        // Combinar los arreglos temporales
        int i = 0, j = 0, k = izq;
        while (i < n1 && j < n2)
        {
            if (leftArray[i] <= rightArray[j])
            {
                arr[k] = leftArray[i];
                i++;
            }
            else
            {
                arr[k] = rightArray[j];
                j++;
            }
            k++;
        }
        // Copiar los elementos restantes de leftArray[], si los hay
        while (i < n1)
        {
            arr[k] = leftArray[i];
            i++;
            k++;
        }
        // Copiar los elementos restantes de rightArray[], si los hay
        while (j < n2)
        {
            arr[k] = rightArray[j];
            j++;
            k++;
        }
    }
}

// busqSecuencial
// Este es una funcion de busqueda secuencial que busca un numero en el arreglo y regresa el indice donde se encuentra
// arroja -1 en caso de que no se localice el numero.
// Tiene una complejidad de O(n).
void busqSecuencial(int arr[], int dato, int n)
{
    cout << "Busqueda secuencial" << endl;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (arr[i] == dato)
        {
            break;
        }
    }
    if (i == n)
    {
        cout << "-1" << endl;
    }
    else
    {   
        cout << "El numero se encuentra en el indice " << i << endl;
    }
}

// busqBinaria (Iterativo & Recursivo)
// Este es una funcion de busqueda binaria que busca un numero en el arreglo y regresa el indice donde se encuentra
// arroja -1 en caso de que no se localice el numero.
// Tiene una complejidad de O(log(n)).
void busqBinaria(int arr[], int n,int dato)
{
    cout << "Busqueda binaria" << endl;
    //primero el metodo iterativo
    int inicio = 0;
    int fin = n - 1;
    int medio;
    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        if (dato == arr[medio])
        {
            cout << "El numero se encuentra en el indice " << medio << endl;
            break;
        }
        else if (dato < arr[medio])
        {
            fin = medio - 1;
        }
        else
        {
            inicio = medio + 1;
        }
    }
    if (inicio > fin)
    {
        cout << "-1" << endl;
    }
}
    // ahora el metodo recursivo
    // Tiene una complejidad de O(log(n)).
void busqBinariaRE(int arr[], int n,int dato, int izquierd, int derecha)
{

    int medio = (izquierd + derecha) / 2; // calculamos el medio
    if (izquierd <= derecha)
    {
        if (dato == arr[medio])
        {
            cout << "Busqueda binaria recursiva" << endl;
            cout << "El numero se encuentra en el indice " << medio << endl;
        }
        else if (dato < arr[medio])
        {
            derecha = medio - 1;
            busqBinariaRE(arr, n, dato, izquierd, derecha);
        }
        else
        {
            izquierd = medio + 1;
            busqBinariaRE(arr, n, dato, izquierd, derecha);
        }
    }
}

// declaramos una funcion que genere numeros aleatorios
int randoms(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// funcion que reinica el vector a valores iniciales
void reiniciarVector(int arr[], int n, int arregloInicial[])
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = arregloInicial[i];
    }
}

// funcion main generando un vector int de n numeros aleatorios
int main()
{
    cout << "Bienvenido" << endl;
    int n;                                                   // declaramos el vector y la cantidad de numeros que va a tener
    cout << "Introduzca la cantidad de numeros que desea: "; // pedimos la cantidad de numeros que va a tener el vector
    cin >> n;
    int arr[n];
    int arregloInicial[n];
    // generamos los numeros aleatorios de 1 a n
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = randoms(1, n);
    }
    // asignamos los numeros aleatorios al vector inicial para que los tome en cuenta en cada caso
    for (int i = 0; i < n; i++)
    {
        arregloInicial[i] = arr[i];
    }

    // imprimimos el vector para conocer sus valores
    cout << "Vector: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl; // un salto de linea para que se vea mejor

    // llamamos a las funciones de ordenamiento y busqueda para que se ejecuten y ordenen el vector
    // empezamos con la funcion de ordenamiento por insercion
    ordenaInsercion(arr, n);
    cout << "Vector ordenado por insercion: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl; // otro salto de linea para que se vea mejor
    // reiniciamos el vector para que tome los valores iniciales
    reiniciarVector(arr, n, arregloInicial);

    // ahora llamamos a la funcion de ordenamiento burbuja
    ordenaBurbuja(arr, n);
    cout << "Vector ordenado por burbuja: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    reiniciarVector(arr, n, arregloInicial);

    // ahora llamamos a la funcion de ordenamiento merge
    ordenaMerge(arr, 0, n - 1);

    cout << "Vector ordenado por mergeShort: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // ahora llamamos a la funcion de busqueda secuencial
    cout << "Introduzca el numero que desea buscar: "; // pedimos el numero que se desea buscar
    int dato;
    cin >> dato;
    busqSecuencial(arr, dato, n);

    // ahora llamamos a la funcion de busqueda binaria
    // y llamamos a la funcion de busqueda binaria recursiva
    busqBinaria(arr, n,dato);

    int izquierd = 0;
    int derecha = n - 1;
    busqBinariaRE(arr, n,dato, izquierd, derecha);



    return 0;
}
