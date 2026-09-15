# Control de flujo

> Hasta ahora tus programas eran una lista: primera línea, segunda, tercera, fin. Un
> programa útil decide y repite. Las cinco construcciones de este archivo son las
> únicas que necesitas para eso, y llevan cuarenta años sin cambiar de forma.

## 🎯 Objetivos

Al terminar este archivo podrás:

- Escribir un `if`/`else if`/`else` y explicar qué es una **condición** y por qué es un `bool`
- Elegir `switch` sobre un `enum class` cuando hay más de tres ramas, y marcar cada
  caída con `[[fallthrough]]` o `break`
- Distinguir `while`, `for` clásico y `for` de rango, y saber cuál pide cada situación
- Cortar un bucle con `break`, saltar una vuelta con `continue`, y saber cuándo eso
  aclara y cuándo enreda
- Reconocer los tres errores clásicos: `=` por `==`, caída entre `case` y el índice
  que se pasa por uno

## 1. Qué problema resuelve

Un programa sin bifurcaciones hace siempre lo mismo. Un programa sin bucles hace cada
cosa una sola vez. El procesador ejecuta instrucciones una detrás de otra; para que
"salte" a otra parte necesita una instrucción de salto, y para que ese salto dependa de
un dato necesita una comparación antes. Todo el control de flujo de C++ se traduce a
eso: **comparar y saltar**. Lo que el lenguaje añade son formas de escribirlo que no se
rompan cuando el programa crece.

Una **condición** es una expresión cuyo valor es `bool`: `true` o `false`. `x > 3` es
una condición. `x` a secas también lo es en C++ (cualquier número distinto de cero es
`true`), pero el bootcamp no lo usa: `if (count != 0)` dice lo que comprueba; `if
(count)` obliga a adivinarlo.

## 2. Cómo funciona

### 2.1 Bifurcar: `if` / `else`

```cpp
#include <iostream>

int main() {
  int stock{3};
  if (stock == 0) {
    std::cout << "agotado\n";
  } else if (stock < 5) {
    std::cout << "quedan pocos\n";
  } else {
    std::cout << "hay stock\n";
  }
}
```

Se evalúa la primera condición; si es `true`, se ejecuta su bloque y se salta el resto.
Si es `false`, se prueba la siguiente. El `else` final recoge lo que ninguna
condición atrapó. Un **bloque** es lo que va entre `{` y `}`: una o más sentencias que
se tratan como una sola.

Las llaves son obligatorias en el bootcamp aunque el bloque tenga una línea. La razón
es histórica y real: el bug *goto fail* de Apple (2014) fue un `if` sin llaves al que
alguien añadió una segunda línea que se ejecutaba siempre.

Desde C++17 un `if` puede declarar una variable que solo existe dentro de él:

```cpp
#include <iostream>
#include <string>

int main() {
  std::string line{"add 3 4"};
  if (auto pos{line.find(' ')}; pos != std::string::npos) {
    std::cout << "comando: " << line.substr(0, pos) << '\n';
  }
  // pos no existe aquí: no puede usarse por error más abajo
}
```

`std::string::npos` es el valor que `find` devuelve cuando no encuentra nada. Lo verás
a fondo en el archivo 04.

### 2.2 Elegir entre muchos: `switch` y `enum class`

Cuando una variable puede tomar un conjunto cerrado de valores (un comando, un estado,
un tipo de habitación), una cadena de `else if` funciona pero no dice que el conjunto es
cerrado. Para eso existe `enum class`: un tipo cuyos únicos valores son los que tú
nombras.

```cpp
#include <iostream>

enum class Command { add, remove, list, quit };

int main() {
  Command cmd{Command::list};
  switch (cmd) {
    case Command::add:
      std::cout << "alta\n";
      break;
    case Command::remove:
      std::cout << "baja\n";
      break;
    case Command::list:
      std::cout << "listado\n";
      break;
    case Command::quit:
      std::cout << "salir\n";
      break;
  }
}
```

