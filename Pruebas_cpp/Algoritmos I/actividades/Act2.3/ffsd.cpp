#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string input = "Esta es una cadena con una dirección IP 192.168.1.1 y otra 10.0.0.1.";

    // Define la expresión regular para encontrar direcciones IP
    std::regex ip_pattern("\\b(?:[0-9]{1,3}\\.){3}[0-9]{1,3}\\b");

    // Realiza la búsqueda en la cadena de entrada
    std::smatch matches;
    if (std::regex_search(input, matches, ip_pattern)) {
        std::cout << "Dirección IP encontrada: " << matches[0] << std::endl;
    } else {
        std::cout << "No se encontraron direcciones IP." << std::endl;
    }

    return 0;
}