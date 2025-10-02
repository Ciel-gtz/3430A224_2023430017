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


// Checkeo de cola VACIA
bool Cola_vacia(Nodo* frente) {
    if (frente == nullptr) {
        // cola vacia
        return true;
    } else {
        // cola con al menos 1 elemento
        return false;
    }
}



// Insertar_cola y Eliminar_cola [FIFO]
void Insertar_cola(Nodo*& frente, Nodo*& fin, string nombre, string carrera, float promedio) {
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

void Eliminar_cola(Nodo*& frente, Nodo*& fin, string& nombre, string& carrera, float& promedio) {
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
void mostrar(Nodo* frente) {
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
int control_int() { 
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
float control_float() { 
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
    cout << "1. Insertar un nuevo estudiante en la cola.\n"; // Insertar_cola
    cout << "2. Eliminar estudiante al frente de la cola\n"; // Eliminar_cola
    cout << "3. Mostrar contenidos de la cola\n"; // Mostrar_cola
    cout << "4. Salir\n++++++++++++\n\n";
    cout << "> Seleccione una opcion: ";
    opcion = control_int();
    while (opcion < 1 || opcion > 4) {
        cout << "\t[Debe elegir una opcion valida (1-4)] : ";
        opcion = control_int();
    }
    return opcion;
}



int main() {
    // Valores iniciales
    Nodo* frente = nullptr;
    Nodo* fin = nullptr;
    int opcion, indice;
    string nombre, carrera;
    float promedio;
    bool vaciaORnot;
    

    // Dirige a las opciones del menu segun lo que el usuario elija
    while (opcion != 4) {

        // Revisa si esta vacia la cola al iniciar cada vez: para no reiterar el codigo
        vaciaORnot = Cola_vacia(frente);

        // Muestra el menu + pide opcion
        opcion = menu();

        // Segun la opcion, hace algo
        switch (opcion) {
            // Insertar_cola
            case 1: 
                cout << "+ Nombre y carrera [Ejemplo: Juan Informatica] : ";
                cin >> nombre, cin >> carrera;
                cout << "+ Promedio [Con punto, no coma]: ";
                promedio = control_float();
                cin.ignore();
                Insertar_cola(frente, fin, nombre, carrera, promedio);
                break;


            // Eliminar_cola
            case 2: 
            // Primero revisa si la cola esta vacia o no
                if (vaciaORnot == true) { 
                    // Si esta vacia, tira aviso
                    cout << "La cola esta vacia.\n";
                } else {
                    // Y si no lo esta, se elimina
                    Eliminar_cola(frente, fin, nombre, carrera, promedio);
                    cout << "\t- Se ha eliminado al primer estudiante de la cola [FIFO] -" << endl;
                }
                break; 


            case 3: // Mostrar_cola
                if (vaciaORnot == true) {
                    cout << "La cola esta vacia.\n";
                } else {
                    mostrar(frente);
                }
                break;


            case 4: // Salir
                cout << "> Saliendo del programa...\n";
                // Liberar toda la memoria de la cola antes de salir
                while (!Cola_vacia(frente) == true) {
                    Eliminar_cola(frente, fin, nombre, carrera, promedio);
                }
                break;


            default:
                cout << "x+ Opcion no valida. Intente de nuevo +x.\n";
        }
    } 

    return 0;
}