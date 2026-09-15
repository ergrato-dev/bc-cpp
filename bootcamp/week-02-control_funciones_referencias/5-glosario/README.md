# Glosario — Semana 02: Control de flujo, funciones y referencias

Términos clave ordenados alfabéticamente, con el término inglés del estándar o del
toolchain entre paréntesis.

## A

### agregado (aggregate)
Tipo que solo agrupa datos: un `struct` con campos públicos, sin constructor propio.
Se inicializa con llaves, campo a campo, o con inicializadores designados.
`Item bolt{.name = "tornillo", .quantity = 12};`.

### alcance (scope)
Región del código fuente donde un nombre es visible. Se decide al compilar. Una
variable declarada en un bloque `{}` tiene alcance hasta la llave de cierre.

### argumento (argument)
El valor que se pasa en una llamada: en `add(3, 4)`, `3` y `4`. Se distingue del
**parámetro**, que es la variable que lo recibe.

### atributo (attribute)
Anotación entre dobles corchetes que informa al compilador de una intención:
`[[nodiscard]]`, `[[fallthrough]]`, `[[maybe_unused]]`.

## B

### bloque (block)
Una o más sentencias entre `{` y `}` tratadas como una sola. Cada bloque abre un
alcance nuevo.

### bucle `for` de rango (range-based `for` loop)
`for (const Item& item : items)`: recorre cada elemento de una colección sin índice.
Es la forma por defecto de recorrer en el bootcamp.

## C

### caída (fallthrough)
En un `switch`, seguir ejecutando el `case` siguiente cuando el actual no termina en
`break`. Accidental es un bug (`-Wimplicit-fallthrough`); deliberada se marca con
`[[fallthrough]]`.

### comportamiento definido por la implementación (implementation-defined behavior)
El compilador elige entre varias opciones válidas y **lo documenta**. `sizeof(int)`
es 4 en GCC x86-64, y está escrito.

### comportamiento indefinido (undefined behavior, UB)
El estándar no impone **ningún** requisito a lo que ocurre: el programa no es un
programa C++ válido aunque compile. El compilador asume que nunca ocurre y optimiza
en consecuencia. Se detecta con ASan, UBSan y `-D_GLIBCXX_ASSERTIONS`.

### comportamiento no especificado (unspecified behavior)
Una de varias opciones válidas, sin obligación de documentar cuál ni de ser
consistente. El orden de evaluación de `f() + g()`.

### condición (condition)
Expresión de tipo `bool` que decide un `if` o un bucle. El bootcamp escribe
`count != 0`, no `count`.

## D

### declaración (declaration)
Introduce un nombre y su tipo sin definirlo: `int add(int a, int b);`. Una función
puede declararse muchas veces. También llamada **prototipo** (*prototype*).

### definición (definition)
La declaración más el cuerpo (o el almacenamiento). Cada función se define **una sola
vez** en todo el programa (regla que verás con nombre, ODR, en la Semana 11).

### duración (storage duration)
Tramo de la ejecución durante el que un objeto existe en memoria. **Automática**
(*automatic*): las variables locales, del `{` al `}`. **Estática** (*static*):
globales y `static` locales, todo el programa.

## E

### enumeración con ámbito (scoped enumeration, `enum class`)
Tipo cuyos únicos valores son los que se nombran: `enum class Command { add, quit };`.
Se accede con `Command::add`. No se convierte a `int` sin un `static_cast`.

### espacio de nombres (namespace)
Caja de nombres que evita choques: `std::cout` es "el `cout` de `std`". El código
del proyecto vive en un `namespace` con el nombre del dominio.

## F

### `[[fallthrough]]`
Atributo que marca una caída deliberada entre `case`; silencia
`-Wimplicit-fallthrough` solo ahí.

### flujo de cadena (string stream, `std::istringstream`)
Flujo de entrada que lee de un `std::string` en vez del teclado. Sirve para partir
una línea en palabras y números con `>>`, y para validar cada campo.

## I

### inicializador designado (designated initializer)
Sintaxis de C++20 para inicializar un agregado nombrando cada campo:
`Item{.name = "tornillo", .quantity = 12}`. El orden tiene que ser el de la
declaración.

### invalidación de referencias (reference invalidation)
Cuando un `std::vector` crece y se reubica, toda referencia (e iterador) a sus
elementos deja de ser válida. Usarla es UB (`heap-use-after-free` en ASan).

