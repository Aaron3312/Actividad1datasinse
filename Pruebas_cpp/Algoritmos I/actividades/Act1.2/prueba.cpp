// Name: Aaron Hernandez Jimenez - A01642529
// Date: 29/08/2023
// Description: Act 1.2 - Algoritmos de Búsqueda y Ordenamiento

//instrucciones:
//Realiza una aplicación en C++ en forma individual, 
//en donde dado n numeros de entrada que son almacenados en un vector<int> realice las siguientes funciones de ordenamiento:

//Desde la aplicación deberá solicitar al usuario la cantidad de búsquedas que desea,
// y por cada búsqueda deberá de solicitar el número que desea buscar y desplegará el índice donde 
//se encuentra localizado o -1 en caso de que no se encuentre, la búsqueda deberá realizarla en ambos métodos (secuencial y binario). 

//Todas las funcionalidades deberán de estar correctamente alineadas y documentadas. 
//Como parte de la documentación deberá incluirse la complejidad de cada una de ellas.

#include <iostream>
#include <ctime>
#include <random>
#include <vector>

using namespace std;

//ordenaInserción tiene un complejidad de O(n^2).
//Ordene en forma ascendente los datos con el método de Inserción
void ordenaInsercion(vector<int> arr[], int n) {
    int auxiliar;
    for (int i = 1; i < n; i++) {
        auxiliar = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > auxiliar) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = auxiliar;
    }
}


//ordenaBurbuja Tiene una complejidad de O(n^2) porque tiene dos ciclos for anidados
void ordenaBurbuja(int arr[], int n){
    int aux; //en vez de utilizar swap() utilizamos una variable auxiliar para hacer el cambio de valores
    for(int i = 0; i < n -1; i++){
        for(int j = 0; j < n-1; j++){
            if(arr[j] > arr [j+1]){
                aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }
}

//ordenaMerge Tiene una complejidad de O(n*log(n)) porque tiene un ciclo for y un while anidados

void ordenaMerge(int arr[], int n){
    int aux;
    for(int i = 0; i < n; i++){
        aux = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > aux){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = aux;
    }
}

//busqSecuencial

void busqSecuencial(int arr[], int n){
    int aux;
    for(int i = 0; i < n; i++){
        aux = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > aux){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = aux;
    }
}

//busqBinaria (Iterativo & Recursivo)	
void busqBinaria(int arr[], int n){
    int aux;
    for(int i = 0; i < n; i++){
        aux = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > aux){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = aux;
    }
}
//declaramos una funcion que genere numeros aleatorios
int randoms(int min, int max){
    return rand() % (max - min + 1) + min;
}

//funcion que reinica el vector a valores iniciales
void reiniciarVector(vector<int>, int n, int arregloInicial[]){
    for(int i = 0; i < n; i++){
        arr[i] = arregloInicial[i];
    }
}


//funcion main generando un vector int de n numeros aleatorios
int main() {
    cout << "Bienvenido" << endl;
    int n;  //declaramos el vector y la cantidad de numeros que va a tener
    cout << "Introduzca la cantidad de numeros que desea: "; //pedimos la cantidad de numeros que va a tener el vector
    cin >> n; 
    vector<int> arr[n];
    int arregloInicial[n];
    //generamos los numeros aleatorios de 1 a n
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        arr[i] = randoms(1, n);
    }
    //asignamos los numeros aleatorios al vector inicial para que los tome en cuenta en cada caso
    for(int i = 0; i < n; i++){
        arregloInicial[i] = arr[i];
    }

    //imprimimos el vector para conocer sus valores
    cout << "Vector: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl; //un salto de linea para que se vea mejor


    //llamamos a las funciones de ordenamiento y busqueda para que se ejecuten y ordenen el vector 
    //empezamos con la funcion de ordenamiento por insercion
    ordenaInsercion(arr, n);
    cout << "Vector ordenado por insercion: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl; //otro salto de linea para que se vea mejor
    //reiniciamos el vector para que tome los valores iniciales
    reiniciarVector(arr, n, arregloInicial);

    return 0;
}


// Función para combinar dos subarreglos ordenados
void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Crear arreglos temporales
    int leftArray[n1];
    int rightArray[n2];

    // Copiar datos a los arreglos temporales leftArray[] y rightArray[]
    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArray[i] = arr[middle + 1 + i];
    }

    // Combinar los arreglos temporales en arr[l..r]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de leftArray[], si los hay
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de rightArray[], si los hay
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

// Función principal de Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Encuentra el punto medio del arreglo
        int middle = left + (right - left) / 2;

        // Ordena la primera mitad y la segunda mitad
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Combina las mitades ordenadas
        merge(arr, left, middle, right);
    }
}

int main() {
    int miArray[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(miArray) / sizeof(miArray[0]);

    cout << "Array original: ";
    for (int i = 0; i < n; i++) {
        cout << miArray[i] << " ";
    }
    cout << endl;

    mergeSort(miArray, 0, n - 1);

    cout << "Array ordenado: ";
    for (int i = 0; i < n; i++) {
        cout << miArray[i] << " ";
    }
    cout << endl;

    return 0;
}

#include <iostream>

using namespace std;

// Función de búsqueda binaria recursiva
int busquedaBinariaRecursiva(int arr[], int elemento, int izquierda, int derecha) {
    if (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        // Si el elemento buscado es igual al elemento en la posición media, lo hemos encontrado
        if (arr[medio] == elemento) {
            return medio;
        }

        // Si el elemento buscado es menor que el elemento en la posición media,
        // buscamos en la mitad izquierda del arreglo
        if (arr[medio] > elemento) {
            return busquedaBinariaRecursiva(arr, elemento, izquierda, medio - 1);
        }

        // Si el elemento buscado es mayor que el elemento en la posición media,
        // buscamos en la mitad derecha del arreglo
        return busquedaBinariaRecursiva(arr, elemento, medio + 1, derecha);
    }

    // Si el elemento no se encuentra en el arreglo, retornamos -1
    return -1;
}

int main() {
    int miArreglo[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int elementoBuscado = 5;
    int n = sizeof(miArreglo) / sizeof(miArreglo[0]);

    int resultado = busquedaBinariaRecursiva(miArreglo, elementoBuscado, 0, n - 1);

    if (resultado != -1) {
        cout << "El elemento " << elementoBuscado << " se encuentra en la posición " << resultado << endl;
    } else {
        cout << "El elemento " << elementoBuscado << " no se encuentra en el arreglo." << endl;
    }

    return 0;
}

