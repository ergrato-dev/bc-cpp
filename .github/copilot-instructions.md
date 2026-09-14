# 🤖 Instrucciones para GitHub Copilot

## 📋 Contexto del Bootcamp

Este es un **Bootcamp C++ Zero to Hero**: 20 semanas sobre **C++ moderno (C++20)**
desde cero absoluto hasta un nivel avanzado. No es un curso de "C con clases", ni un
repaso de sintaxis: forma a alguien capaz de diseñar, escribir, medir, depurar y
entregar software C++ de calidad profesional, con concurrencia, redes, rendimiento y
metaprogramación incluidos.

### 📊 Datos del Bootcamp

- **Duración**: 20 semanas (~5 meses)
- **Dedicación semanal**: 10 horas
- **Total de horas**: 200 horas
- **Modalidad**: autoestudio asincrónico con verificación automática por compilación y
  tests (`cmake` + `ctest` + Catch2)
- **Nivel de entrada**: **cero absoluto**. No se asume programación previa
- **Nivel de salida**: desarrollador C++ avanzado — capaz de escribir bibliotecas,
  servicios concurrentes y servidores de red con tests, sanitizers y benchmarks
- **Estándar objetivo**: **C++20**. Lo que sea C++23 se marca como tal y siempre lleva
  su alternativa en C++20
- **Toolchain**: CMake 3.28+, GCC 13+ o Clang 17+, Catch2 v3, Ninja opcional
- **Sistema operativo**: Linux o WSL2 como primario. macOS y Windows/MSVC se mencionan
  donde difieren, nunca se asumen
- **Idioma del código**: inglés. La prosa es española

---

## 🎯 Objetivos de Aprendizaje

Al finalizar el bootcamp, los estudiantes serán capaces de:

- ✅ Explicar qué hace el compilador, el enlazador y el preprocesador con un archivo `.cpp`
- ✅ Modelar datos con tipos, clases e invariantes explícitos
- ✅ Gestionar recursos con RAII y smart pointers, sin `new`/`delete` a mano
- ✅ Distinguir copia de movimiento y saber cuándo el compilador elide ambas
- ✅ Diseñar jerarquías con polimorfismo dinámico y, cuando toca, estático
- ✅ Escribir código genérico con templates y conceptos que fallan con mensajes legibles
- ✅ Elegir el contenedor y el algoritmo de la STL adecuados y justificarlo por complejidad
- ✅ Modelar errores con excepciones, `optional`, `variant` y `expected` según el caso
- ✅ Organizar un proyecto en bibliotecas, módulos y targets de CMake con tests
- ✅ Computar en tiempo de compilación con `constexpr`, traits y CRTP
- ✅ Escribir código concurrente correcto y demostrarlo con TSan
- ✅ Usar coroutines de C++20 para generadores y pipelines asíncronos
- ✅ Medir antes de optimizar: benchmarks, `perf`, layout de memoria y allocators
- ✅ Hablar con el sistema operativo: ficheros, procesos, `mmap`, sockets, `epoll`
- ✅ Construir un servidor HTTP con Asio y coroutines
- ✅ Endurecer código con sanitizers, fuzzing y análisis estático
- ✅ Diseñar APIs y bibliotecas con ABI estable, documentadas e instalables

---

## 📚 Estructura del Bootcamp

### Distribución por Fases

#### **Fase 1 · Fundamentos (Semanas 1-4)** — 40 horas

- Toolchain, pipeline de compilación, CMake, tipos, E/S
- Control de flujo, funciones, referencias, `string`, `vector`, comportamiento indefinido
- Modelo de memoria, punteros, arrays, `span`, gdb, primer contacto con ASan
- Clases, constructores, RAII, operadores, tests con Catch2

#### **Fase 2 · C++ Moderno Core (Semanas 5-10)** — 60 horas

- Copia, movimiento, `unique_ptr`, `shared_ptr`, `weak_ptr`
- Herencia, funciones virtuales, interfaces, composición
- Templates, deducción, conceptos, variádicos
- Contenedores e iteradores de la STL
- Algoritmos, lambdas, ranges
- Excepciones, `optional`, `variant`, `expected`

