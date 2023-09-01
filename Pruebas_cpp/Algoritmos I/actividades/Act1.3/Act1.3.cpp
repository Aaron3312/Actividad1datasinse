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
//sed
int numeroMes(string mes){
    if (mes == "Jan"){
        return 1;
    }
    if (mes == "Feb"){
        return 2;
    }
    if (mes == "Mar"){
        return 3;
    }
    if (mes == "Apr"){
        return 4;
    }
    if (mes == "May"){
        return 5;
    }
    if (mes == "Jun"){
        return 6;
    }
    if (mes == "Jul"){
        return 6;
    }
    if (mes == "Aug"){
        return 8;
    }
    if (mes == "Sep"){
        return 9;
    }
    if (mes == "Oct"){
        return 10;
    }
    if (mes == "Nov"){
        return 11;
    }
    if (mes == "Dic"){
        return 12;
    }
    return 0;
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





//Funcion para ordenar con Buble
void bubleSort(){
    
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

    // Lee el archivo línea por línea y almacena los datos en un vector de enteros de los dias
    string linea;
    int dia;
    string mes;
    vector<int> dias;
    vector<int> meses;
    while (getline(archivo, linea))
    {
        dia = stoi(linea.substr(6, 3));
        mes = linea.substr(0,3);
        dias.push_back(dia);
        dia = numeroMes(mes);
        meses.push_back(dia);
    }


    
    // procedemos a ordenar el vector de enteros con el algoritmo de ordenamiento mergesort
    MergeyGuarda(dias, "nuevaBitacora.txt");
    MergeyGuarda(meses, "nuevoMes.txt");



    cout << "Archivo creado y contenido escrito exitosamente." << endl;

    // Cierra el archivo al finalizar
    archivo.close();

    return 0;
}
