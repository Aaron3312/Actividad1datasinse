#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>

using namespace std;


struct ParrafoYIpInt // se crea la estructura tipo NODO
{
    long port; // numero que tendra cada puerto
    string texto; //texto del parrafo
};

void GetLinesAndPortFromTxT(string bitacore, int &counts,vector<ParrafoYIpInt> &ParrafoYPuertoVector)
{ // con base en el string que le introducimos es el nombre del archivo
    ifstream bitacora(bitacore);

    if (!bitacora.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
    }

    std::string texto;
    std::regex ipRegex("(\\d{4,5})");;
    string linea;

    while (getline(bitacora, texto))
    { // se lee linea por linea el archivo

        smatch match;
        linea = texto;
        while (regex_search(texto, match, ipRegex))
        { // se busca la ip en la linea
            string Port = match[0];
            cout << Port << "   ";
            cout << linea << endl;
            texto = match.suffix();
            ParrafoYPuertoVector.push_back({stoi(Port),linea});
            counts++;
        }

    }
            bitacora.close();
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}


int main(){
    vector<ParrafoYIpInt> ParrafoYPuertoVector;
    int counts = 0;
    string bitacore = "bitacoraCorta.txt";
    GetLinesAndPortFromTxT(bitacore, counts, ParrafoYPuertoVector);
    cout<<"prueba1"<<endl;
    cout<<counts<<endl;
    for (int i = 0; i < counts; i++)
    {
        cout<<ParrafoYPuertoVector[i].port<<"   "<<ParrafoYPuertoVector[i].texto<<endl;
    }
    cout<<"prueba2"<<endl;
    //ordenamiento con bubble sort por numero de puerto
    int n = counts;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-1; j++){
            if (ParrafoYPuertoVector[j].port > ParrafoYPuertoVector[j+1].port){
                swap(ParrafoYPuertoVector[j].port, ParrafoYPuertoVector[j+1].port);
                swap(ParrafoYPuertoVector[j].texto, ParrafoYPuertoVector[j+1].texto);
            }
        }
    }
    cout << "Ordenado por puerto" << endl;
    for (int i = 0; i < counts; i++)
    {
        cout<<ParrafoYPuertoVector[i].port<<"   "<<ParrafoYPuertoVector[i].texto<<endl;
    }

    cout<<"prueba3"<<endl;

    return 0;
}