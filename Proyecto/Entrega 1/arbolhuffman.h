#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include <unordered_map>
#include <string>
#include "nodo.h"

class ArbolHuffman {
private:
    Nodo* raiz;
    std::unordered_map<char, std::string> codigos;
    void construirCodigos(Nodo* nodo, const std::string& prefijo);
    void liberar(Nodo* nodo);
public:
    // Construye el árbol a partir de un mapa de frecuencias
    ArbolHuffman(const std::unordered_map<char, unsigned long long>& frec);
    // Destructor
    ~ArbolHuffman();
    // Devuelve el mapa de códigos binarios
    const std::unordered_map<char, std::string>& obtenerCodigos() const;
    // Devuelve la raíz del árbol
    Nodo* obtenerRaiz() const;
};

#endif // ARBOLHUFFMAN_H
