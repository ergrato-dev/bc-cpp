cmake_minimum_required(VERSION 3.28)
project(ejercicio_02_utilidades_de_cadenas LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)   # -std=c++20, no -std=gnu++20

add_executable(app src/main.cpp)
target_compile_features(app PUBLIC cxx_std_20)
target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Werror)

# Tests de las semanas 01-03: ejecutan el programa y comprueban su salida.
# Cada test corresponde a un PASO del README y falla hasta que lo descomentas.
enable_testing()

add_test(NAME paso1_trim COMMAND app)
set_tests_properties(paso1_trim PROPERTIES
  PASS_REGULAR_EXPRESSION "trim: \\[hola mundo\\]\ntrim vacio: \\[\\]\ntrim espacios: \\[\\]")

add_test(NAME paso2_to_upper COMMAND app)
set_tests_properties(paso2_to_upper PROPERTIES
  PASS_REGULAR_EXPRESSION "upper: \\[HOLA MUNDO 42\\]\noriginal: \\[hola mundo 42\\]")

add_test(NAME paso3_split COMMAND app)
set_tests_properties(paso3_split PROPERTIES
  PASS_REGULAR_EXPRESSION "split: 4 partes: \\[a\\] \\[b\\] \\[\\] \\[c\\]")

add_test(NAME paso4_join COMMAND app)
set_tests_properties(paso4_join PROPERTIES
  PASS_REGULAR_EXPRESSION "join: \\[x-y-z\\]\njoin vacio: \\[\\]")

add_test(NAME paso5_replace_all COMMAND app)
set_tests_properties(paso5_replace_all PROPERTIES
  PASS_REGULAR_EXPRESSION "replace: \\[perro y perro\\]\nreplace ana: \\[baanaanaa\\]")
