#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include <unordered_map>
#include <string>

class ArbolHuffman {
public:
    // Nodo interno del árbol
    struct Nodo {
        char c;
        unsigned long long freq;
        Nodo* left;
        Nodo* right;
        Nodo(char ch, unsigned long long f) : c(ch), freq(f), left(nullptr), right(nullptr) {}
        Nodo(Nodo* l, Nodo* r) : c('\0'), freq(l->freq + r->freq), left(l), right(r) {}
    };
private:
    Nodo* raiz;
    std::unordered_map<char, std::string> codigos;
    void construirCodigos(Nodo* nodo, const std::string& prefijo);
    void liberar(Nodo* nodo);
public:
    // Construye el árbol de Huffman a partir de un mapa de frecuencias.
    ArbolHuffman(const std::unordered_map<char, unsigned long long>& frec);
    ~ArbolHuffman();

    // Devuelve un mapa de códigos (carácter a cadena de bits).
    const std::unordered_map<char, std::string>& obtenerCodigos() const;

    // Devuelve la raíz del árbol (para decodificación).
    Nodo* obtenerRaiz() const;
};

#endif // ARBOLHUFFMAN_H
