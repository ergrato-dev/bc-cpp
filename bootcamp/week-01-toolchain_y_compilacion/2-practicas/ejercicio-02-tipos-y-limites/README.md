# Ejercicio 02 — Mide los tipos de tu máquina

> Al terminar habrás visto cuántos bytes ocupa cada tipo, dónde termina un `int`, por
> qué `7 / 2` es 3, qué hace `unsigned` al bajar de cero, y qué dice el compilador
> cuando intentas meter `3.7` en un entero.

**Duración estimada**: 90 min
**Prerrequisitos**: [Teoría 04](../../1-teoria/04-tipos-variables-y-constantes.md)
leída; [Ejercicio 01](../ejercicio-01-hola-toolchain/README.md) completado.

## Contexto

Todo lo que la Teoría 04 afirma sobre tamaños, rangos y conversiones se puede
comprobar en tu máquina en unas líneas. Eso es lo que vas a hacer: no creerte la tabla,
sino imprimirla. Los cinco primeros pasos tienen test; los dos últimos son
experimentos con el compilador y el sanitizer que no dejan código en el starter.

## Paso 0: Configurar y ver fallar los tests

```bash
cd starter
cmake --preset debug && cmake --build --preset debug && ctest --preset debug
```

**Verifica**: `0% tests passed, 5 tests failed out of 5`.

## Paso 1: `sizeof` — cuántos bytes ocupa cada tipo

**Por qué**: el tamaño de un tipo decide su rango y cuánta memoria gasta cada
variable. `sizeof` lo da en compilación: no cuesta nada en ejecución.

```cpp
std::cout << std::format("sizeof(bool) = {}\n", sizeof(bool));
std::cout << std::format("sizeof(char) = {}\n", sizeof(char));
std::cout << std::format("sizeof(int) = {}\n", sizeof(int));
std::cout << std::format("sizeof(long long) = {}\n", sizeof(long long));
std::cout << std::format("sizeof(double) = {}\n", sizeof(double));
```

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 1.

**Verifica**: `cmake --build --preset debug && ctest --preset debug` → pasa
`paso1_sizeof`. La salida debe ser `1, 1, 4, 8, 8`. Si tu máquina da otra cosa, no es
un error: es que el estándar solo garantiza mínimos. Apúntalo y sigue; el test asume
x86-64 Linux.

## Paso 2: `numeric_limits` — el rango exacto

**Por qué**: "unos dos mil millones" no sirve para decidir si un `int` te vale.
`<limits>` da el valor exacto para cualquier tipo, en compilación.

```cpp
std::cout << std::format("int: {} .. {}\n",
                         std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max());
std::cout << std::format("unsigned: {} .. {}\n",
                         std::numeric_limits<unsigned int>::min(),
                         std::numeric_limits<unsigned int>::max());
```

La sintaxis `std::numeric_limits<int>` (con `<int>` entre ángulos) es un **template**:
un tipo parametrizado por otro tipo. Los verás a fondo en la Semana 07; hoy basta con
leerlo como "los límites de `int`".

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 2.

**Verifica**: pasa `paso2_limites`: `int: -2147483648 .. 2147483647`.

## Paso 3: División entera, resto y conversión explícita

**Por qué**: `7 / 2` con dos `int` da `3`, no `3.5`. Es la sorpresa número uno de
quien viene de Python o JavaScript, y la causa de muchos "la media sale mal".

```cpp
int a{7};
int b{2};
std::cout << std::format("7 / 2 = {}\n", a / b);        // 3: división entera
std::cout << std::format("7 % 2 = {}\n", a % b);        // 1: resto
std::cout << std::format("7 / 2.0 = {}\n", a / 2.0);    // 3.5: un operando es double
std::cout << std::format("static_cast: {}\n", static_cast<double>(a) / b);
```

`static_cast<double>(a)` convierte **a propósito y a la vista**. Es la única forma de
cast que usarás esta fase; `(double)a` (cast de C) está prohibido en el bootcamp.

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 3.

**Verifica**: pasa `paso3_division`.

## Paso 4: `unsigned` da la vuelta

**Por qué**: restar 1 a un `unsigned` que vale 0 no da -1 ni error: da el máximo. Es
**comportamiento definido** por el estándar (aritmética módulo 2³²), y aun así es la
causa de bucles infinitos y tamaños absurdos. Por eso el bootcamp no usa `unsigned`
para cantidades.

```cpp
unsigned int u{0};
u = u - 1;
std::cout << std::format("0u - 1 = {}\n", u);
```

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 4.

**Verifica**: pasa `paso4_unsigned`: `0u - 1 = 4294967295`.

