cmake_minimum_required(VERSION 3.28)
project(ejercicio_01_interprete_de_comandos LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)   # -std=c++20, no -std=gnu++20

add_executable(app src/main.cpp)
target_compile_features(app PUBLIC cxx_std_20)
# -Wshadow se añade desde esta semana: no está en -Wall ni en -Wextra.
target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Werror)

# Tests de las semanas 01-03: ejecutan el programa y comprueban su salida.
# Esta semana el programa lee de stdin, así que cada test le entrega su entrada
# por una tubería: printf 'línea1\nlínea2\n' | app
enable_testing()

function(add_stdin_test name input regex)
  add_test(NAME ${name} COMMAND sh -c "printf '${input}' | $<TARGET_FILE:app>")
  set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION "${regex}")
endfunction()

# Paso 1: sin entrada, el programa termina y se despide.
add_stdin_test(paso1_adios "" "adiós")

# Paso 2: help responde, un comando desconocido avisa, y quit corta la entrada
# (la segunda línea `help` no debe llegar a ejecutarse).
add_stdin_test(paso2_help_y_quit "help\\nfoo\\nquit\\nhelp\\n"
  "comandos: add sub mul (div )?help quit\nerror: comando desconocido: foo\nadiós")
set_tests_properties(paso2_help_y_quit PROPERTIES FAIL_REGULAR_EXPRESSION "adiós\ncomandos")

# Paso 3: aritmética con dos operandos.
add_stdin_test(paso3_aritmetica "add 3 4\\nsub 10 4\\nmul 6 7\\n" "= 7\n= 6\n= 42")

# Paso 4: la entrada se valida: faltan operandos, no son enteros, o sobran.
add_stdin_test(paso4_validacion "add 3\\nadd 3 x\\nadd 3 4 5\\nadd 3 4\\n"
  "error: se esperaban dos enteros\nerror: se esperaban dos enteros\nerror: se esperaban dos enteros\n= 7")

# Paso 5: división entera y división entre cero rechazada antes de dividir.
add_stdin_test(paso5_div "div 7 2\\ndiv 7 0\\n" "= 3\nerror: división entre cero")
