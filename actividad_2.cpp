#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Nodo {
    string nombreProteina; //resn -> 3 letras
    string codigoPDB; //resid -> numerico
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

    cout << "\t+ Proteina '" << nombre << "' agregada a la cola +\n";
}

// Se mantiene eliminarCola para usar en la opcion 7 como limpieza de memoria
void eliminarCola(Nodo*& frente, Nodo*& fin, string& nombre, string& codigo) { 
    Nodo* nodoActual = frente;
    nombre = nodoActual->nombreProteina;
    codigo = nodoActual->codigoPDB;
    frente = nodoActual->siguiente;

    if (frente == nullptr) {
        fin = nullptr; // si quedo vacia, ambos punteros a null
    }

    delete nodoActual;
}

// Borrar en una posicion especifica
bool eliminarEspecifico(Nodo*& pila, int& posicion) {
    if (pila == nullptr || posicion < 1) {
        return false;
    }
    
    Nodo* actual = pila;
    if (posicion == 1) {  
        // borrar el primero (tope de la pila)
        pila = actual->siguiente;
        delete actual;
        return true;
    }

    // recorrer hasta la posición anterior
    Nodo* anterior = nullptr;
    int contador = 1;
    while (actual != nullptr && contador < posicion) {
        anterior = actual;
        actual = actual->siguiente;
        contador++;
    }

    if (actual == nullptr) {
        return false;
    } 

    anterior->siguiente = actual->siguiente;
    delete actual;
    return true;
}

// Editar en una posicion especifica
bool modificarEspecifico(Nodo* frente, int& posicion, string nombre) {
    if (frente == nullptr || posicion < 1) {
        return false; // Cola vacía o posición inválida
    }

    Nodo* actual = frente;
    int contador = 1;

    // Recorremos hasta llegar a la posición pedida
    while (actual != nullptr && contador < posicion) {
        actual = actual->siguiente;
        contador++;
    }

    if (actual == nullptr) {
        return false; // posición fuera de rango
    }

    // Cortamos el nuevo nombre a 3 letras para mantener el formato
    actual->nombreProteina = nombre;
    return true;
}

// Mostrar lo presente en cola
void mostrarCola(Nodo* frente) {
    cout << "\n> Contenido actual de la cola :\n" << endl;
    int indice = 1;
    Nodo* actual = frente;

    // Header
    cout << "n° :\t[nombre\t->\tcodigo pdb]\n";

    // Imprime la info
    while (actual != nullptr) {
        cout << indice << "  :\t['" << actual->nombreProteina << "'\t->\t'" << actual->codigoPDB << "'\t  ]" << endl;
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
    cout << "\n\n++++++++++++\nMenu\n";
    cout << "1. ⭕ Insertar un nuevo residuo al final de la secuencia.\n";
    cout << "2. ✍️  Modificar el resn de un residuo.\n"; //XXX
    cout << "3. ❌ Eliminar un residuo en una posicion especifica.\n";
    cout << "4. 👁️  Mostrar la lista de residuos.\n";
    cout << "5. 📃 Exportar la lista a un archivo en formato Graphviz (.dot)\n"; //XXX
    cout << "6. 🖨️  Generar imagen .png a partir del archivo .dot\n"; //XXX
    cout << "7. 🚪🏃 Salir\n++++++++++++\n\n";
    cout << "> Seleccione una opcion: ";
    opcion = controlINT();
    while (opcion < 1 || opcion > 7) {
        cout << "\t⚠️  [Debe elegir una opcion valida (1-7)] : ";
        opcion = controlINT();
    }
    return opcion;
}


int main(int argc, char* argv[]) {
    // Valores iniciales
    Nodo* frente = nullptr;
    Nodo* fin = nullptr;
    string nombre, codigo, line, archivoPDB;
    int opcion, temp;
    float promedio;
    bool vaciaORnot, llenaORnot;
    
    // Se lee el archivo que el usuario ingrese
    if (argc < 2) {
        // Si no se ingresa archivo, se avisa y se sale
        cerr << "⚠️ Utilice: ./actividad_2 <ruta_archivo.pdb>" << endl;
        return 1; // Se retorna 1 para indicar error
    }

    archivoPDB = argv[1];
    ifstream pdb_file(archivoPDB);

    if (!pdb_file) {
        cerr << "⚠️ No se pudo abrir el archivo: " << archivoPDB << endl;
        return 1;
    }

    while (getline(pdb_file, line)) {
        // Trabaja con las lineas del archivo
        nombre = line.substr(0, 3); // Usa las primeras 3 letras del archivo

        codigo = line.substr(4);// Utiliza el resto de la linea, se incluye el espacio del ejemplo de archivo en .substr
        insertarCola(frente, fin, nombre, codigo);
    }

    // Y cierra el archivo, ya que los datos ya han sido guardados en la cola
    pdb_file.close();

    // Continua con las opciones del menu
    while (opcion != 7) {
        vaciaORnot = checkColaVacia(frente);

        opcion = menu();

        // Segun la opcion, hace algo
        switch (opcion) {
            // Insertar a la cola
            case 1: 
                // Pido que el usuario ingrese un nombre, se corta por si el usuario puso algo muy largo
                cout << "+ Nombre de la proteina [0 para no editar nada]: ";
                cin >> nombre;
                nombre = nombre.substr(0, 3); // Para guardarlo en el mismo formato de 3 letras

                // Pide al usuario que ingrese un codigo
                cout << "+ Codigo de la proteina [Numerico]: ";
                temp = controlINT(); // Lo pide en int primero para hacer uso de controlINT() y mantener el formato
                codigo = to_string(temp); // Y ahora paso ese int a string

                // Se inserta a la cola
                insertarCola(frente, fin, nombre, codigo);
                break;

            // Modificar resn (nombre)
            case 2: 
                // Primero pide la posicion y el nuevo nombre
                cout << "+ Posicion de la proteina a modificar [Numerico]: ";
                temp = controlINT(); 

                cout << "+ Nombre nuevo de la proteina [Ejemplo: TYR]: ";
                cin >> nombre;
                nombre = nombre.substr(0, 3); 

                // Se modifica en la cola
                modificarEspecifico(frente, temp, nombre);
                break; 

            // Eliminar especifico
            case 3: 
                // Primero revisa si la cola esta vacia o no
                if (vaciaORnot == true) { 
                    // Si esta vacia, tira aviso
                    cout << "⚠️  La cola esta vacia.\n";
                } else {
                    // Y si no lo esta, se elimina
                    //eliminarCola(frente, fin, nombre, codigo);
                    cout << "> Que proteina desea eliminar? [0 para cancelar] : ";
                    temp = controlINT();

                    // Revisa para imprimir o no la informacion de cual se ha borrado
                    if (eliminarEspecifico(frente, temp) == true) {
                        cout << "\tx- Se ha eliminado la proteina en la posicion " << temp << " -x" << endl;
                    } else {
                        cout << "⚠️  No se ha podido borrar la proteina.";
                    }
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
                // Libera toda la memoria de la cola antes de salir
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