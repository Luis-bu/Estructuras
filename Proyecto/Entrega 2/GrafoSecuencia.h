// GrafoSecuencia.h
#ifndef GRAFOSECUENCIA_H
#define GRAFOSECUENCIA_H

#include "NodoGrafo.h"
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <utility>

class GrafoSecuencia {
private:
    std::vector<std::string> lineas;  // líneas originales de la secuencia
    int filas;
    int columnas;                     // ancho original (lineLength de Secuencia)

    // Clave: "fila,columna" → puntero a nodo
    std::unordered_map<std::string, NodoGrafo*> nodos;

    std::string clave(int f, int c) const;

public:
    // Constructor a partir de una Secuencia ya cargada
    explicit GrafoSecuencia(const std::vector<std::string>& lineasSec, int ancho);

    ~GrafoSecuencia();

    // Dijkstra: ruta más corta entre dos posiciones
    bool rutaMasCorta(int fi, int fj, int ti, int tj,
                      std::vector<std::string>& camino,
                      double& costoTotal) const;

    // Encuentra la base más lejana con la MISMA letra que en (fi,fj)
    bool baseRemota(int fi, int fj,
                    int& destinoFila, int& destinoCol,
                    double& costoMaximo) const;

    // Para depuración: imprime matriz (opcional)
    void imprimirMatriz() const;
};

#endif