# Rúbrica de Evaluación — Semana 01: Toolchain y compilación

## 📊 Distribución de Evidencias

| Tipo | Peso | Instrumento |
| ---- | ---- | ----------- |
| Conocimiento 🧠 | 30% | Cuestionario de autoevaluación (10 preguntas) |
| Desempeño 💪 | 40% | Ejercicios 01 y 02 verificados por `ctest` |
| Producto 📦 | 30% | Proyecto semanal: esqueleto del sistema del dominio |

**Nota mínima para aprobar**: 70% en cada tipo de evidencia.

---

## 🧠 Conocimiento (30%)

### Cuestionario — Toolchain y compilación

Responde sin mirar la teoría. Las respuestas están al final, plegadas.

| # | Pregunta | Puntaje |
| - | -------- | ------- |
| 1 | ¿Qué diferencia a un lenguaje compilado de uno interpretado, y qué gana C++ con ser compilado? | 10 |
| 2 | Nombra las cuatro etapas del pipeline de `g++` y el archivo que produce cada una. | 10 |
| 3 | Este mensaje: `/usr/bin/ld: main.o: undefined reference to 'sumar(int, int)'`. ¿Qué etapa lo produce y qué tipo de arreglo necesita? | 10 |
| 4 | ¿Qué hace cada flag en `-std=c++20 -Wall -Wextra -Wpedantic -Werror`? | 10 |
| 5 | ¿Qué diferencia hay entre `cmake --preset debug` y `cmake --build --preset debug`, y qué tipo de error puede salir en cada uno? | 10 |
| 6 | ¿Por qué `int x{3.7};` no compila y `int x = 3.7;` sí? ¿Cuál es peor? | 10 |
| 7 | ¿Cuándo usas `constexpr`, cuándo `const`, y cuándo ninguno? | 10 |
| 8 | ¿Qué imprime `std::cout << 7 / 2;` y por qué? Da dos formas de obtener `3.5`. | 10 |
| 9 | `unsigned int u{0}; u = u - 1;` ¿Es comportamiento definido? ¿Y `int i{INT_MAX}; i = i + 1;`? | 10 |
| 10 | ¿Por qué los avisos van a `std::cerr` y no a `std::cout`? Da una razón práctica comprobable en la terminal. | 10 |

**Total**: 100 puntos → 30% de la nota final.

<details>
<summary>Respuestas</summary>

1. Compilado: un programa (el compilador) traduce el código a código máquina **una vez**; el resultado se ejecuta solo. Interpretado: un intérprete lee y ejecuta el código cada vez. C++ gana rendimiento predecible y ejecutables sin dependencias en tiempo de ejecución; paga con un paso extra y con que el compilador necesita conocer todos los tipos de antemano.
2. Preprocesado (`cpp`) → `.ii`; compilación (`cc1plus`) → `.s` (ensamblador); ensamblado (`as`) → `.o` (código objeto); enlace (`ld`) → ejecutable.
3. Lo produce el **enlazador** (etapa 4). No es sintaxis: la función está declarada pero ninguna unidad de traducción la define, o el `.cpp` que la define no está en la orden de compilación (o en `add_executable`). Se arregla añadiendo el archivo, no tocando el cuerpo.
4. `-std=c++20`: estándar del lenguaje. `-Wall`: warnings habituales. `-Wextra`: más warnings. `-Wpedantic`: rechaza extensiones no estándar del compilador. `-Werror`: todo warning es error.
5. `cmake --preset debug` **configura**: lee `CMakeLists.txt`, detecta el compilador, genera `build/debug/build.ninja`. Falla por sintaxis de CMake, compilador no encontrado o dependencia no descargable. `cmake --build --preset debug` **construye**: llama a ninja/g++. Falla con errores de compilación o de enlace.
6. Las llaves rechazan conversiones que pierden información (*narrowing*): `3.7` → `int` pierde el `.7`. Con `=` el compilador convierte y calla: `x` vale 3 sin aviso. **Peor es que compile**: el bug queda escondido.
7. `constexpr` cuando el valor se conoce al compilar (límites, tasas fijas). `const` cuando se calcula en ejecución y luego no cambia. Ninguno solo si la variable necesita cambiar de verdad.
8. Imprime `3`: los dos operandos son `int`, así que es división entera. `3.5` con `7 / 2.0` (un operando `double`) o con `static_cast<double>(7) / 2`.
9. `unsigned`: **definido**, aritmética módulo 2³², da 4294967295. `int`: **comportamiento indefinido** (desbordamiento con signo); UBSan lo reporta como `signed integer overflow`. El compilador puede asumir que nunca ocurre.
10. Porque son canales distintos (descriptores 1 y 2) y la terminal los redirige por separado: `./app > resultado.txt` guarda solo la salida estándar; los avisos por `cerr` siguen en pantalla. Además `cerr` no tiene buffer: sale aunque el programa se caiga justo después.

