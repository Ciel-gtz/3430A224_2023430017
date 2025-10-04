<div align="center">
<h2>En actividad_1.cpp :</h2>
</div>

- Se realiza una lista dinámica en <strong>FIFO (First In First Out)</strong>, al contrario que en el [laboratorio2](https://github.com/Ciel-gtz/3430A224_2023430017/blob/laboratorio2/actividad_2.cpp), el cual fue realizado con <strong>LIFO (Last In First Out)</strong>.
- Se reutiliza el código <strong>control_int()</strong>.
- Se incluye un menú con el cual el usuario puede interactuar.

El pdf de la guía indicaba colocar una función llamada Cola_llena, el cual, como su nombre indica, tenía el propósito de revisar si la cola estaba llena o no, pero, al ser una lista dinámica (sin límite establecido) esta es básicamente imposible de definir. Se implementó, en este caso:
```
bool checkColaLlena(){
    return false;
}
```
No tiene mucho propósito, pero fue agregado igualmente <sub>(ya que la guía lo requiere)</sub>

⚠️ Un punto a considerar es que si el usuario elige realizar la opción 1 <sub>'Insertar un nuevo estudiante en la cola'</sub>, en la parte cuando pide ingresar promedio, si el usuario agrega un valor con coma en vez de con punto, se van a producir errores. Ejemplo: 
```
+ Promedio [Con punto, no coma]: 6,2
        + Se ha agregado 'juan' a la cola +
++++++++++++
Menu
1. Insertar un nuevo estudiante en la cola.
2. Eliminar estudiante al frente de la cola
3. Mostrar contenidos de la cola
4. Salir
++++++++++++

> Seleccione una opcion:        - Se ha eliminado al primer estudiante de la cola [FIFO] -
```
En este ejemplo del problema, se selecciona automáticamente la opción 2, ya que se guardó este valor aparte.

⚠️ Otra cosa a mencionar es que el formato, al momento de elegir la opcion 3 <sub>'Mostrar contenidos de la cola.'</sub>, si los datos que se ingresaron son muy grandes, entonces el formato va a verse extraño. Funcionalmente no tiene problemas esto.

<div align="center">
<h2>En actividad_2.cpp :</h2>
</div>

Para que corra el programa utilice `./actividad_2 <ruta_archivo.pdb>`. Como ya está hecho el ejemplo .pdb, puede directamente utilizar `./actividad_2 ./proteinasEjemplo.pdb` para correr el ejemplo ya hecho. Igualmente, si se hace uso equivocado de esto, el programa va a dar un aviso cuando, por ejemplo, no se agrega nada después de ./actividad_2.
O también, otra opción sería ejecutar el archivo bash, el cual atomáticamente va a tomar el archivo <proteinasEjemplo.pdb>, haciendo que solo sea necesario escribir en la terminal `./correrPrograma.bash` para que el programa inicie. 
Si se desea editar el archivo a abrir cada vez, entonces, se sugiere abrir el archivo bash y cambiarlo manualmente en `INPUT="proteinasEjemplo.pdb"`. Tengo entendido que se puede hacer que el bash te pida también el archivo y correrlo de modo <sub>./correrPrograma.bash <archivo.pdb></sub> pero, este método es tan similar a solo ejecutar <sub>actividad_2</sub> que se siente reiterativo si lo dejara de esa forma, por ello se prefirió utilizar la línea INPUT.

- Al ser muchas opciones juntas, para una mejor visualización <sub>tanto para mí como para el usuario</sub> se agregaron emojis al menú. Pero, por la posibilidad de cualquier error visual que pueda suceder por esto, se incluye el menú sin emojis aquí:
```
++++++++++++
Menu
1. Insertar un nuevo residuo al final de la secuencia.
2. Modificar el resn de un residuo.
3. Eliminar un residuo en una posicion especifica.
4. Mostrar la lista de residuos.
5. Exportar la lista a un archivo en formato Graphviz (.dot)
6. Generar imagen .png a partir del archivo .dot
7. Salir
++++++++++++
```
En el programa se decide utilizar, para insertar a la cola, solo las primeras 3 letras de lo que sea que entregue el usuario, el cual puede poner tanto numeros como letras, pero, será limitado solo a 3 caracteres. En cambio, para el código de la proteína, el usuario solo podrá poner números, además, se toma la linea que lea del archivo y le sacará los primeros 5 caracteres de este, suponiendo que siempre van a ser 3 letras al inicio y 2 espacios de separación después.
- Se elimina <strong>controlFLOAT</strong> (utilizado en actividad_1.cpp), ya que no es necesario aquí.
- Se agrega <strong>eliminarEspecifico()</strong> para realización de la opción 2, utilizando el bool que retorna para verificar si imprimir que se borró la proteína, o si es que no se pudo borrar la proteína, entonces para decir que hubo un error.
- <strong>nombreProteina</strong> equivale a resn y <strong>codigoPDB</strong> equivale a resid, estos nombres pedidos en el pdf se cambiaron para tener una mayor claridad al momento de realizar el código.
- Se agregaron funciones para eliminar y modificar un dato de la cola en específico, estos siendo <strong>eliminarEspecifico</strong> y <strong>modificarEspecifico</strong> respectivamente.
- Se crea <strong>crearArchivo</strong> y <strong>crearImagen</strong> tomándo como referencia cercana el ejemplo `graphviz_generator.cpp` del profesor, solo se separó su ejemplo en 2 funciones distintas en vez de realizar todo en el main. También, se incluye en ambas funciones sus respectivos formatos de archivo según el que se va a utilizar, ya que en el main se utiliza outputDot sin .dot para que este se pueda reiterar en las opciones 5 y 6. 

\
⚠️ Este código depende mucho el cómo se escriba el pdb por la forma en que lo lee debido a lo descrito con anterioridad, así que, los datos del archivo deben estar escritos en el siguiente formato `nombre+espacio+espacio+código`:
```
ARG  34
GLY  35
VAL  36
```

<div>
<h2></h2>
</div>

```
Para la compilación de los códigos en general se utiliza: 
> g++ [programa].cpp -o [programa] && ./[programa]
O, si ya está el ejecutable presente:
> g++ ./[programa]
```
