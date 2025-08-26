#include <iostream>
#include <sstream>
#include <vector>
#include "sistema.h"

using namespace std;

// Función para dividir una cadena en tokens
vector<string> dividir(const string& entrada) {
    vector<string> tokens;
    stringstream ss(entrada);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Nuestro programa principal
int main() {
    Sistema sistema;
    string entrada;
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

        cout << "Procesamiento completado." << endl;
        cout << "--------------------------------------------" << endl;
    }

    return 0;
}