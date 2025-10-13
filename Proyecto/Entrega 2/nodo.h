#ifndef NODO_H
#define NODO_H

#include <cstdint>
// Definición de un nodo para el árbol de Huffman
class Nodo {
public:
    char c;                       
    unsigned long long freq;      
    Nodo* left;                   
    Nodo* right;                  

    Nodo(char caracter, unsigned long long frecuencia);
    Nodo(Nodo* izquierdo, Nodo* derecho);
};

#endif // NODO_H