#### **Fase 3 · Avanzado (Semanas 11-17)** — 70 horas

- Headers, ODR, módulos, CMake multi-target, clang-tidy, dependencias
- `constexpr`, traits, CRTP, type erasure
- Threads, mutex, condition variables, thread pool, TSan
- Memory model, lock-free, `async`, coroutines
- Cache, layout, allocators, benchmarks, `perf`
- `filesystem`, E/S binaria, POSIX, `mmap`, interop con C
- Sockets, `epoll`, Asio, HTTP

#### **Fase 4 · Producción (Semanas 18-20)** — 30 horas

- Sanitizers, fuzzing, Core Guidelines, CI
- Patrones, diseño de API, ABI, empaquetado
- Proyecto final integrador

### Contenido Semana a Semana

| Semana | Slug                                   | Tema                                                                       |
| ------ | -------------------------------------- | -------------------------------------------------------------------------- |
| 01     | `toolchain_y_compilacion`              | Historia y estándares, g++/clang++, pipeline, CMake mínimo, tipos, E/S     |
| 02     | `control_funciones_referencias`        | Control de flujo, funciones, referencias, alcance, `string`, `vector`, UB  |
| 03     | `memoria_punteros_arrays`              | Stack/heap, punteros, arrays, `span`, `new`/`delete`, gdb, cadenas C       |
| 04     | `clases_raii_tests`                    | Clases, constructores, RAII, operadores, `<=>`, Catch2, `ctest`            |
| 05     | `copia_movimiento_smart_pointers`      | Regla de 0/3/5, rvalues, `move`, `forward`, smart pointers, elisión        |
| 06     | `herencia_polimorfismo`                | `virtual`, vtable, interfaces, slicing, RTTI, composición                  |
| 07     | `templates_conceptos`                  | Templates, deducción, especialización, conceptos, variádicos, errores      |
| 08     | `stl_contenedores_iteradores`          | Secuencias, asociativos, hashing, iteradores, adaptadores, elección        |
| 09     | `algoritmos_lambdas_ranges`            | Lambdas, `<algorithm>`, `<numeric>`, ranges, views, proyecciones           |
| 10     | `errores_optional_variant`             | Excepciones, garantías, `noexcept`, `optional`, `variant`, `expected`      |
| 11     | `modulos_build_tooling`                | ODR, pimpl, módulos C++20, CMake avanzado, clang-tidy, dependencias        |
| 12     | `metaprogramacion_constexpr`           | `constexpr`/`consteval`, traits, `if constexpr`, CRTP, type erasure        |
| 13     | `concurrencia_threads_sincronizacion`  | `jthread`, mutex, `condition_variable`, atomics, thread pool, TSan         |
| 14     | `memory_model_async_coroutines`        | `memory_order`, lock-free, `async`/`future`, `latch`, coroutines           |
| 15     | `rendimiento_profiling`                | Cache, layout, SoA/AoS, allocators, PMR, benchmarks, `perf`, SIMD          |
| 16     | `io_filesystem_sistemas`               | `filesystem`, E/S binaria, procesos, señales, `mmap`, `extern "C"`         |
| 17     | `redes_sockets_asio`                   | Sockets, `epoll`, Asio, coroutines de red, HTTP/1.1                        |
| 18     | `seguridad_sanitizers_fuzzing`         | ASan/UBSan/TSan, libFuzzer, Core Guidelines, GSL, análisis estático, CI    |
| 19     | `diseno_patrones_api`                  | Patrones modernos, diseño de API, arquitectura, ABI, Doxygen, instalación  |
| 20     | `proyecto_final`                       | Especificación, code review, sistema completo del dominio, presentación    |

---

## 🗂️ Estructura de Carpetas

Cada semana sigue esta estructura estándar:

