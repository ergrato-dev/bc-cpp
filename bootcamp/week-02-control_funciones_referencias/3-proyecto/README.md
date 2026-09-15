# Proyecto — Semana 02: menú CRUD en memoria

> Al terminar esta semana tu sistema deja de ser tres registros escritos en el
> código: los registros entran por comandos, viven en un `std::vector`, y cada línea
> que teclea el usuario se valida antes de tocar nada. Es la primera capa que hace
> algo que un usuario reconocería como "un programa".

## 📦 Qué añade esta semana

**La capa 1: el CRUD en memoria.** Un `struct` con los campos de tu recurso, un
`std::vector` que los guarda, cinco funciones libres (alta, baja, búsqueda, listado, valor total)
que solo tocan el vector a través de sus parámetros, y un bucle de comandos que las
llama tras validar cada línea.

Va aquí porque **todo lo que viene después necesita una colección y funciones que la
manipulen**: la Semana 03 le añade un historial con memoria dinámica, la 04 convierte
el `struct` en una `class` con invariantes, la 07 lo hace genérico. Si la separación
"función que calcula / bucle que habla con el usuario" no está clara hoy, la Semana
04 se convierte en una `class` de 400 líneas.

Lo que **no** hay todavía, a propósito: ni ficheros (los datos mueren con el
programa hasta que se carguen desde CSV en la Semana 10), ni `class` con constructor (Semana 04), ni excepciones
(cada fallo es un `bool` y un mensaje, Semana 10). CRUD viene de *Create, Read,
Update, Delete*: las cuatro operaciones básicas sobre una colección. Esta semana
haces tres de ellas; *Update* queda como criterio de calidad opcional.

## 📋 Requisitos verificables

1. **Rama** `week-02` desde `main` en tu repositorio `bc-cpp-<tu-dominio>`. El
   `CMakeLists.txt` lleva `-Wshadow` y `_GLIBCXX_ASSERTIONS` en Debug, como el
   starter.
2. **`struct <Recurso>`** dentro de un `namespace` con el nombre de tu dominio, con
   los campos de la Semana 01 (texto, entero, real) y **valor por defecto en cada
   campo numérico**.
3. **`find_index`**: `const std::vector<Recurso>&` y `std::string_view` de entrada;
   devuelve la posición o `size()`. `[[nodiscard]]`.
4. **`add_item`** (o `add_book`, `add_room`…): rechaza nombre duplicado y valores
   negativos. Devuelve `bool`. `[[nodiscard]]`.
5. **`remove_item`**: elimina por nombre. Devuelve `bool`. `[[nodiscard]]`.
6. **`list_items`**: tabla con `std::format`, anchos fijos, dos decimales;
   `(vacío)` si no hay registros.
7. **`total_value`**: suma de `cantidad × precio`. Devuelve `double`.
8. **Bucle de comandos** con `enum class Command`, `switch` sin `default`, y
   `read_item` que valida los tres campos de `add` **y rechaza datos sobrantes**.
9. **Mensajes exactos** del starter (`ok: <name> añadido`, `error: no existe: <name>`,
   `error: uso: add <name> <quantity> <price>`…), con el sustantivo de tu dominio si
   quieres, pero **los mismos en todos los tests**.
10. **Tests**: los dos del starter más **al menos 8** de la lista del `CMakeLists.txt`,
    todos con entrada por tubería y valores calculados a mano.
11. **`ctest --preset debug` y `ctest --preset asan` en verde**, cero warnings.

## 🧪 Tests mínimos

| Test | Entrada | Qué comprueba (`PASS_REGULAR_EXPRESSION`) |
| --- | --- | --- |
| `help` | `help` | La lista de comandos (viene en el starter) |
| `list_vacio` | `list` | `(vacío)` (viene en el starter) |
| `add_ok` | `add tornillo 12 0.15` | `ok: tornillo añadido` |
| `add_duplicado` | dos `add` con el mismo nombre | el segundo da `error: no se pudo añadir` |
| `add_negativo` | `add tornillo -1 0.15` | `error: no se pudo añadir` |
| `add_uso` | `add tornillo doce 0.15` y `add a 1 1 extra` | `error: uso: add ...` **dos veces** |
| `remove_ok` | `add`, `remove`, `list` | `ok: ... eliminado` y después `(vacío)` |
| `remove_inexistente` | `remove tuerca` | `error: no existe: tuerca` |
| `find_ok` | `add`, `find` | `tornillo 12 0.15` |
| `find_inexistente` | `find tuerca` | `error: no existe: tuerca` |
| `total` | dos `add` y `total` | `Valor total: 2.60 EUR` (con **tus** números) |
| `list_con_registros` | dos `add` y `list` | las dos filas con los anchos de `format` |

