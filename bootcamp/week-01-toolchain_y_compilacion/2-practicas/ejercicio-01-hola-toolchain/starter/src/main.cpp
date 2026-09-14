// Ejercicio 01 — Hola, toolchain
// Cada PASO tiene su código comentado. Descomenta en orden y ejecuta los tests.

#include <format>
#include <iostream>
#include <string>

int main() {
  // ============================================
  // PASO 1: Escribir en la salida estándar
  // ============================================
  // Descomenta las siguientes líneas para el Paso 1:

  // std::cout << "Hola, C++20\n";

  // ============================================
  // PASO 2: Variables tipadas y std::format
  // ============================================
  // Descomenta las siguientes líneas para el Paso 2:

  // int items{3};                       // cantidad: entero
  // double total{18.75};                // importe: real de doble precisión
  // std::cout << std::format("{} items en stock, total {:.2f} EUR\n", items, total);

  // ============================================
  // PASO 3: Una tabla alineada
  // ============================================
  // Descomenta las siguientes líneas para el Paso 3:

  // std::string first{"pan"};           // texto: std::string, no char*
  // std::string second{"leche"};
  // std::cout << std::format("{:<10}{:>6}{:>10}\n", "nombre", "cant.", "precio");
  // std::cout << std::format("{:<10}{:>6}{:>10.2f}\n", first, 3, 1.5);
  // std::cout << std::format("{:<10}{:>6}{:>10.2f}\n", second, 12, 0.89);

  // ============================================
  // PASO 4: Avisos a la salida de error
  // ============================================
  // Descomenta las siguientes líneas para el Paso 4:

  // std::cerr << "aviso: precios sin IVA\n";   // cerr: sin buffer, canal 2

  return 0;
}
