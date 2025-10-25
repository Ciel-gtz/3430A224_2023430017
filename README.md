<div align="center">
<h1>Creación de un árbol AVL<sub>Adelson-Velsky and Landis</sub></h1>
</div>

Para que el código pueda correr es necesario tener instalado:
- Compilador de C++. instalable utilizando `sudo apt install g++`
- Graphviz. instalable utilizando `sudo apt install graphviz -y`

Para la compilación del código se utiliza:
```
./arbol_AVL funciones_GO_minimal.csv 
```
<strong>funciones_GO_minimal.csv</strong> puede reemplazarse por otro archivo GO
<strong>arbol_AVL</strong> puede reemplazarse por <strong>arbol_AVL_SS</strong> dependiendo cuál se desee utilizar en el momento

<div align="center">
<h2><sub>⭐</sub>Sobre el código<sub>⭐</sub></h2>
</div>



El archivo arbol_AVL_SS.cpp<sub>SS viene de ScoreSearch</sub> fue realizado como preferencia porque me agrada más la idea de buscar via score y eliminar via score, ya que es un valor más simple de escribir. En cambio, el archivo arbol_AVL.cpp utiliza el término GO para búsqueda y eliminación<sub>ya que el pdf lo pide</sub>

- Al leer el archivo insercionAVL se revisa inmediatamente si se repite un valor <strong>score</strong> o no, si se repite entonces no se va a agregar, manejando así posibles repeticiones del archivo csv

- Se va actualizando el archivo de grafo cada vez que se borra o inserta un nodo, esto es para tener una visualización más fácil mientras se corre el código.

- Cuando se borra un nodo con 2 hijos, para reemplazarlo, se utiliza del subarbol izquierdo el nodo que se encuentre más a la derecha.

- En arbol_AVL se implementa controlGO(), el cual, sirve para mantener el formato de los códigos GO del archivo CSV.

<div align="center">
<h3>Notas:</h3>
</div>
Las siguientes partes del código vienen de (esta página)[https://stackoverflow.com/questions/2839592/equivalent-of-02d-with-stdstringstream]:
```
#include <iomanip> // setw() y setfill()
#include <sstream> // Para stringstream
...
stringstream stream;
...
stream << setfill('0') << setw(7) << GO;
```
Son sólamente para que se mantenga el formato de código GO de los archivos csv, el cual es de 7 números, rellenando los espacios vacíos con 0.

