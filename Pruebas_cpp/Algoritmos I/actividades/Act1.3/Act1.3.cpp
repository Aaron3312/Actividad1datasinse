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
void merge(vector<int> &dia, int izq, int medio, int derecha)
{
    int n1 = medio - izq + 1;
    int n2 = derecha - medio;
    vector<int> izqArr(n1);
    vector<int> derechArr(n2);

    for (int i = 0; i < n1; i++)
    {
        izqArr[i] = dia[izq + i];
    }
    for (int j = 0; j < n2; j++)
    {
        derechArr[j] = dia[medio + 1 + j];
    }

    // Fusionar los subvectores temporales de nuevo en dia[izq...derecha]
    int i = 0;
    int j = 0;
    int k = izq;

    while (i < n1 && j < n2)
    {
        if (izqArr[i] <= derechArr[j])
        {
            dia[k] = izqArr[i];
            i++;
        }
        else
        {
            dia[k] = derechArr[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de izqArr[], si los hay
    while (i < n1)
    {
        dia[k] = izqArr[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de derechArr[], si los hay
    while (j < n2)
    {
        dia[k] = derechArr[j];
        j++;
        k++;
    }
}

// Función recursiva para realizar MergeSort
void mergeSort(std::vector<int> &dia, int izq, int derecha)
{
    if (izq < derecha)
    {
        // Encuentra el punto medio
        int medio = izq + (derecha - izq) / 2;

        // Ordena la primera y la segunda mitad
        mergeSort(dia, izq, medio);
        mergeSort(dia, medio + 1, derecha);

        // Combina las mitades ordenadas
        merge(dia, izq, medio, derecha);
    }
}

int numeroMes(string mes)
{
    if (mes == "Jan")
    {
        return 1;
    }
    if (mes == "Feb")
    {
        return 2;
    }
    if (mes == "Mar")
    {
        return 3;
    }
    if (mes == "Apr")
    {
        return 4;
    }
    if (mes == "May")
    {
        return 5;
    }
    if (mes == "Jun")
    {
        return 6;
    }
    if (mes == "Jul")
    {
        return 7;
    }
    if (mes == "Aug")
    {
        return 8;
    }
    if (mes == "Sep")
    {
        return 9;
    }
    if (mes == "Oct")
    {
        return 10;
    }
    if (mes == "Nov")
    {
        return 11;
    }
    if (mes == "Dic")
    {
        return 12;
    }
    return 0;
}

int sumaCodigo(string renglon)
{
    string nombre;
    int mes, dia, hora, min, seg, n;
    nombre = renglon.substr(0, 3);
    mes = numeroMes(nombre);
    dia = stoi(renglon.substr(4, 2));
    if (dia > 9)
    {
        n = 1;
    }
    else
    {
        n = 0;
    }
    hora = stoi(renglon.substr(6, 3));
    min = stoi(renglon.substr(9 + n, 3));
    seg = stoi(renglon.substr(12 + n, 3));
    return mes * 100000000 + dia * 1000000 + hora * 10000 + min * 100 + seg;
}

// Función principal para ordenar el vector y guardar en un archivo de texto
void MergeyGuarda(const vector<int> &meses, const vector<int> &dias, const string &filename)
{
    // Hacer una copia del vector de entrada para no modificarlo
    vector<int> dia = dias;
    vector<int> mes = meses;

    // Ordenar el vector utilizando MergeSort
    mergeSort(dia, 0, dia.size() - 1);
    mergeSort(mes, 0, mes.size() - 1);

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
    for (const int &num : mes)
    {
        nuevaBitacora << num << " ";
    }

    // Escribir los elementos ordenados en el archivo de texto
    for (const int &num : dia)
    {
        nuevaBitacora << num << " ";
    }

    // Cerrar el archivo de texto
    nuevaBitacora.close();
}

void ordenaArchivo(){
// decidimos ordenarlo con bubblesort que si bien no es muy eficiente, funciona y es lo unico que se pide
    // Abre un archivo para lectura
    ifstream archivo("bitacoraCorta.txt");
    vector<string> renglones;
    string linea;


    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    else
    {
        cout << "Archivo abierto correctamente." << endl;
    }
            while (getline(archivo, linea))
            {
                renglones.push_back(linea);
            }
            int sizR = renglones.size();
            for (int i = 0; i < sizR; i++)
            {
                for (int j = 0; j < sizR - 1 - i; j++)
                {
                    if (sumaCodigo(renglones[j]) > sumaCodigo(renglones[j + 1]))
                    {
                        renglones[j].swap(renglones[j + 1]);
                    }
                }
            }

            ofstream archivo1("nuevaBitacora.txt");

            for (int i = 0; i < sizR; i++)
            {
                archivo1 << renglones[i] << endl;
            }

            archivo1.close();

            // procedemos a ordenar el vector de enteros con el algoritmo de ordenamiento mergesort
            // MergeyGuarda(meses,dias, "nuevaBitacora.txt");

            cout << "Archivo creado y contenido escrito exitosamente." << endl;

            // Cierra el archivo al finalizar
            archivo.close();
        }
    void busquedaPorFecha(){
    int mes1, dia1, hora1, min1, seg1, mes2, dia2, hora2, min2, seg2, fecha1, fecha2,opcion;
    cout << "Bienvenido al buscador de fechas" << endl;
    cout << "Quieres una fecha pre establecida para pruebas? 1 = si 0 = no" << endl;
    cin >> opcion;
    if (opcion == 1){
        mes1 = 10;
        dia1 = 1;
        hora1 = 1;
        min1 = 1;
        seg1 = 1;
        mes2 = 12;
        dia2 = 1;
        hora2 = 1;
        min2 = 1;
        seg2 = 1;
    }
    else{
    cout << "Ingrese la fecha inicial que quiere buscar" << endl;
    cout << "Mes: ";
    cin >> mes1;
    cout << "Dia: ";
    cin >> dia1;
    cout << "Hora: ";
    cin >> hora1;
    cout << "Minuto: ";
    cin >> min1;
    cout << "Segundo: ";
    cin >> seg1;
    cout << "Ingrese la fecha final que quiere buscar" << endl;
    cout << "Mes: ";
    cin >> mes2;
    cout << "Dia: ";
    cin >> dia2;
    cout << "Hora: ";
    cin >> hora2;
    cout << "Minuto: ";
    cin >> min2;
    cout << "Segundo: ";
    cin >> seg2;
    }
    fecha1 = mes1 * 100000000 + dia1 * 1000000 + hora1 * 10000 + min1 * 100 + seg1;
    fecha2 = mes2 * 100000000 + dia2 * 1000000 + hora2 * 10000 + min2 * 100 + seg2;
    // implementamos un metodo de busqueda binaria para encontrar el primer elemento que sea mayor a la fecha inicial
    // y el ultimo elemento que sea menor a la fecha final
    // primero buscamos el primer elemento que sea mayor a la fecha inicial
    

}
        

int main()
{


    // Lee el archivo línea por línea y almacena los datos en un vector de enteros de los dias
    int dia;
    string mes;
    vector<int> dias;
    vector<int> meses;
    vector<int> renglonesNumero;
    string linea;
   

    ifstream archivo2("nuevaBitacora.txt");

    if (archivo2.is_open())
    {
        cout << "El archivo ya existe" << endl;
        for (int i = 0; i < 4; i++)
        {
            getline(archivo2, linea);
            renglonesNumero.push_back(sumaCodigo(linea));
        }

        if (renglonesNumero[0] < renglonesNumero[1] && renglonesNumero[1] < renglonesNumero[2] && renglonesNumero[2] < renglonesNumero[3])
        {
            cout << "El archivo ya esta ordenado" << endl;
        }
        else {
            cout << "El archivo no esta ordenado" << endl;
            ordenaArchivo();

        }
    }
    else {
        cout << "El archivo no existe" << endl;
        ordenaArchivo();
    }
    // ahora vamos a utilizar un algoritmo de busqueda para poder investigar un periodo entre 2 fechas que se van a preguntar al usuario
    // primero vamos a preguntarle al usuario las fechas que quiere buscar
    BusquedaPorFecha();

    
            
    
        return 0;
    }
