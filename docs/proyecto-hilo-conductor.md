# 🧵 Proyecto hilo conductor

El estudiante construye **un solo sistema** durante 20 semanas, en su dominio (ver
[`dominios.md`](dominios.md)). Cada semana añade una capa; ninguna capa depende de una
posterior. Al final tiene una biblioteca, una CLI, un servidor HTTP, tests, benchmarks
y CI: un proyecto de portfolio, no veinte ejercicios sueltos.

Nombre del repositorio del estudiante: `bc-cpp-<tu-dominio>` (por ejemplo
`bc-cpp-biblioteca`). Una rama por semana: `week-01` … `week-20`. La rama `main`
acumula.

## Capas por semana

| Semana | Capa que se añade | Qué existe al terminar |
| ------ | ----------------- | ---------------------- |
| 01 | Esqueleto | Ejecutable con CMake propio que define el recurso del dominio con tipos y constantes, calcula estadísticas de tres registros fijos y las imprime con `std::format` |
| 02 | Menú CRUD en memoria | `std::vector<Recurso>`, funciones libres de alta, baja, búsqueda, listado. Validación de entrada |
| 03 | Estructura propia | Una pila o cola dinámica propia (con `new`/`delete`, la única vez) para el historial de operaciones |
| 04 | Modelo con invariantes | El recurso como `class` con constructor validado, RAII, `operator<=>`. Primeros tests Catch2 |
| 05 | Propiedad clara | `Repository` con `unique_ptr`; relaciones con `shared_ptr`/`weak_ptr` donde toque. Sin `new`/`delete` |
| 06 | Jerarquía | Procesadores/notificadores polimórficos (`Exporter`, `Validator`...) con interfaz abstracta |
| 07 | Genericidad | `Repository<T>` con conceptos; reutilizable para el segundo tipo del dominio |
| 08 | Índices | Búsqueda por varias claves con `map`/`unordered_map`; elección justificada por complejidad |
| 09 | Consultas | Reportes y agregaciones con `<algorithm>` y ranges; filtros componibles |
| 10 | Errores modelados | Carga robusta desde CSV con `expected`/`optional`; ningún `exit()` ni `abort()` |
| 11 | Biblioteca + CLI | Reestructurado como `lib<dominio>` + `cli` + `tests`; `clang-tidy` y `clang-format` en el build |
| 12 | Serialización genérica | Serializador CSV/JSON basado en traits; `constexpr` donde compense |
| 13 | Procesado paralelo | Importación por lotes con thread pool; TSan limpio |
| 14 | Pipeline asíncrono | Generadores con coroutines para recorrer el repositorio; `latch`/`barrier` en la carga |
| 15 | Rendimiento medido | Benchmarks de los índices de la 08; al menos una optimización con antes/después |
| 16 | Persistencia | Almacenamiento binario propio con índice; `filesystem` para rutas y backups |
| 17 | Servidor HTTP | API REST del dominio con Asio + coroutines; `GET`/`POST`/`DELETE` sobre el recurso |
| 18 | Endurecido | ASan/UBSan/TSan en CI; fuzzer del parser CSV y del parser HTTP; GitHub Actions |
| 19 | Diseño final | Refactor a capas; API pública con pimpl; instalable con `cmake --install`; Doxygen |
| 20 | Entrega | Sistema completo, README de usuario, presentación técnica, code review cruzado |

## Reglas

- **Ninguna capa depende de una posterior.** Si la Semana 08 necesita algo de la 10,
  la malla está mal y se reporta, no se parchea.
- **Cada capa deja tests.** Los mínimos los nombra el `3-proyecto/README.md` de la
  semana; el estudiante puede añadir más.
- **`ctest --preset asan` en verde** es el criterio de entrega de toda semana desde la
  04. Desde la 13, también `tsan`.
- **El starter de cada semana es autocontenido**: incluye lo mínimo de las capas
  previas para compilar solo, pero el estudiante trabaja sobre **su** repositorio, no
  sobre el starter. El starter es la referencia de qué firmas se esperan.
- **Versionado**: antes de empezar una semana, `git switch -c week-NN` desde `main`.
  Al terminar, pull request `week-NN` → `main` en el repositorio del estudiante.

## Qué evalúa cada capa

| Fase | Se evalúa sobre todo |
| ---- | -------------------- |
| 01-04 | Que compila sin warnings, que la entrada se valida, que hay invariantes |
| 05-10 | Ownership correcto, elección de contenedor y de mecanismo de error justificada |
| 11-17 | Estructura del proyecto, corrección concurrente (TSan), mediciones reales |
| 18-20 | Robustez (fuzz + sanitizers), calidad de API, documentación, presentación |
