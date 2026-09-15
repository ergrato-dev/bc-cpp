# `std::vector` y agregados

> Tres registros fijos en `main` era el proyecto de la Semana 01. Un sistema real
> tiene los que hagan falta, y cada uno tiene varios campos. `std::vector` es la
> lista que crece sola; `struct` es el paquete que agrupa los campos. Juntos son el
> 80 % de las estructuras de datos que escribirás este año.

## 🎯 Objetivos

Al terminar este archivo podrás:

- Crear un `std::vector`, añadir con `push_back`, leer con `[]` y `at`, y recorrerlo
  con `for` de rango
- Borrar el último elemento y borrar por posición, y explicar qué pasa con los demás
- Definir un `struct` como **agregado** (paquete de campos sin lógica) e
  inicializarlo con **inicializadores designados** de C++20
- Guardar agregados en un `vector`, buscarlos por campo y modificarlos a través de
  una referencia
- Explicar por qué una referencia a un elemento deja de valer después de un `push_back`

## 1. Qué problema resuelve

Un programa que gestiona "tres tornillos" no gestiona nada: gestiona tres variables.
Un inventario tiene los artículos que tenga, y ese número cambia mientras el programa
corre. Necesitas una colección que **crezca** al añadir y que sepa **cuántos** tiene.
En C eso era un array de tamaño fijo o memoria pedida a mano, con el programador
contando y liberando. `std::vector` hace las dos cosas solo: reserva más memoria
cuando se llena y la libera al morir (por RAII, que verás con nombre en la Semana 04).

Y cada artículo no es un número: es un nombre, una cantidad y un precio que van
**juntos**. Tres `vector` paralelos (`names`, `quantities`, `prices`) se desincronizan
en cuanto borras de uno y no del otro. Un `struct` empaqueta los tres campos en un
solo tipo, y un `vector` de ese tipo mantiene cada registro entero.

## 2. Cómo funciona

### 2.1 Crear, añadir, medir, recorrer

```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> stock{12, 8, 7};     // tres elementos
  stock.push_back(20);                  // cuatro: se añade al final
  std::cout << stock.size() << '\n';    // 4
  std::cout << stock[0] << ' ' << stock.back() << '\n';   // 12 20
  int total{0};
  for (int units : stock) {
    total += units;
  }
  std::cout << total << '\n';           // 47
  std::cout << stock.empty() << '\n';   // 0
}
```

`std::vector<int>` se lee "vector de `int`": el tipo entre ángulos es el de los
elementos, y todos son de ese tipo. Los elementos viven **contiguos** en memoria, uno
detrás de otro, como los bytes de un `int` en el diagrama de la Semana 01. Por eso
`stock[2]` es inmediato: el programa calcula la dirección sumando `2 × sizeof(int)`
al principio. Y por eso `stock[99]` en un vector de cuatro es UB: calcula una
dirección más allá de lo reservado y la lee igual.

`at(i)` hace lo mismo que `[i]` pero **comprueba** el índice y aborta si se pasa (lanza
una excepción, Semana 10). Hasta entonces, la regla: `[]` cuando el índice sale de un
`for` sobre `size()`; `at` cuando viene de fuera (del usuario, de un cálculo).

### 2.2 Modificar a través de una referencia

El `for` de rango con `int units` **copia** cada elemento; modificar `units` no toca
el vector. Con `int&` sí:

```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> prices_cents{150, 89, 320};
  for (int& price : prices_cents) {     // referencia: cada price ES el elemento
    price += 10;
  }
  for (const int& price : prices_cents) {   // const&: leer sin copiar (aquí da igual: int)
    std::cout << price << ' ';          // 160 99 330
  }
  std::cout << '\n';
}
```

Con `int` da igual copiar; con un `struct` de tres campos o un `std::string`, no. La
regla del archivo 02 aplica: `const T&` para leer, `T&` para modificar, valor solo
para tipos pequeños.

### 2.3 Borrar

```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> stock{12, 8, 7, 20};
  stock.pop_back();                             // quita el último: {12, 8, 7}
  stock.erase(stock.begin() + 1);               // quita la posición 1: {12, 7}
  for (int units : stock) {
    std::cout << units << ' ';
  }
  std::cout << '\n';
  stock.clear();                                // {}
  std::cout << stock.size() << '\n';            // 0
}
```

