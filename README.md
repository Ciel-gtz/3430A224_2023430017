<div align="center">
<h1>Creación de un árbol AVL<sub> "Adelson-Velsky and Landis"</sub></h1>
</div>

🔷 Para que el código pueda correr es necesario tener instalado:
- Compilador de C++. instalable utilizando `sudo apt install g++`
- Graphviz. instalable utilizando `sudo apt install graphviz -y`

<br>

🔷 Para la compilación del código se utiliza:
```
./arbol_AVL funciones_GO_minimal.csv 
```
`funciones_GO_minimal.csv` puede reemplazarse por otro archivo GO
`arbol_AVL` puede reemplazarse por `arbol_AVL_SS` dependiendo cuál se desee utilizar en el momento

<br>

🔷 El archivo `arbol_AVL_SS.cpp`<sub> (SS viene de ScoreSearch)</sub> fue realizado como preferencia personal porque me agrada más la idea de buscar via score y eliminar via score, ya que es un valor más simple de escribir. En cambio, el archivo `arbol_AVL_GO.cpp` utiliza el término <strong>GO</strong> para búsqueda y eliminación<sub> ya que el pdf lo pide</sub>.

<br>

<div align="center">
<h2><sub>💫 </sub>Sobre el código<sub> 💫</sub></h2>
</div>

- Al leer el archivo que ingresó el usuario al momento de compilar el código se revisa inmediatamente si se repite un valor <strong>score</strong> o no, si se repite entonces no se va a agregar, manejando así posibles repeticiones del archivo csv

- Se va actualizando el archivo de grafo cada vez que se borra o inserta un nodo, esto es para tener una visualización más fácil mientras se corre el código.

- Cuando se borra un nodo con 2 hijos, para reemplazarlo, se utiliza del subarbol izquierdo el nodo que se encuentre más a la derecha.

- En `arbol_AVL_GO` se implementa <strong>controlGO()</strong>, el cual, sirve para mantener el formato de los códigos GO del archivo CSV.

- En `arbol_AVL_GO` en vez de utilizar <strong>buscarNodo()</strong> se utiliza `buscarNodoviaGO()`. Esto se debe a que el árbol sigue estando ordenado por <strong>score</strong>, y `buscarNodo()` busca específicamente por ese valor siguiendo la estructura del árbol. En cambio, `buscarNodoviaGO()` recorre todos los nodos y compara su código <strong>GO</strong>, permitiendo encontrar el nodo correcto sin depender del ordenamiento por <strong>score</strong>.

<br>

La linea:

```
fp << "\"" << label << "\" [xlabel=< <FONT COLOR=\"#3c5c95ff\">" << nodo->GO << "</FONT> >];\n";
```
Agrega el código <strong>GO</strong> a las cajas de los nodos, colocándolo en la esquina superior izquierda. Así que, si se quiere buscar un nodo, *la caja a la derecha del código corresponde al nodo buscado.*

<br>

<div align="center">
<h2><sub>📝 </sub>Notas<sub> 📝</sub></h2>
</div>


🔷 Las siguientes partes del código vienen de [esta página](https://stackoverflow.com/questions/2839592/equivalent-of-02d-with-stdstringstream) :

```
#include <iomanip> // setw() y setfill()
#include <sstream> // Para stringstream
...
stringstream stream;
...
stream << setfill('0') << setw(7) << GO;
```

Son sólamente para que se mantenga el formato de código GO de los archivos csv, el cual es de 7 números, rellenando los espacios vacíos con 0. Esto para buscar si un código existe también se utiliza (en `buscarNodoviaGO(-)`)

<br>

🔷 Si el usuario ingresa una coma o espacio en vez de escribir un número decimal con punto [ej: 0.94] lo que esté después de la coma se ignorará. Por ello se puso como mensaje:

```
< Ingresar Score
⚠️  Utilice '.' como decimal, no ',': 
```

<div align="center">
______________________________________________
</div>

<br>

> Si solo se debe evaluar un archivo en específico en vez de todo el repositorio, utilice `arbol_AVL_GO.cpp`

> En `arbol_AVL_GO.cpp` se sigue eliminando via <strong>score</strong> ya que no hubo indicación en la guía de que se debería eliminar via GO.










