// NodoGrafo.cxx
#include "nodografo.h"
#include <sstream>

NodoGrafo::NodoGrafo(int f, int c, char b)
    : fila(f), columna(c), base(b), distanciaMin(1e18), padre(nullptr) {}

int NodoGrafo::getFila() const { return fila; }
int NodoGrafo::getColumna() const { return columna; }
char NodoGrafo::getBase() const { return base; }
double NodoGrafo::getDistancia() const { return distanciaMin; }
NodoGrafo* NodoGrafo::getPadre() const { return padre; }

void NodoGrafo::setDistancia(double d) { distanciaMin = d; }
void NodoGrafo::setPadre(NodoGrafo* p) { padre = p; }

bool NodoGrafo::operator>(const NodoGrafo& otro) const {
    return distanciaMin > otro.distanciaMin;
}

std::string NodoGrafo::toString() const {
    std::ostringstream oss;
    oss << base << "(" << fila << "," << columna << ")";
    return oss.str();
}