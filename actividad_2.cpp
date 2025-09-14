#include <iostream>
#include <string>
#include <cstdlib> // Para stoi
#include <limits> // Libreria para manejo de limites numericos
#include <vector> // argv

using namespace std;

struct Contenedor {
    int MAX;          // Capacidad logica (<= 50)
    int TOPE;         // 0 => vacia; 1..MAX => elementos
    bool BAND;        // Bandera de estado
    int pila[50]; // Arreglo estatico (indices 1..MAX)


    // Checkeo de pila
    bool Pila_vacia(int TOPE, bool &BAND) {   
        if (TOPE == 0) {
            BAND = true; // La pila esta vacia
        } else {
            BAND = false; // La pila NO esta vacia
        }
        return BAND;
    }

    bool Pila_llena(int TOPE, int MAX, bool &BAND) {   
        if (TOPE == MAX){
            BAND = true; // La pila esta llena
        } else {
            BAND = false; // La pila NO esta llena
        }
        return BAND;
    }


    // Push y Pop con pila (LIFO)
    void Push(bool &BAND, int &TOPE, int MAX, int pila[], int DATO) { 
        Pila_llena(TOPE, MAX, BAND); // Revisa si se pueden agregar mas datos
        if (BAND == true) {
            cout << "x+ Desbordamiento, pila llena +x\n";
        } else if (BAND == false) { // Si se comprueba que no esta llena...
            TOPE += 1; // Aumenta el tope...
            pila[TOPE] = DATO; // Y se agrega el DATO del usuario
            cout << "+ Agregado: \"" << DATO << "\"\n";
        }
    }

    int Pop(int pila[], int &TOPE, bool &BAND) { 
        Pila_vacia(TOPE, BAND); // Revisa si se pueden eliminar datos
        if (BAND == true) {
            cout << "x+ Subdesbordamiento, pila vacia +x\n";
            return 0;
        } else if (BAND == false) { // Si se comprueba que no esta vacia...
            int DATO = pila[TOPE]; // Guarda el ultimo dato...
            TOPE -= 1; // Se reduce el tope...
            cout << "- Retirado: \"" << DATO << "\"\n"; // Y se muestra cual era el ultimo dato
            return DATO; // Se devuelve el valor retirado (en caso de que se necesite, aunque en este caso especificamente no lo necesitamos asi que se podria hacer que esta funcion sea void en vez de int)
        }
        return 0; 
    }


    // Mostrar los valores dentro de la pila
    void Mostrar(int pila[], int TOPE) {
        if (TOPE == 0) {
            cout << "\nx+ La pila esta vacia +x\n";
        } else {
            cout << "\n> Contenido de la pila\n(Ordenado de ultimo a primero insertado):\n [ ";
            for (int i = TOPE; i >= 1; i--) {
                cout << pila[i] << " ";
            }
            cout << "]" << endl;
        }
    }
};


// Control de entrada para evitar errores
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


// Menu de opciones
int menu() {
    int opcion = 0;
    cout << "++++++++++++\nMenu\n";
    cout << "1. Push (Agregar nuevo valor)\n";
    cout << "2. Pop (Retirar ultimo valor)\n";
    cout << "3. Mostrar (Ver valores en la pila)\n";
    cout << "4. Salir\n++++++++++++\n";
    cout << "> Seleccione una opcion: ";
    opcion = control_int();
    while (opcion < 1 || opcion > 4) {
        cout << "[Debe elegir una opcion valida (1-4)] : ";
        opcion = control_int();
    }
    return opcion;
}


int main(int argc, char* argv[]) {
    // Toma los valores via terminal al ejecutar el programa y los asigna 
    int cantidad_contenedores = atoi(argv[1]); 
    int pilas_contenedores = atoi(argv[2]); 

    cout << cantidad_contenedores << " -> Es su numero de contenedores por pila\n" 
    << pilas_contenedores << " -> Es su numero de pilas de contenedores" << endl;
    
    // Y se asigna como máximo cantidad_contenedores
    /*Contenedor pila;
    pila.MAX = cantidad_contenedores;
    pila.TOPE = 0;
    pila.BAND = false;*/

    vector<Contenedor> pila(pilas_contenedores);

    for (int i = 0; i < pilas_contenedores; i++) {
        pila[i].MAX = cantidad_contenedores;
        pila[i].TOPE = 0;
        pila[i].BAND = false;
    }

    int opcion;
    int valor;

    while (opcion != 4) {
        opcion = menu();

        switch (opcion) {
            case 1:
                cout << "\n> Ingrese el valor a agregar: ";
                cin.ignore(); // Limpiar buffer
                valor = control_int();
                pila[0].Push(pila[0].BAND, pila[0].TOPE, pila[0].MAX, pila[0].pila, valor);
                pila[1].Push(pila[1].BAND, pila[1].TOPE, pila[1].MAX, pila[1].pila, valor);
                break;

            case 2:
                int hola;
                pila[0].Pop(pila[0].pila, pila[0].TOPE, pila[0].BAND);
                pila[1].Pop(pila[1].pila, pila[1].TOPE, pila[1].BAND);
                break;

            case 3:
                pila[0].Mostrar(pila[0].pila, pila[0].TOPE);
                pila[1].Mostrar(pila[1].pila, pila[1].TOPE);
                break;

            case 4:
                cout << "> Saliendo del programa...\n";
                break;

            default:
                cout << "x+ Opcion no valida. Intente de nuevo +x.\n";
        }
    } 

    return 0;
}
