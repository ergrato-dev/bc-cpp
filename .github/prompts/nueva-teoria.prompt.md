---
mode: agent
description: Genera un archivo de teoría de una semana del bootcamp C++ Zero to Hero.
---

# Nueva teoría

Genera `bootcamp/week-{{NN}}-{{SLUG}}/1-teoria/{{MM}}-{{TEMA}}.md`.

Lee antes [`.github/copilot-instructions.md`](../copilot-instructions.md).

## Estructura obligatoria

```markdown
# Título del tema

> Una línea que diga por qué esto importa. No un resumen.

## 🎯 Objetivos

## 1. Qué problema resuelve

## 2. Cómo funciona

## 3. Cómo se escribe en C++20

## 4. Antipatrones

## 5. Trucos

## 📚 Recursos Adicionales

## ✅ Checklist de Verificación
```

Las secciones numeradas pueden ser más de cinco y llevar `###` dentro. Las de emoji son
fijas y van siempre, en ese orden.

## Extensión

**200-300 líneas.** Objetivo ~250.

Si te pasas de 300, el archivo mezcla dos temas: **divídelo en dos archivos**, no lo
recortes. Un archivo = un concepto. Si el título necesita una "y", sospecha.

## Reglas de escritura

- **Español** para la prosa, **inglés** para el código, los identificadores y los
  nombres del estándar. Primera mención de cada término con su nombre inglés entre
  paréntesis: `referencia a rvalue (rvalue reference)`.
- **Cero absoluto.** Cada término técnico se define la primera vez que aparece. No
  asumas vocabulario de informática, ni de C, ni de otro lenguaje.
- **Segunda persona informal**, frases cortas, sin relleno.
- **El porqué antes del cómo**, siempre.
- **Sin ASCII art.** Los diagramas son SVG en `../0-assets/`, referenciados como
  `![Descripción accesible](../0-assets/NN-nombre.svg)`.
- **Sin capturas de pantalla.**

## Reglas del código

- **Todo fragmento compila** con `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror`.
  Compruébalo pegándolo en un `.cpp`. Un fragmento parcial lleva `// ...` donde omite
  y se dice qué falta.
- Los ejemplos de lo que **no** hacer llevan `// ❌` y **el diagnóstico real** que
  producen: el warning, el error del compilador, la salida de ASan/UBSan, o la razón
  de que sea UB si nada lo detecta.
- Los ejemplos correctos llevan `// ✅` cuando contrastan con un ❌.
- Identificadores en inglés, comentarios educativos en español.
- **Ningún concepto de una semana posterior.** Si necesitas algo que se enseña después,
  envuélvelo en una función y di "esto lo verás en la Semana NN". Consulta la malla.
- Lo que sea C++23 lleva el bloque:

```markdown
> [!NOTE]
> **C++23** · `nombre exacto`. En C++20 estricto, la alternativa es *(concreta)*; la
> diferencia es *(en qué se nota)*, y es suficiente para los entregables de esta semana.
```

## Bloques que se usan

- Tablas para comparativas y para "antipatrón → por qué duele → qué hacer".
- Callouts GFM: `> [!NOTE]`, `> [!TIP]`, `> [!IMPORTANT]`, `> [!WARNING]`, `> [!CAUTION]`.
- `> [!WARNING]` obligatorio antes de cualquier ejemplo que muestre UB, aunque sea
  para explicarlo.

## Antipatrones y trucos

La sección `## 4. Antipatrones` no es opcional y no es relleno. Cada antipatrón dice
**qué hace la gente**, **por qué duele** (con el diagnóstico o el bug concreto) y **qué
hacer en su lugar**. Salen de errores reales, no de "no hacer las cosas mal".

La sección `## 5. Trucos` solo admite lo que ahorra tiempo real o revela algo que el
compilador o la herramienta esconden: un flag, un comando de gdb, un truco de Compiler
Explorer, una opción de CMake. Lo que entre aquí se replica en el README de la semana
y en `docs/trucos-cpp.md`.

## Recursos adicionales

Entre dos y cuatro entradas, **cada una con una línea de por qué vale la pena**. Nunca
un enlace desnudo. cppreference primero cuando exista la página.

## Checklist de verificación

Entre cinco y ocho ítems `- [ ]`, verificables por el estudiante sin ayuda. Comprueban
comprensión y capacidad de escribir o diagnosticar, no memoria.

## Verificación antes de entregar

- [ ] Entre 200 y 300 líneas
- [ ] Cada término técnico nuevo definido donde aparece
- [ ] Cada fragmento de código compilado de verdad, o marcado ❌ con su diagnóstico
- [ ] Ningún concepto de una semana posterior sin su aviso
- [ ] Los SVG que referencio existen en `../0-assets/`
- [ ] No he inventado ninguna función, header ni regla del estándar
