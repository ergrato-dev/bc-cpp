# 📌 Política de versiones

Toda dependencia se fija a una **versión exacta**. En CMake eso significa `GIT_TAG` con
un tag, nunca una rama (`main`, `devel`, `master`). Una rama cambia sin avisar y rompe
un starter que compilaba ayer.

## Toolchain mínimo

| Herramienta | Mínimo | Por qué ese mínimo |
| ----------- | ------ | ------------------ |
| CMake | 3.28 | Soporte estable de módulos C++20 y `CMakePresets.json` v6 |
| GCC | 13 | `<format>`, `<ranges>` completos, `std::expected` con `-std=c++23` |
| Clang | 17 | Igual que GCC 13; coroutines y conceptos maduros |
| libstdc++ / libc++ | la del compilador | No se mezclan bibliotecas estándar |
| Ninja | 1.11 | Opcional; los presets lo usan si está |
| gdb | 12 | Pretty printers de la STL que funcionan |
| clang-format / clang-tidy | 17 | Coherentes con Clang 17 |

Ver [`setup.md`](setup.md) para instalarlos en Linux/WSL2.

## Dependencias de los starters

| Biblioteca | Tag exacto | Desde la semana | Uso |
| ---------- | ---------- | --------------- | --- |
| Catch2 | `v3.16.0` | 04 | Tests de todos los starters |
| Google Benchmark | `v1.9.5` | 15 | Microbenchmarks |
| Asio (standalone) | `asio-1-38-2` | 17 | Red asíncrona, coroutines de red |
| nlohmann/json | `v3.12.0` | 17 | JSON en el servidor HTTP (opcional) |

Declaración canónica:

```cmake
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.16.0
  GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Catch2)
```

## Cómo actualizar una versión

1. Comprueba el último tag estable:

   ```bash
   git ls-remote --tags https://github.com/catchorg/Catch2.git | grep -v '\^{}' | sed 's|.*/||' | sort -V | tail -3
   ```

2. Cambia el tag **en esta tabla primero**, luego en todos los starters:

   ```bash
   grep -rl 'GIT_TAG *v3.16.0' bootcamp | xargs sed -i 's/v3.16.0/v3.17.0/'
   ```

3. Compila todo:

   ```bash
   for w in bootcamp/week-*; do ./scripts/compilar-starters.sh "$(basename "$w")" || break; done
   ```

4. Un commit por dependencia: `docs(politica-versiones): sube Catch2 a v3.17.0`.

## Lo que no se hace

- ❌ `GIT_TAG main` / `devel`
- ❌ `find_package` de una biblioteca del sistema en un starter (el estudiante no tiene
  por qué tenerla instalada; `FetchContent` la trae)
- ❌ vcpkg o Conan en los starters. Se enseñan en la Semana 11 como visión de ecosistema,
  no se exigen
- ❌ Dependencias distintas para el mismo fin en semanas distintas (un solo framework
  de tests, un solo benchmark)

_Última verificación de tags: septiembre de 2026._
