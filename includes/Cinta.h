/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Cinta.h
 * Descripción: Contiene la clase Cinta.h
*/

#ifndef CINTA_H
#define CINTA_H

#include <unordered_map>
#include <string>

class Cinta {
 public:
  Cinta(char simbolo_blanco = ' ') : posicion_cabezal_(0), simbolo_blanco_(simbolo_blanco) {}
  void setSimboloBlanco(char simbolo);
  void inicializar(const std::string& cadena_entrada);
  char leer() const;
  void escribir(char simbolo);
  void mover(char direccion);
  std::string obtenerContenidoFormateado() const;

 private:
  std::unordered_map<int, char> grid_;
  int posicion_cabezal_;
  char simbolo_blanco_;
};

#endif