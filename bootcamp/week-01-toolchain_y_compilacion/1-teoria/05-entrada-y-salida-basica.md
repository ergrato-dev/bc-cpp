# Entrada y salida básica

> Un programa que no muestra nada no sirve para nada, y `std::format` es la razón por
> la que imprimir en C++20 dejó de ser doloroso.

## 🎯 Objetivos

Al terminar este archivo podrás:

- Escribir en la terminal con `std::cout` y saber qué es un **stream**
- Formatear texto y números con `std::format` y su mini-lenguaje de especificación
- Leer valores del teclado con `std::cin` y saber qué le falta a eso (validación)
- Distinguir `std::cout` de `std::cerr` y usar cada uno para lo suyo
- Elegir entre `'\n'` y `std::endl` con criterio
- Saber qué trae C++23 (`std::print`) y cómo lograr lo mismo en C++20

## 1. Qué problema resuelve

Todo programa habla con el exterior por tres canales que el sistema operativo le da al
arrancar: **entrada estándar** (el teclado, o lo que le redirijas), **salida estándar**
(la terminal) y **salida de error** (también la terminal, pero por otro canal). En C++
se llaman `std::cin`, `std::cout` y `std::cerr`, y viven en `<iostream>`.

El problema histórico de C++ no era escribir texto, era escribir **texto con números
dentro**. Encadenar `<<` para construir `"Item: pan, 3 unidades, 1.50 EUR"` es
ilegible, y la alternativa de C (`printf("%s, %d, %.2f", ...)`) no comprueba tipos:
pasar un `double` donde esperaba `%d` es comportamiento indefinido. C++20 resolvió las
dos cosas con `std::format`: legible como `printf`, seguro como `<<`.

## 2. Cómo funciona

### 2.1 Streams

Un **stream** (flujo) es una secuencia de bytes con dirección: de tu programa hacia
fuera (`cout`, `cerr`) o de fuera hacia tu programa (`cin`). El operador `<<` "empuja"
algo hacia un stream de salida; `>>` "extrae" algo de un stream de entrada. Ambos
devuelven el propio stream, por eso se encadenan:

```cpp
std::cout << "Total: " << 42 << '\n';
//        ^ devuelve cout    ^ devuelve cout   ^ devuelve cout
```

`cout` está **bufferizado**: lo que escribes se acumula en memoria y se envía a la
terminal de golpe cuando el buffer se llena, cuando el programa termina, o cuando
lo fuerzas (*flush*). `cerr` no: cada escritura sale inmediatamente. Por eso los
mensajes de error van a `cerr`: si el programa se cae justo después, el mensaje ya
está fuera.

### 2.2 `std::format`

`std::format` (en `<format>`) recibe una **cadena de formato** con huecos `{}` y los
rellena con los argumentos que siguen, en orden. Devuelve un `std::string`; no imprime.

```cpp
#include <format>
#include <iostream>
#include <string>

int main() {
  std::string name{"pan"};
  int quantity{3};
  double price{1.5};

  std::string line{std::format("Item: {}, {} unidades, {:.2f} EUR", name, quantity, price)};
  std::cout << line << '\n';
  // Item: pan, 3 unidades, 1.50 EUR
}
```

Cada `{}` puede llevar una **especificación** tras dos puntos. Las que vas a usar:

| Especificación | Ejemplo | Resultado | Qué hace |
| --- | --- | --- | --- |
| `{}` | `format("{}", 3.5)` | `3.5` | Por defecto: representación más corta y exacta |
| `{:.2f}` | `format("{:.2f}", 1.5)` | `1.50` | Coma flotante fija, 2 decimales |
| `{:>8}` | `format("{:>8}", 42)` | `      42` | Ancho 8, alineado a la derecha |
| `{:<8}` | `format("[{:<8}]", "ab")` | `[ab      ]` | Ancho 8, alineado a la izquierda |
| `{:^8}` | `format("[{:^8}]", "ab")` | `[   ab   ]` | Centrado |
| `{:08.3f}` | `format("{:08.3f}", 3.14159)` | `0003.142` | Ancho 8, relleno con ceros, 3 decimales |
| `{:>10.2f}` | `format("{:>10.2f}", 1234.5)` | `   1234.50` | Ancho y decimales combinados: tablas alineadas |
| `{:x}`, `{:b}` | `format("{:x} {:b}", 255, 5)` | `ff 101` | Hexadecimal, binario |
| `{0} {1} {0}` | `format("{0} {1} {0}", "a", "b")` | `a b a` | Índices explícitos: repetir o reordenar |
| `{{` `}}` | `format("{{x}}")` | `{x}` | Llaves literales |

