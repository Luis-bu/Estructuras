#include "abb.h"
using namespace std;

ABB::ABB() : raiz(NULL) {}
ABB::~ABB() { limpiar(); }

// Limpiamos todo el árbol y liberamos la memoria
void ABB::limpiar() {
    limpiarRec(raiz);
    raiz = NULL;
}

// Recorremos en postorden y liberamos cada nodo
void ABB::limpiarRec(Nodo* actual) {
    if (actual == NULL) return;
    limpiarRec(actual->izq);
    limpiarRec(actual->der);
    delete actual;
}

// Insertamos una clave en el ABB
bool ABB::insertar(int clave) {
    return insertarRec(raiz, clave);
}

// Insertamos recursivamente (O(log n) en promedio, O(n) en peor caso)
bool ABB::insertarRec(Nodo*& actual, int clave) {
    if (actual == NULL) { 
        actual = new Nodo(clave);
        return true;
    }
    if (clave < actual->clave) return insertarRec(actual->izq, clave);
    if (clave > actual->clave) return insertarRec(actual->der, clave);
    return false; // ya existe
}

// Verificamos si una clave está en el ABB
bool ABB::contiene(int clave) const {
    return contieneRec(raiz, clave);
}

// Buscamos recursivamente una clave
bool ABB::contieneRec(Nodo* actual, int clave) const {
    if (actual == NULL) return false;
    if (clave < actual->clave) return contieneRec(actual->izq, clave);
    if (clave > actual->clave) return contieneRec(actual->der, clave);
    return true;
}

// Obtenemos el nodo con la clave mínima de un subárbol
ABB::Nodo* ABB::nodoMinimo(Nodo* actual) const {
    Nodo* p = actual;
    while (p != NULL && p->izq != NULL) p = p->izq;
    return p;
}

// Eliminamos una clave del ABB
bool ABB::eliminar(int clave) {
    return eliminarRec(raiz, clave);
}

// Eliminamos recursivamente (3 casos: hoja, un hijo, dos hijos)
bool ABB::eliminarRec(Nodo*& actual, int clave) {
    if (actual == NULL) return false;

    if (clave < actual->clave) return eliminarRec(actual->izq, clave);
    if (clave > actual->clave) return eliminarRec(actual->der, clave);

    // Encontramos la clave
    if (actual->izq == NULL && actual->der == NULL) { 
        delete actual; actual = NULL;
    } else if (actual->izq == NULL) { 
        Nodo* tmp = actual->der;
        delete actual; actual = tmp;
    } else if (actual->der == NULL) { 
        Nodo* tmp = actual->izq;
        delete actual; actual = tmp;
    } else { 
        Nodo* sucesor = nodoMinimo(actual->der);
        actual->clave = sucesor->clave;
        eliminarRec(actual->der, sucesor->clave);
    }
    return true;
}

// Recorremos en inorden y guardamos las claves en la lista
void ABB::inorden(list<int>& salida) const {
    salida.clear();
    inordenRec(raiz, salida);
}

void ABB::inordenRec(Nodo* actual, list<int>& salida) const {
    if (actual == NULL) return;
    inordenRec(actual->izq, salida);
    salida.push_back(actual->clave);
    inordenRec(actual->der, salida);
}
