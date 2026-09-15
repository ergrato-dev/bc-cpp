# Comportamiento indefinido

> En la mayoría de los lenguajes, un error de programa produce un error. En C++, un
> error de cierta clase produce **cualquier cosa**: el resultado correcto, uno
> incorrecto, un cierre, o un programa que funciona un año y falla el día de la
> demo. Esa clase tiene nombre, tiene un mapa, y tiene herramientas que la detectan.

## 🎯 Objetivos

Al terminar este archivo podrás:

- Definir **comportamiento indefinido** (UB) y distinguirlo de *definido por la
  implementación* y de *no especificado*
- Explicar **por qué** existe el UB en C++ y qué hace el compilador cuando lo asume
  imposible
- Reconocer las **cinco trampas** de esta semana en código ajeno
- Nombrar para cada una el warning, el flag o el sanitizer que la detecta
- Rebatir "funciona en mi máquina" con un argumento técnico

## 1. Qué problema resuelve

El estándar de C++ es un contrato entre tú y el compilador. Para cada construcción
dice qué debe pasar. Pero hay operaciones cuyo resultado depende del hardware (¿qué
pasa al sumar uno al mayor `int`?), o cuya comprobación costaría tiempo en **cada**
ejecución (¿está este índice dentro del vector?). El comité tenía dos opciones: obligar
a comprobar siempre, y pagar el coste en todos los programas, o declarar que el
programa **nunca** hace eso y dejar la responsabilidad al programador. C++ eligió lo
segundo. Ese "nunca hace eso" es el **comportamiento indefinido** (*undefined
behavior*, UB): el estándar **no impone ningún requisito** a lo que ocurre después.

Es la razón de que C++ sea rápido, y la razón de que necesite sanitizers. Este
archivo no te enseña a memorizar la lista de UB (tiene cientos de entradas); te
enseña a reconocer las cinco formas que vas a escribir tú esta semana y a activar lo
que las detecta.

## 2. Cómo funciona

### 2.1 El mapa: cuatro grados de definición

| Grado | Qué garantiza el estándar | Ejemplo |
| --- | --- | --- |
| **Definido** | Un único resultado, en todas las plataformas | `unsigned u{0}; u - 1` da la vuelta (módulo 2^N, N = bits de `unsigned`; 4294967295 con 32 bits) |
| **Definido por la implementación** (*implementation-defined*) | El compilador elige, y **lo documenta** | `sizeof(int)`: 4 en GCC x86-64, y está escrito |
| **No especificado** (*unspecified*) | Una de varias opciones válidas, sin obligación de decir cuál ni de ser consistente | El orden en que se evalúan `f()` y `g()` en `f() + g()` |
| **Indefinido** (*undefined*) | **Nada.** Ni un resultado, ni un error, ni que el programa siga | `int i{INT_MAX}; i + 1`; `v[v.size()]`; leer una variable sin inicializar |

Los tres primeros son portabilidad: tu programa es correcto, puede comportarse
distinto en otra máquina. El cuarto es corrección: tu programa **no es un programa
C++ válido**, aunque compile y aunque hoy imprima lo que esperabas.

### 2.2 Lo que hace el compilador con el UB

El compilador **asume que el UB no ocurre** y optimiza en consecuencia. No es
malicia: es la única lectura posible del contrato. Este ejemplo es real:

```cpp
#include <iostream>
#include <limits>

bool fits_one_more(int x) {
  return x + 1 > x;             // ❌ UB si x == INT_MAX (desbordamiento con signo)
}

int main() {
  int max{std::numeric_limits<int>::max()};
  std::cout << fits_one_more(max) << '\n';
}
```

Como `x + 1` **nunca** desborda (eso sería UB, y el UB no ocurre), `x + 1 > x` es
siempre `true`, y el compilador puede sustituir la función entera por `return true;`.
Verificado con GCC 13.4 y Clang 17.0.6, septiembre de 2026:

| Compilador y flags | Imprime | UBSan |
| --- | --- | --- |
| `clang++ -O0` | `0` (la suma dio la vuelta) | `runtime error: signed integer overflow` |
| `clang++ -O2` | `1` | `runtime error: signed integer overflow` (instrumenta antes de optimizar) |
| `g++ -O0` | `1` (ya simplificó a `true`) | nada: la suma ya no existe |
| `g++ -O2` | `1` | nada |

