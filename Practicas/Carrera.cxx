#include "Carrera.h"
#include <stdexcept>

using namespace std;

Carrera::Carrera(string nombre, int estudiantes)
{
    this->nombre = nombre;
    this->estudiantes = estudiantes;
}

string Carrera::obtenerNombre()
{
    return nombre;
}

int Carrera::obtenerEstudiantes()
{
    return estudiantes;
}

void Carrera::fijarNombre(string nom)
{
    nombre = nom;
}

void Carrera::agregarEstudiante()
{
    estudiantes++;
}

void Carrera::eliminarEstudiante()
{
    if (estudiantes > 0)
    {
        estudiantes--;
    }
    else
    {
        throw invalid_argument("No hay estudiantes para eliminar.");
    }
}
