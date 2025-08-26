#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>

using namespace std;

// Clase que representa una secuencia
class Secuencia {
private:
    string nombre;
    string bases;

public:
    Secuencia(const string& n, const string& b);
    int contarBases() const;
    int buscarSubsecuencia(const string& sub) const;
    void enmascararSubsecuencia(const string& sub);
    string getNombre() const;
    string getBases() const;
    void setBases(const string& b);
};

#endif