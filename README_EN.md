<p align="center">
  <img src="assets/bootcamp-header.svg" alt="Bootcamp C++ Zero to Hero" width="800">
</p>

<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/license-CC%20BY--NC--SA%204.0-lightgrey.svg" alt="License CC BY-NC-SA 4.0"></a>
  <a href="#"><img src="https://img.shields.io/badge/weeks-20-yellow.svg" alt="20 Weeks"></a>
  <a href="#"><img src="https://img.shields.io/badge/hours-200-orange.svg" alt="200 Hours"></a>
  <a href="#"><img src="https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white" alt="C++20"></a>
  <a href="#"><img src="https://img.shields.io/badge/CMake-3.28%2B-064F8C?logo=cmake&logoColor=white" alt="CMake"></a>
  <a href="#"><img src="https://img.shields.io/badge/Catch2-v3-3fb950" alt="Catch2"></a>
</p>

<p align="center">
  <a href="README.md"><img src="https://img.shields.io/badge/🇪🇸_Español-0969DA?style=for-the-badge&logoColor=white" alt="Versión en Español"></a>
</p>

---

## 📋 Description

A **20-week (~5 months)** bootcamp on **modern C++ (C++20)**, from **absolute zero** to
an **advanced** level: RAII, templates and concepts, the STL, concurrency, coroutines,
measured performance, systems, networking, and hardening with sanitizers and fuzzing.
Self-paced, 10 hours per week, everything verifiable by compilation and tests.

> The course content (theory, exercises, projects) is written in **Spanish**. Code,
> identifiers and commit messages are in English.

### 🎯 Objectives

By the end of the bootcamp, students will be able to:

- ✅ Explain what the preprocessor, compiler and linker do with a `.cpp` file
- ✅ Model data with explicit types, classes and invariants
- ✅ Manage resources with RAII and smart pointers, with no manual `new`/`delete`
- ✅ Tell copy from move and know when the compiler elides both
- ✅ Design hierarchies with dynamic polymorphism and, when appropriate, static
- ✅ Write generic code with templates and concepts that fail with readable messages
- ✅ Pick the right STL container and algorithm and justify it by complexity
- ✅ Model errors with exceptions, `optional`, `variant` and `expected`
- ✅ Organize a project into libraries, modules and CMake targets with tests
- ✅ Compute at compile time with `constexpr`, traits and CRTP
- ✅ Write correct concurrent code and prove it with TSan
- ✅ Use C++20 coroutines for generators and asynchronous pipelines
- ✅ Measure before optimizing: benchmarks, `perf`, memory layout and allocators
- ✅ Talk to the OS: files, processes, `mmap`, sockets, `epoll`
- ✅ Build an HTTP server with Asio and coroutines
- ✅ Harden code with sanitizers, fuzzing and static analysis
- ✅ Design APIs and libraries with a stable ABI, documented and installable

---

## 🗓️ Structure

|        Phase          | Weeks | Hours | Main topics                                                          |
| :-------------------: | :---: | :---: | -------------------------------------------------------------------- |
| **Fundamentals**      |  1-4  |  40h  | Toolchain, types, control flow, memory, pointers, classes, RAII, tests |
| **Modern C++ Core**   | 5-10  |  60h  | Move semantics, smart pointers, polymorphism, templates, STL, ranges, errors |
| **Advanced**          | 11-17 |  70h  | Build, metaprogramming, concurrency, coroutines, performance, systems, networking |
| **Production**        | 18-20 |  30h  | Sanitizers, fuzzing, CI, API design, ABI, final project              |

**Total: 20 weeks** | **200 hours** | **10 hours per week**

---

## 📚 Week by Week

