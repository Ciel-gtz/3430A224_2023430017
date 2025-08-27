#include <iostream> 
using namespace std; 


// Funciones numericas
int par_o_no(int numero){ // Revisa si el valor es par o no.
    if (numero % 2 == 0) {
        cout << "- o El valor [" << numero << "] ES un numero par" << endl;
    } else {
        cout << "- x El valor [" << numero << "] NO ES un numero par" << endl;
    }
    return 0;
}

void de_1_a_10(){ // Para que revise los valores pares del 1 al 10
    for (int numero = 1; numero <= 10; numero++) {
        par_o_no(numero);
    }
} 


// Funciones string
int Longitud_string(string texto){ // Revisa la longitud de un string
    cout << "> La longitud del texto anterior es de " << texto.length() << " letras\n" << endl;
    return 0;
}


// Funcion principal
int main(){ 
    // Parte numerica
    de_1_a_10(); // Llama a la funcion que revisa los valores pares del 1 al 10

    int numero_usuario;
    cout << "\nIngrese un numero: "; // Solicita un numero al usuario
    cin >> numero_usuario; // Lee la respuesta del usuario

    cout << "\nEl numero ingresado es: " << numero_usuario << "\n"; // Imprime el numero ingresado por el usuario
    par_o_no(numero_usuario); // Llama a la funcion que revisa si el numero del usuario es par o no

    // Parte string
    string texto_almacenado = "\n_______________________\nAhora veremos la longitud de un string"; // Texto almacenado
    cout << texto_almacenado << endl;
    Longitud_string(texto_almacenado);

    string texto_usuario;
    cout << "Ahora ingrese un texto: "; // Solicita un texto al usuario
    cin >> texto_usuario; // Lee la respuesta del usuario

    Longitud_string(texto_usuario); // Llama a la funcion que revisa la longitud del string ingresado por el usuario

    return 0; 
}