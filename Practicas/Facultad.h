#ifndef FACULTAD_H
#define FACULTAD_H
#include <iostream>
#include <string>
#include <list>
#include "Carrera.h"

using namespace std;

class Facultad{
    private:
    string nombre;
    list<Carrera> carreras;

    public:
    string obtenerNombre();
    list<Carrera> obtenerCarreras();
    void fijarNombre(string nom);
    void fijarCarreras(list<Carrera> lista);
};


#endif