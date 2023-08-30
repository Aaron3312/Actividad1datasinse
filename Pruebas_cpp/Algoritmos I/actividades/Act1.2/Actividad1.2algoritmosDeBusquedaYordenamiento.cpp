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

using namespace std;

//ordenaInserción
void ordenaInsercion(int arr[], int n){
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


//ordenaBurbuja 
void ordenaBurbuja(int arr[], int n){
    int aux;
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

//ordenaMerge

//busqSecuencial

//busqBinaria (Iterativo & Recursivo)	

//funcion main generando un vector int de n numeros aleatorios
int main() {
    int n; int arr[n]; //declaramos el vector y la cantidad de numeros que va a tener
    cout << "Introduzca la cantidad de numeros que desea: "; //pedimos la cantidad de numeros que va a tener el vector
    cin >> n; 
    //generamos los numeros aleatorios
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        arr[i] = rand() % 100;
    }
    //imprimimos el vector para conocer sus valores
    cout << "Vector: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl; //un salto de linea para que se vea mejor

    //llamamos a las funciones de ordenamiento
    ordenaInsercion(arr, n);
    cout << "Vector ordenado por insercion: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    ordenaBurbuja(arr, n);
    cout << "Vector ordenado por burbuja: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;

}