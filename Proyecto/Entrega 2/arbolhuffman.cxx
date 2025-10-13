#include "arbolhuffman.h"
#include "nodo.h"
#include <queue>

using std::priority_queue;
using std::string;

// Comparamos para ordenar los nodos por frecuencia
struct CompareHuff {
    bool operator()(Nodo* a, Nodo* b) const {
        if (a->freq == b->freq) return a->c > b->c;
        return a->freq > b->freq;
    }
};

// Constructor: crea el árbol de Huffman a partir de las frecuencias
ArbolHuffman::ArbolHuffman(const std::unordered_map<char, unsigned long long>& frec) : raiz(nullptr) {
    priority_queue<Nodo*, std::vector<Nodo*>, CompareHuff> pq;
    for (const auto& kv : frec) {
        pq.push(new Nodo(kv.first, kv.second));
    }
    if (pq.empty()) return;
    if (pq.size() == 1) {
        Nodo* only = pq.top(); pq.pop();
        raiz = new Nodo(new Nodo(only->c, only->freq), new Nodo('\0', 0));
    } else {
        while (pq.size() > 1) {
            Nodo* a = pq.top(); pq.pop();
            Nodo* b = pq.top(); pq.pop();
            pq.push(new Nodo(a, b));
        }
        raiz = pq.top();
    }
    construirCodigos(raiz, "");
}

// Destructor
ArbolHuffman::~ArbolHuffman() {
    liberar(raiz);
}

// Recorremos el árbol y genera los códigos para cada símbolo
void ArbolHuffman::construirCodigos(Nodo* nodo, const string& prefijo) {
    if (!nodo) return;
    if (!nodo->left && !nodo->right) {
        codigos[nodo->c] = prefijo.empty() ? "0" : prefijo;
        return;
    }
    construirCodigos(nodo->left, prefijo + "0");
    construirCodigos(nodo->right, prefijo + "1");
}

// Liberamos recursivamente la memoria del árbol
void ArbolHuffman::liberar(Nodo* nodo) {
    if (!nodo) return;
    liberar(nodo->left);
    liberar(nodo->right);
    delete nodo;
}

// Devolvemos el mapa de códigos binarios
const std::unordered_map<char, string>& ArbolHuffman::obtenerCodigos() const {
    return codigos;
}

// Devolvemos la raíz del árbol
Nodo* ArbolHuffman::obtenerRaiz() const {
    return raiz;
}