#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct LogEntry {
    std::string date;
    std::string time;
    std::string ip;
    std::string message;
};

// Función de comparación personalizada para ordenar por fecha y hora
bool compareLogEntries(const LogEntry& entry1, const LogEntry& entry2) {
    // Combinar fecha y hora para facilitar la comparación
    std::string datetime1 = entry1.date + " " + entry1.time;
    std::string datetime2 = entry2.date + " " + entry2.time;
    return datetime1 < datetime2;
}

int main() {
    std::ifstream inputFile("bitacora.txt");
    std::vector<LogEntry> logEntries;

    if (!inputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        LogEntry entry;
        iss >> entry.date >> entry.time >> entry.ip;

        // Leer el resto de la línea como un mensaje
        std::getline(iss, entry.message);
        
        logEntries.push_back(entry);
    }

    inputFile.close();

    // Ordenar los registros usando la función de comparación personalizada
    std::sort(logEntries.begin(), logEntries.end(), compareLogEntries);

    // Escribir los registros ordenados en un nuevo archivo
    std::ofstream outputFile("registro_ordenado.txt");
    if (!outputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo de salida." << std::endl;
        return 1;
    }

    for (const auto& entry : logEntries) {
        outputFile << entry.date << " " << entry.time << " " << entry.ip << " " << entry.message << "\n";
    }

    outputFile.close();

    std::cout << "Registros ordenados y guardados en registro_ordenado.txt." << std::endl;

    return 0;
}
