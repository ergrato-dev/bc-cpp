# 🌐 Webografía — Semana 01: Toolchain y compilación

Documentación oficial primero; blogs después. Cada enlace con su motivo.

---

### cppreference.com

- **Enlace**: https://en.cppreference.com/
- **Por qué**: la referencia del estándar escrita para humanos, con ejemplos ejecutables
  y la anotación `(since C++20)` en cada cosa. Es la fuente de verdad del bootcamp;
  cuando este material y cppreference se contradigan, gana cppreference y se abre un
  issue.
- **Páginas de esta semana**:
  [Fundamental types](https://en.cppreference.com/w/cpp/language/types) ·
  [List-initialization](https://en.cppreference.com/w/cpp/language/list_initialization) ·
  [`constexpr`](https://en.cppreference.com/w/cpp/language/constexpr) ·
  [`auto`](https://en.cppreference.com/w/cpp/language/auto) ·
  [`std::format`](https://en.cppreference.com/w/cpp/utility/format/format) ·
  [Format specification](https://en.cppreference.com/w/cpp/utility/format/spec) ·
  [Compiler support](https://en.cppreference.com/w/cpp/compiler_support)

---

### Compiler Explorer

- **Enlace**: https://godbolt.org/
- **Por qué**: compila en el navegador con cualquier versión de GCC, Clang o MSVC, y
  muestra el ensamblador línea a línea. Para "¿esto compila en GCC 13?", "¿qué error da
  Clang aquí?" y "¿qué hace el compilador con esto?", es la respuesta en segundos.

---

### GCC — Manual de opciones

- **Enlace**: https://gcc.gnu.org/onlinedocs/gcc/Invoking-GCC.html
- **Por qué**: qué hace cada flag, de verdad. Las páginas de
  [Overall Options](https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html) (`-E`,
  `-S`, `-c`) y [Warning Options](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
  (`-Wall`, `-Wextra`) son las de esta semana.

---

### Clang — Diagnostic flags

- **Enlace**: https://clang.llvm.org/docs/DiagnosticsReference.html
- **Por qué**: la lista completa de warnings de Clang con ejemplos de qué los dispara.
  Útil cuando un warning no te dice nada y quieres ver el caso que lo motiva.

---

### CMake — Documentación oficial

- **Enlace**: https://cmake.org/cmake/help/latest/
- **Por qué**: el [tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
  (pasos 1-2 esta semana) y las referencias de
  [`cmake-presets(7)`](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) y
  [`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html). Es larga y
  seca, pero es la única fuente que no se queda vieja.

---

### An Introduction to Modern CMake

- **Enlace**: https://cliutils.gitlab.io/modern-cmake/
- **Por qué**: libro web corto que explica por qué el CMake basado en targets es
  mejor que el de variables globales, y cómo reconocer un `CMakeLists.txt` viejo.
  Lee "Introduction" y "The Basics" esta semana.

---

### isocpp.org

- **Enlace**: https://isocpp.org/
- **Por qué**: la web del comité del estándar. Su
  [FAQ](https://isocpp.org/faq) responde a "¿por qué C++ hace X?" con la voz de
  quienes lo diseñaron, y [Get Started](https://isocpp.org/get-started) mantiene la
  lista de libros recomendados si quieres uno de pago.
