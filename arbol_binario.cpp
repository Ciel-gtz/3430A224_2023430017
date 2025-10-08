#include <limits>
#include <fstream>
#include <iostream>

using namespace std;

struct Nodo {
    int info;
    Nodo* izquierda;
    Nodo* derecha;
};

// Crear un nuevo nodo
Nodo* crearNodo(int data) {
    Nodo* newNode = new Nodo;
    newNode->info = data;
    newNode->izquierda = nullptr;
    newNode->derecha = nullptr;
    return newNode;
}


// Controles de entrada para evadir errores...

// Usuario debe escribir char
char userDecision(){ // from: https://stackoverflow.com/questions/43972500/how-to-only-accept-y-or-n-in-users-input-in-c
    char userAnswer;
    do {
        cout << "⚠️ [s/n] : ";
        cin >> userAnswer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        userAnswer = (char)tolower(userAnswer); // from: https://www.geeksforgeeks.org/cpp/tolower-function-in-cpp/
    } 
    while( !cin.fail() && userAnswer!='s' && userAnswer!='n' );

    return userAnswer;   
}

// Usuario debe escribir int
int controlINT() { 
    int valor;
    while (true){
        cin >> valor;
        if (!cin) {
        cout << "⚠️  Solo se permiten numeros : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
        } else {
            return valor;
        }
    }
}


// Funcion recursiva para construir el arbol manualmente
void crearArbol(Nodo* &apnodo) {
    if (apnodo == nullptr) {
        int valor;
        cout << "\n> Ingrese valor para el nodo : ";
        valor = controlINT();
        /// HERE?
        apnodo = crearNodo(valor);
    }

    char resp;

    // Preguntar por hijo izquierdo
    cout << "◀ ¿Existe nodo a la izquierda de " << apnodo->info << "? ";
    resp = userDecision();
    if (resp == 's') {
        apnodo->izquierda = nullptr; // inicializar
        crearArbol(apnodo->izquierda); // llamada recursiva
    } else {
        apnodo->izquierda = nullptr;
    }

    // Preguntar por hijo derecho
    cout << "▶ ¿Existe nodo a la derecha de " << apnodo->info << "? ";
    resp = userDecision();
    if (resp == 's') {
        apnodo->derecha = nullptr;
        crearArbol(apnodo->derecha); // llamada recursiva
    } else {
        apnodo->derecha = nullptr;
    }
}

// Revisa si el valor que el usuario ingresa ya existe en el arbol o no
bool existeEnArbol(Nodo* nodo, int valor) {
    // Final de rama sin encontrar valor 
    if (nodo == nullptr) {
        return false;
    }

    // Nodo actual coincide con valor
    if (nodo->info == valor) {
        return true;
    }

    bool existeIzq = existeEnArbol(nodo->izquierda, valor); // Recorrer el subarbol izquierdo
    bool existeDer = existeEnArbol(nodo->derecha, valor); // Recorrer el subarbol derecho

    if (existeIzq || existeDer) {
        // Encontrado en algun subarbol
        return true;
    } else {
        // No encontrado
        return false;
    }
}

// Ediciones del Arbol...

// Insercion en Arbol
void insertarEnArbol(Nodo* &apnodo, int infor) {
    if (apnodo == nullptr) {
        // arbol o subarbol vacio, crear nuevo nodo
        apnodo = crearNodo(infor);
    } 
    else if (infor < apnodo->info) {
        // Ir al subarbol izquierdo
        if (apnodo->izquierda == nullptr) {
            apnodo->izquierda = crearNodo(infor);
        } else {
            insertarEnArbol(apnodo->izquierda, infor); // llamada recursiva
        }
    } 
    else if (infor > apnodo->info) {
        // Ir al subarbol derecho
        if (apnodo->derecha == nullptr) {
            apnodo->derecha = crearNodo(infor);
        } else {
            insertarEnArbol(apnodo->derecha, infor); // llamada recursiva
        }
    } 
}

// Eliminar de ArbolNOTYET


