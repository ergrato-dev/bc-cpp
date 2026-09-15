# Semana 02 — Control de flujo, funciones y referencias

> Un programa que no decide, no repite y no divide su trabajo en funciones es una
> calculadora de una sola operación. Esta semana el código empieza a tener forma, y con
> la forma llegan las tres preguntas que persiguen a todo programador de C++: ¿copio o
> refiero?, ¿hasta dónde vive esto?, ¿y qué pasa si me salgo del rango?

En la Semana 01 el programa era una lista de instrucciones que se ejecutaban de arriba
abajo. Esta semana aprendes a bifurcar (`if`, `switch`), a repetir (`while`, `for`), a
empaquetar trabajo en funciones y a pasarles datos sin copiarlos (referencias). Con eso
ya puedes escribir un intérprete de comandos y una caja de utilidades de texto. Y como
por primera vez tocas entrada del usuario y rangos de un `vector`, es también la semana
en que el **comportamiento indefinido** deja de ser una nota al pie y pasa a tener su
propio archivo.

---

## 🎯 Objetivos de la Semana

Al finalizar esta semana serás capaz de:

- **Escribir** condicionales con `if`/`else` y `switch` sobre un `enum class`, sin
  *fallthrough* accidental
- **Elegir** entre `while`, `for` clásico y `for` de rango según lo que recorres
- **Declarar y definir** funciones con parámetros, valor de retorno, sobrecarga y
  `[[nodiscard]]`
- **Decidir** si un parámetro va por valor, por referencia o por referencia constante,
  y justificarlo por coste y por intención
- **Predecir** el ámbito y la duración de cualquier variable, y reconocer una
  referencia que sobrevive a lo que refiere
- **Usar** `std::string`, `std::string_view` y `std::vector` como herramientas diarias:
  buscar, recortar, partir, añadir, recorrer
- **Validar** entrada de texto con `std::getline` y `std::istringstream` sin confiar en
  una sola línea que venga del usuario
- **Reconocer** cinco formas de comportamiento indefinido y **nombrar** el flag o el
  sanitizer que detecta cada una

---

## 📋 Prerrequisitos

- [Semana 01](../week-01-toolchain_y_compilacion/README.md) completa: sabes configurar
  y construir con presets, leer un error de compilación y usar `std::format`.
- Los presets `debug` y `asan` funcionando en tu máquina (`ctest --preset asan` en
  verde en el ejercicio 02 de la Semana 01).
- Tu repositorio `bc-cpp-<tu-dominio>` con la rama `week-01` fusionada en `main`.

---

## 🗂️ Estructura de la Semana

```
week-02-control_funciones_referencias/
├── README.md                    # este archivo
├── rubrica-evaluacion.md        # cómo se evalúa la semana
├── 0-assets/                    # 3 diagramas SVG
├── 1-teoria/                    # 6 archivos, un concepto cada uno
├── 2-practicas/                 # 2 ejercicios guiados con starter/ y tests
├── 3-proyecto/                  # la capa 1 de tu sistema: menú CRUD en memoria
├── 4-recursos/                  # libros, vídeos y webgrafía
└── 5-glosario/                  # los términos de esta semana, A-Z
```

---

## 📝 Contenidos

### Teoría

| Archivo | Tema | Duración |
| ------- | ---- | -------- |
| [01 · Control de flujo](1-teoria/01-control-de-flujo.md) | `if`/`else`, `switch` con `enum class`, `while`, `for`, `for` de rango, `break`/`continue` | 30 min |
| [02 · Funciones](1-teoria/02-funciones.md) | Declarar, definir, parámetros por valor / referencia / `const&`, sobrecarga, `[[nodiscard]]` | 35 min |
| [03 · Alcance y duración](1-teoria/03-alcance-y-duracion.md) | Bloques, *shadowing*, la pila de llamadas, `static`, `namespace`, referencias colgantes | 30 min |
| [04 · `std::string` y `std::string_view`](1-teoria/04-string-y-string-view.md) | Construir, buscar, recortar, comparar; vistas sin copia y su vida útil; leer y partir líneas | 30 min |
| [05 · `std::vector` y agregados](1-teoria/05-vector-y-agregados.md) | Añadir, recorrer, indexar, borrar; `struct` como paquete de datos; `vector` de agregados | 30 min |
| [06 · Comportamiento indefinido](1-teoria/06-comportamiento-indefinido.md) | Qué es, por qué existe, el mapa de comportamientos, las cinco trampas y qué las detecta | 25 min |

### Prácticas

| Ejercicio | Qué haces | Duración |
| --------- | --------- | -------- |
| [01 · Intérprete de comandos](2-practicas/ejercicio-01-interprete-de-comandos/README.md) | Funciones, `enum class` + `switch`, referencias de salida, validación de líneas, bucle de lectura | 75 min |
| [02 · Utilidades de cadenas](2-practicas/ejercicio-02-utilidades-de-cadenas/README.md) | `trim`, `to_upper`, `split`, `join`, `replace_all` con `string_view` y `vector`; un desbordamiento cazado por ASan | 75 min |

### Proyecto

Tu sistema deja de ser tres registros fijos: un `std::vector` de tu recurso, funciones
libres de alta, baja, búsqueda y listado, y un bucle de comandos que valida cada línea
antes de tocar nada. → [3-proyecto/README.md](3-proyecto/README.md)

---

## ⏱️ Distribución del Tiempo (10 horas)

| Actividad | Tiempo |
| --------- | ------ |
| Teoría (6 archivos) | 3 h |
| Ejercicio 01 | 1 h 15 min |
| Ejercicio 02 | 1 h 15 min |
| Proyecto | 3 h |
| Recursos y glosario | 1 h |
| Autoevaluación (cuestionario de la rúbrica) | 30 min |
| **Total** | **10 h** |

---

## 🎩 Trucos y atajos

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

---

## 📌 Entregables

1. ✅ Ejercicio 01: `ctest --preset debug` y `ctest --preset asan` con 5 de 5 en verde
2. ✅ Ejercicio 02: 5 de 5 en verde, y el Paso 6 (desbordamiento cazado por ASan) hecho y deshecho
3. ✅ Proyecto: rama `week-02` con `std::vector<Recurso>`, funciones `add_`, `remove_`,
   `find_`, `list_`, bucle de comandos con validación, y al menos 8 tests con entrada por
   tubería, todos en verde en `debug` y `asan`
4. ✅ Pull request `week-02` → `main` con la salida de `ctest --preset asan`
5. ✅ Cuestionario de la [rúbrica](rubrica-evaluacion.md) respondido antes de mirar las soluciones

---

## ✅ Verificación

En cada `starter/` (ejercicios y proyecto):

```bash
cmake --preset asan && cmake --build --preset asan && ctest --preset asan
```

Tiene que salir `100% tests passed` sin ningún `runtime error` ni `AddressSanitizer`.
Los tests de esta semana alimentan al programa por `stdin` con `printf ... | app`; si
un test falla, `ctest --preset asan -R nombre` te enseña la salida real.

---

## 🔗 Navegación

| Anterior | Actual | Siguiente |
| -------- | ------ | --------- |
| [Semana 01 — Toolchain y compilación](../week-01-toolchain_y_compilacion/README.md) | **Semana 02** | Semana 03 (próximamente) |

← [Volver al inicio del bootcamp](../../README.md)
