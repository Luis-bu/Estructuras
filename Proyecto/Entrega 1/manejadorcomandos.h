#ifndef MANEJADORCOMANDOS_H
#define MANEJADORCOMANDOS_H

#include <string>
#include <vector>
#include "secuencia.h"

// Estructura que representa un comando disponible en nuestro programa.
struct Comando {
    std::string nombre;      
    int numParametros;      
    std::string textoAyuda;  
};

// Clase que maneja el registro, validación y ejecución de comandos.
class ManejadorComandos {
private:
    std::vector<Comando> comandos;     
    std::vector<Secuencia> secuencias; 

    // Funciones auxiliares para los distintos comandos.
    void comandoCargar(const std::vector<std::string>& params);
    void comandoListarSecuencias();
    void comandoHistograma(const std::vector<std::string>& params);
    void comandoEsSubsecuencia(const std::vector<std::string>& params);
    void comandoEnmascarar(const std::vector<std::string>& params);
    void comandoGuardar(const std::vector<std::string>& params);

    // Función que devuelve el conjunto de caracteres permitidos para las bases.
    std::vector<char> getOrden();

    // Devuelve true si la cadena representa un entero válido.
    bool esEntero(const std::string& str);

    // Busca un comando por nombre y devuelve su definición.
    bool buscarComando(const std::string& cmd, Comando& comando) const;

    // Valida un comando y sus parámetros.
    bool validarComando(const std::string& cmd, const std::vector<std::string>& params);

public:
    ManejadorComandos();

    // Ejecuta el comando especificado si es válido.
    void ejecutarComando(const std::string& cmd, const std::vector<std::string>& params);

    // Muestra la lista de comandos disponibles.
    void mostrarAyuda();

    // Muestra la ayuda detallada de un comando específico.
    void mostrarAyudaComando(const std::string& cmd);
};

#endif // MANEJADORCOMANDOS_H