<p align="center">
  <img src="assets/bootcamp-header.svg" alt="Bootcamp C++ Zero to Hero" width="800">
</p>

<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/license-CC%20BY--NC--SA%204.0-lightgrey.svg" alt="License CC BY-NC-SA 4.0"></a>
  <a href="#"><img src="https://img.shields.io/badge/semanas-20-yellow.svg" alt="20 Semanas"></a>
  <a href="#"><img src="https://img.shields.io/badge/horas-200-orange.svg" alt="200 Horas"></a>
  <a href="#"><img src="https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white" alt="C++20"></a>
  <a href="#"><img src="https://img.shields.io/badge/CMake-3.28%2B-064F8C?logo=cmake&logoColor=white" alt="CMake"></a>
  <a href="#"><img src="https://img.shields.io/badge/Catch2-v3-3fb950" alt="Catch2"></a>
</p>

<p align="center">
  <a href="README_EN.md"><img src="https://img.shields.io/badge/🇺🇸_English-0969DA?style=for-the-badge&logoColor=white" alt="English Version"></a>
</p>

---

## 📋 Descripción

Bootcamp de **20 semanas (~5 meses)** sobre **C++ moderno (C++20)**, desde **cero
absoluto** hasta un nivel **avanzado**: RAII, templates y conceptos, STL, concurrencia,
coroutines, rendimiento medido, sistemas, redes y endurecimiento con sanitizers y
fuzzing. Autoestudio, 10 horas por semana, con todo verificable por compilación y tests.

### 🎯 Objetivos

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

### 🚀 ¿Por qué C++20?

> **El lenguaje que hay debajo de todo lo demás** — motores, navegadores, bases de
> datos, compiladores, trading, juegos, sistemas embebidos.

C++20 es el primer estándar que hace al lenguaje *cómodo*: conceptos, ranges, `format`,
coroutines, módulos. Este bootcamp lo enseña desde el primer día, sin pasar por el C++
de 1998 "para entender de dónde viene". Lo que se entiende es cómo funciona la máquina;
lo que se escribe es C++ moderno.

---

## 🗓️ Estructura del Bootcamp

|        Fase          | Semanas | Horas | Temas Principales                                                    |
| :------------------: | :-----: | :---: | -------------------------------------------------------------------- |
| **Fundamentos**      |   1-4   |  40h  | Toolchain, tipos, control, memoria, punteros, clases, RAII, tests    |
| **C++ Moderno Core** |  5-10   |  60h  | Movimiento, smart pointers, polimorfismo, templates, STL, ranges, errores |
| **Avanzado**         |  11-17  |  70h  | Build, metaprogramación, concurrencia, coroutines, rendimiento, sistemas, redes |
| **Producción**       |  18-20  |  30h  | Sanitizers, fuzzing, CI, diseño de API, ABI, proyecto final          |

**Total: 20 semanas** | **200 horas** | **10 horas por semana**

---

## 📚 Contenido por Semana

Cada semana incluye:

```
bootcamp/week-XX-tema_principal/
├── README.md                 # Descripción y objetivos
├── rubrica-evaluacion.md     # Criterios de evaluación
├── 0-assets/                 # Diagramas SVG
├── 1-teoria/                 # Material teórico
├── 2-practicas/              # Ejercicios guiados con starter/ (CMake + Catch2)
├── 3-proyecto/               # Capa semanal del proyecto del dominio
├── 4-recursos/               # Recursos adicionales
│   ├── ebooks-free/
│   ├── videografia/
│   └── webgrafia/
└── 5-glosario/               # Términos clave
```

