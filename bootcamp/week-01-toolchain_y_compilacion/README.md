# Semana 01 — Toolchain y compilación

> Antes de escribir una sola clase hay que saber qué hace el compilador con tu archivo,
> por qué el enlazador se queja, y cómo CMake y `ctest` convierten "creo que funciona"
> en "los tests pasan". Esta semana es el ciclo que repetirás las diecinueve siguientes.

Esta semana no hay bucles, ni funciones propias, ni entrada del usuario. Hay tipos,
constantes, `std::format`, y el pipeline entero de `g++` visto por dentro. Si te parece
poco, mira cuánta gente lleva años en C++ sin saber distinguir un error de compilación
de uno de enlace.

---

## 🎯 Objetivos de la Semana

Al finalizar esta semana serás capaz de:

- **Situar** C++20 en la línea de estándares y distinguir el lenguaje del compilador
- **Nombrar** las cuatro etapas del pipeline y **detener** `g++` en cualquiera de ellas
- **Leer** un mensaje de error y decir si viene del preprocesador, del compilador o del enlazador
- **Escribir** un `CMakeLists.txt` mínimo con flags por target y tests con `ctest`
- **Usar** `CMakePresets.json` para configurar, construir y probar sin memorizar líneas de comandos
- **Elegir** el tipo correcto para cada dato y **declararlo** con inicialización uniforme
- **Distinguir** `const` de `constexpr` y usar `auto` solo cuando aporta
- **Formatear** salida con `std::format` y separar resultado (`cout`) de avisos (`cerr`)
- **Provocar y reconocer** un warning con `-Werror`, un error de narrowing y un reporte de UBSan

---

## 📋 Prerrequisitos

- Ninguna semana anterior: esta es la primera.
- Toolchain instalado según [`docs/setup.md`](../../docs/setup.md): GCC 13+ o Clang
  17+, CMake 3.28+, Ninja. Verifica con `g++ --version && cmake --version`.
- Un editor con soporte de `compile_commands.json` (VS Code con las extensiones de
  `.vscode/extensions.json`, o el que prefieras).
- Git, y una cuenta de GitHub para el repositorio de tu proyecto.
- **No hace falta saber programar.** Cero absoluto.

---

## 🗂️ Estructura de la Semana

```
week-01-toolchain_y_compilacion/
├── README.md                    # este archivo
├── rubrica-evaluacion.md        # cómo se evalúa la semana
├── 0-assets/                    # 4 diagramas SVG
├── 1-teoria/                    # 5 archivos, un concepto cada uno
├── 2-practicas/                 # 2 ejercicios guiados con starter/ y tests
├── 3-proyecto/                  # la capa 0 de tu sistema: esqueleto + CMake
├── 4-recursos/                  # libros, vídeos y webgrafía
└── 5-glosario/                  # los términos de esta semana, A-Z
```

---

## 📝 Contenidos

### Teoría

| Archivo | Tema | Duración |
| ------- | ---- | -------- |
| [01 · Qué es C++ hoy](1-teoria/01-que-es-cpp-hoy.md) | Compilado vs interpretado, estándares, compiladores, el programa mínimo | 30 min |
| [02 · Del código fuente al ejecutable](1-teoria/02-del-codigo-fuente-al-ejecutable.md) | Preprocesador, compilador, ensamblador, enlazador; flags; unidades de traducción | 40 min |
| [03 · CMake mínimo](1-teoria/03-cmake-minimo.md) | Configurar y construir, targets, presets, `ctest` | 35 min |
| [04 · Tipos, variables y constantes](1-teoria/04-tipos-variables-y-constantes.md) | Tipos fundamentales, `{}`, `const`/`constexpr`, `auto`, conversiones | 40 min |
| [05 · Entrada y salida básica](1-teoria/05-entrada-y-salida-basica.md) | Streams, `std::format`, `cout`/`cerr`, `'\n'` vs `endl`, `std::print` (C++23) | 35 min |

### Prácticas

| Ejercicio | Qué haces | Duración |
| --------- | --------- | -------- |
| [01 · Compila tu primer programa con CMake](2-practicas/ejercicio-01-hola-toolchain/README.md) | Cuatro tests en verde, el pipeline por dentro, un `-Werror` provocado | 60 min |
| [02 · Mide los tipos de tu máquina](2-practicas/ejercicio-02-tipos-y-limites/README.md) | `sizeof`, `numeric_limits`, división entera, `unsigned`, narrowing, UBSan | 90 min |

### Proyecto

Eliges tu dominio, creas tu repositorio y escribes el esqueleto de tu sistema: tres
registros tipados, un informe con `std::format`, tests de `ctest` calculados a mano.
→ [3-proyecto/README.md](3-proyecto/README.md)

---

## ⏱️ Distribución del Tiempo (10 horas)

| Actividad | Tiempo |
| --------- | ------ |
| Teoría (5 archivos) | 3 h |
| Ejercicio 01 | 1 h |
| Ejercicio 02 | 1 h 30 min |
| Proyecto | 3 h |
| Recursos y glosario | 1 h |
| Autoevaluación (cuestionario de la rúbrica) | 30 min |
| **Total** | **10 h** |

---

## 🧪 Qué necesita C++23 esta semana

Nada obligatorio. Se menciona una función para que la reconozcas:

| Función | Qué hace | Alternativa en C++20 |
| ------- | -------- | -------------------- |
| `std::print` / `std::println` | Formatea e imprime en una llamada | `std::cout << std::format(...)` |

---

## 🎩 Trucos y atajos

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

## 📌 Entregables

1. ✅ Ejercicio 01: `ctest --preset debug` y `ctest --preset asan` con 4 de 4 en verde
2. ✅ Ejercicio 02: 5 de 5 en verde, y los pasos 6 y 7 (narrowing, UBSan) hechos y deshechos
3. ✅ Repositorio `bc-cpp-<tu-dominio>` creado, con el dominio escrito en su README
4. ✅ Proyecto: rama `week-01` con `CMakeLists.txt`, `CMakePresets.json`, `src/main.cpp`
   y al menos 5 tests calculados a mano, todos en verde en `debug` y `asan`
5. ✅ Pull request `week-01` → `main` con dominio, compilador y salida de `ctest`
6. ✅ Cuestionario de la [rúbrica](rubrica-evaluacion.md) respondido antes de mirar las soluciones

---

## ✅ Verificación

En cada `starter/` (ejercicios y proyecto):

```bash
cmake --preset asan && cmake --build --preset asan && ctest --preset asan
```

Tiene que salir `100% tests passed` sin ningún `runtime error` ni `AddressSanitizer`.
Si algo falla antes de eso (Ninja, versión del compilador, `std::format` que "no
existe"), la tabla `🧯 Si algo sale mal` del ejercicio 01 cubre los casos habituales.

---

## 🔗 Navegación

| Anterior | Actual | Siguiente |
| -------- | ------ | --------- |
| — | **Semana 01** | Semana 02 (próximamente) |

← [Volver al inicio del bootcamp](../../README.md)
