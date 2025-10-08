// Este codigo permite generar la representacion de un arbol a traes del software graphviz.

#include <fstream>
#include <iostream>
using namespace std;

struct Node {
    string info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(const string& data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Recorrer el arbol en preorden y escribir en el archivo
void recorrer(Node* node, ofstream& fp) {
    if (node != nullptr) {
        if (node->left != nullptr) {
            fp << node->info << "->" << node->left->info << ";" << endl;
        } else {
            string cadena = node->info + "i";
            fp << cadena << "[shape=point];" << endl;
            fp << node->info << "->" << cadena << ";" << endl;
        }

        if (node->right != nullptr) {
            fp << node->info << "->" << node->right->info << ";" << endl;
        } else {
            string cadena = node->info + "d";
            fp << cadena << "[shape=point];" << endl;
            fp << node->info << "->" << cadena << ";" << endl;
        }

        recorrer(node->left, fp);
        recorrer(node->right, fp);
    }
}

// Generar y mostrar la visualizacion del arbol
void visualize(Node* root) {
    ofstream fp("arbol.txt");

    if (!fp.is_open()) {
        cerr << "Error al abrir el archivo arbol.txt" << endl;
        return;
    }

    fp << "digraph G {" << endl;
    fp << "node [style=filled fillcolor=yellow];" << endl;

    recorrer(root, fp);

    fp << "}" << endl;

    fp.close();

    // Generar y mostrar la imagen del árbol
    system("dot -Tpng -o arbol.png arbol.txt");
    system("eog arbol.png");
}

// Funcion main
int main() {
    Node* root = nullptr;
    root = createNode("A");
    
    root->left = createNode("B");
    root->right = createNode("C");

    root->left->left = createNode("D");
    root->left->right = createNode("E");

    root->right->left = createNode("F");
    root->right->right = createNode("G");

    root->right->right->left = createNode("H");
    root->left->left->right = createNode("I");

    visualize(root);

    return 0;
}

