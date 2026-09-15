# Ejercicio 01 — Intérprete de comandos

> Al terminar tendrás un programa que lee órdenes línea a línea (`add 3 4`, `help`,
> `quit`), las reparte con un `switch` sobre un `enum class`, devuelve resultados a
> través de referencias, y rechaza cualquier línea que no sea exactamente lo que
> espera. Es el esqueleto de todos los programas interactivos del bootcamp.

**Duración estimada**: 75 min
**Prerrequisitos**: [Teoría 01](../../1-teoria/01-control-de-flujo.md),
[02](../../1-teoria/02-funciones.md) y [04](../../1-teoria/04-string-y-string-view.md)
leídas.

## Contexto

Un intérprete de comandos es un bucle: lee una línea, decide qué es, la ejecuta,
vuelve a leer. Ese bucle es el mismo en una calculadora, en un menú de inventario y
en un cliente de red. Aquí lo construyes en cinco pasos, y en cada uno el test te
dice si la pieza encaja. Los tests **alimentan al programa por `stdin`** con una
tubería (`printf 'add 3 4\n' | app`), así que nunca tecleas nada: escribes la entrada
una vez y la ejecutas mil.

## Paso 0: Configurar y ver fallar los tests

```bash
cd starter
cmake --preset debug && cmake --build --preset debug && ctest --preset debug
```

**Verifica**: `0% tests passed, 5 tests failed out of 5`. El programa compila (con
`-Wshadow` además de los flags de siempre) y no hace nada: `main` está vacío.

## Paso 1: El bucle de lectura

**Por qué**: `std::getline` devuelve algo que vale `false` cuando la entrada se acaba,
y eso lo convierte en la condición perfecta de un `while`: el bucle dura exactamente
lo que dure la entrada, venga del teclado o de una tubería.

```cpp
std::string line{};
while (std::getline(std::cin, line)) {   // false cuando se acaba la entrada
  if (line.empty()) {
    continue;                             // línea en blanco: siguiente
  }
  // ... (Paso 2)
}
std::cout << "adiós\n";                   // se acabó la entrada sin `quit`
```

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 1, **dentro de
`main`**. Fíjate en que el bloque contiene, más adentro y todavía comentado, el código
del Paso 2: déjalo comentado por ahora.

**Verifica**: `cmake --build --preset debug && ctest --preset debug` → pasa
`paso1_adios`. El test ejecuta el programa con entrada vacía; lo único que puede
imprimir es la despedida.

Pruébalo tú: `printf 'hola\n\n\nmundo\n' | ./build/debug/app` imprime solo `adiós`.
Y sin tubería, `./build/debug/app` espera a que teclees; termina con `Ctrl-D`
(fin de entrada).

## Paso 2: `enum class` y `switch`

**Por qué**: la primera palabra de la línea es el comando, y el conjunto de comandos
es cerrado. Eso pide un `enum class` y un `switch` sin `default`: si mañana añades un
comando, `-Wswitch` te señalará cada sitio que se te olvidó actualizar (lo vas a ver
en el Paso 5).

Arriba de `main`, el tipo y la función que traduce texto a `Command`:

```cpp
enum class Command { add, sub, mul, help, quit, unknown };

[[nodiscard]] Command parse_command(std::string_view word) {
  if (word == "add") {
    return Command::add;
  }
  // ... sub, mul, help, quit
  return Command::unknown;
}
```

`unknown` es un valor más del enum: "no reconocido" es un caso que el `switch` tiene
que tratar, no un error de programa. Dentro del bucle, partir y despachar:

```cpp
std::istringstream iss{line};
std::string word{};
iss >> word;                          // la primera palabra es el comando
const Command cmd{parse_command(word)};
switch (cmd) {
  case Command::help:
    std::cout << "comandos: add sub mul help quit\n";
    break;
  case Command::quit:
    std::cout << "adiós\n";
    return 0;                         // sale de main: no se lee nada más
  case Command::unknown:
    std::cout << "error: comando desconocido: " << word << '\n';
    break;
  case Command::add:
  case Command::sub:
  case Command::mul: {
    // ... (Paso 3)
    break;
  }
}
```

