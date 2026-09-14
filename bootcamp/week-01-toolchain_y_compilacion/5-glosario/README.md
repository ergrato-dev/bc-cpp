# Glosario — Semana 01: Toolchain y compilación

Términos clave ordenados alfabéticamente, con el término inglés del estándar o del
toolchain entre paréntesis.

## A

### `auto`
Palabra clave que pide al compilador **deducir** el tipo de una variable a partir de su
inicializador. El tipo existe y es fijo; solo no se escribe. `auto x{9.99};` es `double`.

## B

### build system (sistema de construcción)
Programa que sabe qué archivos dependen de cuáles y ejecuta el compilador solo sobre lo
que cambió. Ninja y Make son build systems; CMake genera los archivos que ellos usan.

### buffer (búfer)
Zona de memoria donde `std::cout` acumula lo escrito antes de enviarlo a la terminal
de golpe. `std::cerr` no lo usa: escribe inmediatamente.

## C

### cast (conversión explícita)
Conversión de un valor a otro tipo pedida a propósito. En C++ moderno,
`static_cast<double>(x)`. El cast de C, `(double)x`, está prohibido en el bootcamp.

### CMake
Generador de build systems: lee `CMakeLists.txt` y produce `build.ninja` o un
`Makefile`. Dos fases: **configurar** (`cmake --preset debug`) y **construir**
(`cmake --build --preset debug`).

### `CMakePresets.json`
Archivo que guarda combinaciones de opciones de CMake con nombre (`debug`, `release`,
`asan`, `tsan`) para no escribirlas en la línea de comandos.

### código objeto (object code)
Salida del ensamblador: instrucciones de máquina con huecos donde iría lo definido en
otros archivos. Extensión `.o`. El enlazador rellena los huecos.

### comportamiento indefinido (undefined behavior, UB)
Situación para la que el estándar no define qué pasa: leer una variable sin
inicializar, desbordar un `int`, indexar fuera de rango. El compilador puede asumir
que nunca ocurre. Se detecta con `-fsanitize=undefined` (UBSan), no a ojo.

### compilador (compiler)
Programa que traduce C++ a ensamblador comprobando tipos y sintaxis. En GCC es
`cc1plus`; `g++` es el driver que lo llama junto con el resto del pipeline.

### `const`
Calificador: la variable no cambia después de inicializarse. Su valor puede calcularse
en ejecución.

### `constexpr`
Calificador: la variable no cambia **y** su valor se conoce al compilar. Para
constantes de verdad: límites, tasas, tamaños. Por convención, `kNombre`.

### `ctest`
Herramienta de CMake que ejecuta los tests registrados con `add_test` y reporta
cuáles pasan. `ctest --preset debug`.

## D

### declaración (declaration)
Decir que algo existe sin darle cuerpo: `int sumar(int, int);`. Basta para que el
compilador compruebe una llamada. Ver *definición*.

### definición (definition)
Dar el cuerpo: `int sumar(int a, int b) { return a + b; }`. Tiene que haber
exactamente una en todo el programa; el enlazador se queja si hay cero o más de una.

### driver
Programa que orquesta el pipeline: `g++` y `clang++` llaman al preprocesador, al
compilador, al ensamblador y al enlazador en orden. Con `-E`, `-S`, `-c` se paran antes.

### `double`
Tipo de coma flotante de 8 bytes, ~16 dígitos significativos. El real por defecto.
No para dinero: `0.1 + 0.2 != 0.3`.

## E

### enlazador (linker)
Última etapa del pipeline (`ld`): junta los `.o` y las bibliotecas, resuelve los
símbolos pendientes y produce el ejecutable. Sus errores: `undefined reference`,
`multiple definition`.

### ensamblador (assembler / assembly)
Dos cosas: el **lenguaje** de texto que describe instrucciones de CPU (`.s`), y el
**programa** (`as`) que lo traduce a código objeto.

### estándar (ISO C++ standard)
Documento que define el lenguaje. Versiones por año: C++11, 14, 17, **20**, 23, 26.
Un compilador lo implementa; `-std=c++20` elige cuál.

