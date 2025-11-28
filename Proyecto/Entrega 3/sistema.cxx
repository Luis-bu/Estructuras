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

// Reconstruye las líneas originales a partir de bases y lineLength
const std::vector<std::string>& Secuencia::getLineas() const {
    static std::vector<std::string> lineas_cache;  // cache estático para no reconstruir cada vez
    lineas_cache.clear();

    size_t len = bases.length();
    for (size_t i = 0; i < len; i += lineLength) {
        size_t longitud_linea = std::min(lineLength, len - i);
        lineas_cache.push_back(bases.substr(i, longitud_linea));
    }
    return lineas_cache;
}