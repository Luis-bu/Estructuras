#ifndef PUNTO_H
#define PUNTO_H

#include <cmath>

using namespace std; 

struct Punto {
    double x, y, z;

    // Constructor
    Punto(double x_ = 0.0, double y_ = 0.0, double z_ = 0.0) : x(x_), y(y_), z(z_) {}

    // Es la distancia euclidiana
    double distanciaEuclidiana(const Punto& otro) const {
        return sqrt(pow(x - otro.x, 2) + pow(y - otro.y, 2) + pow(z - otro.z, 2));
    }

    // Es la distancia de Manhattan
    double distanciaManhattan(const Punto& otro) const {
        return abs(x - otro.x) + abs(y - otro.y) + abs(z - otro.z);
    }
};

#endif