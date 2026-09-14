---
mode: agent
description: Genera un ejercicio guiado (patrón descomentar) con starter CMake + Catch2 para una semana del bootcamp C++ Zero to Hero.
---

# Nuevo ejercicio

Genera `bootcamp/week-{{NN}}-{{SLUG}}/2-practicas/ejercicio-{{MM}}-{{TEMA}}/`.

Lee antes [`.github/copilot-instructions.md`](../copilot-instructions.md) y
[`docs/politica-versiones.md`](../../docs/politica-versiones.md).

## ⚠️ Regla fundamental: patrón de descomentar

Los ejercicios son **tutoriales guiados**, NO tareas con TODOs. El estudiante aprende
descomentando código y viendo pasar tests que ya están escritos.

```cpp
// ✅ CORRECTO — código comentado para descomentar
// Descomenta las siguientes líneas para el Paso 1:
// [[nodiscard]] int Item::quantity() const noexcept {
//   return quantity_;
// }

// ❌ INCORRECTO — esto es formato de PROYECTO, no de ejercicio
int Item::quantity() const noexcept {
  // TODO: devolver la cantidad
}
```

## Estructura

```
2-practicas/ejercicio-{{MM}}-{{TEMA}}/
├── README.md
└── starter/
    ├── CMakeLists.txt
    ├── CMakePresets.json
    ├── src/
    │   ├── main.cpp            # puede estar completo o parcialmente comentado
    │   ├── item.hpp
    │   └── item.cpp
    └── tests/
        └── test_item.cpp       # YA escritos; fallan hasta descomentar
```

> ⚠️ **Sin carpeta `solution/`**: el código comentado ES la solución. `**/solution/`
> está en `.gitignore`.

## README.md del ejercicio

```markdown
# Ejercicio {{MM}} — Título en imperativo

> Una línea con lo que vas a tener funcionando al terminar.

**Duración estimada**: 60 min
**Prerrequisitos**: [Teoría 02](../../1-teoria/02-tema.md) leída

## Contexto

El escenario. Por qué haces esto. Sin código todavía.

## Paso 0: Configurar y ver fallar los tests

\`\`\`bash
cd starter
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
\`\`\`

Deben fallar N tests. Es lo esperado: el código que los hace pasar está comentado.

## Paso 1: Título del paso

**Por qué**: el problema que resuelve este paso concreto.

Explicación del concepto con el código que vas a descomentar, comentado en español:

\`\`\`cpp
// el código, tal cual quedará al descomentar
\`\`\`

**Abre `starter/src/item.cpp`** y descomenta la sección del Paso 1.

**Verifica**:

\`\`\`bash
cmake --build --preset debug && ctest --preset debug
\`\`\`

Pasan `[item][ctor]`. Sigue fallando `[item][compare]`: es del Paso 2.

## Paso 2: ...

## Paso final: Compilar con sanitizers

\`\`\`bash
cmake --preset asan && cmake --build --preset asan && ctest --preset asan
\`\`\`

## ✅ Resultado

- [ ] ...

## 🧯 Si algo sale mal

| Síntoma | Causa | Solución |
```

## Reglas de los pasos

- **Todo paso termina en una forma de verificarlo**: un tag de Catch2 que pasa a
  verde, una salida concreta de `main`, o un diagnóstico esperado del compilador o de
  un sanitizer. Nunca "comprueba que funciona".
- **El porqué va antes del cómo**, en cada paso.
- **El README muestra el código antes de que el estudiante lo descomente**, explicado.
  Descomentar sin entender no enseña nada.
- **Los tests van etiquetados por paso** (`TEST_CASE("...", "[item][ctor]")`) para que
  el README pueda decir exactamente qué debe pasar en cada paso.
- **Ningún concepto de una semana posterior.** Consulta la malla.
- Un starter compila desde el Paso 0 (con todo comentado) y **falla en los tests, no en
  la compilación**. Si hace falta un stub para que enlace, se pone el stub.
- **Dentro de un bloque `PASO N`, la prosa va ANTES de la línea
  `// Descomenta las siguientes líneas`; después de esa línea solo hay código
  comentado** (con un espacio tras `//`) hasta el siguiente banner. El script de
  verificación descomenta mecánicamente todo lo que sigue a la marca; un comentario de
  prosa ahí se convierte en código y rompe la compilación. Los pasos "manuales"
  (provocar un error, ver un diagnóstico) se describen en el README, no en el starter.

## Formato del starter

```cpp
// ============================================
// PASO 1: Getter con [[nodiscard]]
// ============================================
// Descomenta las siguientes líneas para el Paso 1:

// [[nodiscard]] int Item::quantity() const noexcept {
//   return quantity_;   // solo lectura: no puede modificar el objeto
// }

// ============================================
// PASO 2: Comparación con operator<=>
// ============================================
// Descomenta las siguientes líneas para el Paso 2:

// auto Item::operator<=>(const Item& other) const = default;
```

## CMakeLists.txt obligatorio

```cmake
cmake_minimum_required(VERSION 3.28)
project(ejercicio_{{MM}}_{{TEMA}} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(item src/item.cpp)
target_include_directories(item PUBLIC src)
target_compile_options(item PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE item)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.16.0   # versión exacta: ver docs/politica-versiones.md
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_executable(tests tests/test_item.cpp)
target_link_libraries(tests PRIVATE item Catch2::Catch2WithMain)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(tests)
```

## CMakePresets.json obligatorio

Copia `docs/plantillas/CMakePresets.json` tal cual. Define `debug`, `release` y `asan`
(este último con `-fsanitize=address,undefined -fno-omit-frame-pointer`).

## Duración

Entre 45 y 90 minutos por ejercicio. Si se pasa, divídelo. Las duraciones de todos los
ejercicios más las de la teoría tienen que cuadrar con las 10 horas del README.

## Troubleshooting

`## 🧯 Si algo sale mal` es obligatorio: tabla Síntoma | Causa | Solución, con al menos
tres filas, sacadas de lo que falla de verdad en ese ejercicio (errores de enlace,
mensajes de template, `undefined reference`, tests que no se descubren, etc.).

## Verificación antes de entregar

- [ ] Cada paso tiene su **Por qué** y su **Verifica**
- [ ] Los tests están escritos, etiquetados por paso, y fallan con todo comentado
- [ ] `./scripts/compilar-starters.sh week-{{NN}}` pasa en `debug` y `asan`
- [ ] Con todo descomentado, `ctest` pasa al 100 %
- [ ] Sin `// TODO:`, sin `solution/`
- [ ] `GIT_TAG` exacto en cada `FetchContent_Declare`
- [ ] La tabla de troubleshooting tiene al menos tres filas reales
- [ ] La duración declarada cuadra con la del README de la semana
