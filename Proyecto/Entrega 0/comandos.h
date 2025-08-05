#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

//Definición de la estructura Comando
struct Comando {
    std::string nombre;
    int numParametros;
    std::string textoAyuda;
};

// Clase ManejadorComandos para gestionar los comandos del programa
class ManejadorComandos {
private:
    std::map<std::string, Comando> comandos;

public:
    ManejadorComandos() {
        // Inicializar comandos con nombre, número de parámetros y el texto de ayuda. Usamos este formato: (nombre, numParametros, textoAyuda)
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

// Aqui validamos los comandos y parámetros
   bool esEntero(const std::string& str) {
    try {
        std::stoi(str);
        return true;
    } catch (...) {
        return false;
    }
}

bool validarComando(const std::string& cmd, const std::vector<std::string>& params) {
    if (cmd == "ayuda" && params.size() == 1) {
        return comandos.find("ayuda_comando") != comandos.end();
    }
    auto it = comandos.find(cmd);
    if (it == comandos.end()) {
        std::cout << "Comando inválido: " << cmd << std::endl;
        return false;
    }
    if (it->second.numParametros != params.size()) {
        std::cout << "Número incorrecto de parámetros para " << cmd << ". Formato: " 
                  << it->second.textoAyuda << std::endl;
        return false;
    }
    if (cmd == "ruta_mas_corta" && params.size() == 5) {
        for (int i = 1; i <= 4; ++i) {
            if (!esEntero(params[i])) {
                std::cout << "Parámetro " << params[i] << " no es un entero válido." << std::endl;
                return false;
            }
        }
    } else if (cmd == "base_remota" && params.size() == 3) {
        for (int i = 1; i <= 2; ++i) {
            if (!esEntero(params[i])) {
                std::cout << "Parámetro " << params[i] << " no es un entero válido." << std::endl;
                return false;
            }
        }
    }
    std::cout << "Procesamiento completado." << std::endl;
    return true;
}

    // Mostrar todos los comandos
    void mostrarAyuda() {
        std::cout << "Comandos disponibles:" << std::endl;
        for (const auto& par : comandos) {
            if (par.first != "ayuda_comando") {
                std::cout << par.second.nombre << std::endl;
            }
        }
    }

    // Mostrar ayuda para un comando
    void mostrarAyudaComando(const std::string& cmd) {
        auto it = comandos.find(cmd);
        if (it != comandos.end() && it->first != "ayuda_comando") {
            std::cout << it->second.textoAyuda << std::endl;
        } else {
            std::cout << "No se encontró ayuda para el comando: " << cmd << std::endl;
        }
    }
};

#endif