# Ejercicio 01 — Compila tu primer programa con CMake

> Al terminar tendrás un ejecutable construido con CMake, cuatro tests de `ctest` en
> verde, y habrás visto con tus ojos las cuatro etapas del pipeline de compilación.

**Duración estimada**: 60 min
**Prerrequisitos**: [Teoría 02](../../1-teoria/02-del-codigo-fuente-al-ejecutable.md),
[Teoría 03](../../1-teoria/03-cmake-minimo.md) y
[Teoría 05](../../1-teoria/05-entrada-y-salida-basica.md) leídas; toolchain instalado
según [`docs/setup.md`](../../../../docs/setup.md).

## Contexto

Un pequeño inventario: tres productos, un total, una tabla. Nada de lógica todavía;
el objetivo es que el **ciclo** (editar → construir → probar) te salga sin pensar,
porque lo vas a repetir mil veces en las próximas diecinueve semanas.

El starter trae `src/main.cpp` con todo el código comentado en cuatro pasos, y un
`CMakeLists.txt` con cuatro tests que comprueban la salida del programa. Los tests
están en rojo. Tu trabajo es ponerlos en verde, uno por paso, entendiendo cada línea.

## Paso 0: Configurar y ver fallar los tests

**Por qué**: antes de tocar nada, comprueba que el toolchain funciona y que los tests
fallan **por la razón esperada** (el programa no imprime nada), no por un error de
instalación.

