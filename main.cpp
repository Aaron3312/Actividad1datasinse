//funcion recursiva que suma todos los numeros de 1 a n
// n es un argumento de la funcion

#include <iostream>
using namespace std;

int suma(int n)
    {
        if (n == 1)
            return 1;
        else
            return n + suma(n - 1);
    }

int main()
{
    int n;
    cout << "Introduzca un numero: ";
    cin >> n;
    cout << "La suma de los numeros de 1 a " << n << " es " << suma(n) << endl;
    return 0;
}
