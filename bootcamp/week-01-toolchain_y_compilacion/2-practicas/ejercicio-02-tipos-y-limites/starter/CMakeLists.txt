cmake_minimum_required(VERSION 3.28)
project(ejercicio_02_tipos_y_limites LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(app src/main.cpp)
target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Werror)

enable_testing()

add_test(NAME paso1_sizeof COMMAND app)
set_tests_properties(paso1_sizeof PROPERTIES
  PASS_REGULAR_EXPRESSION "sizeof\\(bool\\) = 1\nsizeof\\(char\\) = 1\nsizeof\\(int\\) = 4\nsizeof\\(long long\\) = 8\nsizeof\\(double\\) = 8")

add_test(NAME paso2_limites COMMAND app)
set_tests_properties(paso2_limites PROPERTIES
  PASS_REGULAR_EXPRESSION "int: -2147483648 \\.\\. 2147483647\nunsigned: 0 \\.\\. 4294967295")

add_test(NAME paso3_division COMMAND app)
set_tests_properties(paso3_division PROPERTIES
  PASS_REGULAR_EXPRESSION "7 / 2 = 3\n7 % 2 = 1\n7 / 2\\.0 = 3\\.5\nstatic_cast: 3\\.5")

add_test(NAME paso4_unsigned COMMAND app)
set_tests_properties(paso4_unsigned PROPERTIES
  PASS_REGULAR_EXPRESSION "0u - 1 = 4294967295")

add_test(NAME paso5_constantes COMMAND app)
set_tests_properties(paso5_constantes PROPERTIES
  PASS_REGULAR_EXPRESSION "capacidad: 100, precio con IVA: 12\\.10")
