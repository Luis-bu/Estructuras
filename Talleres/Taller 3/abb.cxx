#include "abb.h"

ABB::ABB() : raiz(NULL) {}
ABB::~ABB() { limpiar(); }

void ABB::limpiar() {
    limpiarRec(raiz);
    raiz = NULL;
}

void ABB::limpiarRec(Nodo* actual) {
    if (actual == NULL) return;
    limpiarRec(actual->izq);
    limpiarRec(actual->der);
    delete actual;
}

bool ABB::insertar(int clave) {
    return insertarRec(raiz, clave);
}

bool ABB::insertarRec(Nodo*& actual, int clave) {
    if (actual == NULL) {
        actual = new Nodo(clave);
        return true;
    }
    if (clave < actual->clave) return insertarRec(actual->izq, clave);
    if (clave > actual->clave) return insertarRec(actual->der, clave);
    return false;
}

bool ABB::contiene(int clave) const {
    return contieneRec(raiz, clave);
}

bool ABB::contieneRec(Nodo* actual, int clave) const {
    if (actual == NULL) return false;
    if (clave < actual->clave) return contieneRec(actual->izq, clave);
    if (clave > actual->clave) return contieneRec(actual->der, clave);
    return true;
}

ABB::Nodo* ABB::nodoMinimo(Nodo* actual) const {
    Nodo* p = actual;
    while (p != NULL && p->izq != NULL) p = p->izq;
    return p;
}

bool ABB::eliminar(int clave) {
    return eliminarRec(raiz, clave);
}

bool ABB::eliminarRec(Nodo*& actual, int clave) {
    if (actual == NULL) return false;

    if (clave < actual->clave) return eliminarRec(actual->izq, clave);
    if (clave > actual->clave) return eliminarRec(actual->der, clave);

    // encontrado
    if (actual->izq == NULL && actual->der == NULL) {
        delete actual;
        actual = NULL;
    } else if (actual->izq == NULL) {
        Nodo* tmp = actual->der;
        delete actual;
        actual = tmp;
    } else if (actual->der == NULL) {
        Nodo* tmp = actual->izq;
        delete actual;
        actual = tmp;
    } else {
        Nodo* sucesor = nodoMinimo(actual->der);
        actual->clave = sucesor->clave;
        eliminarRec(actual->der, sucesor->clave);
    }
    return true;
}

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