```
bootcamp/week-XX-tema_principal/
├── README.md                 # Descripción y objetivos de la semana
├── rubrica-evaluacion.md     # Criterios de evaluación detallados
├── 0-assets/                 # Diagramas SVG
├── 1-teoria/                 # Material teórico (archivos .md)
├── 2-practicas/              # Ejercicios guiados con starter/ (patrón descomentar)
│   └── ejercicio-NN-tema/
│       ├── README.md
│       └── starter/          # CMakeLists.txt + src/ + tests/
├── 3-proyecto/               # Capa semanal del proyecto del dominio
│   ├── README.md             # Requisitos del entregable
│   └── starter/              # Esqueleto con TODOs adaptable al dominio
├── 4-recursos/               # Recursos adicionales
│   ├── ebooks-free/
│   ├── videografia/
│   └── webgrafia/
└── 5-glosario/               # Términos clave de la semana (A-Z)
    └── README.md
```

### 📁 Carpetas Raíz

- **`assets/`**: recursos visuales globales (header del README)
- **`docs/`**: documentación transversal (setup, versiones, dominios, proyecto hilo
  conductor, glosario global)
- **`scripts/`**: `verificar-enlaces.sh`, `compilar-starters.sh`
- **`bootcamp/`**: contenido semanal

---

## 🎓 Componentes de Cada Semana

### 1. **Teoría** (`1-teoria/`)

- Archivos markdown con explicaciones conceptuales **en español**
- **El número de archivos de teoría es libre**: los que pida el temario, no un cupo
  fijo. Cuatro a seis es lo normal. **Nunca se sacrifica profundidad para que quepa**
- **Extensión por archivo: ~250 líneas** (rango sano 200-300). Si un archivo se va de
  ahí, el problema es que mezcla dos temas: divídelo en dos archivos, no recortes
- Un archivo = un concepto. Si el título necesita una "y", sospecha
- Cada tema se explica en este orden: **qué problema resuelve → cómo funciona → cómo se
  escribe en C++20 → antipatrones → trucos**
- **Cero absoluto**: la primera vez que aparece un término técnico se define. "Stack",
  "heap", "símbolo", "enlace", "UB" y "ABI" no son vocabulario común
- **Todo fragmento de código compila.** Si es un ejemplo de lo que NO hacer, se marca
  con `// ❌` y se explica qué diagnóstico produce (warning, error, sanitizer, UB)
