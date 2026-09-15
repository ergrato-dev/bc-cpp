# 🌐 Webografía — Semana 02: Control de flujo, funciones y referencias

Documentación oficial primero; blogs después. Cada enlace con su motivo.

---

### cppreference.com

- **Enlace**: https://en.cppreference.com/
- **Por qué**: la fuente de verdad. Esta semana, sobre todo las tablas de miembros de
  `std::string`, `std::string_view` y `std::vector`: cuando dudes de si existe
  `starts_with` o cómo se llama `find_first_not_of`, está aquí con ejemplo.
- **Páginas de esta semana**:
  [`if`](https://en.cppreference.com/w/cpp/language/if) ·
  [`switch`](https://en.cppreference.com/w/cpp/language/switch) ·
  [Range-based for](https://en.cppreference.com/w/cpp/language/range-for) ·
  [Functions](https://en.cppreference.com/w/cpp/language/functions) ·
  [Reference declaration](https://en.cppreference.com/w/cpp/language/reference) ·
  [Scope](https://en.cppreference.com/w/cpp/language/scope) ·
  [Storage duration](https://en.cppreference.com/w/cpp/language/storage_duration) ·
  [`std::string`](https://en.cppreference.com/w/cpp/string/basic_string) ·
  [`std::string_view`](https://en.cppreference.com/w/cpp/string/basic_string_view) ·
  [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) ·
  [Aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization) ·
  [Undefined behavior](https://en.cppreference.com/w/cpp/language/ub)

---

### C++ Core Guidelines — sección F (Functions)

- **Enlace**: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-functions
- **Por qué**: la tabla "¿cómo paso este parámetro?" de la Teoría 02 sale de F.15-F.21.
  Cada regla tiene ejemplo bueno, ejemplo malo y el porqué. Es la página a la que
  volver cada vez que escribas una firma.

---

### Abseil — Tip of the Week #1: `string_view`

- **Enlace**: https://abseil.io/tips/1
- **Por qué**: dos páginas del equipo de C++ de Google sobre cuándo usar
  `string_view` y cuándo no. Los "Tips of the Week" son cortos, concretos y están
  escritos por gente que mantiene millones de líneas; el #1 es exactamente la Teoría
  04. El [#77 (Temporaries, moves, and copies)](https://abseil.io/tips/77) es para
  la Semana 05, pero explica ya por qué devolver por valor no copia.

---

### GCC — Warning Options

- **Enlace**: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
- **Por qué**: busca en la página `-Wshadow`, `-Wswitch`, `-Wimplicit-fallthrough`,
  `-Wreturn-local-addr`, `-Wdangling-reference` y `-Wuninitialized`: los seis warnings
  de esta semana, con qué código los dispara y en qué grupo (`-Wall`, `-Wextra` o
  ninguno) están.

---

### libstdc++ — Debug Mode y `_GLIBCXX_ASSERTIONS`

- **Enlace**: https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode.html
- **Por qué**: qué comprueba exactamente `-D_GLIBCXX_ASSERTIONS` (índices, iteradores
  inválidos, precondiciones) y qué cuesta. Es la alternativa barata a ASan que el
  starter del proyecto activa en Debug.

---

### Clang — Sanitizers

- **Enlace**: https://clang.llvm.org/docs/AddressSanitizer.html ·
  https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
- **Por qué**: la lista de lo que caza cada sanitizer, las opciones de ejecución
  (`ASAN_OPTIONS`, `UBSAN_OPTIONS=halt_on_error=1`) y cómo leer un reporte. Valen
  también para GCC, que usa la misma biblioteca de sanitizers.

---

### Compiler Explorer

- **Enlace**: https://godbolt.org/
- **Por qué**: esta semana, para ver la Teoría 06 con tus ojos: pega `fits_one_more`
  con `-O2` y mira cómo la comparación desaparece. Y para comparar qué avisa GCC y qué
  avisa Clang ante la misma referencia colgante: abre dos compiladores en paralelo.
