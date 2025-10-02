<div align="center">
<h2>En actividad_1.cpp :</h2>
</div>

- Se realiza una lista dinámica en <strong>FIFO (First In First Out)</strong>, al contrario que en el [laboratorio2](https://github.com/Ciel-gtz/3430A224_2023430017/blob/laboratorio2/actividad_2.cpp), el cual fue realizado con <strong>LIFO (Last In First Out)</strong>.
- Se reutiliza el código <strong>control_int()</strong>.
- Se incluye un menú con el cual el usuario puede interactuar.
- 

El pdf de la guía indicaba colocar una función llamada Cola_llena, el cual, como su nombre indica, tenía el propósito de revisar si la cola estaba llena o no, pero, al ser una lista dinámica (sin límite establecido) esta es básicamente imposible de definir. Se implementó, en este caso:
```
bool checkColaLlena(){
    return false;
}
```
No tiene mucho propósito en este caso, pero fue agregado igualmente <sub>(ya que la guía lo requiere)</sub>

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

[TEXT]

<div>
<h2></h2>
</div>

```
Para la compilación de los códigos se utiliza: 
> g++ [programa].cpp -o [programa] && ./[programa]
O, si ya está el ejecutable presente:
> g++ ./[programa]
```
