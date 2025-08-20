#include <iostream>
#include "Polinomio.h"

int main() {
    // Caso 1: ambos vacíos
    Polinomio<double> m1, m2;
    std::cout << "Caso 1: " << (m1 * m2) << std::endl;

    // Caso 2: uno vacío
    Polinomio<double> m3;
    m3.FijarCoeficiente(2, 3.0);
    m3.FijarCoeficiente(0, 2.0);
    Polinomio<double> vacio;
    std::cout << "Caso 2: " << (m3 * vacio) << std::endl;

    // Caso 3: igual tamaño
    Polinomio<double> m4, m5;
    m4.FijarCoeficiente(2, 3.0);
    m4.FijarCoeficiente(0, 2.0);
    m5.FijarCoeficiente(2, -3.0);
    m5.FijarCoeficiente(0, 4.0);
    std::cout << "Caso 3: " << (m4 * m5) << std::endl;

    // Caso 4: izq más grande
    Polinomio<int> m6, m7;
    m6.FijarCoeficiente(3, 5);
    m6.FijarCoeficiente(2, 1);
    m6.FijarCoeficiente(0, -2);
    m7.FijarCoeficiente(2, 3);
    m7.FijarCoeficiente(0, 7);
    std::cout << "Caso 4: " << (m6 * m7) << std::endl;

    // Caso 5: der más grande
    Polinomio<int> m8, m9;
    m8.FijarCoeficiente(1, 2);
    m8.FijarCoeficiente(0, 3);
    m9.FijarCoeficiente(2, 4);
    m9.FijarCoeficiente(1, 1);
    m9.FijarCoeficiente(0, 1);
    std::cout << "Caso 5: " << (m8 * m9) << std::endl;

    // Caso 6: con decimales
    Polinomio<double> m10, m11;
    m10.FijarCoeficiente(2, 2.5);
    m10.FijarCoeficiente(0, -1.5);
    m11.FijarCoeficiente(2, 1.5);
    m11.FijarCoeficiente(0, 1.5);
    std::cout << "Caso 6: " << (m10 * m11) << std::endl;

    // Caso 7: coeficientes que se anulan
    Polinomio<int> m12, m13;
    m12.FijarCoeficiente(2, 5);
    m13.FijarCoeficiente(2, -5);
    std::cout << "Caso 7: " << (m12 * m13) << std::endl;

    return 0;
}
