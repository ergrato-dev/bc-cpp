# Rúbrica de Evaluación — Semana 02: Control de flujo, funciones y referencias

## 📊 Distribución de Evidencias

| Tipo | Peso | Instrumento |
| ---- | ---- | ----------- |
| Conocimiento 🧠 | 30% | Cuestionario de autoevaluación (10 preguntas) |
| Desempeño 💪 | 40% | Ejercicios 01 y 02 verificados por `ctest` |
| Producto 📦 | 30% | Proyecto semanal: menú CRUD en memoria |

**Nota mínima para aprobar**: 70% en cada tipo de evidencia.

---

## 🧠 Conocimiento (30%)

### Cuestionario — Control de flujo, funciones y referencias

Responde sin mirar la teoría. Las respuestas están al final, plegadas.

| # | Pregunta | Puntaje |
| - | -------- | ------- |
| 1 | ¿Por qué un `switch` sobre un `enum class` **sin** `default` es más seguro que con él? ¿Qué flag lo hace posible? | 10 |
| 2 | `void reset(int counter) { counter = 0; }` compila con `-Wall` pero no con `-Wall -Wextra -Werror`. ¿Qué hace de verdad, qué warning produce y cómo se arregla? | 10 |
| 3 | Para cada parámetro, ¿valor, `const&` o `&`?: (a) un `int`, (b) un `std::vector<Item>` que solo se lee, (c) un `std::string` que la función va a modificar para el llamador, (d) un texto de solo lectura que puede venir como literal. | 10 |
| 4 | ¿Qué diferencia hay entre el **alcance** y la **duración** de una variable? Da un ejemplo en que no coincidan. | 10 |
| 5 | `const std::string& r{longest("abcd", "xy")};` con `longest` que devuelve `const std::string&` a uno de sus parámetros. ¿Qué pasa, qué compilador avisa y qué sanitizer lo caza? | 10 |
| 6 | ¿Qué son los "dos números" de un `std::string_view`? ¿Por qué `std::string_view v{a + b};` es UB? | 10 |
| 7 | `std::istringstream in{"add 3 4 5"}; int a{}, b{}; in >> a >> b;` ¿Qué lee, qué queda sin leer, y cómo se detecta que sobra algo? (Fíjate: la primera palabra no es un número.) | 10 |
| 8 | `Item& first{items[0]}; items.push_back(x); first.quantity++;` ¿Es correcto? ¿Por qué? ¿Cómo se escribe bien? | 10 |
| 9 | Nombra las cuatro categorías de comportamiento del estándar y clasifica: `sizeof(int)`, `unsigned u{0}; u - 1`, `int i{INT_MAX}; i + 1`, `v[v.size()]`. | 10 |
| 10 | Un compañero dice: "lo ejecuté con `-O0` diez veces y siempre imprime 3; no hay UB". Da dos argumentos técnicos en contra y di qué haría falta para convencerte. | 10 |

**Total**: 100 puntos → 30% de la nota final.

<details>
<summary>Respuestas</summary>

1. Sin `default`, si el enum gana un valor y a un `switch` le falta su `case`, GCC y Clang avisan con `-Wswitch` (en `-Wall`): `enumeration value 'x' not handled in switch`. Con `-Werror` es un error, y el compilador te da la lista de sitios que actualizar. Un `default` silencia ese aviso: el valor nuevo cae en él sin que nadie se entere.
2. Modifica una **copia**: el `hits` del llamador no cambia. GCC/Clang con `-Wextra`: `parameter 'counter' set but not used [-Wunused-but-set-parameter]`. Se arregla con `int& counter` (referencia: la función escribe en la variable del llamador) o devolviendo el valor nuevo.
3. (a) por valor: copiar un `int` cuesta lo mismo que mirarlo. (b) `const std::vector<Item>&`: sin copia, promesa de no tocar. (c) `std::string&`: la función escribe en la variable del llamador. (d) `std::string_view`: vista sin copia que acepta literales sin construir un `std::string` temporal.
4. **Alcance**: desde dónde se puede nombrar (decidido al compilar). **Duración**: hasta cuándo existe en memoria (ocurre al ejecutar). No coinciden en una `static` local (alcance del bloque, duración de todo el programa) y en una referencia colgante (el nombre sigue visible, el objeto ya murió).
5. Los literales `"abcd"` y `"xy"` se convierten en `std::string` **temporales** que mueren al final de la línea; `r` queda **colgante** y leerla es UB. GCC 13 avisa con `-Wdangling-reference` (`possibly dangling reference to a temporary`); Clang no avisa. ASan lo reporta como `stack-use-after-scope`. Arreglo: `std::string r{longest(...)}` (copia) o pasar variables con nombre que sobrevivan.
6. Un puntero al primer carácter y una longitud. No posee el texto: lo mira. `a + b` crea un `std::string` temporal que muere al terminar la línea; la vista se queda apuntando a memoria liberada. Arreglo: `std::string joined{a + b};`.
7. `in >> a` intenta leer un entero de `add` y **falla**: `a` queda en 0, el flujo entra en estado de error y `>> b` ya no lee nada. La expresión completa es `false`. Si la entrada fuera `3 4 5`, leería 3 y 4 y dejaría ` 5`; se detecta con `in >> std::ws; if (!in.eof())` (queda algo sin leer). Moraleja: la primera palabra se lee aparte como `std::string`.
8. No. `push_back` puede reubicar el vector en otra memoria; `first` sigue apuntando a la vieja: referencia colgante, UB, ASan lo reporta como `heap-use-after-free`. Bien: guardar el índice (`std::size_t i{0}`) y volver a indexar después del `push_back`: `items[i].quantity++`.
9. Definido, definido por la implementación, no especificado, indefinido. `sizeof(int)`: definido por la implementación (4 en GCC x86-64, documentado). `u - 1`: definido (módulo 2^N, N = bits del tipo; 4294967295 con 32 bits). `i + 1` con `INT_MAX`: indefinido. `v[v.size()]`: indefinido.
10. (1) El UB no promete un resultado ni promete repetirlo: `-O0` diez veces solo dice qué hizo ese compilador con esos flags. (2) El compilador asume que el UB no ocurre: con `-O2` puede eliminar comprobaciones o cambiar el resultado (`x + 1 > x` → `true`). Para convencerme: `ctest --preset asan` sin reportes **y** el mismo resultado con `-O2`.

