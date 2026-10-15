/** 
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Complejidad Computaciónal
 * Curso 2026/2027
 * Diego García Hernández
 * Archivo: main.cpp
 * Descripción: Contiene la función principal del proyecto
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../includes/LeerFichero.h"
#include "../includes/MaquinaTuring.h"

void mostrarUso() {
  std::cerr << "Uso: ./P2_MT -config <fichero_configuracion> [-in <fichero_cadenas>]\n";
}

int main(int argc, char* argv[]) {
  std::string fichero_config = "";
  std::string fichero_entrada = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-config" && i + 1 < argc) {
      fichero_config = "../test/" + std::string(argv[++i]);
    } else if (arg == "-in" && i + 1 < argc) {
      fichero_entrada = "../test/" + std::string(argv[++i]);
    }
  }

  if (fichero_config.empty()) {
    std::cerr << "Error: El parametro -config es obligatorio.\n";
    mostrarUso();
    return 1;
  }

  try {
    LeerFichero parser(fichero_config);
    MaquinaTuring maquina = parser.parsear(true);
    auto evaluarCadena = [&](const std::string& cadena) {
      std::cout << "\n==================================================\n";
      std::cout << " EVALUANDO CADENA: '" << cadena << "'\n";
      std::cout << "==================================================\n";

      maquina.inicializarEjecucion(cadena);
      maquina.ejecutar();

      std::cout << "\n--- RESULTADO DE LA EJECUCION ---\n";
      if (maquina.esEstadoAceptacion()) {
        std::cout << "Estado de aceptacion: SI\n";
      } else {
        std::cout << "Estado de aceptacion: NO\n";
      }
      std::cout << "Contenido final:\n";
      maquina.imprimirCintas();
      std::cout << "==================================================\n";
    };

    if (!fichero_entrada.empty()) {
      std::ifstream f_in(fichero_entrada);
      if (!f_in.is_open()) {
        std::cerr << "Error: No se pudo abrir el fichero de entrada '" << fichero_entrada << "'\n";
        return 1;
      }
      std::string linea;
      while (std::getline(f_in, linea)) {
        evaluarCadena(linea);
      }
    } else {
      std::cout << "Introduce la cadena a evaluar (escribe ':q' o pulsa Enter sin escribir nada para salir).\n";
      std::string linea;
      while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, linea);
        
        if (linea.empty() || linea == ":q") {
          std::cout << "Terminando simulador...\n";
          break;
        }
        
        evaluarCadena(linea);
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  }

  return 0;
}


