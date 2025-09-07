### Instrucciones Ejercicio_0
Escriba un programa en C++ que permita almacenar la informacion de pacientes en una estructura. Cada paciente debe contener como datos el nombre, edad, peso y altura. Dentro de la funcion main debe exponer tres ejemplos de “pacientes” entregando la informacion de cada uno de ellos por la salida estandar
\
\
### Instrucciones Ejercicio_1
Escriba un programa en C++ que permita almacenar la informacion de los pacientes (estructura) en un arreglo. Dentro de la funcion main debe incorporar los ejemplos de “pacientes” utilizados anteriormente, almacenarlos en el arreglo y entregar la informacion de cada uno de ellos por la salida estandar
\
\
### Instrucciones Ejercicio_2
Escriba un programa en C++ que permita almacenar la informacion de pacientes en una estructura para trabajar con una lista dinamica. Aquı no se puede utilizar la librerıa list y debe realizar la actualizacion de la estructura, la inclusion de las funciones para agregar, imprimir y eliminar. Dentro de la funcion main debe incorporar los ejemplos de pacientes y dejar en evidencia todas las funciones desarrolladas.
\
\
### Instrucciones Ejercicio_3
Escriba un programa en C++ que permita obtener algunos datos del espacio muestral de pacientes que se maneja y se encuentra almacenado en la lista. Es de interes poder conocer el promedio de edad y el promedio de peso del grupo presente ademas del IMC de cada uno de los pacientes. Dentro de la funcion main debe incorporar los ejemplos de pacientes y dejar en evidencia todas las funciones desarrolladas.

Respecto al IMC o Indice de Masa Corporal (IMC):
Este es uno de los indicadores mas utilizados para determinar si una persona tiene sobre-peso, obesidad o bajo peso.

IMC = peso / altura2

“Un IMC dentro de los rangos normales indica un peso saludable, mientras que un IMC muy alto o muy bajo puede ser un signo de riesgo para diversas enfermedades”
\
\
### Instrucciones Ejercicio_4
Escriba un programa en C++ que permita trabajar con la gestion de pacientes a traves de opciones interactivas. Es de interes poder incorporar un menu que permita a un usuario nave-gar por las opciones que existen y utilizar todas las funcionalidades (funciones desarrolladas).
Ademas se debe sumar la posibilidad de realizar la carga de informacion desde un archivo de texto plano o CSV
-
Se siguió el tutorial del usuario Shmeowlex "READING FROM A CSV IN C++ IN 6 MINUTES" en YouTube para lo relacionado a gestión de archivos.
También se utilizó el código presente en "https://www.codespeedy.com/taking-only-integer-input-in-cpp/" para la realización de la función control_int() y control_float(), las cuales se utilizan para evadir que el usuario ingrese letras cuando se requiere números.
El programa inicia con un menú, en el cual el usuario se mueve escribiendo un número con respecto a lo que desea realizar, el menú continúa mostrándose hasta que el usuario seleccione la opción de salir, en la cual se borra la memoria del struct de la RAM.
AVISO: La opción "Guardar informacion a CSV" reemplazará todo lo que ya estaba presente en el CSV, por ello se sugiere primero utilizar la opción "Cargar CSV" antes que todo. Esta opción también se puede utilizar para restaurar el CSV a su estado default (con solo los headers presentes).
AVISO 2: No existe algún control en caso de que se repitan nombres, en cambio, la opción "Eliminar un paciente" borrará al primer paciente que encuentre con el nombre que pidió borrar el usuario.
\
\
\
### Para la compilación de los códigos se utiliza: 
## g++ [programa].cpp -o [programa] && ./[programa]
