<div align="center">
<h1>Creación de un árbol binario</h1>
</div>

Para que el código pueda correr es necesario tener instalado:
- Compilador de C++. instalable utilizando `sudo apt install g++`
- Graphviz. instalable utilizando `sudo apt install graphviz -y`

<div align="center">
<h2>Sobre el código</h2>
</div>




en GenerarGrafo no puse eog porque se me hace mas comodo el abrir el archivo png en visual mientras interactuo con la terminal y asi ir viendo los cambios en vivo
opcion default ->Error (dificil que llegue aqui por como ya revisa los vaores en menu(), pero, lo pongo por si acaso)

al leer el archivo insercionAVL revisa inmediatamente si se repite un valor o no, si se repite entonces no se va a agregar, manejando así posibles repeticiones del archivo csv

- se va actualizando el archivo de grafo cada vez que borras o insertas un nodo para una fácil visualización mientras se corre el código
cuando borra nodo raiz, se usa subarbol izquierdo, nodo más a la derecha
