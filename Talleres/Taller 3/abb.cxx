#include "abb.h"

ABB::ABB() : raiz(NULL) {}
ABB::~ABB() { limpiar(); }

// Libera toda la memoria del árbol
void ABB::limpiar() {
    limpiarRec(raiz);
    raiz = NULL;
}

// Recorrido postorden para liberar nodos
void ABB::limpiarRec(Nodo* actual) {
    if (actual == NULL) return;
    limpiarRec(actual->izq);
    limpiarRec(actual->der);
    delete actual;
}

// Inserta una clave en el ABB
bool ABB::insertar(int clave) {
    return insertarRec(raiz, clave);
}

// Inserción recursiva (O(log n) en promedio, O(n) en peor caso si se desbalancea)
bool ABB::insertarRec(Nodo*& actual, int clave) {
    if (actual == NULL) { // caso base: nodo vacío
        actual = new Nodo(clave);
        return true;
    }
    if (clave < actual->clave) return insertarRec(actual->izq, clave);
    if (clave > actual->clave) return insertarRec(actual->der, clave);
    return false; // clave duplicada
}

// Verifica si una clave existe en el árbol
bool ABB::contiene(int clave) const {
    return contieneRec(raiz, clave);
}

// Búsqueda recursiva
bool ABB::contieneRec(Nodo* actual, int clave) const {
    if (actual == NULL) return false;
    if (clave < actual->clave) return contieneRec(actual->izq, clave);
    if (clave > actual->clave) return contieneRec(actual->der, clave);
    return true;
}

// Busca el nodo con el valor mínimo en un subárbol
ABB::Nodo* ABB::nodoMinimo(Nodo* actual) const {
    Nodo* p = actual;
    while (p != NULL && p->izq != NULL) p = p->izq;
    return p;
}

// Elimina una clave del ABB
bool ABB::eliminar(int clave) {
    return eliminarRec(raiz, clave);
}

// Eliminación recursiva con 3 casos: hoja, un hijo, dos hijos
bool ABB::eliminarRec(Nodo*& actual, int clave) {
    if (actual == NULL) return false;

    if (clave < actual->clave) return eliminarRec(actual->izq, clave);
    if (clave > actual->clave) return eliminarRec(actual->der, clave);

    // caso encontrado
    if (actual->izq == NULL && actual->der == NULL) { // hoja
        delete actual;
        actual = NULL;
    } else if (actual->izq == NULL) { // un hijo derecho
        Nodo* tmp = actual->der;
        delete actual;
        actual = tmp;
    } else if (actual->der == NULL) { // un hijo izquierdo
        Nodo* tmp = actual->izq;
        delete actual;
        actual = tmp;
    } else { // dos hijos: reemplazar con el sucesor
        Nodo* sucesor = nodoMinimo(actual->der);
        actual->clave = sucesor->clave;
        eliminarRec(actual->der, sucesor->clave);
    }
    return true;
}

// Recorrido en inorden (devuelve claves ordenadas)
void ABB::inorden(std::list<int>& salida) const {
    salida.clear();
    inordenRec(raiz, salida);
}

void ABB::inordenRec(Nodo* actual, std::list<int>& salida) const {
    if (actual == NULL) return;
    inordenRec(actual->izq, salida);
    salida.push_back(actual->clave);
    inordenRec(actual->der, salida);
}
