#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <vector>
#include <string>

using namespace std;

// Clase que representa una secuencia
class Secuencia {
private:
    string nombre;
    string bases;
    size_t lineLength;

public:
    Secuencia(const string& n, const string& b, size_t ll = 70);
    int contarBases() const;
    int buscarSubsecuencia(const string& sub) const;
    void enmascararSubsecuencia(const string& sub);
    string getNombre() const;
    string getBases() const;
    void setBases(const string& b);
    size_t getLineLength() const; 
    const std::vector<std::string>& getLineas() const;
};

#endif