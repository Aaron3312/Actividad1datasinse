//insertar elementos en una cola
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;
};

//Prototipos de funcion
void insertarCola(Nodo *&, Nodo *&, int);
bool cola_vacia(Nodo *);
void suprimirCola(Nodo *&, Nodo *&, int &);

int main(){

    //abrimos el archivo bitacoraCorta.txt
    ifstream bitacoraCorta;



    Nodo *frente = NULL;
    Nodo *fin = NULL;

    int dato;

    cout << "Digite un numero: ";
    cin >> dato;
    insertarCola(frente, fin, dato);

    cout << "Digite un numero: ";
    cin >> dato;
    insertarCola(frente, fin, dato);

    cout << "Digite un numero: ";
    cin >> dato;
    insertarCola(frente, fin, dato);

    while (frente != NULL)
    {
        suprimirCola(frente, fin, dato);
        if(frente != NULL){
            cout << dato << ", ";
        }
        else{
            cout << dato << ".";
        }
    }
    


    getch();
    return 0;
}

//funcion para insertar elementos en una cola
void insertarCola(Nodo *&frente, Nodo *&fin, int n){
    Nodo *nuevo_nodo = new Nodo();

    nuevo_nodo -> dato = n;
    nuevo_nodo -> siguiente = NULL;

    if(cola_vacia(frente)){
        frente = nuevo_nodo;
    }
    else{
        fin -> siguiente = nuevo_nodo;
    }

    fin = nuevo_nodo;

    cout<< "\tEl elemento "<< n << " se inserto correctamente a la cola"<<endl;
};

//funcion para determinar si la cola esta vacia o no
bool cola_vacia(Nodo *frente){
    return (frente == NULL)? true : false;
};

//Prototipos de funcion
void suprimirCola(Nodo *&frente, Nodo *&fin, int &n){
    n = frente -> dato;
    Nodo *aux = frente;

    if (frente == fin){
        frente = NULL;
        fin = NULL;
    }
    else{
        frente = frente -> siguiente;
    }
    delete aux;
};
