#include "sistema.h"

// Constructor
Sistema::Sistema() {}

// Función para ejecutar un comando
void Sistema::ejecutarComando(const string& cmd, const vector<string>& params) {
    manejador.ejecutarComando(cmd, params);
}

// Función para mostrar ayuda
void Sistema::mostrarAyuda() {
    manejador.mostrarAyuda();
}

// Función para mostrar ayuda de un comando específico
void Sistema::mostrarAyudaComando(const string& cmd) {
    manejador.mostrarAyudaComando(cmd);
}