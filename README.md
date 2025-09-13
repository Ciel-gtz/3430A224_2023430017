<div align="center">
<h2>En actividad_1.cpp:</h2>
</div>
- Se reutiliza <strong> control_int() </strong> para control de errores 
- En <strong> Pop() </strong> se retorna el último dato de la pila, pero, esto no es necesario, sobretodo en este caso, ya que solo se quería retirar este valor de la pila.
Se pudo utilizar en cambio una función void de la siguiente forma:
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

<div align="center">
<h2>En actividad_2.cpp:</h2>
 </div>



```
Para la compilación de los códigos se utiliza: 
> g++ [programa].cpp -o [programa] && ./[programa]
O, si ya está el ejecutable presente:
> g++ ./[programa]
```