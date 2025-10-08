#include <limits>
#include <fstream>
#include <iostream>

using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* crearNodo(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}


// Controles de entrada para evadir errores
char userDecision(){ // from: https://stackoverflow.com/questions/43972500/how-to-only-accept-y-or-n-in-users-input-in-c
    char userAnswer;
    do {
        cout << "[s/n] : ";
        cin >> userAnswer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        userAnswer = (char)tolower(userAnswer); // from: https://www.geeksforgeeks.org/cpp/tolower-function-in-cpp/
    } 
    while( !std::cin.fail() && userAnswer!='s' && userAnswer!='n' );

    return userAnswer;   
}

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


// Funcion recursiva para construir el arbol manualmente
void crearArbol(Node* &apnodo) {
    if (apnodo == nullptr) {
        int valor;
        cout << "\n> Ingrese valor para el nodo : ";
        valor = controlINT();
        apnodo = crearNodo(valor);
    }

    char resp;

    // Preguntar por hijo izquierdo
    cout << "◀ ¿Existe nodo a la izquierda de " << apnodo->info << "? ";
    resp = userDecision();
    if (resp == 's') {
        apnodo->left = nullptr; // inicializar
        crearArbol(apnodo->left); // llamada recursiva
    } else {
        apnodo->left = nullptr;
    }

    // Preguntar por hijo derecho
    cout << "▶ ¿Existe nodo a la derecha de " << apnodo->info << "? ";
    resp = userDecision();
    if (resp == 's') {
        apnodo->right = nullptr;
        crearArbol(apnodo->right); // llamada recursiva
    } else {
        apnodo->right = nullptr;
    }
}


// Funciones recursivas para imprimir el arbol...
// En Preorden
void printPreOrden(Node* node) {
    if (node == nullptr) {
        return;
    }
    cout << node->info << " ";   // Imprimir el dato del nodo actual
    printPreOrden(node->left);   // Recorrer el subarbol izquierdo
    printPreOrden(node->right);  // Recorrer el subarbol derecho
}

// En Inorden
void printInOrden(Node* node) {
    if (node == nullptr) {
        return;
    }
    printInOrden(node->left);    // Recorrer el subarbol izquierdo
    cout << node->info << " ";    // Imprimir el dato del nodo actual
    printInOrden(node->right);   // Recorrer el subarbol derecho
}

// En Postorden
void printPostOrden(Node* node) {
    if (node == nullptr) {
        return;
    }
    printPostOrden(node->left);   // Recorrer el subarbol izquierdo
    printPostOrden(node->right);  // Recorrer el subarbol derecho
    cout << node->info << " ";    // Imprimir el dato del nodo actual
}

/*
// Recorrer el arbol en preorden y escribir en el archivo
void recorrer(Node* node, ofstream& fp) {
    if (node != nullptr) {
        if (node->left != nullptr) {
            fp << node->info << "->" << node->left->info << ";" << endl;
        } else {
            string cadena = node->info + "i";
            fp << cadena << "[shape=point];" << endl;
            fp << node->info << "->" << cadena << ";" << endl;
        }

        if (node->right != nullptr) {
            fp << node->info << "->" << node->right->info << ";" << endl;
        } else {
            string cadena = node->info + "d";
            fp << cadena << "[shape=point];" << endl;
            fp << node->info << "->" << cadena << ";" << endl;
        }

        recorrer(node->left, fp);
        recorrer(node->right, fp);
    }
}

// Generar y mostrar la visualizacion del arbol
void visualize(Node* root) {
    ofstream fp("arbol.txt");

    if (!fp.is_open()) {
        cerr << "Error al abrir el archivo arbol.txt" << endl;
        return;
    }

    fp << "digraph G {" << endl;
    fp << "node [style=filled fillcolor=yellow];" << endl;

    recorrer(root, fp);

    fp << "}" << endl;

    fp.close();

    // Generar y mostrar la imagen del árbol
    system("dot -Tpng -o arbol.png arbol.txt");
    system("eog arbol.png");
}
*/


/* 
Agregar:
    insertar numero ELEMENTOS UNICOS (recorrer -> insertar)
    eliminar num buscado (recorrer -> eliminar)
    modificar num buscado (recorrer -> eliminar)
    mostrar preorden inorden posordenXX!
    genera grafo
    finalizar

*/

// Menu de opciones
int menu() {
    int opcion = 0;
    cout << "\n\n++++++++++++\nMenu\n";
    cout << "1. ⭕ Insertar nuevo nodo.\n";
    cout << "2. ❌ Eliminar nodo.\n";
    cout << "3. ✍️ Modificar nodo.\n";
    cout << "4. 👁️ Mostrar recorridos del arbol.\n";
    cout << "5. 🖨️ Generar grafo.\n";
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
    Node* root = nullptr;
    int opcion;

    // Primero hace que el usuario construya el arbol
    cout << "──{ Construccion interactiva del arbol binario }──\n";
    crearArbol(root);

    // Para despues trabajar con el:
    
    while (opcion != 6) {

        opcion = menu();

        switch (opcion) {
            // 1. ⭕ Insertar nuevo nodo.
            case 1: 
            
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
                printPreOrden(root);

                cout << " ]\n[ Recorrido en inorden: ";
                printInOrden(root);

                cout << " ]\n[ Recorrido en postorden: ";
                printPostOrden(root);
                cout << " ]" << endl;
            
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