`erase` recibe una **posición** en forma de *iterador*: `stock.begin()` es la
posición del primer elemento y `+ 1` la siguiente. Los iteradores son el tema de la
Semana 08; hoy basta con `begin() + i` para "la posición `i`". Al borrar del medio,
los elementos posteriores **se desplazan** una posición hacia atrás para cerrar el
hueco: borrar el primero de un millón mueve 999.999. Es correcto y es lento; cuando
importe, la Semana 08 da alternativas.

### 2.4 `struct`: un paquete de campos

Un **agregado** es un tipo que solo agrupa datos: campos públicos, sin lógica, sin
reglas que proteger. Se declara con `struct`:

```cpp
#include <format>
#include <iostream>
#include <string>

struct Item {
  std::string name;
  int quantity{0};       // valor por defecto si no se da
  double price{0.0};
};

int main() {
  Item bolt{.name = "tornillo", .quantity = 12, .price = 0.15};   // designados (C++20)
  Item empty{};                                                   // "", 0, 0.0
  bolt.quantity -= 2;
  std::cout << std::format("{} x{} a {:.2f}\n", bolt.name, bolt.quantity, bolt.price);
  std::cout << empty.name.empty() << '\n';   // 1
}
```

`.name = "tornillo"` es un **inicializador designado** (C++20): nombra el campo que
inicializa. Se leen sin abrir la definición del `struct`, y el compilador rechaza el
orden equivocado: GCC, `error: designator order for field 'Item::name' does not match
declaration order in 'Item'`; Clang lo trata como warning (`-Wreorder-init-list`), que
con `-Werror` también es error. Los campos se acceden con `.`: `bolt.quantity`.

Un `struct` así **no tiene invariantes**: nada impide `bolt.quantity = -5`. Cuando un
tipo tenga reglas que cumplir ("la cantidad nunca es negativa") necesitará un
constructor que las imponga, y eso es una `class` (Semana 04). Hasta entonces, la
regla se comprueba en la función que modifica el campo.

### 2.5 `vector` de agregados

```cpp
#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct Item {
  std::string name;
  int quantity{0};
};

// Devuelve la posición del item con ese nombre, o items.size() si no está.
[[nodiscard]] std::size_t find_index(const std::vector<Item>& items, std::string_view name) {
  for (std::size_t i{0}; i < items.size(); ++i) {
    if (items[i].name == name) {
      return i;
    }
  }
  return items.size();
}

int main() {
  std::vector<Item> items{};
  items.push_back({.name = "tornillo", .quantity = 12});
  items.push_back({.name = "tuerca", .quantity = 8});

  const std::size_t pos{find_index(items, "tuerca")};
  if (pos != items.size()) {
    Item& found{items[pos]};                  // referencia: modifica el del vector
    found.quantity += 5;
  }
  for (const Item& item : items) {            // const&: sin copiar cada struct
    std::cout << std::format("{:<10}{:>4}\n", item.name, item.quantity);
  }
}
```

"No encontrado" se codifica devolviendo `items.size()`, una posición que nunca es
válida. Es la convención de `find` en `std::string` (`npos`) llevada al vector; en la
Semana 10 la sustituirás por `std::optional`, que dice lo mismo con tipo.

### 2.6 La referencia que deja de valer

```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v{1, 2, 3};
  int& first{v[0]};
  v.push_back(4);               // puede mover los tres elementos a otra memoria
  std::cout << first << '\n';   // ❌ UB: first apunta a la memoria vieja. ASan: heap-use-after-free
}
```

Cuando un `vector` se llena, reserva un bloque **más grande en otro sitio**, copia
los elementos y libera el viejo. Toda referencia (y todo iterador) a los elementos
antiguos queda colgante. Es la versión con `vector` de la referencia a una local del
archivo 03, y el compilador no la ve. Regla: **no guardes referencias a elementos de
un `vector` que vaya a crecer**; guarda el índice y vuelve a indexar.

## 3. Cómo se escribe en C++20

```cpp
#include <string>
#include <string_view>
#include <vector>

struct Item {
  std::string name;
  int quantity{0};             // ✅ cada campo con valor por defecto
  double price{0.0};
};

// ✅ el vector por const& para leer, por & para modificar
[[nodiscard]] double total_value(const std::vector<Item>& items);
[[nodiscard]] bool add_item(std::vector<Item>& items, const Item& item);   // false si ya existe
[[nodiscard]] bool remove_item(std::vector<Item>& items, std::string_view name);
[[nodiscard]] std::size_t find_index(const std::vector<Item>& items, std::string_view name);
void list_items(const std::vector<Item>& items);
```

