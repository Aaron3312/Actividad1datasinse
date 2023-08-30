//
// Created by Aaron on 24/08/2023. (DD/MM/YYYY)
//
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// vamos a generar un arreglo de 10 numeros de manera random con las librerias random y time
// vamos a ordenar el arreglo de menor a mayor con el metodo de burbuja
// vamos a imprimir el arreglo ordenado
//generamos una funcion llamada BubbleShort para ordenamiento burbuja

void BubbleShort(int arreglo[], int n) {
    int aux;
    for (int i = 0; i < n; i++) { // complejidad de esta linea es = n
        for (int j = 0; j < n - 1 - i; j++) { // complejidad de esta linea es = n
            if (arreglo[j] > arreglo[j + 1]) { // complejidad de esta linea es = 1
                aux = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = aux;
            }
        }
    }
}


int main() {
    int arreglos[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        arreglos[i] = rand() % 10;
    }
    cout << "Arreglo desordenado" << endl;
    for (int i = 0; i < 10; i++) {
        cout << arreglos[i] << " ";
    }
    cout << endl;
    BubbleShort(arreglos, 10);
    cout << "Arreglo ordenado" << endl;
    for (int i = 0; i < 10; i++) {
        cout << arreglos[i] << " ";
    }
    return 0;
}
//como corro el .exe? en la terminal ./bubbleShort.exe
// como genero el .exe ? g++ bubbleShort.cpp -o bubbleShort.exe