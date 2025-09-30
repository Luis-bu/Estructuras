#include "programa.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>
#include <iomanip>

using namespace std;

Programa::Programa() : tiempoABB(0), tiempoAVL(0), tiempoRN(0) {}

Programa::~Programa() {
    limpiar();
}

// Configuramos la ruta del archivo de entrada
void Programa::configurarEntrada(const string& ruta) {
    rutaEntrada = ruta;
}

// Leemos las operaciones desde archivo
int Programa::leerOperaciones() {
    ifstream in(rutaEntrada);
    if (!in.is_open()) return 0;

    operaciones.clear();
    while (in.good()) {
        char op;
        string codigoStr;
        in >> op >> codigoStr;
        if (!in.good()) break;
        if (op != 'A' && op != 'E') continue;
        int codigo = atoi(codigoStr.c_str());
        operaciones.push_back({op, codigo});
    }
    in.close();
    return operaciones.size();
}

// Ejecutamos las operaciones en ABB, AVL y RN
void Programa::ejecutar() {
    // ABB
    clock_t t0 = clock();
    for (size_t i=0; i<operaciones.size(); ++i) {
        if (operaciones[i].tipo == 'A') abb.insertar(operaciones[i].codigo);
        else abb.eliminar(operaciones[i].codigo);
    }
    clock_t t1 = clock();
    tiempoABB = (t1 - t0) / double(CLOCKS_PER_SEC);

    // AVL
    t0 = clock();
    for (size_t i=0; i<operaciones.size(); ++i) {
        if (operaciones[i].tipo == 'A') avl.insertar(operaciones[i].codigo);
        else avl.eliminar(operaciones[i].codigo);
    }
    t1 = clock();
    tiempoAVL = (t1 - t0) / double(CLOCKS_PER_SEC);

    // RN
    t0 = clock();
    for (size_t i=0; i<operaciones.size(); ++i) {
        if (operaciones[i].tipo == 'A') rn.insert(operaciones[i].codigo);
        else rn.erase(operaciones[i].codigo);
    }
    t1 = clock();
    tiempoRN = (t1 - t0) / double(CLOCKS_PER_SEC);
}

// Guardamos los recorridos inorden de cada estructura
void Programa::recorrerInorden() {
    inordenABB.clear();
    inordenAVL.clear();
    inordenRN.clear();

    abb.inorden(inordenABB);
    avl.inorden(inordenAVL);

    for (set<int>::iterator it = rn.begin(); it != rn.end(); ++it) {
        inordenRN.push_back(*it);
    }
}

// Comparamos si ABB, AVL y RN tienen los mismos datos
bool Programa::compararEstructuras() {
    return (inordenABB == inordenRN && inordenAVL == inordenRN);
}

// Mostramos resultados en consola
void Programa::mostrarResultados() {
    cout << "Tiempo ABB: " << tiempoABB << " s\n";
    cout << "Tiempo AVL: " << tiempoAVL << " s\n";
    cout << "Tiempo RN (std::set): " << tiempoRN << " s\n";
    cout << "Comparacion: "
         << (compararEstructuras() ? "TODOS IGUALES" : "DIFERENTES") << "\n";

    // Mostramos los recorridos directamente
    cout << "ABB inorden: ";
    for (int v : inordenABB) cout << setw(6) << setfill('0') << v << " ";
    cout << "\n";

    cout << "AVL inorden: ";
    for (int v : inordenAVL) cout << setw(6) << setfill('0') << v << " ";
    cout << "\n";

    cout << "RN inorden: ";
    for (int v : inordenRN) cout << setw(6) << setfill('0') << v << " ";
    cout << "\n";

}

// Limpiamos las estructuras y datos temporales
void Programa::limpiar() {
    abb.limpiar();
    avl.limpiar();
    rn.clear();
    operaciones.clear();
    inordenABB.clear();
    inordenAVL.clear();
    inordenRN.clear();
    tiempoABB = tiempoAVL = tiempoRN = 0;
}
