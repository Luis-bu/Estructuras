#include "nodo.h"

// Constructor para nodo hoja
Nodo::Nodo(char caracter, unsigned long long frecuencia)
    : c(caracter), freq(frecuencia), left(nullptr), right(nullptr) {}

// Constructor para nodo interno
Nodo::Nodo(Nodo* izquierdo, Nodo* derecho)
    : c('\0'), freq(0), left(izquierdo), right(derecho) {
    if (izquierdo) freq += izquierdo->freq;
    if (derecho) freq += derecho->freq;
}