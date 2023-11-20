#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct ParrafoYPuerto // se crea la estructura tipo NODO
{
    vector<int> ips; // numeros de ips
    string texto;    // texto del parrafo
};

void GetLinesAndIntFromIpTXT(string bitacore, int &counts, vector<ParrafoYPuerto> &ParrafoYPuertoVector)
{ // con base en el string que le introducimos es el nombre del archivo
    ifstream bitacora(bitacore);

    if (!bitacora.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
    }

    std::string texto;
    // std::regex ipRegex("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
    // std::regex ipRegex("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+):(\\d+)");
    std::regex ipRegex("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
    string linea;

    while (getline(bitacora, texto))
    { // se lee linea por linea el archivo

        std::smatch match;
        linea = texto;

        while (regex_search(texto, match, ipRegex))
        { // se busca la ip en la linea

            // si match 1 es null entonces se le asigna un 192
            ParrafoYPuertoVector.push_back({{stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])}, linea});
            printf("IPINVECTOR: %d.%d.%d.%d\n", ParrafoYPuertoVector[counts].ips[0], ParrafoYPuertoVector[counts].ips[1], ParrafoYPuertoVector[counts].ips[2], ParrafoYPuertoVector[counts].ips[3]);

            texto = match.suffix();
            counts++;
            cout << "counts: " << counts << endl;
        }
    }
    bitacora.close();
}

int main()
{
    vector<ParrafoYPuerto> ParrafoYPuertoVector;
    int counts = 0;
    string bitacore = "bitacoraCorta.txt";
    GetLinesAndIntFromIpTXT(bitacore, counts, ParrafoYPuertoVector);

    // vector<Entra> entradas = {{{1, 2, 3, 1, 2}, "Texto1"}, {{0, 4}, "Texto2"}, {{2, 4, 2, 4}, "Texto3"}};
    return 0;
}