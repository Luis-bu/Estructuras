#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <ctime>
#include <cstdlib>

#include "abb.h"
#include "avl.h"

// Estructura para guardar cada operación leída del archivo
struct Operacion {
    char tipo; // 'A' = Agregar, 'E' = Eliminar
    int codigo;
};

// Función que carga las operaciones desde el archivo
bool leerOperaciones(const char* nombreArchivo, std::vector<Operacion>& ops) {
    std::ifstream in(nombreArchivo);
    if (!in.is_open()) return false;

    ops.clear();
    while (in.good()) {
        char op;
        std::string codigoStr;
        in >> op >> codigoStr;
        if (!in.good()) break;
        if (op != 'A' && op != 'E') continue;
        int codigo = std::atoi(codigoStr.c_str());
        ops.push_back({op, codigo});
    }
    in.close();
    return true;
}

// Convierte un std::set en una lista (para comparación inorden)
void listaDesdeSet(const std::set<int>& s, std::list<int>& salida) {
    salida.clear();
    for (std::set<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
        salida.push_back(*it);
    }
}

// Compara dos listas para ver si contienen los mismos elementos
bool listasIguales(const std::list<int>& a, const std::list<int>& b) {
    if (a.size() != b.size()) return false;
    std::list<int>::const_iterator itA = a.begin();
    std::list<int>::const_iterator itB = b.begin();
    while (itA != a.end() && itB != b.end()) {
        if (*itA != *itB) return false;
        ++itA; ++itB;
    }
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " archivo_entrada.txt\n";
        return 1;
    }

    // Leer operaciones desde archivo
    std::vector<Operacion> ops;
    if (!leerOperaciones(argv[1], ops)) {
        std::cerr << "Error al abrir archivo\n";
        return 1;
    }

    ABB abb;
    AVL avl;
    std::set<int> rn;

    // Procesar en ABB y medir tiempo
    std::clock_t t0 = std::clock();
    for (size_t i=0;i<ops.size();++i) {
        if (ops[i].tipo=='A') abb.insertar(ops[i].codigo);
        else abb.eliminar(ops[i].codigo);
    }
    std::clock_t t1 = std::clock();
    double tiempoABB = (t1-t0)/double(CLOCKS_PER_SEC);

    // Procesar en AVL y medir tiempo
    t0 = std::clock();
    for (size_t i=0;i<ops.size();++i) {
        if (ops[i].tipo=='A') avl.insertar(ops[i].codigo);
        else avl.eliminar(ops[i].codigo);
    }
    t1 = std::clock();
    double tiempoAVL = (t1-t0)/double(CLOCKS_PER_SEC);

    // Procesar en RN (std::set) y medir tiempo
    t0 = std::clock();
    for (size_t i=0;i<ops.size();++i) {
        if (ops[i].tipo=='A') rn.insert(ops[i].codigo);
        else rn.erase(ops[i].codigo);
    }
    t1 = std::clock();
    double tiempoRN = (t1-t0)/double(CLOCKS_PER_SEC);

    // Comparar recorridos inorden
    std::list<int> inABB, inAVL, inRN;
    abb.inorden(inABB);
    avl.inorden(inAVL);
    listaDesdeSet(rn, inRN);

    // Mostrar resultados
    std::cout << "Tiempo ABB: " << tiempoABB << " s\n";
    std::cout << "Tiempo AVL: " << tiempoAVL << " s\n";
    std::cout << "Tiempo RN (std::set): " << tiempoRN << " s\n";

    std::cout << "ABB == RN: " << (listasIguales(inABB,inRN)?"IGUALES":"DIFERENTES") << "\n";
    std::cout << "AVL == RN: " << (listasIguales(inAVL,inRN)?"IGUALES":"DIFERENTES") << "\n";

    return 0;
}
