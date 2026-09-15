# Ejercicio 02 — Utilidades de cadenas

> Al terminar tendrás cinco funciones de texto que usarás durante todo el bootcamp
> (`trim`, `to_upper`, `split`, `join`, `replace_all`), cada una con la firma que le
> corresponde: vista, copia, vector, `const&` o referencia modificable. Y habrás
> visto a ASan cazar un desbordamiento que en `debug` pasa en silencio.

**Duración estimada**: 75 min
**Prerrequisitos**: [Teoría 02](../../1-teoria/02-funciones.md),
[04](../../1-teoria/04-string-y-string-view.md) y
[05](../../1-teoria/05-vector-y-agregados.md) leídas;
[Ejercicio 01](../ejercicio-01-interprete-de-comandos/README.md) completado.

## Contexto

Cada función de este ejercicio existe para practicar **una decisión de firma** de la
Teoría 02 y 04: ¿recibo una vista o una copia? ¿devuelvo texto nuevo o modifico el
que me dan? Las cinco juntas cubren todos los casos. El programa imprime cada
resultado entre corchetes: un espacio de más o de menos se ve.

## Paso 0: Configurar y ver fallar los tests

```bash
cd starter
cmake --preset debug && cmake --build --preset debug && ctest --preset debug
```

**Verifica**: `0% tests passed, 5 tests failed out of 5`.

## Paso 1: `trim` — vista dentro, vista fuera

**Por qué**: recortar espacios no necesita crear texto nuevo: el resultado es un
**tramo** del texto original. Recibir y devolver `std::string_view` lo dice en la
firma y no copia nada. El llamador sigue siendo el dueño; la vista vale mientras él
viva.

```cpp
[[nodiscard]] std::string_view trim(std::string_view text) {
  const std::size_t start{text.find_first_not_of(" \t")};
  if (start == std::string_view::npos) {
    return "";                                   // todo eran espacios (o nada)
  }
  const std::size_t end{text.find_last_not_of(" \t")};
  return text.substr(start, end - start + 1);
}
```

`find_first_not_of` devuelve la posición del primer carácter que **no** está en
`" \t"`; `npos` significa que todos lo estaban. Ese caso se trata **antes** de
calcular `end`: con `npos` la resta daría un número gigante.

**Abre `starter/src/main.cpp`** y descomenta las dos secciones del Paso 1 (la función
arriba, las tres líneas de `main` abajo).

**Verifica**: pasa `paso1_trim`: `[hola mundo]`, `[]`, `[]`.

## Paso 2: `to_upper` — la única vez que un `std::string` va por valor

**Por qué**: pasar a mayúsculas necesita **una copia** que modificar (el original no
debe cambiar). Si la firma pide `std::string` por valor, la copia la hace la llamada,
y si el llamador pasa un temporal no hay copia ninguna. Recibir `const std::string&`
y copiar dentro haría lo mismo con una línea más.

```cpp
[[nodiscard]] std::string to_upper(std::string text) {
  for (char& c : text) {                         // char&: modifica el de dentro
    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }
  return text;
}
```

Dos `static_cast` para una letra: `std::toupper` viene de C, recibe y devuelve
`int`, y con un `char` negativo (acentos en algunas codificaciones) es UB. Pasar por
`unsigned char` lo evita; el segundo cast devuelve el resultado a `char`. Es feo y es
correcto; la alternativa bonita no existe hasta que veas `<locale>` o Unicode de
verdad.

**Abre `starter/src/main.cpp`** y descomenta las dos secciones del Paso 2.

**Verifica**: pasa `paso2_to_upper`. La segunda línea, `original: [hola mundo 42]`,
demuestra que el `std::string` del llamador no cambió.

## Paso 3: `split` — de una vista a un vector

**Por qué**: partir `"a,b,,c"` produce **cuatro** cadenas nuevas, y "cuántas" no se
sabe hasta recorrer. Eso pide un `std::vector<std::string>` devuelto por valor. Cada
campo se copia a un `std::string` propio porque el vector tiene que sobrevivir al
texto original.

```cpp
[[nodiscard]] std::vector<std::string> split(std::string_view text, char separator) {
  std::vector<std::string> parts{};
  std::size_t start{0};
  std::size_t pos{text.find(separator)};
  while (pos != std::string_view::npos) {
    parts.push_back(std::string{text.substr(start, pos - start)});
    start = pos + 1;
    pos = text.find(separator, start);
  }
  parts.push_back(std::string{text.substr(start)});  // el último campo
  return parts;
}
```

El bucle añade un campo por cada separador encontrado; el `push_back` de después
añade lo que queda tras el último. Por eso `"a,b,,c"` da cuatro partes y no tres: el
campo vacío entre las dos comas cuenta. Es lo que hace un lector de CSV, y lo
reutilizarás en la Semana 10.

**Abre `starter/src/main.cpp`** y descomenta las dos secciones del Paso 3.

**Verifica**: pasa `paso3_split`: `4 partes: [a] [b] [] [c]`.

## Paso 4: `join` — el vector por `const&`

**Por qué**: `join` solo **lee** el vector. Pasarlo por valor copiaría todas las
cadenas; por `const&` no copia nada y la firma promete no tocarlo.

```cpp
[[nodiscard]] std::string join(const std::vector<std::string>& parts, std::string_view separator) {
  std::string result{};
  for (std::size_t i{0}; i < parts.size(); ++i) {
    if (i > 0) {
      result += separator;
    }
    result += parts[i];
  }
  return result;
}
```

Aquí el índice sí se usa (para saber si es el primero), así que el `for` clásico es
el correcto. `join({}, "-")` en `main` pasa un vector vacío: el bucle no da ninguna
vuelta y `result` sale vacío, sin caso especial.

