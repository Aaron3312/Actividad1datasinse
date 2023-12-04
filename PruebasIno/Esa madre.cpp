#include <stdio.h>
#include <string>
#include <iostream>


using namespace std;

class CPersona // Clase Persona maestra
{
public:
    string nombre;
    string apellido;
    string direccion;
    string telefono;
    string email;
    string fechaNacimiento;
    string sexo;
    string curp;
    string rfc;
    string estadoCivil;
    string nacionalidad;
    string escolaridad;
    string profesion;
    string religion;
    string tipoSangre;
    string alergias;
    string enfermedades;
    string discapacidades;
    string deportes;
    string pasatiempos;
    string idiomas;
    string habilidades;
    string referencias;
    string observaciones;
    string fechaIngreso;
    string fechaEgreso;
    string motivoEgreso;
    string puesto;
    string departamento;
    string jefeInmediato;
    string sueldo;
    string horario;
    string diasLaborales;
    string fechaInicio;
    string fechaFin;
    string institucion;
    string grado;
    string titulo;
    string cedula;
    string idioma;
    string nivel;
    string certificacion;
    string fechaCertificacion;
    string institucionCertificacion;
    string curso;
    string fechaCurso;
    string institucionCurso;
    string nombrePadre;
    string nombreMadre;
    string nombreConyuge;
    string nombreHijo;
    string nombreHermano;
    string nombreOtro;
    string parentesco;
    string fechaNacimientoFamiliar;
    string telefonoFamiliar;
    string emailFamiliar;
    string nombreEmpresa;
    string direccionEmpresa;
    string telefonoEmpresa;
    string emailEmpresa;
    string puestoEmpresa;
    string fechaIngresoEmpresa;
    string fechaEgresoEmpresa;
    string motivoEgresoEmpresa;
    string jefeInmediatoEmpresa;
    string sueldoEmpresa;
    string horarioEmpresa;
    string diasLaboralesEmpresa;
    string nombreEmpresa2;
    string direccionEmpresa2;
    string telefonoEmpresa2;
    string emailEmpresa2;
    string puestoEmpresa2;
    string fechaIngresoEmpresa2;
    string fechaEgresoEmpresa2;
    string motivoEgresoEmpresa2;
    string jefeInmediatoEmpresa2;
    string sueldoEmpresa2;
    string horarioEmpresa2;
    string diasLaboralesEmpresa2;
    string nombreEmpresa3;
    string direccionEmpresa3;
    string telefonoEmpresa3;
    string emailEmpresa3;
    string puestoEmpresa3;
    string fechaIn;
    // declaramos int year como privado
private:
    int year;

public:
    void setedad(int anios); // metodo
    int getedad();
    CPersona();  // Inicio de Constructor
    ~CPersona(); // Fin de destructor
};

CPersona::CPersona() {}
CPersona::~CPersona() {}

void CPersona::setedad(int anios)
{ // metodo
    year = anios;
}

int CPersona::getedad()
{ // metodo
    return year;
}

// Clase Cliente hija
class CCliente : CPersona
{
public:
    string rfc;
    string razonSocial;
    string direccion;
    string telefono;
    string email;
    string fechaRegistro;
    string fechaUltimaCompra;
    string tipoCliente;
    string observaciones;
    string nombreContacto;
    string telefonoContacto;
    string emailContacto;
    string nombreContacto2;
    string telefonoContacto2;
    string emailContacto2;
    string nombreContacto3;
    string telefonoContacto3;
    string emailContacto3;
    string nombreContacto4;
    string telefonoContacto4;
    string emailContacto4;
    string nombreContacto5;
    string telefonoContacto5;
    string emailContacto5;
    string nombreContacto6;
    string telefonoContacto6;
    string emailContacto6;
    string nombreContacto7;
    string telefonoContacto7;
    string emailContacto7;
    string nombreContacto8;
    string telefonoContacto8;
    string emailContacto8;
    string nombreContacto9;
    string telefonoContacto9;
    string emailContacto9;
    string nombreContacto10;
    string telefonoContacto10;
    string emailContacto10;
    string nombreContacto11;
    string telefonoContacto11;
    string emailContacto11;
    string nombreContacto12;
    string telefonoContacto12;
    string emailContacto12;
    string nombreContacto13;
    string telefonoContacto13;
    string emailContacto13;
    string nombreContacto14;
    string telefonoContacto14;
    string emailContacto14;
    string nombreContacto15;
    string telefonoContacto15;
    string emailContacto15;
    string nombreContacto16;
    string telefonoContacto16;
    string emailContacto16;
    string nombreContacto17;
    string telefonoContacto17;
    string emailContacto17;
    string nombreContacto18;
    string telefonoContacto18;
    string emailContacto18;
    string nombreContacto19;
    string telefonoContacto19;
    string emailContacto19;
    string nombreContacto20;
    string telefonoContacto20;
    string emailContacto20;
    string nombreContacto21;
    string telefonoContacto21;
    string emailContacto21;
    string nombreContacto22;
    string telefonoContacto22;
    string emailContacto22;

public:
    void registro();
    void imprimir();
    CCliente();  // Inicio de Constructor
    ~CCliente(); // Fin de destructor
};

CCliente::CCliente() {}  // Inicio de Constructor
CCliente::~CCliente() {} // Destructor

