#include <stdlib.h>
#include <iostream>
#include <limits>
using namespace std;

// ─────────────| Controles de entrada |─────────────¬
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

// ─────────────| Sobre los caracteres |─────────────¬
void leer_nodos(string *vector, int totalElem) {
    int inicio = 97; // 'a'
    for (int i = 0; i < totalElem; i++) {
        vector[i] = static_cast<char>(inicio + i);  // a, b, c, etc.
    }
}


// ─────────────| Sobre la matriz |─────────────¬
// inicializa un vector. recibe el vector como un puntero.
void inicializar_vector_caracter(string *vector, int totalElem) {
    int col;
  
    // recorre el vector.
    for (col=0; col<totalElem; col++) {
        vector[col] = ' ';
    }
}

// imprime un vector. recibe el vector como un puntero.
void imprimir_vector_caracter(string *vector, int totalElem, string nombreVector) {
    for (int i=0; i<totalElem; i++) {
        cout << nombreVector << "[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

// Imprime matriz
void imprimir_matriz(int **matriz, int totalElem) {
    cout << endl;
    for (int fila=0; fila<totalElem; fila++) {
        for (int col=0; col<totalElem; col++) {
            cout << "\t|" << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}


// ─────────────| Ingresa datos a la matriz |─────────────¬
void leer_datos_matriz(int **matriz, int matriz_size) {
    int valor;
    char decision;

    cout << "\n+x Ingrese los datos de la matriz de adyacencia x+\n";
    cout << "\tOrganizados de forma: matriz[Fila][columna]\n\t(ingrese -1 si no hay conexión)\n" << endl;
    for (int fila=0; fila<matriz_size; fila++) {
        for (int col=0; col<matriz_size; col++) {
            // Evita que se pida valor por si mismo
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


// ─────────────| Dijkstra |─────────────¬
void aplicar_dijkstra(string *V, string *S, string *VS, int *D, int **M, int totalElem) {
    cout << "\n─────────────| Dijkstra |─────────────¬\n";

    // Inicializa D con la fila 0 de la matriz (distancias desde el primer nodo)
    for (int col = 0; col < totalElem; col++)
        D[col] = M[0][col];
    
    // Muestra estado inicial
    cout << "<──| Estados iniciales |──>\n\n- matriz:";
    imprimir_matriz(M, totalElem);
    cout << "\n- vectores:\n";
    imprimir_vector_caracter(S, totalElem, "S");
    imprimir_vector_caracter(VS, totalElem, "VS");
    
    cout << "\n- Distancias iniciales:\n";
    for (int i = 0; i < totalElem; i++)
        cout << "D[" << i << "] = " << D[i] << " ";
    cout << endl;
    cout << "\n──────────────────────────────────────¬\n";

    // Agrega el primer vértice (V[0]) a S
    S[0] = V[0];
    cout << "\nPrimer vértice agregado a S: " << S[0] << endl;

    // Actualiza VS (vertices que no están en S)
    int k = 0;
    for (int j = 0; j < totalElem; j++) {
        bool found = false;
        for (int i = 0; i < totalElem; i++)
            if (S[i] == V[j]) found = true;
        if (!found)
            VS[k++] = V[j];
    }

    imprimir_vector_caracter(VS, totalElem, "VS");
    cout << "\n───────────| Fin Dijkstra |────────────\n";
}


// ─────────────| Main |─────────────¬
int main(int argc, char **argv) {
    // número de elementos.
    int totalElem; 

// <──| Err: mala ejecucion. |──>
    if (argc<2) {
        cout << "⚠️  Utilice: ./[ejecutable] [n° de nodos]" << endl;
        return 1;
    } 
    if (atoi(argv[1])<2) {
        cout << "⚠️  El número de nodos debe ser mayor o igual a 2." << endl;
        return 1;
    }

// <──| Convierte string a entero. |──>
    totalElem = atoi(argv[1]);

    
// <──| Creación de matriz. |──>
    // crea matriz nxn de enteros.
    int **matriz;
    matriz = new int*[totalElem];
    for(int i=0; i<totalElem; i++)
        matriz[i] = new int[totalElem];

    // Lee los datos de la matriz.
    leer_datos_matriz(matriz, totalElem);

// <──| Creación de vectores. |──>
    // Vectores de carácteres
    string V[totalElem];
    string S[totalElem];
    string VS[totalElem];

    // inicializa vectores.
    inicializar_vector_caracter(V, totalElem);
    inicializar_vector_caracter(S, totalElem);
    inicializar_vector_caracter(VS, totalElem);

    // Lee los nodos para agregar caracteres [a, b, c...] al vector V.
    leer_nodos(V, totalElem);


// <──| Imprime la matriz. |──>
    imprimir_matriz(matriz, totalElem);

// <──| Aplica el algoritmo de Dijkstra. |──>
    int D[totalElem];
    aplicar_dijkstra(V, S, VS, D, matriz, totalElem);
    imprimir_vector_caracter(V, totalElem, "V");
    
// <──| Libera memoria de la matriz. |──>
    for (int i = 0; i < totalElem; i++)
        delete[] matriz[i];
    delete[] matriz;

    return 0;
}
