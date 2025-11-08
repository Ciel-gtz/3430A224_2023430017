#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#define TRUE 0
#define FALSE 1
#define N 5

using namespace std;

int calcular_minimo(int dw, int dv, int mvw) {
    int min = 0;

    if (dw == -1) {
        if (dv != -1 && mvw != -1)
            min = dv + mvw;
        else
            min = -1;
    } else {
        if (dv != -1 && mvw != -1) {
            if (dw <= (dv + mvw))
                min = dw;
            else
                min = (dv + mvw);
        } else {
            min = dw;
        }
    }

    cout << "dw: " << dw << " dv: " << dv << " mvw: " << mvw << " min: " << min << endl;
    return min;
}

int buscar_indice_caracter(char V[N], char caracter) {
    for (int i = 0; i < N; i++) {
        if (V[i] == caracter)
            return i;
    }
    return N; // no encontrado
}

void inicializar_vector_D(int D[N], int M[N][N]) {
    for (int col = 0; col < N; col++) {
        D[col] = M[0][col];
    }
}

void inicializar_vector_caracter(char vector[N]) {
    for (int col = 0; col < N; col++) {
        vector[col] = ' ';
    }
}

void actualizar_pesos(int D[N], char VS[N], int M[N][N], char V[N], char v) {
    cout << "\n> actualiza pesos en D[]\n";

    int i = 0;
    int indice_w, indice_v;

    indice_v = buscar_indice_caracter(V, v);
    while (VS[i] != ' ' && i < N) {
        if (VS[i] != v) {
            indice_w = buscar_indice_caracter(V, VS[i]);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
        i++;
    }
}



void agrega_vertice_a_S(char S[N], char vertice) {
    for (int i = 0; i < N; i++) {
        if (S[i] == ' ') {
            S[i] = vertice;
            return;
        }
    }
}



int elegir_vertice(char VS[N], int D[N], char V[N]) {
    int i = 0;
    int menor = 0;
    int peso;
    int vertice = ' ';

    while (VS[i] != ' ' && i < N) {
        peso = D[buscar_indice_caracter(V, VS[i])];
        if ((peso != -1) && (peso != 0)) {
            if (vertice == ' ') {
                menor = peso;
                vertice = VS[i];
            } else {
                if (peso < menor) {
                    menor = peso;
                    vertice = VS[i];
                }
            }
        }
        i++;
    }

    cout << "\nvertice: " << vertice << "\n\n";
    return vertice;
}

int busca_caracter(char c, char vector[N]) {
    for (int j = 0; j < N; j++) {
        if (c == vector[j]) {
            return TRUE;
        }
    }
    return FALSE;
}

void actualizar_VS(char V[N], char S[N], char VS[N]) {
    inicializar_vector_caracter(VS);
    int k = 0;
    for (int j = 0; j < N; j++) {
        if (busca_caracter(V[j], S) != TRUE) {
            VS[k] = V[j];
            k++;
        }
    }
}

void leer_nodos(char vector[N]) {
    int inicio = 97; // 'a'
    for (int i = 0; i < N; i++) {
        vector[i] = static_cast<char>(inicio + i);
    }
}

void imprimir_vector_caracter(char vector[N], const char *nomVector) {
    for (int i = 0; i < N; i++) {
        cout << nomVector << "[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

void imprimir_vector_entero(int vector[N]) {
    for (int i = 0; i < N; i++) {
        cout << "D[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

void imprimir_matriz(int matriz[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "matriz[" << i << "," << j << "]: " << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void aplicar_dijkstra(char V[N], char S[N], char VS[N], int D[N], int M[N][N]) {
    inicializar_vector_D(D, M);

    cout << "---------Estados iniciales ---------------------------------------\n";
    imprimir_matriz(M);
    cout << "\n";
    imprimir_vector_caracter(S, "S");
    imprimir_vector_caracter(VS, "VS");
    imprimir_vector_entero(D);
    cout << "------------------------------------------------------------------\n\n";

    cout << "> agrega primer valor V[0] a S[] y actualiza VS[]\n\n";
    agrega_vertice_a_S(S, V[0]);
    imprimir_vector_caracter(S, "S");
    actualizar_VS(V, S, VS);
    imprimir_vector_caracter(VS, "VS");
    imprimir_vector_entero(D);

    for (int i = 1; i < N; i++) {
        cout << "\n> elige vertice menor en VS[] según valores en D[]\n";
        cout << "> lo agrega a S[] y actualiza VS[]\n";
        int v = elegir_vertice(VS, D, V);

        agrega_vertice_a_S(S, static_cast<char>(v));
        imprimir_vector_caracter(S, "S");

        actualizar_VS(V, S, VS);
        imprimir_vector_caracter(VS, "VS");

        actualizar_pesos(D, VS, M, V, static_cast<char>(v));
        imprimir_vector_entero(D);
    }
}

void imprimir_grafo(int matriz[N][N], char vector[N]) {
    FILE *fp = fopen("grafo.txt", "w");
    if (!fp) {
        cerr << "Error al abrir el archivo grafo.txt" << endl;
        return;
    }

    fprintf(fp, "digraph G {\n");
    fprintf(fp, "graph [rankdir=LR]\n");
    fprintf(fp, "node [style=filled fillcolor=yellow];\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && matriz[i][j] > 0) {
                fprintf(fp, "%c->%c [label=%d];\n", vector[i], vector[j], matriz[i][j]);
            }
        }
    }

    fprintf(fp, "}\n");
    fclose(fp);

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

int main(int argc, char **argv) {
    char V[N], S[N], VS[N];
    int D[N];

    // valores de prueba1.
    int M[N][N] = {
        {0, 4, 11, -1, -1},
        {-1, 0, -1, 6, 2},
        {-1, 3, 0, 6, -1},
        {-1, -1, -1, 0, -1},
        {-1, -1, 5, 3, 0}
    };

    // valores de prueba2.
    /*int M[N][N] = {
        {0, 2, 1, -1, 3},
        {-1, 0, -1, 4, -1},
        {-1, 1, 0, -1, 1},
        {1, -1, 3, 0, 5},
        {-1, -1, -1, -1, 0}
    };*/

    inicializar_vector_caracter(V);
    inicializar_vector_caracter(S);
    inicializar_vector_caracter(VS);

    leer_nodos(V);
    aplicar_dijkstra(V, S, VS, D, M);
    imprimir_grafo(M, V);///}+*

    return 0;
}