En una expresión regular de CTest, `.` significa "cualquier carácter" y `(` abre un
grupo: escríbelos como `\\.` y `\\(` dentro del `CMakeLists.txt`. `add_uso` es el
test que demuestra que validas **toda** la línea: `add a 1 1 extra` tiene que fallar.

## 🎨 Criterios de calidad

Lo que `ctest` no ve y sí se evalúa:

- Ninguna función recibe el `vector` por valor. `const&` para leer, `&` para
  modificar, y solo las de alta y baja lo modifican.
- `main` **no toca `items` directamente** salvo para pasárselo a las funciones y a
  `list_items`. Si hay un `items.push_back` en `main`, la capa está mal repartida.
- Ninguna variable sin `{}`; ningún `using namespace`; ningún `std::endl`.
- `switch` sin `default`: añadir un comando tiene que producir un error de `-Wswitch`.
- Ningún índice se usa sin comprobarlo antes contra `size()`.
- Nombres del dominio y en inglés: `add_book`, `Room`, `price_per_night`.
- Opcional, cuenta como *Update*: un comando `set <name> <quantity>` que modifica un
  registro existente a través de una referencia (`Item& found{items[index]}`), con su
  test.

## 💡 Adaptación a tu dominio

| Dominio | Recurso | `add` | Validación extra con sentido | `total` |
| --- | --- | --- | --- | --- |
| 📚 Biblioteca | `Book` | `add <isbn> <copies> <price>` | ISBN no repetido | valor del fondo |
| 💊 Farmacia | `Medicine` | `add <name> <units> <price>` | unidades ≥ 0 | valor del stock |
| 🏨 Hotel | `Room` | `add <number> <nights> <price_per_night>` | número de habitación único | ingresos previstos |
| 🍽️ Restaurante | `Dish` | `add <name> <servings> <price>` | precio > 0 | facturación |
| 🏋️ Gimnasio | `Member` | `add <id> <months> <monthly_fee>` | meses entre 1 y 12 | ingresos del periodo |
| 🚕 Taxis | `Ride` | `add <plate> <km> <rate_per_km>` | km > 0 | recaudación |

La forma es la misma en todos: un `struct` de tres campos, un `vector`, cinco
funciones, un bucle. Cambia el vocabulario y **las reglas de validación**, que son la
parte que de verdad pertenece a tu dominio.

## 🚦 Cómo entregarlo

```bash
# En tu repositorio bc-cpp-<tu-dominio>
git switch main && git pull
git switch -c week-02
# ... trabaja ...
cmake --preset asan && cmake --build --preset asan && ctest --preset asan
git add -A && git commit -m "feat(week-02): menú CRUD en memoria para <tu-dominio>"
git push -u origin week-02
```

Abre un pull request `week-02` → `main`. En la descripción: qué reglas de validación
has añadido para tu dominio y la salida de `ctest --preset asan`.

## 🧯 Errores comunes

| Error | Por qué pasa | Solución |
| --- | --- | --- |
| `add tornillo 12 0.15 extra` responde `ok` | `read_item` no comprueba que el flujo se haya agotado | `in >> std::ws; return in.eof();` como en el ejercicio 01 |
| `add tornillo 12` responde `ok` con precio 0 | Descartaste el resultado de `in >> ... >> out.price` | El `if (!(in >> ...))` es la validación; sin él no hay validación |
| `error: ignoring return value of 'bool add_item(...)'` | Llamaste a `add_item` sin mirar el `bool` | Ese es el sentido de `[[nodiscard]]`: `if (!add_item(...))` |
| `remove` funciona pero `list` después muestra el registro borrado | Borraste con `pop_back` en vez de `erase(begin() + index)`: quitaste el último, no el buscado | `erase` por posición; comprueba `index != size()` antes |
| `Assertion '__n < this->size()' failed` al hacer `find` de algo que no existe | Indexaste `items[index]` con `index == size()` | Comparar con `size()` **antes** de indexar. Esa aserción es `_GLIBCXX_ASSERTIONS` salvándote |
| El test `total` falla por un céntimo | Redondeaste a mano paso a paso | Calcula con todos los decimales y redondea solo al final, como `{:.2f}` |
| `error: declaration of 'name' shadows a previous local` | Dos `std::string name` en el mismo `case` o uno fuera del `switch` | `-Wshadow` está activo. Cada `case` con llaves `{}` tiene su propio alcance |
| `-Wswitch` al añadir el comando `set` | Falta su `case` | Correcto: es la lista de tareas. Añade el `case` |

## 🔗 Navegación

| Anterior | Actual | Siguiente |
| -------- | ------ | --------- |
| [Ejercicio 02](../2-practicas/ejercicio-02-utilidades-de-cadenas/README.md) | **Proyecto Semana 02** | [Rúbrica](../rubrica-evaluacion.md) |

← [Volver a la Semana 02](../README.md)
