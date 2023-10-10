#include <iostream>
#include <vector>

using namespace std;

// Nodo La clase nodo es una clase que contiene un entero data y dos punteros a nodos, uno para el nodo izquierdo y otro para el nodo derecho.
struct Node
{
    int data;
    Node *right;
    Node *left;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

// Clase BST La clase BST es una clase que contiene un puntero a un nodo raíz y una función insert
//  que se encarga de insertar un nuevo nodo en el árbol binario de búsqueda.
class BST
{
private:
    vector<int> vect; // Vector que contiene los ancestros
    Node *Root; // Puntero a la raiz del arbol
    int height(Node *); // Funcion que calcula la altura del arbol
    void ancestors(Node *, int, vector<int>); // Funcion que calcula los ancestros de un valor dado
    int whatlevelamI(Node *, int, int); // Funcion que calcula el nivel de un valor dado
    void DeleteAll(Node *); // Funcion que elimina todos los nodos del arbol
    void insert(int &, Node *&); // Funcion que inserta un nuevo nodo en el arbol
    void preOrder(Node *); // Funcion que recorre el arbol en preOrder
    void inOrder(Node *); // Funcion que recorre el arbol en inOrder
    void postOrder(Node *); // Funcion que recorre el arbol en postOrder
    void levelByLevel(Node *); // Funcion que recorre el arbol por niveles

public:
    void ancestors(int valor) { ancestors(Root, valor, vect); } 
    int whatlevelamI(int valor) { return whatlevelamI(Root, valor, 0); }
    void DeleteAll() { DeleteAll(Root); }
    void insert(int &valor) { insert(valor, Root); }
    void visit(int val);
    void inOrder() { inOrder(Root); }
    void postOrder() { postOrder(Root); }
    BST() : Root(NULL) {}
    ~BST() { cout << "DestructorActivated"<<endl;
    DeleteAll(Root); }
    void preOrder() { preOrder(Root); }
    void levelByLevel() { levelByLevel(Root); }
    int height() { return height(Root); }
};

// Insert Function La función insert es una función de la clase BST que se encarga de insertar un nuevo nodo en el árbol binario de búsqueda.
//  Toma como parámetros una referencia a un entero valor y un puntero a un nodo currentNode. Si el puntero currentNode es nulo,
//  se crea un nuevo nodo con el valor valor. Si el valor valor es menor que el valor del nodo actual,
// se llama a la función insert recursivamente con el nodo izquierdo del nodo actual.
void BST::insert(int &valor, Node *&currentNode) //La complejidad de la funcion es O(n)
{
    if (currentNode == NULL)
        currentNode = new Node(valor);
    else
    {
        if (valor < currentNode->data)
            insert(valor, currentNode->left);
        else if (valor > currentNode->data)
            insert(valor, currentNode->right);
        else
            cout << "The value exist in the tree" << endl;
    }
}

// Funcion Visit La función visit es una función de la clase BST que se encarga de imprimir el árbol binario de búsqueda.
void BST::visit(int val) //La complejidad de la funcion es O(n)
{
    cout << "Visit Function" << endl;
    switch (val)
    {
    case 1:
        cout << "preOrder" << endl;
        preOrder();
        return;
    case 2:
        cout << "InOrder" << endl;
        inOrder();
        return;
    case 3:
        cout << "PostOrder" << endl;
        postOrder();
        return;
    case 4:
        cout << "LevelByLevel" << endl;
        levelByLevel();
        return;
    default:
        cout << "No valid option" << endl;
    }
}
// Funcion preOrder La función preOrder es una función de la clase BST que se encarga de imprimir el árbol binario de búsqueda en preOrder.
void BST::preOrder(Node *currentNode)   
{ // subFuncion preOrder
    if (currentNode != NULL) 
    {
        cout << currentNode->data << " ";
        preOrder(currentNode->left);
        preOrder(currentNode->right);
    }
}
// Funcion inOrder La función inOrder es una función de la clase BST que se encarga de imprimir el árbol binario de búsqueda en inOrder.
void BST::inOrder(Node *currentNode)
{ // subFuncion inOrder
    if (currentNode != NULL)
    {
        inOrder(currentNode->left);
        cout << currentNode->data << " ";
        inOrder(currentNode->right);
    }
}
// Funcion postOrder La función postOrder es una función de la clase BST que se encarga de imprimir el árbol binario de búsqueda en postOrder.
void BST::postOrder(Node *currentNode)
{ // subFuncion postOrder
    if (currentNode != NULL)
    {
        postOrder(currentNode->left);
        postOrder(currentNode->right);
        cout << currentNode->data << " ";
    }
}
// Funcion levelByLevel La función levelByLevel es una función de la clase BST que se encarga de imprimir el árbol binario de búsqueda por niveles.
void BST::levelByLevel(Node *currentNode)
{ // subFuncion levelByLevel
    if (currentNode != NULL)
    {
        cout << currentNode->data << " ";
        levelByLevel(currentNode->left);
        levelByLevel(currentNode->right);
    }
}

// Funcion Height La función Height es una función de la clase BST que se encarga de calcular la altura del árbol binario de búsqueda.
int BST::height(Node *currentNode) //La complejidad de la funcion es O(n)
{
    if (currentNode == NULL)
    {
        return 0;
    }
    else
    {
        int leftHeight = height(currentNode->left);
        int rightHeight = height(currentNode->right);
        if (leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
}

// Funcion Ancestors La función Ancestors es una función de la clase BST que se encarga de imprimir los ancestros de un valor dado.
void BST::ancestors(Node *currentNode, int valor, vector<int> vect)  //La complejidad de la funcion es O(n)
{
    if (currentNode == NULL){
        cout << "The value doesn't exist in the tree" << endl;
        return;
    }
    else{
        vect.push_back(currentNode->data);
        if (valor == currentNode->data){
            for (int i = 0; i < vect.size() - 1; i++)
                cout << vect[i] << " ";
            return;
        }
        else if (valor < currentNode->data)
            ancestors(currentNode->left, valor, vect);
        else if (valor > currentNode->data)
            ancestors(currentNode->right, valor, vect);
    }
}

// Funcion whatlevelamI The function whatlevelamI is a member function of the BST class in the Act3.1.cpp file. It takes three parameters: a pointer to a Node object
int BST::whatlevelamI(Node *currentNode, int value, int level) //La complejidad de la funcion es O(n)
{
    if (currentNode == NULL)
        return -1;
    else
    {
        if (value == currentNode->data)
            return level;
        else if (value < currentNode->data)
            return whatlevelamI(currentNode->left, value, level + 1);
        else if (value > currentNode->data)
            return whatlevelamI(currentNode->right, value, level + 1);
    }
    return -1;
}

// Funcion DeleteAll La función DeleteAll es una función de la clase BST que se encarga de eliminar todos los nodos del árbol binario de búsqueda.
void BST::DeleteAll(Node *currentNode) //La complejidad de la funcion es O(n)
{
    if (currentNode != NULL)
    {
        DeleteAll(currentNode->left);
        DeleteAll(currentNode->right);
        delete currentNode;
    }
}

int main()
{

    //First case a tree with only one node
    cout << "First case" << endl;
    BST A1;
    vector<int> v1 = {3};
    A1.insert(v1[0]);
    A1.visit(1);
    A1.visit(2);
    A1.visit(3);
    A1.visit(4);
    cout << "Tree's tall: " << A1.height() << endl;
    cout << "Ancesters of the value 3:";
    A1.ancestors(3);
    cout << "\nLevel of the 3 value: " << A1.whatlevelamI(3) << endl;

       // Second case a tree already ordered
    cout << "Second case" << endl;
    BST A2;
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7};
    for (int i : v2)
    {
        A2.insert(i);
    }
    A2.visit(1);
    A2.visit(2);
    A2.visit(3);
    A2.visit(4);
    cout << "Tree's tall: " << A2.height() << endl;
    cout << "Ancesters of the value 3: ";
    A2.ancestors(3);
    cout << "\nLevel of the 5 value: " << A2.whatlevelamI(5) << endl;

    // Third case a tree with 7 nodes (some repeated and some values that don't exist)
    cout << "Third case" << endl;
    BST A3;
    vector<int> v3 = {7, 2, 10, 2, 9, 3, 7};
    for (int i : v3)
    {
        A3.insert(i);
    }
    A3.visit(1);
    A3.visit(2);
    A3.visit(3);
    A3.visit(4);
    cout << "\nTall of the tree: " << A3.height() << endl;
    cout << "\nAncestros del valor 4: ";
    A3.ancestors(4);
    cout << "\nLevel of the value 2: " << A3.whatlevelamI(2) << endl;

    // Fourth case a tree with 7 nodes (none repeated and all values exist)
    cout << "Fourth Case" << endl;
    BST A4;
    vector<int> v4 = {12, 1, 6, 9, 3, 5, 2};
    for (int i : v4)
    {
        A4.insert(i);
    }
    A4.visit(1);
    A4.visit(2);
    A4.visit(3);
    A4.visit(4);
    cout << "Tree's tall: " << A4.height() << endl;
    cout << "Ancesters of the value 4:";
    A4.ancestors(4);
    cout << "\nLevel of value 3: " << A4.whatlevelamI(3) << endl;

    return 0;
}