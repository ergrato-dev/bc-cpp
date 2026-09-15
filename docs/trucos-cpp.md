# 🎩 Trucos de C++ y del toolchain

Índice global de la sección `## 🎩 Trucos y atajos` del README de cada semana. Cada
truco vive en dos sitios: el README de su semana y aquí, con el texto **literal**. Se
sincroniza al publicar cada semana (ver `.claude/skills/verificar-estructura`).

Criterio de admisión: ahorra tiempo real o revela algo que el compilador, CMake, gdb o
el editor esconden. Un consejo genérico de productividad no es un truco.

Las semanas sin publicar no tienen sección.

---

## Semana 01 — Toolchain y compilación

| Truco | Cómo |
| ----- | ---- |
| Comprobar que un archivo compila sin generar nada | `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsyntax-only x.cpp`. Milisegundos por vuelta |
| Ver qué estándar usa tu compilador por defecto | `g++ -dM -E -x c++ /dev/null \| grep __cplusplus` → `201703L` es C++17; con `-std=c++20`, `202002L` |
| Ver la orden real de `g++` que ejecuta CMake | `cmake --build --preset debug -- -v`. Comprueba que lleva `-Werror` y `-std=c++20` |
| Ver qué trae un `#include` | `g++ -std=c++20 -E x.cpp \| wc -l`. `<iostream>` en GCC 13: ~43.000 líneas |
| Ver el ensamblador de una línea concreta | Pega el archivo en https://godbolt.org/ con `-std=c++20 -O2`; al pasar el ratón por una línea de C++ se iluminan sus instrucciones |
| Cambiar de compilador sin tocar nada | `CXX=clang++ cmake --preset debug --fresh`. CMake lee `CXX` al configurar |
| Ejecutar un solo test | `ctest --preset debug -R paso3`. `-R` es una expresión regular sobre el nombre |
| Ver qué escribió el programa cuando un test falla | Los presets ya llevan `--output-on-failure`; si no, `ctest --preset debug --output-on-failure` |
| Saber qué tipo dedujo `auto` | Provoca un error: `auto x{...}; x.no_existe();` y el compilador te dice el tipo en el mensaje |

---

## Semana 02 — Control de flujo, funciones y referencias

| Truco | Cómo |
| ----- | ---- |
| Cazar un `if (x = 5)` antes de que muerda | Ya lo hace `-Wall` (`-Wparentheses`); con `-Werror` no compila. Si de verdad quieres asignar dentro de un `if`, dobla los paréntesis: `if ((x = f()))` |
| Que el compilador vigile los `switch` | Un `switch` sobre un `enum class` sin `default` y sin algún valor dispara `-Wswitch` (en `-Wall`). Deja el `default` fuera a propósito y el compilador te avisará cuando añadas un valor al enum |
| Detectar variables que tapan a otras | `-Wshadow` no está en `-Wall` ni en `-Wextra`. Añádelo a `target_compile_options` de tu proyecto: cada `int x` dentro de otro `int x` te avisará |
| Índices de `vector` comprobados sin cambiar código | `-D_GLIBCXX_ASSERTIONS` en las opciones de compilación (libstdc++): `v[10]` sobre un vector de 3 aborta con `Assertion '__n < this->size()' failed` en vez de leer basura |
| Probar un programa que lee `stdin` sin teclear | `printf 'add 3 4\nquit\n' \| ./build/debug/app`. Es exactamente lo que hacen los tests de esta semana |
| Ver qué línea de entrada rompió el programa | `printf ... \| ./app` y, si falla, `printf ... \| head -n 2 \| ./app`: reduce la entrada hasta aislar la línea |
| Convertir texto a número sin que un fallo cierre el programa | `std::istringstream iss{line}; if (!(iss >> n)) { /* inválido */ }`. `std::stoi` lanza una excepción con `"abc"`, y las excepciones llegan en la Semana 10 |
| Saber si una función copia su argumento | Pon un `std::cout` en el constructor de copia... cuando sepas clases (Semana 04). Hoy: `-O0`, `gdb`, `break f` y `info args`: si es referencia, `gdb` muestra `(std::string &) @0x...` |
