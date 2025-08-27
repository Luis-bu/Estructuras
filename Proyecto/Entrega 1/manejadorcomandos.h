#ifndef MANEJADORCOMANDOS_H
#define MANEJADORCOMANDOS_H

#include <string>
#include <vector>
#include <fstream>
#include "secuencia.h"

// Estructura que representa un comando
struct Comando {
    string nombre;
    int numParametros;
    string textoAyuda;
};

// Clase que maneja los comandos
class ManejadorComandos {
private:
    vector<Comando> comandos;
    vector<Secuencia> secuencias;

public:
    ManejadorComandos();
    bool esEntero(const string& str);
    vector<char> getOrden();
    bool buscarComando(const string& cmd, Comando& comando) const;
    bool validarComando(const string& cmd, const vector<string>& params);
    void ejecutarComando(const string& cmd, const vector<string>& params);
    void mostrarAyuda();
    void mostrarAyudaComando(const string& cmd);
};

#endif