`std::istringstream iss{line}` convierte la línea en un flujo del que `>>` lee
palabra a palabra. Los tres comandos aritméticos comparten un bloque: eso **no** es
*fallthrough* accidental, es una lista de etiquetas para el mismo código.

**Abre `starter/src/main.cpp`** y descomenta las **dos** secciones del Paso 2: la de
arriba de `main` (enum y `parse_command`) y la de dentro del bucle. Deja comentado lo
que esté marcado como Paso 3 o Paso 5.

**Verifica**: pasa `paso2_help_y_quit`. Ese test envía `help`, `foo`, `quit` y otro
`help`: espera la lista, el error de comando desconocido, la despedida, y **que el
segundo `help` no se ejecute**. Si ves dos listas de comandos, tu `quit` hace `break`
en vez de `return`.

## Paso 3: Operandos por referencia

**Por qué**: `read_operands` tiene que devolver **tres** cosas: si la lectura fue
bien, y los dos números. Un `return` solo devuelve una. La solución clásica: el `bool`
por `return` y los números por **referencias de salida**, variables del llamador que
la función rellena.

```cpp
[[nodiscard]] bool read_operands(std::istringstream& in, int& a, int& b) {
  if (!(in >> a >> b)) {
    return false;
  }
  return true;
}

[[nodiscard]] int apply(Command cmd, int a, int b) {
  switch (cmd) {
    case Command::add:
      return a + b;
    case Command::sub:
      return a - b;
    case Command::mul:
      return a * b;
    case Command::help:
    case Command::quit:
    case Command::unknown:
      return 0;
  }
  return 0;
}
```

`in` también va por referencia, y no constante: leer de un flujo **lo modifica** (la
posición de lectura avanza). `apply` lista los casos que nunca le llegarán para que
el `switch` esté completo: así `-Wswitch` seguirá vigilando también aquí. El `return
0;` final es para el compilador, que no sabe que el `switch` cubre todo.

En el bloque compartido de `main`:

```cpp
int a{};
int b{};
if (!read_operands(iss, a, b)) {
  std::cout << "error: se esperaban dos enteros\n";
  break;
}
std::cout << "= " << apply(cmd, a, b) << '\n';
```

`[[nodiscard]]` en `read_operands` es lo que hace que escribir `read_operands(iss,
a, b);` sin el `if` no compile: el `bool` es la parte importante.

**Abre `starter/src/main.cpp`** y descomenta las dos secciones del Paso 3: las
funciones arriba de `main` y el bloque dentro del `switch`.

**Verifica**: pasa `paso3_aritmetica` (`= 7`, `= 6`, `= 42`). Sigue fallando
`paso4_validacion`: ahora mismo `add 3 4 5` responde `= 7` e ignora el 5.

## Paso 4: No confiar en la línea

**Por qué**: `in >> a >> b` falla si faltan números o si no son números, pero **no**
si sobran. `add 3 4 5` pasa la lectura y el `5` se queda en el flujo sin que nadie lo
mire. Una línea que no es exactamente lo que se espera es una línea inválida; la
regla del bootcamp desde hoy: **validar toda la entrada, no solo el principio**.

```cpp
in >> std::ws;          // salta espacios finales
if (!in.eof()) {        // queda algo que no se ha leído
  return false;
}
```

`std::ws` consume espacios en blanco; `eof()` es `true` si después de eso el flujo se
acabó. `add 3 4 ` (con espacio final) sigue siendo válido; `add 3 4 5` y `add 3 4x`,
no.

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 4, dentro de
`read_operands`.

**Verifica**: pasa `paso4_validacion`: tres errores y un `= 7`. Sigue fallando
`paso5_div`: `div` todavía es un comando desconocido.

## Paso 5: Añadir `div` y dejar que `-Wswitch` haga la lista

**Por qué**: añadir un comando toca cuatro sitios (el enum, `parse_command`, `apply`
y el `switch` de `main`). Nadie se acuerda de los cuatro. El compilador sí.

Primero **añade `div` al enum**, entre `mul` y `help`:

```cpp
enum class Command { add, sub, mul, div, help, quit, unknown };
```

