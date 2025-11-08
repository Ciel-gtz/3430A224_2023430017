#include <stdlib.h>
#include <iostream>
#include <limits>
using namespace std;

// ─────────────| Controles de entrada |─────────────¬

    // Usuario debe escribir int
int controlINT() { 
    int valor;
    while (true){
        cin >> valor;
        // Se modificó para que el usuario no ingrese negativos ni 0, exceptuando -1 
        if (!cin || valor<-1 || valor == 0){
        cout << "⚠️  Solo se permiten numeros positivos o -1 : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
        } else {
            return valor;
        }
    }
}


// ─────────────| Operaciones sobre vectores y matrices |─────────────¬

// Genera los nombres de los nodos en el vector.
void leer_nodos(string *vector, int totalElem) {
    int inicio = 97; // 'a'
    for (int i = 0; i < totalElem; i++) {
        vector[i] = static_cast<char>(inicio + i);  // a, b, c, etc.
    }
}

// Inicializa un vector de strings con espacios en blanco .
void inicializar_vector_caracter(string *vector, int totalElem) {
    int col;
  
    // recorre el vector.
    for (col=0; col<totalElem; col++) {
        vector[col] = ' ';
    }
}

// Imprime un vector de strings con su nombre como etiqueta.
void imprimir_vector_caracter(string *vector, int totalElem, string nombreVector) {
    for (int i=0; i<totalElem; i++) {
        cout << " | " << nombreVector << "[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

// Imprime un vector de enteros,
void imprimir_vector_entero(int *vector, int totalElem) {
    for (int i = 0; i < totalElem; i++){
        cout << " | D[" << i << "] = " << vector[i] << " ";
    }
    cout << endl;
}

// Imprime una matriz.
void imprimir_matriz(int **matriz, int totalElem) {
    cout << endl;
    for (int fila=0; fila<totalElem; fila++) {
        for (int col=0; col<totalElem; col++) {
            cout << "\t|" << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}

// Solicita al usuario ingresar los valores de la matriz.
void leer_datos_matriz(int **matriz, int matriz_size) {
    int valor;

    cout << "\n+x Ingrese los datos de la matriz de adyacencia x+\n" 
         << "\tOrganizados de forma: matriz[Fila][columna]\n" 
         << "\t(ingrese -1 si no hay conexión)\n" << endl;
    
    for (int fila = 0; fila < matriz_size; fila++) {
        for (int col = 0; col < matriz_size; col++) {

            // La diagonal principal siempre vale 0.
            if (fila == col) {
                matriz[fila][col] = 0;
                continue;
            }

            // Copia el valor simétrico ya ingresado para no reiterar pedirlo innecesariamente.
            if (col < fila) {
                matriz[fila][col] = matriz[col][fila];
                continue;
            }

            // Solicita el valor del usuario para esta posición
            cout << ">> matriz[" << fila << "][" << col << "] ---> ";
            valor = controlINT();

            // Asigna el valor ingresado y su copia simétrica
            matriz[fila][col] = valor;
            matriz[col][fila] = valor;
        }
    }
}


// ─────────────| Funciones de apoyo a Prim |─────────────¬

// Busca si un carácter está en un vector.
bool busca_caracter(string c, string *vector, int totalElem) {
    for (int j = 0; j < totalElem; j++) {
        if (c == vector[j]) {
            return true;
        }
    }
    return false;
}

// Agrega un vértice al conjunto S
void agrega_vertice_a_S(string *S, string vertice, int totalElem) {
    for (int i = 0; i < totalElem; i++) {
        if (S[i] == " " || S[i].empty()) { // busca primer espacio vacío
            S[i] = vertice;
            break;
        }
    }
}

// Devuelve el índice de un carácter dentro de un vector.
int buscar_indice_caracter(string *vector, string caracter, int totalElem) {
    for (int i = 0; i < totalElem; i++) {
        if (vector[i] == caracter)
            return i;
    }
    return totalElem; // no encontrado
}

// Actualiza el conjunto VS = V - S
void actualizar_VS(string *V, string *S, string *VS, int totalElem) {
    inicializar_vector_caracter(VS, totalElem);

    int k = 0;
    for (int i = 0; i < totalElem; i++) {
        if (!busca_caracter(V[i], S, totalElem)) {
            VS[k] = V[i];
            k++;
        }
    }
}

// Selecciona el vértice con menor distancia dentro de VS.
int elegir_vertice(string *VS, int *D, string *V, int totalElem) {
    int i = 0;
    int menor = 0;
    int peso;
    int indice_vertice = -1; // -1 si no se encuentra un vértice válido


    // Recorre todos los vértices en VS[] mientras no haya espacios vacíos
    while ((i < totalElem) && (VS[i] != " ")) {
        int indice_VS = buscar_indice_caracter(V, VS[i], totalElem);
        peso = D[indice_VS]; // Obtiene el peso (distancia) desde el vector D[]

        // Ignora pesos inválidos (sin conexión o distancia 0)
        if ((peso != -1) && (peso != 0)) {
            // Si es el primer vértice válido, se guarda directamente como menor
            if (indice_vertice == -1) {
                menor = peso;
                indice_vertice = indice_VS;
            } 
            // Si ya hay uno seleccionado, compara y guarda el menor peso
            else if (peso < menor) {
                menor = peso;
                indice_vertice = indice_VS;
            }
        }
        // Avanza al siguiente vértice de VS[]
        i++;
    }

    // Si encontró un vértice válido, lo muestra y lo retorna
    if (indice_vertice != -1){
        cout << "\n- vertice elegido: " << V[indice_vertice] << " [peso: " << menor << "]\n";
        return indice_vertice;
    }
    
    // Si no encontró ninguno válido, avisa y retorna -1
    else{
        cout << "\n⚠️  No se ha encontrado vertice valido\n";
        return indice_vertice;
    }
}

// Actualiza los pesos de los vértices según la última elección en Prim.
void actualizar_pesos_prim(int *D, string *S, int **M, string *V, int totalElem) {
    cout << "\n> actualiza pesos en D[]\n";

    // Para cada vértice que NO está en S,
    // actualiza su distancia mínima hacia el conjunto S.
    for (int i = 0; i < totalElem; i++) {
        if (!busca_caracter(V[i], S, totalElem)) { // vértice fuera de S
            int menor = -1;
            for (int j = 0; j < totalElem; j++) {
                if (busca_caracter(V[j], S, totalElem) && M[i][j] > 0) {
                    if (menor == -1 || M[i][j] < menor) {
                        menor = M[i][j];
                    }
                }
            }
            D[i] = menor; // -1 si no tiene conexión
        }
    }
}


// ─────────────| Algoritmo de Prim |─────────────¬

void aplicar_prim(string *V, string *S, string *VS, int *D, int **M, int **MST, int totalElem) {
    cout << "\n─────────| Estados iniciales |─────────¬\n";

    /*
    MST -> Matriz del árbol de expansión mínima (Minimum Spanning Tree).
    S -> Conjunto de vértices ya en el MST.
    V -> Lista de todos los vertices del grafo(a, b, c, …).
    M -> matriz de adyacencia original con los pesos.
    */

    // <──| Inicializa D con los pesos de la fila 0 de la matriz |──>
    for (int col = 0; col < totalElem; col++)
        D[col] = M[0][col];
    

    // <──| Muestra estados iniciales |──>
    cout << "- matriz:";
    imprimir_matriz(M, totalElem);
    cout << "\n- vectores:\n";
    imprimir_vector_caracter(S, totalElem, "S");
    imprimir_vector_caracter(VS, totalElem, "VS");
    
    cout << "\n- Distancia inicial:\n";
    imprimir_vector_entero(D, totalElem);


    cout << "\n───────────────| Prim |───────────────¬\n";
    // <──| agrega primer vértice (V[0]) a S |──>

    cout << "<─| Agrega primer valor V[0] a S[] y actualiza VS[] |─>\n\n";

    agrega_vertice_a_S(S, V[0], totalElem);
    imprimir_vector_caracter(S, totalElem, "S");

    actualizar_VS(V, S, VS, totalElem);
    imprimir_vector_caracter(VS, totalElem, "VS");
    
    imprimir_vector_entero(D, totalElem);

    cout << "\n──────────────────────────────────────¬\n";
    // <──| Bucle principal del algoritmo de Prim |──>

    for (int step = 1; step < totalElem; step++) {
        // Selecciona vértice con menor D dentro de VS
        cout << "<─| elige vertice menor en VS[] según valores en D[] |─>\n\n";
        cout << "\t<─| lo agrega a S[] y actualiza VS[] |─>\n\n";

        int v = elegir_vertice(VS, D, V, totalElem); // índice del vértice elegido
        if (v == -1) break; // si no hay vértice válido, termina


        // Busca la conexión mínima entre el vértice elegido y el conjunto S
        int from = -1;
        int peso_min = numeric_limits<int>::max();

        // Recorre todos los vértices que ya están en S para buscar el peso más bajo
        for (int i = 0; i < totalElem; i++) {
            if (busca_caracter(V[i], S, totalElem) && M[i][v] > 0) {
                if (M[i][v] < peso_min) {
                    peso_min = M[i][v];
                    from = i;
                }
            }
        }

        // Guarda la arista elegida en el MST
        if (from != -1 && peso_min != numeric_limits<int>::max()) {
            MST[from][v] = peso_min;
            MST[v][from] = peso_min; // grafo no dirigido
            cout << "→ Agregada al conjunto L: " << V[from] << " - " << V[v]
                 << " (peso " << peso_min << ")\n";
        }

        // -> Añade el vértice elegido a S
        agrega_vertice_a_S(S, V[v], totalElem);
        imprimir_vector_caracter(S, totalElem, "S");

        // -> Actualiza VS
        actualizar_VS(V, S, VS, totalElem);
        imprimir_vector_caracter(VS, totalElem, "VS");

        // -> Actualiza los pesos mínimos hacia el conjunto S
        actualizar_pesos_prim(D, S, M, V, totalElem);
        imprimir_vector_entero(D, totalElem);
    }

    // <──| Muestra las aristas finales del MST (conjunto L) |──>
    cout << "\n────────────── Conjunto L ──────────────\n";

    for (int i = 0; i < totalElem; i++) {
        for (int j = i + 1; j < totalElem; j++) {
            if (MST[i][j] > 0)
                cout << V[i] << " -- " << V[j] << " [peso: " << MST[i][j] << "]\n";
        }
    }

    cout << "\n─────────────| Fin Prim |──────────────\n";
}


// ─────────────| Crea y visualiza grafo con Graphviz |─────────────¬

void imprimir_grafo(int **matriz, string *vector, int totalElem, string nombreArchivo) {
    string dotFile = nombreArchivo + ".txt";
    FILE *fp = fopen(dotFile.c_str(), "w");

    if (!fp) {
        cerr << "⚠️  Error al abrir el archivo " << dotFile << endl;
        return;
    }

    fprintf(fp, "graph G {\n");
    fprintf(fp, "graph [rankdir=LR];\n");
    fprintf(fp, "node [style=filled, fillcolor=\"#ae73cfff\"];\n");

    for (int i = 0; i < totalElem; i++) {
        for (int j = i + 1; j < totalElem; j++) {
            if (matriz[i][j] > 0) {
                fprintf(fp, "%s -- %s [label=%d];\n", vector[i].c_str(), vector[j].c_str(), matriz[i][j]);
            }
        }
    }

    fprintf(fp, "}\n");
    fclose(fp);

    system(("dot -Tpng -o" + nombreArchivo + ".png " + nombreArchivo + ".txt").c_str());
    system(("eog " + nombreArchivo + ".png &").c_str());
}


// ─────────────| Main |─────────────¬

int main(int argc, char **argv) {
    int totalElem; // cantidad de nodos del grafo

// <──| Validación de argumentos de entrada |──>
    if (argc<2) {
        cout << "⚠️  Utilice: ./[ejecutable] [n° de nodos]" << endl;
        return 1;
    } 
    if (atoi(argv[1])<2) {
        cout << "⚠️  El número de nodos debe ser mayor o igual a 2." << endl;
        return 1;
    }

    totalElem = atoi(argv[1]); // conversión de argumento a entero


// <──| inicialización de vectores. |──>
    string V[totalElem];
    string S[totalElem];
    string VS[totalElem];

    inicializar_vector_caracter(V, totalElem);
    inicializar_vector_caracter(S, totalElem);
    inicializar_vector_caracter(VS, totalElem);
    
    leer_nodos(V, totalElem); // llena V con 'a', 'b', 'c', etc.
    imprimir_vector_caracter(V, totalElem, "V"); // Muestra los nodos


// <──| Creación de matriz interactuable. |──>
    int **matriz;
    matriz = new int*[totalElem];
    for(int i=0; i<totalElem; i++)
        matriz[i] = new int[totalElem];

    leer_datos_matriz(matriz, totalElem);


// <──| Creación de matriz para almacenar el MST. |──>
    int **matrizMST;
    matrizMST = new int*[totalElem];
    for (int i = 0; i < totalElem; i++) {
        matrizMST[i] = new int[totalElem];
        for (int j = 0; j < totalElem; j++)
            matrizMST[i][j] = 0; // inicializa en 0
    }


// <──| Ejecución del algoritmo de Prim. |──>
    int D[totalElem];
    aplicar_prim(V, S, VS, D, matriz, matrizMST, totalElem);
    

// <──| Creación y visualización del grafo |──>
    imprimir_grafo(matriz, V, totalElem, "grafo_original");
    imprimir_grafo(matrizMST, V, totalElem, "grafo_minimo");


// <──| Libera memoria de las matrices |──>
    for (int i = 0; i < totalElem; i++) {
        delete[] matriz[i];
        delete[] matrizMST[i];
    }
    delete[] matriz;
    delete[] matrizMST;

    return 0;
}