| Semana | Tema | Descripción |
|--------|------|-------------|
| 01 | `toolchain_y_compilacion` | Historia y estándares, g++/clang++, pipeline de compilación, CMake mínimo, tipos, E/S |
| 02 | `control_funciones_referencias` | Control de flujo, funciones, referencias, alcance, `string`, `vector`, comportamiento indefinido |
| 03 | `memoria_punteros_arrays` | Stack/heap, punteros, arrays, `span`, `new`/`delete`, gdb, ASan, cadenas C |
| 04 | `clases_raii_tests` | Clases, constructores, RAII, operadores, `<=>`, Catch2, `ctest` |
| 05 | `copia_movimiento_smart_pointers` | Regla de 0/3/5, rvalues, `move`, `forward`, `unique_ptr`, `shared_ptr`, `weak_ptr`, elisión |
| 06 | `herencia_polimorfismo` | `virtual`, vtable, interfaces, slicing, RTTI, composición sobre herencia |
| 07 | `templates_conceptos` | Templates, deducción, especialización, conceptos, variádicos, leer errores |
| 08 | `stl_contenedores_iteradores` | Secuencias, asociativos, hashing, iteradores, adaptadores, guía de elección |
| 09 | `algoritmos_lambdas_ranges` | Lambdas, `<algorithm>`, `<numeric>`, ranges, views, proyecciones |
| 10 | `errores_optional_variant` | Excepciones, garantías, `noexcept`, `optional`, `variant`, `expected` |
| 11 | `modulos_build_tooling` | ODR, pimpl, módulos C++20, CMake multi-target, clang-tidy, dependencias |
| 12 | `metaprogramacion_constexpr` | `constexpr`/`consteval`, traits, `if constexpr`, CRTP, type erasure |
| 13 | `concurrencia_threads_sincronizacion` | `jthread`, mutex, `condition_variable`, atomics, thread pool, TSan |
| 14 | `memory_model_async_coroutines` | `memory_order`, lock-free, `async`/`future`, `latch`/`barrier`, coroutines |
| 15 | `rendimiento_profiling` | Cache, layout, SoA/AoS, allocators, PMR, benchmarks, `perf`, SIMD |
| 16 | `io_filesystem_sistemas` | `filesystem`, E/S binaria, procesos, señales, `mmap`, `extern "C"` |
| 17 | `redes_sockets_asio` | Sockets POSIX, `epoll`, Asio, coroutines de red, HTTP/1.1 |
| 18 | `seguridad_sanitizers_fuzzing` | ASan/UBSan/TSan, libFuzzer, Core Guidelines, GSL, análisis estático, CI |
| 19 | `diseno_patrones_api` | Patrones modernos, diseño de API, arquitectura, ABI, Doxygen, instalación |
| 20 | `proyecto_final` | Especificación, code review, sistema completo del dominio, presentación |

### 🔑 Componentes Clave

- 📖 **Teoría**: un archivo por concepto, con todo el código compilado
- 💻 **Práctica**: ejercicios guiados por descomentar, con tests Catch2 ya escritos
- 🧵 **Proyecto**: un sistema del dominio del estudiante que crece 20 semanas
- 📝 **Evaluación**: conocimiento, desempeño y producto, verificados por `ctest`
- 🎓 **Recursos**: glosarios, referencias y material complementario

---

## 🛠️ Stack Tecnológico

| Tecnología       | Versión        | Uso                                    |
| ---------------- | -------------- | -------------------------------------- |
| C++              | **C++20**      | Lenguaje (C++23 marcado donde aparece) |
| GCC              | **13+**        | Compilador primario                    |
| Clang            | **17+**        | Compilador secundario, sanitizers, fuzzer, clang-tidy |
| CMake            | **3.28+**      | Build system, presets                  |
| Ninja            | **1.11+**      | Generador (opcional)                   |
| Catch2           | **v3**         | Tests                                  |
| Google Benchmark | **1.9**        | Microbenchmarks (semana 15)            |
| Asio             | **1.38**       | Red asíncrona (semana 17)              |
| gdb / lldb       | **12+ / 17+**  | Depuración                             |
| ASan/UBSan/TSan  | del compilador | Detección de UB, memoria y data races  |
| libFuzzer        | de Clang       | Fuzzing (semana 18)                    |
| clang-format / clang-tidy | **17+** | Formato y análisis estático           |
| GitHub Actions   | —              | CI (semana 18)                         |

**Entorno de desarrollo**: Linux o WSL2 + VS Code (cpptools o clangd) + CMake Tools.
Ver [`docs/setup.md`](docs/setup.md).

---

## 🚀 Inicio Rápido

### Prerrequisitos

- **GCC 13+ o Clang 17+**, **CMake 3.28+** — instalación en [`docs/setup.md`](docs/setup.md)
- **Git**
- **VS Code** (recomendado) con las extensiones de `.vscode/extensions.json`

### 1. Clonar el Repositorio

```bash
git clone https://github.com/ergrato-dev/bc-cpp.git
cd bc-cpp
```

### 2. Verificar el toolchain

```bash
g++ --version && cmake --version
```

### 3. Compilar el primer ejercicio

```bash
cd bootcamp/week-01-toolchain_y_compilacion/2-practicas/ejercicio-01-*/starter
cmake --preset debug && cmake --build --preset debug && ctest --preset debug
```

### 4. Seguir las Instrucciones

Cada semana contiene un `README.md` con objetivos, contenidos, distribución del tiempo
y entregables.

---

## 📊 Metodología de Aprendizaje

### Estrategias Didácticas

- 🎯 **Aprendizaje Basado en Proyectos**: un sistema del dominio que crece cada semana
- 🏛️ **Dominios Únicos**: cada estudiante trabaja sobre su dominio (anticopia)
- 🧩 **Descomentar para aprender**: los ejercicios traen el código explicado y los tests
  escritos; se aprende leyendo, descomentando y viendo pasar tests