| Week | Topic | Description |
|------|-------|-------------|
| 01 | `toolchain_y_compilacion` | History and standards, g++/clang++, compilation pipeline, minimal CMake, types, I/O |
| 02 | `control_funciones_referencias` | Control flow, functions, references, scope, `string`, `vector`, undefined behavior |
| 03 | `memoria_punteros_arrays` | Stack/heap, pointers, arrays, `span`, `new`/`delete`, gdb, ASan, C strings |
| 04 | `clases_raii_tests` | Classes, constructors, RAII, operators, `<=>`, Catch2, `ctest` |
| 05 | `copia_movimiento_smart_pointers` | Rule of 0/3/5, rvalues, `move`, `forward`, `unique_ptr`, `shared_ptr`, `weak_ptr`, elision |
| 06 | `herencia_polimorfismo` | `virtual`, vtable, interfaces, slicing, RTTI, composition over inheritance |
| 07 | `templates_conceptos` | Templates, deduction, specialization, concepts, variadics, reading errors |
| 08 | `stl_contenedores_iteradores` | Sequences, associative, hashing, iterators, adaptors, choosing a container |
| 09 | `algoritmos_lambdas_ranges` | Lambdas, `<algorithm>`, `<numeric>`, ranges, views, projections |
| 10 | `errores_optional_variant` | Exceptions, guarantees, `noexcept`, `optional`, `variant`, `expected` |
| 11 | `modulos_build_tooling` | ODR, pimpl, C++20 modules, multi-target CMake, clang-tidy, dependencies |
| 12 | `metaprogramacion_constexpr` | `constexpr`/`consteval`, traits, `if constexpr`, CRTP, type erasure |
| 13 | `concurrencia_threads_sincronizacion` | `jthread`, mutex, `condition_variable`, atomics, thread pool, TSan |
| 14 | `memory_model_async_coroutines` | `memory_order`, lock-free, `async`/`future`, `latch`/`barrier`, coroutines |
| 15 | `rendimiento_profiling` | Cache, layout, SoA/AoS, allocators, PMR, benchmarks, `perf`, SIMD |
| 16 | `io_filesystem_sistemas` | `filesystem`, binary I/O, processes, signals, `mmap`, `extern "C"` |
| 17 | `redes_sockets_asio` | POSIX sockets, `epoll`, Asio, networked coroutines, HTTP/1.1 |
| 18 | `seguridad_sanitizers_fuzzing` | ASan/UBSan/TSan, libFuzzer, Core Guidelines, GSL, static analysis, CI |
| 19 | `diseno_patrones_api` | Modern patterns, API design, architecture, ABI, Doxygen, install |
| 20 | `proyecto_final` | Spec, code review, complete domain system, presentation |

---

## 🛠️ Stack

C++20 · GCC 13+ / Clang 17+ · CMake 3.28+ · Ninja · Catch2 v3 · Google Benchmark ·
Asio · gdb/lldb · ASan/UBSan/TSan · libFuzzer · clang-format/clang-tidy · GitHub Actions.
Linux or WSL2 as the primary platform. See [`docs/setup.md`](docs/setup.md).

## 🚀 Quick Start

```bash
git clone https://github.com/ergrato-dev/bc-cpp.git
cd bc-cpp/bootcamp/week-01-toolchain_y_compilacion/2-practicas/ejercicio-01-*/starter
cmake --preset debug && cmake --build --preset debug && ctest --preset debug
```

## 📊 Method and Assessment

- Project-based: one system in the student's own **domain**, growing every week
- Exercises are **uncomment-to-learn** tutorials with Catch2 tests already written
- Weekly assessment: Knowledge 🧠 30% · Performance 💪 40% · Product 📦 30%, minimum 70% each
- Passing bar: compiles with `-Wall -Wextra -Wpedantic -Werror`, `ctest --preset asan` green

Unique-domain (anti-copy) policy: [`docs/dominios.md`](docs/dominios.md).

## 📄 License

[CC BY-NC-SA 4.0](LICENSE). Educational material provided "as is", see the disclaimer in
the [Spanish README](README.md#️-exención-de-responsabilidad).

<p align="center">
  <strong>🎓 Bootcamp C++ Zero to Hero</strong><br>
  <em>If it doesn't compile with -Werror and has no test, it's not a deliverable.</em>
</p>
