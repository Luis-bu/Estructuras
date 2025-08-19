#include <iostream>
#include "Polinomio.h"

int main() {
    // Caso 1: ambos vacíos
    Polinomio<double> p1, p2;
    std::cout << "Caso 1: " << (p1 + p2) << std::endl;

    // Caso 2: uno vacío
    p1.FijarCoeficiente(2, 3.0);
    p1.FijarCoeficiente(0, 2.0);
    Polinomio<double> vacio;
    std::cout << "Caso 2: " << (p1 + vacio) << std::endl;

    // Caso 3: igual tamaño
    Polinomio<double> p3, p4;
    p3.FijarCoeficiente(2, 3.0);
    p3.FijarCoeficiente(0, 2.0);
    p4.FijarCoeficiente(2, -3.0);
    p4.FijarCoeficiente(0, 4.0);
    std::cout << "Caso 3: " << (p3 + p4) << std::endl;

    // Caso 4: izq más grande
    Polinomio<int> p5, p6;
    p5.FijarCoeficiente(3, 5);
    p5.FijarCoeficiente(2, 1);
    p5.FijarCoeficiente(0, -2);
    p6.FijarCoeficiente(2, 3);
    p6.FijarCoeficiente(0, 7);
    std::cout << "Caso 4: " << (p5 + p6) << std::endl;

    // Caso 5: der más grande
    Polinomio<int> p7, p8;
    p7.FijarCoeficiente(1, 2);
    p7.FijarCoeficiente(0, 3);
    p8.FijarCoeficiente(3, 4);
    p8.FijarCoeficiente(1, 1);
    p8.FijarCoeficiente(0, 1);
    std::cout << "Caso 5: " << (p7 + p8) << std::endl;

    // Caso 6: con decimales
    Polinomio<double> p9, p10;
    p9.FijarCoeficiente(2, 2.5);
    p9.FijarCoeficiente(0, -1.5);
    p10.FijarCoeficiente(2, 1.5);
    p10.FijarCoeficiente(0, 1.5);
    std::cout << "Caso 6: " << (p9 + p10) << std::endl;

    // Caso 7: coeficientes que se anulan
    Polinomio<int> p11, p12;
    p11.FijarCoeficiente(2, 5);
    p12.FijarCoeficiente(2, -5);
    std::cout << "Caso 7: " << (p11 + p12) << std::endl;

    return 0;
}
