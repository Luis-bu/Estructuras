#ifndef PUNTO_H
#define PUNTO_H

#include <cmath>

struct Punto {
    double x, y, z;

    // Constructor
    Punto(double x_ = 0.0, double y_ = 0.0, double z_ = 0.0) : x(x_), y(y_), z(z_) {}

    // Distancia Euclidiana
    double distanciaEuclidiana(const Punto& otro) const {
        return std::sqrt(std::pow(x - otro.x, 2) + std::pow(y - otro.y, 2) + std::pow(z - otro.z, 2));
    }

    // Distancia de Manhattan
    double distanciaManhattan(const Punto& otro) const {
        return std::abs(x - otro.x) + std::abs(y - otro.y) + std::abs(z - otro.z);
    }
};

#endif