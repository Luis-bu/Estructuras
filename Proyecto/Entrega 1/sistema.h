#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <vector>
#include "manejadorcomandos.h"

using namespace std;

class Sistema {
private:
    ManejadorComandos manejador;

public:
    Sistema();
    void ejecutarComando(const string& cmd, const vector<string>& params);
    void mostrarAyuda();
    void mostrarAyudaComando(const string& cmd);
};

#endif