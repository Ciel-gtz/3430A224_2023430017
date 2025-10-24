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
    int FE;
    string function; // Equivalente a Function de archivo GO
    float score; // Equivalente a Score de archivo GO
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

// Usuario debe escribir float
float controlFLOAT() { 
    float valor;
    while (true){
        cin >> valor;
        if (!cin) {
        cout << "⚠️  Solo se permiten numeros\n⚠️  Utilice '.' como decimal, no ',': ";
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
void insercionBalanceado(Nodo** nodocabeza, bool* BO, string function, float score) {
    Nodo* nodo = *nodocabeza;
    Nodo* nodo1;
    Nodo* nodo2;

    if (nodo != nullptr) {
        if (score < nodo->score) {
            insercionBalanceado(&(nodo->izquierda), BO, function, score);
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
                        if (nodo1->FE <= 0) { // Rotacion II
                            nodo->izquierda = nodo1->derecha;
                            nodo1->derecha = nodo;
                            nodo->FE = 0;
                            nodo = nodo1;
                        } else { // Rotacion ID
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
        } else if (score > nodo->score) {
            insercionBalanceado(&(nodo->derecha), BO, function, score);
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
                        if (nodo1->FE >= 0) { // Rotacion DD
                            nodo->derecha = nodo1->izquierda;
                            nodo1->izquierda = nodo;
                            nodo->FE = 0;
                            nodo = nodo1;
                        } else { // Rotacion DI
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
        nodo->function = function;
        nodo->score = score;
        nodo->FE = 0;
        *BO = true;
    }

    *nodocabeza = nodo;
}

// Busca un valor en el arbol
bool Busqueda(Nodo* nodo, float score) {
    if (nodo != nullptr) {
        if (score < nodo->score)
            Busqueda(nodo->izquierda, score);
        else if (score > nodo->score)
            Busqueda(nodo->derecha, score);
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
                if (nodo1->FE >= 0) { // Rotacion DD
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
                } else { // Rotacion DI
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
                if (nodo1->FE <= 0) { // Rotacion II
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
        otro->score = aux->score;
        aux = aux->izquierda;
        *BO = true;
    }
    *aux1 = aux;
    *otro1 = otro;
}

void EliminacionBalanceado(Nodo** nodocabeza, bool* BO, float score) {
    Nodo *nodo, *otro;
    nodo = *nodocabeza;
    if (nodo != nullptr) {
        if (score < nodo->score) {
            EliminacionBalanceado(&(nodo->izquierda), BO, score);
            Restructura1(&nodo, BO);
        } else if (score > nodo->score) {
            EliminacionBalanceado(&(nodo->derecha), BO, score);
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
        string label = nodo->function + "\\n" + to_string(nodo->score);

        // Hijo izquierdo
        if (nodo->izquierda != nullptr) {
            string leftLabel = nodo->izquierda->function + "\\n" + to_string(nodo->izquierda->score);
            fp << "\"" << label << "\" -> \"" << leftLabel << "\" [label=\"" << nodo->izquierda->FE << "\"];\n";

        } else {
            string nullLeft = label + "i";
            fp << "\"" << label << "\" -> \"" << nullLeft << "\" [label=\"" << nodo->FE << "\"];\n";
            fp << "\"" << nullLeft << "\" [fillcolor=\"#727275ff\"];\n";  // <- different color
        }

        // Hijo derecho
        if (nodo->derecha != nullptr) {
            string rightLabel = nodo->derecha->function + "\\n" + to_string(nodo->derecha->score);
            fp << "\"" << label << "\" -> \"" << rightLabel << "\" [label=\"" << nodo->derecha->FE << "\"];\n";
        } else {
            string nullRight = label + "d";
            fp << "\"" << label << "\" -> \"" << nullRight << "\" [label=\"" << nodo->FE << "\"];\n";
            fp << "\"" << nullRight << "\" [fillcolor=\"#727275ff\"];\n";  // <- different color
        }

        fp << "\n";

        preOrden(nodo->izquierda, fp);
        preOrden(nodo->derecha, fp);
    }
}

// Generar grafo con Graphviz (.png y .txt) 
void generarGrafo(Nodo* ArbolInt, string nombreTXT, string nombrePNG) {
    if (!ArbolInt) return;
    ofstream fp(nombreTXT);

    fp << "digraph G {\n\n";
    fp << "node [style=filled fillcolor=\"#89d1daff\" shape=box];\n";

    string raiz_etiqueta = ArbolInt->function + "\\n" + to_string(ArbolInt->score);
    fp << "null [shape=point];\n";
    fp << "null -> \"" << raiz_etiqueta << "\" [label=\"" << ArbolInt->FE << "\"];\n";


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
        // Variables para el arbol
    Nodo* raiz = nullptr;
    bool inicio = false;
        // Sobre la lectura del archivo
    string fileGO, line, go_id, temp_score_GO;
        // Variables de trabajo con el usuario + info nodos
    string function, nombre;
    int opcion;
    float score;


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

    // Obteniendo informacon del archivo
    while (getline(file_csv, line)) {
        stringstream ss(line);
        getline(ss, go_id, ';'); // salta 'GO:[code]' de csv
        // getline(ss, temp_GO, ';');
        getline(ss, function, ';'); // function es 'Function' del csv
        getline(ss, temp_score_GO, ';');
        
        score = stof(temp_score_GO); // score es 'Score' del csv
        bool inicio = false;
        insercionBalanceado(&raiz, &inicio, function, score);
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
                cout << "Ingresar Score: ";
                score = controlFLOAT();
                
                cout << "Ahora ingrese Function: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, function); // Lee tambien espacios 

                inicio = false;
                insercionBalanceado(&raiz, &inicio, function, score);
                generarGrafo(raiz, nombreTXT, nombrePNG);

                break;
            }

            // 2. 👁️ Buscar dato.
            case 2: {
                // que busque identificador?? idk
                cout << "Buscar via Score: ";
                score = controlFLOAT();
                Busqueda(raiz, score);

                break; 
            }

            // 3. ❌  Eliminar dato.
            case 3: {       
                cout << "Eliminar via Score: ";
                score = controlFLOAT();
                inicio = false;

                EliminacionBalanceado(&raiz, &inicio, score);
                generarGrafo(raiz, nombreTXT, nombrePNG);

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

                generarGrafo(raiz, nombreTXT, nombrePNG);
                system(abrir.c_str());
            
                break;
            }

            // 5. 🚪🏃 Salir.
            case 5:  {
                system("clear");
                return 0;
            }

            // Err
            default:{
                cout << "⚠️  Opcion no valida. Intente de nuevo .\n";
            }
        }
    } 
    return 1;    
}
