<div align="center">
<h1><sub>⭐</sub> Algoritmos de Ordenamiento <sub>⭐</sub></h1>
</div>

🔷 Este código implementa distintos algoritmos clásicos de ordenamiento, permitiendo comparar sus tiempos de ejecución utilizando arreglos aleatorios generados por el programa.

🔷 Incluye las siguientes funciones:
- **Bubble Sort**
- **Insertion Sort**
- **Selection Sort**
- **Shellsort**
- **QuickSort** (con pivote central)

🔷 Además, el programa permite, si el usuario lo desea, **visualizar** los vectores antes y después de ordenarlos.

<br>


<div align="center">
<h2><sub>📌</sub> Ejecución del programa <sub>📌</sub></h2>
</div>

Para ejecutar:

```bash
./ordenamientos [N°] [s|n]
```

Donde:

* **[N°]** es la cantidad de elementos del arreglo (entero ≥ 1).
* **[s|n]** es decidir si desea visualizar los vectores [`s`] o no [`n`].

Como ejemplo puede utilizar:

```bash
./ordenamientos 34 s
```

lo cual creará 34 elementos aleatorios, mostrando el ordenamiento de estos.

<br>


<div align="center">
<h2><sub>✅</sub> Validación de argumentos <sub>✅</sub></h2>
</div>

El programa verifica:

```cpp
((argc <= 2 || argc > 3) || (argv[2][0] != 'n' && argv[2][0] != 's'))
```

Esto significa:

* ✘ Si faltan argumentos, se cancela.
* ✘ Si hay demasiados argumentos, se cancela.
* ✘ Si la segunda opción NO es `s` o `n`, se cancela igualmente.

Además:

* ✘ Si el número entregado es **≤ 0**, también se cancela.
* ✔ Solo se permiten enteros positivos.

<br>


<div align="center">
<h2><sub>🔢</sub> Generación del arreglo aleatorio <sub>🔢</sub></h2>
</div>

Los valores del arreglo son generados de forma aleatoria con:

```cpp
srand(time(NULL));
```

