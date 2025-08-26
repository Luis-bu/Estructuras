#include "sistema.h"

Sistema::Sistema() {}

void Sistema::ejecutarComando(const string& cmd, const vector<string>& params) {
    manejador.ejecutarComando(cmd, params);
}

void Sistema::mostrarAyuda() {
    manejador.mostrarAyuda();
}

void Sistema::mostrarAyudaComando(const string& cmd) {
    manejador.mostrarAyudaComando(cmd);
}