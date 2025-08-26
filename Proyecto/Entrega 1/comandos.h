#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

// Estructura para representar un comando
struct Comando {
    string nombre;
    int numParametros;
    string textoAyuda;
};

// Clase para gestionar los comandos de nuestro programa
class ManejadorComandos {
private:
    vector<Comando> comandos;
    vector<pair<string, string> > secuencias; // Nombre y secuencia

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

    // Carga una secuencia desde una línea
    string cargarSecuencia(ifstream& archivo) {
        string secuencia = "";
        string linea;
        while (getline(archivo, linea) && linea[0] != '>') {
            secuencia += linea;
        }
        return secuencia;
    }

    // Cuenta bases, ignorando '-'
    int contarBases(const string& secuencia) {
        int count = 0;
        for (unsigned int i = 0; i < secuencia.length(); ++i) {
            if (secuencia[i] != '-') count++;
        }
        return count;
    }

    // Orden de códigos
    vector<char> getOrden() {
        vector<char> orden;
        orden.push_back('A');
        orden.push_back('C');
        orden.push_back('G');
        orden.push_back('T');
        orden.push_back('U');
        orden.push_back('R');
        orden.push_back('Y');
        orden.push_back('K');
        orden.push_back('M');
        orden.push_back('S');
        orden.push_back('W');
        orden.push_back('B');
        orden.push_back('D');
        orden.push_back('H');
        orden.push_back('V');
        orden.push_back('N');
        orden.push_back('X');
        orden.push_back('-');
        return orden;
    }

public:

    // Constructor que define los comandos disponibles
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

    // Validamos los comandos y parámetros
    bool validarComando(const string& cmd, const vector<string>& params) {
        Comando comando;
        if (cmd == "ayuda" && params.size() == 1) {
            return buscarComando("ayuda_comando", comando);
        }
        // Verificamos si el comando existe
        if (!buscarComando(cmd, comando)) {
            cout << "Comando inválido: " << cmd << endl;
            return false;
        }
        // Verificamos el número de parámetros
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
        return true;
    }

    // Ejecutar los comandos
    void ejecutarComando(const string& cmd, const vector<string>& params) {
        // Cargar secuencias desde un archivo
                if (cmd == "cargar" && params.size() == 1) {
            ifstream archivo(params[0].c_str());
            if (!archivo) {
                cout << params[0] << " no se encuentra o no puede leerse." << endl;
                return;
            }
            secuencias.clear(); // Sobrescribe datos previos
            string linea;
            string nombre = "";
            string secuencia = "";
            while (getline(archivo, linea)) {
                if (linea[0] == '>') {
                    if (!nombre.empty()) {
                        secuencias.push_back(make_pair(nombre, secuencia));
                    }
                    nombre = linea.substr(1);
                    secuencia = "";
                } else {
                    secuencia += linea;
                }
            }
            if (!nombre.empty()) {
                secuencias.push_back(make_pair(nombre, secuencia));
            }
            archivo.close();
            int n = static_cast<int>(secuencias.size());
            if (n == 0) {
                cout << params[0] << " no contiene ninguna secuencia." << endl;
            } else {
                cout << n << " secuencia" << (n > 1 ? "s" : "") << " cargada" << (n > 1 ? "s" : "") << " correctamente desde " << params[0] << "." << endl;
            }
        
            // Mostrar las secuencias cargadas
        } else if (cmd == "listar_secuencias" && params.empty()) {
            if (secuencias.empty()) {
                cout << "No hay secuencias cargadas en memoria." << endl;
            } else {
                cout << "Hay " << secuencias.size() << " secuencia" << (secuencias.size() > 1 ? "s" : "") << " cargada" << (secuencias.size() > 1 ? "s" : "") << " en memoria:" << endl;
                for (unsigned int i = 0; i < secuencias.size(); ++i) {
                    int bases = contarBases(secuencias[i].second);
                    cout << "Secuencia " << secuencias[i].first << " contiene " << (secuencias[i].second.find('-') != string::npos ? "al menos " : "") << bases << " base" << (bases > 1 ? "s" : "") << "." << endl;
                }
            }
            // Mostrar el histograma
        } else if (cmd == "histograma" && params.size() == 1) {
            bool found = false;
            for (unsigned int i = 0; i < secuencias.size(); ++i) {
                if (secuencias[i].first == params[0]) {
                    found = true;
                    vector<char> orden = getOrden();
                    for (unsigned int j = 0; j < orden.size(); ++j) {
                        int freq = 0;
                        for (unsigned int k = 0; k < secuencias[i].second.length(); ++k) {
                            if (secuencias[i].second[k] == orden[j]) freq++;
                        }
                        cout << orden[j] << " : " << freq << endl;
                    }
                    break;
                }
            }
            if (!found) cout << "Secuencia inválida." << endl;
        } else if (cmd == "es_subsecuencia" && params.size() == 1) {
            if (secuencias.empty()) {
                cout << "No hay secuencias cargadas en memoria." << endl;
            } else {
                int count = 0;
                string sub = params[0];
                for (unsigned int i = 0; i < secuencias.size(); ++i) {
                    size_t pos = 0;
                    while ((pos = secuencias[i].second.find(sub, pos)) != string::npos) {
                        count++;
                        pos++;
                    }
                }
                if (count == 0) {
                    cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
                } else {
                    cout << "La subsecuencia dada se repite " << count << " veces dentro de las secuencias cargadas en memoria." << endl;
                }
            }
            // Enmascarar subsecuencia
        } else if (cmd == "enmascarar" && params.size() == 1) {
            if (secuencias.empty()) {
                cout << "No hay secuencias cargadas en memoria." << endl;
            } else {
                int count = 0;
                string sub = params[0];
                for (unsigned int i = 0; i < secuencias.size(); ++i) {
                    size_t pos = 0;
                    while ((pos = secuencias[i].second.find(sub, pos)) != string::npos) {
                        secuencias[i].second.replace(pos, sub.length(), string(sub.length(), 'X'));
                        count++;
                        pos += sub.length();
                    }
                }
                if (count == 0) {
                    cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada." << endl;
                } else {
                    cout << count << " subsecuencia" << (count > 1 ? "s" : "") << " han sido enmascarada" << (count > 1 ? "s" : "") << " dentro de las secuencias cargadas en memoria." << endl;
                }
            }
            // Guardar secuencias en un archivo
        } else if (cmd == "guardar" && params.size() == 1) {
            if (secuencias.empty()) {
                cout << "No hay secuencias cargadas en memoria." << endl;
            } else {
                ofstream archivo(params[0].c_str());
                if (!archivo) {
                    cout << "Error guardando en " << params[0] << "." << endl;
                } else {
                    for (unsigned int i = 0; i < secuencias.size(); ++i) {
                        archivo << ">" << secuencias[i].first << endl;
                        for (unsigned int j = 0; j < secuencias[i].second.length(); j += 70) {
                            archivo << secuencias[i].second.substr(j, 70) << endl;
                        }
                    }
                    archivo.close();
                    cout << "Las secuencias han sido guardadas en " << params[0] << "." << endl;
                }
            }
        }
        cout << "Procesamiento completado." << endl;
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