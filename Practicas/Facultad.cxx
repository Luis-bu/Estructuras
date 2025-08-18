#include "Facultad.h"
#include <stdexcept>

using namespace std;

Facultad::Facultad(string nombre) : nombre(nombre) {}

string Facultad::obtenerNombre() {
    return nombre;
}

list<Carrera> Facultad::obtenerCarreras() {
    return carreras;
}

void Facultad::fijarNombre(string nom) {
    nombre = nom;
}

void Facultad::fijarCarreras(list<Carrera> lista) {
    carreras = lista;
}