`switch` compara `cmd` con cada `case` y salta al que coincide. Después **sigue
ejecutando hacia abajo** hasta encontrar un `break`: eso se llama *fallthrough* (caída)
y es la fuente de errores número uno de esta construcción. Cada `case` termina en
`break`, salvo que la caída sea deliberada, en cuyo caso se escribe:

```cpp
    case Command::add:
      [[fallthrough]];      // ✅ caída a propósito, y el compilador lo sabe
    case Command::remove:
```

`[[fallthrough]]` es un **atributo**: una anotación entre dobles corchetes que informa
al compilador de una intención. Aparecerán más (`[[nodiscard]]` en el archivo 02).

Un `switch` sobre un `enum class` **sin `default`** tiene una ventaja: si añades un
valor al `enum` y olvidas su `case`, GCC y Clang avisan con `-Wswitch` (dentro de
`-Wall`): `enumeration value 'undo' not handled in switch`. Con `-Werror`, no
compila. Un `default` silencia ese aviso; póngalo solo cuando de verdad todos los
valores no listados se tratan igual.

### 2.3 Repetir: `while` y `for`

`while` repite mientras la condición sea `true`. Se usa cuando **no sabes cuántas
vueltas** habrá: leer líneas hasta que se acaben, reintentar hasta que algo funcione.

```cpp
#include <iostream>
#include <string>

int main() {
  std::string line{};
  while (std::getline(std::cin, line)) {   // false cuando se acaba la entrada
    if (line == "quit") {
      break;                                // sale del bucle
    }
    if (line.empty()) {
      continue;                             // salta a la siguiente vuelta
    }
    std::cout << "leído: " << line << '\n';
  }
}
```

`std::getline` lee una línea entera de `std::cin` (hasta el salto de línea, que
descarta) y la deja en `line`. Devuelve algo que se convierte a `false` cuando no queda
nada que leer, así que el bucle termina solo cuando la entrada se acaba (Ctrl-D en la
terminal, fin de archivo en una tubería).

`for` clásico es un `while` con la inicialización, la condición y el avance en una
línea. Se usa cuando **sí sabes cuántas vueltas**: contar hasta `n`, recorrer índices.

```cpp
for (int i{0}; i < 5; ++i) {
  std::cout << i << ' ';                    // 0 1 2 3 4
}
```

`++i` suma uno a `i`. La condición se comprueba **antes** de cada vuelta, incluida la
primera: con `i < 0` el cuerpo no se ejecuta nunca.

### 2.4 Recorrer: `for` de rango

Cuando lo que quieres es "cada elemento de esta colección", el índice sobra:

```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> stock{12, 8, 7};
  int total{0};
  for (int units : stock) {                 // "para cada units en stock"
    total += units;
  }
  std::cout << total << '\n';               // 27
}
```

`std::vector` es una lista que crece sola; el archivo 05 es suyo. Lo que importa hoy:
el `for` de rango no puede pasarse de largo ni quedarse corto, porque no hay índice
que equivocar. Es la forma por defecto de recorrer en el bootcamp; el `for` clásico
queda para cuando el índice se usa de verdad (imprimir la posición, recorrer dos
colecciones a la vez).

## 3. Cómo se escribe en C++20

Reglas del bootcamp para que el control de flujo se lea de un vistazo:

```cpp
// ✅ condición explícita, llaves siempre, una comparación por línea
if (stock == 0) {
  return;
}

// ✅ switch sobre enum class, un break por case, sin default
switch (cmd) {
  case Command::add:
    add_item();
    break;
  case Command::quit:
    return;
}

// ✅ for de rango por defecto; clásico solo si usas el índice
for (const std::string& name : names) {
  std::cout << name << '\n';
}
for (std::size_t i{0}; i < names.size(); ++i) {
  std::cout << i << ": " << names[i] << '\n';
}
```

`const std::string&` en el `for` de rango significa "sin copiar cada elemento"; el
archivo 02 explica el `&`. `std::size_t` es el tipo que `size()` devuelve; usar `int`
como índice funciona pero dispara `-Wsign-compare` (`comparison of integer expressions
of different signedness`), y con `-Werror` no compila.

