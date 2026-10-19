# PRÁCTICA 2: Simulador de Máquina de Turing Determinista

## Diego García Hernández
## alu0101633732@ull.edu.es

## Opciones Seleccionadas

De acuerdo con las variaciones permitidas en el enunciado:

* **Escritura y movimientos:** Simultáneos.
* **Movimientos permitidos:** Izquierda (`L`), Derecha (`R`) y No movimiento (`S`).
* **Límites de la cinta:** Infinita en ambas direcciones.

## Compilación

Para compilar el proyecto en consola mediante CMake:

```bash
cd build
cmake ..
make
```

## Ejecución

El programa principal acepta las siguientes opciones por línea de comandos:

```bash
# Modo interactivo (introducción de cadenas por teclado)
./P2_MT -config <fichero_configuracion>

# Modo por fichero de entradas
./P2_MT -config <fichero_configuracion> -in <fichero_cadenas>
```

### Ejemplos

```bash
./P2_MT -config Ejemplo1_MT.txt
./P2_MT -config Ejemplo2_MT.txt -in cadenas.txt
```