#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

// Definición de la estructura Comando
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
    ManejadorComandos() {
        comandos.push_back(Comando{"ayuda", 0, "ayuda: Lista todos los comandos disponibles.\nayuda <comando>: Muestra la ayuda para un comando específico."});
        comandos.push_back(Comando{"ayuda_comando", 1, ""});
        comandos.push_back(Comando{"cargar", 1, "cargar <nombre_archivo>: Carga un archivo FASTA en memoria."});
        comandos.push_back(Comando{"listar_secuencias", 0, "listar_secuencias: Muestra las secuencias cargadas en memoria."});
        comandos.push_back(Comando{"histograma", 1, "histograma <descripcion_secuencia>: Muestra el histograma de frecuencias de una secuencia."});
        comandos.push_back(Comando{"es_subsecuencia", 1, "es_subsecuencia <subsecuencia>: Verifica si una subsecuencia existe en las secuencias cargadas."});
        comandos.push_back(Comando{"enmascarar", 1, "enmascarar <subsecuencia>: Enmascara una subsecuencia reemplazando sus bases por 'X'."});
        comandos.push_back(Comando{"guardar", 1, "guardar <nombre_archivo>: Guarda las secuencias en un archivo FASTA."});
        comandos.push_back(Comando{"codificar", 1, "codificar <nombre_archivo.fabin>: Codifica las secuencias usando Huffman y guarda en un archivo binario."});
        comandos.push_back(Comando{"decodificar", 1, "decodificar <nombre_archivo.fabin>: Decodifica un archivo binario y carga las secuencias en memoria."});
        comandos.push_back(Comando{"ruta_mas_corta", 5, "ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>: Encuentra la ruta más corta entre dos bases."});
        comandos.push_back(Comando{"base_remota", 3, "base_remota <descripcion_secuencia> <i> <j>: Encuentra la base más lejana del mismo tipo."});
        comandos.push_back(Comando{"salir", 0, "salir: Termina la ejecución del programa."});
    }

    // Verifica si una cadena es un entero válido
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