Un mismo programa, dos respuestas, y el sanitizer solo lo ve en dos de las cuatro
combinaciones: GCC elimina la suma antes de que UBSan pueda vigilarla. Eso es lo que significa "indefinido": **no hay una respuesta que
esperar**, y "funciona en mi máquina" solo dice qué hizo tu compilador, hoy, con tus
flags.

### 2.3 Las cinco trampas de esta semana

Cada una viene de algo que has aprendido esta semana. Cada una lleva su detector.

**1. Índice fuera de rango** (archivos 04 y 05)

```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> stock{12, 8, 7};
  std::size_t index{0};
  std::cin >> index;
  std::cout << stock[index] << '\n';   // ❌ UB si index >= 3: lee memoria ajena
}
```

Detecta: ASan (`heap-buffer-overflow`) en el preset `asan`; `-D_GLIBCXX_ASSERTIONS`
(`Assertion '__n < this->size()' failed`) sin sanitizer; `stock.at(index)` aborta
siempre. Evita: comprobar `index < stock.size()` **antes**, siempre que el índice
venga de fuera.

**2. Desbordamiento con signo** (Semana 01, archivo 05 al sumar cantidades)

```cpp
#include <iostream>
#include <limits>

int main() {
  int total{std::numeric_limits<int>::max()};
  total += 1;                          // ❌ UB: signed integer overflow
  std::cout << total << '\n';
}
```

Detecta: UBSan (`runtime error: signed integer overflow: 2147483647 + 1 cannot be
represented in type 'int'`) mientras el compilador no lo haya simplificado. Evita:
`long long` cuando la suma pueda crecer; comprobar antes de sumar cuando el dato es
del usuario.

**3. Variable sin inicializar** (Semana 01, y cada `int total;` que se te escape)

```cpp
#include <iostream>

int main() {
  int total;                           // ❌ UB al leerla: no tiene valor, tiene basura
  for (int i{0}; i < 3; ++i) {
    total += i;
  }
  std::cout << total << '\n';          // 3, 4, 32771... lo que hubiera en la pila
}
```

Detecta: Clang, `-Wuninitialized` (en `-Wall`), siempre. GCC, **solo con
optimización** (`-O1` o más): a `-O0` este programa compila limpio e imprime basura.
MemorySanitizer (`-fsanitize=memory`, solo Clang) lo caza en ejecución. Evita: `{}`
en toda declaración; `int total{0};`. Es la regla más barata del bootcamp.

**4. Referencia colgante** (archivos 03, 04 y 05)

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string make_label() { return "temporal"; }

int main() {
  std::string_view view{make_label()};   // ❌ UB: el string muere al final de la línea
  std::cout << view << '\n';             //    ASan: stack-use-after-scope
}
```

Tres variantes, un mismo error: devolver una referencia a una local (el compilador
avisa: `-Wreturn-local-addr` en GCC, `-Wreturn-stack-address` en Clang), una vista
sobre un temporal (nadie avisa), y una referencia a un elemento de un `vector` que
luego crece (nadie avisa; ASan: `heap-use-after-free`). Detecta: ASan, en los tres
casos. Evita: devolver por valor; `std::string_view` solo como parámetro; índices
en vez de referencias a elementos de un `vector`.

**5. División entre cero** (ejercicio 01, en cuanto el usuario escriba `div 7 0`)

```cpp
#include <iostream>

int main() {
  int units{7};
  int groups{0};
  std::cin >> groups;
  std::cout << units / groups << '\n';   // ❌ UB si groups == 0
}
```

Detecta: UBSan (`runtime error: division by zero`), y sin él, casi siempre un
`Floating point exception` del sistema, que es una casualidad del hardware, no una
garantía. Evita: `if (groups == 0)` antes de dividir. Con `double`, `7.0 / 0.0` **no**
es UB si el tipo cumple IEEE 754 (`std::numeric_limits<double>::is_iec559`, `true` en
GCC y Clang x86-64): da `inf`.

## 3. Cómo se escribe en C++20

No hay sintaxis para el UB; hay hábitos que lo excluyen. Los de esta semana:

```cpp
#include <string_view>
#include <vector>

struct Item { int quantity{0}; };                    // ✅ todo con valor por defecto

