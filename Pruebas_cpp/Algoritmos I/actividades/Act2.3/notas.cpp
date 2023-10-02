#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    // Crea un unordered_map para almacenar las asignaciones IP-Valor
    unordered_map<string, string> ipMap;

    // Abre el archivo de texto
    ifstream inputFile("archivo.txt");

    // Verifica si el archivo se abrió correctamente
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    // Lee cada línea del archivo
    string line;
    while (getline(inputFile, line)) {
        // Supongamos que cada línea tiene el formato "IP Valor"
        // Puedes ajustar esto según el formato real de tu archivo
        string ipAddress;
        string value;

        // Utiliza un stringstream para dividir la línea en IP y valor
        istringstream lineStream(line);
        if (lineStream >> ipAddress >> value) {
            // Agrega la asignación IP-Valor al unordered_map
            ipMap[ipAddress] = value;
        } else {
            cerr << "Formato de línea incorrecto: " << line << endl;
        }
    }

    // Ahora puedes acceder a los valores por dirección IP
    string ipAddressToFind = "192.168.1.1";
    if (ipMap.find(ipAddressToFind) != ipMap.end()) {
        cout << "Valor para " << ipAddressToFind << ": " << ipMap[ipAddressToFind] << endl;
    } else {
        cout << "Dirección IP no encontrada: " << ipAddressToFind << endl;
    }

    // Cierra el archivo
    inputFile.close();

    return 0;
}