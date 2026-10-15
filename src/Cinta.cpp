/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Cinta.cpp
 * Descripción: Contiene la implementación de la clase Cinta
*/

#include "../includes/Cinta.h"

void Cinta::setSimboloBlanco(char simbolo) { 
  simbolo_blanco_ = simbolo; 
}

void Cinta::inicializar(const std::string& cadena_entrada) {
  grid_.clear();
  posicion_cabezal_ = 0;
  for (size_t i = 0; i < cadena_entrada.length(); ++i) {
    grid_[i] = cadena_entrada[i];
  }
}

char Cinta::leer() const {
  auto it = grid_.find(posicion_cabezal_);
  if (it != grid_.end()) {
    return it->second;
  }
  return simbolo_blanco_;
}

void Cinta::escribir(char simbolo) {
  grid_[posicion_cabezal_] = simbolo;
}

void Cinta::mover(char direccion) {
  if (direccion == 'L') {
    posicion_cabezal_--;
  } else if (direccion == 'R') {
    posicion_cabezal_++;
  }
}

std::string Cinta::obtenerContenidoFormateado() const {
  if (grid_.empty()) {
    return "[" + std::string(1, simbolo_blanco_) + "]";
  }
  int min_idx = posicion_cabezal_;
  int max_idx = posicion_cabezal_;

  for (const auto& par : grid_) {
    if (par.first < min_idx) min_idx = par.first;
    if (par.first > max_idx) max_idx = par.first;
  }

  std::string resultado = "";
  for (int i = min_idx; i <= max_idx; ++i) {
    char c = simbolo_blanco_;
    auto it = grid_.find(i);
    if (it != grid_.end()) {
      c = it->second;
    }

    if (i == posicion_cabezal_) {
      resultado += "[" + std::string(1, c) + "]";
    } else {
      resultado += c;
    }
  }
  return resultado;
}