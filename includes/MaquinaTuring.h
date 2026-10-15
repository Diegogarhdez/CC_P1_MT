/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: MaquinaTuring.h
 * Descripción: Contiene la clase MaquinaTuring
*/

#ifndef MAQUINATURING_H_
#define MAQUINATURING_H_

#include <map>

#include "Cinta.h"
#include "Alfabeto.h"
#include "Estado.h"

class MaquinaTuring {
 public: 
  MaquinaTuring(bool modo_traza = false) { modo_traza_ = modo_traza; }
  void inicializarEjecucion(const std::string& cadena_entrada);
  void ejecutar();

  void anadirEstado(const std::string& nombre_estado) {
    estados_[nombre_estado] = Estado(nombre_estado);
  }
  void anadirSimboloEntrada(char simbolo) {
    alfabeto_entrada_.insertarSimbolo(simbolo);
  }
  void anadirSimboloCinta(char simbolo) {
    alfabeto_cinta_.insertarSimbolo(simbolo);
  }
  void setEstadoInicial(const std::string& estado) {
    estado_inicial_ = estado;
  }
  void setSimboloBlanco(char simbolo) {
    simbolo_blanco_ = simbolo;
    alfabeto_cinta_.setSimboloBlanco(simbolo);
  }
  void marcarEstadoFinal(const std::string& estado);
  
  void setNumeroCintas(int numero) {
    numero_cintas_ = numero;
    cintas_.assign(numero_cintas_, Cinta(simbolo_blanco_));
  }
  void anadirTransicion(const std::string& estado_origen, const std::vector<char>& leidos, const Transicion& transicion) {
    estados_[estado_origen].anadirTransicion(leidos, transicion);
  }

  bool esEstadoAceptacion() const;
  void imprimirCintas() const;

 private:
  bool modo_traza_;
  std::vector<Cinta> cintas_;
  std::map<std::string, Estado> estados_;
  std::string estado_actual_;
  std::string estado_inicial_ = " ";
  char simbolo_blanco_ = ' '; 
  int numero_cintas_ = 1;
  Alfabeto alfabeto_entrada_;
  Alfabeto alfabeto_cinta_;
};

#endif