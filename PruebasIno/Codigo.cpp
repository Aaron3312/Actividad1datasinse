#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

HANDLE hSemaphore;  // Semáforo para sincronización

// Función para simular trabajo en un proceso
void SimulateWork(const char* processName) {
    cout << processName << " iniciado. Realizando trabajo..." << endl;
    Sleep(3000);  // Simulación de trabajo
    cout << processName << " completado." << endl;
}

// Función para el proceso hijo
DWORD WINAPI ChildProcess(LPVOID lpParam) {
    WaitForSingleObject(hSemaphore, INFINITE);  // Espera al semáforo
    SimulateWork("Proceso Hijo");
    ReleaseSemaphore(hSemaphore, 1, NULL);  // Libera el semáforo
    return 0;
}

// Función para mostrar el contenido de un directorio en Windows
void ListDirectoryContents() {
    cout << "Espacio de Usuario - Comandos Básicos en Windows" << endl;
    system("dir");
}

// Función para leer y escribir en un archivo
void ReadWriteFile() {
    cout << "\nIO Management - Leer y Escribir en un Archivo en Windows" << endl;
    const char* filename = "demo.txt";
    HANDLE fileHandle = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (fileHandle != INVALID_HANDLE_VALUE) {
        const char* dataToWrite = "Hola, este es un archivo de demostracion en Windows.";
        DWORD bytesWritten;
        WriteFile(fileHandle, dataToWrite, static_cast<DWORD>(strlen(dataToWrite)), &bytesWritten, NULL);

        cout << "Datos escritos en el archivo." << endl;
        CloseHandle(fileHandle);
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
}





int main() {
    // Espacio de Usuario - Comandos Básicos
    cout << "Espacio de Usuario - Comandos Básicos en Windows" << endl;
    ListDirectoryContents();


    // Process Management - Crear un nuevo proceso
    cout << "\nProcess Management - Crear un nuevo proceso en Windows" << endl;
    STARTUPINFO si = {};
    PROCESS_INFORMATION pi = {};
    if (CreateProcess(_T("C:\\Windows\\System32\\notepad.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cout << "Proceso creado con éxito." << endl;
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        cerr << "Error al crear el proceso." << endl;
    }

    // Process Management - Sincronización de Procesos con Semáforos
    hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
    if (hSemaphore == NULL) {
        cerr << "Error al crear el semáforo." << endl;
        return 1;
    }

    // Crear proceso hijo
    HANDLE hChildThread = CreateThread(NULL, 0, ChildProcess, NULL, 0, NULL);
    if (hChildThread == NULL) {
        cerr << "Error al crear el hilo del proceso hijo." << endl;
        return 1;
    }

    // Simular trabajo en el proceso principal
    SimulateWork("Proceso Principal");

    // Esperar a que el hilo del proceso hijo termine
    WaitForSingleObject(hChildThread, INFINITE);

    // Cerrar manejadores
    CloseHandle(hChildThread);
    CloseHandle(hSemaphore);

    // IO Management - Leer y Escribir en un Archivo
    cout << "\nIO Management - Leer y Escribir en un Archivo en Windows" << endl;
    const char* filename = "demo.txt";
    HANDLE fileHandle = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (fileHandle != INVALID_HANDLE_VALUE) {
        const char* dataToWrite = "Hola, este es un archivo de demostracion en Windows.";
        DWORD bytesWritten;
        WriteFile(fileHandle, dataToWrite, static_cast<DWORD>(strlen(dataToWrite)), &bytesWritten, NULL);

        cout << "Datos escritos en el archivo." << endl;
        CloseHandle(fileHandle);
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
    ReadWriteFile();

    return 0;
}
