#include "manejadorcomandos.h"
#include "arbolhuffman.h"
#include "nodo.h"


#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstdint>

using std::cout;
using std::endl;
using std::ifstream;
using std::min;
using std::string;
using std::vector;

// Devuelve true si la cadena representa un entero válido.
bool ManejadorComandos::esEntero(const string& str) {
    std::istringstream iss(str);
    int n;
    return (iss >> n) && iss.eof();
}

// Devuelve el orden de las bases permitidas por la especificación.
vector<char> ManejadorComandos::getOrden() {
    return {'A','C','G','T','U','R','Y','K','M','S','W','B','D','H','V','N','X','-'};
}

// Busca un comando en la tabla de comandos.
bool ManejadorComandos::buscarComando(const string& cmd, Comando& comando) const {
    for (const auto& c : comandos) {
        if (c.nombre == cmd) {
            comando = c;
            return true;
        }
    }
    return false;
}

// Valida un comando y sus parámetros.
bool ManejadorComandos::validarComando(const string& cmd, const vector<string>& params) {
    Comando comando;
    if (cmd == "ayuda" && params.size() == 1) {
        return buscarComando("ayuda_comando", comando);
    }
    if (!buscarComando(cmd, comando)) {
        cout << "Comando inválido: " << cmd << endl;
        return false;
    }
    if (static_cast<int>(params.size()) != comando.numParametros) {
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

// Constructor: inicializa la lista de comandos. Cada entrada incluye nombre, número de parámetros y texto de ayuda con ejemplos.
ManejadorComandos::ManejadorComandos() {
    comandos.push_back({"ayuda", 0, "ayuda: Lista todos los comandos disponibles.\nayuda <comando>: Muestra la ayuda para un comando específico.\nEjemplo: ayuda cargar"});
    comandos.push_back({"ayuda_comando", 1, "ayuda_comando <comando>: Muestra la ayuda detallada de un comando.\nEjemplo: ayuda_comando cargar"});
    comandos.push_back({"cargar", 1, "cargar <nombre_archivo>: Carga un archivo FASTA en memoria.\nEjemplo: cargar secuencias.fasta"});
    comandos.push_back({"listar_secuencias", 0, "listar_secuencias: Muestra las secuencias cargadas en memoria.\nEjemplo: listar_secuencias"});
    comandos.push_back({"histograma", 1, "histograma <descripcion_secuencia>: Muestra el histograma de frecuencias de una secuencia.\nEjemplo: histograma secuencia1"});
    comandos.push_back({"es_subsecuencia", 1, "es_subsecuencia <subsecuencia>: Verifica si una subsecuencia existe en las secuencias cargadas.\nEjemplo: es_subsecuencia ATCG"});
    comandos.push_back({"enmascarar", 1, "enmascarar <subsecuencia>: Enmascara una subsecuencia reemplazando sus bases por 'X'.\nEjemplo: enmascarar ATCG"});
    comandos.push_back({"guardar", 1, "guardar <nombre_archivo>: Guarda las secuencias en un archivo FASTA.\nEjemplo: guardar resultado.fasta"});
    comandos.push_back({"codificar", 1, "codificar <nombre_archivo.fabin>: Codifica las secuencias usando Huffman y guarda en un archivo binario.\nEjemplo: codificar datos.fabin"});
    comandos.push_back({"decodificar", 1, "decodificar <nombre_archivo.fabin>: Decodifica un archivo binario y carga las secuencias en memoria.\nEjemplo: decodificar datos.fabin"});
    comandos.push_back({"ruta_mas_corta", 5, "ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>: Encuentra la ruta más corta entre dos bases.\nEjemplo: ruta_mas_corta secuencia1 0 0 5 5"});
    comandos.push_back({"base_remota", 3, "base_remota <descripcion_secuencia> <i> <j>: Encuentra la base más lejana del mismo tipo.\nEjemplo: base_remota secuencia1 2 3"});
    comandos.push_back({"salir", 0, "salir: Termina la ejecución del programa.\nEjemplo: salir"});
}

//Corección: "Sugeriría que al momento de estructurar el código, se pueda definir una función para cada comando a ejecutar, de forma que sea más fácil la lectura del código y el mantenimiento del mismo."
//Solución: Se ha implementado una función independiente para cada comando, mejorando la organización y claridad del código.
// Función que redirige a los métodos de cada comando tras la validación.
void ManejadorComandos::ejecutarComando(const string& cmd, const vector<string>& params) {
    if (!validarComando(cmd, params)) {
        return;
    }
    if (cmd == "ayuda") {
        mostrarAyuda();
    } else if (cmd == "ayuda_comando") {
        mostrarAyudaComando(params[0]);
    } else if (cmd == "cargar") {
        comandoCargar(params);
    } else if (cmd == "listar_secuencias") {
        comandoListarSecuencias();
    } else if (cmd == "histograma") {
        comandoHistograma(params);
    } else if (cmd == "es_subsecuencia") {
        comandoEsSubsecuencia(params);
    } else if (cmd == "enmascarar") {
        comandoEnmascarar(params);
    } else if (cmd == "guardar") {
        comandoGuardar(params);
    } else if (cmd == "codificar") {
        comandoCodificar(params);
    } else if (cmd == "decodificar") {
        comandoDecodificar(params);
    } else if (cmd == "ruta_mas_corta" || cmd == "base_remota") {
        // Informamos que estos comandos están reconocidos pero no implementados.
        cout << "Comando " << cmd << " válido, pero no implementado en nuestra entrega" << endl;
    } else if (cmd == "salir") {
    }
}

//CORRECIÓN: "El comando permite cargar secuencias que cuentan con símbolos no permitidos como bases."
//SOLUCIÓN: Se ha añadido una validación al cargar secuencias para asegurar que sólo se acepten bases permitidas. Si una secuencia contiene símbolos no válidos, se informa al usuario y no se carga esa secuencia.
// Carga las secuencias desde un archivo FASTA.
void ManejadorComandos::comandoCargar(const vector<string>& params) {
    const string& nombreArchivo = params[0];
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << nombreArchivo << " no se encuentra o no puede leerse." << endl;
        return;
    }
    vector<char> permitido = getOrden();
    auto esValida = [&](char c) {
        char up = std::toupper(static_cast<unsigned char>(c));
        return std::find(permitido.begin(), permitido.end(), up) != permitido.end();
    };
    secuencias.clear();
    string linea;
    string nombreSec = "";
    string bases = "";
    size_t lineLength = 0;
    bool secuenciaValida = true;
    while (std::getline(archivo, linea)) {
        if (!linea.empty() && linea[0] == '>') {
            if (!nombreSec.empty()) {
                if (secuenciaValida) {
                    secuencias.emplace_back(nombreSec, bases, lineLength);
                } else {
                    cout << "La secuencia '" << nombreSec << "' contiene símbolos no permitidos y no será cargada." << endl;
                }
            }
            nombreSec = linea.substr(1);
            bases.clear();
            lineLength = 0;
            secuenciaValida = true;
        } else {
            if (!linea.empty()) {
                if (lineLength == 0) {
                    lineLength = linea.length();
                }
                for (char c : linea) {
                    if (!esValida(c)) {
                        secuenciaValida = false;
                    }
                    bases.push_back(c);
                }
            }
        }
    }
    if (!nombreSec.empty()) {
        if (secuenciaValida) {
            secuencias.emplace_back(nombreSec, bases, lineLength);
        } else {
            cout << "La secuencia '" << nombreSec << "' contiene símbolos no permitidos y no será cargada." << endl;
        }
    }
    archivo.close();
    int n = static_cast<int>(secuencias.size());
    if (n == 0) {
        cout << nombreArchivo << " no contiene ninguna secuencia válida." << endl;
    } else {
        cout << n << " secuencia" << (n > 1 ? "s" : "")
             << " cargada" << (n > 1 ? "s" : "") << " correctamente desde "
             << nombreArchivo << "." << endl;
    }
}

// Lista las secuencias cargadas en memoria. Informa si no hay ninguna.
void ManejadorComandos::comandoListarSecuencias() {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
    } else {
        cout << "Hay " << secuencias.size() << " secuencia"
             << (secuencias.size() > 1 ? "s" : "") << " cargada"
             << (secuencias.size() > 1 ? "s" : "") << " en memoria:" << endl;
        for (const auto& seq : secuencias) {
            int basesCount = seq.contarBases();
            cout << "Secuencia " << seq.getNombre() << " contiene "
                 << (seq.getBases().find('-') != string::npos ? "al menos " : "")
                 << basesCount << " base" << (basesCount != 1 ? "s" : "") << "." << endl;
        }
    }
}