</details>

---

## 💪 Desempeño (40%)

### Ejercicio 01 — Intérprete de comandos (20 puntos)

| Criterio | Puntaje |
| -------- | ------- |
| `ctest --preset debug`: 5 de 5 tests en verde | 8 |
| `ctest --preset asan`: 5 de 5 en verde, sin reportes | 4 |
| Paso 5 hecho: ha visto los dos errores de `-Wswitch` al añadir `div` y sabe explicar por qué son útiles | 4 |
| Paso 6 hecho: ha visto el `runtime error: division by zero` de UBSan y ha restaurado la comprobación | 4 |
| **Subtotal** | **20** |

### Ejercicio 02 — Utilidades de cadenas (20 puntos)

| Criterio | Puntaje |
| -------- | ------- |
| `ctest --preset debug`: 5 de 5 tests en verde | 8 |
| `ctest --preset asan`: 5 de 5 en verde, sin reportes | 4 |
| Sabe justificar la firma de cada una de las cinco funciones (vista, copia, vector, `const&`, `&`) | 4 |
| Paso 6 hecho: ha visto el desbordamiento pasar en `debug`, fallar en `asan`, y ha borrado el código | 4 |
| **Subtotal** | **20** |

**Total Desempeño**: 40 puntos → 40% de la nota final.

---

## 📦 Producto (30%)

### Proyecto Semanal — Menú CRUD en memoria

| Criterio | Descripción | Puntaje |
| -------- | ----------- | ------- |
| Compilación | `cmake --build --preset debug` sin un solo warning (`-Wall -Wextra -Wpedantic -Wshadow -Werror`) | 10 |
| Sanitizers | `ctest --preset asan` en verde, sin reportes | 10 |
| Tests | Los 2 del starter + mínimo 8 propios con entrada por tubería y valores a mano; incluye `add_uso` con datos sobrantes | 20 |
| Firmas | `vector` por `const&`/`&` según el uso; `string_view` para nombres; `[[nodiscard]]` en las que devuelven `bool` o posición; ningún `vector` por valor | 15 |
| Validación | `read_item` rechaza campos que faltan, que no son números y que sobran; negativos y duplicados rechazados en `add`; ningún índice usado sin comprobar contra `size()` | 15 |
| Separación | `main` solo despacha: no hay `push_back`/`erase` fuera de las funciones; `switch` sin `default`; `namespace` del dominio | 10 |
| Adaptación al dominio | Nombres del dominio en inglés; al menos una regla de validación propia del dominio; README del proyecto adaptado | 10 |
| Entrega | Rama `week-02`, pull request con reglas de validación y salida de `ctest` | 10 |
| **Total** | | **100** |

### Penalizaciones

| Situación | Penalización |
| --------- | ------------ |
| No compila con `-Wall -Wextra -Wpedantic -Wshadow -Werror` | 0 en Producto |
| Fallo de ASan o UBSan en los tests | -20 |
| `add a 1 1 extra` aceptado (no valida la línea completa) | -10 |
| Un `vector` o un `std::string` pasado por valor para solo leerlo | -5 cada uno |
| `switch` con `default` que silencia `-Wswitch` | -5 |
| Variable sin inicializar, `using namespace std;`, `std::endl` o cast de C | -5 cada uno |
| Sin tests propios (solo los 2 del starter) | -15 |
| Test cuyo valor esperado es copiado de la salida del programa sin calcularlo (se pregunta) | -10 |
| Código copiado de otro dominio | 0 en Producto |

---

## 📅 Fecha de Entrega

- **Ejercicios**: al terminar cada uno; se comprueban con `ctest`.
- **Proyecto**: 7 días después del inicio de la semana.
- **Formato**: pull request `week-02` → `main` en el repositorio del estudiante.
