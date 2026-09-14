// Proyecto — Semana 01: esqueleto del sistema de tu dominio.
//
// NOTA PARA EL APRENDIZ: adapta `Item` a tu dominio (Book, Medicine, Member, Dish,
// Room...). Renombra el título del informe, las variables y los campos. Los tres
// registros van fijos en el código: la entrada del usuario y los ficheros llegan en
// semanas posteriores, cuando sepas validarlos.

#include <format>
#include <iostream>
#include <string>

int main() {
  // --- Constantes del dominio -----------------------------------------------
  // TODO 1: declara el nombre del recurso y la tasa de IVA como constantes.
  // Firma esperada:
  //   constexpr double kVatRate{0.21};
  //   const std::string kResourceName{"Item"};   // std::string no puede ser constexpr aquí
  // Pista: constexpr para lo que se conoce al compilar; const para el resto.

  // --- Tres registros fijos -------------------------------------------------
  // TODO 2: declara tres registros con nombre (std::string), cantidad (int) y
  // precio unitario (double), con inicialización uniforme {}.
  // Firma esperada (para Item; en tu dominio los campos cambian):
  //   std::string name_a{"tornillo"};  int qty_a{12};  double price_a{0.15};
  //   std::string name_b{"tuerca"};    int qty_b{8};   double price_b{0.10};
  //   std::string name_c{"arandela"};  int qty_c{7};   double price_c{0.05};
  // Pista: en Biblioteca, "cantidad" puede ser ejemplares y "precio" el de reposición.

  // --- Cabecera -------------------------------------------------------------
  // TODO 3: imprime la cabecera "=== Inventario de <recurso> ===" usando kResourceName.
  // Firma esperada de la salida:
  //   === Inventario de Item ===
  // Pista: std::cout << std::format("=== Inventario de {} ===\n", kResourceName);

  // --- Tabla ----------------------------------------------------------------
  // TODO 4: imprime una tabla con columnas nombre (ancho 12, izquierda),
  // cantidad (ancho 6, derecha) y precio (ancho 8, derecha, 2 decimales).
  // Firma esperada de la salida (con los datos de ejemplo):
  //   nombre       cant.  precio
  //   tornillo        12    0.15
  // Pista: std::format("{:<12}{:>6}{:>8.2f}\n", ...)

  // --- Estadísticas ---------------------------------------------------------
  // TODO 5: calcula e imprime:
  //   Total unidades: <suma de cantidades>
  //   Valor total: <suma de cantidad * precio, 2 decimales> EUR
  //   Valor con IVA: <valor total * (1 + kVatRate), 2 decimales> EUR
  //   Media de unidades: <total / 3, 2 decimales>
  // Pista: la media es una división REAL. Si divides dos int obtienes un int.
  //        static_cast<double>(total_units) / 3 — o divide entre 3.0.

  // --- Porcentaje -----------------------------------------------------------
  // TODO 6: imprime qué porcentaje del total de unidades representa el primer
  // registro, con un decimal: "tornillo: 44.4% del stock".
  // Pista: 100.0 * qty_a / total_units. El 100.0 (double) fuerza división real.

  return 0;
}
