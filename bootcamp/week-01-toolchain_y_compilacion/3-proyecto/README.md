# Proyecto — Semana 01: el esqueleto de tu sistema

> Al terminar esta semana tendrás el repositorio de tu dominio creado, con un
> ejecutable propio construido con CMake que imprime el primer informe de tu recurso.
> Es pequeño; es la base sobre la que se apilan las diecinueve capas siguientes.

## 📦 Qué añade esta semana

**La capa 0: el repositorio y el ciclo de construcción.** Eliges tu dominio, creas
`bc-cpp-<tu-dominio>`, y escribes un programa que declara tres registros de tu recurso
con tipos correctos y calcula sus estadísticas básicas.

Va aquí y no después porque **todo lo demás se construye encima de este ciclo**:
`cmake --preset` → `--build` → `ctest`. Si esta semana no te sale con los ojos
cerrados, la Semana 04 (clases + Catch2) se hace cuesta arriba.

Lo que **no** hay todavía, a propósito: ni funciones (Semana 02), ni entrada del
usuario (Semana 02, cuando sepas validarla), ni ficheros (Semana 10). Tres registros
fijos en el código son suficientes para practicar tipos, constantes y `std::format`.

## 📋 Requisitos verificables

1. **Repositorio** `bc-cpp-<tu-dominio>` con rama `week-01`, con este `README.md` de
   proyecto adaptado y el dominio elegido escrito en la primera línea (ver
   [`docs/dominios.md`](../../../docs/dominios.md)).
2. **`CMakeLists.txt`** con `project(<tu_dominio> LANGUAGES CXX)`, C++20 sin
   extensiones, target `app` con `-Wall -Wextra -Wpedantic -Werror`, y
   `CMakePresets.json` copiado de la plantilla.
3. **Constantes**: al menos una `constexpr` (tasa, límite) y una `const std::string`
   con el nombre del recurso. Ninguna constante mágica suelta en los `format`.
4. **Tres registros** con nombre (`std::string`), cantidad (`int`) y precio o importe
   (`double`), declarados con inicialización uniforme `{}`. Los campos se llaman como en
   tu dominio (`isbn`, `stock`, `price_per_night`...), no `name_a`.
5. **Cabecera** `=== Inventario de <Recurso> ===` (o el sustantivo de tu dominio:
   `Catálogo`, `Censo`, `Carta`...) construida con `std::format` a partir de la
   constante del nombre.
6. **Tabla** de tres filas con columnas alineadas por especificación de ancho de
   `std::format`, precio con dos decimales.
7. **Estadísticas**: total de unidades, valor total, valor con IVA (o el recargo que
   tenga sentido en tu dominio), media de unidades con dos decimales. La media es una
   división **real**.
8. **Porcentaje** del primer registro sobre el total, con un decimal.
9. **Tests**: un `add_test` por cada línea de salida de los requisitos 5-8 (mínimo
   cinco), con los valores calculados a mano para **tus** datos.
10. **`ctest --preset debug` y `ctest --preset asan` en verde**, cero warnings.

## 🧪 Tests mínimos

| Test | Qué comprueba (`PASS_REGULAR_EXPRESSION`) |
| --- | --- |
| `cabecera` | `=== Inventario de <Recurso> ===` (viene en el starter) |
| `total_unidades` | `Total unidades: <N>` con tu N |
| `valor_total` | `Valor total: <X.XX> EUR` |
| `valor_con_iva` | `Valor con IVA: <Y.YY> EUR` |
| `media` | `Media de unidades: <M.MM>` |
| `porcentaje` | `<primer nombre>: <P.P>% del stock` |

Calcula los valores esperados **a mano o con una calculadora** antes de escribir el
test. Un test que copia lo que imprime el programa no comprueba nada.

## 🎨 Criterios de calidad

Lo que `ctest` no ve y sí se evalúa:

