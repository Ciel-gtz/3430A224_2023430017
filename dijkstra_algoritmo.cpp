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

    cout << "\n+x Ingrese los datos de la matriz de adyacencia x+\n";
    cout << "\tOrganizados de forma: matriz[Fila][columna]\n\t(ingrese -1 si no hay conexión)\n" << endl;
    for (int fila=0; fila<matriz_size; fila++) {
        for (int col=0; col<matriz_size; col++) {
            // Evita que se pida el valor de si mismo
            if (fila == col) {
                matriz[fila][col] = 0;
                continue;
            }
            
            cout << ">> matriz[" << fila << "][" << col << "] ---> ";
            valor = controlINT();
            matriz[fila][col] = valor;
        }
    }
}


// ─────────────| Funciones de apoyo a Dijkstra |─────────────¬

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
    int indice_vertice = -1; // -1 si no se encuentra

    while ((VS[i] != " ") && (i < totalElem)) {
        int indice_VS = buscar_indice_caracter(V, VS[i], totalElem);
        peso = D[indice_VS];

        if ((peso != -1) && (peso != 0)) {
            if (indice_vertice == -1) {
                menor = peso;
                indice_vertice = indice_VS;
            } else {
                if (peso < menor) {
                    menor = peso;
                    indice_vertice = indice_VS;
                }
            }
        }
        i++;
    }
    if (indice_vertice != -1){
        cout << "\n- vertice elegido: " << V[indice_vertice] << " [peso: " << menor << "]\n";
        return indice_vertice;
    }
        
    else{
        cout << "\n⚠️  No se ha encontrado vertice valido\n";
        return indice_vertice;
    }
}

// Calcula el mínimo entre el peso actual y una posible ruta alternativa.
int calcular_minimo(int dw, int dv, int mvw) {
    int minimo;

    if (dw == -1) {
        if (dv != -1 && mvw != -1)
            minimo = dv + mvw;
        else
            minimo = -1;
    } else {
        if (dv != -1 && mvw != -1) {
            if (dw <= (dv + mvw))
                minimo = dw;
            else
                minimo = (dv + mvw);
        } else {
            minimo = dw;
        }
    }

    cout << "dw: " << dw << " dv: " << dv << " mvw: " << mvw << " min: " << minimo << endl;
    return minimo;
}

// Actualiza los pesos de los vértices según la última elección en Dijkstra.
void actualizar_pesos(int *D, string *VS, int **M, string *V, string v, int totalElem) {
    cout << "\n> actualiza pesos en D[]\n";

    int i = 0;
    int indice_w, indice_v;

    indice_v = buscar_indice_caracter(V, v, totalElem);
    while ((VS[i] != " ") && (i < totalElem)) {
        if (VS[i] != v) {
            indice_w = buscar_indice_caracter(V, VS[i], totalElem);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
        i++;
    }
}


// ─────────────| Algoritmo de Dijkstra |─────────────¬

void aplicar_dijkstra(string *V, string *S, string *VS, int *D, int **M, int totalElem) {
    cout << "\n─────────| Estados iniciales |─────────¬\n";

    // V: todos los vértices
    // S: vértices ya visitados
    // VS: vértices aún no visitados
    // D: distancias mínimas


    // Inicializa D con la fila 0 de la matriz (distancias desde el primer nodo)
    for (int col = 0; col < totalElem; col++)
        D[col] = M[0][col];
    
    // Muestra estado inicial
    cout << "- matriz:";
    imprimir_matriz(M, totalElem);
    cout << "\n- vectores:\n";
    imprimir_vector_caracter(S, totalElem, "S");
    imprimir_vector_caracter(VS, totalElem, "VS");
    
    cout << "\n- Distancia inicial:\n";
    imprimir_vector_entero(D, totalElem);

    cout << "\n─────────────| Dijkstra |─────────────¬\n";

      // agrega primer vértice (V[0]) al conjunto S
    cout << "<─| Agrega primer valor V[0] a S[] y actualiza VS[] |─>\n\n";

    agrega_vertice_a_S(S, V[0], totalElem);
    imprimir_vector_caracter(S, totalElem, "S");

    actualizar_VS(V, S, VS, totalElem);
    imprimir_vector_caracter(VS, totalElem, "VS");
    
    imprimir_vector_entero(D, totalElem);

    cout << "\n──────────────────────────────────────¬\n";

    // Bucle principal del algoritmo
    for (int i = 1; i < totalElem; i++) {
        // elige un vértice en v de VS[] tal que D[v] sea el mínimo 
        cout << "\n> elige vertice menor en VS[] según valores en D[]\n";
        cout << "> lo agrega a S[] y actualiza VS[]\n";
        int v = elegir_vertice(VS, D, V, totalElem);
        
        agrega_vertice_a_S(S, V[v], totalElem);
        imprimir_vector_caracter(S, totalElem, "S");

        actualizar_VS(V, S, VS, totalElem);
        imprimir_vector_caracter(VS, totalElem, "VS");

        actualizar_pesos(D, VS, M, V, V[v], totalElem);
        imprimir_vector_entero(D, totalElem);
    }
    
    cout << "\n───────────| Fin Dijkstra |────────────\n";
}


// ─────────────| Crea y visualiza grafo con Graphviz |─────────────¬

void imprimir_grafo(int **matriz, string *vector, int totalElem) {
    FILE *fp = fopen("grafo.txt", "w");

    if (!fp) {
        cerr << "⚠️  Error al abrir el archivo grafo.txt" << endl;
        return;
    }

    fprintf(fp, "digraph G {\n");
    fprintf(fp, "graph [rankdir=LR];\n");
    fprintf(fp, "node [style=filled, fillcolor=\"#ae73cfff\" ];\n");

    for (int i = 0; i < totalElem; i++) {
        for (int j = 0; j < totalElem; j++) {
            if (i != j && matriz[i][j] > 0) {
                fprintf(fp, "%s -> %s [label=%d];\n", vector[i].c_str(), vector[j].c_str(), matriz[i][j]);
            }
        }
    }

    fprintf(fp, "}\n");
    fclose(fp);
    
    // Genera imagen y la abre con eog
    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
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


// <──| Creación de matriz interactuable. |──>
    int **matriz;
    matriz = new int*[totalElem];
    for(int i=0; i<totalElem; i++)
        matriz[i] = new int[totalElem];

    leer_datos_matriz(matriz, totalElem);

// <──| inicialización de vectores. |──>
    string V[totalElem];
    string S[totalElem];
    string VS[totalElem];

    inicializar_vector_caracter(V, totalElem);
    inicializar_vector_caracter(S, totalElem);
    inicializar_vector_caracter(VS, totalElem);
    
    leer_nodos(V, totalElem); // llena V con 'a', 'b', 'c', etc.
    imprimir_vector_caracter(V, totalElem, "V");
    
// <──| Ejecución del algoritmo de Dijkstra. |──>
    int D[totalElem];
    aplicar_dijkstra(V, S, VS, D, matriz, totalElem);
    
// <──| Creación y visualización del grafo |──>
    imprimir_grafo(matriz, V, totalElem);

// <──| Libera memoria de la matriz. |──>
    for (int i = 0; i < totalElem; i++)
        delete[] matriz[i];
    delete[] matriz;

    return 0;
}
