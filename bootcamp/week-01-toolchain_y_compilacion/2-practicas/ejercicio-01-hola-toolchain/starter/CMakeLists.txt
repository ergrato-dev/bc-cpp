cmake_minimum_required(VERSION 3.28)
project(ejercicio_01_hola_toolchain LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)   # -std=c++20, no -std=gnu++20

add_executable(app src/main.cpp)
target_compile_features(app PUBLIC cxx_std_20)
target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Tests de las semanas 01-03: ejecutan el programa y comprueban su salida.
# Cada test corresponde a un PASO del README y falla hasta que lo descomentas.
enable_testing()

add_test(NAME paso1_saludo COMMAND app)
set_tests_properties(paso1_saludo PROPERTIES
  PASS_REGULAR_EXPRESSION "Hola, C\\+\\+20")

add_test(NAME paso2_inventario COMMAND app)
set_tests_properties(paso2_inventario PROPERTIES
  PASS_REGULAR_EXPRESSION "3 items en stock, total 18\\.75 EUR")

add_test(NAME paso3_tabla COMMAND app)
set_tests_properties(paso3_tabla PROPERTIES
  PASS_REGULAR_EXPRESSION "pan +3 +1\\.50\nleche +12 +0\\.89")

add_test(NAME paso4_aviso_en_cerr COMMAND app)
set_tests_properties(paso4_aviso_en_cerr PROPERTIES
  PASS_REGULAR_EXPRESSION "aviso: precios sin IVA")
