#include "programa.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " archivo_entrada.txt\n";
        return 1;
    }

    Programa prog;
    prog.configurarEntrada(argv[1]);

    if (prog.leerOperaciones() == 0) {
        cerr << "Error: no se pudieron leer operaciones\n";
        return 1;
    }

    prog.ejecutar();
    prog.recorrerInorden();
    prog.mostrarResultados();

    return 0;
}
