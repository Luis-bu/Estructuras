#include <iostream>
#include <sstream>
#include <vector>
#include "comandos.h"

std::vector<std::string> dividir(const std::string& entrada) {
    std::vector<std::string> tokens;
    std::stringstream ss(entrada);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ManejadorComandos manejador;
    std::string entrada;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, entrada);
        if (entrada.empty()) continue;

        auto tokens = dividir(entrada);
        std::string comando = tokens[0];
        std::vector<std::string> params(tokens.begin() + 1, tokens.end());

        if (comando == "salir") {
            break;
        } else if (comando == "ayuda" && params.empty()) {
            manejador.mostrarAyuda();
        } else if (comando == "ayuda" && params.size() == 1) {
            manejador.mostrarAyudaComando(params[0]);
        } else if (manejador.validarComando(comando, params)) {
            std::cout << "Comando " << comando << " válido, pero no implementado en Entrega 0." << std::endl;
        }
    }

    return 0;
}