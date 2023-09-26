// Name: Aaron Hernandez Jimenez - A01642529
// Date: 25/09/2023
// Act 2.1 - Implementación de un ADT de estructura de datos lineales (lista doblemente-ligada)

#include <iostream>

using namespace std;
void Add(int);

struct Node
{
    int Id;
    Node *before;
    Node *next;
};

class DoubleList
{
private:
    Node *I, *F, *T, *aux;

public:
    DoubleList() : I(NULL) {}
    void create(int);
    Node *read(int);
    void update(int, int);
    void dell(int);
    void present_I();
    void present_F();
};

void DoubleList::create(int x)
{
    T = new Node();
    T->Id = x;
    T->next = NULL;
    T->before = NULL;

    if (I == NULL)
    {
        I = T;
        F = T;
    }
    else if (I->Id > T->Id)
    {
        I->before = T;
        T->next = I;
        I = T;
    }
    else if (T->Id > F->Id)
    {
        F->next = T;
        T->before = F;
        F = T;
    }
    else if (T->Id > I->Id && T->Id < F->Id)
    {
        aux = I;
        while (aux->Id < T->Id)
        {
            aux = aux->next;
        }
        T->before = aux->before;
        T->next = aux;
        aux->before = T;
        aux = T->before;
        aux->next = T;
    }
}

Node *DoubleList::read(int x)
{
    T = I;

    if (I == NULL)
    {
        cout << "empty list" << endl;
    }
    while (T != NULL && T->Id != x)
    {
        T = T->next;
    }

    if (T == NULL)
    {
        cout << "The number is not found" << endl;
    }
    return T;
}

void DoubleList::dell(int busq)
{
    T = read(busq);

    if (T == NULL)
    {
        cout << "The operation can't be completed" << endl;
        return;
    }
    aux = T->before;
    aux->next = T->next;
    aux = T->next;
    aux->before = T->before;
    delete T;
}

void DoubleList::update(int x, int mod)
{
    dell(x);
    create(mod);
}

void DoubleList::present_I()
{
    T = I;
    while (T != NULL)
    {
        cout << "ID: " << T->Id << endl;
        T = T->next;
    }
}

void DoubleList::present_F()
{
    T = F;
    while (T != NULL)
    {
        cout << "ID: " << T->Id << endl;
        T = T->before;
    }
}

int main()
{
    DoubleList List;
    Node *A;
    for (int i = 1; i < 10; i++)
    {
        List.create(i * 10);
    }
    List.create(1);
    List.create(100);
    List.create(55);
    cout << "Present from the begining" << endl;
    List.present_I();
    cout << "Present from the end" << endl;
    List.present_F();
    A = List.read(50);
    cout << A->Id << endl;
    List.dell(30);
    cout << "Present list whit the 30th deleted" << endl;
    List.present_F();
    List.update(20, 25);
    cout << "Present list whit the 20th value change whit 25" << endl;
    List.present_F();
    return 0;
}