</details>

---

## 💪 Desempeño (40%)

### Ejercicio 01 — Compila tu primer programa con CMake (20 puntos)

| Criterio | Puntaje |
| -------- | ------- |
| `ctest --preset debug`: 4 de 4 tests en verde | 8 |
| `ctest --preset asan`: 4 de 4 en verde, sin reportes | 4 |
| Paso 5 hecho: sabe mostrar la orden real de `g++` y ha generado `.ii`, `.s` y `.o` | 4 |
| Paso 6 hecho: ha provocado y arreglado un `-Werror=unused-variable` | 4 |
| **Subtotal** | **20** |

### Ejercicio 02 — Mide los tipos de tu máquina (20 puntos)

| Criterio | Puntaje |
| -------- | ------- |
| `ctest --preset debug`: 5 de 5 tests en verde | 8 |
| `ctest --preset asan`: 5 de 5 en verde, sin reportes | 4 |
| Paso 6 hecho: ha visto el error de narrowing y sabe explicar por qué `=` es peor | 4 |
| Paso 7 hecho: ha visto el reporte de UBSan y ha borrado el código con UB | 4 |
| **Subtotal** | **20** |

**Total Desempeño**: 40 puntos → 40% de la nota final.

---

## 📦 Producto (30%)

### Proyecto Semanal — Esqueleto del sistema del dominio

| Criterio | Descripción | Puntaje |
| -------- | ----------- | ------- |
| Compilación | `cmake --build --preset debug` sin un solo warning (`-Werror` activo) | 10 |
| Sanitizers | `ctest --preset asan` en verde, sin reportes | 10 |
| Tests | Mínimo 5 `add_test` con valores calculados a mano; todos pasan | 20 |
| Tipos y constantes | Todo inicializado con `{}`; `constexpr`/`const` bien elegidos; sin números mágicos en los `format` | 20 |
| Salida | Cabecera, tabla alineada con anchos de `format`, estadísticas con los decimales pedidos, media como división real | 15 |
| Adaptación al dominio | Nombres del dominio en inglés; la "cantidad" y el "precio" tienen sentido en ese dominio; el README del proyecto está adaptado | 15 |
| Entrega | Rama `week-01`, pull request con dominio, compilador y salida de `ctest` | 10 |
| **Total** | | **100** |

### Penalizaciones

| Situación | Penalización |
| --------- | ------------ |
| No compila con `-Wall -Wextra -Wpedantic -Werror` | 0 en Producto |
| Fallo de ASan o UBSan en los tests | -20 |
| Variable sin inicializar (`int x;`) | -10 |
| `using namespace std;`, `std::endl`, `printf` o cast de C | -5 cada uno |
| Sin tests propios (solo el `cabecera` del starter) | -15 |
| Test cuyo valor esperado es copiado de la salida del programa sin calcularlo (se pregunta) | -10 |
| Código copiado de otro dominio | 0 en Producto |

---

## 📅 Fecha de Entrega

- **Ejercicios**: al terminar cada uno; se comprueban con `ctest`.
- **Proyecto**: 7 días después del inicio de la semana.
- **Formato**: pull request `week-01` → `main` en el repositorio del estudiante.