## 4. Antipatrones

| Qué hace la gente | Por qué duele | Qué hacer |
| --- | --- | --- |
| `if (x = 5)` | Asigna 5 a `x` y la condición es "5", o sea `true`, siempre. GCC: `suggest parentheses around assignment used as truth value [-Wparentheses]`; con `-Werror` no compila | `==`. Y leer los warnings |
| `case` sin `break` sin querer | El código del `case` siguiente se ejecuta también. GCC con `-Wextra`: `this statement may fall through [-Wimplicit-fallthrough=]` | `break` en cada `case`; `[[fallthrough]]` cuando la caída es deliberada |
| `switch` con `default: break;` "por si acaso" | Silencia `-Wswitch`: añades un valor al `enum` y nadie te avisa de que falta su rama | Sin `default` cuando el `switch` cubre un `enum class` |
| `for (int i = 0; i <= v.size(); ++i)` | `<=` visita `v[v.size()]`, una posición más allá del final: comportamiento indefinido (archivo 06) | `<`. O mejor, `for` de rango |
| `if (ok == true)` | `ok` ya es un `bool`; compararlo con `true` es preguntar si la verdad es verdad | `if (ok)`, `if (!ok)` |
| `while (true)` con un `break` enterrado | La condición de salida está escondida en el cuerpo; quien lee no sabe cuándo termina | Poner la condición en el `while`. `while (true)` solo si hay varias salidas y todas están a la vista |
| Anidar cuatro `if` | Cada nivel es una hipótesis más que el lector tiene que recordar | Salir pronto: `if (!valid) { return; }` y seguir en el nivel base |

## 5. Trucos

- **`-Wswitch` como lista de tareas** — cuando añadas un valor a un `enum class`,
  construye antes de tocar nada: cada `switch` incompleto aparece como error. El
  compilador te da la lista de sitios que hay que actualizar.
- **`if` con inicializador para acotar** — `if (auto pos{s.find(':')}; pos !=
  std::string::npos)` deja `pos` fuera del alcance del resto de la función. Menos
  variables vivas, menos formas de usarlas mal.
- **Contar vueltas sin romper nada** — un `std::cout << "vuelta " << i << '\n';` al
  principio del cuerpo es el depurador más barato que existe. Bórralo al terminar (con
  `-Werror` una variable de depuración sin usar no compila, así que no se te olvidará).
- **Salir de dos bucles anidados** — `break` solo sale del más interno. Extrae los
  bucles a una función y usa `return`; es más claro que una bandera `bool done`.

## 📚 Recursos Adicionales

- [cppreference — `if` statement](https://en.cppreference.com/w/cpp/language/if) —
  incluye el `if` con inicializador (C++17) y `if constexpr`, que verás en la Semana 12.
- [cppreference — `switch` statement](https://en.cppreference.com/w/cpp/language/switch) —
  la regla exacta de la caída entre `case`.
- [cppreference — Range-based for loop](https://en.cppreference.com/w/cpp/language/range-for) —
  qué hace de verdad el `for` de rango por debajo. Hoy basta con la primera sección.
- [C++ Core Guidelines — ES.70: Prefer a `switch`-statement to an `if`-statement when there is a choice](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es70-prefer-a-switch-statement-to-an-if-statement-when-there-is-a-choice) —
  y las vecinas ES.71 (`for` de rango) y ES.78 (no caer entre `case` sin marcarlo).

## ✅ Checklist de Verificación

- [ ] Sé qué es una condición y por qué escribo `count != 0` y no `count`
- [ ] Puedo escribir un `switch` sobre un `enum class` y sé qué pasa si olvido un `break`
- [ ] Sé por qué un `switch` sin `default` es más seguro que uno con él
- [ ] Sé cuándo usar `while`, cuándo `for` clásico y cuándo `for` de rango
- [ ] Sé qué hacen `break` y `continue`, y de cuántos bucles sale `break`
- [ ] He visto el warning de `if (x = 5)` y sé qué flag lo produce