Lo importante: **la cadena de formato se comprueba al compilar**. Si pones tres `{}` y
pasas dos argumentos, o pides `{:d}` para un `std::string`, el error es de compilación,
no un fallo en ejecución. Eso es lo que `printf` nunca pudo dar.

## 3. Cómo se escribe en C++20

### 3.1 Salida

```cpp
#include <format>
#include <iostream>

int main() {
  // Texto fijo: << directo, sin format.
  std::cout << "Inventario\n";

  // Texto con valores: format construye la línea, << la envía.
  int items{3};
  double total{12.75};
  std::cout << std::format("{} items, total {:.2f} EUR\n", items, total);

  // Una tabla alineada: ancho fijo por columna.
  std::cout << std::format("{:<10}{:>6}{:>10}\n", "nombre", "cant.", "precio");
  std::cout << std::format("{:<10}{:>6}{:>10.2f}\n", "pan", 3, 1.5);
  std::cout << std::format("{:<10}{:>6}{:>10.2f}\n", "leche", 12, 0.89);

  // Errores: a cerr, nunca a cout.
  std::cerr << "aviso: precio sin IVA\n";
  return 0;
}
```

```
Inventario
3 items, total 12.75 EUR
nombre     cant.    precio
pan            3      1.50
leche         12      0.89
aviso: precio sin IVA
```

> [!NOTE]
> **C++23** · `std::print("{} items\n", items)` hace `cout << format(...)` en una sola
> llamada, y `std::println` añade el salto de línea. Necesita GCC 14 o Clang 18 con
> `-std=c++23`. En C++20 estricto, la alternativa es `std::cout << std::format(...)`;
> el resultado es idéntico, y es suficiente para los entregables de esta semana.

### 3.2 `'\n'` frente a `std::endl`

```cpp
std::cout << "a" << '\n';         // ✅ salto de línea
std::cout << "a" << std::endl;    // ⚠️ salto de línea + flush (vaciar el buffer)
```

`std::endl` fuerza un *flush* cada vez. En un bucle que escribe mil líneas, son mil
llamadas al sistema operativo en vez de unas pocas: hasta cien veces más lento. Usa
`'\n'`. El buffer se vacía solo al terminar el programa, y si necesitas forzarlo
(antes de una operación que puede colgarse), `std::cout << std::flush;` lo dice
explícitamente.

### 3.3 Entrada

```cpp
#include <iostream>
#include <string>

int main() {
  std::cout << "¿Cuántos items? ";
  int count{};
  std::cin >> count;                 // lee un entero; se salta espacios y saltos de línea

  std::cout << "¿Nombre del primero? ";
  std::string name;
  std::cin >> name;                  // lee UNA palabra (para hasta el primer espacio)

  std::cout << "Leído: " << count << " x " << name << '\n';
  return 0;
}
```

Dos cosas que este código **no** hace y que verás en la Semana 02:

1. **Comprobar que la lectura funcionó.** Si el usuario escribe `abc` cuando esperabas
   un entero, `std::cin >> count` falla, `count` se pone a 0, y `cin` queda en estado
   de error: todas las lecturas siguientes fallan también, en silencio. La solución
   (`if (!(std::cin >> count))`) necesita `if`, que es del próximo tema.
2. **Leer una línea entera** con espacios: `std::getline(std::cin, name)`. Lo verás
   junto con `std::string` a fondo.

> [!WARNING]
> Un programa que lee de `std::cin` sin comprobar el resultado **no es un entregable**
> en este bootcamp. Esta semana los starters no leen entrada por eso: hasta que sepas
> validarla, todo viene de constantes en el código.

### 3.4 Qué stream para qué

| Stream | Canal | Bufferizado | Para qué |
| --- | --- | --- | --- |
| `std::cout` | salida estándar (1) | Sí | El resultado del programa: lo que el usuario pidió |
| `std::cerr` | salida de error (2) | No | Errores y avisos: lo que el usuario no pidió pero debe ver |
| `std::clog` | salida de error (2) | Sí | Logs de diagnóstico (rara vez) |
| `std::cin` | entrada estándar (0) | Sí | Lo que el usuario escribe |