//CORRECIÓN: "Como sugerencia, no incluir las bases que tengan conteo igual a 0."
//SOLUCIÓN: Se ha modificado la función del comando histograma para que sólo muestre las bases con conteo mayor a 0.
// Muestra el histograma de una secuencia indicada por su nombre.
void ManejadorComandos::comandoHistograma(const vector<string>& params) {
    const string& descripcion = params[0];
    auto it = std::find_if(secuencias.begin(), secuencias.end(), [&](const Secuencia& s) {
        return s.getNombre() == descripcion;
    });
    if (it == secuencias.end()) {
        cout << "Secuencia inválida." << endl;
        return;
    }
    vector<char> orden = getOrden();
    const string& bases = it->getBases();
    for (char base : orden) {
        int freq = 0;
        for (char b : bases) {
            if (b == base) {
                freq++;
            }
        }
        if (freq > 0) {
            cout << base << " : " << freq << endl;
        }
    }
}

// Verifica la existencia de una subsecuencia en las secuencias cargadas y
// reporta cuántas veces se repite en total.
void ManejadorComandos::comandoEsSubsecuencia(const vector<string>& params) {
    const string& subseq = params[0];
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    int conteo = 0;
    for (const auto& seq : secuencias) {
        conteo += seq.buscarSubsecuencia(subseq);
    }
    if (conteo == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada se repite " << conteo << " vez" << (conteo != 1 ? "es" : "") << " dentro de las secuencias cargadas en memoria." << endl;
    }
}

