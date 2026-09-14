# CLAUDE.md

Instrucciones para agentes que trabajan sobre este repositorio.

## Qué es esto

Bootcamp de **C++ moderno (C++20)**, 20 semanas, 200 horas, autoestudio. De cero
absoluto a desarrollador C++ avanzado: fundamentos, RAII, templates, STL, concurrencia,
coroutines, rendimiento, sistemas, redes y producción.

## Fuente de verdad de las convenciones

**[`.github/copilot-instructions.md`](.github/copilot-instructions.md)** contiene el
molde completo: malla curricular, estructura de cada semana, reglas de longitud,
convenciones de código y de escritura, paleta de los SVG, reglas de seguridad del
contenido y el checklist de publicación de una semana.

Léelo **antes** de generar contenido. No deduzcas el patrón mirando archivos sueltos.

## Generadores

En `.github/prompts/` hay siete plantillas ejecutables:

| Prompt | Genera |
| ------ | ------ |
| `nueva-semana.prompt.md` | El esqueleto completo de una semana |
| `nueva-teoria.prompt.md` | Un archivo de `1-teoria/` |
| `nuevo-ejercicio.prompt.md` | Un ejercicio de `2-practicas/` con su `starter/` |
| `nuevo-proyecto.prompt.md` | El `3-proyecto/` de una semana |
| `svg-diagrama.prompt.md` | Un diagrama de `0-assets/` |
| `commit-message.prompt.md` | El mensaje de commit |
| `security-review.prompt.md` | Revisión de UB, memoria y entrada sin validar |

## Agentes y skills

- `.claude/agents/curriculo-coherencia-reviewer.md` — malla vs contenido, horas,
  prerrequisitos, progresión
- `.claude/agents/veracidad-cpp-reviewer.md` — afirmaciones sobre el estándar y el
  compilador, verificadas compilando o en cppreference
- `.claude/skills/verificar-estructura/` — una semana está completa y enlazada
- `.claude/skills/compilar-starters/` — todos los starters compilan y sus tests se
  comportan como deben (fallan con todo comentado, pasan con todo descomentado)
- `.claude/skills/verificar-progresion/` — ningún concepto usado antes de su semana

## Reglas duras

1. **Todo fragmento de código compila.** Teoría incluida. Con
   `-std=c++20 -Wall -Wextra -Wpedantic -Werror`, en GCC 13+ y Clang 17+. Si es un
   ejemplo de fallo, se dice qué falla y con qué mensaje exacto.

2. **Verifica contra el compilador de verdad.** Este entorno tiene `g++` y `clang++`.
   Antes de afirmar algo sobre un diagnóstico, un warning o una optimización, compílalo.
   Antes de afirmar algo sobre el estándar, búscalo en cppreference y enlázalo.

3. **Cero absoluto de verdad.** Cada término técnico se define la primera vez que
   aparece. "Stack", "heap", "símbolo", "enlace", "UB", "ABI" y "vtable" no son
   vocabulario común.

4. **Progresión estricta.** Ninguna semana usa lo que se enseña después. Sin smart
   pointers antes de la 05, sin templates antes de la 07, sin lambdas antes de la 09,
   sin excepciones antes de la 10, sin threads antes de la 13. La malla está en
   `copilot-instructions.md`; consúltala antes de escribir un starter.

5. **Sin UB sin marcar.** Todo ejemplo con comportamiento indefinido lleva
   `// ❌ UB:`, la razón, y el sanitizer o flag que lo detecta. "Funciona en mi
   máquina" no es un argumento.

6. **Profundidad sobre cobertura.** Mejor tres conceptos bien explicados que veinte
   listados. Extensión de un archivo de teoría: 200-300 líneas. Si se pasa, es que
   mezcla dos temas: divídelo, no lo recortes.

7. **El porqué antes del cómo.** Ninguna regla de C++ sin el problema que resuelve.

8. **Todo entregable, verificable.** Con `ctest`. Los ejercicios traen los tests
   escritos; el proyecto exige tests mínimos nombrados en su README.

9. **Diagramas en SVG**, con la paleta del bootcamp, tema oscuro, sin degradados, con
   `role="img"` y `aria-label`. Nunca ASCII art. Nunca capturas de pantalla.

10. **Sin `solution/`.** `**/solution/` está en `.gitignore`. El código comentado de
    los ejercicios es la solución. Nunca crees ni comitees esa carpeta.

11. **Una semana por tanda.** La Semana 01 es la plantilla de calidad.

## Antes de dar por terminada una tanda

```bash
./scripts/verificar-enlaces.sh
./scripts/compilar-starters.sh week-NN
```

El primero comprueba nombres de carpeta, enlaces relativos, navegación y SVG huérfanos.
El segundo configura, compila y ejecuta los tests de cada `starter/` de la semana en
`debug` y `asan`.

## Estructura

```
bootcamp/week-NN-slug/   20 semanas, ver .github/copilot-instructions.md
docs/                    setup, versiones, dominios, hilo conductor, trucos, plantillas
scripts/                 verificar-enlaces.sh, compilar-starters.sh
assets/                  header del README
```

## Idioma

Español para la prosa y los comentarios educativos. Inglés para el código, los
identificadores, los nombres del estándar y los mensajes de commit
(Conventional Commits: `feat(week-01): ...`).
