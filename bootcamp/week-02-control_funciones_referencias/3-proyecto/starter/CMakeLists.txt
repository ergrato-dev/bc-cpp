cmake_minimum_required(VERSION 3.28)
# NOTA PARA EL APRENDIZ: renombra el proyecto a tu dominio (biblioteca, farmacia...).
project(inventario_item LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)   # -std=c++20, no -std=gnu++20

add_executable(app src/main.cpp)
target_compile_features(app PUBLIC cxx_std_20)
target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Werror)
# En Debug (presets debug y asan), libstdc++ comprueba los índices de vector y
# string: v[10] sobre un vector de 3 aborta con un mensaje en vez de leer basura.
target_compile_definitions(app PRIVATE $<$<CONFIG:Debug>:_GLIBCXX_ASSERTIONS>)

enable_testing()

# Cada test entrega su entrada al programa por stdin y comprueba la salida.
function(add_stdin_test name input regex)
  add_test(NAME ${name} COMMAND sh -c "printf '${input}' | $<TARGET_FILE:app>")
  set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION "${regex}")
endfunction()

# Dos tests de ejemplo: pasan con el starter tal cual.
add_stdin_test(help "help\\nquit\\n" "comandos: add remove find list total help quit\nadiós")
add_stdin_test(list_vacio "list\\n" "\\(vacío\\)")

# TODO: añade al menos 8 tests más, uno por comportamiento del README:
#   add_ok, add_duplicado, add_negativo, add_uso, remove_ok, remove_inexistente,
#   find_ok, find_inexistente, total, list_con_registros.
# Firma esperada (CMake):
#   add_stdin_test(add_ok "add tornillo 12 0.15\\n" "ok: tornillo añadido")
#   add_stdin_test(total "add tornillo 12 0.15\\nadd tuerca 8 0.10\\ntotal\\n" "Valor total: 2\\.60 EUR")
# Pista: calcula el valor esperado a mano. En una expresión regular, el punto se
#        escapa como \\. y los paréntesis como \\( \\).
