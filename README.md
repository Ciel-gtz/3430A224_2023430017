<div align="center">
<h1>Creación de un árbol binario</h1>
</div>

Para que el código pueda correr es necesario tener instalado:
- Compilador de C++. instalable utilizando `sudo apt install g++`
- Graphviz. instalable utilizando `sudo apt install graphviz -y`

<div align="center">
<h2>Sobre las funciones del código</h2>
</div>

<h3>💫 Sobre los controles de entrada para evadir errores :</h3>

```
char userDecision() {...
}
int controlINT() {...
}
```

El código utilizado para `userDecision()` viene de combinar los códigos presentes en [esta página](https://stackoverflow.com/questions/43972500/how-to-only-accept-y-or-n-in-users-input-in-c), el cual, mientras no se escriba s o n, se seguirá preguntando al usuario que coloque la letra adecuada, también, se toma de aquí sólamente la primera letra de lo que sea que el usuario ingrese.  
- Además se utiliza `(char)tolower(userAnswer);` para que no importe si el usuario coloca mayúsculas, estas se tomarán como minúsculas igualmente. La idea de utilizar esto [viene de aquí](https://www.geeksforgeeks.org/cpp/tolower-function-in-cpp/).

Sobre `int controlINT()`, este es un código que vengo reiterando con anterioridad. En uno de los laboratorios anteriores se encuentra el link.
<br><br>
<h3>💫 Sobre el arbol :</h3>

```
void crearArbol(Nodo* &apnodo, vector<int>& lista) {...
}
Nodo* buscarNodo(Nodo* nodo, int valor) {...
}
```

En `crearArbol(-)` se utilizan vectores para ir guardando los valores que va agregando inicialmente el usuario, siendo una forma fácil y directa de verificar que no se repitan los números en esta parte del código, ya que, si hay un valor en la lista que concuerde con el valor ingresado, se va a pedir un valor nuevo hasta que el usuario ingrese uno no existente, el cual se agregará a la lista y así continuamente. Claramente la desición de utilizar vectores en vez de un arreglo es porque no se sabrá cuántos nodos quiera ingresar el usuario.

La función `buscarNodo(-)` busca un valor elegido en el árbol, devolviendo un puntero al nodo si es que existe, o un null si es que no existe. Esta función es utilizada también en `editarNodo(-)`, donde se utiliza el puntero, y en la primera opción del menú para comprobar si ya existe el valor. 
<br><br>
<h3>💫 Sobre ediciones en el arbol :</h3>

```
void insertarNodo(Nodo* &apnodo, int infor) {...
}
void eliminarNodo(Nodo* &apnodo, int valor) {...
}
void editarNodo(Nodo* raiz, int valorViejo) {...
}
```
`insertarNodo(-)` va comparando valores entre los nodos hojas y sus padres, creando rangos entre los cuales la nueva información se situará en su respectivo sitio.

sobre `eliminarNodo(-)`, este se puede describir como si se separara en 3 etapas:
- <strong>Caso 1: Nodo hoja</strong> : Se elimina el nodo hoja directamente.
- <strong>Caso 2: Un solo hijo</strong> : Al tener solo un nodo hijo, este nodo tomará su lugar. 
- <strong>Caso 3: Dos hijos</strong> : En este caso se utilizará, del nodo que se quiere borrar, el nodo que está más a la izquierda del subarbol derecho, siendo el nodo que (supuestamente) debería tener el valor más cercano al nodo que se quiere borrar (digo supuestamente porque en este código no se organiza el árbol por valores como usualmente debería ser el caso)
<br><br>
<h3>💫 Sobre el grafo :</h3>

```
void recorrer(Nodo* nodo, ofstream& fp) {...
}
void visualizarArbol(Nodo* root, string nombreArchivo) {...
}
```

Del código de `recorrer(-)` entregado por el profesor, se modificó un poco la forma de escritura (ya que el código original utilizaba char para los datos, en cambio, en el código se utiliza int). Las modificaciones hechas básicamente es poner un '_' atrás de cada número, ya que sin esto (o utilizando un '.') graphviz los interpreta como valores numéricos y no como identificadores de nodo, provocando errores al momento de utilizar `visualizarArbol(-)`.

Hablando de `visualizarArbol(-)`, este deja al usuario elegir el nombre del archivo .png junto a su respectivo .txt (técticamente el main pide el nombre, pero se implementó la forma en esta función para que utilice el nombre que el usuario decida colocar). Esto deja guardar los resultados de varios grafos distintos, dejándome guardar varios ejemplos en mi repositorio: el del ejemplo en 'Laboratorio_4.pdf' titulado como <strong>'grafo_ejemplo.png'</strong> y 3 ejemplos de opciones del menú utilizadas en el grafo del pdf, encontrados en la carpeta <strong>'grafos_TESTS'</strong> <sub>(las opciones se correlacionan con la ennumeración de los títulos de los grafos dentro de esta carpeta).</sub>
<br><br>
<h3>💫 Sobre las funciones recursivas para imprimir el arbol :</h3>

```
void printPreOrden(Nodo* Nodo) {...
}
void printInOrden(Nodo* Nodo) {...
}
void printPostOrden(Nodo* Nodo) {...
}
```

Estos códigos son muy similares, solo cambia el orden del procesamiento:
- `printPreOrden(-)` : se procesa primero el nodo actual, luego su subárbol izquierdo y después el derecho.
- `printInOrden(-)` : se procesa primero el subárbol izquierdo, luego el nodo actual y después el derecho.
- `printPostOrden(-)` :  se procesa primero el subárbol izquierdo, después el derecho y al final el nodo actual.
<br><br>
<h3>💫 Menú :</h3>

```
++++++++++++
Menu
1. ⭕ Insertar nuevo nodo.
2. ❌ Eliminar nodo.
3. ✍️ Modificar nodo.
4. 👁️ Mostrar recorridos del arbol.
5. 🖨️ Generar grafo.
6. 🚪🏃 Salir.
++++++++++++
```

<br><br>
<h3>💫 Sobre el main :</h3>

No hay mucho que explicar, solo corre el código como tal, incluyendo a las funciones y utilizando a `int opcion` para moverse por las opciones del menú y correr estas con respecto a lo que el usuario desee realizar.

<div align="center">
<h1></h1>
</div>

```
Para la compilación de los códigos en general se utiliza: 
> g++ [programa].cpp -o [programa] && ./[programa]
O, si ya está el ejecutable presente:
> g++ ./[programa]
```
