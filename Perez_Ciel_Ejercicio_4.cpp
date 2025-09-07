#include <iostream> 
#include <fstream> // Libreria para manejo de archivos
#include <stdio.h> // Libreria para entrada y salida estandar
#include <stdlib.h> // Libreria para gestion de memoria dinamica
using namespace std; 

// Estructura para almacenar la informacion de los pacientes
struct Paciente { 
    string nombre;
    int edad;
    float peso;
    float altura;
    Paciente* next;
};



// Funciones: Imprimir, Agregar y Eliminar pacientes
    // Crea paciente
Paciente* creaPaciente (string nombre_, int edad_, float peso_, float altura_){ 
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
        cout << "\n" << "> Altura: " << actual->altura << " m";
        cout << "\n__________________\n";
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



// Calculos con datos de pacientes
    // Promedio peso
float promedioPeso(Paciente *head) {
	Paciente *actual = head; // Se asigna la cabeza de lista como nodo actual

    // Valores iniciales vacios
    float suma_peso = 0;
    int contador = 0;

	while (actual != NULL) { // Se recorre hasta el ultimo nodo
        float peso_actual = actual->peso;
        suma_peso += peso_actual; // Suma de pesos
        contador += 1; // Para ver cuantos pacientes hay
	actual = actual->next; // Se avanza entre los nodos de la lista para ir al siguiente paciente
	}

    float promedio = suma_peso/contador;
    return promedio;
}

    // Promedio edad
int promedioEdad(Paciente *head) {
	Paciente *actual = head; // Se asigna la cabeza de lista como nodo actual

    // Valores iniciales vacios
    int suma_edad = 0;
    int contador = 0;

	while (actual != NULL) { // Se recorre hasta el ultimo nodo
        int edad_actual = actual->edad;
        suma_edad += edad_actual; // Suma de edades
        contador += 1; // Para ver cuantos pacientes hay
	actual = actual->next; // Se avanza entre los nodos de la lista para ir al siguiente paciente
	}

    int promedio = suma_edad/contador;
    return promedio;
}

    // Checkear IMC
void check_IMC(float imc_calculado) {
    // Revisa los rangos de IMC y lo imprime dependiendo en que categoria caiga
    if (imc_calculado < 18.5) {
        cout << "  | El IMC es bajo\n" << endl;
    } else if (imc_calculado >= 18.5 && imc_calculado <= 24.9) {
        cout << "  | El IMC es normal\n" << endl;
    } else {
        cout << "  | El IMC es alto\n" << endl;
    }
}

    // IMC individual
void pacienteIMC(Paciente *head) {
    Paciente *actual = head; // Se asigna la cabeza de lista como nodo actual

    cout << "\n[ Indice de Masa Corporal (IMC) por paciente ]\n";

    while (actual != NULL) { // Revisa el IMC individualmente por paciente
        float peso_actual = actual->peso;
        float altura_actual = actual->altura;

        // Calculo IMC
        float imc_calculado = peso_actual / (altura_actual * altura_actual);

        // Imprimir IMC por paciente
        cout << "> El IMC de " << actual->nombre << " es de " << imc_calculado << endl;
        // Checkear si es normal, muy alto o muy bajo
        check_IMC(imc_calculado);
        
    actual = actual->next; // Se avanza entre los nodos de la lista para ir al siguiente paciente
    }
}



// Manejo de archivos
    // Cargar CSV
void cargarCSV(Paciente **head) {
    ifstream iFile; // Declara el archivo de entrada
    iFile.open("pacientes.csv"); // Abre el archivo en modo lectura

    // Variables vacias**
    string nombre, texto, line;
    int location, edad;
    float peso, altura;

    getline(iFile, line); // Lee y descarta el header


    while (getline(iFile, line)) {

        // nombre
        location = line.find(',');
        nombre = line.substr(0, location);

        // edad
        texto = line.substr(location + 1);
        location = texto.find(',');
        edad = stoi(texto.substr(0, location));

        // peso
        texto = texto.substr(location + 1);
        location = texto.find(',');
        peso = stof(texto.substr(0, location));

        // altura
        texto = texto.substr(location + 1);
        altura = stof(texto);

        
         // crear y agregar
        Paciente *newPatient = creaPaciente(nombre, edad, peso, altura);
        agregarPaciente(head, newPatient);
    }

    iFile.close(); // Cierra el archivo
}

    // Agregar pacientes a CSV


// Interacciones con el usuario
    // funcion para capturar datos de pacientes
void capturarDatosPaciente(int &contador_pacientes_totales, string &nombre, int &edad, float &peso, float &altura) {
    cout << "\n| Cual es el nombre de este paciente? [Ejemplo: Juan] > ";
    cin >> nombre;
    cout << "| Cual es la edad de este paciente? [Ejemplo: 57] > ";
    cin >> edad;
    cout << "| Cual es el peso (kg) de este paciente? [Ejemplo: 74.5] > ";
    cin >> peso;
    cout << "| Cual es la altura (m) de este paciente? [Ejemplo: 1.80] > ";
    cin >> altura;
    cout << "| [ El paciente " << nombre << " ha sido agregado exitosamente!]\n" << endl;
}


// Menu interactuable
int menu() {
    int opcion = 0;
    cout << "\n++++++++++++\nSeleccione una opcion:\n";
    cout << "1. Agregar paciente\n";
    cout << "2. Mostrar pacientes\n";
    cout << "3. Calcular promedios de edad y peso\n";
    cout << "4. Calcular IMC por paciente\n";
    cout << "5. Leer CSV\n";   /****** */
    cout << "6. Agregar pacientes a CSV\n"; /******** */
    cout << "7. Salir + borrar memoria\n";
    cout << "Opcion: ";
    cin >> opcion;
    while (opcion < 1 || opcion > 7) {
        cout << "[Debe elegir una opcion valida (1-5)] : ";
        cin >> opcion;
    }
    return opcion;
}


// Funcion principal
int main(){     
    Paciente *head = NULL; // Punero a la cabeza de lista
    Paciente *newPatient; // Puntero temporal para la creacion de nuevos nodos
    int opcion = 0;

    // Al ver las opciones, revisa la que eligió el usuario y sigue respecto a eso
    while (opcion != 7) { // Y se reitera hasta que el usuario elija salir
        opcion = menu();
        cout << "____________" << endl;

        // Opcion 1: Usuario agrega pacientes
        if (opcion == 1) {
            // Variables iniciales
            int contador_pacientes_totales, edad;
            string nombre;
            float peso, altura;

            // Crea contador
            cout << "Cuantos pacientes desea agregar? : ";
            cin >> contador_pacientes_totales;

            // Agrega informacion de pacientes mientras el contador sea distinto de 0
            while (contador_pacientes_totales != 0){
                contador_pacientes_totales -= 1;
                capturarDatosPaciente(contador_pacientes_totales, nombre, edad, peso, altura);
                newPatient = creaPaciente(nombre, edad, peso, altura);
                agregarPaciente(&head, newPatient);
            }
        }

        // Opcion 2: Imprime los pacientes
        if (opcion == 2) {
            imprimirPaciente(head); // Imprime los pacientes de la lista
        }

        // Opcion 3: Calcula promedios
        if (opcion == 3) {
            // Calculos con datos de pacientes
            float promedioPeso_ = promedioPeso(head); // Promedio de peso
            int promedioEdad_ = promedioEdad(head); // Promedio de edad

            // Imprimir valores grupales obtenidos
            cout << "\n+ El peso en promedio es: " << promedioPeso_ << endl;
            cout << "+ La edad en promedio es: " << promedioEdad_ << endl;
        }

        // Opcion 4: Calcula IMC por paciente
        if (opcion == 4) {
            pacienteIMC(head); // calcula e imprime IMP por paciente + manda a checkear si es normal, muy alto o muy bajo
        }

        // Opcion 5: Cargar CSV
        if (opcion == 5) {
            cargarCSV(&head);
            // Aqui se implementaria la carga de un archivo CSV
        }

        // Opcion 6: Agregar pacientes a CSV
        if (opcion == 6) {
            cout << "Agregando pacientes a CSV)\n";
            // Aqui se implementaria la adición de pacientes a un archivo CSV
        }
    }

    liberarPacientes(head); // Se libera la memoria de la lista    
    return 0;
}
