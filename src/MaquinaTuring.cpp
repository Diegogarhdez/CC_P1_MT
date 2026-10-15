/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: MaquinaTuring.cpp
 * Descripción: Contiene la implementación clase MaquinaTuring
*/

#include "../includes/MaquinaTuring.h"

void MaquinaTuring::marcarEstadoFinal(const std::string& estado) {
  auto it = estados_.find(estado);
  if (it != estados_.end()) {
    it->second.setFinal(true);
  }
}

void MaquinaTuring::inicializarEjecucion(const std::string& cadena_entrada) {
  estado_actual_ = estado_inicial_;
  for (int i = 0; i < numero_cintas_; ++i) {
    cintas_[i].setSimboloBlanco(simbolo_blanco_);
    if (i == 0) {
      cintas_[i].inicializar(cadena_entrada);
    } else {
      cintas_[i].inicializar("");
    }
  }
}

void MaquinaTuring::ejecutar() {
  while (true) {
    std::vector<char> simbolos_leidos;
    for (int i = 0; i < numero_cintas_; ++i) {
      simbolos_leidos.push_back(cintas_[i].leer());
    }

    if (modo_traza_) {
      std::cout << "Estado actual: " << estado_actual_ << "\n";
      imprimirCintas();
      std::cout << "Leyendo: ";
      for (char c : simbolos_leidos) std::cout << c << " ";
      std::cout << "\n-----------------------\n";
    }

    const Transicion* transicion = estados_[estado_actual_].obtenerTransicion(simbolos_leidos);

    if (transicion == nullptr) break; 

    const std::vector<char>& escritos = transicion->getSimbolosAEscribir();
    const std::vector<char>& movimientos = transicion->getMovimientos();

    for (int i = 0; i < numero_cintas_; ++i) {
      cintas_[i].escribir(escritos[i]);
      cintas_[i].mover(movimientos[i]);
    }
    estado_actual_ = transicion->getEstadoSiguiente();
  }
}

bool MaquinaTuring::esEstadoAceptacion() const {
  auto it = estados_.find(estado_actual_);
  if (it != estados_.end()) {
    return it->second.esFinal();
  }
  return false;
}

void MaquinaTuring::imprimirCintas() const {
  for (int i = 0; i < numero_cintas_; ++i) {
    if (numero_cintas_ > 1) {
      std::cout << "Cinta " << i + 1 << ": ";
    } else {
      std::cout << "Cinta: ";
    }
    std::cout << cintas_[i].obtenerContenidoFormateado() << std::endl;
  }
}