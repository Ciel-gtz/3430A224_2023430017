#include <limits>
#include <vector> // Para guardar valores iniciales en lista
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/* estructura del nodo */
typedef struct Nodo {
    Nodo* izquierda;
    Nodo* derecha;
    int FE, info, GO; // maybe del or change info bc idk what that would b anymor
    string function;
    float score;
} Nodo;


/* =========================|| Controles de entrada para evadir errores...*/
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


/* =========================|| Sobre el arbol...*/
// Insercion balanceada AVL
void insercionBalanceado(Nodo** nodocabeza, bool* BO, int infor) {
    Nodo* nodo = *nodocabeza;
    Nodo* nodo1;
    Nodo* nodo2;

    if (nodo != nullptr) {
        if (infor < nodo->info) {
            insercionBalanceado(&(nodo->izquierda), BO, infor);
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
            insercionBalanceado(&(nodo->derecha), BO, infor);
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
            cout << "⚠️  El nodo ya se encuentra en el arbol.\n";
        }
    } else {
        nodo = new Nodo();
        nodo->izquierda = nullptr;
        nodo->derecha = nullptr;
        // Add info**********************
        nodo->info = infor;
        nodo->FE = 0;
        *BO = true;
    }

    *nodocabeza = nodo;
}

// Busca un valor en el arbol
bool Busqueda(Nodo* nodo, int infor) {
    if (nodo != nullptr) {
        if (infor < nodo->info)
            Busqueda(nodo->izquierda, infor);
        else if (infor > nodo->info)
            Busqueda(nodo->derecha, infor);
        else
            return true; // El nodo SI se encuentra en el arbol
    } 
    return false; // El nodo NO se encuentra en el arbol
}


/* =========================|| Reestructuraciones...*/
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


/* =========================|| Ediciones en Arbol...*/
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


/* =========================|| Para la generacion del grafo...*/
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


/* =========================|| Menu de opciones */
int menu() {
    int opcion;
    cout << "\n\n++++++++++++\nMenu\n";
    cout << "1. ⭕ Insertar dato.\n"; 
    cout << "2. 👁️  Buscar dato.\n";
    cout << "3. ❌ Eliminar dato.\n";
    cout << "4. 🖨️  Generar + mostrar grafo o guardar grafo en otro archivo.\n";
    cout << "5. 🚪🏃 Salir.\n++++++++++++\n\n";
    cout << "> Seleccione una opcion: ";
    opcion = controlINT();
    while (opcion < 1 || opcion > 5) {
        cout << "\t⚠️  [Debe elegir una opcion valida (1 - 5)] : ";
        opcion = controlINT();
    }
    return opcion;
}


/* =========================|| Main */
int main(int argc, char* argv[]) {
    /* Variables iniciales */
    Nodo* raiz = nullptr;
    int opcion, elemento, location, GO;
    float score;
    string nombre, fileGO, line, function, temp_score_GO, temp_GO, _;
    bool inicio;
    

    /* ===== > Esta seccion es para leer el archivo */
    if (argc < 2) {
        // Si no se ingresa archivo, se avisa y se sale
        cerr << "⚠️  Utilice: ./arbol_AVL <ruta_archivo_GO.csv>" << endl;
        return 1;
    }

    fileGO = argv[1];
    ifstream file_csv(fileGO);

    if (!file_csv) {
        cerr << "⚠️  No se pudo abrir el archivo: " << fileGO << endl;
        return 1;
    }
    
    getline(file_csv, line); // Salta el header

    while (getline(file_csv, line)) {
        stringstream ss(line);
        getline(ss, _, ':'); // salta 'GO:' de csv
        getline(ss, temp_GO, ';');
        getline(ss, function, ';'); // function es 'Function' del csv
        getline(ss, temp_score_GO, ';');
        
        GO = stof(temp_GO); // GO es 'GO' del csv
        score = stof(temp_score_GO); // score es 'Score' del csv
    }

    // Y se cierra el archivo
    file_csv.close();


    /* ===== > Pide nombre de archivo para ir guardando */
    cout << "──{ Construccion de un arbol balanceado AVL }──\n";

    cout << "\n> Ingrese un nombre para los archivos .png y .txt del grafo que va a crear : ";
    cin >> nombre; 

    string nombreTXT = nombre + ".txt";
    string nombrePNG = nombre + ".png";


    /* ===== > Desarrollo de las opciones presentes en el menu */
    while (opcion) { 
        
        opcion = menu();

        switch (opcion) {
            // 1. ⭕ Insertar dato.
            case 1: {
                cout << "Ingresar elemento: ";
                cin >> elemento;
                inicio = false;
                insercionBalanceado(&raiz, &inicio, elemento);
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

            // 4. 🖨️  Generar + mostrar grafo o guardar grafo en otro archivo.
            case 4: {
                // Pregunta en caso de que se quiera guardar el grafo en otro archivo
                cout << "> ¿Desea crear otro archivo en vez de '" << nombre << "'? : ";
                if (userDecision() == 's') {
                    cout << "> Ingrese un nombre para los archivos .png y .txt del grafo nuevo: ";
                    cin >> nombre;
                }

                string nombreTXT = nombre + ".txt";
                string nombrePNG = nombre + ".png";

                string abrir = "eog " + nombrePNG;

                GenerarGrafo(raiz, nombreTXT, nombrePNG);
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
