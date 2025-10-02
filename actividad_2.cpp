#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Nodo {
    string nombreProteina;
    string codigoPDB;
    Nodo* siguiente;
};

// Checkea si la cola esta vacia o no
bool checkColaVacia(Nodo* frente) {
    if (frente == nullptr) {
        // cola vacia
        return true;
    } else {  
        // cola con al menos 1 elemento
        return false;
    }
}


// insertarCola y eliminarCola [FIFO]
void insertarCola(Nodo*& frente, Nodo*& fin, string nombre, string codigo) {
    Nodo* nuevo = new Nodo();
    nuevo->nombreProteina = nombre;
    nuevo->codigoPDB = codigo;
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

    cout << "\t+ Proteina'" << nombre << "' agregada a la cola +\n";
}

void eliminarCola(Nodo*& frente, Nodo*& fin, string& nombre, string& codigo) { // cambiar a que sea de forma especifica
    Nodo* nodoActual = frente;
    nombre = nodoActual->nombreProteina;
    codigo = nodoActual->codigoPDB;
    frente = nodoActual->siguiente;

    if (frente == nullptr) {
        fin = nullptr; // si quedo vacia, ambos punteros a null
    }

    delete nodoActual;
}


// Mostrar lo presente en cola
void mostrarCola(Nodo* frente) {
    cout << "\n> Contenido actual de la cola :\n";
    int indice = 1;
    Nodo* actual = frente;

    // Header
    cout << "n° :\t[\tnombre de la proteina\t->\tcodigo pdb\t]" << endl;

    // Imprime la info
    while (actual != nullptr) {
        cout << indice << "  :\t[\t'" << actual->nombreProteina << "'\t->\t'" << actual->codigoPDB << "'\t]" << endl;
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
        cout << "⚠️  Solo se permiten numeros : ";
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
    cout << "1. Insertar un nuevo residuo al final de la secuencia.\n";
    cout << "2. Modificar el resn de un residuo.\n";
    cout << "3. Eliminar un residuo en una posicion especifica.\n";
    cout << "4. Mostrar la lista de residuos.\n";
    cout << "5. Exportar la lista a un archivo en formato Graphviz (.dot)\n";
    cout << "6. Generar imagen .png a partir del archivo .dot\n";
    cout << "7. Salir\n++++++++++++\n\n";
    cout << "> Seleccione una opcion: ";
    opcion = controlINT();
    while (opcion < 1 || opcion > 7) {
        cout << "\t⚠️  [Debe elegir una opcion valida (1-7)] : ";
        opcion = controlINT();
    }
    return opcion;
}


int main() {
    // Valores iniciales
    Nodo* frente = nullptr;
    Nodo* fin = nullptr;
    string nombre, codigo;
    int opcion;
    float promedio;
    bool vaciaORnot, llenaORnot;
    
    while (opcion != 7) {
        vaciaORnot = checkColaVacia(frente);

        opcion = menu();

        // Segun la opcion, hace algo
        switch (opcion) {
            // Insertar a la cola
            case 1: 
                /*
                cout << "+ Nombre y carrera [Ejemplo: Juan Informatica] : ";
                cin >> nombre, cin >> carrera;
                cin.ignore();
                insertarCola(frente, fin, nombre, carrera, promedio);
                */
                break;

            // Modificar resn
            case 2: 
               
                break; 

            // Eliminar especifico
            case 3: 
                // Primero revisa si la cola esta vacia o no
                if (vaciaORnot == true) { 
                    // Si esta vacia, tira aviso
                    cout << "⚠️  La cola esta vacia.\n";
                } else {
                    // Y si no lo esta, se elimina
                    eliminarCola(frente, fin, nombre, codigo);
                    cout << "\tx- Se ha eliminado la proteina "<< nombre << "-x" << endl;
                }
                break;

            // Mostrar cola
            case 4: 
                if (vaciaORnot == true) {
                    cout << "⚠️  La cola esta vacia.\n";
                } else {
                    mostrarCola(frente);
                }
                break;

            // Exportar a .dot
            case 5:
                break;

            // Generar imagen .png a partir de .dot
            case 6:  
                break;

            // Salir del programa
            case 7: 
                cout << "> Saliendo del programa...\n";
                // Liberar toda la memoria de la cola antes de salir
                while (!checkColaVacia(frente)) {
                    eliminarCola(frente, fin, nombre, codigo);
                }
                break;


            default:
                cout << "⚠️  Opcion no valida. Intente de nuevo .\n";
        }
    } 

    return 0;
}