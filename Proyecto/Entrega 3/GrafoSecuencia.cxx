// GrafoSecuencia.cxx
#include "GrafoSecuencia.h"
#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>     // std::reverse
#include <sstream>
#include <iomanip>

std::string GrafoSecuencia::clave(int f, int c) const {
    return std::to_string(f) + "," + std::to_string(c);
}

GrafoSecuencia::GrafoSecuencia(const std::vector<std::string>& lineasSec, int ancho)
    : lineas(lineasSec), filas(static_cast<int>(lineasSec.size())), columnas(ancho) {

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas && j < static_cast<int>(lineas[i].size()); ++j) {
            char base = lineas[i][j];
            NodoGrafo* nodo = new NodoGrafo(i, j, base);
            nodos[clave(i, j)] = nodo;
        }
    }
}

GrafoSecuencia::~GrafoSecuencia() {
    for (std::unordered_map<std::string, NodoGrafo*>::iterator it = nodos.begin(); it != nodos.end(); ++it) {
        delete it->second;
    }
    nodos.clear();
}

bool GrafoSecuencia::rutaMasCorta(int fi, int fj, int ti, int tj,
                                  std::vector<std::string>& camino,
                                  double& costoTotal) const {
    if (fi < 0 || fi >= filas || fj < 0 || fj >= columnas ||
        ti < 0 || ti >= filas || tj < 0 || tj >= columnas) {
        return false;
    }

    // Resetear todos los nodos
    for (std::unordered_map<std::string, NodoGrafo*>::const_iterator it = nodos.begin(); it != nodos.end(); ++it) {
        it->second->setDistancia(1e18);
        it->second->setPadre(nullptr);
    }

    // Comparador correcto para priority_queue (menor distancia primero)
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

        if (i == ti && j == tj) break;  // ya llegamos

        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];

            if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
                char a = actual->getBase();
                char b = lineas[ni][nj];
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

    if (costoTotal > 1e17) return false;  // no hay camino

    // Reconstruir camino
    camino.clear();
    NodoGrafo* actual = destino;
    while (actual != nullptr) {
        camino.push_back(actual->toString());
        actual = actual->getPadre();
    }
    std::reverse(camino.begin(), camino.end());

    return true;
}

bool GrafoSecuencia::baseRemota(int fi, int fj,
                                int& destFila, int& destCol,
                                double& costoMaximo) const {
    if (fi < 0 || fi >= filas || fj < 0 || fj >= columnas) return false;

    char baseBuscada = lineas[fi][fj];
    double mejorCosto = -1.0;
    int mejorI = -1, mejorJ = -1;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas && j < static_cast<int>(lineas[i].size()); ++j) {
            if (lineas[i][j] == baseBuscada && !(i == fi && j == fj)) {
                std::vector<std::string> tempCaminoTmp;
                double costoTmp = 0.0;
                if (rutaMasCorta(fi, fj, i, j, tempCaminoTmp, costoTmp)) {
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