#include <iostream> 
using namespace std; 

// Estructura para almacenar la informacion de los pacientes
struct Paciente { 
    string nombre;
    int edad;
    float peso;
    int altura;
};

// Nodo de la lista enlazada
struct Nodo {
    Paciente datos;
    Nodo* siguiente;
};


    // Funciones: Imprimir, Agregar y Eliminar pacientes
/*void imprimirPaciente(Paciente paciente) { 
    cout << "\n" << "> Nombre: " << paciente.nombre;
    cout << "\n" << "> Edad: " << paciente.edad;
    cout << "\n" << "> Peso: " << paciente.peso << " kg";
    cout << "\n" << "> Altura: " << paciente.altura << " cm";
    cout << "\n__________________";
}*/

void agregarPaciente(Nodo*& head, const Paciente& paciente) {
    Nodo* nuevo = new Nodo{paciente, nullptr};
    if (head == nullptr) {
        head = nuevo;
    } else {
        Nodo* temp = head;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

/*void eliminarPaciente(Paciente pacientes[], int &numPacientes, int indice) {///***
    if (indice < 0 || indice >= numPacientes) {
        cout << "Indice invalido." << endl;
        return;
    }
    for (int i = indice; i < numPacientes - 1; i++) {
        pacientes[i] = pacientes[i + 1];
    }
    numPacientes--;
}*/


// Funcion principal
int main(){     
    Nodo* ptrPaciente = nullptr; // Puntero a paciente vacio

    // Ejemplos de pacientes
    Paciente paciente1 = {"Cuca", 33, 74.5, 135};
    Paciente paciente2 = {"Gertrudis", 21, 60.0, 165};
    Paciente paciente3 = {"ElefanteGuerreroPsiquicoAncestral", 100, 140.7, 200};

    // Almacena los pacientes en la lista dinamica por medio de la funcion agregarPaciente
    agregarPaciente(ptrPaciente, paciente1);
    agregarPaciente(ptrPaciente, paciente2);
    agregarPaciente(ptrPaciente, paciente3);

    /*pacientes.push_back(paciente1);
    pacientes.push_back(paciente2);
    pacientes.push_back(paciente3);*/

    /*imprimirPaciente(pacientes[0]); // Imprime paciente 1
    imprimirPaciente(pacientes[1]); // Imprime paciente 2
    imprimirPaciente(pacientes[2]); // Imprime paciente 3*/

    return 0; 
}