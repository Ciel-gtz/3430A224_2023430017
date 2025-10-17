#include <limits>
#include <vector> // Para guardar valores iniciales en lista
#include <fstream>
#include <iostream>

using namespace std;

/* estructura del nodo */
typedef struct Nodo {
    Nodo* izquierda;
    Nodo* derecha;
    int info, FE;
} Nodo;

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
// Insercion balanceada AVL
void InsercionBalanceado(Nodo** nodocabeza, bool* BO, int infor) {
    Nodo* nodo = *nodocabeza;
    Nodo* nodo1;
    Nodo* nodo2;

    if (nodo != nullptr) {
        if (infor < nodo->info) {
            InsercionBalanceado(&(nodo->izquierda), BO, infor);
            if (*BO) {
                switch (nodo->FE) {
                    case 1:
                        nodo->FE = 0;
                        *BO = false;
                        break;
                    case 0:
                        nodo->FE = -1;
                        break;
                    case -1:
                        nodo1 = nodo->izquierda;
                        if (nodo1->FE <= 0) { // Rotación II
                            nodo->izquierda = nodo1->derecha;
                            nodo1->derecha = nodo;
                            nodo->FE = 0;
                            nodo = nodo1;
                        } else { // Rotación ID
                            nodo2 = nodo1->derecha;
                            nodo->izquierda = nodo2->derecha;
                            nodo2->derecha = nodo;
                            nodo1->derecha = nodo2->izquierda;
                            nodo2->izquierda = nodo1;

                            if (nodo2->FE == -1)
                                nodo->FE = 1;
                            else
                                nodo->FE = 0;

                            if (nodo2->FE == 1)
                                nodo1->FE = -1;
                            else
                                nodo1->FE = 0;
                            nodo = nodo2;
                        }
                        nodo->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else if (infor > nodo->info) {
            InsercionBalanceado(&(nodo->derecha), BO, infor);
            if (*BO) {
                switch (nodo->FE) {
                    case -1:
                        nodo->FE = 0;
                        *BO = false;
                        break;
                    case 0:
                        nodo->FE = 1;
                        break;
                    case 1:
                        nodo1 = nodo->derecha;
                        if (nodo1->FE >= 0) { // Rotación DD
                            nodo->derecha = nodo1->izquierda;
                            nodo1->izquierda = nodo;
                            nodo->FE = 0;
                            nodo = nodo1;
                        } else { // Rotación DI
                            nodo2 = nodo1->izquierda;
                            nodo->derecha = nodo2->izquierda;
                            nodo2->izquierda = nodo;
                            nodo1->izquierda = nodo2->derecha;
                            nodo2->derecha = nodo1;

                            if (nodo2->FE == 1)
                                nodo->FE = -1;
                            else
                                nodo->FE = 0;

                            if (nodo2->FE == -1)
                                nodo1->FE = 1;
                            else
                                nodo1->FE = 0;

                            nodo = nodo2;
                        }
                        nodo->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else {
            cout << "El nodo ya se encuentra en el árbol\n";
        }
    } else {
        nodo = new Nodo();
        nodo->izquierda = nullptr;
        nodo->derecha = nullptr;
        nodo->info = infor;
        nodo->FE = 0;
        *BO = true;
    }

    *nodocabeza = nodo;
}

// Busca un valor en el arbol
void Busqueda(Nodo* nodo, int infor) {
    if (nodo != nullptr) {
        if (infor < nodo->info)
            Busqueda(nodo->izquierda, infor);
        else if (infor > nodo->info)
            Busqueda(nodo->derecha, infor);
        else
            cout << "El nodo SÍ se encuentra en el árbol\n";
    } else {
        cout << "El nodo NO se encuentra en el árbol\n";
    }
}

/* =========================||
Reestructuraciones...*/
void Restructura1(Nodo** nodocabeza, bool* BO) {
    Nodo *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    if (*BO) {
        switch (nodo->FE) {
            case -1:
                nodo->FE = 0;
                break;
            case 0:
                nodo->FE = 1;
                *BO = false;
                break;
            case 1:
                nodo1 = nodo->derecha;
                if (nodo1->FE >= 0) { // Rotación DD
                    nodo->derecha = nodo1->izquierda;
                    nodo1->izquierda = nodo;
                    switch (nodo1->FE) {
                        case 0:
                            nodo->FE = 1;
                            nodo1->FE = -1;
                            *BO = false;
                            break;
                        case 1:
                            nodo->FE = 0;
                            nodo1->FE = 0;
                            *BO = false;
                            break;
                    }
                    nodo = nodo1;
                } else { // Rotación DI
                    nodo2 = nodo1->izquierda;
                    nodo->derecha = nodo2->izquierda;
                    nodo2->izquierda = nodo;
                    nodo1->izquierda = nodo2->derecha;
                    nodo2->derecha = nodo1;
                    if (nodo2->FE == 1)
                        nodo->FE = -1;
                    else
                        nodo->FE = 0;
                    if (nodo2->FE == -1)
                        nodo1->FE = 1;
                    else
                        nodo1->FE = 0;
                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }
    *nodocabeza = nodo;
}

void Restructura2(Nodo** nodocabeza, bool* BO) {
    Nodo *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    if (*BO) {
        switch (nodo->FE) {
            case 1:
                nodo->FE = 0;
                break;
            case 0:
                nodo->FE = -1;
                *BO = false;
                break;
            case -1:
                nodo1 = nodo->izquierda;
                if (nodo1->FE <= 0) { // Rotación II
                    nodo->izquierda = nodo1->derecha;
                    nodo1->derecha = nodo;
                    switch (nodo1->FE) {
                        case 0:
                            nodo->FE = -1;
                            nodo1->FE = 1;
                            *BO = false;
                            break;
                        case -1:
                            nodo->FE = 0;
                            nodo1->FE = 0;
                            *BO = false;
                            break;
                    }
                    nodo = nodo1;
                } else { // Rotación ID
                    nodo2 = nodo1->derecha;
                    nodo->izquierda = nodo2->derecha;
                    nodo2->derecha = nodo;
                    nodo1->derecha = nodo2->izquierda;
                    nodo2->izquierda = nodo1;
                    if (nodo2->FE == -1)
                        nodo->FE = 1;
                    else
                        nodo->FE = 0;
                    if (nodo2->FE == 1)
                        nodo1->FE = -1;
                    else
                        nodo1->FE = 0;
                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }
    *nodocabeza = nodo;
}




/* =========================||
Ediciones en Arbol...*/
// Eliminar en Arbol
void Borra(Nodo** aux1, Nodo** otro1, bool* BO) {
    Nodo *aux, *otro;
    aux = *aux1;
    otro = *otro1;
    if (aux->derecha != nullptr) {
        Borra(&(aux->derecha), &otro, BO);
        Restructura2(&aux, BO);
    } else {
        otro->info = aux->info;
        aux = aux->izquierda;
        *BO = true;
    }
    *aux1 = aux;
    *otro1 = otro;
}

void EliminacionBalanceado(Nodo** nodocabeza, bool* BO, int infor) {
    Nodo *nodo, *otro;
    nodo = *nodocabeza;
    if (nodo != nullptr) {
        if (infor < nodo->info) {
            EliminacionBalanceado(&(nodo->izquierda), BO, infor);
            Restructura1(&nodo, BO);
        } else if (infor > nodo->info) {
            EliminacionBalanceado(&(nodo->derecha), BO, infor);
            Restructura2(&nodo, BO);
        } else {
            otro = nodo;
            if (otro->derecha == nullptr) {
                nodo = otro->izquierda;
                *BO = true;
                delete otro;
            } else if (otro->izquierda == nullptr) {
                nodo = otro->derecha;
                *BO = true;
                delete otro;
            } else {
                Borra(&(otro->izquierda), &otro, BO);
                Restructura1(&nodo, BO);
                delete otro;
            }
        }
    } else {
        cout << "El nodo NO se encuentra en el arbol\n";
    }
    *nodocabeza = nodo;
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
void GenerarGrafo(Nodo* ArbolInt, string nombreTXT, string nombrePNG) {
    if (!ArbolInt) return;
    ofstream fp(nombreTXT);
    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=\"#b56cc3ff\"];\n";
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
    cout << "2. 👁️  Buscar dato.\n";
    cout << "3. ❌ Eliminar dato.\n";
    cout << "4. 🖨️  Generar grafo o guardar grafo en otro archivo.\n";
    cout << "5. 🚪🏃 Salir.\n++++++++++++\n\n";
    cout << "> Seleccione una opcion: ";
    opcion = controlINT();
    while (opcion < 1 || opcion > 5) {
        cout << "\t⚠️  [Debe elegir una opcion valida (1 - 5)] : ";
        opcion = controlINT();
    }
    return opcion;
}

int main(int argc, char* argv[]) {
    Nodo* raiz = nullptr;
    int opcion, valor, elemento;
    string nombre, archivoGO, line;
    bool inicio;
    
    //
    // Se lee el archivo que el usuario ingrese
    if (argc < 2) {
        // Si no se ingresa archivo, se avisa y se sale
        cerr << "⚠️  Utilice: ./arbol_AVL <ruta_archivo_GO.csv>" << endl;
        return 1; // Se retorna 1 para indicar error
    }

    archivoGO = argv[1];
    ifstream file_GO(archivoGO);

    if (!file_GO) {
        cerr << "⚠️  No se pudo abrir el archivo: " << archivoGO << endl;
        return 1;
    }

    while (getline(file_GO, line)) {

    }


    // Primero inserta lo que puso el usuario via terminal NOTYET
    cout << "──{ Construccion de un arbol balanceado AVL }──\n";

    cout << "\n> Ingrese un nombre para los archivos .png y .txt del grafo que va a crear : ";
    cin >> nombre; 

    string nombreTXT = nombre + ".txt";
    string nombrePNG = nombre + ".png";

    // Para despues trabajar con este arbol inicial:
    while (opcion != 5) { 
        
        opcion = menu();

        switch (opcion) {
            // 1. ⭕ Insertar dato.
            case 1: {
                cout << "Ingresar elemento: ";
                cin >> elemento;
                inicio = false;
                InsercionBalanceado(&raiz, &inicio, elemento);
                GenerarGrafo(raiz, nombreTXT, nombrePNG);

                break;
            }

            // 2. 👁️ Buscar dato.
            case 2: {
                // que busque identificador?? idk
                cout << "Buscar elemento: ";
                cin >> elemento;
                Busqueda(raiz, elemento);

                break; 
            }

            // 3. ❌  Eliminar dato.
            case 3: {       
                cout << "Eliminar elemento: ";
                cin >> elemento;
                inicio = false;
                EliminacionBalanceado(&raiz, &inicio, elemento);
                GenerarGrafo(raiz, nombreTXT, nombrePNG);

                break;
            }
            // 4. 🖨️  Generar grafo.
            case 4: {
                // Pregunta en caso de que se quieran guardar más grafos
                cout << "> ¿Desea crear otro archivo en vez de '" << nombre << "'? : ";
                if (userDecision() == 's') {
                    cout << "> Ingrese un nombre para los archivos .png y .txt del grafo nuevo: ";
                    cin >> nombre;
                }
                string nombreTXT = nombre + ".txt";
                string nombrePNG = nombre + ".png";

                GenerarGrafo(raiz, nombreTXT, nombrePNG);
                
                string abrir = "eog " + nombrePNG;
                system(abrir.c_str());
            
                break;
            }
            // 5. 🚪🏃 Salir.
            case 5:  {
                system("clear");

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
