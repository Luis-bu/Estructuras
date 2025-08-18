#ifndef CARRERA_H
#define CARRERA_H
#include <iostream>
#include <string>

using namespace std;

class Carrera
{
    private:
    string nombre; 
    int estudiantes;

    public:

    Carrera(string nombre, int estudiantes);
    string obtenerNombre();
    int obtenerEstudiantes();
    void fijarNombre(string nom);
    void agregarEstudiante();
    void eliminarEstudiante();
};
#endif