// Enmascara todas las ocurrencias de una subsecuencia reemplazando sus bases por 'X'.
void ManejadorComandos::comandoEnmascarar(const vector<string>& params) {
    const string& sub = params[0];
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    int totalEnmascaradas = 0;
    for (auto& seq : secuencias) {
        int ocurrencias = seq.buscarSubsecuencia(sub);
        if (ocurrencias > 0) {
            seq.enmascararSubsecuencia(sub);
            totalEnmascaradas += ocurrencias;
        }
    }
    if (totalEnmascaradas == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada." << endl;
    } else {
        cout << totalEnmascaradas << " subsecuencia" << (totalEnmascaradas != 1 ? "s" : "")
             << " han sido enmascarada" << (totalEnmascaradas != 1 ? "s" : "")
             << " dentro de las secuencias cargadas en memoria." << endl;
    }
}

// Guarda las secuencias cargadas en un archivo FASTA.
void ManejadorComandos::comandoGuardar(const vector<string>& params) {
    const string& nombreArchivo = params[0];
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    std::ofstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "Error guardando en " << nombreArchivo << "." << endl;
        return;
    }
    for (const auto& seq : secuencias) {
        archivo << '>' << seq.getNombre() << endl;
        const string& bases = seq.getBases();
        size_t lineLength = seq.getLineLength();
        for (size_t j = 0; j < bases.length(); j += lineLength) {
            size_t length = std::min(lineLength, bases.length() - j);
            archivo << bases.substr(j, length) << endl;
        }
    }
    archivo.close();
    cout << "Las secuencias han sido guardadas en " << nombreArchivo << "." << endl;
}

// Muestra la lista de nombres de comandos disponibles.
void ManejadorComandos::mostrarAyuda() {
    cout << "Comandos disponibles:" << endl;
    for (const auto& c : comandos) {
        if (c.nombre != "ayuda_comando") {
            cout << c.nombre << endl;
        }
    }
}

// Muestra el texto de ayuda de un comando específico. Si el comando no se encuentra, informa al usuario.
void ManejadorComandos::mostrarAyudaComando(const string& cmd) {
    Comando comando;
    if (buscarComando(cmd, comando) && cmd != "ayuda_comando") {
        cout << comando.textoAyuda << endl;
    } else {
        cout << "No se encontró ayuda para el comando: " << cmd << endl;
    }
}

