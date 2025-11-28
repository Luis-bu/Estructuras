#include "secuencia.h"

// Constructor
Secuencia::Secuencia(const string& n, const string& b, size_t ll) : nombre(n), bases(b), lineLength(ll) {}

// Contamos las bases en una secuencia
int Secuencia::contarBases() const {
    int count = 0;
    for (unsigned int i = 0; i < bases.length(); ++i) {
        if (bases[i] != '-') count++;
    }
    return count;
}

// Buscamos una subsecuencia en la secuencia
int Secuencia::buscarSubsecuencia(const string& sub) const {
    int count = 0;
    size_t pos = 0;
    while ((pos = bases.find(sub, pos)) != string::npos) {
        count++;
        pos++;
    }
    return count;
}

// Enmascaramos una subsecuencia en la secuencia
void Secuencia::enmascararSubsecuencia(const string& sub) {
    size_t pos = 0;
    while ((pos = bases.find(sub, pos)) != string::npos) {
        bases.replace(pos, sub.length(), string(sub.length(), 'X'));
        pos += sub.length();
    }
}

// Getters y Setters
string Secuencia::getNombre() const { return nombre; }
string Secuencia::getBases() const { return bases; }
void Secuencia::setBases(const string& b) { bases = b; }
size_t Secuencia::getLineLength() const { return lineLength; }