- 🔬 **Medir, no suponer**: sanitizers desde la semana 03, benchmarks desde la 15
- 👥 **Code Review**: la semana 20 incluye revisión cruzada

### Distribución del Tiempo (10 h/semana)

| Actividad | Tiempo |
| --------- | ------ |
| Teoría (4-6 archivos) | 3 h |
| Ejercicios guiados (2-3) | 3-3.5 h |
| Proyecto semanal | 3 h |
| Autoevaluación y glosario | 0.5-1 h |

### Evaluación

Cada semana incluye tres tipos de evidencias:

1. **Conocimiento 🧠** (30%): cuestionario con respuestas al final de la rúbrica
2. **Desempeño 💪** (40%): ejercicios verificados por `ctest` en cada starter
3. **Producto 📦** (30%): la capa semanal del proyecto del dominio

**Criterio de aprobación**: mínimo 70% en cada tipo de evidencia. Compila con
`-Wall -Wextra -Wpedantic -Werror`, pasa `ctest --preset asan`, coherente con el
dominio, sin copia.

---

## 🏛️ Política de Dominios Únicos (Anticopia)

Cada estudiante elige (o recibe del instructor) un **dominio único** en la Semana 01 y
lo mantiene las 20 semanas: 📚 Biblioteca, 💊 Farmacia, 🏋️ Gimnasio, 🏫 Escuela,
🐾 Tienda de mascotas, 🍽️ Restaurante, 🏦 Banco, 🚕 Taxis, 🏥 Hospital, 🎬 Cine,
🏨 Hotel, ✈️ Viajes, 🚗 Concesionario, 👕 Ropa, 🔧 Taller y más.

Los ejercicios usan un `Item` genérico; el proyecto se hace sobre el dominio propio.
Catálogo completo y reglas en [`docs/dominios.md`](docs/dominios.md).

---

## 📞 Soporte

- 💬 **Discussions**: [GitHub Discussions](https://github.com/ergrato-dev/bc-cpp/discussions)
- 🐛 **Issues**: [GitHub Issues](https://github.com/ergrato-dev/bc-cpp/issues)
- 🤝 **Contribuir**: [CONTRIBUTING.md](CONTRIBUTING.md)

---

## ⚠️ Exención de Responsabilidad

Este repositorio es un recurso **educativo** creado con fines de aprendizaje. Al utilizarlo, aceptas los siguientes términos:

- **Solo fines educativos**: el contenido, los ejemplos de código y los proyectos están diseñados exclusivamente para la enseñanza y el aprendizaje. No constituyen asesoramiento profesional ni de seguridad.
- **Sin garantías**: el material se proporciona **"tal cual"**, sin garantías de ningún tipo, expresas o implícitas.
- **Código en producción**: los ejemplos son ilustrativos. Antes de usarlos en entornos productivos, realiza revisiones de seguridad, rendimiento y adaptación a tu contexto.
- **Versiones de software**: las versiones de compiladores y bibliotecas mencionadas pueden quedar desactualizadas. Consulta siempre la documentación oficial más reciente.
- **Limitación de responsabilidad**: los autores y contribuidores no se responsabilizan por pérdidas de datos, daños directos o indirectos ni cualquier otro perjuicio derivado del uso de este material.
- **Responsabilidad del estudiante**: cada estudiante es responsable de sus propias implementaciones, entornos y decisiones técnicas.

---

## 📄 Licencia

Este proyecto está bajo la licencia **[CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)** (Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International).

**Puedes:** compartir y adaptar el material, incluso crear forks educativos.
**No puedes:** usar este material con fines comerciales.
**Debes:** dar crédito apropiado y distribuir las adaptaciones bajo la misma licencia.

Ver el archivo [LICENSE](LICENSE) para el texto completo.

---

## 📚 Documentación Adicional

- [`docs/README.md`](docs/README.md) — índice de la documentación transversal
- [`.github/copilot-instructions.md`](.github/copilot-instructions.md) — convenciones de contenido
- [`CODE_OF_CONDUCT.md`](CODE_OF_CONDUCT.md) · [`SECURITY.md`](SECURITY.md)

---

<p align="center">
  <strong>🎓 Bootcamp C++ Zero to Hero</strong><br>
  <em>Si no compila con -Werror y no tiene un test, no es un entregable.</em>
</p>

<p align="center">
  <a href="bootcamp/week-01-toolchain_y_compilacion/README.md">Comenzar Semana 1</a> •
  <a href="docs/README.md">Ver Documentación</a> •
  <a href="https://github.com/ergrato-dev/bc-cpp/issues">Reportar Issue</a>
</p>

<p align="center">Hecho con ❤️ para la comunidad de desarrolladores</p>
