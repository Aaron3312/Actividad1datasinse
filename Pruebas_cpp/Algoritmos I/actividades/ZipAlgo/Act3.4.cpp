#include <iostream>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>

using namespace std;

struct ParrafoYPuerto // se crea la estructura tipo NODO
{
    int port; // numero que tendra cada puerto
    string texto; //texto del parrafo
};

void GetLinesAndPortFromTxT(string bitacore, int &counts,vector<ParrafoYPuerto> &ParrafoYPuertoVector)
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


struct Node
{
    int key, acum;
    Node *left, *right;
    vector <string> renglones;
    Node(int d, string b):key(d), left(NULL), right(NULL), acum(1){}
};

class BST{
    private:
        Node *Root;
        void Insert(int&, string&, Node*&);
        void DeleteAll(Node*);
        
        vector <Node*> Nodos;
    public:
        BST():Root(NULL){}
        ~BST(){
            DeleteBST(Root);
            cout<<"\nDestructor: BST deleted";
        }
        void Insert(int &value, string &IP){Insert(value, IP, Root);}
        void DeleteAll(){DeleteAll(Root);}
        void Display_Tree();
        void DeleteBST(Node*&);
        void visit(int);

        void Heapify(vector<Node*>&, int);
        void Push(Node*);
        void MaxH(vector <Node*>&, int);
        bool Empty();
        void Delete();
        void Pop();
};



void BST::Insert(int &value, string &IP, Node *&currentNode){
    if (currentNode == NULL){
        currentNode = new Node(value, IP);
        currentNode->renglones.push_back(IP);
        Nodos.push_back(currentNode);
        MaxH(Nodos, Nodos.size());
    }else{
        if (value<currentNode->key)
            Insert(value, IP, currentNode->left);
        else if (value>currentNode->key)
            Insert(value, IP, currentNode->right);
        else{
            currentNode->acum += 1;
            currentNode->renglones.push_back(IP);
        }
    }
}

void BST::Display_Tree(){
    if (Root == NULL){
        cout << "El arbol esta vacio"<<endl;
        return;
    }
    
    queue<Node*> Q;
    Q.push(Root);

    queue<int> padres;
    padres.push(-1);

    queue<char> dir;
    dir.push('^');

    Node *Aux;
    while (!Q.empty()){
        Q.push(NULL);

        Aux = Q.front();
        while (Aux != NULL){
            cout << Aux->key << "(" << padres.front() << ") ";
            padres.pop();
            dir.pop();

            if(Aux->left !=NULL){
                Q.push(Aux->left);
                padres.push(Aux->key);
                dir.push('<');
            }
            if(Aux->right !=NULL){
                Q.push(Aux->right);
                padres.push(Aux->key);
                dir.push('>');
            }

            Q.pop();
            Aux = Q.front();
        }
        Q.pop();
        cout<<endl;
    }
}

void BST::DeleteBST(Node *&currentNode){
    if(!currentNode)
        return;
    DeleteBST(currentNode->left);
    DeleteBST(currentNode->right);
    delete currentNode;
}


bool BST::Empty(){
    if (Nodos.size() <= 0){
        return true;
    } else{
        return false;
    }
}

void BST::Delete(){
    if (Empty() == true){
        return;
    }
    Nodos[0] = Nodos[Nodos.size()-1];
    Nodos.pop_back();
    MaxH(Nodos, Nodos.size());
}

void BST::Heapify(vector<Node*> &hT, int i){
    int size = hT.size();

    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;

    if(l<size && hT[l]->acum > hT[largest]->acum)
        largest = l;
    if(r<size && hT[r]->acum > hT[largest]->acum)
        largest = r;
    
    if (largest != i){
        swap(hT[i], hT[largest]);
        Heapify(hT, largest);
    }
}

void BST::MaxH(vector<Node*> &hT, int size){
    for (int i = size/2 - 1; i >= 0; i--)
    {
        Heapify(hT, i);
    }
}

void BST::Push(Node *value){
    Nodos.push_back(value);
    MaxH(Nodos,Nodos.size());
}

void BST::Pop(){
    if (Empty() == true){
        cout<<"Error"<<endl;
        return;
    }
    cout<<"Puerto "<<Nodos[0]->key<<endl;
    for (int i = 0; i < Nodos[0]->renglones.size(); i++){
        cout<<Nodos[0]->renglones[i]<<endl;
    }
    Delete();
}


int main(){

    vector<ParrafoYPuerto> ParrafoYPuertoVector;
    int counts = 0;
    string bitacore = "bitacora.txt";
    GetLinesAndPortFromTxT(bitacore, counts, ParrafoYPuertoVector);

    BST A;

    for(int i = 0; i <= counts; i++){
        A.Insert(ParrafoYPuertoVector[i].port, ParrafoYPuertoVector[i].texto);
    }
    // mostramos el arbol 
    A.Display_Tree();
    cout<<"Los 5 puertos que más se repiten y sus IPs son:"<<endl;
    A.Pop();
    A.Pop();
    A.Pop();
    A.Pop();
    A.Pop();

    return 0;
}