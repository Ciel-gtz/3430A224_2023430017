<div align="center">
<h1>Algoritmo de Dijkstra</h1>
</div>

El código implementa el algoritmo de Dijkstra, que permite determinar las rutas de menor costo (o distancia mínima) desde un nodo inicial hacia todos los demás en un grafo dirigido.

<br>

🔷 Para que el código pueda correr es necesario tener instalado:
- Compilador de C++. instalable utilizando `sudo apt install g++`
- Graphviz. instalable utilizando `sudo apt install graphviz -y`

<br>

🔷 Para la compilación del código se utiliza:
```
./dijkstra [N°]
```
[N°] corresponderá a la cantidad de nodos que desee agregar el usuario, debiendo ser un número entero mayor o igual a 2.

<br>

En la matriz:
- Los valores menores a <strong>-1</strong> no son permitidos.
- <strong>-1</strong> corresponderá a 2 nodos que no poseen conexión.
- <strong>0</strong> corresponde a la diagonal, en otras palabras, se refiere a los momentos en que se evalúa matriz[X][X] en vez de matriz[X][Z]
- Los valores <strong>positivos</strong> corresponden a dos nodos conectados, el valor correspondiendo al peso entre ambos nodos.

<div align="center">
<h2><sub>💫 </sub>Sobre el código<sub> 💫</sub></h2>
</div>

<br>

- `controlINT()` fue editado de manera que solo permita números mayores o iguales a 2, además, también acepta -1. Esto se hizo para que el usuario no coloque negativos ni el 0, manteniendo el formato de que los nodos que valen 0 son solo parte de la diagonal.
- El código le pide al usuario ingresar los pesos entre nodos, fuera de eso (y el valor en la ejecución del código via terminal) no existen más interacciones directas con este.
- `leer_nodos()` genera las etiquetas de los vértices en orden alfabético utilizando el código ascii.

<br>

En la función `aplicar_dijkstra` se piden "V, S, VS, D" los cuales corresponden a:
- V: todos los vértices
- S: vértices ya visitados
- VS: vértices aún no visitados
- D: distancias mínimas

<br>

`aplicar_dijkstra()` es el núcleo del algoritmo, encargado de:
- Inicializar las distancias (D[]) desde el nodo inicial.
- Seleccionar en cada paso el vértice con menor peso desde VS[].
- Actualizar los pesos de los vértices adyacentes.
- Repetir hasta que todos los vértices sean procesados.

<br>

Se deja en el repositorio el archivo `grafo_ejemplo.png`, el cual corresponde a la matriz:
```
int M[N][N] = {{ 0, 4, 11, -1, -1},
                 {-1, 0, -1,  6,  2},
                 {-1 ,3,  0,  6, -1},
                 {-1,-1, -1,  0, -1},
                 {-1,-1,  5,  3,  0}};
```

<br>

🔷 Al finalizar la ejecución, se generarán los siguientes archivos:
- `grafo.txt` -> Contiene las instrucciones DOT del grafo.
- `grafo.png` -> Imagen del grafo generada por Graphviz.
