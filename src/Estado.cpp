/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Estado.cpp
 * Descripción: Contiene la implementación de la clase Estado
*/

#include "../includes/Estado.h"

const Transicion* Estado::obtenerTransicion(const std::vector<char>& simbolos_leidos) const {
  auto it = transiciones_.find(simbolos_leidos);
  if (it != transiciones_.end()) {
    return &(it->second);
  }
  return nullptr; 
}


