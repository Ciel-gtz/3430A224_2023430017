#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Nodo {
    string nombre;
    string carrera;
    float promedio;
    Nodo* siguiente;
};

// Checkeo de cola VACIA y LLENA
bool checkColaVacia(Nodo* frente) {
    if (frente == nullptr) {
        // cola vacia
        return true;
    } else {  
        // cola con al menos 1 elemento
        return false;
    }
}

bool checkColaLlena(){
    return false;
}


// insertarCola y eliminarCola [FIFO]
void insertarCola(Nodo*& frente, Nodo*& fin, string nombre, string carrera, float promedio) {
    Nodo* nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->carrera = carrera;
    nuevo->promedio = promedio;
    nuevo->siguiente = nullptr;

    // Si la cola esta vacia: el nodo es frente y fin
    if (fin == nullptr) {
        frente = fin = nuevo;
    } 
    // si no: se agrega al final.
    else {
        fin->siguiente = nuevo;
        fin = nuevo;
    }

    cout << "\t+ Se ha agregado '" << nombre << "' a la cola +\n";
}

void eliminarCola(Nodo*& frente, Nodo*& fin, string& nombre, string& carrera, float& promedio) {
    Nodo* nodoActual = frente;
    nombre = nodoActual->nombre;
    carrera = nodoActual->carrera;
    promedio = nodoActual->promedio;
    frente = nodoActual->siguiente;

    // esta parte de la cola ahora queda disponible
    if (frente == nullptr) {
        fin = nullptr; 
    }

    delete nodoActual;
}


// Mostrar lo presente en cola
void mostrarCola(Nodo* frente) {
    cout << "\n> Contenido actual de la cola :\n";
    int indice = 1;
    Nodo* actual = frente;

    // Header
    cout << "\tn°: [  nombre  ;  carrera  ;  promedio  ]" << endl;

    // Imprime la info
    while (actual != nullptr) {
        cout << "\t" << indice << " : [ '" << actual->nombre << "' ;  '" << actual->carrera << "'  ; '" << actual->promedio << "' ]" << endl;
        actual = actual->siguiente;
        indice++; // equivalente a indice = indice + 1;
    }
}


// Control de entrada para evitar errores
    // Con int
int controlINT() { 
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

    // Con float
float controlFLOAT() { 
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
    cout << "\n++++++++++++\nMenu\n";
    cout << "1. Insertar un nuevo estudiante en la cola.\n"; // insertarCola
    cout << "2. Eliminar estudiante al frente de la cola\n"; // eliminarCola
    cout << "3. Mostrar contenidos de la cola\n"; // Mostrar_cola
    cout << "4. Salir\n++++++++++++\n\n";
    cout << "> Seleccione una opcion: ";
    opcion = controlINT();
    while (opcion < 1 || opcion > 4) {
        cout << "\t[Debe elegir una opcion valida (1-4)] : ";
        opcion = controlINT();
    }
    return opcion;
}


int main() {
    // Valores iniciales
    Nodo* frente = nullptr;
    Nodo* fin = nullptr;
    string nombre, carrera;
    int opcion, indice;
    float promedio;
    bool vaciaORnot, llenaORnot;
    
    // Dirige a las opciones del menu segun lo que el usuario elija
    while (opcion != 4) {
        
        // Revisa si esta vacia al iniciar cada vez: para no reiterar el codigo
        vaciaORnot = checkColaVacia(frente);

        // Muestra el menu + pide opcion
        opcion = menu();

        // Segun la opcion, hace algo
        switch (opcion) {
            // Insertar cola
            case 1: 
                // Se revisa si esta llena la cola primero (aunque siempre va a tirar false)
                if (checkColaLlena()) {
                    cout << "La cola esta llena" << endl;
                } else {
                    cout << "+ Nombre y carrera [Ejemplo: Juan Informatica] : ";
                    cin >> nombre, cin >> carrera;
                    cout << "+ Promedio [Con punto, no coma]: ";
                    promedio = controlFLOAT();
                    cin.ignore();
                    insertarCola(frente, fin, nombre, carrera, promedio);
                }
                break;

            // Eliminar cola
            case 2: 
                // Primero revisa si la cola esta vacia o no
                if (vaciaORnot == true) { 
                    // Si esta vacia, tira aviso
                    cout << "La cola esta vacia.\n";
                } else {
                    // Y si no lo esta, se elimina
                    eliminarCola(frente, fin, nombre, carrera, promedio);
                    cout << "\t- Se ha eliminado al primer estudiante de la cola [FIFO] -" << endl;
                }
                break; 

            // Mostrar cola
            case 3: 
                if (vaciaORnot == true) {
                    cout << "La cola esta vacia.\n";
                } else {
                    mostrarCola(frente);
                }
                break;

            // Salir
            case 4: 
                cout << "> Saliendo del programa...\n";
                // Liberar toda la memoria de la cola antes de salir
                while (!checkColaVacia(frente)) {
                    eliminarCola(frente, fin, nombre, carrera, promedio);
                }
                break;


            default:
                cout << "x+ Opcion no valida. Intente de nuevo +x.\n";
        }
    } 

    return 0;
}