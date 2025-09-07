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

    // Imprimir pacientes
void imprimirPaciente(Paciente *head) {
	Paciente *actual = head; // Se asigna la cabeza de lista como nodo actual
	while (actual != NULL) { // Se recorre hasta el ultimo nodo
        cout << "\n" << "> Nombre: " << actual->nombre;
        cout << "\n" << "> Edad: " << actual->edad;
        cout << "\n" << "> Peso: " << actual->peso << " kg";
        cout << "\n" << "> Altura: " << actual->altura << " cm";
        cout << "\n__________________" << endl;
	actual = actual->next; // Se avanza entre los nodos de la lista para ir al siguiente paciente
	}
}

    // Agregar paciente al final de la lista
void agregarPaciente(Paciente **head, Paciente *newPaciente) {
    if (*head == NULL) { // Si la lista esta vacia se crea la cabeza
        *head = newPaciente;
    } else {
        Paciente *actual = *head; // Se asigna la cabeza de lista como nodo actual
        while (actual->next != NULL) {
            actual = actual->next; // Se avanza entre los nodos de la lista
        }
        actual->next = newPaciente; // Inserta al final
    }
}

    // Liberar memoria
void liberarPacientes(Paciente *head) {
	Paciente *actual = head; // Se asigna la cabeza de lista como nodo actual
	while (actual != NULL) { // Se recorre hasta el ultimo nodo
		Paciente *next = actual->next; // Se guarda referencia al siguiente nodo
		delete(actual); // Se libera la memoria del nodo actual
		actual = next; // Se avanza al siguiente nodo
	}
}

    // Elimina un paciente por nombre
void eliminarPaciente(Paciente*& head, const string& nombre_del) {
    Paciente *actual = head;
    Paciente *anterior = NULL;
    cout << "\n+ Eliminando a " << nombre_del << endl;

    while (actual != NULL) {
        if (actual->nombre == nombre_del) {
            if (anterior == NULL) {
                head = actual->next;
            } else {
                anterior->next = actual->next;
            }
            delete actual; // Liberar memoria del nodo eliminado
            return; // Salir después de eliminar el nodo
        }
        anterior = actual;
        actual = actual->next;
    }
}


// Funcion principal
int main(){     
    Paciente *head = NULL; // Punero a la cabeza de lista
	Paciente *newPatient; // Puntero temporal para la creacion de nuevos nodos

    // Ejemplos de pacientes
    newPatient = creaPaciente("Cuca", 33, 74.5, 135);
    agregarPaciente(&head, newPatient); // Se agrega a la lista
    newPatient = creaPaciente("Gertrudis", 21, 60.0, 165);
    agregarPaciente(&head, newPatient);
    newPatient = creaPaciente("ElefanteGuerreroPsiquicoAncestral", 100, 140.7, 200);
    agregarPaciente(&head, newPatient); // Se agrega a la lista

    imprimirPaciente(head); // Imprime los pacientes de la lista

    eliminarPaciente(head, "Gertrudis"); // Elimina a un paciente por nombre

    cout << "___________\nPacientes actualizados:" << endl;

    imprimirPaciente(head);

    liberarPacientes(head); // Se libera la memoria de la lista
    return 0; 
}