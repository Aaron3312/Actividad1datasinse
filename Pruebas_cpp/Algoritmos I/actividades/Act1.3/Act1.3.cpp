// Name: Aaron Hernandez Jimenez - A01642529
// Date: 31/08/2023
//Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)

//Instrucciones:
//En equipos de tres personas, hacer una aplicación que:

//Abra el archivo de entrada llamado "bitacora.txt Download bitacora.txt" lealo y almacene los datos Formato del archivo bitacora.pdf).
//Ordene la información por fecha para la realización de las búsquedas (con el algoritmo de ordenamiento de preferencia)
//Solicite al usuario las fechas de inicio y fin de búsqueda de información.
//Despliegue los registros correspondientes a ese rango de fechas.
//Almacenar en un archivo el resultado del ordenamiento.
//Realizar una investigación y reflexión en forma individual de la importancia y eficiencia del uso de los diferentes
// algoritmos de ordenamiento y búsqueda en una situación problema de esta naturaleza, generando un documento llamado "ReflexAct1.3.pdf"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int main() {
    // Abre un archivo para lectura
    ifstream archivo("bitacora.txt");
    
    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }
    else
    {
        cout << "Archivo abierto correctamente." << endl;
    }
    
    // Crea un archivo de texto
    ofstream archivo1("nuevaBitacora.txt");
    

    // Verifica si el archivo se creó correctamente
    if (!archivo1.is_open()) {
        cerr << "No se pudo crear el archivo." << endl;
        return 1;
    }

    // Escribe contenido en el archivo
    archivo1 << "Este es un nuevo archivo de texto." << endl;
    archivo1 << "Puedes escribir más líneas aquí." << endl;

    // Cierra el archivo al finalizar
    archivo.close();
    archivo1.close();

    cout << "Archivo creado y contenido escrito exitosamente." << endl;

    return 0;
}





