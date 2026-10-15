/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Estado.h
 * Descripción: Contiene la declaración de la clase Estado
*/

#ifndef ESTADO_H_
#define ESTADO_H_

#include <map>
#include <vector>
#include <string>
#include <optional>

#include "Transicion.h"

class Estado {
public:
  Estado() {}
  Estado(const std::string& nombre) : nombre_(nombre) {}
  void anadirTransicion(const std::vector<char>& simbolos_leidos, const Transicion& transicion) {
    transiciones_[simbolos_leidos] = transicion;
  }
  const Transicion* obtenerTransicion(const std::vector<char>& simbolos_leidos) const;

  std::string getNombre() const { return nombre_; }
  bool esFinal() const { return es_final_; }
  void setFinal(bool final) { es_final_ = final; }

private:
  std::string nombre_;
  bool es_final_ = false;
  std::map<std::vector<char>, Transicion> transiciones_; 
};

#endif