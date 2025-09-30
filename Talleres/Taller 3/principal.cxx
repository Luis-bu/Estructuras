#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <cstdlib>

#include "abb.h"
#include "avl.h"
using namespace std;

// Guardamos una operación leída del archivo
struct Operacion {
    char tipo; // 'A' = Agregar, 'E' = Eliminar
    int codigo;
};

// Leemos todas las operaciones desde un archivo
bool leerOperaciones(const char* nombreArchivo, vector<Operacion>& ops) {
    ifstream in(nombreArchivo);
    if (!in.is_open()) return false;

    ops.clear();
    while (in.good()) {
        char op;
        string codigoStr;
        in >> op >> codigoStr;
        if (!in.good()) break;
        if (op != 'A' && op != 'E') continue;
        int codigo = atoi(codigoStr.c_str());
        ops.push_back({op, codigo});
    }
    in.close();
    return true;
}

// Convertimos un set en lista (para comparación inorden)
void listaDesdeSet(const set<int>& s, list<int>& salida) {
    salida.clear();
    for (set<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
        salida.push_back(*it);
    }
}

// Comparamos dos listas para verificar si son iguales
bool listasIguales(const list<int>& a, const list<int>& b) {
    if (a.size() != b.size()) return false;
    list<int>::const_iterator itA = a.begin();
    list<int>::const_iterator itB = b.begin();
    while (itA != a.end() && itB != b.end()) {
        if (*itA != *itB) return false;
        ++itA; ++itB;
    }
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " archivo_entrada.txt\n";
        return 1;
    }

    // Leemos operaciones desde archivo
    vector<Operacion> ops;
    if (!leerOperaciones(argv[1], ops)) {
        cerr << "Error al abrir archivo\n";
        return 1;
    }

    ABB abb;
    AVL avl;
    set<int> rn;

    // Procesamos en ABB
    clock_t t0 = clock();
    for (size_t i=0;i<ops.size();++i) {
        if (ops[i].tipo=='A') abb.insertar(ops[i].codigo);
        else abb.eliminar(ops[i].codigo);
    }
    clock_t t1 = clock();
    double tiempoABB = (t1-t0)/double(CLOCKS_PER_SEC);

    // Procesamos en AVL
    t0 = clock();
    for (size_t i=0;i<ops.size();++i) {
        if (ops[i].tipo=='A') avl.insertar(ops[i].codigo);
        else avl.eliminar(ops[i].codigo);
    }
    t1 = clock();
    double tiempoAVL = (t1-t0)/double(CLOCKS_PER_SEC);

    // Procesamos en RN (set de C++)
    t0 = clock();
    for (size_t i=0;i<ops.size();++i) {
        if (ops[i].tipo=='A') rn.insert(ops[i].codigo);
        else rn.erase(ops[i].codigo);
    }
    t1 = clock();
    double tiempoRN = (t1-t0)/double(CLOCKS_PER_SEC);

    // Comparamos recorridos inorden
    list<int> inABB, inAVL, inRN;
    abb.inorden(inABB);
    avl.inorden(inAVL);
    listaDesdeSet(rn, inRN);

    // Mostramos resultados
    cout << "Tiempo ABB: " << tiempoABB << " s\n";
    cout << "Tiempo AVL: " << tiempoAVL << " s\n";
    cout << "Tiempo RN (std::set): " << tiempoRN << " s\n";

    cout << "ABB == RN: " << (listasIguales(inABB,inRN)?"IGUALES":"DIFERENTES") << "\n";
    cout << "AVL == RN: " << (listasIguales(inAVL,inRN)?"IGUALES":"DIFERENTES") << "\n";

    return 0;
}