### estrechamiento (narrowing conversion)
Conversión que puede perder información: `double` → `int`, `long` → `int`. La
inicialización con llaves `{}` la rechaza en compilación; con `=` pasa en silencio.

## F

### flag (opción de línea de comandos)
Argumento que cambia el comportamiento del compilador: `-std=c++20`, `-Wall`, `-O2`,
`-g`. En CMake se cuelgan de un target con `target_compile_options`.

### `std::format`
Función de `<format>` (C++20) que construye un `std::string` rellenando huecos `{}`
con argumentos. Comprueba la cadena de formato al compilar. `{:.2f}`, `{:>10}`.

## I

### `#include`
Directiva del preprocesador que pega el contenido de otro archivo en este. Trae las
**declaraciones** de la biblioteca (`<iostream>`, `<format>`), no sus definiciones.

### inicialización uniforme (list-initialization)
Inicializar con llaves: `int x{3};`. Rechaza estrechamientos y funciona igual para
todos los tipos. La forma que el bootcamp usa siempre.

### `int`
Tipo entero con signo, 4 bytes en x86-64, rango ±2 147 483 647. El entero por defecto
para contadores y cantidades.

## L

### literal
Un valor escrito directamente en el código: `42` (`int`), `3.14` (`double`), `'a'`
(`char`), `"hola"` (cadena de C), `true` (`bool`). Sufijos: `42L`, `3.14f`, `42U`.

## N

### `std::numeric_limits`
Plantilla de `<limits>` que da los límites de un tipo:
`std::numeric_limits<int>::max()` es 2147483647.

## P

### preprocesador (preprocessor)
Primera etapa del pipeline: ejecuta las líneas con `#` (`#include`, `#define`) y quita
comentarios. Trabaja con texto, no entiende C++. Salida: `.ii`.

### preset
Ver `CMakePresets.json`.

## S

### sanitizer
Instrumentación que el compilador añade al binario para detectar errores en ejecución:
ASan (memoria), UBSan (comportamiento indefinido), TSan (data races). Preset `asan`.

### `sizeof`
Operador que devuelve el tamaño en bytes de un tipo o expresión, resuelto en
compilación. `sizeof(int)` es 4 en x86-64.

### `std::cerr`
Stream de salida de error (descriptor 2). Sin buffer. Para avisos y errores.

### `std::cin`
Stream de entrada estándar (descriptor 0). `std::cin >> x` lee un valor. Sin comprobar
el resultado no es código de verdad (Semana 02).

### `std::cout`
Stream de salida estándar (descriptor 1). Con buffer. Para el resultado del programa.

### `std::endl`
Salto de línea **más un flush** del buffer. Innecesario casi siempre; usa `'\n'`.

### `std::string`
Tipo de la biblioteca estándar para texto: una secuencia de caracteres que crece sola.
`#include <string>`. A fondo en la Semana 02.

### stream (flujo)
Secuencia de bytes con dirección: de salida (`cout`, `cerr`) o de entrada (`cin`).
`<<` escribe en uno; `>>` lee de uno.

## T

### target
Unidad de construcción en CMake: un ejecutable (`add_executable`) o una biblioteca.
Los flags, includes y dependencias se cuelgan de un target, nunca de variables globales.

### tipo (type)
Define cuántos bytes ocupa un valor, cómo se interpretan y qué operaciones admite.
Fijo desde que la variable nace hasta que muere.

## U

### unidad de traducción (translation unit)
Un archivo `.cpp` después del preprocesado: lo que el compilador ve de una vez. Cada
una se compila a su propio `.o` sin saber de las demás.

### `unsigned`
Entero sin signo. Da la vuelta de forma **definida** (módulo 2ⁿ) al bajar de cero.
Para bits y máscaras, no para cantidades.

## W

### warning (aviso)
Diagnóstico del compilador sobre algo que compila pero huele a bug. Con `-Werror`, es
un error. El bootcamp compila siempre con `-Wall -Wextra -Wpedantic -Werror`.

---

> 📚 Glosario global del bootcamp: [docs/glosario-global.md](../../../docs/glosario-global.md)
