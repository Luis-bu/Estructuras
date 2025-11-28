// GrafoSecuencia.cxx
#include "GrafoSecuencia.h"
#include <iostream>
#include <cmath>
#include <queue>
#include <sstream>

std::string GrafoSecuencia::clave(int f, int c) const {
    return std::to_string(f) + "," + std::to_string(c);
}

GrafoSecuencia::GrafoSecuencia(const std::vector<std::string>& lineasSec, int ancho)
    : lineas(lineasSec), filas(lineasSec.size()), columnas(ancho) {

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas && j < (int)lineas[i].length(); ++j) {
            char base = lineas[i][j];
            NodoGrafo* nodo = new NodoGrafo(i, j, base);
            nodos[clave(i, j)] = nodo;
        }
    }
}

GrafoSecuencia::~GrafoSecuencia() {
    for (auto& par : nodos) {
        delete par.second;
    }
}

bool GrafoSecuencia::rutaMasCorta(int fi, int fj, int ti, int tj,
                                  std::vector<std::string>& camino,
                                  double& costoTotal) const {
    if (fi < 0 || fi >= filas || fj < 0 || fj >= columnas ||
        ti < 0 || ti >= filas || tj < 0 || tj >= columnas) {
        return false;
    }

    // Reset distancias
    for (auto& par : nodos) {
        par.second->setDistancia(1e18);
        par.second->setPadre(nullptr);
    }

    auto cmp = [](NodoGrafo mayor;
    std::priority_queue<NodoGrafo*, std::vector<NodoGrafo*>, decltype(cmp)> pq(cmp);

    std::string inicio = clave(fi, fj);
    nodos.at(inicio)->setDistancia(0);
    pq.push(nodos.at(inicio));

    int di[] = {-1, 0, 1, 0};
    int dj[] = {0, 1, 0, -1};

    while (!pq.empty()) {
        NodoGrafo* actual = pq.top(); pq.pop();
        int i = actual->getFila();
        int j = actual->getColumna();

        if (i == ti && j == tj) break;

        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];
            if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
                char a = actual->getBase();
                char b = lineas[ni][nj];
                double peso = 1.0 / (1.0 + std::abs((int)a - (int)b));

                NodoGrafo* vecino = nodos.at(clave(ni, nj));
                double nuevaDist = actual->getDistancia() + peso;

                if (nuevaDist < vecino->getDistancia()) {
                    vecino->setDistancia(nuevaDist);
                    vecino->setPadre(actual);
                    pq.push(vecino);
                }
            }
        }
    }

    NodoGrafo* destino = nodos.at(clave(ti, tj));
    costoTotal = destino->getDistancia();
    if (costoTotal >= 1e18) return false;

    // Reconstruir camino
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

    char baseObjetivo = lineas[fi][fj];
    double maxDist = -1;
    int mejorF = -1, mejorC = -1;

    // Probar Dijkstra desde (fi,fj) hacia TODAS las posiciones con la misma base
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas && j < (int)lineas[i].length(); ++j) {
            if (lineas[i][j] == baseObjetivo && !(i == fi && j == fj)) {
                std::vector<std::string> caminoTmp;
                double costoTmp;
                if (rutaMasCorta(fi, fj, i, j, caminoTmp, costoTmp)) {
                    if (costoTmp > maxDist) {
                        maxDist = costoTmp;
                        mejorF = i;
                        mejorC = j;
                    }
                }
            }
        }
    }

    if (maxDist < 0) return false; // no hay otra base igual

    destFila = mejorF;
    destCol = mejorC;
    costoMaximo = maxDist;
    return true;
}

void GrafoSecuencia::imprimirMatriz() const {
    for (const auto& linea : lineas) {
        std::cout << linea << std::endl;
    }
}