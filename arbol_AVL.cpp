#include <limits>
#include <vector> // Para guardar valores iniciales en lista
#include <fstream>
#include <iostream>

using namespace std;

struct Nodo {
    Nodo* izquierda;
    Nodo* derecha;
    int info, FE;
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
char userDecision(){
    char userAnswer;
    do {
        cout << "! [s/n] : ";
        cin >> userAnswer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        userAnswer = (char)tolower(userAnswer);
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
Ediciones en Arbol...*/
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
    if (apnodo == nullptr) { // Parar recursion en null branches
        return;
    }

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

// Editar en Arbol
void editarNodo(Nodo* raiz, int valorViejo) {
    // Primero revisa si valorViejo siquiera existe
    Nodo* nodoEditar = buscarNodo(raiz, valorViejo);

    // Si no existe: avisa y se cancela la operacion
    if (nodoEditar == nullptr) {
        cout << "⚠️  El nodo '" << valorViejo << "' no existe en el arbol.\n";
        return;
    }

    // Si existe: se pide nuevo valor
    int valorNuevo;
    cout << "> Nuevo valor para el nodo '" << valorViejo << "' : ";
    valorNuevo = controlINT();

    // Pero si el valor nuevo ya existe, se cancela la operacion
    Nodo* nodoDuplicado = buscarNodo(raiz, valorNuevo);
    if (nodoDuplicado != nullptr) {
        cout << "⚠️  Ya existe el nodo '" << valorNuevo << "'.\n";
        return;
    }

    // Si no, entonces se modifica
    nodoEditar->info = valorNuevo;
    cout << "+x El nodo '" << valorViejo << "' ha sido actualizado a '" << valorNuevo << "' x+" << endl;
}







/* =========================||
Para la generacion del grafo...*/
// Recorrido preorden para generar el grafo
void preOrden(Nodo* nodo, ofstream& fp) {
    if (nodo != nullptr) {
        if (nodo->izquierda != nullptr)
            fp << nodo->info << " -> " << nodo->izquierda->info << ";\n";
        else
            fp << nodo->info << " -> " << "\"" << nodo->info << "i" << "\""<< " [shape=point];\n";
        if (nodo->derecha != nullptr)
            fp << nodo->info << " -> " << nodo->derecha->info << ";\n";
        else
            fp << nodo->info << " -> " << "\"" << nodo->info << "d" << "\""<< " [shape=point];\n";

        preOrden(nodo->izquierda, fp);
        preOrden(nodo->derecha, fp);
    }
}

// Generar grafo con Graphviz (.png y .txt) 
void GenerarGrafo(Nodo* ArbolInt, string nombreArchivo) {
    string nombreTXT = nombreArchivo + ".txt";
    string nombrePNG = nombreArchivo + ".png";

    if (!ArbolInt) return;
    ofstream fp(nombreTXT);
    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=y\"#b56cc3ff\"];\n";
    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz -> " << ArbolInt->info << ";\n";

    preOrden(ArbolInt, fp);

    fp << "}" << endl;

    fp.close();

    string comando = "dot -Tpng -o " + nombrePNG + " " + nombreTXT;

    system(comando.c_str());

}



/*
Funciones GO minimal.cs max 12 terminos, insertado via terminal
(int argc, char ** arg

que menu sea el de AVL.cpp


por cada nodo insertado debe considerar GO, Function, Score, permitiendo mantener la estructura del AVL, a traves de los FE vistos en clases{
que FE sea menor o igual a +- 1}

- crear arbol terminos GO
- insertar termino GO nuevo 
-buscar termino GO
- genera grafoYES!

*/







/* =========================||*/
// Menu de opciones
int menu() {
    int opcion;
    cout << "\n\n++++++++++++\nMenu\n";
    cout << "1. ⭕ Insertar dato.\n"; 
    cout << "2. 👁️ Buscar dato.\n";
    cout << "3. ❌  Eliminar dato.\n";
    cout << "4. 🖨️  Generar grafo.\n";
    cout << "5. 🚪🏃 Salir.\n++++++++++++\n\n";
    cout << "> Seleccione una opcion: ";
    opcion = controlINT();
    while (opcion < 1 || opcion > 5) {
        cout << "\t⚠️  [Debe elegir una opcion valida (1-5)] : ";
        opcion = controlINT();
    }
    return opcion;
}

int main() {
    Nodo* raiz = nullptr;
    int opcion, valor;
    string nombre;
    
    // Primero inserta lo que puso el usuario via terminal NOTYET
    cout << "──{ Construccion de un arbol balanceado AVL }──\n";

    // Para despues trabajar con este arbol inicial:
    while (opcion != 5) {

        opcion = menu();

        switch (opcion) {
            // 1. ⭕ Insertar dato.
            case 1: {
                /*
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
                */

                break;
            }

            // 2. 👁️ Buscar dato.
            case 2: {
                
                break; 
            }

            // 3. ❌  Eliminar dato.
            case 3: {       
                /*
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

                cout << "Arbol actual: [ ";
                printPreOrden(raiz);
                cout << " ]" << endl;
                */

                break;
            }
            // 4. 🖨️  Generar grafo.
            case 4: {
                cout << "> Ingrese un nombre para los archivos .png y .txt: ";
                cin >> nombre; 
                GenerarGrafo(raiz, nombre);
            
                break;
            }
            // 5. 🚪🏃 Salir.
            case 5:  {
                cout << "> Saliendo del programa...\n";

                break;
            }
            // Err
            default:{
                cout << "⚠️  Opcion no valida. Intente de nuevo .\n";
            }
        }
    } 

    return 0;
}
