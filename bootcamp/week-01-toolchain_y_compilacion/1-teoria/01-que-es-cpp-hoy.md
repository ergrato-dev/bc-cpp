# Qué es C++ hoy

> C++ no es "C con clases" ni el lenguaje de los años noventa que sale en los memes: es
> el lenguaje que hay debajo de tu navegador, tu base de datos y tu videojuego, y en
> 2020 se volvió cómodo de escribir.

## 🎯 Objetivos

Al terminar este archivo podrás:

- Explicar qué significa que C++ sea un **lenguaje compilado** y por qué eso importa
- Situar C++20 en la línea de estándares y saber qué te aporta frente a los anteriores
- Nombrar tres dominios donde C++ es la opción por defecto, y por qué
- Distinguir el **lenguaje** (una especificación) de un **compilador** (un programa)
- Saber qué vas a construir en veinte semanas y en qué orden

## 1. Qué problema resuelve

Un **programa** es una lista de instrucciones para una máquina. La máquina solo
entiende **código máquina**: números que la CPU (el procesador) interpreta como
"suma esto", "guarda aquello", "salta a esa instrucción". Nadie escribe programas así
desde los años cincuenta.

Un **lenguaje de programación** es un idioma intermedio: legible por personas,
traducible a código máquina. Hay dos formas de hacer esa traducción:

| Estrategia | Cómo funciona | Ejemplos | Coste |
| --- | --- | --- | --- |
| **Interpretado** | Un programa (el *intérprete*) lee tu código y lo ejecuta línea a línea, cada vez que lo lanzas | Python, JavaScript | Lento en ejecución; el intérprete tiene que estar instalado donde corre |
| **Compilado** | Un programa (el *compilador*) traduce tu código a código máquina **una vez**; el resultado se ejecuta solo | C, C++, Rust | Un paso más antes de ejecutar; el resultado va a la velocidad de la máquina |

C++ es compilado. Eso resuelve un problema concreto: **rendimiento predecible sin
dependencias en tiempo de ejecución**. El ejecutable que produces corre sin instalar
nada más, y cada línea que escribes se convierte en instrucciones que puedes ver
(lo harás en el archivo 02 y en Compiler Explorer).

El precio: el compilador necesita saber **todo** sobre tu programa antes de ejecutarlo.
Qué tipo tiene cada variable, cuánta memoria ocupa, qué función se llama. Esa
información es lo que vas a aprender a darle.

## 2. Cómo funciona

### 2.1 El lenguaje y el estándar

C++ no pertenece a una empresa. Está definido por un documento, el **estándar ISO**,
que escribe un comité internacional (WG21). Cada pocos años sale una versión nueva,
nombrada por el año:

| Estándar | Año | Qué trajo (lo que te afecta) |
| --- | --- | --- |
| C++98 / C++03 | 1998 / 2003 | El lenguaje "clásico": clases, templates, la STL (la biblioteca estándar de contenedores y algoritmos) |
| C++11 | 2011 | La refundación: `auto`, lambdas, smart pointers, semántica de movimiento, threads. A partir de aquí se habla de **C++ moderno** |
| C++14 | 2014 | Pulido de C++11 |
| C++17 | 2017 | `std::optional`, `std::variant`, `std::string_view`, `std::filesystem`, `if constexpr` |
| **C++20** | 2020 | **Conceptos, ranges, `std::format`, coroutines, módulos, `<=>`**. El estándar de este bootcamp |
| C++23 | 2023 | `std::print`, `std::expected`, `std::generator`. Se marca cuando aparece |
| C++26 | 2026 | Reflexión, contratos. En marcha; no se cubre |

Este bootcamp enseña **C++20** porque es el primer estándar donde el código genérico
(templates) se puede restringir con **conceptos** y donde formatear texto no requiere
pelearse con `printf` ni con `<<` encadenados. Cuando algo sea C++23, lo verás marcado
así:

> [!NOTE]
> **C++23** · `std::print`. En C++20 estricto, la alternativa es
> `std::cout << std::format(...)`; el resultado es idéntico, y es suficiente para los
> entregables de esta semana.

### 2.2 El compilador no es el lenguaje

