// Ejercicio 01 — Intérprete de comandos
// Cada PASO tiene su código comentado. Descomenta en orden y ejecuta los tests.
// El programa lee líneas de la entrada estándar (stdin) y responde a cada una.

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

// ============================================
// PASO 2: enum class Command y parse_command
// ============================================
// Descomenta las siguientes líneas para el Paso 2:

// enum class Command { add, sub, mul, help, quit, unknown };
//
// // Convierte la primera palabra de la línea en un Command.
// [[nodiscard]] Command parse_command(std::string_view word) {
//   if (word == "add") {
//     return Command::add;
//   }
//   if (word == "sub") {
//     return Command::sub;
//   }
//   if (word == "mul") {
//     return Command::mul;
//   }
//   // ---- PASO 5: descomenta cuando añadas `div` al enum ----
//   // if (word == "div") {
//   //   return Command::div;
//   // }
//   if (word == "help") {
//     return Command::help;
//   }
//   if (word == "quit") {
//     return Command::quit;
//   }
//   return Command::unknown;
// }

// ============================================
// PASO 3: read_operands (referencias de salida) y apply
// ============================================
// Descomenta las siguientes líneas para el Paso 3:

// // Lee dos enteros del resto de la línea. Devuelve false si faltan o no son enteros.
// // `a` y `b` son referencias: la función escribe en las variables del llamador.
// [[nodiscard]] bool read_operands(std::istringstream& in, int& a, int& b) {
//   if (!(in >> a >> b)) {
//     return false;
//   }
//   // ---- PASO 4: descomenta para rechazar datos sobrantes ("add 3 4 5") ----
//   // in >> std::ws;          // salta espacios finales
//   // if (!in.eof()) {        // queda algo que no se ha leído
//   //   return false;
//   // }
//   return true;
// }
//
// // Aplica la operación. Solo se llama con comandos aritméticos; los demás se
// // listan para que -Wswitch siga avisando si el enum crece.
// [[nodiscard]] int apply(Command cmd, int a, int b) {
//   switch (cmd) {
//     case Command::add:
//       return a + b;
//     case Command::sub:
//       return a - b;
//     case Command::mul:
//       return a * b;
//     // ---- PASO 5: descomenta cuando añadas `div` al enum ----
//     // case Command::div:
//     //   return a / b;       // main comprueba b != 0 antes de llamar
//     case Command::help:
//     case Command::quit:
//     case Command::unknown:
//       return 0;
//   }
//   return 0;
// }

int main() {
  // ============================================
  // PASO 1: el bucle de lectura
  // ============================================
  // Descomenta las siguientes líneas para el Paso 1:

  // std::string line{};
  // while (std::getline(std::cin, line)) {   // false cuando se acaba la entrada
  //   if (line.empty()) {
  //     continue;                             // línea en blanco: siguiente
  //   }
  //
  //   // ============================================
  //   // PASO 2: partir la línea y despachar con switch
  //   // ============================================
  //   // Descomenta las siguientes líneas para el Paso 2:
  //
  //   // std::istringstream iss{line};
  //   // std::string word{};
  //   // iss >> word;                          // la primera palabra es el comando
  //   // const Command cmd{parse_command(word)};
  //   // switch (cmd) {
  //   //   case Command::help:
  //   //     std::cout << "comandos: add sub mul help quit\n";
  //   //     break;
  //   //   case Command::quit:
  //   //     std::cout << "adiós\n";
  //   //     return 0;
  //   //   case Command::unknown:
  //   //     std::cout << "error: comando desconocido: " << word << '\n';
  //   //     break;
  //   //   case Command::add:
  //   //   case Command::sub:
  //   //   case Command::mul:
  //   //   // ---- PASO 5: descomenta cuando añadas `div` al enum ----
  //   //   // case Command::div:
  //   //   {
  //   //     // ============================================
  //   //     // PASO 3: leer operandos y calcular
  //   //     // ============================================
  //   //     // Descomenta las siguientes líneas para el Paso 3:
  //   //
  //   //     // int a{};
  //   //     // int b{};
  //   //     // if (!read_operands(iss, a, b)) {
  //   //     //   std::cout << "error: se esperaban dos enteros\n";
  //   //     //   break;
  //   //     // }
  //   //     // // ---- PASO 5: descomenta cuando añadas `div` ----
  //   //     // // if (cmd == Command::div && b == 0) {
  //   //     // //   std::cout << "error: división entre cero\n";
  //   //     // //   break;
  //   //     // // }
  //   //     // std::cout << "= " << apply(cmd, a, b) << '\n';
  //   //     break;
  //   //   }
  //   // }
  // }
  // std::cout << "adiós\n";                   // se acabó la entrada sin `quit`

  return 0;
}
