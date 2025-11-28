// GrafoSecuencia.cxx
#include "GrafoSecuencia.h"
#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iomanip>

std::string GrafoSecuencia::clave(int f, int c) const {
    return std::to_string(f) + "," + std::to_string(c);
}

GrafoSecuencia::GrafoSecuencia(const std::vector<std::string>& lineasSec, int ancho)
    : lineas(lineasSec), filas(static_cast<int>(lineasSec.size())), columnas(ancho) {

    // CREAMOS TODOS los nodos (incluso si la línea es corta)
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            char base = ' ';  // por defecto espacio si la línea es corta
            if (j < static_cast<int>(lineas[i].length())) {
                base = lineas[i][j];
            }
            NodoGrafo* nodo = new NodoGrafo(i, j, base);
            nodos[clave(i, j)] = nodo;
        }
    }
}

GrafoSecuencia::~GrafoSecuencia() {
    for (auto& par : nodos) {
        delete par.second;
    }
    nodos.clear();
}

bool GrafoSecuencia::rutaMasCorta(int fi, int fj, int ti, int tj,
                                  std::vector<std::string>& camino,
                                  double& costoTotal) const {
    // Validar límites
    if (fi < 0 || fi >= filas || fj < 0 || fj >= columnas ||
        ti < 0 || ti >= filas || tj < 0 || tj >= columnas) {
        return false;
    }

    // Resetear nodos
    for (auto& par : nodos) {
        par.second->setDistancia(1e18);
        par.second->setPadre(nullptr);
    }

    struct Comparador {
        bool operator()(NodoGrafo* a, NodoGrafo* b) const {
            return a->getDistancia() > b->getDistancia();
        }
    };

    std::priority_queue<NodoGrafo*, std::vector<NodoGrafo*>, Comparador> pq;

    std::string claveInicio = clave(fi, fj);
    nodos.at(claveInicio)->setDistancia(0.0);
    pq.push(nodos.at(claveInicio));

    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};

    while (!pq.empty()) {
        NodoGrafo* actual = pq.top();
        pq.pop();

        int i = actual->getFila();
        int j = actual->getColumna();

        if (i == ti && j == tj) break;

        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];

            if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
                char a = actual->getBase();

                // ACCESO SEGURO a la base del vecino
                char b = ' ';
                if (nj < static_cast<int>(lineas[ni].length())) {
                    b = lineas[ni][nj];
                }

                double peso = 1.0 / (1.0 + std::abs(static_cast<int>(a) - static_cast<int>(b)));

                std::string claveVecino = clave(ni, nj);
                NodoGrafo* vecino = nodos.at(claveVecino);

                double nuevaDist = actual->getDistancia() + peso;
                if (nuevaDist < vecino->getDistancia()) {
                    vecino->setDistancia(nuevaDist);
                    vecino->setPadre(actual);
                    pq.push(vecino);
                }
            }
        }
    }

    std::string claveDestino = clave(ti, tj);
    NodoGrafo* destino = nodos.at(claveDestino);
    costoTotal = destino->getDistancia();

    if (costoTotal > 1e17) return false;

    camino.clear();
    NodoGrafo* nodo = destino;
    while (nodo != nullptr) {
        camino.push_back(nodo->toString());
        nodo = nodo->getPadre();
    }
    std::reverse(camino.begin(), camino.end());
    return true;
}

bool GrafoSecuencia::baseRemota(int fi, int fj,
                                int& destFila, int& destCol,
                                double& costoMaximo) const {
    if (fi < 0 || fi >= filas || fj < 0 || fj >= columnas) return false;

    // ACCESO SEGURO a la base origen
    char baseBuscada = ' ';
    if (fj < static_cast<int>(lineas[fi].length())) {
        baseBuscada = lineas[fi][fj];
    }

    double mejorCosto = -1.0;
    int mejorI = -1, mejorJ = -1;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i == fi && j == fj) continue;

            char actual = ' ';
            if (j < static_cast<int>(lineas[i].length())) {
                actual = lineas[i][j];
            }

            if (actual == baseBuscada) {
                std::vector<std::string> temp;
                double costoTmp = 0.0;
                if (rutaMasCorta(fi, fj, i, j, temp, costoTmp)) {
                    if (costoTmp > mejorCosto) {
                        mejorCosto = costoTmp;
                        mejorI = i;
                        mejorJ = j;
                    }
                }
            }
        }
    }

    if (mejorCosto < 0) return false;

    destFila = mejorI;
    destCol = mejorJ;
    costoMaximo = mejorCosto;
    return true;
}