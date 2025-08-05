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

//Nuestro programa principal
//Aquí se gestionan los comandos y se interactúa con el usuario
int main() {
    ManejadorComandos manejador;
    std::string entrada;
    std::cout << "Bienvenido al programa. Ingrese 'ayuda' para ver los comandos disponibles o 'ayuda <comando>' para detalles." << std::endl;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, entrada);
        entrada.erase(0, entrada.find_first_not_of(" \n\r\t")); // Eliminamos los espacios en blanco al inicio
        entrada.erase(entrada.find_last_not_of(" \n\r\t") + 1); // Eliminamos los espacios en blancoal final
        if (entrada.empty()) continue;

        std::vector<std::string> tokens = dividir(entrada);
        std::string comando = tokens[0];
        std::vector<std::string> params(tokens.begin() + 1, tokens.end());

        if (comando == "salir") {
            break;  
        } else if (comando == "ayuda" && params.empty()) {
            manejador.mostrarAyuda();
        } else if (comando == "ayuda" && params.size() == 1) {
            manejador.mostrarAyudaComando(params[0]);
       } else if (manejador.validarComando(comando, params)) {
         std::cout << "Comando " << comando << " válido, pero no implementado en nuestra entrega" << std::endl;
         std::cout << "Procesamiento completado." << std::endl;
        }

    }

    return 0;
}