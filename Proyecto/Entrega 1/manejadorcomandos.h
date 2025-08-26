#ifndef MANEJADORCOMANDOS_H
#define MANEJADORCOMANDOS_H

#include <string>
#include <vector>
#include <fstream>
#include "secuencia.h"

using namespace std;

// Estructura que representa un comando
struct Comando {
    string nombre;
    int numParametros;
    string textoAyuda;
};

// Definición de la clase ManejadorComandos
class ManejadorComandos {
private:
    vector<Comando> comandos;
    vector<Secuencia> secuencias;

    bool esEntero(const string& str);
    string cargarSecuencia(ifstream& archivo);
    int contarBases(const string& secuencia);
    vector<char> getOrdenTabla1();
    bool buscarComando(const string& cmd, Comando& comando) const;

public:
    ManejadorComandos();
    bool validarComando(const string& cmd, const vector<string>& params);
    void ejecutarComando(const string& cmd, const vector<string>& params);
    void mostrarAyuda();
    void mostrarAyudaComando(const string& cmd);
};

#endif