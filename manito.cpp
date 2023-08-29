#include <iostream>
#include <vector>
using namespace std;

// una funcion recursiba que encuentre el numero mas pequeño en una lista
// la lista sera A = [1,4,24,17,-5,10,-22]

int minimo(int A[], int n)
{
    if (n == 1)
        return A[0];
    else
    {
        int x = minimo(A, n - 1);
        if (x < A[n - 1])
            return x;
        else
            return A[n - 1];
    }
}

int main()
{
    int A[] = {1, 4, 24, 17, -5, 2000, 55};
    cout << A[0] << endl;
    //explicame un poco de que es sizeof(A) / sizeof(A[0])?
    //sizeof(A) es el tamaño total de la lista
    //sizeof(A[0]) es el tamaño de un elemento de la lista
    //entonces sizeof(A) / sizeof(A[0]) es el numero de elementos en la lista
    cout << "El tamaño de la lista es: " << endl;
    cout << sizeof(A) << endl;
    cout << sizeof(A[0]) << endl;
    int n = sizeof(A) / sizeof(A[0]);
    cout << "El minimo es: " << minimo(A, n) << endl;
    return 0;
    
    // thomas h cormen introduccion a los algoritmos

