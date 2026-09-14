---
name: verificar-progresion
description: Comprueba que una semana del bootcamp C++ no usa ningún concepto que se enseña en una semana posterior (smart pointers, templates, lambdas, excepciones, threads...). Úsalo sobre la teoría y los starters de cualquier semana antes de publicarla.
---

# Verificar progresión

El bootcamp empieza en cero absoluto. Un `std::unique_ptr` en la Semana 03 o una
lambda en la Semana 04 no es un atajo: es un agujero por el que el estudiante cae sin
saber qué está leyendo.

## 1. La tabla de introducción

Cada concepto tiene una semana en la que se enseña. Antes de esa semana, no aparece
sin envolver y anotar.

| Semana | Se introduce | Patrón de búsqueda |
| --- | --- | --- |
| 01 | tipos, `auto`, `const`, `constexpr` en variables, `iostream`, `std::format` | — |
| 02 | `if`/`for`/`while`/`switch`, funciones, referencias, `std::string`, `std::string_view`, `std::vector`, `enum class` | — |
| 03 | punteros, `nullptr`, `std::array`, `std::span`, `new`/`delete`, cadenas C | `new \|delete \|std::span\|std::array` |
| 04 | `class`, constructores, destructores, RAII, operadores, `<=>`, Catch2 | `class \|struct .*{\|operator` |
| 05 | copia/movimiento, `std::move`, `&&`, `std::forward`, `unique_ptr`, `shared_ptr`, `weak_ptr` | `std::move\|std::forward\|unique_ptr\|shared_ptr\|weak_ptr\|make_unique\|make_shared` |
| 06 | `virtual`, `override`, `final`, clases abstractas, `dynamic_cast` | `virtual\|override\|final\|dynamic_cast` |
| 07 | `template`, `concept`, `requires`, `decltype`, variádicos | `template\|concept \|requires\|decltype\|\.\.\.` |
| 08 | `std::map`, `std::set`, `unordered_*`, `std::list`, `std::deque`, iteradores explícitos | `std::map\|std::set\|unordered_\|std::list\|std::deque\|::iterator` |
| 09 | lambdas, `std::function`, `<algorithm>`, `<numeric>`, `std::ranges` | `\[\]\|\[&\|\[=\|\[this\|std::function\|<algorithm>\|<numeric>\|std::ranges\|views::` |
| 10 | `throw`, `try`/`catch`, `noexcept` en firmas propias, `std::optional`, `std::variant`, `std::expected` | `throw\|try {\|catch\|std::optional\|std::variant\|std::expected\|std::visit` |
| 11 | módulos, `export module`, bibliotecas CMake, `clang-tidy` | `export module\|import ` |
| 12 | `constexpr` en funciones, `consteval`, `if constexpr`, `<type_traits>`, CRTP | `consteval\|if constexpr\|type_traits\|static_assert` |
| 13 | `std::thread`, `std::jthread`, `std::mutex`, `lock_guard`, `condition_variable`, `std::atomic` | `std::thread\|jthread\|std::mutex\|lock_guard\|scoped_lock\|condition_variable\|std::atomic` |
| 14 | `memory_order`, `std::async`, `std::future`, `latch`, `barrier`, `co_await`, `co_yield` | `memory_order\|std::async\|std::future\|std::latch\|std::barrier\|co_await\|co_yield\|co_return` |
| 15 | `std::pmr`, allocators, Google Benchmark, `alignas` | `std::pmr\|allocator\|benchmark::\|alignas` |
| 16 | `std::filesystem`, `fstream` binario, `fork`, `mmap`, `extern "C"` | `std::filesystem\|fork(\|mmap(\|extern "C"` |
| 17 | sockets, `epoll`, Asio | `socket(\|epoll\|asio::` |

Excepciones legítimas que **no** son hallazgo:

- `std::string`, `std::vector`, `std::cout` y `std::format` desde la 01-02: son las
  herramientas mínimas para escribir algo.
- Los **tests con Catch2** en los starters desde la Semana 04. Antes de la 04 los
  ejercicios se verifican por salida de `main` y `assert`.
- Un `&&` que es el operador lógico, no una referencia a rvalue. Mira el contexto.
- Uso **envuelto y anotado**: una función auxiliar ya escrita que el estudiante no
  tiene que entender todavía, con el comentario "esto lo verás en la Semana NN".

## 2. Cómo buscar

Para la semana `NN`, greppea en su teoría y sus starters todos los patrones de las
semanas posteriores:

```bash
week=bootcamp/week-NN-*
grep -rnE 'unique_ptr|shared_ptr|make_unique|std::move' $week/1-teoria $week/2-practicas $week/3-proyecto
```

Ignora los archivos de `4-recursos/` y `5-glosario/`: un glosario puede mencionar un
término futuro con la nota "se ve en la Semana NN".

## 3. Qué hacer con cada aparición

| Caso | Veredicto |
| --- | --- |
| Concepto futuro en prosa de la teoría, explicado como si ya se supiera | 🔴 |
| Concepto futuro en un starter que el estudiante tiene que descomentar o implementar | 🔴 |
| Concepto futuro en código auxiliar del starter, envuelto y anotado | ✅ (verifica que la anotación existe) |
| Concepto futuro en prosa con "esto lo verás en la Semana NN" | ✅ |
| Concepto futuro en un antipatrón, explicado como "esto no lo hagas todavía" | 🟡 — sospechoso; mejor quitarlo |
| Concepto en su semana o después | ✅ |

## 4. Informe

```
ruta:línea: 🔴 adelantado: "<cita literal>". Se enseña en la Semana NN. Envolver y anotar, o sustituir por <alternativa de la semana actual>.
ruta:línea: 🟡 sospechoso: "<cita literal>". Aparece como antipatrón antes de su semana. Considerar quitarlo.
```

Cita literalmente. Si no hay hallazgos, di qué patrones buscaste y sobre qué archivos.
