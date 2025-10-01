#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <vector> 

using namespace std;

struct Nodo {
    string nombre;
    string carrera;
    float promedio;
    Nodo* siguiente;


    // Checkeo de cola
    bool cola_vacia(int TOPE, bool &BAND) {   
        if (TOPE == 0) {
            BAND = true; // La cola esta vacia
        } else {
            BAND = false; // La cola NO esta vacia
        }
        return BAND;
    }

    bool cola_llena(int TOPE, int MAX, bool &BAND) {   // Siempre devuelve falso por ser lista dinámica
        if (TOPE == MAX){
            BAND = true; // La cola esta llena
        } else {
            BAND = false; // La cola NO esta llena
        }
        return BAND;
    }


    // Insertar_cola y Eliminar_cola [FIFO]*** AUN NO ES FIFO
    void Insertar_cola(bool &BAND, int &TOPE, int MAX, string cola[], string DATO) { 
        cola_llena(TOPE, MAX, BAND); // Revisa si se pueden agregar mas datos
        if (BAND == true) {
            cout << "x+ Desbordamiento, cola llena +x\n";
        } else if (BAND == false) { // Si se comprueba que no esta llena...
            TOPE += 1; // Aumenta el tope...
            cola[TOPE] = DATO; // Y se agrega el DATO del usuario
            cout << "+ Agregado: \"" << DATO << "\"\n";
        }
    }

    string Eliminar_cola(string cola[], int &TOPE, bool &BAND) { 
        cola_vacia(TOPE, BAND); // Revisa si se pueden eliminar datos
        if (BAND == true) {
            cout << "x+ Subdesbordamiento, cola vacia +x\n";
            return "";
        } else if (BAND == false) { // Si se comprueba que no esta vacia...
            string DATO = cola[TOPE]; // Guarda el ultimo dato...
            TOPE -= 1; // Se reduce el tope...
            cout << "- Retirado: \"" << DATO << "\"\n"; // Y se muestra cual era el ultimo dato
            return DATO; // Se devuelve el dato retirado (en caso de que se necesite, aunque en este caso especificamente no lo necesitamos asi que se podria hacer que esta funcion sea void en vez de int)
        }
        return ""; 
    }


    // Mostrar los valores dentro de la cola
    void Mostrar(string cola[], int TOPE) {
        if (TOPE == 0) {
            cout << "\nx+ La cola esta vacia +x\n";
        } else {
            cout << "\n> Contenido de la cola:\n [ ";
            for (int i = TOPE; i >= 1; i--) {
                cout << cola[i] << " ";
            }
            cout << "]" << endl;
        }
    }
};


// Control de entrada para evitar errores
int control_int() { // Con int
    int value;
    while (true){
        cin >> value;
        if (!cin) {
        cout << "x+ Solo se permiten numeros : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
        } else {
            return value;
        }
    }
}

float control_float() { // Con float
    float value;
    while (true){
        cin >> value;
        if (!cin) {
        cout << "x+ Solo se permiten numeros : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
        } else {
            return value;
        }
    }
}


// Menu de opciones
int menu() {
    int opcion = 0;
    cout << "++++++++++++\nMenu\n";
    cout << "1. Insertar un nuevo estudiante en la cola.\n"; // Insertar_cola
    cout << "2. Eliminar estudiante al frente de la cola\n"; // Eliminar_cola
    cout << "3. Mostrar contenidos de la cola\n"; // Mostrar_cola
    cout << "4. Salir\n++++++++++++\n";
    cout << "> Seleccione una opcion: ";
    opcion = control_int();
    while (opcion < 1 || opcion > 4) {
        cout << "[Debe elegir una opcion valida (1-4)] : ";
        opcion = control_int();
    }
    return opcion;
}

// El main
int main() {
    /*
    // Se asigna en un vector el numero de cola de Nodoes
    vector<Nodo> cola(colas_Nodoes);

    // Se crean listas vacias, asignandoles el band false y el maximo de Nodoes por cola como la cantidad que el usuario coloco
    for (int i = 0; i < colas_Nodoes; i++) {
        cola[i].MAX = cantidad_Nodoes;
        cola[i].TOPE = 0;
        cola[i].BAND = false;
    }*/

    int opcion;
    

    // Se ven las opciones del menu
    while (opcion != 4) {
        opcion = menu();

        switch (opcion) {
            case 1: // Insertar_cola
                // static int contador_global = 0;
                
                break;

            case 2: // Eliminar_cola
                
                break; 

            case 3: // Mostrar_cola
            
                break;

            case 4: // Salir
                cout << "> Saliendo del programa...\n";
                //cola.clear(); // Borrar memoria
                break;

            default:
                cout << "x+ Opcion no valida. Intente de nuevo +x.\n";
        }
    } 

    return 0;
}