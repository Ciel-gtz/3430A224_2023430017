#include <iostream> 
#include <stdio.h> // Libreria para entrada y salida estandar
#include <stdlib.h> // Libreria para gestion de memoria dinamica
using namespace std; 

// Estructura para almacenar la informacion de los pacientes
struct Paciente { 
    string nombre;
    int edad;
    float peso;
    int altura;
    Paciente* next;
};


    // Funciones: Imprimir, Agregar y Eliminar pacientes
/*void imprimirPaciente(Paciente paciente) { 
    cout << "\n" << "> Nombre: " << paciente.nombre;
    cout << "\n" << "> Edad: " << paciente.edad;
    cout << "\n" << "> Peso: " << paciente.peso << " kg";
    cout << "\n" << "> Altura: " << paciente.altura << " cm";
    cout << "\n__________________";
}*/
// Crea paciente
Paciente* creaPaciente (string nombre_, int edad_, float peso_, int altura_){ 
	Paciente* newPaciente = new Paciente; // Reserva dinamica de memoria
    newPaciente->nombre = nombre_; 
	newPaciente->edad = edad_; 
    newPaciente->peso = peso_; 
    newPaciente->altura = altura_;
	newPaciente->next = NULL; 
	return newPaciente;
}



/*void agregarPaciente(Nodo*& head, const Paciente& paciente) {
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
}*/

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

// Liberar memoria
void liberarPacientes(Paciente *head) {
	Paciente *current = head; // Se asigna la cabeza de lista como nodo actual
	while (current != NULL) { // Se recorre hasta el ultimo nodo
		Paciente *next = current->next; // Se guarda referencia al siguiente nodo
		free(current); // Se libera la memoria del nodo actual
		current = next; // Se avanza al siguiente nodo
	}
}


// Funcion principal
int main(){     
    Paciente *head = NULL; // Punero a la cabeza de lista
	Paciente *newPatient; // Puntero temporal para la creacion de nuevos nodos

    // Ejemplos de pacientes
    newPatient = creaPaciente("Cuca", 33, 74.5, 135);
    /*agregarPaciente(&head, newPatient); // Se agrega a la lista
    newPatient = creaPaciente("Gertrudis", 21, 60.0, 165);
    agregarPaciente(&head, newPatient);
    newPatient = creaPaciente("ElefanteGuerreroPsiquicoAncestral", 100, 140.7, 200);
    agregarPaciente(&head, newPatient); // Se agrega a la lista*/


    // Almacena los pacientes en la lista dinamica por medio de la funcion creaPaciente
    /*creaPaciente(ptrPaciente, paciente1);
    creaPaciente(ptrPaciente, paciente2);
    creaPaciente(ptrPaciente, paciente3);*/

    /*pacientes.push_back(paciente1);
    pacientes.push_back(paciente2);
    pacientes.push_back(paciente3);*/

    /*imprimirPaciente(pacientes[0]); // Imprime paciente 1
    imprimirPaciente(pacientes[1]); // Imprime paciente 2
    imprimirPaciente(pacientes[2]); // Imprime paciente 3*/

    liberarPacientes(head); // Se libera la memoria de la lista
    return 0; 
}