# 📚 Ebooks Gratuitos — Semana 02: Control de flujo, funciones y referencias

Todo lo de esta lista es gratuito y legal. Cada entrada dice por qué vale la pena esta
semana, no solo qué es.

---

### C++ Core Guidelines

- **Autores**: Bjarne Stroustrup, Herb Sutter y la comunidad (ISO C++)
- **Formato**: web, un solo documento largo, actualizado continuamente
- **Enlace**: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
- **Por qué leerlo**: esta semana las reglas de la sección **F (Functions)** son
  literalmente la Teoría 02 con más ejemplos: cómo pasar parámetros, qué devolver,
  cuándo una función es demasiado larga. Y la sección **ES (Expressions and
  statements)** cubre el control de flujo y el alcance.
- **Secciones para esta semana**: `F.15`-`F.21` (parámetros), `F.43` (nunca devolver
  referencia a local), `ES.5` (alcances pequeños), `ES.12` (no tapar nombres),
  `ES.20` (inicializar siempre), `ES.70`-`ES.79` (`switch`, `for` de rango, caída),
  `SL.str.1`-`SL.str.2` (`string` y `string_view`), `SL.con.2` (`vector` por defecto).

---

### Learn C++ (learncpp.com)

- **Autor**: Alex (mantenido por la comunidad)
- **Formato**: web, lecciones cortas numeradas
- **Enlace**: https://www.learncpp.com/
- **Por qué leerlo**: la segunda pasada, más despacio, de todo lo de esta semana.
  Sus capítulos sobre funciones y referencias tienen decenas de ejemplos de "¿copia
  o no copia?" con la respuesta razonada.
- **Capítulos para esta semana**: 2 (Functions and Files), 7 (Scope, Duration, and
  Linkage), 8 (Control Flow), 12 (Compound Types: References and Pointers, solo las
  lecciones de referencias), 16 (`std::vector`), 5.7-5.10 (`std::string` y
  `std::string_view`).

---

### C++ Annotations

- **Autor**: Frank B. Brokken (Universidad de Groninga)
- **Formato**: web, PDF, ePub; muy extenso; se actualiza cada año
- **Enlace**: https://fbb-git.gitlab.io/cppannotations/
- **Por qué leerlo**: el capítulo sobre `std::string` es una referencia completa de
  sus miembros con ejemplos, más ordenada que cppreference para leerla de corrido.
- **Capítulos para esta semana**: 3.3 (Scope resolution), 5 (The `string` data
  type), 12.4.2 (`vector`).

---

### A Guide to Undefined Behavior in C and C++

- **Autor**: John Regehr (Universidad de Utah)
- **Formato**: tres entradas de blog, ~40 minutos de lectura en total
- **Enlace**: https://blog.regehr.org/archives/213
- **Por qué leerlo**: la explicación más clara escrita de por qué el compilador hace
  lo que hace con el UB, con ejemplos que se pueden pegar en Compiler Explorer. Es la
  lectura que convierte "el UB es peligroso" en "entiendo exactamente qué asume el
  compilador". Las partes 2 y 3 enlazan desde la 1.

---

### What Every C Programmer Should Know About Undefined Behavior

- **Autor**: Chris Lattner (creador de LLVM y Clang), blog de LLVM
- **Formato**: tres entradas de blog
- **Enlace**: https://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html
- **Por qué leerlo**: la misma historia contada desde dentro del compilador: qué
  optimizaciones dependen de que el UB no ocurra y qué pasaría con el rendimiento si
  se definieran. Complementa a Regehr; leer los dos deja el tema cerrado.