## Paso 5: `constexpr`, `const` y `auto`

**Por qué**: la mayoría de los valores de un programa no cambian nunca. Decirlo
(`constexpr` si se conoce al compilar, `const` si no) documenta la intención y deja
que el compilador vigile. `auto` deduce el tipo del inicializador: `double` aquí.

```cpp
constexpr int kCapacity{100};
constexpr double kVatRate{0.21};
const double price{10.0};
auto price_with_vat{price * (1.0 + kVatRate)};
std::cout << std::format("capacidad: {}, precio con IVA: {:.2f}\n",
                         kCapacity, price_with_vat);
```

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 5.

**Verifica**: pasan los 5 tests. Ahora intenta modificar una constante: añade
`kCapacity = 200;` después de su declaración y construye.

```
error: assignment of read-only variable 'kCapacity'
```

Borra esa línea. Eso es el compilador vigilando por ti.

## Paso 6: Narrowing — el compilador te protege

**Por qué**: `int x = 3.7;` compila y deja `x` en 3 sin decir nada. Con llaves, no.
Tienes que ver ese error una vez para reconocerlo siempre.

Añade **al final de `main`, antes del `return`**:

```cpp
int truncated{3.7};
```

**Verifica**: `cmake --build --preset debug` falla con

```
error: narrowing conversion of '3.7000000000000002e+0' from 'double' to 'int' [-Wnarrowing]
```

(Y además `unused variable 'truncated'`, porque no la usas. Dos errores, una línea.)
Cambia `{3.7}` por `= 3.7` y construye: ahora solo queda el de variable sin usar. Ese
es el punto: **con `=` el truncamiento pasa en silencio**. Borra la línea.

## Paso 7: Desbordamiento con signo — UB detectado por UBSan

**Por qué**: el Paso 4 mostró que `unsigned` da la vuelta de forma definida. Con `int`
no hay definición: es **comportamiento indefinido**, y el compilador puede asumir que
nunca ocurre. UBSan lo caza en ejecución.

> [!WARNING]
> Este código tiene UB a propósito. Se ejecuta **solo** con el preset `asan`, para ver
> el reporte, y se borra después. Nunca queda en un entregable.

Añade al final de `main`, antes del `return`:

```cpp
int big{std::numeric_limits<int>::max()};
big = big + 1;
std::cout << std::format("big = {}\n", big);
```

```bash
cmake --preset asan && cmake --build --preset asan && ./build/asan/app
```

**Verifica**: la última parte de la salida es

```
main.cpp:NN:13: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
big = -2147483648
```

Imprime -2147483648 **en esta máquina, hoy**. Con `-O2` podría imprimir otra cosa, o
el compilador podría eliminar la línea entera: eso significa "indefinido". Borra las
tres líneas.

## Paso final: Sanitizers en verde

```bash
cmake --build --preset asan && ctest --preset asan
```

**Verifica**: `100% tests passed, 0 tests failed out of 5`, sin ningún `runtime error`.

## ✅ Resultado

- [ ] 5 de 5 tests en verde en `debug` y `asan`
- [ ] Sé cuántos bytes ocupan `bool`, `char`, `int`, `long long` y `double` en mi máquina
- [ ] Sé por qué `7 / 2` es 3 y tengo dos formas de obtener 3.5
- [ ] He visto a `unsigned` dar la vuelta y sé por qué eso es legal
- [ ] He visto el error de narrowing y el de asignar a una constante
- [ ] He visto un reporte de UBSan y he borrado el código que lo provocó

## 🧯 Si algo sale mal

| Síntoma | Causa | Solución |
| --- | --- | --- |
| `paso1_sizeof` falla y la salida muestra otros números | Tu plataforma no es x86-64 Linux (ARM, Windows nativo, un compilador de 32 bits) | Los tamaños son correctos para tu máquina; el test asume x86-64. Anótalo y sigue |
| `error: 'numeric_limits' is not a member of 'std'` | Falta `#include <limits>` | El starter lo trae; comprueba que no lo borraste |
| `paso3_division` falla con `7 / 2.0 = 3.5000000000000000` o similar | Cambiaste `{}` por `{:.2f}` o al revés | `{}` imprime la representación más corta: `3.5`. Usa el formato exacto del README |
| En el Paso 7 no aparece `runtime error` | Construiste con `debug`, no con `asan` | El sanitizer solo está en el preset `asan`: `cmake --preset asan && cmake --build --preset asan` |
| `error: unused variable` al añadir el código de los pasos 6 y 7 | Es lo esperado en el Paso 6 (y por eso se imprime `big` en el 7) | Lee el mensaje, entiende por qué, y borra el código como dice el paso |