- Diagramas SVG cuando aporten (nunca ASCII art, nunca capturas de pantalla)
- Referencias a [cppreference.com](https://en.cppreference.com/) como fuente de verdad
  y al borrador del estándar cuando el matiz lo pida

### 2. **Prácticas** (`2-practicas/`)

Los ejercicios son **tutoriales guiados**, NO tareas con TODOs. El estudiante aprende
**descomentando código** y viendo los tests pasar.

```
2-practicas/ejercicio-01-nombre/
├── README.md                 # Pasos numerados con el código explicado
└── starter/
    ├── CMakeLists.txt        # Catch2 vía FetchContent, versión exacta
    ├── src/
    │   ├── main.cpp
    │   └── ...
    └── tests/
        └── test_nombre.cpp   # Tests YA escritos; fallan hasta descomentar
```

Formato del starter:

```cpp
// ============================================
// PASO 2: Constructor con lista de inicialización
// ============================================
// Descomenta las siguientes líneas para el Paso 2:

// Item::Item(std::string name, int quantity)
//     : name_{std::move(name)}, quantity_{quantity} {
//   if (quantity_ < 0) {
//     throw std::invalid_argument{"quantity must be >= 0"};
//   }
// }
```

Formato de un paso en el README:

```markdown
## Paso 2: Constructor con lista de inicialización

**Por qué**: inicializar en el cuerpo del constructor significa construir primero por
defecto y asignar después: dos operaciones donde basta una, y un error de compilación
si el miembro es `const` o una referencia.

**Abre `starter/src/item.cpp`** y descomenta la sección del Paso 2.

**Verifica**:

\`\`\`bash
cmake --build build && ctest --test-dir build --output-on-failure
\`\`\`

Deben pasar `[item][ctor]`. Sigue fallando `[item][compare]`: es del Paso 3.
```

Reglas:

- Todo paso termina con una **forma de verificarlo**: un test que pasa, una salida
  concreta, o un diagnóstico del compilador o de un sanitizer
- Los **tests van escritos en el starter** y fallan hasta que el estudiante descomenta.
  Los tests son el contrato del ejercicio
- ❌ No usar `// TODO:` en prácticas — eso es formato de proyecto
- ❌ **Sin carpeta `solution/`**: el código comentado ES la solución. `**/solution/`
  está en `.gitignore`
- Los starters se compilan con `-Wall -Wextra -Wpedantic -Werror`. Un starter que
  avisa no se publica

### 3. **Proyecto** (`3-proyecto/`)

Cada semana añade **una capa nueva al mismo sistema del dominio del estudiante** (ver
`docs/proyecto-hilo-conductor.md`). Nunca un proyecto desechable por semana.

El starter del proyecto usa `// TODO:` con pistas y la firma esperada, sobre un recurso
genérico `Item` que el estudiante renombra a su dominio:

```cpp
// NOTA PARA EL APRENDIZ: adapta `Item` a tu dominio asignado
// (Book, Medicine, Member, Dish, Room...).

// TODO: implementar la búsqueda por nombre.
// Firma esperada:
//   std::optional<Item> Repository::find_by_name(std::string_view name) const;
// Pista: std::ranges::find_if sobre items_ comparando item.name().
```

El README del proyecto incluye:

1. Qué capa se añade esta semana y por qué va aquí
2. Requisitos verificables (compila, tests que deben existir y pasar, comportamiento)
3. Cómo verificarlo: `cmake -S . -B build && cmake --build build && ctest --test-dir build`
4. Criterios de calidad más allá de lo automatizable
5. Adaptación al dominio con ejemplos para al menos cinco dominios

**Política de dominios únicos**: el estudiante elige (o el instructor asigna) un
dominio en la Semana 01 y lo mantiene 20 semanas. Ver `docs/dominios.md`.

### 4. **Recursos** (`4-recursos/`)

- **ebooks-free/**: libros y guías gratuitas y legales (Core Guidelines, cppreference
  offline, libros con licencia abierta)
- **videografia/**: charlas de CppCon, C++Now, Meeting C++, ACCU y tutoriales
- **webgrafia/**: cppreference primero, luego blogs de calidad (Sutter, Meyers, Niebler,
  Abseil tips, etc.)

Cada recurso lleva una línea de por qué vale la pena, no solo el enlace.

### 5. **Glosario** (`5-glosario/`)

Términos A-Z **en español**, con el **término inglés del estándar entre paréntesis**
siempre que exista (`referencia a rvalue (rvalue reference)`, `regla de una definición
(One Definition Rule, ODR)`). Es la pieza que conecta la prosa española con el
vocabulario de cppreference y del estándar; no es opcional.

---

## 📝 Convenciones de Código

### Estándar y flags

- **C++20** en todos los targets: `target_compile_features(t PUBLIC cxx_std_20)`
- Warnings como errores en starters: `-Wall -Wextra -Wpedantic -Werror`
- **Sin extensiones del compilador**: `CMAKE_CXX_EXTENSIONS OFF`
- Lo que sea C++23 (`std::print`, `std::expected`, `std::generator`, deducing `this`)
  se marca en la propia línea y lleva su alternativa en C++20

```markdown
> [!NOTE]
> **C++23** · `std::expected` llega en C++23 (GCC 13+, Clang 17+ con `-std=c++23`).
> En C++20 estricto, la alternativa es `tl::expected` o un `std::variant<T, Error>`.
```

### Estilo

- **Nomenclatura**: `snake_case` para funciones, variables y archivos; `PascalCase`
  para tipos; `kConstantName` para constantes; miembros privados con sufijo `_`
- **Headers**: `.hpp`; implementación `.cpp`; `#pragma once`
- **Includes** ordenados: propio, proyecto, terceros, estándar
- **`.clang-format`** de la raíz es la única verdad de formato. No se discute estilo en
  revisiones: se ejecuta `clang-format`
- ✅ `std::string_view` para parámetros de solo lectura de cadenas
- ✅ `std::span` para vistas de contiguos, nunca `T*, size_t`
- ✅ `auto` cuando el tipo es obvio a la derecha; explícito cuando informa
- ✅ `enum class` siempre; `enum` plano nunca
- ✅ `[[nodiscard]]` en funciones cuyo resultado ignorar es un bug
- ❌ `using namespace std;` en headers, nunca; en `.cpp` de ejercicios, tampoco
- ❌ `new`/`delete` crudos fuera de la Semana 03 (donde se enseñan para entenderlos)
- ❌ Casts de C: `(int)x`. Siempre `static_cast` y compañía
- ❌ `#define` para constantes: `constexpr` o `enum class`
- ❌ Arrays C en interfaces: `std::array` o `std::span`

### Comportamiento indefinido

- Toda mención a UB se acompaña de **cómo detectarlo**: `-fsanitize=address,undefined`,
  `-Wall`, o el test que lo expone
- Un ejemplo con UB se marca con `// ❌ UB:` y la razón. Nunca se deja un ejemplo con UB
  sin marcar, ni siquiera "para simplificar"

### CMake

- Versión mínima `cmake_minimum_required(VERSION 3.28)`
- **Target-based**: `target_link_libraries`, `target_include_directories`,
  `target_compile_features`. Nunca variables globales `CMAKE_CXX_FLAGS` en starters
- Dependencias con `FetchContent` y **`GIT_TAG` fijado a una versión exacta** (tag,
  nunca rama). Las versiones viven en `docs/politica-versiones.md`
- Tests con `include(CTest)` + `catch_discover_tests(target)`
- Un `CMakePresets.json` por starter con los presets `debug`, `release` y `asan`

### Placeholders

- `<tu-dominio>` para el nombre del dominio del estudiante
- `<ruta-al-repo>` para rutas locales
- ❌ Nunca una ruta absoluta real de una máquina concreta en el material

---

## 🔐 Reglas de Seguridad y Rigor del Contenido

- ✅ Todo fragmento de código publicado **compila** con GCC 13+ y Clang 17+ en
  `-std=c++20 -Wall -Wextra -Wpedantic -Werror`. Si es un ejemplo de fallo, se dice qué
  falla y con qué mensaje
- ✅ Toda afirmación sobre el estándar se puede señalar en cppreference. Nada de "creo
  que el estándar dice"
- ✅ Comportamientos que dependen del compilador (mensajes, optimizaciones, soporte de
  módulos) se marcan con compilador y versión: `verificado con GCC 14.2, agosto 2026`
- ✅ Antes de cualquier ejemplo que lea entrada externa (ficheros, sockets, argv) se
  validan tamaños y límites. El bootcamp enseña a no confiar en la entrada desde la
  Semana 02
- ✅ Los ejemplos de red escuchan en `127.0.0.1` salvo que la teoría explique
  explícitamente qué implica exponerse
- ❌ Nunca inventar una función, un header o un concepto del estándar. Si hay duda, se
  verifica en cppreference o se dice que no se ha podido verificar
- ❌ Nunca un ejemplo con UB "que funciona en mi máquina" presentado como válido
- ❌ Nunca `system()` con entrada del usuario, ni `strcpy`/`sprintf`/`gets` como código
  recomendado. Si aparecen, es en la sección de antipatrones con su sustituto
- ❌ Nunca dependencias sin `GIT_TAG` exacto, ni descargas sin origen verificable

---

## 🎨 Recursos Visuales

- ✅ **SVG** para todos los diagramas (nunca ASCII art, nunca capturas de pantalla)
- 🌙 **Tema oscuro**, **sin degradados**, colores sólidos
- ✅ Paleta del bootcamp:

```
fondo             #0d1117      texto              #e6edf3
superficie        #161b22      texto secundario   #8b949e
superficie alta   #21262d      texto atenuado     #484f58
borde             #30363d      acento (azul C++)  #659ad2
acento oscuro     #00599c      código             #79c0ff
éxito             #3fb950      advertencia        #d29922
error             #f85149      violeta (templates)#a371f7
stack             #4ade80      heap               #f0883e
```

- Los colores `stack`/`heap` se reservan para diagramas de memoria. `violeta` para
  todo lo que ocurre en tiempo de compilación (instanciación, `constexpr`, conceptos)
- ✅ Tipografía sans-serif exclusivamente: `Inter, Roboto, "Segoe UI", system-ui, sans-serif`;
  `ui-monospace, "JetBrains Mono", Consolas, monospace` para código dentro del diagrama
- ✅ `viewBox` siempre, `role="img"`, `<title>` y `aria-label` descriptivo
- ✅ Ancho objetivo 800-880 px, texto mínimo 12 px, sin JS ni fuentes externas
- ✅ Nombrar en orden de lectura: `01-pipeline-de-compilacion.svg`, `02-stack-y-heap.svg`
- ✅ Todo SVG debe estar enlazado desde al menos un `.md`; uno huérfano es un error
  que reporta `verificar-enlaces.sh`
- **El número de SVG por semana es el que el contenido pida**, no un cupo. Un diagrama
  que no aporte información que el texto no tiene es ruido

---

## 📖 Documentación

### README.md de Semana

Debe incluir, en este orden:

1. Título `# Semana NN — Tema` + blockquote gancho de una línea
2. `## 🎯 Objetivos de la Semana`
3. `## 📋 Prerrequisitos`
4. `## 🗂️ Estructura de la Semana` (árbol de archivos)
5. `## 📝 Contenidos` (tablas de teoría, prácticas y proyecto con duración)
6. `## ⏱️ Distribución del Tiempo (10 horas)`
7. `## 🎩 Trucos y atajos` (compilador, CMake, gdb, editor; mínimo cinco)
8. `## 📌 Entregables`
9. `## ✅ Verificación` (comandos de compilación y tests)
10. `## 🔗 Navegación` (anterior / actual / siguiente)

Las semanas que usan algo de C++23 añaden además una sección
`## 🧪 Qué necesita C++23 esta semana` con la tabla de equivalencias en C++20.

### Archivos de Teoría

```markdown
# Título del Tema

> Blockquote de una línea: por qué esto importa.

## 🎯 Objetivos

## 1. Qué problema resuelve

## 2. Cómo funciona

## 3. Cómo se escribe en C++20

## 4. Antipatrones

## 5. Trucos

## 📚 Recursos Adicionales

## ✅ Checklist de Verificación
```

---

## 📊 Evaluación

Cada semana incluye **tres tipos de evidencias**:

1. **Conocimiento 🧠** (30%): cuestionario de autoevaluación con respuestas al final
2. **Desempeño 💪** (40%): ejercicios verificados por `ctest` en cada starter
3. **Producto 📦** (30%): la capa semanal del proyecto del dominio

Mínimo **70%** en cada tipo. Al ser autoestudio, el cuestionario incluye sus respuestas
en una sección colapsable (`<details>`) al final de la rúbrica.

Penalizaciones estándar del Producto:

| Situación | Penalización |
| --------- | ------------ |
| No compila con `-Wall -Wextra -Wpedantic -Werror` | 0 en Producto |
| Fallo de ASan o UBSan en los tests | -20 |
| `new`/`delete` crudos (fuera de la Semana 03) | -10 |
| Cast de C o `using namespace std;` en un header | -5 cada uno |
| Sin tests propios del proyecto | -15 |
| Código copiado de otro dominio | 0 en Producto |

**Lo que no se automatiza** (legibilidad, elección de contenedor, diseño de API) se
evalúa con criterios observables escritos en la rúbrica, nunca con "está bien hecho".

---

## 🤖 Instrucciones para Copilot

### Límites de Respuesta

1. **Divide respuestas largas**
   - ❌ Nunca generar respuestas que superen los límites de tokens
   - ✅ Dividir por carpetas: teoría → prácticas → proyecto → recursos → assets
   - ✅ Indicar siempre qué parte se entregó y qué falta

2. **Una semana por tanda**, usando la Semana 01 como plantilla de calidad

### Generación de Contenido

1. **Profundidad sobre cobertura**: es preferible explicar bien tres conceptos que
   listar veinte. El bootcamp existe porque los tutoriales superficiales sobran.
2. **Siempre el porqué**: ninguna regla de C++ sin el problema que resuelve y qué pasa
   si no se cumple.
3. **Cero absoluto de verdad**: cada término se define la primera vez.
4. **Verificable**: todo entregable compila y tiene tests. Si no se puede testear,
   replantear el entregable.
5. **Progresión estricta**: ninguna semana usa un concepto que se enseña más tarde. Sin
   smart pointers antes de la 05, sin templates antes de la 07, sin lambdas antes de la
   09, sin excepciones antes de la 10, sin threads antes de la 13. Cuando un starter
   temprano necesite algo posterior, se envuelve y se explica en una línea como "esto lo
   verás en la Semana NN".
6. **Compilar antes de publicar.** `./scripts/compilar-starters.sh week-NN` tiene que
   pasar. Un fragmento de teoría se comprueba pegándolo en un `.cpp` y compilándolo.
7. **No inventar funciones, headers ni comportamientos del estándar.** Si hay duda,
   decirlo y enlazar cppreference en lugar de improvisar algo plausible.

### Estado del lenguaje

- El estándar objetivo es **C++20**; el material se escribe contra él
- **Módulos** se enseñan en la Semana 11 con su estado real en GCC 14 / Clang 18 /
  CMake 3.28; el resto del bootcamp usa headers porque el ecosistema aún los usa
- **RAII y smart pointers** se enseñan **antes** que la herencia: gestionar recursos
  sin saber quién es dueño es adivinar
- **Conceptos** se enseñan junto con los templates, no como "tema avanzado": un
  template sin restricciones es un error de diseño desde el día uno
- **Excepciones** se enseñan tarde (Semana 10) y junto con sus alternativas; hasta
  entonces los ejemplos fallan con `assert` o con códigos de retorno explicados

---

## 📚 Referencias Oficiales

- **cppreference**: https://en.cppreference.com/
- **C++ Core Guidelines**: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
- **ISO C++ (isocpp.org)**: https://isocpp.org/
- **Borrador del estándar (eel.is)**: https://eel.is/c++draft/
- **CMake**: https://cmake.org/cmake/help/latest/
- **Catch2**: https://github.com/catchorg/Catch2/tree/devel/docs
- **Compiler Explorer**: https://godbolt.org/
- **Compiler support**: https://en.cppreference.com/w/cpp/compiler_support

---

## 🔗 Enlaces Importantes

- **Repositorio**: https://github.com/ergrato-dev/bc-cpp
- **Documentación general**: [docs/README.md](../docs/README.md)
- **Primera semana**: [bootcamp/week-01-toolchain_y_compilacion/README.md](../bootcamp/week-01-toolchain_y_compilacion/README.md)

---

## ✅ Checklist para Nuevas Semanas

- [ ] Estructura de carpetas completa
- [ ] `README.md` con las 10 secciones obligatorias (incluida `🎩 Trucos y atajos`)
- [ ] Teoría en `1-teoria/`, un archivo por concepto (~250 líneas cada uno)
- [ ] Cada término técnico nuevo definido en su primera aparición
- [ ] Todo fragmento de código de la teoría compila (o se marca como ❌ con su diagnóstico)
- [ ] Prácticas con patrón descomentar, tests escritos en el starter, sin `solution/`
- [ ] `./scripts/compilar-starters.sh week-NN` pasa en debug y asan
- [ ] Proyecto que añade una capa al proyecto hilo conductor, con adaptación por dominio
- [ ] Ningún concepto usado antes de la semana en que se enseña
- [ ] Lo que sea C++23 marcado con su alternativa en C++20
- [ ] Recursos en las tres subcarpetas, cada uno con su justificación
- [ ] Glosario A-Z con el término inglés del estándar entre paréntesis
- [ ] `rubrica-evaluacion.md` con cuestionario + respuestas en `<details>`
- [ ] Trucos replicados en `docs/trucos-cpp.md`
- [ ] SVG con la paleta del bootcamp, todos enlazados
- [ ] Navegación anterior/siguiente correcta
- [ ] `./scripts/verificar-enlaces.sh` sin errores

---

## 💡 Notas Finales

- **Prioridad**: profundidad sobre cobertura
- **Enfoque**: escribir y medir C++, no leer sobre C++
- **Objetivo**: formar desarrolladores C++, no coleccionistas de sintaxis
- **Filosofía**: si no compila con `-Werror` y no tiene un test, no es un entregable

---

_Última actualización: septiembre de 2026_
_Versión: 1.0 · C++20 · GCC 13+ / Clang 17+ / CMake 3.28+_
