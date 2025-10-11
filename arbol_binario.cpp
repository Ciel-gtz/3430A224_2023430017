#include <limits>
#include <vector> // Para guardar valores iniciales en lista
#include <fstream>
#include <iostream>

using namespace std;

struct Nodo {
    int info;
    Nodo* izquierda;
    Nodo* derecha;
};

// Crear un nuevo nodo
Nodo* crearNodo(const int data) {
    Nodo* newNode = new Nodo;
    newNode->info = data;
    newNode->izquierda = nullptr;
    newNode->derecha = nullptr;
    return newNode;
}


/* =========================||
Controles de entrada para evadir errores...*/
// Usuario debe escribir char
char userDecision(){ // from: https://stackoverflow.com/questions/43972500/how-to-only-accept-y-or-n-in-users-input-in-c
    char userAnswer;
    do {
        cout << "! [s/n] : ";
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


/* =========================||
Sobre el arbol...*/
// Funcion recursiva para construir el arbol manualmente
void crearArbol(Nodo* &apnodo, vector<int>& lista) {
    if (apnodo == nullptr) {
        int valor;
        bool existe;

        // Checkeo para que no se repitan valores al inicio
        while (true) {
            cout << "\n> Ingrese valor para el nodo: ";
            valor = controlINT();

            // Comprobar si ya existe valor en la lista
            existe = false;
            for (int valorNodo : lista) {
                if (valorNodo == valor) {
                    existe = true;
                    break;
                }
            }
            if (existe == true) {
                cout << "⚠️  El nodo " << valor << " ya existe, intente nuevamente.\n";
            } else {
                lista.push_back(valor); // guardar valor
                break;
            }
        }
        apnodo = crearNodo(valor);
    }

    char resp;
    // Preguntar por hijo izquierdo
    cout << "◀ ¿Existe nodo a la izquierda de " << apnodo->info << "? ";
    resp = userDecision();
    apnodo->izquierda = nullptr; // inicializar
    if (resp == 's') {
        crearArbol(apnodo->izquierda, lista); // llamada recursiva
    } 

    // Preguntar por hijo derecho
    cout << "▶ ¿Existe nodo a la derecha de " << apnodo->info << "? ";
    resp = userDecision();
    if (resp == 's') {
        apnodo->derecha = nullptr;
        crearArbol(apnodo->derecha, lista); // llamada recursiva
    } else {
        apnodo->derecha = nullptr;
    }
}

// Busca un valor en el arbol y devuelve un puntero al nodo si existe, nullptr si no
Nodo* buscarNodo(Nodo* nodo, int valor) {
    if (nodo == nullptr){
        // No se encuentra valor
        return nullptr;
    }

    if (nodo->info == valor){
        // Se encuentra valor -> devuelve puntero
        return nodo;
    } 

    // Buscar subarbol izquierdo
    Nodo* encontrado = buscarNodo(nodo->izquierda, valor);

    if (encontrado != nullptr){
        // Se encuentra valor izquierdo -> devuelve puntero
        return encontrado;
    }
    
    // Buscar subarbol derecho
    return buscarNodo(nodo->derecha, valor);
}


/* =========================||
Ediciones del Arbol...*/
// Insercion en Arbol
void insertarNodo(Nodo* &apnodo, int infor) {
    if (apnodo == nullptr) {
        // arbol o subarbol vacio, crear nuevo nodo
        apnodo = crearNodo(infor);
    } 
    else if (infor < apnodo->info) {
        // Ir al subarbol izquierdo
        if (apnodo->izquierda == nullptr) {
            apnodo->izquierda = crearNodo(infor);
        } else {
            insertarNodo(apnodo->izquierda, infor); // llamada recursiva
        }
    } 
    else if (infor > apnodo->info) {
        // Ir al subarbol derecho
        if (apnodo->derecha == nullptr) {
            apnodo->derecha = crearNodo(infor);
        } else {
            insertarNodo(apnodo->derecha, infor); // llamada recursiva
        }
    } 
}

// Eliminar en Arbol
void eliminarNodo(Nodo* &apnodo, int valor) {
    // Buscar el nodo recursivamente
    if (valor < apnodo->info) {
        eliminarNodo(apnodo->izquierda, valor);
    } 
    else if (valor > apnodo->info) {
        eliminarNodo(apnodo->derecha, valor);
    } 
    else {
        // Caso 1: Nodo hoja 
        if (apnodo->izquierda == nullptr && apnodo->derecha == nullptr) { // (No hay nodo a la izquierda ni derecha)
            delete apnodo;
            // Se redifine puntero a null
            apnodo = nullptr;
        }

        // Caso 2: Un solo hijo 
        else if (apnodo->izquierda == nullptr) { // (Nodo a la izquierda...
            Nodo* temp = apnodo;
            apnodo = apnodo->derecha;
            delete temp;
        }
        else if (apnodo->derecha == nullptr) { //... o derecha)
            Nodo* temp = apnodo;
            apnodo = apnodo->izquierda;
            delete temp;
        }

        // Caso 3: Dos hijos 
        else { // (Nodo a la izquierda y derecha)
            // Se usa el mas a la izquierda del subarbol derecho
            Nodo* sucesor = apnodo->derecha;
            while (sucesor->izquierda != nullptr){
                sucesor = sucesor->izquierda;
            }
            
            // Copiar valor del sucesor al nodo actual
            apnodo->info = sucesor->info;

            // Eliminar el nodo duplicado en el subarbol derecho
            eliminarNodo(apnodo->derecha, sucesor->info);
        }
    }
}




/* =========================||
Sobre el grafo...*/
// Recorrer el arbol en preorden y escribir en el archivo
void recorrer(Nodo* nodo, ofstream& fp) {
    if (nodo != nullptr) {
        string nodoID = "_" + to_string(nodo->info); // sin _ me salen errores, con . tmb salen errores

        if (nodo->izquierda != nullptr) {
            fp << nodoID << "->_" << nodo->izquierda->info << ";" << endl;
        } else {
            string cadena = nodoID + "i";
            fp << cadena << "[shape=point];" << endl;
            fp << nodoID << "->" << cadena << ";" << endl;
        }

        if (nodo->derecha != nullptr) {
            fp << nodoID << "->_" << nodo->derecha->info << ";" << endl;
        } else {
            string cadena = nodoID + "d";
            fp << cadena << "[shape=point];" << endl;
            fp << nodoID << "->" << cadena << ";" << endl;
        }

        recorrer(nodo->izquierda, fp);
        recorrer(nodo->derecha, fp);
    } else {
        return;
    }
}

// Generar y mostrar la visualizacion del Arbol
void visualizarArbol(Nodo* root) {
    ofstream fp("arbolW.txt");

    if (!fp.is_open()) {
        cerr << "Error al abrir el archivo arbolW.txt" << endl;
        return;
    }

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=\"#47e388ff\"];\n";

    recorrer(root, fp);

    fp << "}" << endl;

    fp.close();

    system("dot -Tpng -o arbolW.png arbolW.txt");
    system("eog arbolW.png");
}


/* =========================||
Funciones recursivas para imprimir el arbol...*/
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


/* =========================||*/
// Menu de opciones
int menu() {
    int opcion = 0;
    cout << "\n\n++++++++++++\nMenu\n";
    cout << "1. ⭕ Insertar nuevo nodo.\n"; 
    cout << "2. ❌ Eliminar nodo.\n"; // NOTYET : eliminar num buscado (recorrer -> eliminar)
    cout << "3. ✍️  Modificar nodo.\n"; // NOTYET : modificar num buscado (recorrer -> eliminar)
    cout << "4. 👁️  Mostrar recorridos del arbol.\n";
    cout << "5. 🖨️  Generar grafo.\n";
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
    vector<int> valoresIniciales;

    // Primero hace que el usuario construya el arbol
    cout << "──{ Construccion interactiva del arbol binario }──\n";
    crearArbol(raiz, valoresIniciales);

    // Para despues trabajar con este arbol inicial:
    while (opcion != 6) {

        opcion = menu();

        switch (opcion) {
            // 1. ⭕ Insertar nuevo nodo.
            case 1: {
                cout << "\n> Valor para el nodo nuevo : ";
                valor = controlINT();

                // Revisa primero si es que valor ya existe
                Nodo* nodoEncontrado = buscarNodo(raiz, valor);
                if (nodoEncontrado != nullptr) {
                    // Si es que existe, avisa y vuelve al menu
                    cout << "⚠️  El nodo " << valor << " ya existe en el arbol.\n";
                    break;
                } 
                
                // Si no existe, lo inserta
                insertarNodo(raiz, valor);
                
                break;
            }
            // 2. ❌ Eliminar nodo.
            case 2: {
                cout << "Nodos elegibles: [ ";
                printPreOrden(raiz);
                cout << " ] > Nodo a eliminar : ";

                valor = controlINT();
                
                // Revisa primero si es que valor existe
                Nodo* nodoEncontrado = buscarNodo(raiz, valor);
                if (nodoEncontrado != nullptr) {
                    eliminarNodo(raiz, valor);    
                } else {
                    cout << "⚠️  El nodo " << valor << " no existe.\n";   
                }
                break; 
            }
            // 3. ✍️ Modificar nodo.
            case 3: {
                

                break;
            }
            // 4. 👁️ Mostrar recorridos del arbol.
            case 4: {
                cout << "\n[ Recorrido en preorden:   ";
                printPreOrden(raiz);

                cout << "\t]\n[ Recorrido en inorden:   ";
                printInOrden(raiz);

                cout << "\t]\n[ Recorrido en postorden:   ";
                printPostOrden(raiz);
                cout << "\t]" << endl;
            
                break;
            }
            // 5. 🖨️ Generar grafo.
            case 5:{
                visualizarArbol(raiz);
                break;
            }
            // 6. 🚪🏃 Salir.
            case 6:  {
                cout << "> Saliendo del programa...\n";
                break;
            }
            default:{
                cout << "⚠️  Opcion no valida. Intente de nuevo .\n";
            }
        }
    } 

    return 0;
}