```bash
cd starter
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

**Verifica**: la configuración termina con `Build files have been written to`, la
construcción con `Linking CXX executable app`, y `ctest` muestra:

```
0% tests passed, 4 tests failed out of 4
```

Si `cmake --preset debug` falla con `CMake Error: Could not create named generator Ninja`,
instala Ninja (`sudo apt install ninja-build`) o cambia `"generator"` a
`"Unix Makefiles"` en `CMakePresets.json`.

## Paso 1: Escribir en la salida estándar

**Por qué**: `std::cout` es la salida estándar del programa. Todo lo que el usuario
pidió ver sale por aquí. `\n` es el salto de línea; no uses `std::endl` (Teoría 05,
sección 3.2).

```cpp
std::cout << "Hola, C++20\n";
```

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 1.

**Verifica**:

```bash
cmake --build --preset debug && ctest --preset debug
```

Pasa `paso1_saludo`. Siguen fallando los otros tres: son de los pasos siguientes.

## Paso 2: Variables tipadas y `std::format`

**Por qué**: una cantidad es un `int`; un importe es un `double`. Declararlos con
llaves `{}` impide conversiones silenciosas (Teoría 04). Y para mezclar texto y números
en una línea, `std::format` es legible y se comprueba al compilar.

```cpp
int items{3};
double total{18.75};
std::cout << std::format("{} items en stock, total {:.2f} EUR\n", items, total);
```

`{:.2f}` fuerza dos decimales: `18.75`, no `18.750000` ni `18.8`.

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 2.

**Verifica**: `cmake --build --preset debug && ctest --preset debug` → pasan
`paso1_saludo` y `paso2_inventario`.

## Paso 3: Una tabla alineada

**Por qué**: alinear columnas a mano con espacios se rompe en cuanto un nombre es más
largo. Las especificaciones de ancho de `std::format` (`{:<10}`, `{:>6}`) lo hacen por
ti, y son las mismas para texto y para números.

```cpp
std::string first{"pan"};
std::string second{"leche"};
std::cout << std::format("{:<10}{:>6}{:>10}\n", "nombre", "cant.", "precio");
std::cout << std::format("{:<10}{:>6}{:>10.2f}\n", first, 3, 1.5);
std::cout << std::format("{:<10}{:>6}{:>10.2f}\n", second, 12, 0.89);
```

`{:<10}` = ancho 10, alineado a la izquierda. `{:>10.2f}` = ancho 10, derecha, dos
decimales. La cabecera usa `{:>10}` sin `.2f` porque `"precio"` es texto.

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 3.

**Verifica**: pasa `paso3_tabla`. Ejecuta el programa a mano y mira la tabla:

```bash
./build/debug/app
```

```
nombre     cant.    precio
pan            3      1.50
leche         12      0.89
```

## Paso 4: Avisos a la salida de error

**Por qué**: los errores y avisos van por otro canal (`std::cerr`) para que
`./app > resultado.txt` guarde el resultado limpio y el aviso siga en pantalla.

```cpp
std::cerr << "aviso: precios sin IVA\n";
```

**Abre `starter/src/main.cpp`** y descomenta la sección del Paso 4.

**Verifica**: pasan los 4 tests. Y comprueba la separación de canales:

```bash
./build/debug/app > /dev/null
```

Solo debe aparecer `aviso: precios sin IVA`: la salida estándar se fue a la nada, la
de error no.

## Paso 5: Ver el pipeline por dentro

**Por qué**: CMake esconde la orden de `g++`. Verla una vez te enseña qué flags lleva
de verdad y te prepara para leer errores de compilación y de enlace.

```bash
cmake --build --preset debug -- -v
```

Busca la línea que contiene `-Wall -Wextra -Wpedantic -Werror` y `-std=c++20`: es la
orden real. Ahora para el pipeline en cada etapa, a mano:

```bash
cd src
g++ -std=c++20 -E main.cpp -o main.ii && wc -l main.ii     # preprocesado: ¿cuántas líneas?
g++ -std=c++20 -S main.cpp -o main.s && grep -c '' main.s   # ensamblador
g++ -std=c++20 -c main.cpp -o main.o && file main.o         # objeto: "relocatable"
rm main.ii main.s main.o
cd ..
```

**Verifica**: `main.ii` tiene decenas de miles de líneas (tu programa está al final:
`tail -20 main.ii`); `file main.o` dice `ELF 64-bit LSB relocatable`.

## Paso 6: Provocar un warning y ver `-Werror` en acción

**Por qué**: el bootcamp compila con warnings como errores. Tienes que ver qué aspecto
tiene eso antes de que te pase sin querer.

Añade **al principio de `main`** una variable que no uses:

```cpp
int unused{42};
```

**Verifica**: `cmake --build --preset debug` falla con

```
error: unused variable 'unused' [-Werror=unused-variable]
```

Es un warning (`-Wunused-variable`) convertido en error por `-Werror`. Borra la línea
y vuelve a construir: verde otra vez.

## Paso final: Compilar con sanitizers

**Por qué**: desde hoy, nada se entrega sin pasar por el preset `asan`. Este programa
no tiene errores de memoria, pero el hábito empieza ahora.

```bash
cmake --preset asan && cmake --build --preset asan && ctest --preset asan
```

**Verifica**: `100% tests passed, 0 tests failed out of 4`, sin ningún reporte de
`AddressSanitizer` ni `runtime error`.

## ✅ Resultado

- [ ] `ctest --preset debug` y `ctest --preset asan`: 4 de 4 en verde
- [ ] He visto la orden de `g++` que CMake ejecuta, con `-Werror` y `-std=c++20`
- [ ] He generado y mirado `main.ii`, `main.s` y `main.o`
- [ ] He provocado un `-Werror=unused-variable` y lo he arreglado
- [ ] Sé por qué el aviso va por `cerr` y lo he comprobado con `> /dev/null`

## 🧯 Si algo sale mal

| Síntoma | Causa | Solución |
| --- | --- | --- |
| `CMake Error: Could not create named generator Ninja` | Ninja no está instalado | `sudo apt install ninja-build`, o cambia el generador a `"Unix Makefiles"` en `CMakePresets.json` |
| `error: 'format' is not a member of 'std'` | El compilador es anterior a GCC 13 / Clang 17, o falta `-std=c++20` | `g++ --version`. Si es < 13, sigue [`docs/setup.md`](../../../../docs/setup.md). Si es ≥ 13, comprueba que `CMakeLists.txt` tiene `target_compile_features(app PUBLIC cxx_std_20)` |
| `ctest` dice `No tests were found!!!` | Ejecutaste `ctest` desde `src/` o sin preset | Desde `starter/`, `ctest --preset debug` |
| Un test falla con `Required regular expression not found` pero la salida parece correcta | Un espacio de más o de menos: los anchos de `format` son exactos | Ejecuta `./build/debug/app` y compara carácter a carácter con la tabla de este README |
| Los tests pasan en `debug` pero al ejecutar no ves nada | Estás mirando el binario viejo | `cmake --build --preset debug` reconstruye; luego `./build/debug/app` |
| `error: expected ';' before ...` | Al descomentar quedó una línea a medias, o un `//` de más | Mira la línea **anterior** a la que señala el error |
