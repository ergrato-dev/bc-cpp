#!/usr/bin/env bash
# Verifica integridad estructural del bootcamp:
#   1. Nombres de carpeta week-NN-slug bien formados.
#   2. Enlaces relativos en markdown que resuelven a una ruta real.
#   3. Sección "Navegación" en el README de cada semana.
#   4. SVG de 0-assets/ y assets/ enlazados desde algún .md.
#   5. Ninguna carpeta solution/ ni build/ dentro de bootcamp/.
#   6. Todo FetchContent_Declare lleva GIT_TAG (nunca una rama).
#
# Uso: scripts/verificar-enlaces.sh
# Salida: lista de problemas encontrados; exit code 1 si hay al menos uno.

set -u
cd "$(dirname "$0")/.." || exit 1

fail=0

echo "== 1. Nombres de carpeta =="
while IFS= read -r d; do
  name=$(basename "$d")
  if ! [[ "$name" =~ ^week-[0-9]{2}-[a-z0-9_]+$ ]]; then
    echo "NOMBRE INVALIDO (week): $d"
    fail=1
  fi
done < <(find bootcamp -mindepth 1 -maxdepth 1 -type d -iname "week-*" 2>/dev/null)

echo "== 2. Enlaces relativos en markdown =="
# ponytail: no parsea markdown de verdad, solo strip de fences ``` y luego
# grep de enlaces "](...)" . Falsos positivos conocidos: URLs con paréntesis
# anidados. Si el script reporta algo distinto a eso, es un enlace roto real.
while IFS= read -r f; do
  content=$(awk '/^```/{c=!c; next} !c' "$f")
  while IFS= read -r link; do
    [ -z "$link" ] && continue
    clean="${link%%#*}"
    [ -z "$clean" ] && continue
    case "$clean" in http*|\<http*|mailto:*|\#*|/*) continue ;; esac
    dir=$(dirname "$f")
    resolved=$(realpath -m "$dir/$clean")
    if [ ! -e "$resolved" ]; then
      echo "ENLACE ROTO: $f -> $link"
      fail=1
    fi
  done < <(printf '%s\n' "$content" | grep -oE '\]\([^)]+\)' | sed -E 's/^\]\(//;s/\)$//')
# .claude/ y .github/prompts/ contienen plantillas con rutas de ejemplo que no
# resuelven por diseño.
done < <(find . -iname "*.md" -not -path "./.git/*" -not -path "*/build/*" \
           -not -path "./.claude/*" -not -path "./.github/prompts/*")

echo "== 3. Navegación anterior/siguiente en README de cada semana =="
while IFS= read -r rm; do
  if ! grep -q "Navegación" "$rm"; then
    echo "SIN NAVEGACION: $rm"
    fail=1
  fi
done < <(find bootcamp -mindepth 2 -maxdepth 2 -iname "README.md" 2>/dev/null)

echo "== 4. SVG huérfanos y XML válido =="
while IFS= read -r svg; do
  base=$(basename "$svg")
  if ! python3 -c "import xml.dom.minidom,sys; xml.dom.minidom.parse(sys.argv[1])" "$svg" 2>/dev/null; then
    echo "SVG MAL FORMADO (XML inválido; GitHub no lo renderiza): $svg"
    fail=1
  fi
  if ! grep -rqF "$base" --include="*.md" .; then
    echo "SVG HUERFANO (no enlazado desde ningún .md): $svg"
    fail=1
  fi
done < <(find bootcamp assets -iname "*.svg" 2>/dev/null)

echo "== 5. Carpetas prohibidas =="
# solution/ no puede existir ni en disco; build/ es local (gitignore) pero nunca versionado.
while IFS= read -r d; do
  echo "CARPETA PROHIBIDA: $d"
  fail=1
done < <(find bootcamp -type d -name solution 2>/dev/null)
if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  while IFS= read -r f; do
    [ -z "$f" ] && continue
    echo "BUILD VERSIONADO: $f"
    fail=1
  done < <(git ls-files bootcamp | grep -E '/build/' )
fi

echo "== 6. FetchContent con GIT_TAG exacto =="
while IFS= read -r cm; do
  # Cada bloque FetchContent_Declare( ... ) debe contener GIT_TAG y no ser una rama.
  awk -v file="$cm" '
    /FetchContent_Declare\(/ { inblock=1; hastag=0; block=""; next }
    inblock { block = block $0 "\n" }
    inblock && /GIT_TAG/ {
      hastag=1
      if ($0 ~ /GIT_TAG[ \t]+(main|master|devel|develop|dev|HEAD)([ \t]|$)/) {
        print "GIT_TAG ES UNA RAMA: " file ": " $0; exit 1
      }
    }
    inblock && /^\)/ { inblock=0; if (!hastag) { print "FETCHCONTENT SIN GIT_TAG: " file; exit 1 } }
  ' "$cm" || fail=1
done < <(find bootcamp -name CMakeLists.txt -not -path "*/build/*" 2>/dev/null)

if [ "$fail" -eq 0 ]; then
  echo "OK: sin problemas detectados."
fi
exit "$fail"
