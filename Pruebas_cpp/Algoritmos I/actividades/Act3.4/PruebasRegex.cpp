#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>

using namespace std;


struct ParrafoYPuerto // se crea la estructura tipo NODO
{
    long port; // numero que tendra cada puerto
    string texto; //texto del parrafo
};



//long StringToLongInt(string input){
    //stringstream sd(input);
   // string segment;
//    vector<int> ip_parts;
    /*
    while (getline(sd, segment, '.'))
    {
        ip_parts.push_back(stoi(segment));
    }
    long  octeto1 = ip_parts[0];*/
   // long octeto1 = stoi(input);
//}
/*
int ReadArchive(string bitacore){
    ifstream bitacora("bitacoraCorta.txt");

    if (!bitacora.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    std::string texto;
  std::regex ipRegex("^(.*):(\\d+)$");
    string linea;

    while (getline(bitacora, texto))
    { // se lee linea por linea el archivo

        smatch match;
        linea = texto;

        while (regex_search(texto, match, ipRegex))
        { // se busca la ip en la linea
            // cout << "IP encontrada: " << match[0] << endl;
            string ip_str = match[0];
            string Port = ip_str;
            cout << Port << "   ";
            cout << linea << endl;
            //texto = match.suffix();
            return 0;
        }

    }


}
*/
int main()
{
  /*  std::string text = "Oct 9 10:32:24 423.2.230.77:6166 Failed password for illegal user guest";
std::regex pattern("\\d+"); // Definir una expresión regular para encontrar números

// Buscar coincidencias en el texto
std::smatch matches;
if (std::regex_search(text, matches, pattern)) {
    std::cout << "Se ha encontrado un numero: " << matches[0] << std::endl;
}*/

    string str = "the ape was at the sex";
    smatch matches;
    regex reg ("(ape[^ ]?)");

    while (regex_search(str, matches, reg)) {
        cout << matches.str(1) << endl;
        str = matches.suffix().str();
    }
    string linas = "Oct 9 10:32:24 423.2.230.77:6166 Failed password for illegal user guest";
    regex reg2 ("(\\d{4,5})");
    smatch matches1;
    int i = 0;
    while (regex_search(linas, matches1, reg2)) {
        cout << matches1.str(i) << endl;
        i++;
        linas = matches.suffix().str();
    }

    for (int i = 0; i < 10; i++) {
        cout << matches1.str(i) << endl;
    }
    return 0;
}

int main(){
    ifstream bitacora("bitacoraCorta.txt");
    

    smatch matches;
    regex reg ("(ape[^ ]?)");

    while (regex_search(str, matches, reg)) {
        cout << matches.str(1) << endl;
        str = matches.suffix().str();
    }
    string linas = "Oct 9 10:32:24 423.2.230.77:6166 Failed password for illegal user guest";
    regex reg2 ("(\\d{4,5})");
    smatch matches1;
    int i = 0;
    while (regex_search(linas, matches1, reg2)) {
        cout << matches1.str(i) << endl;
        i++;
        linas = matches.suffix().str();
    }

    for (int i = 0; i < 10; i++) {
        cout << matches1.str(i) << endl;
    }
       vector<string> ipInicial;
    string ipFinal;
    // abrimos el archivo bitacoraCorta.txt
    ListaDoble Lista;
    Node *A;
    ifstream bitacora("bitacora.txt");

    if (!bitacora.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    std::string texto;
    std::regex ipRegex("\\b(?:[0-9]{1,3}\\.){3}[0-9]{1,3}\\b"); // como funciona esto de regex?
    string linea;

    while (getline(bitacora, texto))
    { // se lee linea por linea el archivo
        smatch match;
        linea = texto;

        while (regex_search(texto, match, ipRegex))
        { // se busca la ip en la linea
            // cout << "IP encontrada: " << match[0] << endl;
            string ip_str = match[0];

            long long int NumIP = StringToLongInt(ip_str);
            Lista.create(linea, NumIP);
            texto = match.suffix();
        }
    }
