#include <iostream> 
using namespace std; 

// Estructura para almacenar la informacion de los pacientes
struct Paciente { 
    string nombre;
    int edad;
    float peso;
    int altura;
};



// Funciones: Imprimir, Agregar y Eliminar pacientes
void imprimirPaciente(Paciente paciente) { 
    cout << "\n" << "> Nombre: " << paciente.nombre;
    cout << "\n" << "> Edad: " << paciente.edad;
    cout << "\n" << "> Peso: " << paciente.peso << " kg";
    cout << "\n" << "> Altura: " << paciente.altura << " cm";
    cout << "\n__________________";
}

void agregarPaciente(Paciente pacientes[], int &numPacientes, Paciente nuevoPaciente) {///***
    pacientes[numPacientes] = nuevoPaciente;
    numPacientes++;
}

void eliminarPaciente(Paciente pacientes[], int &numPacientes, int indice) {///***
    if (indice < 0 || indice >= numPacientes) {
        cout << "Indice invalido." << endl;
        return;
    }
    for (int i = indice; i < numPacientes - 1; i++) {
        pacientes[i] = pacientes[i + 1];
    }
    numPacientes--;
}



// Funcion principal
int main(){ 

    Paciente pacientes[3]; // Lista dinamica de pacientes*******

    // Ejemplos de pacientes
    Paciente paciente1 = {"Cuca", 33, 74.5, 135};
    Paciente paciente2 = {"Gertrudis", 21, 60.0, 165};
    Paciente paciente3 = {"ElefanteGuerreroPsiquicoAncestral", 100, 140.7, 200};

    // Almacena los pacientes en el arreglo**** Cambiar esto por lista dinamica iggggg lolz
    pacientes[0] = paciente1;
    pacientes[1] = paciente2;
    pacientes[2] = paciente3;

    imprimirPaciente(pacientes[0]); // Imprime paciente 1
    imprimirPaciente(pacientes[1]); // Imprime paciente 2
    imprimirPaciente(pacientes[2]); // Imprime paciente 3

    return 0; 
}