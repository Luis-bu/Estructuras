#ifndef ABB_H
#define ABB_H

#include <list>

class ABB {
public:
    ABB();
    ~ABB();

    bool insertar(int clave);
    bool eliminar(int clave);
    bool contiene(int clave) const;
    void inorden(std::list<int>& salida) const;
    void limpiar();

private:
    struct Nodo {
        int clave;
        Nodo* izq;
        Nodo* der;
        Nodo(int c) : clave(c), izq(NULL), der(NULL) {}
    };

    Nodo* raiz;

    bool insertarRec(Nodo*& actual, int clave);
    bool eliminarRec(Nodo*& actual, int clave);
    Nodo* nodoMinimo(Nodo* actual) const;
    bool contieneRec(Nodo* actual, int clave) const;
    void inordenRec(Nodo* actual, std::list<int>& salida) const;
    void limpiarRec(Nodo* actual);
};

#endif