El estándar dice **qué** debe hacer un programa C++. Un **compilador** es un programa
concreto que lo implementa. Hay tres grandes:

| Compilador | Quién lo hace | Plataforma típica | Ejecutable |
| --- | --- | --- | --- |
| **GCC** (GNU Compiler Collection) | Proyecto GNU | Linux | `g++` |
| **Clang** | Proyecto LLVM (Apple, Google y otros) | macOS, Linux, Android | `clang++` |
| **MSVC** | Microsoft | Windows | `cl.exe` |

Los tres compilan el mismo estándar, pero cada uno va a su ritmo. En septiembre de 2026
GCC 13+ y Clang 17+ cubren C++20 casi entero; los módulos siguen siendo la parte más
verde en todos. Cuando este material diga "verificado con GCC 13.4" es porque el
comportamiento concreto (un mensaje de error, una optimización) depende del compilador,
no del estándar.

> [!TIP]
> Este bootcamp usa **g++ como compilador primario** y **clang++ como segundo**: sus
> mensajes de error son distintos y a veces uno explica mejor que el otro. Tener los
> dos instalados (ver [`docs/setup.md`](../../../docs/setup.md)) es la mejor herramienta
> de depuración gratuita que existe.

### 2.3 Dónde está C++

No hace falta creerse la lista; se puede comprobar en los repositorios públicos:

- **Navegadores**: Chromium y Firefox. El motor que renderiza esta página.
- **Bases de datos**: MySQL, MongoDB, ClickHouse, RocksDB.
- **Motores de juego**: Unreal Engine; el núcleo de Unity.
- **Compiladores e intérpretes**: LLVM, GCC, V8 (el motor de JavaScript de Chrome y
  Node.js), CPython en partes críticas.
- **Machine learning**: TensorFlow, PyTorch (el núcleo; Python es la interfaz).
- **Sistemas embebidos, automoción, aeroespacial, trading de alta frecuencia**: donde
  cada microsegundo y cada byte cuentan.

El patrón: **allí donde el rendimiento es el producto**, C++ es la opción por
defecto. Y el motivo de fondo lo verás en la Semana 03: C++ te deja decidir dónde
vive cada byte.

## 3. Cómo se escribe en C++20

Tu primer programa completo. Léelo; en el ejercicio 01 lo escribirás y compilarás.

```cpp
// hello.cpp — el programa mínimo que hace algo visible
#include <iostream>   // trae std::cout: la salida estándar (la terminal)

int main() {
  std::cout << "Hola, C++20\n";   // << envía texto a la salida; \n es salto de línea
  return 0;                       // 0 significa "terminé bien" para el sistema operativo
}
```

Cinco cosas, y cada una tiene un porqué:

1. **`#include <iostream>`** — el lenguaje base no sabe escribir en la terminal. Esa
   capacidad vive en la **biblioteca estándar**, y `#include` la trae. Lo verás en
   detalle en el archivo 02.
2. **`int main()`** — todo programa C++ empieza en una función llamada `main`. El
   sistema operativo la llama; cuando termina, el programa termina.
3. **`std::`** — el prefijo de todo lo que viene de la biblioteca estándar
   (`std` = *standard*). Es un **espacio de nombres**: una forma de que `cout` de la
   biblioteca no choque con un `cout` tuyo.
4. **`;`** — cada instrucción termina en punto y coma. Olvidarlo es el error de
   compilación más frecuente de la primera semana, y el compilador lo señala bien.
5. **`return 0;`** — el valor que `main` devuelve es el **código de salida** que ve la
   terminal: 0 es éxito, cualquier otro número es error. En `main`, y solo en `main`,
   puedes omitirlo y el compilador pone `return 0;` por ti.

