#ifndef AVL_H
#define AVL_H

#include <list>

class AVL {
public:
    AVL();
    ~AVL();

    bool insertar(int clave);
    bool eliminar(int clave);
    bool contiene(int clave) const;
    void inorden(std::list<int>& salida) const;
    void limpiar();

private:
    struct Nodo {
        int clave;
        int altura;
        Nodo* izq;
        Nodo* der;
        Nodo(int c) : clave(c), altura(1), izq(NULL), der(NULL) {}
    };

    Nodo* raiz;

    void limpiarRec(Nodo* actual);
    int alturaDe(Nodo* actual) const;
    int factorBalance(Nodo* actual) const;
    void actualizarAltura(Nodo* actual);

    Nodo* rotacionDerecha(Nodo* y);
    Nodo* rotacionIzquierda(Nodo* x);

    bool contieneRec(Nodo* actual, int clave) const;
    void inordenRec(Nodo* actual, std::list<int>& salida) const;

    Nodo* insertarRec(Nodo* actual, int clave, bool& cambiado);
    Nodo* eliminarRec(Nodo* actual, int clave, bool& cambiado);
    Nodo* nodoMinimo(Nodo* actual) const;
};

#endif
