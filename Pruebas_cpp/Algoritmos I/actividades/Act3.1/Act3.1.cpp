#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
class BST{
    private:
        Node* Root;
        void insert (int&, Node*&);
        void preOrder (Node*);
        void inOrder (Node*);
        void postOrder(Node*);
        void levelByLevel(Node*);
        int height(Node*);
        void ancestors(Node*, int);
        int whatlevelamI(Node*, int, int);
    public:
        void insert(int &value) { insert(value, Root); }
        void visit(int num);
        void preOrder() { preOrder(Root); }
        void inOrder() { inOrder(Root); }
        void postOrder() { postOrder(Root); }
        void levelByLevel() { levelByLevel(Root); }
        int height() { return height(Root); }
        void ancestors(int value) { ancestors(Root, value); }
        int whatlevelamI(int value) { return whatlevelamI(Root, value, 0); }
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
void BST::ancestors(Node* currentNode, int value){
    if (currentNode == NULL)
        cout << "El arbol esta vacio" << endl;
    else{
        if (value < currentNode->data){
            cout << currentNode->data << " ";
            ancestors(currentNode->left, value);
        }
        else if (value > currentNode->data){
            cout << currentNode->data << " ";
            ancestors(currentNode->right, value);
        }
    }
}

//Funcion whatlevelamI, si el valor no existe regresa -1
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
}
int main(){
    BST A;
    vector <int> v = {5, 3, 2, 4, 7, 6, 7};
    for (int i : v){
        A.insert(i);
    }
    A.visit(1);
    A.visit(2);
    A.visit(3);
    A.visit(4);
    cout << "\nAltura del arbol: " << A.height() << endl;
    cout << "Ancestros del valor 6: ";
    A.ancestors(6);
    cout << "\nNivel del valor 6: " << A.whatlevelamI(6) << endl;
    return 0;
}