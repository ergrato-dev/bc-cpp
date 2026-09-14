// Ejercicio 02 — Tipos y límites
// Cada PASO tiene su código comentado. Descomenta en orden y ejecuta los tests.

#include <format>
#include <iostream>
#include <limits>

int main() {
  // ============================================
  // PASO 1: sizeof — cuántos bytes ocupa cada tipo
  // ============================================
  // Descomenta las siguientes líneas para el Paso 1:

  // std::cout << std::format("sizeof(bool) = {}\n", sizeof(bool));
  // std::cout << std::format("sizeof(char) = {}\n", sizeof(char));
  // std::cout << std::format("sizeof(int) = {}\n", sizeof(int));
  // std::cout << std::format("sizeof(long long) = {}\n", sizeof(long long));
  // std::cout << std::format("sizeof(double) = {}\n", sizeof(double));

  // ============================================
  // PASO 2: numeric_limits — el rango exacto
  // ============================================
  // Descomenta las siguientes líneas para el Paso 2:

  // std::cout << std::format("int: {} .. {}\n",
  //                          std::numeric_limits<int>::min(),
  //                          std::numeric_limits<int>::max());
  // std::cout << std::format("unsigned: {} .. {}\n",
  //                          std::numeric_limits<unsigned int>::min(),
  //                          std::numeric_limits<unsigned int>::max());

  // ============================================
  // PASO 3: División entera, resto y conversión explícita
  // ============================================
  // Descomenta las siguientes líneas para el Paso 3:

  // int a{7};
  // int b{2};
  // std::cout << std::format("7 / 2 = {}\n", a / b);        // ambos int: división entera
  // std::cout << std::format("7 % 2 = {}\n", a % b);        // resto
  // std::cout << std::format("7 / 2.0 = {}\n", a / 2.0);    // un double: división real
  // std::cout << std::format("static_cast: {}\n", static_cast<double>(a) / b);

  // ============================================
  // PASO 4: unsigned da la vuelta (definido) — signed no (UB)
  // ============================================
  // Descomenta las siguientes líneas para el Paso 4:

  // unsigned int u{0};
  // u = u - 1;                                              // definido: módulo 2^32
  // std::cout << std::format("0u - 1 = {}\n", u);

  // ============================================
  // PASO 5: constexpr, const y auto
  // ============================================
  // Descomenta las siguientes líneas para el Paso 5:

  // constexpr int kCapacity{100};                           // conocido al compilar
  // constexpr double kVatRate{0.21};
  // const double price{10.0};                               // no cambia tras nacer
  // auto price_with_vat{price * (1.0 + kVatRate)};          // auto deduce double
  // std::cout << std::format("capacidad: {}, precio con IVA: {:.2f}\n",
  //                          kCapacity, price_with_vat);

  return 0;
}
