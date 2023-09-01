    
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(){
    ifstream archivo;
    string linea;
    archivo.open("bitacora.txt");
    vector<int> meses;
    string mes;
    int aux;
    while (getline(archivo, linea))
    {
        mes = linea.substr(0, 3);
        if (mes == "Jan"){aux = 1;}
        if (mes == "Feb"){aux = 2;}
        if (mes == "Mar"){aux = 3;}
        if (mes == "Apr"){aux = 4;}
        if (mes == "May"){aux = 5;}
        if (mes == "Jun"){aux = 6;}
        if (mes == "Jul"){aux = 7;}
        if (mes == "Aug"){aux = 8;}
        if (mes == "Sep"){aux = 9;}
        if (mes == "Oct"){aux = 10;}
        if (mes == "Nov"){aux = 11;}
        if (mes == "Dec"){aux = 12;}

        meses.push_back(aux);
    }
    //sacamos los meses a consola
    for (int i = 0; i < meses.size(); i++)
    {
        cout << meses[i] << endl;
    }
}