// Función que codifica las secuencias cargadas usando Huffman y las guarda en un archivo binario.
void ManejadorComandos::comandoCodificar(const vector<string>& params) {
    const string& nombreArchivo = params[0];
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    // calcular frecuencias
    std::unordered_map<char, unsigned long long> frec;
    for (const auto& seq : secuencias) {
        const string& b = seq.getBases();
        for (char c : b) frec[c]++;
    }
    // construir árbol de Huffman con el TAD
    ArbolHuffman arbol(frec);
    const auto& codes = arbol.obtenerCodigos();
    // abrir archivo
    std::ofstream out(nombreArchivo.c_str(), std::ios::binary);
    if (!out) {
        cout << "No se pueden guardar las secuencias cargadas en " << nombreArchivo << "." << endl;
        return;
    }
    // escribir número de símbolos y pares símbolo-frecuencia
    uint16_t n = static_cast<uint16_t>(frec.size());
    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (const auto& kv : frec) {
        char c = kv.first;
        unsigned long long f = kv.second;
        out.write(&c, sizeof(char));
        out.write(reinterpret_cast<const char*>(&f), sizeof(unsigned long long));
    }
    // escribir número de secuencias
    uint32_t ns = static_cast<uint32_t>(secuencias.size());
    out.write(reinterpret_cast<const char*>(&ns), sizeof(ns));
    // escribir nombres
    for (const auto& seq : secuencias) {
        const string& nombre = seq.getNombre();
        uint16_t li = static_cast<uint16_t>(nombre.size());
        out.write(reinterpret_cast<const char*>(&li), sizeof(li));
        out.write(nombre.c_str(), nombre.size());
    }
    // escribir cada secuencia: longitud, justificación y código binario
    for (const auto& seq : secuencias) {
        const string& b = seq.getBases();
        uint64_t wi = static_cast<uint64_t>(b.size());
        uint16_t xi = static_cast<uint16_t>(seq.getLineLength());
        out.write(reinterpret_cast<const char*>(&wi), sizeof(wi));
        out.write(reinterpret_cast<const char*>(&xi), sizeof(xi));
        // construir cadena de bits
        std::string bits;
        bits.reserve(b.size() * 4);
        for (char ch : b) bits += codes.at(ch);
        size_t byteCount = (bits.size() + 7) / 8;
        std::vector<unsigned char> buffer(byteCount, 0);
        for (size_t i = 0; i < bits.size(); ++i) {
            if (bits[i] == '1') {
                buffer[i / 8] |= (1 << (7 - (i % 8)));
            }
        }
        out.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    }
    out.close();
    cout << "Secuencias codificadas y almacenadas en " << nombreArchivo <<endl;
}

// Función que decodifica un archivo binario con secuencias codificadas usando Huffman y las carga en memoria.
void ManejadorComandos::comandoDecodificar(const vector<string>& params) {
    const string& nombreArchivo = params[0];
    std::ifstream in(nombreArchivo.c_str(), std::ios::binary);
    if (!in) {
        cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
        return;
    }
    secuencias.clear();
    uint16_t n;
    if (!in.read(reinterpret_cast<char*>(&n), sizeof(n))) {
        cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
        return;
    }
    // leer pares símbolo-frecuencia
    std::unordered_map<char, unsigned long long> frec;
    for (uint16_t i = 0; i < n; ++i) {
        char c;
        unsigned long long f;
        if (!in.read(&c, sizeof(char)) || !in.read(reinterpret_cast<char*>(&f), sizeof(unsigned long long))) {
            cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
            return;
        }
        frec[c] = f;
    }
    // construir árbol para decodificar
    ArbolHuffman arbol(frec);
    Nodo* root = arbol.obtenerRaiz();
    uint32_t ns;
    if (!in.read(reinterpret_cast<char*>(&ns), sizeof(ns))) {
        cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
        return;
    }
    // leer nombres
    std::vector<string> nombres;
    nombres.reserve(ns);
    for (uint32_t i = 0; i < ns; ++i) {
        uint16_t li;
        if (!in.read(reinterpret_cast<char*>(&li), sizeof(li))) {
            cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
            return;
        }
        string nombre(li, '\0');
        if (!in.read(&nombre[0], li)) {
            cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
            return;
        }
        nombres.push_back(nombre);
    }
    unsigned char currentByte = 0;
    int bitsLeft = 0;
    auto readBit = [&]() -> int {
        if (bitsLeft == 0) {
            if (!in.read(reinterpret_cast<char*>(&currentByte), 1)) return -1;
            bitsLeft = 8;
        }
        bitsLeft--;
        return (currentByte >> bitsLeft) & 1;
    };
    // leer cada secuencia
    for (uint32_t idx = 0; idx < ns; ++idx) {
        uint64_t wi;
        uint16_t xi;
        if (!in.read(reinterpret_cast<char*>(&wi), sizeof(wi)) || !in.read(reinterpret_cast<char*>(&xi), sizeof(xi))) {
            cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
            return;
        }
        string decoded;
        decoded.reserve(static_cast<size_t>(wi));
        for (uint64_t cnt = 0; cnt < wi; ++cnt) {
            Nodo* node = root;
            while (node->left || node->right) {
                int bit = readBit();
                if (bit < 0) {
                    cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
                    return;
                }
                node = (bit == 0) ? node->left : node->right;
            }
            decoded.push_back(node->c);
        }
        bitsLeft = 0;
        secuencias.emplace_back(nombres[idx], decoded, static_cast<size_t>(xi));
    }
    in.close();
    cout << "Secuencias decodificadas desde " << nombreArchivo << " y cargadas en memoria." << endl;
}

