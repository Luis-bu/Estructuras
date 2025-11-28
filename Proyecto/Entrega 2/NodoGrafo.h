// NodoGrafo.h
#ifndef NODOGRAFO_H
#define NODOGRAFO_H

#include <string>

class NodoGrafo {
private:
    int fila;
    int columna;
    char base;           // 'A', 'C', 'G', 'T', '-', 'X', etc.
    double distanciaMin; // para Dijkstra
    NodoGrafo* padre;    // para reconstruir camino

public:
    // Constructor
    NodoGrafo(int f = 0, int c = 0, char b = ' ');

    // Getters
    int getFila() const;
    int getColumna() const;
    char getBase() const;
    double getDistancia() const;
    NodoGrafo* getPadre() const;

    // Setters
    void setDistancia(double d);
    void setPadre(NodoGrafo* p);

    // Para usar en priority_queue (menor distancia primero)
    bool operator>(const NodoGrafo& otro) const;

    // Representación legible para imprimir ruta
    std::string toString() const;
};

#endif