#include <iostream>
#include <sstream>
#include <vector>
#include "sistema.h"

using namespace std;

vector<string> dividir(const string& entrada) {
    vector<string> tokens;
    stringstream ss(entrada);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

//CORRECCIÓN: "No es necesario que salga "Procesamiento completado." cada vez que se puede ejecutar el comando. Eso tal vez servía para la entrega 0, pero ahora sólo es necesario que salgan los mensajes definidos en el enunciado."
//SOLUCIÓN: Se ha eliminado el mensaje "Procesamiento completado." para cumplir con el requisito.
// Función principal que maneja la interacción con el usuario.
int main() {
    Sistema sistema;
    string entrada;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Bienvenido a nuestro programa. Ingrese 'ayuda' para ver los comandos disponibles o 'ayuda <comando>' para ver detalles." << endl;

    while (true) {
        cout << "$ ";
        getline(cin, entrada);
        entrada.erase(0, entrada.find_first_not_of(" \n\r\t"));
        entrada.erase(entrada.find_last_not_of(" \n\r\t") + 1);
        if (entrada.empty()) continue;

        vector<string> tokens = dividir(entrada);
        string comando = tokens[0];
        vector<string> params(tokens.begin() + 1, tokens.end());

        if (comando == "salir" && params.empty()) {
            break;
        } else if (comando == "salir" && !params.empty()) {
            cout << "El comando 'salir' no acepta parámetros." << endl;
            continue;
        } else if (comando == "ayuda" && params.empty()) {
            sistema.mostrarAyuda();
        } else if (comando == "ayuda" && params.size() == 1) {
            sistema.mostrarAyudaComando(params[0]);
        } else {
            sistema.ejecutarComando(comando, params);
        }

        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }

    return 0;
}