[[nodiscard]] bool take(std::vector<Item>& items, std::size_t index, int units) {
  if (index >= items.size()) {                       // ✅ comprobar antes de indexar
    return false;
  }
  if (units < 0 || units > items[index].quantity) {  // ✅ validar el dato de fuera
    return false;
  }
  items[index].quantity -= units;
  return true;
}
```

Y en el `CMakeLists.txt`: el preset `asan` en cada `ctest`, `-D_GLIBCXX_ASSERTIONS`
en `debug`. El código del bootcamp no se entrega si el sanitizer habla.

## 4. Antipatrones

| Qué dice la gente | Por qué no vale | Qué hacer |
| --- | --- | --- |
| "Funciona en mi máquina" | Dice qué hizo un compilador con unos flags un día. El UB no promete repetirlo | Ejecutar con `asan`; si el sanitizer calla y el código es correcto, entonces sí |
| "Compila sin warnings, así que está bien" | Los warnings cazan una fracción del UB (uninit, return-local). El índice fuera de rango y la vista colgante compilan limpios | Warnings **y** sanitizers **y** tests |
| "Lo ejecuté diez veces y siempre da 3" | El UB puede ser determinista hoy y cambiar con `-O2`, con otro compilador o al añadir una línea antes | Igual: sanitizers |
| "El desbordamiento da la vuelta, como en `unsigned`" | Con signo **no** está definido; el compilador asume que no pasa y elimina tus comprobaciones | `unsigned` solo para bits; `long long` o comprobar antes |
| "Pongo `default:` con un valor seguro y listo" | No es UB, pero esconde el error real: el `switch` incompleto (archivo 01) | Sin `default`; que `-Wswitch` avise |
| "Es UB, pero es rápido" | El compilador optimiza **asumiendo que no hay UB**; un programa con UB no es más rápido, es incorrecto | Escribir el código correcto y medir (Semana 15) |

## 5. Trucos

- **Dos presets, siempre** — `ctest --preset debug` y `ctest --preset asan`. El
  segundo es el que encuentra las trampas 1, 4 y 5. Tarda el doble; vale el triple.
- **Leer un reporte de ASan** — la primera línea dice **qué** (`heap-buffer-overflow`);
  la primera línea con `#0` que apunte a **tu** archivo dice **dónde**. El resto es
  contexto. Con `-g` (los presets `debug` y `asan` lo llevan) sale el número de línea.
- **`-fsanitize=undefined` avisa, no para** — por defecto UBSan imprime y sigue. Para
  que aborte en el primer error (y `ctest` lo cuente como fallo): `UBSAN_OPTIONS=halt_on_error=1`.
- **`-O2` como segundo compilador** — si un programa se comporta distinto con `-O0` y
  con `-O2`, casi seguro tiene UB. Es una prueba gratis: `cmake --preset release`.
- **Compiler Explorer para ver la asunción** — pega `fits_one_more` con `-O2`: el
  ensamblador es `mov eax, 1; ret`. Ver la comparación desaparecer enseña más que
  cualquier explicación.

## 📚 Recursos Adicionales

- [cppreference — Undefined behavior](https://en.cppreference.com/w/cpp/language/ub) —
  la definición de los cuatro grados y una lista de ejemplos con lo que el compilador
  hace con ellos. Es **la** página de este archivo.
- [Clang — UndefinedBehaviorSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html) —
  la lista de comprobaciones de UBSan y las opciones de ejecución. Vale también para
  GCC.
- [Clang — AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) —
  qué detecta ASan y qué no (no detecta uninit: eso es MSan).
- [John Regehr — *A Guide to Undefined Behavior in C and C++*](https://blog.regehr.org/archives/213) —
  tres partes, de 2010 y vigentes. La mejor explicación escrita de por qué el compilador
  hace lo que hace con el UB.
- [C++ Core Guidelines — ES.20: Always initialize an object](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es20-always-initialize-an-object) —
  y ES.103 (no desbordar), ES.105 (no dividir entre cero), ES.65 (no desreferenciar
  lo inválido).

## ✅ Checklist de Verificación

- [ ] Puedo definir UB y dar un ejemplo de cada uno de los otros tres grados
- [ ] Sé por qué el compilador asume que el UB no ocurre y qué hace con `x + 1 > x`
- [ ] Reconozco las cinco trampas y sé cuál avisa el compilador, cuál ASan y cuál UBSan
- [ ] Sé qué detecta `-D_GLIBCXX_ASSERTIONS` y en qué se diferencia de ASan
- [ ] Sé por qué "funciona en mi máquina" no demuestra nada y qué sí lo demuestra
- [ ] Sé qué hace `UBSAN_OPTIONS=halt_on_error=1` y cuándo usarlo