**Abre `starter/src/main.cpp`** y descomenta las dos secciones del Paso 4.

**Verifica**: pasa `paso4_join`: `[x-y-z]` y `[]`.

## Paso 5: `replace_all` — modificar a través de una referencia

**Por qué**: sustituir en sitio es la operación natural sobre un texto que ya tienes.
`std::string& text` sin `const` es la única firma que lo dice: "voy a cambiar lo que
me pasas". Devuelve `void` porque el resultado **es** el argumento.

```cpp
void replace_all(std::string& text, std::string_view from, std::string_view to) {
  if (from.empty()) {
    return;                                      // buscar "" no termina nunca
  }
  std::size_t pos{text.find(from)};
  while (pos != std::string::npos) {
    text.replace(pos, from.size(), to);
    pos = text.find(from, pos + to.size());      // seguir DESPUÉS de lo insertado
  }
}
```

La línea del `find` es la que importa: la siguiente búsqueda empieza **después** del
texto recién insertado. Si empezara en `pos`, con `from = "a"` y `to = "aa"` volvería a
encontrar la `a` que acaba de poner, la doblaría otra vez, y así hasta agotar la
memoria. El caso `banana → baanaanaa` del `main` lo comprueba.

**Abre `starter/src/main.cpp`** y descomenta las dos secciones del Paso 5.

**Verifica**: pasan los 5 tests.

## Paso 6: Un desbordamiento que `debug` no ve y ASan sí

**Por qué**: la Teoría 06 dice que un índice fuera de rango puede "funcionar". Hay que
verlo funcionar una vez, y luego ver a ASan decir lo contrario, para no volver a
creerse una ejecución en verde sin sanitizer.

> [!WARNING]
> Este código tiene UB a propósito. Se ejecuta con `debug` para ver que calla y con
> `asan` para ver que grita. Después se borra.

Añade al final de `main`, antes del `return`:

```cpp
std::vector<std::size_t> lengths(fields.size());     // 4 ceros, capacidad exacta
for (std::size_t i{0}; i <= lengths.size(); ++i) {   // ❌ UB: <= visita lengths[4]
  lengths[i] = i * 10;
}
std::cout << "lengths: " << lengths.size() << '\n';
```

Es el error clásico de `<=` por `<` (Teoría 01). Primero con `debug`:

```bash
cmake --build --preset debug && ./build/debug/app | tail -n 1
```

**Verifica**: imprime `lengths: 4` y termina bien. Escribió 8 bytes fuera del vector
y **nadie se enteró**. Ahora con `asan`:

```bash
cmake --preset asan && cmake --build --preset asan && ./build/asan/app
```

**Verifica**: la salida contiene

```
ERROR: AddressSanitizer: heap-buffer-overflow on address ...
WRITE of size 8 at ...
    #0 ... in main .../src/main.cpp:NN
```

`heap-buffer-overflow` es el **qué**; la línea `#0` con `main.cpp:NN` es el
**dónde**. Cambia `<=` por `<`, vuelve a ejecutar con `asan` y comprueba que calla.
Después borra las cinco líneas: `ctest --preset asan` tiene que volver a dar 5 de 5.

Sin sanitizer también se puede cazar: `-D_GLIBCXX_ASSERTIONS` en las opciones de
compilación convierte ese `lengths[4]` en `Assertion '__n < this->size()' failed`. El
starter del proyecto de esta semana lo lleva activado en `debug`.

## Paso final: Sanitizers en verde

```bash
cmake --build --preset asan && ctest --preset asan
```

**Verifica**: `100% tests passed, 0 tests failed out of 5`, sin ningún reporte.

## ✅ Resultado

- [ ] 5 de 5 tests en verde en `debug` y `asan`
- [ ] Puedo justificar la firma de cada función: por qué vista, copia, `const&` o `&`
- [ ] Sé por qué `trim` comprueba `npos` antes de restar
- [ ] Sé por qué `split("a,b,,c")` da cuatro partes y no tres
- [ ] Sé por qué `replace_all` busca a partir de `pos + to.size()`
- [ ] He visto el mismo desbordamiento pasar en `debug` y fallar en `asan`, y he borrado el código

## 🧯 Si algo sale mal

| Síntoma | Causa | Solución |
| --- | --- | --- |
| `paso1_trim` falla con `trim: [hola mundo ]` (espacio antes del corchete) | Recortaste solo por delante, o el `+ 1` de `end - start + 1` falta | `find_last_not_of` da la posición del último carácter útil; la longitud es `end - start + 1` |
| `trim("   ")` se cuelga o imprime basura | Falta el `if (start == npos)`: `end - start + 1` con `npos` es un número enorme | Tratar `npos` antes de calcular nada |
| `to_upper("ñandú")` deja la `ñ` igual o imprime basura | `std::toupper` solo conoce ASCII en el *locale* por defecto; los acentos en UTF-8 son dos bytes | Es lo esperado esta semana. Unicode de verdad necesita una biblioteca (ICU) que no está en el estándar |
| `paso3_split` da `3 partes` | Falta el `push_back` de después del bucle | El último campo no tiene separador detrás: se añade fuera del bucle |
| `paso5_replace_all` se queda colgado | La siguiente búsqueda empieza en `pos` en vez de en `pos + to.size()` | Es el bucle infinito del `banana`. Mata el programa con `Ctrl-C` y corrige el `find` |
| En el Paso 6 `debug` también falla | Tienes `-D_GLIBCXX_ASSERTIONS` o `-fsanitize` en el entorno (`CXXFLAGS`) | Es una buena noticia. `echo $CXXFLAGS` para saber de dónde viene |
| En el Paso 6 `asan` no reporta nada | Construiste `debug`, no `asan`, o el `<=` ya está corregido | `./build/asan/app`, no `./build/debug/app` |
