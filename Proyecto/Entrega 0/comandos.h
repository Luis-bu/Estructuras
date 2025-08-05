#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream> 

using namespace std; 

// Definimos la estructura comando
struct Comando {
    string nombre;
    int numParametros;
    string textoAyuda;
};

// Usamos clase ManejadorComandos para gestionar los comandos
class ManejadorComandos {
private:
    map<string, Comando> comandos;

public:
    ManejadorComandos() {
        // Inicializar comandos con nombre, número de parámetros y texto de ayuda
        comandos["ayuda"] = {"ayuda", 0, "ayuda: Lista todos los comandos disponibles.\nayuda <comando>: Muestra la ayuda para un comando específico."};
        comandos["ayuda_comando"] = {"ayuda_comando", 1, ""};
        comandos["cargar"] = {"cargar", 1, "cargar <nombre_archivo>: Carga un archivo FASTA en memoria."};
        comandos["listar_secuencias"] = {"listar_secuencias", 0, "listar_secuencias: Muestra las secuencias cargadas en memoria."};
        comandos["histograma"] = {"histograma", 1, "histograma <descripcion_secuencia>: Muestra el histograma de frecuencias de una secuencia."};
        comandos["es_subsecuencia"] = {"es_subsecuencia", 1, "es_subsecuencia <subsecuencia>: Verifica si una subsecuencia existe en las secuencias cargadas."};
        comandos["enmascarar"] = {"enmascarar", 1, "enmascarar <subsecuencia>: Enmascara una subsecuencia reemplazando sus bases por 'X'."};
        comandos["guardar"] = {"guardar", 1, "guardar <nombre_archivo>: Guarda las secuencias en un archivo FASTA."};
        comandos["codificar"] = {"codificar", 1, "codificar <nombre_archivo.fabin>: Codifica las secuencias usando Huffman y guarda en un archivo binario."};
        comandos["decodificar"] = {"decodificar", 1, "decodificar <nombre_archivo.fabin>: Decodifica un archivo binario y carga las secuencias en memoria."};
        comandos["ruta_mas_corta"] = {"ruta_mas_corta", 5, "ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>: Encuentra la ruta más corta entre dos bases."};
        comandos["base_remota"] = {"base_remota", 3, "base_remota <descripcion_secuencia> <i> <j>: Encuentra la base más lejana del mismo tipo."};
        comandos["salir"] = {"salir", 0, "salir: Termina la ejecución del programa."};
    }

    // Usamos una función para verificar si es un entero la cadena
    bool esEntero(const string& str) {
        istringstream iss(str);
        int n;
        return (iss >> n) && iss.eof();
    }

    // Validamos los comandos y parámetros
    bool validarComando(const string& cmd, const vector<string>& params) {
        if (cmd == "ayuda" && params.size() == 1) {
            return comandos.find("ayuda_comando") != comandos.end();
        }
        map<string, Comando>::const_iterator it = comandos.find(cmd); // Reemplazo de auto
        if (it == comandos.end()) {
            cout << "Comando inválido: " << cmd << endl;
            return false;
        }
        if (it->second.numParametros != params.size()) {
            cout << "Número incorrecto de parámetros para " << cmd << ". Formato: " 
                 << it->second.textoAyuda << endl;
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
        return true;
    }

    // Mostrar todos los comandos
    void mostrarAyuda() {
        cout << "Comandos disponibles:" << endl;
        for (map<string, Comando>::const_iterator par = comandos.begin(); par != comandos.end(); ++par) { // Reemplazo de auto
            if (par->first != "ayuda_comando") {
                cout << par->second.nombre << endl;
            }
        }
    }

    // Mostrar ayuda para un comando
    void mostrarAyudaComando(const string& cmd) {
        map<string, Comando>::const_iterator it = comandos.find(cmd); // Reemplazo de auto
        if (it != comandos.end() && it->first != "ayuda_comando") {
            cout << it->second.textoAyuda << endl;
        } else {
            cout << "No se encontró ayuda para el comando: " << cmd << endl;
        }
    }
};

#endif