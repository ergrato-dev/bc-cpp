#!/usr/bin/env bash
# Configura, compila y ejecuta los tests de cada starter/ de una semana.
#
# Uso: scripts/compilar-starters.sh week-NN [preset ...]
#   preset: debug | release | asan | tsan   (por defecto: debug asan)
#
# Para cada starter imprime COMPILA / NO COMPILA y el recuento de tests.
# Un starter tal cual está en el repo (código comentado, TODOs sin hacer)
# tiene que COMPILAR y puede tener tests que fallan: eso no es error aquí.
# Lo que sí es error: no configurar, no compilar, o que un test crashee
# (señal SIGSEGV/SIGABRT o reporte de sanitizer).
#
# Exit code 1 si algún starter no compila o algún test crashea.

set -u
cd "$(dirname "$0")/.." || exit 1

week="${1:-}"
shift || true
presets=("$@")
[ "${#presets[@]}" -eq 0 ] && presets=(debug asan)

if [ -z "$week" ]; then
  echo "Uso: $0 week-NN [preset ...]" >&2
  exit 2
fi

dir=$(find bootcamp -mindepth 1 -maxdepth 1 -type d -name "${week}*" | head -1)
if [ -z "$dir" ]; then
  echo "No existe ninguna carpeta bootcamp/${week}*" >&2
  exit 2
fi

fail=0
count=0

while IFS= read -r starter; do
  count=$((count + 1))
  for preset in "${presets[@]}"; do
    log=$(mktemp)
    if ! cmake -S "$starter" --preset "$preset" >"$log" 2>&1; then
      echo "$starter [$preset]: 🔴 NO CONFIGURA: $(grep -m1 -E 'Error|error' "$log")"
      fail=1; rm -f "$log"; continue
    fi
    if ! cmake --build "$starter/build/$preset" >"$log" 2>&1; then
      echo "$starter [$preset]: 🔴 NO COMPILA: $(grep -m1 -E 'error:' "$log")"
      fail=1; rm -f "$log"; continue
    fi
    # ctest devuelve != 0 si hay tests que fallan; eso aquí es informativo.
    ctest --test-dir "$starter/build/$preset" --output-on-failure >"$log" 2>&1
    # ctest imprime "N% tests passed, F tests failed out of T" (con 100% no hay F).
    total=$(grep -oE 'out of [0-9]+' "$log" | grep -oE '[0-9]+$' || echo 0)
    failed=$(grep -oE '[0-9]+ tests failed' "$log" | grep -oE '^[0-9]+' || echo 0)
    passed=$((total - failed))
    if grep -qE 'SIGSEGV|SIGABRT|AddressSanitizer|UndefinedBehaviorSanitizer|ThreadSanitizer|runtime error:' "$log"; then
      echo "$starter [$preset]: 🔴 COMPILA · TESTS CRASHEAN: $(grep -m1 -E 'SIGSEGV|SIGABRT|Sanitizer|runtime error:' "$log")"
      fail=1
    else
      echo "$starter [$preset]: ✅ COMPILA · TESTS: pasan $passed / $total"
    fi
    rm -f "$log"
  done
done < <(find "$dir" -type d -name starter -not -path "*/build/*" | sort)

if [ "$count" -eq 0 ]; then
  echo "Sin starters en $dir"
  exit 0
fi

if [ "$fail" -eq 0 ]; then
  echo "OK: $count starters compilados con presets: ${presets[*]}."
fi
exit "$fail"