`Item` se pasa por `const&` (tres campos, uno de ellos un `std::string`: no es
pequeño). El `vector` **nunca** se pasa por valor: sería copiar todos los registros.

## 4. Antipatrones

| Qué hace la gente | Por qué duele | Qué hacer |
| --- | --- | --- |
| `std::vector<std::string> names; std::vector<int> qtys;` en paralelo | Borras de uno y no del otro; el índice 3 ya no es el mismo registro | Un `struct` y un solo `vector` |
| `for (int i = 0; i <= v.size(); ++i)` | Visita `v[v.size()]`: fuera del vector. UB; ASan: `heap-buffer-overflow` | `<`, o `for` de rango |
| `void process(std::vector<Item> items)` | Copia todos los registros en cada llamada | `const std::vector<Item>&` |
| `Item& it{v[0]}; v.push_back(...); it.quantity++;` | La referencia queda colgante si el vector se reubica. UB sin aviso | Guardar el índice, no la referencia |
| `v[idx]` con `idx` leído del usuario sin comprobar | Un índice fuera de rango es UB en silencio | `if (idx < v.size())` antes, o `v.at(idx)` |
| Borrar dentro de un `for` de rango sobre el mismo vector | El `for` de rango sigue mirando posiciones que se han desplazado: UB | Recorrer por índice hacia atrás, o construir un vector nuevo con lo que se queda |
| `struct` con un campo sin valor por defecto (`int quantity;`) | `Item x{};` lo pone a 0, pero `Item x;` lo deja con basura | `int quantity{0};` en la definición |

## 5. Trucos

- **`-D_GLIBCXX_ASSERTIONS`** — con libstdc++ (GCC), convierte `v[i]` fuera de rango
  en un abort con mensaje: `Assertion '__n < this->size()' failed`. Añádelo a
  `target_compile_definitions` en el preset `debug`; el starter del proyecto ya lo
  lleva.
- **Ver un vector en `gdb`** — `print items` muestra los elementos; `print
  items.size()` y `print items[1].name` también funcionan en GCC con los *pretty
  printers* de libstdc++, que vienen instalados con el compilador.
- **`reserve` cuando sabes cuántos vendrán** — `items.reserve(1000)` pide memoria
  para mil de golpe; los siguientes `push_back` no reubican. Solo cuando lo midas
  (Semana 15); hoy es solo para saber que existe.
- **`{}` para "vacío"** — `std::vector<Item> items{};` es un vector sin elementos.
  `std::vector<int> v(5)` (paréntesis) son **cinco ceros**; `std::vector<int> v{5}`
  (llaves) es **un elemento que vale 5**. Fíjate en el paréntesis.

## 📚 Recursos Adicionales

- [cppreference — `std::vector`](https://en.cppreference.com/w/cpp/container/vector) —
  hoy: `push_back`, `pop_back`, `size`, `empty`, `operator[]`, `at`, `back`, `erase`,
  `clear`. La sección *Iterator invalidation* es la tabla formal de la sección 2.6.
- [cppreference — Aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization) —
  qué es un agregado y los inicializadores designados (C++20).
- [cppreference — Class declaration (`struct`)](https://en.cppreference.com/w/cpp/language/class) —
  solo la diferencia entre `struct` y `class`: el acceso por defecto. Lo demás es de la
  Semana 04.
- [C++ Core Guidelines — SL.con.2: Prefer using STL `vector` by default](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#slcon2-prefer-using-stl-vector-by-default-unless-you-have-a-reason-to-use-a-different-container) —
  y C.2 (`struct` si los campos varían libremente; `class` si hay invariantes).

## ✅ Checklist de Verificación

- [ ] Sé crear un `vector`, añadir, medir, recorrer y borrar el último y por posición
- [ ] Sé qué diferencia hay entre `v[i]` y `v.at(i)` y cuándo usar cada uno
- [ ] Puedo definir un `struct` con valores por defecto e inicializarlo con `.campo =`
- [ ] Sé escribir `find_index` y por qué devuelve `size()` cuando no encuentra
- [ ] Sé por qué una referencia a un elemento deja de valer tras un `push_back`
- [ ] Sé qué pasa con los elementos posteriores al hacer `erase` en el medio
