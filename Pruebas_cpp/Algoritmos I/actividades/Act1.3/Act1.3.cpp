// Name: Aaron Hernandez Jimenez - A01642529
// Date: 31/08/2023
// Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)

// Instrucciones:
// En equipos de tres personas, hacer una aplicación que:

// Abra el archivo de entrada llamado "bitacora.txt Download bitacora.txt" lealo y almacene los datos Formato del archivo bitacora.pdf).
// Ordene la información por fecha para la realización de las búsquedas (con el algoritmo de ordenamiento de preferencia)
// Solicite al usuario las fechas de inicio y fin de búsqueda de información.
// Despliegue los registros correspondientes a ese rango de fechas.
// Almacenar en un archivo el resultado del ordenamiento.
// Realizar una investigación y reflexión en forma individual de la importancia y eficiencia del uso de los diferentes
//  algoritmos de ordenamiento y búsqueda en una situación problema de esta naturaleza, generando un documento llamado "ReflexAct1.3.pdf"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Función para combinar dos subvectores ordenados
void merge( vector<int>& dia, int izq, int medio, int derecha) {
    int n1 = medio - izq + 1;
    int n2 = derecha - medio;
    vector<int> izqArr(n1);
    vector<int> derechArr(n2);

    for (int i = 0; i < n1; i++) {
        izqArr[i] = dia[izq + i];
    }
    for (int j = 0; j < n2; j++) {
        derechArr[j] = dia[medio + 1 + j];
    }

    // Fusionar los subvectores temporales de nuevo en dia[izq...derecha]
    int i = 0;
    int j = 0;
    int k = izq;

    while (i < n1 && j < n2) {
        if (izqArr[i] <= derechArr[j]) {
            dia[k] = izqArr[i];
            i++;
        } else {
            dia[k] = derechArr[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de izqArr[], si los hay
    while (i < n1) {
        dia[k] = izqArr[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de derechArr[], si los hay
    while (j < n2) {
        dia[k] = derechArr[j];
        j++;
        k++;
    }
}

// Función recursiva para realizar MergeSort
void mergeSort(std::vector<int>& dia, int izq, int derecha) {
    if (izq < derecha) {
        // Encuentra el punto medio
        int medio = izq + (derecha - izq) / 2;

        // Ordena la primera y la segunda mitad
        mergeSort(dia, izq, medio);
        mergeSort(dia, medio + 1, derecha);

        // Combina las mitades ordenadas
        merge(dia, izq, medio, derecha);
    }
}

// Función principal para ordenar el vector y guardar en un archivo de texto
void MergeyGuarda(const std::vector<int>& dias, const string& filename) {
    // Hacer una copia del vector de entrada para no modificarlo
    std::vector<int> dia = dias;

    // Ordenar el vector utilizando MergeSort
    mergeSort(dia, 0, dia.size() - 1);

    // Crea un archivo de texto
    ofstream nuevaBitacora(filename);

    // Verifica si el archivo se creó correctamente
    if (!nuevaBitacora.is_open())
    {
        cerr << "No se pudo crear el archivo." << endl;
    }
    else
    {
        cout << "Archivo creado correctamente." << endl;
    }

    // Escribir los elementos ordenados en el archivo de texto
    for (const int& num : dia) {
        nuevaBitacora << num << " ";
    }

    // Cerrar el archivo de texto
    nuevaBitacora.close();

}

//lee las primeras 3 letras del archivo y las guarda en un string
void OptenerMeses(ifstream& archivo, vector<string>& meses){
    string linea;
    string mes;
    while (getline(archivo, linea))
    {
        mes = linea.substr(0, 3);
        meses.push_back(mes);
    }
        for (int i = 0; i < meses.size(); i++)
    {
        cout << meses[i] << endl;
    }
    cout << "Ads" << endl;
}


int main()
{
    // Abre un archivo para lectura
    ifstream archivo("bitacora.txt");

    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }
    else
    {
        cout << "Archivo abierto correctamente." << endl;
    }
//
    // Lee el archivo línea por línea y almacena los datos en un vector de enteros de los dias
    string linea;
    int dia;
    int n = 0;
    vector<int> dias;
    while (getline(archivo, linea))
    {
        dia = stoi(linea.substr(4, 2));
        dias.push_back(dia);
    }

    // se llama a la funcion que lee los meses y los guarda en un vector de enteros
    vector<string> meses;
    OptenerMeses(archivo, meses);
//


    
    // procedemos a ordenar el vector de enteros con el algoritmo de ordenamiento mergesort
    MergeyGuarda(dias, "nuevaBitacora.txt");



    cout << "Archivo creado y contenido escrito exitosamente." << endl;

    // Cierra el archivo al finalizar
    archivo.close();

    return 0;
}
