// arbolhuffman.cxx
// Implementación del TAD para árboles de Huffman.

#include "arbolhuffman.h"
#include <queue>

using std::priority_queue;
using std::unordered_map;
using std::string;

// Comparador para la cola de prioridad (frecuencia ascendente).
struct CompareHuff {
    bool operator()(ArbolHuffman::Nodo* a, ArbolHuffman::Nodo* b) {
        if (a->freq == b->freq) return a->c > b->c;
        return a->freq > b->freq;
    }
};

ArbolHuffman::ArbolHuffman(const unordered_map<char, unsigned long long>& frec) : raiz(nullptr) {
    priority_queue<Nodo*, std::vector<Nodo*>, CompareHuff> pq;
    for (auto& kv : frec) {
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

ArbolHuffman::~ArbolHuffman() {
    liberar(raiz);
}

void ArbolHuffman::liberar(Nodo* nodo) {
    if (!nodo) return;
    liberar(nodo->left);
    liberar(nodo->right);
    delete nodo;
}

void ArbolHuffman::construirCodigos(Nodo* nodo, const string& prefijo) {
    if (!nodo) return;
    if (!nodo->left && !nodo->right) {
        codigos[nodo->c] = prefijo.empty() ? "0" : prefijo;
        return;
    }
    construirCodigos(nodo->left, prefijo + "0");
    construirCodigos(nodo->right, prefijo + "1");
}

const unordered_map<char, string>& ArbolHuffman::obtenerCodigos() const {
    return codigos;
}

ArbolHuffman::Nodo* ArbolHuffman::obtenerRaiz() const {
    return raiz;
}