## M

### marco de pila (stack frame)
Bloque de la pila de llamadas que guarda los parámetros y las variables locales de
una llamada, y la dirección a la que volver. Nace en la llamada y muere en el `return`.

## N

### `[[nodiscard]]`
Atributo que hace que ignorar el valor devuelto por una función produzca un warning
(`-Wunused-result`), y con `-Werror`, un error.

### `npos`
Valor que `find` y compañía devuelven cuando no encuentran nada:
`std::string::npos`, `std::string_view::npos`. Es el mayor `std::size_t` posible.
Siempre se compara antes de usar la posición.

## O

### operador de resolución de ámbito (scope resolution operator, `::`)
"Busca dentro de": `std::cout`, `Command::add`, `inventory::add_item`.

## P

### parámetro (parameter)
Variable declarada en la firma de una función que recibe el argumento de la llamada:
en `int add(int a, int b)`, `a` y `b`.

### parámetro de salida (output parameter)
Parámetro por referencia no constante que la función rellena para el llamador:
`bool read_operands(std::istringstream& in, int& a, int& b)`.

### paso por referencia (pass by reference)
El parámetro es un alias de la variable del llamador: `void reset(int& counter)`. Sin
copia; la función puede modificar el original. Con `const`, sin copia y sin poder
modificar.

### paso por valor (pass by value)
El parámetro es una **copia** del argumento: `void reset(int counter)`. Modificarlo
no toca el original. Correcto para tipos pequeños.

### pila de llamadas (call stack)
Zona de memoria que crece con cada llamada a función (un marco) y se encoge con cada
`return`. Tamaño fijo (8 MB por defecto en Linux). La Semana 03 la compara con el
*heap*.

## R

### referencia (reference)
Segundo nombre para una variable que ya existe: `int& r{x};`. Se inicializa una vez,
no puede estar vacía ni cambiar de variable. Con `const` promete no modificar.

### referencia colgante (dangling reference)
Referencia (o `std::string_view`) a un objeto que ya no existe: una local devuelta,
un temporal que murió, un elemento de un `vector` reubicado. Usarla es UB. GCC avisa
en algunos casos (`-Wreturn-local-addr`, `-Wdangling-reference`); ASan la caza en
ejecución.

## S

### sobrecarga (overloading)
Varias funciones con el mismo nombre y parámetros distintos: `describe(int)` y
`describe(double)`. El compilador elige por los tipos de los argumentos.

### sombreado (shadowing)
Declarar en un bloque interior una variable con el nombre de otra exterior, que queda
tapada mientras dure la interior. Legal y confuso; `-Wshadow` lo avisa (no está en
`-Wall`).

### `static` (variable local estática, static local variable)
Variable local que se inicializa una sola vez y vive todo el programa. Estado
compartido entre llamadas; el bootcamp lo evita.

### `std::size_t`
Tipo entero sin signo que devuelven `size()` y `sizeof`. Se usa para índices y
tamaños; mezclarlo con `int` en una comparación dispara `-Wsign-compare`.

### `std::string`
Cadena de texto que **posee** su memoria: guarda los caracteres y su longitud, crece
sola y se libera sola. Copiarla copia el texto.

### `std::string_view`
Vista de solo lectura sobre texto ajeno: un puntero y una longitud. No posee nada;
vale mientras viva el dueño. Firma por defecto para parámetros de texto de entrada.

### `std::vector`
Colección de elementos del mismo tipo, contiguos en memoria, que crece sola con
`push_back`. `v[i]` no comprueba el índice; `v.at(i)` sí.

## T

### tubería (pipe)
En la terminal, `|` conecta la salida de un programa con la entrada de otro:
`printf 'add 3 4\n' | ./app`. Es como los tests de esta semana alimentan al programa.

## V

### validación de entrada (input validation)
Comprobar que lo que llega de fuera (usuario, fichero, red) es exactamente lo que se
espera antes de usarlo: `if (!(in >> n))`, `in >> std::ws; in.eof()`, `index <
v.size()`. Regla del bootcamp desde esta semana.

### vista (view)
Objeto que mira datos que pertenecen a otro sin copiarlos ni poseerlos.
`std::string_view` es la de esta semana; `std::span` (Semana 03) es la de los
contiguos.
