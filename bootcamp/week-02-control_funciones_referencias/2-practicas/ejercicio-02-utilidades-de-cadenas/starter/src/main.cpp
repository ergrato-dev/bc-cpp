// Ejercicio 02 — Utilidades de cadenas
// Cada PASO tiene su código comentado. Descomenta en orden y ejecuta los tests.
// Todas las salidas van entre corchetes para que los espacios se vean.

#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// ============================================
// PASO 1: trim — recortar espacios por los dos lados
// ============================================
// Descomenta las siguientes líneas para el Paso 1:

// // Devuelve una vista sobre `text` sin espacios ni tabuladores en los extremos.
// // No copia: la vista apunta al texto del llamador, que sigue siendo el dueño.
// [[nodiscard]] std::string_view trim(std::string_view text) {
//   const std::size_t start{text.find_first_not_of(" \t")};
//   if (start == std::string_view::npos) {
//     return "";                                   // todo eran espacios (o nada)
//   }
//   const std::size_t end{text.find_last_not_of(" \t")};
//   return text.substr(start, end - start + 1);
// }

// ============================================
// PASO 2: to_upper — copia deliberada, modificación, devolución
// ============================================
// Descomenta las siguientes líneas para el Paso 2:

// // Recibe una copia (por valor), la pasa a mayúsculas y la devuelve.
// [[nodiscard]] std::string to_upper(std::string text) {
//   for (char& c : text) {                         // char&: modifica el de dentro
//     c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
//   }
//   return text;
// }

// ============================================
// PASO 3: split — partir por un separador en un vector
// ============================================
// Descomenta las siguientes líneas para el Paso 3:

// // "a,b,,c" con ',' → {"a", "b", "", "c"}. Los campos vacíos se conservan.
// [[nodiscard]] std::vector<std::string> split(std::string_view text, char separator) {
//   std::vector<std::string> parts{};
//   std::size_t start{0};
//   std::size_t pos{text.find(separator)};
//   while (pos != std::string_view::npos) {
//     parts.push_back(std::string{text.substr(start, pos - start)});
//     start = pos + 1;
//     pos = text.find(separator, start);
//   }
//   parts.push_back(std::string{text.substr(start)});  // el último campo
//   return parts;
// }

// ============================================
// PASO 4: join — la operación inversa
// ============================================
// Descomenta las siguientes líneas para el Paso 4:

// // {"x", "y", "z"} con "-" → "x-y-z". Sin separador delante del primero.
// [[nodiscard]] std::string join(const std::vector<std::string>& parts, std::string_view separator) {
//   std::string result{};
//   for (std::size_t i{0}; i < parts.size(); ++i) {
//     if (i > 0) {
//       result += separator;
//     }
//     result += parts[i];
//   }
//   return result;
// }

// ============================================
// PASO 5: replace_all — modificar en sitio a través de una referencia
// ============================================
// Descomenta las siguientes líneas para el Paso 5:

// // Sustituye todas las apariciones de `from` por `to`, en el propio `text`.
// void replace_all(std::string& text, std::string_view from, std::string_view to) {
//   if (from.empty()) {
//     return;                                      // buscar "" no termina nunca
//   }
//   std::size_t pos{text.find(from)};
//   while (pos != std::string::npos) {
//     text.replace(pos, from.size(), to);
//     pos = text.find(from, pos + to.size());      // seguir DESPUÉS de lo insertado
//   }
// }

int main() {
  // ============================================
  // PASO 1: trim
  // ============================================
  // Descomenta las siguientes líneas para el Paso 1:

  // std::cout << "trim: [" << trim("   hola mundo \t ") << "]\n";
  // std::cout << "trim vacio: [" << trim("") << "]\n";
  // std::cout << "trim espacios: [" << trim("   ") << "]\n";

  // ============================================
  // PASO 2: to_upper
  // ============================================
  // Descomenta las siguientes líneas para el Paso 2:

  // const std::string original{"hola mundo 42"};
  // std::cout << "upper: [" << to_upper(original) << "]\n";
  // std::cout << "original: [" << original << "]\n";  // intacto: to_upper recibió una copia

  // ============================================
  // PASO 3: split
  // ============================================
  // Descomenta las siguientes líneas para el Paso 3:

  // const std::vector<std::string> fields{split("a,b,,c", ',')};
  // std::cout << "split: " << fields.size() << " partes:";
  // for (const std::string& field : fields) {
  //   std::cout << " [" << field << "]";
  // }
  // std::cout << '\n';

  // ============================================
  // PASO 4: join
  // ============================================
  // Descomenta las siguientes líneas para el Paso 4:

  // const std::vector<std::string> words{"x", "y", "z"};
  // std::cout << "join: [" << join(words, "-") << "]\n";
  // std::cout << "join vacio: [" << join({}, "-") << "]\n";

  // ============================================
  // PASO 5: replace_all
  // ============================================
  // Descomenta las siguientes líneas para el Paso 5:

  // std::string phrase{"gato y gato"};
  // replace_all(phrase, "gato", "perro");
  // std::cout << "replace: [" << phrase << "]\n";
  // std::string fruit{"banana"};
  // replace_all(fruit, "a", "aa");                 // `to` contiene a `from`: no debe colgarse
  // std::cout << "replace ana: [" << fruit << "]\n";

  return 0;
}
