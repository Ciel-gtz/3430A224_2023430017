<div align="center">
<h2>En actividad_1.cpp:</h2>
</div>

- Se utiliza <strong> LIFO (Last In First Out) </strong> para controlar la forma en la que entran y salen los datos de la pila, siendo el último dato que el usuario ingrese, el primero que vaya a salir con la función Pop()
- Se reutiliza <strong> control_int() </strong> para control de errores

En <strong> Pop() </strong> se retorna el último dato de la pila, pero, esto no es necesario, sobretodo en este caso, ya que solo se quería retirar este valor de la pila. Se pudo utilizar en cambio una función void de la siguiente forma:

```
void Pop(int pila[], int &TOPE, bool &BAND) { 
    Pila_vacia(TOPE, BAND); 
    if (BAND == true) {
        cout << "x+ Subdesbordamiento, pila vacia +x\n";
    } else if (BAND == false) { 
        TOPE -= 1; 
        cout << "- se ha retirado el dato\n";
    }
}
```
Pero se prefirió dejar la versión int de esta función para reutilizar el código en actividad_2


<div align="center">
<h2>En actividad_2.cpp:</h2>
 </div>

Para la compilación del código se utiliza:
```
./actividad_2 [valor_1] [valor_2]
```
- <strong> [valor_1] </strong> equivale a la cantidad de contenedores por pila, mientras que <strong> [valor_2] </strong> equivale a la cantidad de pilas que se van a crear
- Para la interfaz e interacciones con el usuario se utiliza para los rangos, un valor más que con el que se trabaja realmente en las funciones y demás (por ejemplo, si se muestra que se está trabajando, en la interfaz. con [1 - 3], en realidad se está trabajando con [0 - 2])
- Se utiliza como base el código anterior, pero, se cambian ciertas cosas para realizar trabajo con strings, ya que se utiliza para colocarle nombre único a cada caja en vez de valores por pila (como se realizaba en la actividad anterior).
- Para colocar los nombres a cada contenedor se utiliza static int para que se evada la repetición de valores, colocándo los nombres por el usuario de forma automática. El usuario en esta sección solo debe decidir con qué pila trabajar y cuántos contenedores agregar.


<div>
<h2></h2>
</div>

```
- Ignorar esto, son apuntes para mí

Para la compilación de los códigos se utiliza: 
> g++ [programa].cpp -o [programa] && ./[programa]
O, si ya está el ejecutable presente:
> g++ ./[programa]
```
