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
    string pila[50]; // Arreglo estatico (indices 1..MAX)


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
    void Push(bool &BAND, int &TOPE, int MAX, string pila[], string DATO) { 
        Pila_llena(TOPE, MAX, BAND); // Revisa si se pueden agregar mas datos
        if (BAND == true) {
            cout << "x+ Desbordamiento, pila llena +x\n";
        } else if (BAND == false) { // Si se comprueba que no esta llena...
            TOPE += 1; // Aumenta el tope...
            pila[TOPE] = DATO; // Y se agrega el DATO del usuario
            cout << "+ Agregado: \"" << DATO << "\"\n";
        }
    }

    string Pop(string pila[], int &TOPE, bool &BAND) { 
        Pila_vacia(TOPE, BAND); // Revisa si se pueden eliminar datos
        if (BAND == true) {
            cout << "x+ Subdesbordamiento, pila vacia +x\n";
            return "";
        } else if (BAND == false) { // Si se comprueba que no esta vacia...
            string DATO = pila[TOPE]; // Guarda el ultimo dato...
            TOPE -= 1; // Se reduce el tope...
            cout << "- Retirado: \"" << DATO << "\"\n"; // Y se muestra cual era el ultimo dato
            return DATO; // Se devuelve el dato retirado (en caso de que se necesite, aunque en este caso especificamente no lo necesitamos asi que se podria hacer que esta funcion sea void en vez de int)
        }
        return ""; 
    }


    // Mostrar los valores dentro de la pila
    void Mostrar(string pila[], int TOPE) {
        if (TOPE == 0) {
            cout << "\nx+ La pila esta vacia +x\n";
        } else {
            cout << "\n> Contenido de la pila:\n [ ";
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
    cout << "1. Agregar contenedor\n";
    cout << "2. Mover/eliminar contenedor\n";
    cout << "3. Mostrar contenedores\n";
    cout << "4. Salir\n++++++++++++\n";
    cout << "> Seleccione una opcion: ";
    opcion = control_int();
    while (opcion < 1 || opcion > 4) {
        cout << "[Debe elegir una opcion valida (1-4)] : ";
        opcion = control_int();
    }
    return opcion;
}

// Apoyo opcion 1
int elegir_pila(int pilas_contenedores){
    // Primero revisa que contenedor quiere editar el usuario
    int pila_editar = -1;
    cout << "> Que pila desea editar?\n ";
    while (pila_editar > pilas_contenedores || pila_editar < 1) {
        cout << "x+ Pilas existentes -> [ 1 - " << pilas_contenedores << " ] : ";
        pila_editar = control_int();
    }
    return pila_editar - 1;
}

int contenedores_pila(int cantidad_contenedores) {
    int valor = -1;
    cout << "\n> Cuantos contenedores desea agregar?\n- Notese que estos tendrán su etiqueta/nombre automaticamente agregado" << endl;
    while (valor < 0 || valor > cantidad_contenedores) {
        cout << "x+ El valor elegido debe estar entre [ 0 - " << cantidad_contenedores << " ] : ";
        valor = control_int();
    }
    return valor;
}

// Opcion 3
void mostrar_pilas(vector<Contenedor> &pilas, int pilas_contenedores, int cantidad_contenedores) {
    cout << "\n> Contenedores por columnas:\n";

    // Recorre de arriba (TOPE máximo) hacia abajo (1)
    for (int fila = cantidad_contenedores; fila >= 1; fila--) { // Se recorre de la fila mas alta; cuando fila sea 0, se detiene; fila = fila - 1 
        for (int columna = 0; columna < pilas_contenedores; columna++) {
            if (pilas[columna].TOPE >= fila) {
                cout << "[" << pilas[columna].pila[fila] << "]\t"; // \t es el equivalente a un tabulador, para que aparezca la informacion ordenada
            } else {
                cout << "[    ]\t"; // espacio vacio si no hay contenedor
            }
        }
        cout << "\n"; // Para mostrarlos como columnas
    }
    // Se muestran los indices de las columnas
    for (int columna = 0; columna < pilas_contenedores; columna++) {
        cout << " " << columna + 1 << "\t";
    }
    cout << "\n";
}


// El main
int main(int argc, char* argv[]) {
    // Toma los valores via terminal al ejecutar el programa y los asigna 
    int cantidad_contenedores = atoi(argv[1]); // Equivalente a filas
    int pilas_contenedores = atoi(argv[2]); // Equivalente a columnas

    cout << "\n" << cantidad_contenedores << " -> Es su numero de contenedores por pila\n" 
    << pilas_contenedores << " -> Es su numero de pilas de contenedores [equivalente al rango 0 - " << pilas_contenedores - 1 << " ]" << endl;
    
    // Se asigna en un vector el numero de pila de contenedores
    vector<Contenedor> pila(pilas_contenedores);

    // Se crean listas vacias, asignandoles el band false y el maximo de contenedores por pila como la cantidad que el usuario coloco
    for (int i = 0; i < pilas_contenedores; i++) {
        pila[i].MAX = cantidad_contenedores;
        pila[i].TOPE = 0;
        pila[i].BAND = false;
    }

    int opcion, pila_elegida, cantidad_repeticiones, decide;
    string etiqueta;

    // Se ven las opciones del menu
    while (opcion != 4) {
        opcion = menu();

        switch (opcion) {
            case 1:
                static int contador_global = 0;
                // Primero pregunta a que pila se desea agregar un contenedor
                pila_elegida = elegir_pila(pilas_contenedores);
                cantidad_repeticiones = contenedores_pila(cantidad_contenedores);

                // Agregar los contenedores con etiqueta automática
                for (int i = 0; i < cantidad_repeticiones; i++) {
                    // Generar etiqueta: "pilaIndex#tContador"
                    etiqueta = to_string(pila_elegida) + "#t" + to_string(contador_global++);
                
                // Agrega el nombre con un push a la pila elegida por la cantidad de contenedores que el usuario quiso agregar
                pila[pila_elegida].Push(pila[pila_elegida].BAND, pila[pila_elegida].TOPE, pila[pila_elegida].MAX, pila[pila_elegida].pila, etiqueta);
                }

                cout << "La pila ha sido editada" << endl;
                mostrar_pilas(pila, pilas_contenedores, cantidad_contenedores);
                etiqueta = ""; // Se restaura etiqueta a su valor inicial
                break;

            case 2:
                mostrar_pilas(pila, pilas_contenedores, cantidad_contenedores);
                // Primero se saca un contenedor de una pila
                pila_elegida = elegir_pila(pilas_contenedores);
                etiqueta = pila[pila_elegida].Pop(pila[pila_elegida].pila, pila[pila_elegida].TOPE, pila[pila_elegida].BAND);

                // Esto por si hubo un error al momento de sacar (ej: no se saco nada)
                if (etiqueta == "") { 
                    break;
                }

                // confirmar si se quiere borrar o mover
                while (decide != 1 && decide != 0) {
                    cout << "\n> Este contenedor lo quiere eliminar o mover? [0: eliminar, 1: mover] : ";
                    decide = control_int();
                }

                if (decide == 0) {
                    cout << "x+ El contenedor " << etiqueta << " ha sido eliminado +x" << endl;
                    etiqueta = ""; 
                    decide = 2; // Se restaura valor decide a otro numero cualquiera distinto de 0 o 1
                    break;
                } else if (decide == 1) {
                    // Se busca mover a alguna pila
                    cout << "> A qué lugar quisiera mover este contenedor? : ";
                    pila_elegida = elegir_pila(pilas_contenedores);
                    pila[pila_elegida].Push(pila[pila_elegida].BAND, pila[pila_elegida].TOPE, pila[pila_elegida].MAX, pila[pila_elegida].pila, etiqueta);
                    mostrar_pilas(pila, pilas_contenedores, cantidad_contenedores);
                    etiqueta = "";
                    decide = 2;
                    break;
                }                
                break; // Lo dejo por si pasa algun bug raro XD

            case 3:
                mostrar_pilas(pila, pilas_contenedores, cantidad_contenedores);
                break;

            case 4:
                cout << "> Saliendo del programa...\n";
                pila.clear(); // Borrar memoria
                break;

            default:
                cout << "x+ Opcion no valida. Intente de nuevo +x.\n";
        }
    } 

    return 0;
}
