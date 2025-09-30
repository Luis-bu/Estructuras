#include "avl.h"

AVL::AVL() : raiz(NULL) {}
AVL::~AVL() { limpiar(); }

// Liberamos todos los nodos del árbol
void AVL::limpiar() {
    limpiarRec(raiz);
    raiz = NULL;
}

void AVL::limpiarRec(Nodo* actual) {
    if (actual == NULL) return;
    limpiarRec(actual->izq);
    limpiarRec(actual->der);
    delete actual;
}

// Calculamos la altura de un nodo
int AVL::alturaDe(Nodo* actual) const {
    if (actual == NULL) return 0;
    return actual->altura;
}

// Recalculamos la altura de un nodo después de inserción/eliminación
void AVL::actualizarAltura(Nodo* actual) {
    if (actual == NULL) return;
    int hIzq = alturaDe(actual->izq);
    int hDer = alturaDe(actual->der);
    actual->altura = (hIzq > hDer ? hIzq : hDer) + 1;
}

// Diferencia de alturas entre subárbol izquierdo y derecho
int AVL::factorBalance(Nodo* actual) const {
    if (actual == NULL) return 0;
    return alturaDe(actual->izq) - alturaDe(actual->der);
}

// Rotación simple a la derecha
AVL::Nodo* AVL::rotacionDerecha(Nodo* y) {
    Nodo* x = y->izq;
    Nodo* T2 = x->der;

    x->der = y;
    y->izq = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

// Rotación simple a la izquierda
AVL::Nodo* AVL::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->der;
    Nodo* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}

// Insertamos un valor y reequilibramos si es necesario
bool AVL::insertar(int clave) {
    bool cambiado = false;
    raiz = insertarRec(raiz, clave, cambiado);
    return cambiado;
}

AVL::Nodo* AVL::insertarRec(Nodo* actual, int clave, bool& cambiado) {
    if (actual == NULL) {
        cambiado = true;
        return new Nodo(clave);
    }
    if (clave < actual->clave) {
        actual->izq = insertarRec(actual->izq, clave, cambiado);
    } else if (clave > actual->clave) {
        actual->der = insertarRec(actual->der, clave, cambiado);
    } else {
        return actual; // clave duplicada
    }

    actualizarAltura(actual);
    int bf = factorBalance(actual);

    // Casos de rotación
    if (bf > 1 && clave < actual->izq->clave) return rotacionDerecha(actual); // LL
    if (bf < -1 && clave > actual->der->clave) return rotacionIzquierda(actual); // RR
    if (bf > 1 && clave > actual->izq->clave) { // LR
        actual->izq = rotacionIzquierda(actual->izq);
        return rotacionDerecha(actual);
    }
    if (bf < -1 && clave < actual->der->clave) { // RL
        actual->der = rotacionDerecha(actual->der);
        return rotacionIzquierda(actual);
    }

    return actual;
}

// Verificamos si una clave existe
bool AVL::contiene(int clave) const {
    return contieneRec(raiz, clave);
}

bool AVL::contieneRec(Nodo* actual, int clave) const {
    if (actual == NULL) return false;
    if (clave < actual->clave) return contieneRec(actual->izq, clave);
    if (clave > actual->clave) return contieneRec(actual->der, clave);
    return true;
}

// Encontramos el nodo mínimo
AVL::Nodo* AVL::nodoMinimo(Nodo* actual) const {
    Nodo* p = actual;
    while (p != NULL && p->izq != NULL) p = p->izq;
    return p;
}

// Eliminamos un valor y reequilibramos si es necesario
bool AVL::eliminar(int clave) {
    bool cambiado = false;
    raiz = eliminarRec(raiz, clave, cambiado);
    return cambiado;
}

AVL::Nodo* AVL::eliminarRec(Nodo* actual, int clave, bool& cambiado) {
    if (actual == NULL) {
        cambiado = false;
        return actual;
    }

    if (clave < actual->clave) {
        actual->izq = eliminarRec(actual->izq, clave, cambiado);
    } else if (clave > actual->clave) {
        actual->der = eliminarRec(actual->der, clave, cambiado);
    } else {
        // Nodo encontrado
        cambiado = true;
        if (actual->izq == NULL || actual->der == NULL) { // un hijo o ninguno
            Nodo* tmp = actual->izq ? actual->izq : actual->der;
            if (tmp == NULL) {
                delete actual;
                actual = NULL;
            } else {
                *actual = *tmp;
                delete tmp;
            }
        } else {
            // dos hijos
            Nodo* sucesor = nodoMinimo(actual->der);
            actual->clave = sucesor->clave;
            actual->der = eliminarRec(actual->der, sucesor->clave, cambiado);
        }
    }

    if (actual == NULL) return actual;

    actualizarAltura(actual);
    int bf = factorBalance(actual);

    // Reequilibrar
    if (bf > 1 && factorBalance(actual->izq) >= 0) return rotacionDerecha(actual); // LL
    if (bf > 1 && factorBalance(actual->izq) < 0) { // LR
        actual->izq = rotacionIzquierda(actual->izq);
        return rotacionDerecha(actual);
    }
    if (bf < -1 && factorBalance(actual->der) <= 0) return rotacionIzquierda(actual); // RR
    if (bf < -1 && factorBalance(actual->der) > 0) { // RL
        actual->der = rotacionDerecha(actual->der);
        return rotacionIzquierda(actual);
    }

    return actual;
}

// Recorrido en inorden
void AVL::inorden(std::list<int>& salida) const {
    salida.clear();
    inordenRec(raiz, salida);
}

void AVL::inordenRec(Nodo* actual, std::list<int>& salida) const {
    if (actual == NULL) return;
    inordenRec(actual->izq, salida);
    salida.push_back(actual->clave);
    inordenRec(actual->der, salida);
}
