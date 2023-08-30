// Name: Aaron Hernandez Jimenez - A01642529
// Date: 14/08/2023
// Description: Act 1.1 - Funciones Iterativas, Recursivas y su análisis de Complejidad

#include <iostream>

using namespace std;

//Realiza una aplicación en C++ en forma individual,  que calculé la sumatora de 1 hasta n y llame a tres 
//funciones: llamadas sumaIterativa, sumaRecursiva y sumaDirecta.

//funcion iterativa que suma todos los numeros de 1 a n
//La complejidad de esta funcion es O(n) porque depende del numero que se le de, va a ser la cantidad de operaciones que se hagan
int sumaIterativa(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    return sum;
}

//funcion recursiva que suma todos los numeros de 1 a n
//La complejidad de esta funcion es O(n) porque depende del numero que se le de, va a ser la cantidad de operaciones que se hagan
int sumaRecursiva(int n)
{
    if (n == 1)
        return 1;
    else
        return n + sumaRecursiva(n - 1);
}

//funcion directa que suma todos los numeros de 1 a n
//La complejidad de esta funcion es O(1) porque no importa el numero que se le de, siempre va a ser la misma cantidad de operaciones
int sumaDirecta(int n)
{
    return (n * (n + 1)) / 2;
}

//la funcion suma es la que se va a llamar en el main y regresa las 3 funciones, pero n tiene que ser positivo y entero
int suma(int n) {
    if (n > 0) {
        cout << "Suma iterativa: " << sumaIterativa(n) << endl;
        cout << "Suma recursiva: " << sumaRecursiva(n) << endl;
        cout << "Suma directa: " << sumaDirecta(n) << endl;
        return 0;
    }
    else {
        cout << "El numero debe ser positivo y entero" << endl;
        cout << "Introduzca un numero: ";
        cin >> n;
        return suma(n);
    }
}

//funcion main que llama a la funcion suma y pide un numero al usuario para calcular la sumatoria de 1 a n
int main() {
    int n;
    cout << "Introduzca un numero: ";
    cin >> n;
    cout << "La suma de los numeros de 1 a " << n << " es "<<endl;
    cout << suma(n) << endl;
    return 0;
}