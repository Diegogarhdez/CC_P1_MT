/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Transicion.h
 * Descripción: Contiene la declaración clase Transicion
*/

#ifndef TRANSICION_H_
#define TRANSICION_H_

#include <vector>
#include <string>

class Transicion {
public:
  Transicion() {}
  Transicion(const std::string& estado_siguiente, 
             const std::vector<char>& simbolos_a_escribir, 
             const std::vector<char>& movimientos)
      : estado_siguiente_(estado_siguiente), 
        simbolos_a_escribir_(simbolos_a_escribir), 
        movimientos_(movimientos) {}

  // Getters
  std::string getEstadoSiguiente() const { return estado_siguiente_; }
  const std::vector<char>& getSimbolosAEscribir() const { return simbolos_a_escribir_; }
  const std::vector<char>& getMovimientos() const { return movimientos_; }

private:
  std::string estado_siguiente_;
  std::vector<char> simbolos_a_escribir_;
  std::vector<char> movimientos_;
};

#endif