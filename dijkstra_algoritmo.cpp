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


// ─────────────| Sobre la matriz |─────────────¬
// inicializa un vector. recibe el vector como un puntero.
void inicializar_vector_caracter (string *vector, int n) {
    int col;
  
    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = ' ';
    }
}

// imprime un vector. recibe el vector como un puntero.
void imprimir_vector_caracter(string *vector, int n) {
    cout << endl;
    for (int i=0; i<n; i++) {
        cout << "vector[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

// inicializa matriz nxn. recibe puntero a la matriz.
void inicializar_matriz_enteros (int **matriz, int n) {
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            matriz[fila][col] = -1;
        }
    }
}

// Imprime matriz
void imprimir_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
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


// ─────────────| Main |─────────────¬
int main(int argc, char **argv) {
    // número de elementos.
    int n;

    /* ===== > Err: mala ejecucion */
    if (argc<2) {
        cout << "⚠️  Utilice: ./[ejecutable] [n° de nodos]" << endl;
        return 1;
    } if (atoi(argv[1])<=0) {
        cout << "⚠️  El número de nodos debe ser mayor a 0." << endl;
        return 1;
    }

    // convierte string a entero.
    n = atoi(argv[1]);
    //***string V[n];

    // inicializa e imprime vectores.
    //***inicializar_vector_caracter(V, n);
    //***imprimir_vector_caracter(V, n);

    // crea matriz nxn de enteros.
    int **matriz;
    matriz = new int*[n];
    for(int i=0; i<n; i++)
        matriz[i] = new int[n];

    //***inicializar_matriz_enteros(matriz, n);
    // Lee los datos de la matriz.
    leer_datos_matriz(matriz, n);
    imprimir_matriz(matriz, n);

    return 0;
}
