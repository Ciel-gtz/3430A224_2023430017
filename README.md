<div align="center">
<h1>Algoritmo de Prim</h1>
</div>

🔷 El código implementa el algoritmo de Prim, el cual permite encontrar el árbol de expansión mínima (MST) de un grafo no dirigido y ponderado, conectando todos los vértices con el menor costo total posible.

🔷 Este código se realizó utilizando el código de Dijkstra presente en [laboratorio6](https://github.com/Ciel-gtz/3430A224_2023430017/blob/laboratorio6/dijkstra_algoritmo.cpp) como base:
- Se agregó la función `actualizar_pesos_prim()` para manejar los pesos en Prim.
- Se modificó `imprimir_grafo()` de forma que puede generar archivos con distinto nombre ahora.
- Se modificó `elegir_vertice()` para seleccionar vértices por peso directo, no acumulado.
- Se reemplazó `aplicar_Dijkstra()` a `aplicar_Prim()`, cambiando el flujo de Dijkstra por el de Prim.
- Se actualizó `leer_datos_matriz()` para copiar valores simétricos automáticamente.
- Se adaptó `main()` para inicializar <strong>matrizMST</strong>, <strong>imprimir V[]</strong>, y mostrar grafos.
- Se eliminaron funciones de Dijkstra <strong>(aplicar_Dijkstra, actualizar_pesos_Dijkstra)</strong>.

<br>

🔷 Para que el código pueda correr es necesario tener instalado:
- Compilador de C++. instalable utilizando `sudo apt install g++`
- Graphviz. instalable utilizando `sudo apt install graphviz -y`

<br>

🔷 Para la compilación del código se utiliza:
```
./prim [N°]
```
[N°] corresponderá a la cantidad de nodos que desee agregar el usuario, debiendo ser un número entero mayor o igual a 2.

<br>

🔷 En la matriz:
- Los valores menores a <strong>-1</strong> no son permitidos.
- <strong>-1</strong> corresponderá a 2 nodos que no poseen conexión.
- <strong>0</strong> corresponde a la diagonal, en otras palabras, se refiere a los momentos en que se evalúa matriz[X][X] en vez de matriz[X][Z]
- Los valores <strong>positivos</strong> corresponden a dos nodos conectados, el valor correspondiendo al peso entre ambos nodos.

*En el caso de la matriz de Prim, no se pide que el usuario ingrese la matriz[A][B] y matriz[B][A], en cambio se pide solo uno de los dos, agregando automáticamente el valor a su copia simétrica.

<div align="center">
<h2><sub>💫 </sub>Sobre el código<sub> 💫</sub></h2>
</div>

<br>

- `controlINT()` fue editado de manera que solo permita números mayores o iguales a 2, además, también acepta -1. Esto se hizo para que el usuario no coloque negativos ni el 0, manteniendo el formato de que los nodos que valen 0 son solo parte de la diagonal.
- El código le pide al usuario ingresar los pesos entre nodos, fuera de eso (y el valor en la ejecución del código via terminal) no existen más interacciones directas con este.
- `leer_nodos()` genera las etiquetas de los vértices en orden alfabético utilizando el código ascii.

<br>

🔷 En la función `aplicar_Prim` se piden los parámetros:
- MST -> Matriz del árbol de expansión mínima <sub>(Minimum Spanning Tree).</sub>
- S -> Conjunto de vértices ya en el MST.
- V -> Lista de todos los vértices del grafo (a, b, c, …).
- M -> matriz de adyacencia original con los pesos.
- VS -> Vértices aún no incorporados.
- D -> vector de distancias mínimas desde los vértices del conjunto S hacia los que están en VS.
- totalElem -> cantidad total de nodos en el grafo.

<br>

`aplicar_prim()` es el núcleo del algoritmo, encargado de:
- Inicializar los conjuntos S, VS y el vector de distancias D[].
- Elegir en cada iteración el vértice con el menor peso de conexión hacia el conjunto VS[].
- Agregar ese vértice al conjunto S y actualizar los pesos mínimos de los vértices aún no visitados.
- Registrar las aristas seleccionadas en la matriz MST.
- Repetir el proceso hasta que todos los vértices estén incluidos en el árbol de expansión mínima.

<br>

🔷 Se deja en el repositorio el archivo `grafo_original.png`, el cual corresponde a la matriz:
```
- matriz:
        |0      |6      |1      |5      |-1     |-1 
        |6      |0      |5      |-1     |3      |-1 
        |1      |5      |0      |5      |6      |4 
        |5      |-1     |5      |0      |-1     |2 
        |-1     |3      |6      |-1     |0      |6 
        |-1     |-1     |4      |2      |6      |0 
```

<details>
<summary><sub>💫 </sub>Los cuales vienen de estas entradas del usuario<sub> 💫</sub></summary>

matriz[0][1] ---> 6

matriz[0][2] ---> 1

matriz[0][3] ---> 5

matriz[0][4] ---> -1

matriz[0][5] ---> -1

matriz[1][2] ---> 5

matriz[1][3] ---> -1

matriz[1][4] ---> 3

matriz[1][5] ---> -1

matriz[2][3] ---> 5

matriz[2][4] ---> 6

matriz[2][5] ---> 4

matriz[3][4] ---> -1

matriz[3][5] ---> 2

matriz[4][5] ---> 6

</details>

<br>
<br>

🔷 Al finalizar la ejecución, se generarán los siguientes archivos:
- `grafo_original.txt` -> Contiene las instrucciones DOT del <strong>grafo completo</strong>.
- `grafo_original.png` -> Imagen del grafo completo generada por Graphviz.
- `grafo_minimo.txt` -> Contiene las instrucciones DOT del <strong>árbol de expansión mínima (MST)</strong>.
- `grafo_minimo.png` -> Imagen del árbol de expansión mínima generada por Graphviz.

<details>
<summary><sub>💫 </sub>Más información sobre ambos grafos<sub> 💫</sub></summary>

El programa genera dos visualizaciones distintas usando <strong>Graphviz</strong>:

🔷 `grafo_original` -> Muestra el grafo con todos los pesos tal como fueron introducidos por el usuario.

🔷 `grafo_minimo.png` -> Corresponde al <strong>árbol de expansión mínima (MST)</strong>. Este grafo incluye solo las aristas seleccionadas por el algoritmo de Prim, es decir, aquellas que conectan todos los vértices con el <strong>menor costo total posible</strong>.

</details>

<br>


| Para el desarrollo del código se utiliza como referencia la información en:
[cp-algorithms.com](https://cp-algorithms.com/graph/mst_prim.html), 
[geeksforgeeks.org](https://www.geeksforgeeks.org/dsa/prims-minimum-spanning-tree-mst-greedy-algo-5/) y 
[programiz.com](https://www.programiz.com/dsa/prim-algorithm)
