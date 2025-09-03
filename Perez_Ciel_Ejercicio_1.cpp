#include <iostream> 
using namespace std; 



// Estructura para almacenar la informacion de los pacientes
struct Paciente { 
    string nombre;
    int edad;
    float peso;
    int altura;
};


// Imprime pacientes
void imprimirPaciente(Paciente paciente) { 
    cout << "\n" << "> Nombre: " << paciente.nombre;
    cout << "\n" << "> Edad: " << paciente.edad;
    cout << "\n" << "> Peso: " << paciente.peso << " kg";
    cout << "\n" << "> Altura: " << paciente.altura << " cm";
    cout << "\n__________________";
}


// Funcion principal
int main(){ 

    Paciente pacientes[3]; // Arreglo de pacientes

    // Ejemplos de pacientes
    Paciente paciente1 = {"Cuca", 33, 74.5, 135};
    Paciente paciente2 = {"Gertrudis", 21, 60.0, 165};
    Paciente paciente3 = {"ElefanteGuerreroPsiquicoAncestral", 100, 140.7, 200};

    // Almacena los pacientes en el arreglo
    pacientes[0] = paciente1;
    pacientes[1] = paciente2;
    pacientes[2] = paciente3;

    imprimirPaciente(pacientes[0]); // Imprime paciente 1
    imprimirPaciente(pacientes[1]); // Imprime paciente 2
    imprimirPaciente(pacientes[2]); // Imprime paciente 3

    return 0; 
}