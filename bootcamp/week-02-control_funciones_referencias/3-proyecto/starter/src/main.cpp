// Proyecto — Semana 02: menú CRUD en memoria para tu dominio.
//
// NOTA PARA EL APRENDIZ: adapta `Item` a tu dominio (Book, Medicine, Member, Dish,
// Room...). Renombra el namespace, el struct, los campos y los mensajes. Los tres
// registros fijos de la Semana 01 desaparecen: ahora los registros entran por
// comandos, y cada comando se valida antes de tocar el vector.
//
// Comandos que el programa entiende (uno por línea):
//   add <name> <quantity> <price>   alta; falla si el nombre existe o hay negativos
//   remove <name>                   baja; falla si no existe
//   find <name>                     muestra un registro; falla si no existe
//   list                            tabla de todos los registros
//   total                           valor total (quantity * price) con dos decimales
//   help                            lista de comandos
//   quit                            termina

#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace inventory {   // NOTA PARA EL APRENDIZ: renombra al nombre de tu dominio

struct Item {
  std::string name;
  int quantity{0};
  double price{0.0};
};

// --- Búsqueda -------------------------------------------------------------
// TODO 1: devuelve la posición del registro con ese nombre, o items.size() si no está.
// Firma esperada:
//   [[nodiscard]] std::size_t find_index(const std::vector<Item>& items, std::string_view name);
// Pista: for con índice std::size_t; comparar items[i].name == name; return i.

// --- Alta -----------------------------------------------------------------
// TODO 2: añade el registro si el nombre no existe y quantity y price no son negativos.
// Devuelve true si lo añadió.
// Firma esperada:
//   [[nodiscard]] bool add_item(std::vector<Item>& items, const Item& item);
// Pista: find_index(items, item.name) != items.size() significa duplicado.

// --- Baja -----------------------------------------------------------------
// TODO 3: elimina el registro con ese nombre. Devuelve true si existía.
// Firma esperada:
//   [[nodiscard]] bool remove_item(std::vector<Item>& items, std::string_view name);
// Pista: items.erase(items.begin() + index). Cuidado: begin() + index necesita que
//        index sea válido; compruébalo antes.

// --- Listado (dado como ejemplo de formato) --------------------------------
void list_items(const std::vector<Item>& items) {
  if (items.empty()) {
    std::cout << "(vacío)\n";
    return;
  }
  std::cout << std::format("{:<12}{:>6}{:>10}\n", "nombre", "cant.", "precio");
  for (const Item& item : items) {
    std::cout << std::format("{:<12}{:>6}{:>10.2f}\n", item.name, item.quantity, item.price);
  }
}

// --- Valor total ----------------------------------------------------------
// TODO 4: suma quantity * price de todos los registros.
// Firma esperada:
//   [[nodiscard]] double total_value(const std::vector<Item>& items);
// Pista: for de rango con const Item&; acumular en un double.

enum class Command { add, remove, find, list, total, help, quit, unknown };

[[nodiscard]] Command parse_command(std::string_view word) {
  if (word == "add") {
    return Command::add;
  }
  if (word == "remove") {
    return Command::remove;
  }
  if (word == "find") {
    return Command::find;
  }
  if (word == "list") {
    return Command::list;
  }
  if (word == "total") {
    return Command::total;
  }
  if (word == "help") {
    return Command::help;
  }
  if (word == "quit") {
    return Command::quit;
  }
  return Command::unknown;
}

// --- Lectura validada de los argumentos de `add` ---------------------------
// TODO 5: lee "<name> <quantity> <price>" del flujo en `out`. Devuelve false si
// falta algo, si quantity o price no son números, o si sobran datos.
// Firma esperada:
//   [[nodiscard]] bool read_item(std::istringstream& in, Item& out);
// Pista: in >> out.name >> out.quantity >> out.price; luego in >> std::ws; in.eof().

}  // namespace inventory

int main() {
  std::vector<inventory::Item> items{};
  std::string line{};

  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream in{line};
    std::string word{};
    in >> word;
    const inventory::Command cmd{inventory::parse_command(word)};

    switch (cmd) {
      case inventory::Command::add: {
        // TODO 6: read_item; si falla, "error: uso: add <name> <quantity> <price>".
        // Si add_item devuelve false, "error: no se pudo añadir: <name>".
        // Si todo va bien, "ok: <name> añadido".
        break;
      }
      case inventory::Command::remove: {
        // TODO 7: leer el nombre (in >> name; si falla, "error: uso: remove <name>").
        // remove_item; "ok: <name> eliminado" o "error: no existe: <name>".
        break;
      }
      case inventory::Command::find: {
        // TODO 8: leer el nombre; find_index; imprimir con std::format
        // "<name> <quantity> <price con 2 decimales>" o "error: no existe: <name>".
        break;
      }
      case inventory::Command::list:
        inventory::list_items(items);
        break;
      case inventory::Command::total:
        // TODO 9: std::cout << std::format("Valor total: {:.2f} EUR\n", total_value(items));
        break;
      case inventory::Command::help:
        std::cout << "comandos: add remove find list total help quit\n";
        break;
      case inventory::Command::quit:
        std::cout << "adiós\n";
        return 0;
      case inventory::Command::unknown:
        std::cout << "error: comando desconocido: " << word << '\n';
        break;
    }
  }
  std::cout << "adiós\n";
  return 0;
}
