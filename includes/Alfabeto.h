/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: Alfabeto.h
 * Descripción: Contiene la declaración clase Alfabeto
*/

#ifndef ALFABETO_H_
#define ALFABETO_H_

#include <set>
#include <iostream>

class Alfabeto {
public:
  // Constructor por defecto
  Alfabeto() : simbolo_blanco_(' ') {} 

  // Constructor si queremos inicializarlo con un set ya creado y un símbolo blanco
  Alfabeto(const std::set<char>& alfabeto, char simbolo_blanco) 
      : alfabeto_(alfabeto), simbolo_blanco_(simbolo_blanco) {}

  // Actualizamos el símbolo blanco cuando lo leamos del fichero
  void setSimboloBlanco(char c) { simbolo_blanco_ = c; }
  char getSimboloBlanco() const { return simbolo_blanco_; }

  // Verificamos si pertenece (incluyendo el blanco dinámico)
  bool pertenece(char c) const { 
    return c == simbolo_blanco_ || alfabeto_.find(c) != alfabeto_.end(); 
  }

  void insertarSimbolo(char c) { 
    alfabeto_.insert(c); 
  }

  std::set<char> getSimbolos() const { 
    return alfabeto_; 
  }

private:
  std::set<char> alfabeto_;
  char simbolo_blanco_;
};

std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);

#endif