/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: LeerFichero.cpp
 * Descripción: Contiene la implementación de LeerFichero.cpp
*/

#include "../includes/LeerFichero.h"
#include "../includes/Transicion.h"
#include "../includes/MaquinaTuring.h"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <set>
#include <stdexcept>

MaquinaTuring LeerFichero::parsear(bool modo_traza) {
  const std::filesystem::path ruta_fichero(nombre_fichero_);
  std::ifstream fichero_entrada(ruta_fichero);
  if (!fichero_entrada.is_open() && ruta_fichero.is_relative() &&
      ruta_fichero.parent_path().empty()) {
    fichero_entrada.clear();
    fichero_entrada.open(std::filesystem::path("../tests") / ruta_fichero);
    if (!fichero_entrada.is_open()) {
      fichero_entrada.clear();
      fichero_entrada.open(std::filesystem::path("tests") / ruta_fichero);
    }
  }
  if (!fichero_entrada.is_open()) {
    throw std::runtime_error("Error al abrir el fichero\n");
  }

  MaquinaTuring maquina_turing_configurada(modo_traza);
  std::string linea;
  std::size_t numero_linea = 0;

  auto leerLineaValida = [&](std::vector<std::string>& campos) {
    while (std::getline(fichero_entrada, linea)) {
      ++numero_linea;
      std::stringstream ss(linea);
      std::string campo;
      campos.clear();
      while (ss >> campo) {
        campos.push_back(campo);
      }
      if (campos.empty() || campos.front().starts_with('#')) continue;
      return true;
    }
    return false;
  };

  auto errorLinea = [&](const std::string& mensaje) {
    throw std::runtime_error("Error en el fichero '" + nombre_fichero_ +
                             "', linea " + std::to_string(numero_linea) + ": " + mensaje);
  };

  auto leerDefinicion = [&](const std::string& descripcion, std::vector<std::string>& campos) {
    if (!leerLineaValida(campos)) {
      errorLinea("falta la definicion de " + descripcion);
    }
  };

  std::vector<std::string> campos;

  // 1. Conjunto de estados (Q)
  leerDefinicion("estados", campos);
  std::set<std::string> estados;
  for (const std::string& estado : campos) {
    if (!estados.insert(estado).second) {
      errorLinea("el estado '" + estado + "' esta repetido");
    }
    maquina_turing_configurada.anadirEstado(estado);
  }

  // 2. Conjunto de símbolos del alfabeto de entrada (Sigma)
  leerDefinicion("el alfabeto de entrada", campos);
  std::set<char> simbolos_entrada;
  for (const std::string& token : campos) {
    if (token.size() != 1) {
      errorLinea("simbolo de entrada invalido '" + token + "' (debe ser un unico caracter)");
    }
    if (!simbolos_entrada.insert(token[0]).second) {
      errorLinea("el simbolo de entrada '" + token + "' esta repetido");
    }
    maquina_turing_configurada.anadirSimboloEntrada(token[0]);
  }

  // 3. Conjunto de símbolos del alfabeto de la cinta (Gamma)
  leerDefinicion("el alfabeto de cinta", campos);
  std::set<char> simbolos_cinta;
  for (const std::string& token : campos) {
    if (token.size() != 1) {
      errorLinea("simbolo de cinta invalido '" + token + "' (debe ser un unico caracter)");
    }
    if (!simbolos_cinta.insert(token[0]).second) {
      errorLinea("el simbolo de cinta '" + token + "' esta repetido");
    }
    maquina_turing_configurada.anadirSimboloCinta(token[0]);
  }

  // Validar que el alfabeto de entrada está contenido en el de cinta
  for (char c : simbolos_entrada) {
    if (!simbolos_cinta.contains(c)) {
      errorLinea("el simbolo de entrada '" + std::string(1, c) + "' no pertenece al alfabeto de cinta");
    }
  }

  // 4. Estado inicial (s)
  leerDefinicion("el estado inicial", campos);
  if (campos.size() != 1) {
    errorLinea("el estado inicial debe ser exactamente un estado");
  }
  if (!estados.contains(campos[0])) {
    errorLinea("el estado inicial '" + campos[0] + "' no pertenece al conjunto de estados");
  }
  maquina_turing_configurada.setEstadoInicial(campos[0]);

  // 5. Símbolo blanco (b)
  leerDefinicion("el simbolo blanco", campos);
  if (campos.size() != 1 || campos[0].size() != 1) {
    errorLinea("el simbolo blanco debe ser un unico caracter");
  }
  char simbolo_blanco = campos[0][0];
  if (!simbolos_cinta.contains(simbolo_blanco)) {
    errorLinea("el simbolo blanco '" + std::string(1, simbolo_blanco) + "' no pertenece al alfabeto de cinta");
  }
  maquina_turing_configurada.setSimboloBlanco(simbolo_blanco);

  // 6. Estados finales (F)
  leerDefinicion("los estados finales", campos);
  for (const std::string& estado : campos) {
    if (!estados.contains(estado)) {
      errorLinea("el estado final '" + estado + "' no pertenece al conjunto de estados");
    }
    maquina_turing_configurada.marcarEstadoFinal(estado);
  }

  // 7. Número de cintas
  leerDefinicion("el numero de cintas", campos);
  if (campos.size() != 1) {
    errorLinea("el numero de cintas debe ser un unico valor numerico");
  }
  int numero_cintas = 0;
  try {
    numero_cintas = std::stoi(campos[0]);
    if (numero_cintas < 1) throw std::invalid_argument("");
  } catch (...) {
    errorLinea("el numero de cintas debe ser un entero mayor o igual a 1");
  }
  maquina_turing_configurada.setNumeroCintas(numero_cintas);

  // 8. Transiciones
  // Formato para k cintas: estado_actual (1) + leidos (k) + estado_sig (1) + escritos (k) + movs (k)
  size_t campos_esperados = 2 + 3 * numero_cintas;

  while (leerLineaValida(campos)) {
    if (campos.size() != campos_esperados) {
      errorLinea("una transicion para " + std::to_string(numero_cintas) + 
                 " cintas debe tener exactamente " + std::to_string(campos_esperados) + " elementos separados por espacios");
    }

    const std::string& estado_origen = campos[0];
    if (!estados.contains(estado_origen)) {
      errorLinea("el estado de origen '" + estado_origen + "' no existe");
    }

    std::vector<char> leidos;
    for (int i = 0; i < numero_cintas; ++i) {
      if (campos[1 + i].size() != 1 || !simbolos_cinta.contains(campos[1 + i][0])) {
        errorLinea("simbolo leido invalido o no pertenece a la cinta");
      }
      leidos.push_back(campos[1 + i][0]);
    }

    const std::string& estado_destino = campos[1 + numero_cintas];
    if (!estados.contains(estado_destino)) {
      errorLinea("el estado destino '" + estado_destino + "' no existe");
    }

    std::vector<char> escritos;
    for (int i = 0; i < numero_cintas; ++i) {
      if (campos[2 + numero_cintas + i].size() != 1 || !simbolos_cinta.contains(campos[2 + numero_cintas + i][0])) {
        errorLinea("simbolo a escribir invalido o no pertenece a la cinta");
      }
      escritos.push_back(campos[2 + numero_cintas + i][0]);
    }

    std::vector<char> movimientos;
    for (int i = 0; i < numero_cintas; ++i) {
      char mov = campos[2 + 2 * numero_cintas + i][0];
      if (campos[2 + 2 * numero_cintas + i].size() != 1 || (mov != 'L' && mov != 'R' && mov != 'S')) {
        errorLinea("movimiento invalido (debe ser L, R o S)");
      }
      movimientos.push_back(mov);
    }

    Transicion t(estado_destino, escritos, movimientos);
    maquina_turing_configurada.anadirTransicion(estado_origen, leidos, t);
  }

  return maquina_turing_configurada;
}