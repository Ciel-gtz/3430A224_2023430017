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



```
Para la compilación de los códigos se utiliza: 
> g++ [programa].cpp -o [programa] && ./[programa]
O, si ya está el ejecutable presente:
> g++ ./[programa]
```
