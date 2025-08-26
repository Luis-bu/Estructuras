#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

// Estructura para representar un comando
struct Comando {
    string nombre;
    int numParametros;
    string textoAyuda;
};

// Clase para gestionar los comandos del programa
class ManejadorComandos {
private:
    vector<Comando> comandos;

public:
    // Constructor que define los comandos disponibles
    // tienen estructura: nombre, número de parámetros un texto de ayuda (nuevo: añadimos un ejemplo para mejorar el comando)
    ManejadorComandos() {
        comandos.push_back(Comando{"ayuda", 0, "ayuda: Lista todos los comandos disponibles.\nayuda <comando>: Muestra la ayuda para un comando específico.\nEjemplo: ayuda cargar"});
        comandos.push_back(Comando{"ayuda_comando", 1, "ayuda_comando <comando>: Muestra la ayuda detallada de un comando.\nEjemplo: ayuda_comando cargar"});
        comandos.push_back(Comando{"cargar", 1, "cargar <nombre_archivo>: Carga un archivo FASTA en memoria.\nEjemplo: cargar secuencias.fasta"});
        comandos.push_back(Comando{"listar_secuencias", 0, "listar_secuencias: Muestra las secuencias cargadas en memoria.\nEjemplo: listar_secuencias"});
        comandos.push_back(Comando{"histograma", 1, "histograma <descripcion_secuencia>: Muestra el histograma de frecuencias de una secuencia.\nEjemplo: histograma secuencia1"});
        comandos.push_back(Comando{"es_subsecuencia", 1, "es_subsecuencia <subsecuencia>: Verifica si una subsecuencia existe en las secuencias cargadas.\nEjemplo: es_subsecuencia ATCG"});
        comandos.push_back(Comando{"enmascarar", 1, "enmascarar <subsecuencia>: Enmascara una subsecuencia reemplazando sus bases por 'X'.\nEjemplo: enmascarar ATCG"});
        comandos.push_back(Comando{"guardar", 1, "guardar <nombre_archivo>: Guarda las secuencias en un archivo FASTA.\nEjemplo: guardar resultado.fasta"});
        comandos.push_back(Comando{"codificar", 1, "codificar <nombre_archivo.fabin>: Codifica las secuencias usando Huffman y guarda en un archivo binario.\nEjemplo: codificar datos.fabin"});
        comandos.push_back(Comando{"decodificar", 1, "decodificar <nombre_archivo.fabin>: Decodifica un archivo binario y carga las secuencias en memoria.\nEjemplo: decodificar datos.fabin"});
        comandos.push_back(Comando{"ruta_mas_corta", 5, "ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>: Encuentra la ruta más corta entre dos bases.\nEjemplo: ruta_mas_corta secuencia1 0 0 5 5"});
        comandos.push_back(Comando{"base_remota", 3, "base_remota <descripcion_secuencia> <i> <j>: Encuentra la base más lejana del mismo tipo.\nEjemplo: base_remota secuencia1 2 3"});
        comandos.push_back(Comando{"salir", 0, "salir: Termina la ejecución del programa.\nEjemplo: salir"});
    }
//

    // Verifica si una cadena es un entero
    bool esEntero(const string& str) {
        istringstream iss(str);
        int n;
        return (iss >> n) && iss.eof();
    }

    // Busca un comando en el vector por su nombre
    bool buscarComando(const string& cmd, Comando& comando) const {
        for (unsigned int i = 0; i < comandos.size(); ++i) {
            if (comandos[i].nombre == cmd) {
                comando = comandos[i];
                return true;
            }
        }
        return false;
    }

    // Validamos los comandos y parámetros
    bool validarComando(const string& cmd, const vector<string>& params) {
        Comando comando;
        if (cmd == "ayuda" && params.size() == 1) {
            return buscarComando("ayuda_comando", comando);
        }
        if (!buscarComando(cmd, comando)) {
            cout << "Comando inválido: " << cmd << endl;
            return false;
        }
        if (comando.numParametros != static_cast<int>(params.size())) {
            cout << "Número incorrecto de parámetros para " << cmd << ". Formato: " 
                 << comando.textoAyuda << endl;
            return false;
        }
        if (cmd == "ruta_mas_corta" && params.size() == 5) {
            for (int i = 1; i <= 4; ++i) {
                if (!esEntero(params[i])) {
                    cout << "Parámetro " << params[i] << " no es un entero válido." << endl;
                    return false;
                }
            }
        } else if (cmd == "base_remota" && params.size() == 3) {
            for (int i = 1; i <= 2; ++i) {
                if (!esEntero(params[i])) {
                    cout << "Parámetro " << params[i] << " no es un entero válido." << endl;
                    return false;
                }
            }
        }
        cout << "Procesamiento completado." << endl;
        return true;
    }

    // Mostrar todos los comandos
    void mostrarAyuda() {
        cout << "Comandos disponibles:" << endl;
        for (unsigned int i = 0; i < comandos.size(); ++i) {
            if (comandos[i].nombre != "ayuda_comando") {
                cout << comandos[i].nombre << endl;
            }
        }
    }

    // Mostrar ayuda para un comando
    void mostrarAyudaComando(const string& cmd) {
        Comando comando;
        if (buscarComando(cmd, comando) && cmd != "ayuda_comando") {
            cout << comando.textoAyuda << endl;
        } else {
            cout << "No se encontró ayuda para el comando: " << cmd << endl;
        }
    }
};

#endif