Los números entre paréntesis son los **descriptores de fichero** del sistema
operativo. Importan porque la terminal te deja redirigirlos por separado:

```bash
./app > resultado.txt        # cout va al archivo; cerr sigue en pantalla
./app 2> errores.txt         # cerr al archivo; cout en pantalla
./app > out.txt 2>&1         # los dos al archivo
```

Si mezclas errores en `cout`, `./app > resultado.txt` guarda los errores dentro del
resultado. Esa es la razón práctica de separar.

## 4. Antipatrones

| Qué hace la gente | Por qué duele | Qué hacer |
| --- | --- | --- |
| `printf("%d", x)` en C++ | No comprueba tipos: `printf("%d", 3.5)` es UB y compila. Y no sabe imprimir `std::string` | `std::format`. Misma sintaxis de anchos y decimales, comprobada al compilar |
| `std::endl` en cada línea | Un *flush* por línea. En salidas grandes, el programa pasa más tiempo en llamadas al sistema que calculando | `'\n'`. `std::flush` explícito solo cuando lo necesites |
| Errores por `cout` | `./app > salida.txt` mete los errores en el archivo de resultados; el usuario no los ve | `std::cerr` para todo lo que sea error o aviso |
| Encadenar diez `<<` para una línea | `cout << "a: " << a << ", b: " << b << ", c: " << std::fixed << std::setprecision(2) << c << '\n';` es ilegible y el `setprecision` se queda pegado para las siguientes escrituras | `std::format` para cualquier línea con más de un valor |
| `using namespace std;` para "ahorrar" `std::` | Trae mil nombres a tu ámbito; `count`, `size`, `min` chocarán con los tuyos con errores crípticos | `std::` siempre. Son cinco caracteres |
| Leer de `cin` sin comprobar | Un `abc` donde iba un número deja `cin` en error y el programa sigue con ceros como si nada | Semana 02: `if (!(std::cin >> x))`. Hasta entonces, sin entrada del usuario |

## 5. Trucos

- **Probar especificaciones de formato sin compilar** — en https://godbolt.org/ con
  `-std=c++20`, un `main` con `std::cout << std::format(...)` y la pestaña de salida
  (*Execute*). Iterar sobre un `{:>10.2f}` ahí es más rápido que en tu proyecto.
- **`{}` imprime cualquier tipo del estándar** que tenga formateador: enteros, reales,
  `bool` (`true`/`false`), `char`, `std::string`, `std::string_view`. Cuando escribas
  tus propios tipos (Semana 04) verás cómo enseñarle a `format` a imprimirlos.
- **Anchos variables** — `std::format("{:>{}}", value, width)`: el segundo `{}` se
  rellena con el ancho. Útil para tablas cuyas columnas se calculan.
- **Ver el buffer en acción** — `std::cout << "a"; while(true){}` no imprime nada
  (el buffer nunca se vacía); con `std::cerr << "a";` sí. Es la demostración de por
  qué los errores van a `cerr`. (Ctrl+C para salir.)

## 📚 Recursos Adicionales

- [cppreference — `std::format`](https://en.cppreference.com/w/cpp/utility/format/format) —
  la referencia con todos los argumentos y ejemplos ejecutables.
- [cppreference — Standard format specification](https://en.cppreference.com/w/cpp/utility/format/spec) —
  la tabla completa del mini-lenguaje `{:...}`. Tenla a mano hasta que la memorices.
- [cppreference — `std::cout`](https://en.cppreference.com/w/cpp/io/cout) — y las notas
  sobre sincronización con `stdio` y buffering, cortas.
- [C++ Core Guidelines — SL.io.50: Avoid `endl`](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#slio50-avoid-endl) —
  la regla con la explicación en tres líneas.

## ✅ Checklist de Verificación

- [ ] Puedo explicar qué es un stream y por qué `<<` se puede encadenar
- [ ] Sé formatear un `double` con dos decimales y alinearlo a la derecha en 10 columnas
- [ ] Sé qué comprueba `std::format` al compilar que `printf` no comprueba
- [ ] Sé por qué los errores van a `cerr` y puedo demostrarlo con una redirección
- [ ] Sé por qué `'\n'` y no `std::endl`, y cuándo sí querría un flush
- [ ] Sé qué le falta al `std::cin >> x` de esta semana para ser código de verdad
- [ ] Sé qué es `std::print` y cómo escribo lo mismo en C++20
