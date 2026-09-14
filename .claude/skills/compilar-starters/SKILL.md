---
name: compilar-starters
description: Compila y ejecuta los tests de todos los starters de una semana del bootcamp C++ en debug y asan, y comprueba que los ejercicios fallan con todo comentado y pasan con todo descomentado. Úsalo antes de publicar una semana o tras tocar cualquier starter.
---

# Compilar starters

Un starter que no compila, o cuyos tests no se comportan como el README promete, rompe
el ejercicio entero. Este skill lo comprueba de verdad, no leyendo.

## 1. Estado tal cual está en el repo

```bash
./scripts/compilar-starters.sh week-NN
```

Para cada `starter/` de la semana: `cmake --preset debug`, `cmake --build`, `ctest`;
después lo mismo con `asan`. El script imprime por starter:

- `COMPILA` / `NO COMPILA`
- `TESTS: pasan X / fallan Y`

Reglas de aceptación:

| Starter | Debe compilar | Tests esperados |
| --- | --- | --- |
| Ejercicio, todo comentado | Sí | **Fallan** los de los pasos por descomentar. Ninguno crashea |
| Proyecto, TODOs sin hacer | Sí | Falla el test de ejemplo. Ninguno crashea |

Un starter que **no compila** con todo comentado es un hallazgo crítico: al estudiante
le explota antes de empezar.

## 2. Ejercicios con todo descomentado

Copia el starter a un directorio temporal y quita el prefijo `// ` de las líneas que
siguen a cada banner `PASO N`:

```bash
tmp=$(mktemp -d)
cp -r bootcamp/week-NN-*/2-practicas/ejercicio-MM-*/starter "$tmp/starter"
# ponytail: descomenta todo lo que esté entre un banner "PASO" y el siguiente banner o EOF,
# solo líneas que empiezan por "// " seguido de código (no las que son prosa).
find "$tmp/starter/src" -name '*.cpp' -o -name '*.hpp' | while read -r f; do
  awk '
    /^\/\/ =+$/ { inpaso = 0 }
    /^\/\/ PASO [0-9]+/ { inpaso = 1 }
    /^\/\/ Descomenta/ { next }
    inpaso && /^\/\/ [^ ]/ { sub(/^\/\/ /, ""); print; next }
    inpaso && /^\/\/$/ { print ""; next }
    { print }
  ' "$f" > "$f.tmp" && mv "$f.tmp" "$f"
done
cd "$tmp/starter" && cmake --preset asan && cmake --build --preset asan && ctest --preset asan --output-on-failure
```

Debe pasar el **100 %** de los tests en `asan`. Un test que falla descomentado es un
bug del ejercicio, no del estudiante. Un reporte de ASan/UBSan es crítico.

Si el `awk` no descomenta bien un starter, es señal de que el starter no sigue el
formato de banners de `nuevo-ejercicio.prompt.md`: repórtalo también.

## 3. Compiladores

Comprueba con qué estás compilando:

```bash
g++ --version | head -1
clang++ --version | head -1
cmake --version | head -1
```

El mínimo del bootcamp es GCC 13 / Clang 17 / CMake 3.28. Si tienes menos, lo que
falle por soporte incompleto de C++20 (`<format>`, módulos, `<ranges>` parcial) se
reporta como "sin verificar en este entorno", no como fallo del starter, y se dice qué
versión tienes. Si tienes ambos compiladores, pasa el script dos veces con
`CXX=g++` y `CXX=clang++`.

## 4. Qué mirar además de compilar

- `FetchContent_Declare` con `GIT_TAG` exacto y que coincide con
  `docs/politica-versiones.md`.
- `-Wall -Wextra -Wpedantic -Werror` en todos los targets del starter.
- `CMAKE_CXX_EXTENSIONS OFF`.
- `CMakePresets.json` idéntico a `docs/plantillas/CMakePresets.json`.
- Sin `build/` ni `solution/` dentro del starter.

## 5. Informe

Por starter, una línea:

```
week-NN/2-practicas/ejercicio-01-x/starter: ✅ compila · comentado: 0/6 pasan · descomentado: 6/6 pasan · asan limpio
week-NN/3-proyecto/starter:                 ✅ compila · TODOs: 0/1 pasan
week-NN/2-practicas/ejercicio-02-y/starter: 🔴 no compila con todo comentado: <primera línea del error>
```

Y al final la versión de compilador y CMake con la que verificaste. Sin elogios.
