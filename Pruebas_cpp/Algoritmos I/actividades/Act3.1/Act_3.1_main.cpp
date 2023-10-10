#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(NULL), right(NULL) {}
};
class BST{
    private:
        vector<int> vect;
        Node* Root;
        void insert (int&, Node*&);
        void preOrder (Node*);
        void inOrder (Node*);
        void postOrder(Node*);
        void levelByLevel(Node*);
        int height(Node*);
        void ancestors(Node*, int, vector<int>);
        int whatlevelamI(Node*, int, int);
        void DeleteAll(Node*) ;
    public:
        BST() : Root(NULL) {}
        ~BST() {
            cout << "~Destructor" << endl;
            DeleteAll(Root);
        }
        void insert(int &value) { insert(value, Root); }
        void visit(int num);
        void preOrder() { preOrder(Root); }
        void inOrder() { inOrder(Root); }
        void postOrder() { postOrder(Root); }
        void levelByLevel() { levelByLevel(Root); }
        int height() { return height(Root); }
        void ancestors(int value) { ancestors(Root, value, vect); }
        int whatlevelamI(int value) { return whatlevelamI(Root, value, 0); }
        void DeleteAll() { DeleteAll(Root); }
};

//Funcion Insert
void BST::insert(int &value, Node* &currentNode){
    if (currentNode == NULL)
        currentNode = new Node(value);
    else{
        if (value < currentNode->data)
            insert(value, currentNode->left);
        else if (value > currentNode->data)
            insert(value, currentNode->right);
        else
            cout << "\nEl valor ya existe" << endl;
    }
}

//Funcion Visit
void BST::visit(int num){
    cout<<"\nVisit..."<<endl;
    switch(num){
        case 1: 
            cout<<"preOrder"<<endl;
            preOrder();
            return;
        case 2: 
            cout<<"InOrder"<<endl;
            inOrder();
            return;
        case 3: 
            cout<<"PostOrder"<<endl;
            postOrder();
            return;
        case 4: 
            cout<<"LevelByLevel"<<endl;
            levelByLevel();
            return;
        default: cout<<"Opcion no valida"<<endl;
    }
}
void BST::preOrder(Node* currentNode){      //subFuncion preOrder
    if (currentNode != NULL){
        cout << currentNode->data << " ";
        preOrder(currentNode->left);
        preOrder(currentNode->right);
    }
}   
void BST::inOrder(Node* currentNode){       //subFuncion inOrder
    if (currentNode != NULL){
        inOrder(currentNode->left);
        cout << currentNode->data << " ";
        inOrder(currentNode->right);
    }
}
void BST::postOrder(Node* currentNode){    //subFuncion postOrder
    if (currentNode != NULL){
        postOrder(currentNode->left);
        postOrder(currentNode->right);
        cout << currentNode->data << " ";
    }
}
void BST::levelByLevel(Node* currentNode){ //subFuncion levelByLevel
    if (currentNode != NULL){
        cout << currentNode->data << " ";
        levelByLevel(currentNode->left);
        levelByLevel(currentNode->right);
    }
}

//Funcion Height
int BST::height(Node* currentNode){
    if (currentNode == NULL){
        return 0;
    }
    else{
        int leftHeight = height(currentNode->left);
        int rightHeight = height(currentNode->right);
        if (leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
}

//Funcion Ancestors
void BST::ancestors(Node* currentNode, int value, vector<int> vect){
    if (currentNode == NULL)
        return;
    else{
        vect.push_back(currentNode->data);
        if (value == currentNode->data){
            for (int i = 0; i < vect.size() - 1; i++)
                cout << vect[i] << " ";
            return;
        }
        else if (value < currentNode->data)
            ancestors(currentNode->left, value, vect);
        else if (value > currentNode->data)
            ancestors(currentNode->right, value, vect);
    }
}

//Funcion whatlevelamI
int BST::whatlevelamI(Node* currentNode, int value, int level){
    if (currentNode == NULL)
        return -1;
    else{
        if (value == currentNode->data)
            return level;
        else if (value < currentNode->data)
            return whatlevelamI(currentNode->left, value, level + 1);
        else if (value > currentNode->data)
            return whatlevelamI(currentNode->right, value, level + 1);
    }
    return -1;
}

//Funcion DeleteAll
void BST::DeleteAll(Node* currentNode){
    if (currentNode != NULL){
        DeleteAll(currentNode->left);
        DeleteAll(currentNode->right);
        delete currentNode;
    }
}

int main(){
    //Pruebas
    //---------------Primer caso-------------------//
    //Un arbol con 7 nodos (1 repetido y un valor que no existe) 
    cout<<"Primer caso"<<endl;
    BST A1;
    vector <int> v1 = {5, 3, 2, 4, 7, 6, 7};
    for (int i : v1){
        A1.insert(i);
    }
    A1.visit(1);
    A1.visit(2);
    A1.visit(3);
    A1.visit(4);
    cout << "\nAltura del arbol: " << A1.height() << endl;
    cout << "Ancestros del valor 8: ";
    A1.ancestors(8);
    cout << "\nNivel del valor 6: " << A1.whatlevelamI(6) << endl;
    
    //---------------Segundo caso-------------------//
    //Un arbol con 7 nodos (ninguno repetido y todos los valores existen) 
    cout<<"\nSegundo caso"<<endl;
    BST A2;
    vector <int> v2 = {5, 3, 2, 4, 7, 6, 8};
    for (int i : v2){
        A2.insert(i);
    }
    A2.visit(1);
    A2.visit(2);
    A2.visit(3);
    A2.visit(4);
    cout << "\nAltura del arbol: " << A2.height() << endl;
    cout << "Ancestros del valor 4: ";
    A2.ancestors(4);
    cout << "\nNivel del valor 4: " << A2.whatlevelamI(8) << endl;

    //---------------Tercer caso-------------------//
    //Un arbol con 1 solo nodo
    cout<<"\nTercer caso"<<endl;
    BST A3;
    vector <int> v3 = {9};
    A3.insert(v3[0]);
    A3.visit(1);
    A3.visit(2);
    A3.visit(3);
    A3.visit(4);
    cout << "\nAltura del arbol: " << A3.height() << endl;
    cout << "Ancestros del valor 9: ";
    A3.ancestors(9);
    cout << "\nNivel del valor 9: " << A3.whatlevelamI(9) << endl;

    //---------------Cuarto caso-------------------//
    //Un arbol ya ordenado 
    cout<<"\nCuarto caso"<<endl;
    BST A4;
    vector <int> v4 = {1, 2, 3, 4, 5, 6, 7};
    for (int i : v4){
        A4.insert(i);
    }
    A4.visit(1);
    A4.visit(2);
    A4.visit(3);
    cout << "\nAltura del arbol: " << A4.height() << endl;
    cout << "Ancestros del valor 5: ";
    A4.ancestors(5);
    cout << "\nNivel del valor 7: " << A4.whatlevelamI(7) << endl;

    return 0;
}