Construye **sin descomentar nada más**:

```bash
cmake --build --preset debug
```

**Verifica**: dos errores, uno por cada `switch`:

```
error: enumeration value 'div' not handled in switch [-Werror=switch]
```

Esa es tu lista de tareas. Ahora descomenta las **cuatro** secciones marcadas como
Paso 5: en `parse_command`, en `apply`, la etiqueta `case Command::div:` del
`switch` de `main`, y la comprobación de división entre cero justo antes de llamar a
`apply`. Actualiza también el texto de `help` para que incluya `div`.

```cpp
if (cmd == Command::div && b == 0) {
  std::cout << "error: división entre cero\n";
  break;
}
```

Dividir un entero entre cero es comportamiento indefinido
([Teoría 06](../../1-teoria/06-comportamiento-indefinido.md)); se comprueba **antes**
de que `apply` lo intente, no después.

**Verifica**: pasan los 5 tests. `printf 'div 7 0\n' | ./build/debug/app` responde con
el error y no con `Floating point exception`.

## Paso 6: Ver la división entre cero con UBSan

**Por qué**: para saber qué caza el sanitizer tienes que verlo cazar una vez.

> [!WARNING]
> Este paso provoca UB a propósito. Se ejecuta con el preset `asan` para ver el
> reporte y se deshace después.

Comenta temporalmente el `if (cmd == Command::div && b == 0)` y construye con `asan`:

```bash
cmake --preset asan && cmake --build --preset asan
printf 'div 7 0\n' | ./build/asan/app
```

**Verifica**: la salida contiene

```
main.cpp:NN:MM: runtime error: division by zero
```

Vuelve a descomentar el `if`. `ctest --preset asan` tiene que volver a dar 5 de 5.

## Paso final: Sanitizers en verde

```bash
cmake --build --preset asan && ctest --preset asan
```

**Verifica**: `100% tests passed, 0 tests failed out of 5`, sin ningún `runtime
error`.

## ✅ Resultado

- [ ] 5 de 5 tests en verde en `debug` y `asan`
- [ ] Sé por qué `std::getline` sirve como condición de `while`
- [ ] Sé qué es una referencia de salida y por qué `read_operands` devuelve `bool`
- [ ] He visto a `-Wswitch` señalar los dos `switch` incompletos al añadir `div`
- [ ] Sé qué hace `in >> std::ws; in.eof()` y qué entrada rechaza
- [ ] He visto el reporte `division by zero` de UBSan y he restaurado la comprobación

## 🧯 Si algo sale mal

| Síntoma | Causa | Solución |
| --- | --- | --- |
| `paso2_help_y_quit` falla y la salida tiene dos veces `comandos:` | El `case Command::quit` hace `break` en vez de `return 0` | `return 0;` sale de `main`; `break` solo sale del `switch` |
| `error: 'Command' does not name a type` | Descomentaste el bloque de `main` del Paso 2 pero no el de arriba (el enum) | Los pasos 2 y 3 tienen dos secciones cada uno: arriba de `main` y dentro |
| `error: ignoring return value of 'bool read_operands(...)'` | Llamaste a `read_operands` sin usar el `bool` | Ese es el punto de `[[nodiscard]]`: `if (!read_operands(...))` |
| `paso4_validacion` falla: `add 3 4 5` responde `= 7` | El Paso 4 (dentro de `read_operands`) sigue comentado | Descomenta `in >> std::ws; if (!in.eof())` |
| `error: enumeration value 'div' not handled in switch` | Añadiste `div` al enum y falta algún `case` | Es la lista de tareas del Paso 5: un `case` por `switch` |
| `error: declaration of 'line' shadows a previous local` | Declaraste otra `line` dentro del bucle | `-Wshadow` está activo esta semana. Usa otro nombre |
| Sin tubería, el programa "se queda colgado" | Espera entrada del teclado | Teclea comandos y termina con `quit` o `Ctrl-D` |
| En Windows/MSVC el test no encuentra `sh` | Los tests usan `sh -c "printf ... \| app"`, que es POSIX | Usa WSL2, como indica `docs/setup.md` |
