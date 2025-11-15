#include <iostream>
#include <cstdlib>   // rand, srand, atoi
#include <ctime>     // time
#include <chrono>    // timing

using namespace std;
using std::chrono::duration;
using std::chrono::high_resolution_clock;


// ─────────────| Impresión de vectores |─────────────¬

void imprimir_vector(const int *arregloDatos, int cantidadElementos) {

    cout << "\n¬ Vectores ──> ";
    for (int i = 0; i < cantidadElementos; ++i) {
        cout << "v[" << i << "]=" << arregloDatos[i];
        if (i + 1 < cantidadElementos) cout << " ; ";
    }
    cout << "\n";
}

void decision_imprimir(char opcion, int *arregloDatos, int cantidadElementos) {

    if (opcion == 's') {
        imprimir_vector(arregloDatos, cantidadElementos);
    }

}


// ─────────────| Copia de arreglos |─────────────¬

// Copia los 'cantidadElementos' del arreglo original hacia el arreglo copia.
void copiar_arreglo(const int *original, int *copia, int cantidadElementos) {

    for (int i = 0; i < cantidadElementos; ++i) copia[i] = original[i];
}


// ─────────────| Implementaciones de algoritmos |─────────────¬

// Bubble sort (O(n^2))
void bubbleSort(int *arreglo, int cantidadElementos) {

    // Recorre todas las pasadas del método burbuja
    for (int i = 0; i < cantidadElementos - 1; i++) {

        // Recorre comparando elementos adyacentes
        for (int j = 0; j < (cantidadElementos - 1 - i); j++) {

            // Si el elemento actual es mayor al siguiente se intercambia
            if (arreglo[j] > arreglo[j + 1]) {

                int temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
}

// Inserción (O(n^2))
void insercion(int *arreglo, int cantidadElementos) {

    // Desde el segundo elemento hasta el final
    for (int i = 1; i < cantidadElementos; i++) {

        // Guarda el valor a insertar
        int valorActual = arreglo[i];

        // Posición inmediata anterior
        int j = i - 1;

        // Mientras j no salga del arreglo y el valor previo sea mayor a valorActual
        while (j >= 0 && arreglo[j] > valorActual) {

            // Desplaza hacia la derecha
            arreglo[j + 1] = arreglo[j];

            j = j - 1;
        }

        // Inserta valorActual en la posición correcta
        arreglo[j + 1] = valorActual;
    }
}

// Selección (O(n^2))
void seleccion(int *arreglo, int cantidadElementos) {

    // Recorre cada posición del arreglo
    for (int i = 0; i < cantidadElementos - 1; i++) {

        // Índice del valor mínimo encontrado en esta pasada
        int minIdx = i;

        // Busca un valor menor en el resto del arreglo
        for (int j = i + 1; j < cantidadElementos; j++) {

            if (arreglo[j] < arreglo[minIdx]) {
                minIdx = j;
            }
        }

        // Si se encontró un nuevo mínimo → intercambiar
        if (minIdx != i) {

            int temp = arreglo[i];
            arreglo[i] = arreglo[minIdx];
            arreglo[minIdx] = temp;
        }
    }
}

// Shellsort (O(n × logn))
void shellsort(int *arreglo, int cantidadElementos) {

    // Tamaño inicial del salto
    int gap = cantidadElementos / 2;

    // Mientras el gap sea mayor que cero
    while (gap > 0) {

        // Inserción modificada utilizando el gap
        for (int i = gap; i < cantidadElementos; i++) {

            int temp = arreglo[i];
            int j = i;

            // Comparar elementos separados por el gap
            while (j >= gap && arreglo[j - gap] > temp) {

                arreglo[j] = arreglo[j - gap];

                j = j - gap;
            }

            // Insertar valor temporal en posición correcta
            arreglo[j] = temp;
        }

        // Reducir el gap a la mitad
        gap = gap / 2;
    }
}

// <──| quickSort |──>

// Partición del quickSort
int particionar(int *arreglo, int izquierda, int derecha) {

    // pivote como elemento central del subarreglo
    int indiceMedio = (izquierda + derecha) / 2;
    int pivote = arreglo[indiceMedio];

    int i = izquierda;
    int j = derecha;

    while (true) {

        // Avanza 'i' hasta encontrar un elemento >= pivote
        while (true) {
            if (arreglo[i] < pivote) {
                i = i + 1;  // antes era i++
            } else {
                break;
            }
        }

        // Retrocede 'j' hasta encontrar un elemento <= pivote
        while (true) {
            if (arreglo[j] > pivote) {
                j = j - 1;  // antes era j--
            } else {
                break;
            }
        }

        // Si los índices se cruzan → partición terminada
        if (i >= j) {
            return j;
        }

        // Intercambio explícito entre arreglo[i] y arreglo[j]
        int temp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = temp;

        // Avanzar 'i' y retroceder 'j' después del intercambio
        i = i + 1;
        j = j - 1;
    }
}


// Función recursiva del quickSort, ordena parte izq y der del pivote
void quickSortRec(int *arreglo, int izquierda, int derecha) {

    // Condición de recursión
    if (izquierda < derecha) {

        // Índice del pivote ordenado
        int indicePivote = particionar(arreglo, izquierda, derecha);

        // Ordena izquierda
        quickSortRec(arreglo, izquierda, indicePivote);

        // Ordena derecha
        quickSortRec(arreglo, indicePivote + 1, derecha);
    }
}


// Para utilizar tiempoMS
void quickSort(int *arreglo, int cantidadElementos) {

    if (cantidadElementos > 0) {
        quickSortRec(arreglo, 0, cantidadElementos - 1);
    }
}


// ─────────────| Función para medida de tiempo |─────────────¬

// Mide el tiempo de ejecución en milisegundos de alguna de las funciones void (de ordenamiento) sobre una copia de original.
double tiempoMS(void (*funcion)(int*, int), int *original, int *resultado, int cantidadElementos) {

    // Copiar el arreglo original
    copiar_arreglo(original, resultado, cantidadElementos);

    // Marca el inicio del conteo
    auto t1 = high_resolution_clock::now();
    // Ejecutar algoritmo de ordenamiento
    funcion(resultado, cantidadElementos);
    // Marca el fin del conteo
    auto t2 = high_resolution_clock::now();

    // calcular duración en milisegundos
    double milisegundos = duration<double, milli>(t2 - t1).count();
    return milisegundos;
}


// ─────────────| Main |─────────────¬

int main(int argc, char** argv) {

    // <──| Valores iniciales |──>
    char VER; // opción 's' o 'n'
    int N; // tamaño del vector


    // <──| Validación de argumentos de entrada |──>
    if ((argc <= 2 || argc > 3) || (argv[2][0] != 'n' && argv[2][0] != 's')) {
        cout << "⚠️  Uso: " << argv[0] << " [valor > 0] [visualizar? s|n]\n" 
             << "\tRecuerde utilizar 'n' o 's'; no 'S' o 'N' u otros\n";
        return 1;

    } else {
        VER = (argv[2])[0];
    }

    if (atoi(argv[1]) <= 0) {
        cout << "⚠️  '" << argv[1] << "' debia ser un entero positivo.\n";
        return 1;

    } else {
        N = atoi(argv[1]);
    }


    // <──| Generación del valor del vector aleatorio |──>
    int *original = new int[N];
    srand (time(NULL)); // sin esto no se generan valores aleatorios
    for (int i = 0; i < N; ++i) {
        original[i] = (rand() % 10000) + 1; // valores del 1 hasta 10000
    }

    // Si argv[2] == 's' mostrar vectores
    decision_imprimir(VER, original, N);
    // 'original' es el arreglo desordenado

    // arreglo dinámico
    int *resultado = new int[N]; 
    
    cout << "\n─────────────| Ordenamientos |─────────────¬\n"
         << "Metodo" <<  "\t\t|Tiempo (ms)\n"
         << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
    

    // <──| Burbuja |──>
    double tBubbleSort = tiempoMS(bubbleSort, original, resultado, N);
    cout << "⭐ Burbuja" << "\t|" << tBubbleSort << " ms" << endl;
    decision_imprimir(VER, resultado, N); // 'resultado' es el arreglo ordenado

    cout << "────────────────────────────────────────────" << endl;

    // <──| Inserción |──> 
    double tInsercion = tiempoMS(insercion, original, resultado, N);
    cout << "⭐ Insercion" << "\t|" << tInsercion << " ms" << endl;
    decision_imprimir(VER, resultado, N);


    cout << "────────────────────────────────────────────" << endl;

    // <──| Selección |──> 
    double tSeleccion = tiempoMS(seleccion, original, resultado, N);
    cout << "⭐ Seleccion" << "\t|" << tSeleccion << " ms" << endl;
    decision_imprimir(VER, resultado, N);


    cout << "────────────────────────────────────────────" << endl;

    // <──| Shellsort |──> 
    double tShell = tiempoMS(shellsort, original, resultado, N);
    cout << "⭐ Shellsort" << "\t|" << tShell << " ms" << endl;
    decision_imprimir(VER, resultado, N);


    cout << "────────────────────────────────────────────" << endl;

    // <──| quickSort |──> 
    double tquickSort = tiempoMS(quickSort, original, resultado, N);
    cout << "⭐ quickSort" << "\t|" << tquickSort << " ms" << endl;
    decision_imprimir(VER, resultado, N);


    cout << "────────────────────────────────────────────" << endl;

    // <──| Liberar memoria |──> 
    delete[] original;
    delete[] resultado;

    return 0;
}
