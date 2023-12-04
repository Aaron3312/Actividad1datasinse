#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define una clase base “Persona” con los atributos generales de una persona.
// Identifica por lo menos 3 atributos para la clase.
class Persona
{
private:
    string nombre;
    string apellido;
    int edad;

public:
    Persona(string, string, int);
    void setNombre(string);
    void setApellido(string);
    void setEdad(int);
    string getNombre();
    string getApellido();
    int getEdad();
};

Persona::Persona(string _nombre, string _apellido, int _edad)
{
    nombre = _nombre;
    apellido = _apellido;
    edad = _edad;
}

void Persona::setNombre(string _nombre)
{
    nombre = _nombre;
}

void Persona::setApellido(string _apellido)
{
    apellido = _apellido;
}

void Persona::setEdad(int _edad)
{
    edad = _edad;
}

string Persona::getNombre()
{
    return nombre;
}

string Persona::getApellido()
{
    return apellido;
}

int Persona::getEdad()
{
    return edad;
}

// Establece 2 clases derivadas que hereden de tu clase Persona. Estas clases
// son Cliente y Empleado. Identifica por lo menos 3 atributos específicos para cada clase.
//
// Para cada una de las clases hijas define un método registro, que reciba como
// parámetros los atributos de la clase y los asigne a los miembros privados.
class Cliente : public Persona
{
private:
    string direccion;
    string telefono;
    string email;

public:
    Cliente(string, string, int, string, string, string);
    void setDireccion(string);
    void setTelefono(string);
    void setEmail(string);
    string getDireccion();
    string getTelefono();
    string getEmail();
    void registro(string, string, int, string, string, string);
};

Cliente::Cliente(string _nombre, string _apellido, int _edad, string _direccion, string _telefono, string _email) : Persona(_nombre, _apellido, _edad)
{
    direccion = _direccion;
    telefono = _telefono;
    email = _email;
}

void Cliente::setDireccion(string _direccion)
{
    direccion = _direccion;
}

void Cliente::setTelefono(string _telefono)
{
    telefono = _telefono;
}

void Cliente::setEmail(string _email)
{
    email = _email;
}

string Cliente::getDireccion()
{
    return direccion;
}

string Cliente::getTelefono()
{
    return telefono;
}

string Cliente::getEmail()
{
    return email;
}

void Cliente::registro(string _nombre, string _apellido, int _edad, string _direccion, string _telefono, string _email)
{
    setNombre(_nombre);
    setApellido(_apellido);
    setEdad(_edad);
    setDireccion(_direccion);
    setTelefono(_telefono);
    setEmail(_email);
}

class Empleado : public Persona
{
private:
    string puesto;
    string direccion;
    string telefono;

public:
    Empleado(string, string, int, string, string, string);
    void setPuesto(string);
    void setDireccion(string);
    void setTelefono(string);
    string getPuesto();
    string getDireccion();
    string getTelefono();
    void registro(string, string, int, string, string, string);
};

Empleado::Empleado(string _nombre, string _apellido, int _edad, string _puesto, string _direccion, string _telefono) : Persona(_nombre, _apellido, _edad)
{
    puesto = _puesto;
    direccion = _direccion;
    telefono = _telefono;
}

void Empleado::setPuesto(string _puesto)
{
    puesto = _puesto;
}

void Empleado::setDireccion(string _direccion)
{
    direccion = _direccion;
}

void Empleado::setTelefono(string _telefono)
{
    telefono = _telefono;
}

string Empleado::getPuesto()
{
    return puesto;
}

string Empleado::getDireccion()
{
    return direccion;
}

string Empleado::getTelefono()
{
    return telefono;
}

void Empleado::registro(string _nombre, string _apellido, int _edad, string _puesto, string _direccion, string _telefono)
{
    setNombre(_nombre);
    setApellido(_apellido);
    setEdad(_edad);
    setPuesto(_puesto);
    setDireccion(_direccion);
    setTelefono(_telefono);
}

// En la función principal de tu programa main () solicita la captura de un cliente y un
// empleado y después imprime en pantalla los datos registrados.

int main()
{
    string nombre;
    string apellido;
    int edad;
    string direccion;
    string telefono;
    string email;
    string puesto;

    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;
    cout << "Ingrese el apellido del cliente: ";
    cin >> apellido;
    cout << "Ingrese la edad del cliente: ";
    cin >> edad;
    cout << "Ingrese la direccion del cliente: ";
    cin >> direccion;
    cout << "Ingrese el telefono del cliente: ";
    cin >> telefono;
    cout << "Ingrese el email del cliente: ";
    cin >> email;

    Cliente cliente(nombre, apellido, edad, direccion, telefono, email);

    cout << "Ingrese el nombre del empleado: ";
    cin >> nombre;
    cout << "Ingrese el apellido del empleado: ";
    cin >> apellido;
    cout << "Ingrese la edad del empleado: ";
    cin >> edad;
    cout << "Ingrese el puesto del empleado: ";
    cin >> puesto;
    cout << "Ingrese la direccion del empleado: ";
    cin >> direccion;
    cout << "Ingrese el telefono del empleado: ";
    cin >> telefono;

    Empleado empleado(nombre, apellido, edad, puesto, direccion, telefono);

    cout << "Datos del cliente: " << endl;
    cout << "Nombre: " << cliente.getNombre() << endl;
    cout << "Apellido: " << cliente.getApellido() << endl;
    cout << "Edad: " << cliente.getEdad() << endl;
    cout << "Direccion: " << cliente.getDireccion() << endl;
    cout << "Telefono: " << cliente.getTelefono() << endl;
    cout << "Email: " << cliente.getEmail() << endl;

    cout << "Datos del empleado: " << endl;
    cout << "Nombre: " << empleado.getNombre() << endl;
    cout << "Apellido: " << empleado.getApellido() << endl;
    cout << "Edad: " << empleado.getEdad() << endl;
    cout << "Puesto: " << empleado.getPuesto() << endl;
    cout << "Direccion: " << empleado.getDireccion() << endl;
    cout << "Telefono: " << empleado.getTelefono() << endl;

    return 0;
}
