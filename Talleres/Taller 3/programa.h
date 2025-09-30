#ifndef PROGRAMA_H
#define PROGRAMA_H

#include <string>
#include <vector>
#include <list>
#include <set>    
#include "abb.h"
#include "avl.h"

class Programa {
public:
    Programa();
    ~Programa();

    void configurarEntrada(const std::string& ruta);
    int leerOperaciones();
    void ejecutar();
    void medirTiempos();
    void recorrerInorden();
    bool compararEstructuras();
    void mostrarResultados();
    void limpiar();

private:
    struct Operacion {
        char tipo;   // 'A' = Agregar, 'E' = Eliminar
        int codigo;
    };

    ABB abb;
    AVL avl;
    std::set<int> rn;

    std::string rutaEntrada;
    std::vector<Operacion> operaciones;

    std::list<int> inordenABB;
    std::list<int> inordenAVL;
    std::list<int> inordenRN;

    double tiempoABB;
    double tiempoAVL;
    double tiempoRN;
};

#endif
