#include <iostream> 
using namespace std; 

double cuadrado(double x){ // Eleva al cuadrado un numero de punto flotante de doble precisión.
    return x * x;
}

void imprimirCuadrado(double x){ // Imprime el cuadrado de x
    cout << "El cuadrado de " << x << " es " << cuadrado(x) << "\n";
} // Un return de tipo void indica que la funcion no devuelve ningun valor

int main(){ 
    imprimirCuadrado(1.234); // Print: El cuadrado de 1.234 es 1.52276
    imprimirCuadrado(5.555); // Print: El cuadrado de 5.555 es 30.864
    imprimirCuadrado(-1.5); // Print: El cuadrado de -1.5 es 2.25

    return 0; 
}