> el cual viene de este link de [cplusplus.com](https://cplusplus.com/reference/cstdlib/srand/)

El arreglo se llena con valores aleatorios entre 1 y 10000 y se guardan en `original[]`, mientras que cada algoritmo trabaja en su copia `resultado[]`.

<br>

La función:

```cpp
copiar_arreglo(original, resultado, N);
```

permite que cada método de ordenamiento trabaje siempre con el arreglo inicial, evitando que el original sea modificado.

<br>


<div align="center">
<h2><sub>⏱️</sub> Medición del tiempo <sub>⏱️</sub></h2>
</div>

La función:

```cpp
double tiempoMS(void (*funcion)(int*, int), int *original, int *resultado, int cantidadElementos)
```

Permite medir los **milisegundos** que demora cada algoritmo.

> Esta funcion es un extracto modificado de la función presente en [stackoverflow.com](https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c)

<br>

en esta función, la parte `void (*funcion)(int*, int)` recibe un **puntero a función** para poder utilizar cualquier algoritmo que tenga un formato de estilo:

```cpp
void algoritmo(int*, int)
```

> La idea de utilizar esto proviene de este otro link de [stackoverflow.com](https://stackoverflow.com/questions/19417826/passing-function-pointer)

<br>


<div align="center">
<h2><sub>📚</sub> Descripción de los algoritmos <sub>📚</sub></h2>
</div>

### ☄️ **Bubble Sort (O(n²))**

Compara pares adyacentes y mueve el mayor hacia la derecha.

Ciclo externo → número de pasadas
Ciclo interno → comparaciones e intercambios

---

### ☄️ **Insertion Sort (O(n²))**

Separa el arreglo entre una parte ordenada y otra desordenada.

Toma el elemento actual y lo inserta en su posición correcta, moviendo los mayores hacia la derecha.

---

### ☄️ **Selection Sort (O(n²))**

Busca el valor mínimo en la parte desordenada y lo intercambia con la posición actual.

Siempre realiza el mismo número de comparaciones, independiente del orden del arreglo.

---

### ☄️ **Shellsort (O(n log n))**

Es una mejora de `Insertion Sort`, utilizando “saltos” (`gap` en el código).

Inicialmente compara elementos alejados, y va reduciendo el salto a la mitad hasta llegar a 1, donde finalmente se comporta como un Insertion Sort optimizado.

---

### ☄️ **QuickSort (O(n log n))**

El pivote es elegido como el elemento central:

```cpp
pivote = arreglo[(izquierda + derecha) / 2]
```

El particionar:

1. Avanza `i` hacia la derecha hasta encontrar un valor >= pivote
2. Retrocede `j` hacia la izquierda hasta encontrar un valor <= pivote
3. Si `i < j` intercambia
4. Si `i >= j` retorna la posición del corte

Luego QuickSort recursivamente ordena:

- la parte izquierda: `[izquierda ... pivote]`
- la parte derecha: `[pivote+1 ... derecha]`

<br>


<div align="center">
<h2><sub>📤</sub> Salida del programa <sub>📤</sub></h2>
</div>

Si el usuario elige que no quiere mostrar los vectores, entonces sólo se verá una tabla simple con el método y el tiempo que tardó el computador en desarrollar el método <sub>(en milisegundos)</sub>  :

```
─────────────| Ordenamientos |─────────────¬
Metodo          |Tiempo (ms)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

⭐ Burbuja      |0.0002 ms
────────────────────────────────────────────
⭐ Insercion    |0.00013 ms
────────────────────────────────────────────
⭐ Seleccion    |0.00018 ms
────────────────────────────────────────────
⭐ Shellsort    |0.00016 ms
────────────────────────────────────────────
⭐ quickSort    |0.00021 ms
────────────────────────────────────────────
```

<br>

Y algo similar se presenta si el usuario decidió ejecutar el programa con `s` :

```
# @usuario: ./ordenamientos 5 s

¬ Vectores ──> v[0]=9386 ; v[1]=6004 ; v[2]=9472 ; v[3]=1702 ; v[4]=8823

─────────────| Ordenamientos |─────────────¬
Metodo          |Tiempo (ms)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

⭐ Burbuja      |0.00024 ms

¬ Vectores ──> v[0]=1702 ; v[1]=6004 ; v[2]=8823 ; v[3]=9386 ; v[4]=9472
────────────────────────────────────────────
⭐ Insercion    |0.00013 ms

¬ Vectores ──> v[0]=1702 ; v[1]=6004 ; v[2]=8823 ; v[3]=9386 ; v[4]=9472
────────────────────────────────────────────
⭐ Seleccion    |0.00018 ms

¬ Vectores ──> v[0]=1702 ; v[1]=6004 ; v[2]=8823 ; v[3]=9386 ; v[4]=9472
────────────────────────────────────────────
⭐ Shellsort    |0.00019 ms

¬ Vectores ──> v[0]=1702 ; v[1]=6004 ; v[2]=8823 ; v[3]=9386 ; v[4]=9472
────────────────────────────────────────────
⭐ quickSort    |0.00022 ms

¬ Vectores ──> v[0]=1702 ; v[1]=6004 ; v[2]=8823 ; v[3]=9386 ; v[4]=9472
────────────────────────────────────────────
```

Se muestra el arreglo original (desordenado) y el resultado de cada ordenamiento

> ⚠️ al colocar un '5' en realidad no se generan vectores del 1 al 5, sino que se generan del 0 al 5-1, prácticamente siguen siendo 5 vectores

<br>


<div align="center">
<h2><sub>🗑️</sub> Liberación de memoria <sub>🗑️</sub></h2>
</div>

Al terminar, el programa libera memoria con:

```cpp
delete[] original;
delete[] resultado;
```

<br>

---

> Al escribir 'vector' no me refiero a que esté trabajando con vectores, esto hace mención al concepto de vector de ser un 'conjunto de elementos ordenados en secuencia', pero la implementación corresponde a un arreglo dinámico.