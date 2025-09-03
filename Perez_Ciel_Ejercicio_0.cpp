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
void imprimirPaciente(const Paciente& paciente) { 
    cout << "\n" << "> Nombre: " << paciente.nombre;
    cout << "\n" << "> Edad: " << paciente.edad;
    cout << "\n" << "> Peso: " << paciente.peso << " kg";
    cout << "\n" << "> Altura: " << paciente.altura << " cm";
    cout << "\n__________________";
}


// Funcion principal
int main(){ 
    // Ejemplos de pacientes
    Paciente paciente1 = {"Cuca", 33, 74.5, 135};
    Paciente paciente2 = {"Gertrudis", 21, 60.0, 165};
    Paciente paciente3 = {"ElefanteGuerreroPsiquicoAncestral", 100, 140.7, 200};

    imprimirPaciente(paciente1); // Imprime paciente 1
    imprimirPaciente(paciente2); // Imprime paciente 2
    imprimirPaciente(paciente3); // Imprime paciente 3

    return 0; 
}