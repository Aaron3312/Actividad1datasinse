//Hacer un programa que usando colas haga el siguiente menu
// 1. Insertar un caracter a una cola
// 2. Mostrar todos los elementos de la cola
// 3. salir

#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

struct Nodo{
    char dato;
    Nodo *siguiente;
};

//Prototipos de funcion
void menu();
void insertarCola(Nodo *&, Nodo *&, char);
bool cola_vacia(Nodo *&);
void suprimirCola(Nodo *&, Nodo *&, char &);

int main(){
    menu();

    getch();
    return 0;
}

void menu(){
    int opcion;
    char dato;

    Nodo *frente = NULL;
    Nodo *fin = NULL;
    do{
        cout <<"\t :Menu:\n";
        cout <<"1. Insertar un caracter a una cola" << endl;
        cout <<"2. Mostrar todos los elementos de la cola" << endl;
        cout <<"3. Salir" << endl;
        cout <<"Opcion: ";
        cin >> opcion;
        switch (opcion){
        case 1:
            cout << "\nDigite un caracter: ";
            cin >> dato;
            insertarCola(frente, fin, dato);
            break;
        case 2:
            cout << "\nMostrando los elementos de la cola: ";
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
            break;
        case 3:
            break;
        }    system("cls");
        
    }
    while (opcion != 3);
}

void insertarCola(Nodo *&frente, Nodo *&fin, char n){
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
    cout << "\nElemento " << n << " insertado a cola correctamente" << endl;
}

//funcion para determinar si la cola esta vacia o no
bool cola_vacia(Nodo *&frente){
    return(frente == NULL)? true : false;
}

//funcion para eliminar elementos de la cola
void suprimirCola(Nodo *&frente, Nodo *&fin, char &n){
    n = frente -> dato;
    Nodo *aux = frente;

    if(frente == fin){
        frente = NULL;
        fin = NULL;
    }
    else{
        frente = frente -> siguiente;
    }
    delete aux;
}

