cmake_minimum_required(VERSION 3.28)
# NOTA PARA EL APRENDIZ: renombra el proyecto a tu dominio (biblioteca, farmacia...).
project(inventario_item LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)   # -std=c++20, no -std=gnu++20

add_executable(app src/main.cpp)
target_compile_features(app PUBLIC cxx_std_20)
target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Werror)

enable_testing()

# Test de ejemplo: la cabecera del informe. Falla hasta que implementes el TODO 1.
add_test(NAME cabecera COMMAND app)
set_tests_properties(cabecera PROPERTIES
  PASS_REGULAR_EXPRESSION "=== Inventario de Item ===")

# TODO: añade un test por cada requisito del README (total, media, máximo, porcentaje).
# Firma esperada (CMake):
#   add_test(NAME total COMMAND app)
#   set_tests_properties(total PROPERTIES PASS_REGULAR_EXPRESSION "Total unidades: 27")
# Pista: los valores exactos dependen de TUS tres registros; calcula el esperado a mano.