- Ninguna variable declarada sin inicializar (`int x;`): todas con `{}`.
- Ningún número mágico dentro de un `std::format`: el IVA, el número de registros y
  el nombre del recurso son constantes con nombre.
- `constexpr` donde el valor se conoce al compilar; `const` donde no.
- Ningún `using namespace std;`. Ningún `std::endl`. Ningún `printf`.
- Los nombres son del dominio y en inglés: `stock`, no `cantidad`; `Book`, no `Item`.
- Un solo `return 0;` al final de `main`, o ninguno.

## 💡 Adaptación a tu dominio

| Dominio | Recurso | Tres registros | "Cantidad" | "Precio" | Estadística con sentido |
| --- | --- | --- | --- | --- | --- |
| 📚 Biblioteca | `Book` | tres títulos | ejemplares | precio de reposición | valor del fondo |
| 💊 Farmacia | `Medicine` | tres medicamentos | unidades en stock | precio unitario | valor del stock con IVA |
| 🏨 Hotel | `Room` | tres habitaciones | noches reservadas | precio por noche | ingresos del mes |
| 🍽️ Restaurante | `Dish` | tres platos | raciones vendidas | precio | facturación del día |
| 🏋️ Gimnasio | `Member` | tres planes | socios en el plan | cuota mensual | ingresos mensuales |
| 🚕 Taxis | `Ride` | tres trayectos | km | tarifa por km | recaudación |

En todos los casos la estructura es la misma: tres registros × (texto, entero, real),
un total, un valor, una media, un porcentaje. Cambia el vocabulario, no la forma.

## 🚦 Cómo entregarlo

```bash
# En tu repositorio bc-cpp-<tu-dominio>
git switch -c week-01
# ... trabaja ...
cmake --preset asan && cmake --build --preset asan && ctest --preset asan
git add -A && git commit -m "feat(week-01): esqueleto del sistema de <tu-dominio>"
git push -u origin week-01
```

Abre un pull request `week-01` → `main` en tu repositorio. En la descripción: tu
dominio, qué compilador y versión has usado, y la salida de `ctest --preset asan`.

## 🧯 Errores comunes

| Error | Por qué pasa | Solución |
| --- | --- | --- |
| La media sale `9` en vez de `9.00`, o sale entera | `total / 3` con dos `int` es división entera, y `{:.2f}` sobre un `int` no compila | `static_cast<double>(total) / 3`, o `total / 3.0` |
| `Valor con IVA` da un céntimo de diferencia respecto a tu cálculo a mano | Redondeaste el valor total **antes** de aplicar el IVA; el programa redondea solo al imprimir | Calcula a mano con todos los decimales y redondea al final, como hace el programa |
| `error: narrowing conversion` al declarar un registro | Escribiste `int stock{12.0}` o `int price{1.5}`: un literal `double` en un `int`. (`double price{1}` sí compila: de `int` a `double` no se pierde nada) | Cada campo con un literal de su tipo: `int` con enteros, `double` con decimales |
| El test `porcentaje` falla aunque el número parece igual | `{:.1f}` da `44.4`; escribiste `44.44` o `44,4` en la expresión regular | Copia el formato exacto: un decimal, punto decimal, `%` sin espacio |
| `-Werror=unused-variable` en un registro | Declaraste un campo que luego no usas en la tabla ni en las estadísticas | O lo usas, o no lo declaras. Un dato que no se usa no existe |
| `Test project ... No tests were found` | El `enable_testing()` está después de los `add_test`, o falta | `enable_testing()` va antes del primer `add_test` |

## 🔗 Navegación

| Anterior | Actual | Siguiente |
| -------- | ------ | --------- |
| [Ejercicio 02](../2-practicas/ejercicio-02-tipos-y-limites/README.md) | **Proyecto Semana 01** | [Rúbrica](../rubrica-evaluacion.md) |

← [Volver a la Semana 01](../README.md)