Y así se convierte en algo que corre:

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror hello.cpp -o hello
./hello
```

```
Hola, C++20
```

Cada flag tiene un motivo, y los verás en el archivo 02. Por ahora, el importante:
`-std=c++20` le dice al compilador **qué estándar** estás escribiendo.

## 4. Antipatrones

| Qué hace la gente | Por qué duele | Qué hacer |
| --- | --- | --- |
| Aprender "C primero para entender C++" | C enseña a gestionar memoria a mano, punteros crudos y cadenas terminadas en cero. En C++ moderno todo eso es lo que **no** se hace. Desaprender cuesta más que aprender | Empezar en C++20 directamente. Lo que necesitas saber de C (punteros, arrays) llega en la Semana 03, explicado como lo que es: la capa de abajo |
| Compilar sin `-std=c++20` | El compilador usa su estándar por defecto (GCC 13: C++17). `std::format` no existe, los conceptos no existen, y los errores no dicen "te falta el flag" | Siempre `-std=c++20`, o mejor, dejar que CMake lo ponga (archivo 03) |
| Copiar código de tutoriales de 2010 | `new`/`delete` a mano, `char*` para texto, `NULL`, `typedef`. Compila, y es exactamente lo que te hará perder horas con fallos de memoria | Si un tutorial no usa `auto`, `std::string` ni smart pointers, es anterior a C++11. Cierra la pestaña |
| Confundir "C++ es difícil" con "C++ es grande" | El lenguaje tiene cuarenta años de capas. Nadie usa todas. Intentar aprenderlas todas antes de escribir un programa es la forma segura de no escribir ninguno | Aprender el subconjunto moderno, en orden. Esa es la malla de este bootcamp |
| Usar `using namespace std;` en todo | Trae **todos** los nombres de la biblioteca estándar a tu ámbito. Cuando declares una variable `count` o una función `size`, chocarán con `std::count` y `std::size`, y el error será críptico | Escribir `std::` siempre. Cinco caracteres. En un header, `using namespace` es directamente un bug que afecta a todo el que lo incluya |

## 5. Trucos

- **Compiler Explorer** (https://godbolt.org/) compila lo que escribes en tiempo real
  con docenas de compiladores y versiones, y te enseña el código máquina resultante.
  Es la forma más rápida de comprobar "¿esto compila en GCC 13?" sin instalar nada.
  Pon `-std=c++20 -O2` en la caja de opciones.
- **cppreference** (https://en.cppreference.com/) es la referencia del estándar escrita
  para humanos. Cada página dice desde qué estándar existe cada cosa (`(since C++20)`).
  Si un tutorial y cppreference se contradicen, gana cppreference.
- **Saber qué estándar usa tu compilador por defecto**:

  ```bash
  g++ -dM -E -x c++ /dev/null | grep __cplusplus
  ```

  Imprime `#define __cplusplus 201703L` en GCC 13: C++17 por defecto. Con
  `-std=c++20` delante del `-dM` verás `202002L`. Ese número es la forma oficial de
  identificar un estándar desde el código.

## 📚 Recursos Adicionales

- [cppreference — C++20](https://en.cppreference.com/w/cpp/20) — la lista completa de lo
  que trajo C++20, con enlace a cada feature. Sirve de mapa de las veinte semanas.
- [cppreference — Compiler support](https://en.cppreference.com/w/cpp/compiler_support) —
  qué compilador soporta qué feature desde qué versión. Consulta obligada antes de decir
  "esto no compila".
- [isocpp.org — Get Started](https://isocpp.org/get-started) — la página oficial del
  comité para quien empieza; mantiene una lista curada de libros y recursos.
- [Kate Gregory — *Stop Teaching C* (CppCon 2015)](https://www.youtube.com/@CppCon) —
  busca el título en el canal. Veinte minutos sobre por qué este bootcamp empieza donde
  empieza.

## ✅ Checklist de Verificación

- [ ] Puedo explicar con mis palabras la diferencia entre un lenguaje compilado y uno
      interpretado, y qué gano y qué pierdo con cada uno
- [ ] Sé qué estándar enseña este bootcamp y desde qué año existe
- [ ] Sé distinguir "el estándar C++" de "GCC" y explicar por qué un programa puede
      compilar en uno y no en otro
- [ ] Puedo escribir de memoria el programa mínimo y decir para qué sirve cada una de
      sus cinco partes
- [ ] He comprobado con `g++ -dM -E` qué estándar usa mi compilador por defecto
- [ ] Sé por qué `using namespace std;` no aparecerá en ningún starter del bootcamp