void CCliente::registro()
{
    int anios;
    std::cout << "Ingrese el nombre del apellido: ";
    cin >> nombre;
    fflush(stdin);
    std::cout << "Ingrese sexo: ";
    cin >> apellido;
    fflush(stdin);
    std::cout << "Ingrese la direccion del cliente: ";
    cin >> direccion;
    fflush(stdin);
    std::cout << "Ingrese el telefono del cliente: ";
    cin >> telefono;
    fflush(stdin);
    std::cout << "Ingrese el email del cliente: ";
    cin >> email;
    fflush(stdin);
    std::cout << "Ingrese la fecha de registro del cliente: ";
    cin >> fechaRegistro;
    fflush(stdin);
    std::cout << "Ingrese la fecha de la ultima compra del cliente: ";
    cin >> fechaUltimaCompra;
    fflush(stdin);
    std::cout << "Ingrese el tipo de cliente: ";
    cin >> tipoCliente;
    fflush(stdin);
    std::cout << "Ingrese la curp del cliente: ";
    cin >> curp;
    fflush(stdin);
    std::cout << "Ingrese el rfc del cliente: ";
    cin >> rfc;
    fflush(stdin);
    std::cout << endl;
    std::cout << endl;
    std::cout << endl;
    std::cout << "Nombre: " << nombre << endl;
    std::cout << "Apellido: " << apellido << endl;
    std::cout << "Direccion: " << direccion << endl;
    std::cout << "Telefono: " << telefono << endl;
    std::cout << "Email: " << email << endl;
    std::cout << "Fecha de registro: " << fechaRegistro << endl;
    std::cout << "CURP: " << curp << endl;
}

void CCliente::imprimir()
{
    std::cout << "Nombre: " << nombre << endl;
    std::cout << "Apellido: " << apellido << endl;
    std::cout << "Direccion: " << direccion << endl;
    std::cout << "Telefono: " << telefono << endl;
    std::cout << "Email: " << email << endl;
    std::cout << "Fecha de registro: " << fechaRegistro << endl;
    std::cout << "CURP: " << curp << endl;
}

class CEmpleado : CPersona // Clase Empleado hija
{
public:
    string fechaIngreso;
    int num_empleado;
    string puesto;

private:
    float salario;

public:
    void setsalario(int pesos);
    float getsalario();
    void registro();
    void imprimir();
    CEmpleado();
    ~CEmpleado();
};

CEmpleado::CEmpleado() {}  // Inicio de Constructor
CEmpleado::~CEmpleado() {} // Destructor

void CEmpleado::registro()
{
    int anios;
    std::cout << "Ingrese el nombre del empleado: ";
    cin >> nombre;
    fflush(stdin);
    std::cout << "Ingrese el apellido del empleado: ";
    cin >> apellido;
    fflush(stdin);
    std::cout << "Ingrese la direccion del empleado: ";
    cin >> direccion;
    fflush(stdin);
    std::cout << "Ingrese el telefono del empleado: ";
    cin >> telefono;
    fflush(stdin);
    std::cout << "Ingrese el email del empleado: ";
    cin >> email;
    fflush(stdin);
    std::cout << "Ingrese la fecha de nacimiento del empleado: ";
    cin >> fechaNacimiento;
    fflush(stdin);
    std::cout << "Ingrese el sexo del empleado: ";
    cin >> sexo;
    fflush(stdin);
    std::cout << "Ingrese la curp del empleado: ";
    cin >> curp;
    fflush(stdin);
    std::cout << "Ingrese el rfc del empleado: ";
    cin >> rfc;
    fflush(stdin);
    std::cout << "Ingrese el estado civil del empleado: ";
    cin >> estadoCivil;
    fflush(stdin);
    std::cout << "Ingrese la nacionalidad del empleado: ";
    cin >> nacionalidad;
    fflush(stdin);
    std::cout << "Ingrese la escolaridad del empleado: ";
    cin >> escolaridad;
    fflush(stdin);
    std::cout << "Ingrese la profesion del empleado: ";
    cin >> profesion;
    fflush(stdin);
    std::cout << "Ingrese la religion del empleado: ";
    cin >> religion;
    fflush(stdin);
    std::cout << "Ingrese el tipo de sangre del empleado: ";
    cin >> tipoSangre;
    fflush(stdin);
    std::cout << "Ingrese las alergias del empleado: ";
    cin >> alergias;
    fflush(stdin);
    std::cout << "Ingrese las enfermedades del empleado: ";
    cin >> enfermedades;
    fflush(stdin);
    std::cout << "Ingrese las discapacidades del empleado: ";
    cin >> discapacidades;
    fflush(stdin);
    std::cout << "Ingrese los deportes del empleado: ";
    cin >> deportes;
    fflush(stdin);
    std::cout << "Ingrese los pasatiempos del empleado: ";
    cin >> pasatiempos;
    fflush(stdin);
    std::cout << "Ingrese los idiomas del empleado: ";
    cin >> idiomas;
    fflush(stdin);
    std::cout << "Ingrese las habilidades del empleado: ";
    cin >> habilidades;
    std::cout << endl;
    std::cout << endl;
    std::cout << endl;
    std::cout << "Nombre: " << nombre << endl;
    std::cout << "Apellido: " << apellido << endl;
    std::cout << "Direccion: " << direccion << endl;
    std::cout << "Telefono: " << telefono << endl;
    std::cout << "Email: " << email << endl;
    std::cout << "Fecha de nacimiento: " << fechaNacimiento << endl;
    std::cout << "Sexo: " << sexo << endl;
    std::cout << "CURP: " << curp << endl;
}

int main() // aqui inicia el programa
{
    CCliente clientl;
    clientl.registro();

    system("pause");
    cout << endl;

    CEmpleado empleadol;
    empleadol.registro();
    system("pause");
    return 0;
};