// Funciones recursivas para imprimir el arbol...

// En Preorden
void printPreOrden(Nodo* Nodo) {
    if (Nodo == nullptr) {
        return;
    }
    cout << Nodo->info << " ";   // Imprimir el dato del nodo actual
    printPreOrden(Nodo->izquierda);   // Recorrer el subarbol izquierdo
    printPreOrden(Nodo->derecha);  // Recorrer el subarbol derecho
}

// En Inorden
void printInOrden(Nodo* Nodo) {
    if (Nodo == nullptr) {
        return;
    }
    printInOrden(Nodo->izquierda);    // Recorrer el subarbol izquierdo
    cout << Nodo->info << " ";    // Imprimir el dato del nodo actual
    printInOrden(Nodo->derecha);   // Recorrer el subarbol derecho
}

// En Postorden
void printPostOrden(Nodo* Nodo) {
    if (Nodo == nullptr) {
        return;
    }
    printPostOrden(Nodo->izquierda);   // Recorrer el subarbol izquierdo
    printPostOrden(Nodo->derecha);  // Recorrer el subarbol derecho
    cout << Nodo->info << " ";    // Imprimir el dato del nodo actual
}


// Menu de opciones
int menu() {
    int opcion = 0;
    cout << "\n\n++++++++++++\nMenu\n";
    cout << "1. ⭕ Insertar nuevo nodo.\n"; // NOTYET : insertar numero ELEMENTOS UNICOS (recorrer -> insertar)
    cout << "2. ❌ Eliminar nodo.\n"; // NOTYET : eliminar num buscado (recorrer -> eliminar)
    cout << "3. ✍️  Modificar nodo.\n"; // NOTYET : modificar num buscado (recorrer -> eliminar)
    cout << "4. 👁️  Mostrar recorridos del arbol.\n";
    cout << "5. 🖨️  Generar grafo.\n"; // NOTYET
    cout << "6. 🚪🏃 Salir.\n++++++++++++\n\n";
    cout << "> Seleccione una opcion: ";
    opcion = controlINT();
    while (opcion < 1 || opcion > 6) {
        cout << "\t⚠️  [Debe elegir una opcion valida (1-6)] : ";
        opcion = controlINT();
    }
    return opcion;
}

int main() {
    Nodo* raiz = nullptr;
    int opcion, valor;

    // Primero hace que el usuario construya el arbol
    cout << "──{ Construccion interactiva del arbol binario }──\n";
    crearArbol(raiz);

    // Para despues trabajar con el:
    
    while (opcion != 6) {

        opcion = menu();

        switch (opcion) {
            // 1. ⭕ Insertar nuevo nodo.
            case 1: 
                cout << "\n> Valor para el nodo nuevo : ";
                valor = controlINT();
                // Revisa primero si es que valor ya existe
                if (existeEnArbol(raiz, valor)) {
                    // Si es que existe, avisa y vuelve al menu
                    cout << "⚠️  El nodo " << valor << " ya existe en el arbol.\n";
                    break;
                } // Si no existe, lo inserta
                insertarEnArbol(raiz, valor);
                break;

            // 2. ❌ Eliminar nodo.
            case 2: 
            
                break; 

            // 3. ✍️ Modificar nodo.
            case 3: 

                break;

            // 4. 👁️ Mostrar recorridos del arbol.
            case 4: 
                cout << "\n[ Recorrido en preorden: ";
                printPreOrden(raiz);

                cout << "]\n[ Recorrido en inorden: ";
                printInOrden(raiz);

                cout << "]\n[ Recorrido en postorden: ";
                printPostOrden(raiz);
                cout << "]" << endl;
            
                break;

            // 5. 🖨️ Generar grafo.
            case 5:
            
                break;

            // 6. 🚪🏃 Salir.
            case 6:  
                cout << "> Saliendo del programa...\n";
                break;

            default:
                cout << "⚠️  Opcion no valida. Intente de nuevo .\n";
        }
    } 

    return 0;
}
