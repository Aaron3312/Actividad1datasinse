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

//funcion numero a nombre de mes
string nombreMes(int mes)
{
    if (mes == 1)
    {
        return "Jan";
    }
    if (mes == 2)
    {
        return "Feb";
    }
    if (mes == 3)
    {
        return "Mar";
    }
    if (mes == 4)
    {
        return "Apr";
    }
    if (mes == 5)
    {
        return "May";
    }
    if (mes == 6)
    {
        return "Jun";
    }
    if (mes == 7)
    {
        return "Jul";
    }
    if (mes == 8)
    {
        return "Aug";
    }
    if (mes == 9)
    {
        return "Sep";
    }
    if (mes == 10)
    {
        return "Oct";
    }
    if (mes == 11)
    {
        return "Nov";
    }
    if (mes == 12)
    {
        return "Dic";
    }
    return "0";
}

//Funcion para hacer busqueda binaria en un vector 
void busqBinaria(int dato)
{  
    ifstream archivo3("BitacoraDeNumeros.txt");
    string linea;
    vector<int> renglonesNumero;
    while (getline(archivo3, linea))
    {
        renglonesNumero.push_back(stoi(linea));
    }
    int n = renglonesNumero.size();
    cout << "Funcion Busqueda binaria" << endl;
    //primero el metodo iterativo
    int inicio = 0;
    int fin = n-1;
    int medio;
    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        if (dato == renglonesNumero[medio])
        {
            cout << "El numero se encuentra en el indice " << medio << endl;
            break;
        }
        else if (dato < renglonesNumero[medio])
        {
            fin = medio - 1;
        }
        else
        {
            inicio = medio + 1;
        }
    }
    if (inicio > fin)
    {
        cout << "-1" << endl;
    }
}

// Función para ordenar un vector utilizando el algoritmo de bubble sort
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

int sumaCodigo(string renglon) // funcion para convertir el renglon en un numero que represente la fecha
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

// Función para ordenar un vector utilizando el algoritmo de bubble sort
void ordenaArchivo(vector<string> renglones){
// decidimos ordenarlo con bubblesort que si bien no es muy eficiente, funciona y es lo unico que se pide
    // Abre un archivo para lectura
    ifstream archivo("bitacora.txt");
    string linea;


    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    else
    {
        cout << "Archivo abierto correctamente." << endl;
        cout << "Organizando y ordenando todo lo que tiene que ver con el hecho del algoritmo bubblesort, aprox 2:30 min" << endl;
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

    void busqSecuencial(int fecha1, int fecha2, vector<string> renglones, ofstream& archivo5)
{   
    ifstream archivo3("BitacoraDeNumeros.txt");
    string linea;
    vector<int> renglonesNumero;
    vector<string> renglones2;
    while (getline(archivo3, linea))
    {
        renglonesNumero.push_back(stoi(linea));
    }
    
    archivo3.close();

    ifstream archivo4("nuevaBitacora.txt");
    while (getline(archivo4, linea))
    {
        renglones2.push_back(linea);
    }

    int n = renglonesNumero.size();
    cout << "Busqueda secuencial" << endl;
    
    int minimo, maximo;
    for (int i = 0; i < n ; i++)
    {
        if (renglonesNumero[i] >= (fecha1))
        {
            minimo = i;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (renglonesNumero[i] >= (fecha2))
        {
            maximo = i;
            break;
        }
    }
    archivo3.close();
    archivo4.close();
    cout << "El numero minimo es: " << minimo << endl;
    cout << "El numero maximo es: " << maximo << endl;
    for (int i = minimo; i <= maximo; i++)
    {
        archivo5 << renglones2[i] << endl;
    }
    archivo5.close();

}
    void busquedaPorFecha(vector<string> renglones){
    int mes1, dia1, hora1, min1, seg1, mes2, dia2, hora2, min2, seg2, fecha1, fecha2,opcion;
    cout << "Bienvenido al buscador de fechas" << endl;
    cout << "Quieres una fecha pre establecida para pruebas? 1 = si 0 = no" << endl;
    cin >> opcion;
    if (opcion == 1){
        int numeroClave = 904055638;
        int numeroClave2 = 1001072246;
        mes1 = (numeroClave / 100000000);
        dia1 = (numeroClave % 100000000) / 1000000;
        hora1 = (numeroClave % 1000000) / 10000;
        min1 = (numeroClave % 10000) / 100;
        seg1 = numeroClave % 100;
        mes2 = (numeroClave2 / 100000000);
        dia2 = (numeroClave2 % 100000000) / 1000000;
        hora2 = (numeroClave2 % 1000000) / 10000;
        min2 = (numeroClave2 % 10000) / 100;
        seg2 = numeroClave2 % 100;

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
    string mesunonombre = nombreMes(mes1);
    string mesdosnombre = nombreMes(mes2);
    ofstream archivo5("BusquedaPorFecha.txt");
    cout << "La fecha inicial es: " << mesunonombre << "/" << dia1 << " " << hora1 << ":" << min1 << ":" << seg1 << endl;
    cout << "La fecha final es: " << mesdosnombre << "/" << dia2 << " " << hora2 << ":" << min2 << ":" << seg2 << endl;
    archivo5 << "La fecha inicial es: " << mesunonombre << "/" << dia1 << " " << hora1 << ":" << min1 << ":" << seg1 << endl;
    archivo5 << "La fecha final es: " << mesdosnombre << "/" << dia2 << " " << hora2 << ":" << min2 << ":" << seg2 << endl;
    fecha1 = mes1 * 100000000 + dia1 * 1000000 + hora1 * 10000 + min1 * 100 + seg1;
    fecha2 = mes2 * 100000000 + dia2 * 1000000 + hora2 * 10000 + min2 * 100 + seg2;
    cout << "La fecha inicial en numero es: " << fecha1 << endl;
    cout << "La fecha final en numero es: " << fecha2 << endl;
    // implementamos un metodo de busqueda binaria para encontrar el primer elemento que sea mayor a la fecha inicial
    // y el ultimo elemento que sea menor a la fecha final
    // primero buscamos el primer elemento que sea mayor a la fecha inicial
    //le pasamos tambein un elemento de texto a la busqueda secuencial para que nos regrese el renglon de texto
    busqSecuencial(fecha1,fecha2,renglones,archivo5);
    
    // ahora buscamos el ultimo elemento que sea menor a la fecha final


}

    void obtenerRengloNumYRenglo(vector<string> renglones){
        string linea;
        ifstream archivo2("nuevaBitacora.txt");
        ofstream archivo3("BitacoraDeNumeros.txt");
        renglones.clear();
        while (getline(archivo2, linea))
        {
            renglones.push_back(linea);
            archivo3 << sumaCodigo(linea) << endl;
        }
        archivo2.close();
        archivo3.close();
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
    vector<string> renglones;

   
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
            obtenerRengloNumYRenglo(renglones);
            busquedaPorFecha(renglones);

        }
        else {
            cout << "El archivo no esta ordenado" << endl;
            ordenaArchivo(renglones);
            obtenerRengloNumYRenglo(renglones);
            busquedaPorFecha(renglones);
            
        }
    }
    else {
        cout << "El archivo no existe" << endl;
        ordenaArchivo(renglones);
        obtenerRengloNumYRenglo(renglones);
        busquedaPorFecha(renglones);
    }

    archivo2.close();




    
            
    
        return 0;
    }
